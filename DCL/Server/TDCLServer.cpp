// ==============================
// Fichier:			TDCLServer.cp
// Projet:			Desktop Connection Library
//
// Cr�� le:			14/1/2002
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
// The Original Code is TDCLServer.cp.
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
// $Id: TDCLServer.cp,v 1.4 2004/11/24 14:09:08 paul Exp $
// ===========

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Server/TDCLServer.h>

// K
#include <K/Misc/TSmartPtr.h>

// DCL
#include <DCL/Exceptions/Errors/TDCLBadParamError.h>
#include <DCL/Interfaces/TDCLEvent.h>
#include <DCL/Interfaces/TDCLApplication.h>

// ------------------------------------------------------------------------- //
//  *�TDCLServer( TDCLApplication* )
// ------------------------------------------------------------------------- //
TDCLServer::TDCLServer( TDCLApplication* inApplication )
	:
		TDCLThread( inApplication->GetThreadsIntf() ),
		mApplication( inApplication ),
		mStateMutex( nil ),
		mState( kStopped )
{
	mStateMutex = GetThreadsIntf()->CreateSemaphore();
}

// ------------------------------------------------------------------------- //
//  *�~TDCLServer( void )
// ------------------------------------------------------------------------- //
TDCLServer::~TDCLServer( void )
{	
	if (mStateMutex)
	{
		delete mStateMutex;
	}
}

// ------------------------------------------------------------------------- //
//  *�Start( void )
// ------------------------------------------------------------------------- //
void
TDCLServer::Start( void )
{
	// Acquisition
	mStateMutex->Acquire();
	
	if (mState == kStopped)
	{
		mState = kStarting;

		try {
			// On lance le processus l�ger.
			TDCLThread::Start();
		} catch ( ... ) {
			// The state is still kStopped.

			// Release the semaphore
			mStateMutex->Release();

			throw;	// Rethrow.
		}
	} // else: do nothing
	
	// Lib�ration
	mStateMutex->Release();
}

// ------------------------------------------------------------------------- //
//  *�Stop( void )
// ------------------------------------------------------------------------- //
void
TDCLServer::Stop( void )
{
	// Acquisition
	mStateMutex->Acquire();
	
	if ((mState == kRunning) || (mState == kStarting))
	{
		PostEvent(
			new TDCLEvent( TDCLEvent::kServerEvent, TDCLEvent::kStopServer ) );
	} // else: do nothing
	
	// Lib�ration
	mStateMutex->Release();
}

// ------------------------------------------------------------------------- //
//  *�Kill( void )
// ------------------------------------------------------------------------- //
void
TDCLServer::Kill( void )
{
	// Acquisition
	mStateMutex->Acquire();
	
	if (mState != kStopped)
	{
		try {
			DoKill();
			
			TDCLThread::Stop();
		} catch ( ... ) {
			// The state is now unknown

			mState = kUnknown;
			
			// Release the semaphore
			mStateMutex->Release();

			throw;	// Rethrow.
		}

		mState = kStopped;

	} // else: do nothing
	
	// Lib�ration
	mStateMutex->Release();
}

// ------------------------------------------------------------------------- //
//  *�GetState( void )
// ------------------------------------------------------------------------- //
TDCLServer::EState
TDCLServer::GetState( void )
{
	EState theResult;
	
	// Acquisition
	mStateMutex->Acquire();
	
	theResult = mState;
	
	// Lib�ration
	mStateMutex->Release();
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  *�RequestPresent( TDCLCommLayer* )
// ------------------------------------------------------------------------- //
void
TDCLServer::RequestPresent( TDCLCommLayer* inCommLayer )
{
	PostEvent( new TDCLEvent(
						TDCLEvent::kServerEvent,
						TDCLEvent::kIncomingRequest,
						inCommLayer ) );
}

// ------------------------------------------------------------------------- //
//  *�WaitingConnection( TDCLCommLayer* )
// ------------------------------------------------------------------------- //
void
TDCLServer::WaitingConnection( TDCLCommLayer* inCommLayer )
{
	PostEvent( new TDCLEvent(
						 TDCLEvent::kServerEvent,
						 TDCLEvent::kWaitingConnection,
						 inCommLayer ) );
}

// ------------------------------------------------------------------------- //
//  *�Disconnected( TDCLLink* )
// ------------------------------------------------------------------------- //
void
TDCLServer::Disconnected( TDCLLink* inLink )
{
	PostEvent( new TDCLEvent(
						TDCLEvent::kServerEvent,
						TDCLEvent::kDisconnected,
						inLink ) );
}

// ------------------------------------------------------------------------- //
//  *�Run( void )
// ------------------------------------------------------------------------- //
void
TDCLServer::Run( void )
{
	// Boucle principale du serveur.
	Boolean keepLooping = true;
	while( keepLooping )
	{
		// On donne un peu de temps.
		Yield();

		EState theState;
		EState theNextState;

		// Acquisition
		mStateMutex->Acquire();

		// R�cup�ration.
		theState = mState;
		theNextState = theState;
	
		// Lib�ration
		mStateMutex->Release();
		
		switch ( theState )
		{
			case kStarting:
				// On dit aux sous-classes de commencer � �couter.
				DoStartListening();
				
				// L'�tape suivante est d'attendre effectivement.
				theNextState = kRunning;
				break;

			case kRunning:
				// On attend un �v�nement.
				{
					TSmartPtr< TDCLEvent > theNextEvent;
					theNextEvent = WaitNextEvent(
										TDCLEvent::kServerEventMask,
										IDCLThreads::IThread::kForever );
					
					if (theNextEvent.Get() == nil)
					{
						// On a dormi tout le temps.
						DoIdle();
					} else {
						// Traitement de l'�v�nement.
						Boolean processed = false;
						theNextState = ProcessEvent(
										theNextEvent.Get(), &processed );
						
						if (!processed)
						{
							throw DCLBadParamError;
						}
					}
				}
				break;

			case kStopping:
				DoStop();
			
			case kStopped:	
			case kUnknown:	
				theNextState = kStopped;
				keepLooping = false;
				break;
		}
		
		if (theState != theNextState)
		{
			// Acquisition
			mStateMutex->Acquire();

			// V�rification que l'�tat n'a pas �t� chang� pendant qu'on avait
			// le dos tourn�.
			if (mState == theState)
			{
				// Changement
				mState = theNextState;
			}
	
			// Lib�ration
			mStateMutex->Release();
		}
	}

	// Indication � l'application que le serveur est ferm�.
	GetApplication()->ServerIsDown( this );
}

// ------------------------------------------------------------------------- //
//  *�HandleCommLayerException( TDCLCommLayer*, TDCLException* )
// ------------------------------------------------------------------------- //
void
TDCLServer::HandleCommLayerException(
							TDCLCommLayer* inCommLayer,
							TDCLException* inException )
{
	mApplication->HandleCommLayerException( inCommLayer, inException );
}

// ------------------------------------------------------------------------- //
//  *�ProcessEvent( TDCLEvent*, Boolean* )
// ------------------------------------------------------------------------- //
TDCLServer::EState
TDCLServer::ProcessEvent( TDCLEvent* inEvent, Boolean* outProcessed )
{
	EState theNextState = kRunning;
	
	// Quel est cet �v�nement que nous avons re�u?
	TDCLEvent::EEventID theEventID = inEvent->GetEventID();

	switch( theEventID )
	{
		case TDCLEvent::kWaitingConnection:
			// On attend le Newton.
			GetApplication()->WaitConnection(
					this,
					(TDCLCommLayer*) (inEvent->GetEventData()) );
			*outProcessed = true;
			break;

		case TDCLEvent::kIncomingRequest:
			// Une connexion vient d'arriver.
			theNextState = HandleIncomingConnection(
						(TDCLCommLayer*) (inEvent->GetEventData()) );
			*outProcessed = true;
			break;

		case TDCLEvent::kDisconnected:
		{
			// Un lien a �t� d�connect�.
			TDCLLink* theLink = (TDCLLink*) (inEvent->GetEventData());
			theNextState = HandleLinkDisconnection( theLink );
			
			// On indique � l'application que le lien est d�connect�.
			mApplication->Disconnected( theLink );
			*outProcessed = true;
		}
		break;

		case TDCLEvent::kStopServer:
			// Il faut se fermer.
			theNextState = kStopping;
			*outProcessed = true;
			break;
		
		default:
			*outProcessed = false;
	}
	
	return theNextState;
}

// ------------------------------------------------------------------------- //
//  *�HandleException( TDCLException* )
// ------------------------------------------------------------------------- //
void
TDCLServer::HandleException( TDCLException* inException )
{
	// Acquisition
	mStateMutex->Acquire();

	switch ( mState )
	{
		case kStopped:
		case kStarting:
		case kStopping:
			mState = kStopped;
			break;
	
		case kRunning:
		default:
			mState = kUnknown;
			break;
	}
	
	// Lib�ration
	mStateMutex->Release();

	mApplication->HandleServerException( this, inException );
}

// ================================================ //
// You will have a head crash on your private pack. //
// ================================================ //
