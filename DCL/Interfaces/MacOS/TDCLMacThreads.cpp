// ==============================
// Fichier:			TDCLMacThreads.cp
// Projet:			Desktop Connection Library
//
// Cr�� le:			27/10/2002
// Tabulation:		4 espaces
//
// ***** BEGIN LICENSE BLOCK *****
// Version: MPL 1.1
//
// The contents of this file are subject to the Mozilla Public License Version
// 1.1 (the "License"); you may not use this file except in compliance with
// the License. You may obtain a copy of the License at
// http://www.mozilla.org/MPL/
//
// Software distributed under the License is distributed on an "AS IS" basis,
// WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
// for the specific language governing rights and limitations under the
// License.
//
// The Original Code is TDCLMacThreads.cp.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2002-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLMacThreads.cp,v 1.5 2004/11/24 14:09:00 paul Exp $
// ===========

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/MacOS/TDCLMacThreads.h>

// DCL
#include <DCL/Exceptions/Errors/TDCLLimitReachedError.h>
#include <DCL/Exceptions/Errors/TDCLUnknownError.h>
#include <DCL/Exceptions/Thread_Exceptions/TDCLSemaphoreBusyException.h>
#include <DCL/Exceptions/Thread_Exceptions/TDCLThreadActiveException.h>
#include <DCL/Exceptions/Thread_Exceptions/TDCLThreadStoppedException.h>
#include <DCL/Interfaces/TDCLThread.h>

///
/// Structure pour le r�veil programm�.
///
typedef struct
{
	TMTask			fTask;			///< T�che du TM pour nous r�veiller
	ThreadID		fThreadID;		///< R�f�rence sur le processus l�ger �
									///< r�veiller
	ThreadTaskRef	fTaskRef;		///< Contexte (n�cessaire pour r�veiller
									///< depuis l'interruption)
	Boolean			fExpired;		///< Si on a �t� r�veill� par la t�che.
} TMTaskExtended;

// ------------------------------------------------------------------------- //
//  * TDCLMacThreads( void )
// ------------------------------------------------------------------------- //
TDCLMacThreads::TDCLMacThreads( void )
	:
		mTimerProcUPP( NewTimerUPP((TimerProcPtr) TimerProc ) )
{
	// Gaz � tous les �tages.
}

// ------------------------------------------------------------------------- //
//  * ~TDCLMacThreads( void )
// ------------------------------------------------------------------------- //
TDCLMacThreads::~TDCLMacThreads( void )
{
	DisposeTimerUPP( mTimerProcUPP );
}

// ------------------------------------------------------------------------- //
//  * Yield( void )
// ------------------------------------------------------------------------- //
void
TDCLMacThreads::Yield( void )
{
	(void) ::YieldToAnyThread();
}

// ------------------------------------------------------------------------- //
//  * TimerProc( TMTaskPtr inTMTaskPtr )
// ------------------------------------------------------------------------- //
void
TDCLMacThreads::TimerProc( TMTaskPtr inTMTaskPtr )
{
	OSErr theErr = ::SetThreadReadyGivenTaskRef(
		((TMTaskExtended*) inTMTaskPtr)->fTaskRef,
		((TMTaskExtended*) inTMTaskPtr)->fThreadID );

	if (theErr == noErr)
	{
		((TMTaskExtended*) inTMTaskPtr)->fExpired = true;
	}
}

// ------------------------------------------------------------------------- //
//  * CreateThread( TDCLThread* )
// ------------------------------------------------------------------------- //
TDCLMacThreads::IThread*
TDCLMacThreads::CreateThread( TDCLThread* inThreadedObject )
{
	return new TThread( this, inThreadedObject );
}

// ------------------------------------------------------------------------- //
//  * CreateSemaphore( void )
// ------------------------------------------------------------------------- //
TDCLMacThreads::ISemaphore*
TDCLMacThreads::CreateSemaphore( void )
{
	return new TSemaphore( this );
}

// ------------------------------------------------------------------------- //
//  * TSemaphore( void )
// ------------------------------------------------------------------------- //
TDCLMacThreads::TSemaphore::TSemaphore( TDCLMacThreads* inThreadsIntf )
	:
		mThreads( inThreadsIntf ),
		mSemaphore( false )	// Le s�maphore est libre
{
	// Initialisation de la queue.
	mQueue.qFlags = 0;
	mQueue.qHead = nil;
	mQueue.qTail = nil;
}

// ------------------------------------------------------------------------- //
//  *�~TSemaphore( void )
// ------------------------------------------------------------------------- //
TDCLMacThreads::TSemaphore::~TSemaphore( void )
{
	if (mSemaphore)
	{
		throw DCLSemaphoreBusy;
	}
}

// ------------------------------------------------------------------------- //
//  *�Acquire( void )
// ------------------------------------------------------------------------- //
void
TDCLMacThreads::TSemaphore::Acquire( void )
{
	QElem	myElem;

	// Initialisation de l'�l�ment
	myElem.qLink = nil;
	myElem.qType = dummyType;

	while ( true )
	{
		// Attente jusqu'� ce que le s�maphore ait �t� lib�r�.

		if ( mSemaphore == false )
		{
			// Cette op�ration est atomique.
			::Enqueue( &myElem, &mQueue );
		
			Boolean	done = false;
			
			// Suis-je le premier dans la queue.
			if ( mQueue.qHead == &myElem )
			{
				// Vivi. J'ai le droit de jouer avec le s�maphore.
			
				if ( mSemaphore == false )
				{
					mSemaphore = true;
					done = true;
				} // Sinon, je continue � boucler.
			}

			// Suppression de l'�l�ment de la liste.
			OSErr theErr = ::Dequeue ( &myElem, &mQueue );
			if (theErr != noErr)
			{
				throw DCLPlatformUnknownError( theErr );
			}
	
			// Termin�?
			if (done)
			{
				break;
			}
		}

		// On passe un peu de temps � faire autre chose.
		mThreads->Yield();
	}
}

// ------------------------------------------------------------------------- //
//  *�Release( void )
// ------------------------------------------------------------------------- //
void
TDCLMacThreads::TSemaphore::Release( void )
{
	// Je marque juste le s�maphore comme libre.
	mSemaphore = false;
}

// ------------------------------------------------------------------------- //
//  * TThread( void )
// ------------------------------------------------------------------------- //
TDCLMacThreads::TThread::TThread(
				TDCLMacThreads* inThreadsIntf,
				TDCLThread* inThreadedObject )
	:
		IThread( inThreadedObject ),
		mThreadID( kNoThreadID ),
		mState( kStopped ),
		mMutex( inThreadsIntf ),
		mRunTPP( (ThreadEntryTPP) NewThreadEntryUPP( (ThreadEntryProcPtr) Run ) ),
		mThreads( inThreadsIntf ),
		mWakeCount( 0 )
{
	// This space for rent.
}

// ------------------------------------------------------------------------- //
//  * TThread( void )
// ------------------------------------------------------------------------- //
TDCLMacThreads::TThread::~TThread( void )
{
	if (mState != kStopped)
	{
		throw DCLThreadActive;
	}
	
	if (mRunTPP)
	{
		DisposeThreadEntryUPP( mRunTPP );
	}
}

// ------------------------------------------------------------------------- //
//  * Start( void )
// ------------------------------------------------------------------------- //
void
TDCLMacThreads::TThread::Start( void ) 
{
	if (mState != kStopped)
	{
		throw DCLThreadActive;
	}
	
	// On synchronise.
	mMutex.Acquire();
	
	OSErr theErr = ::NewThread(
						kCooperativeThread,
						mRunTPP,
						this,
						0 /* Default stack size */,
						kCreateIfNeeded,
						nil,
						&mThreadID );
	
	switch ( theErr )
	{
		case 0:
			break;
	
		case threadTooManyReqsErr:
			mMutex.Release();
			throw DCLPlatformLimitReachedError( theErr );
		
		case threadNotFoundErr:	// Probl�mes d'arguments (ne doit pas arriver)
		case threadProtocolErr:
		default:
			mMutex.Release();
			throw DCLPlatformUnknownError( theErr );
	}

	// Attente que Run soit appel� et mState mis � jour.
	mMutex.Acquire();

	// Lib�ration du mutex.
	mMutex.Release();
}

// ------------------------------------------------------------------------- //
//  * Stop( void )
// ------------------------------------------------------------------------- //
void
TDCLMacThreads::TThread::Stop( void ) 
{
	if (mState == kStopped)
	{
		throw DCLThreadStopped;
	}

	mState = kStopped;
	
	OSErr theErr = ::DisposeThread( mThreadID, nil, false );
	
	mThreadID = kNoThreadID;
	
	switch ( theErr )
	{
		case 0:
			break;
	
		case threadTooManyReqsErr:
			throw DCLPlatformLimitReachedError( theErr );
		
		case threadNotFoundErr:	// Probl�mes d'arguments (ne doit pas arriver)
		case threadProtocolErr:
		default:
			throw DCLPlatformUnknownError( theErr );
	}
}

// ------------------------------------------------------------------------- //
//  * Suspend( void )
// ------------------------------------------------------------------------- //
void
TDCLMacThreads::TThread::Suspend( void ) 
{
	if (mState == kStopped)
	{
		throw DCLThreadStopped;
	}
	
	if (mState == kRunning)
	{
		mState = kSuspended;

		OSErr theErr = ::SetThreadState(
							mThreadID, kStoppedThreadState, kNoThreadID );
	
		switch ( theErr )
		{
			case 0:
				break;
		
			case threadTooManyReqsErr:
				throw DCLPlatformLimitReachedError( theErr );
			
			case threadNotFoundErr:	// Probl�mes d'arguments (ne doit pas arriver)
			case threadProtocolErr:
			default:
				throw DCLPlatformUnknownError( theErr );
		}
	}
}

// ------------------------------------------------------------------------- //
//  * Resume( void )
// ------------------------------------------------------------------------- //
void
TDCLMacThreads::TThread::Resume( void ) 
{
	if (mState == kStopped)
	{
		throw DCLThreadStopped;
	}
	
	if (mState == kSuspended)
	{
		mState = kRunning;
		
		OSErr theErr = ::SetThreadState(
							mThreadID, kRunningThreadState, kNoThreadID );
	
		switch ( theErr )
		{
			case 0:
				break;
		
			case threadTooManyReqsErr:
				throw DCLPlatformLimitReachedError( theErr );
			
			case threadNotFoundErr:	// Probl�mes d'arguments (ne doit pas arriver)
			case threadProtocolErr:
			default:
				throw DCLPlatformUnknownError( theErr );
		}
	}
}

// ------------------------------------------------------------------------- //
//  * Sleep( KUInt32 )
// ------------------------------------------------------------------------- //
Boolean
TDCLMacThreads::TThread::Sleep( KUInt32 inMilliseconds /* = kForever */ )
{
	Boolean theResult;
	
	// Le nombre de r�veil est-il nul?
	if (mWakeCount > 0)
	{
		mWakeCount--;
		theResult = false;	// On n'a pas dormi tout le temps demand�.
	} else {
		if (inMilliseconds == kForever)
		{
			OSErr theErr = ::SetThreadState(
								mThreadID, kStoppedThreadState, kNoThreadID );
			if (theErr != noErr)
			{
				throw DCLPlatformUnknownError( theErr );
			}

			theResult = true;	// On a toujours �t� r�veill�.
		} else {
			TMTaskExtended theSleepTask;

			// Initialisation de la structure pour le TimeManager.
			theSleepTask.fTask.qLink		= NULL;
			theSleepTask.fTask.qType		= 0;
			theSleepTask.fTask.tmAddr		= mThreads->mTimerProcUPP;
			theSleepTask.fTask.tmCount		= 0;
			theSleepTask.fTask.tmWakeUp		= 0;
			theSleepTask.fTask.tmReserved	= 0;

			theSleepTask.fThreadID = mThreadID;
			
			// On note la r�f�rence sur l'application.
			OSErr theErr = ::GetThreadCurrentTaskRef( &theSleepTask.fTaskRef );
			if (theErr != noErr)
			{
				throw DCLPlatformUnknownError( theErr );
			}
			
			// On installe cette t�che.
			::InsTime( (QElemPtr) &theSleepTask );
			
			// On lance la t�che pour dans inMilliseconds.
			Boolean doItTwice = false;
			KUInt32 theMilliseconds = inMilliseconds;
			if (inMilliseconds & 0x80000000)
			{
				theMilliseconds = inMilliseconds / 2;
				doItTwice = true;
			}
			
			do {
				// Par d�faut, on n'a pas dormi tout le temps.
				theSleepTask.fExpired = false;
				
				::PrimeTime( (QElemPtr) &theSleepTask, (long) (theMilliseconds) );
			
				// Ensuite, on dort.
				theErr = ::SetThreadState( mThreadID, kStoppedThreadState, kNoThreadID );
				if (theErr != noErr)
				{
					// Nettoyage.
					::RmvTime( (QElemPtr) &theSleepTask );
					throw DCLPlatformUnknownError( theErr );
				}
			
				// On vient d'�tre r�veill�.
				// Doit-on retourner faire un petit somme?	
				if (doItTwice && theSleepTask.fExpired)
				{
					doItTwice = false;
				} else {
					break;
				}
			} while ( true );
			
			// Il s'agit finalement d'enlever la t�che.
			::RmvTime( (QElemPtr) &theSleepTask );

			// On dit si on a �t� r�veill� ou non.
			theResult = theSleepTask.fExpired;
		}
	}
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * WakeUp( void )
// ------------------------------------------------------------------------- //
void
TDCLMacThreads::TThread::WakeUp( void )
{
	// Acquisition du mutex.
	mMutex.Acquire();

	// Le processus l�ger dort-il?
	if (mState == kSleeping)
	{
		// Debout.
		OSErr theErr = ::SetThreadState(
						mThreadID, kRunningThreadState, kNoThreadID );
		if (theErr != noErr)
		{
			// Nettoyage.
			throw DCLPlatformUnknownError( theErr );
		}		
	} else {
		// On incr�mente juste le compteur.
		mWakeCount++;
	}
	
	// Lib�ration du mutex.
	mMutex.Release();
}

// ------------------------------------------------------------------------- //
//  * Run( TThread* )
// ------------------------------------------------------------------------- //
pascal void*
TDCLMacThreads::TThread::Run( TThread* inThis )
{
	inThis->mState = kRunning;
	inThis->mMutex.Release();	// Synchronisation.

	// On tourne.
	inThis->GetThreadedObject()->DoRun();
	
	inThis->mState = kStopped;
	
	return nil;
}

// ------------------------------------------------------------------------- //
//  * GetState( void )
// ------------------------------------------------------------------------- //
TDCLMacThreads::EState
TDCLMacThreads::TThread::GetState( void )
{
	return mState;
}

// ========================= //
// A modem is a baudy house. //
// ========================= //