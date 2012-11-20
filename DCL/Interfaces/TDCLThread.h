// ==============================
// Fichier:			TDCLThread.h
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
// The Original Code is TDCLThread.h.
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
// $Id: TDCLThread.h,v 1.4 2004/11/24 14:08:59 paul Exp $
// ===========

#ifndef _TDCLTHREAD_H
#define _TDCLTHREAD_H

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Interfaces/IDCLThreads.h>
#include <DCL/Interfaces/TDCLEvent.h>

///
/// Classe pour un objet dans un processus l�ger.
/// Pour les d�tails, voir IDCLThreads.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class TDCLThread
{
public:
	///
	/// Constructeur � partir de l'interface IDCLThreads.
	///
	TDCLThread( IDCLThreads* inThreadFactory );

	///
	/// Destructeur.
	///
	virtual ~TDCLThread( void );

	///
	/// D�marre le processus l�ger.
	///
	inline void Start( void )
		{
			mThread->Start();
		}

	///
	/// Arr�te le processus l�ger.
	///
	inline void Stop( void )
		{
			mThread->Stop();
		}

	///
	/// Suspend le processus l�ger.
	///
	inline void Suspend( void )
		{
			mThread->Suspend();
		}

	///
	/// Reprend le processus l�ger.
	///
	inline void Resume( void )
		{
			mThread->Resume();
		}

	///
	/// Poste un �v�nement pour ce processus.
	/// Les �v�nements sont g�r�s dans l'ordre d'arriv�e (� am�liorer?)
	/// L'�v�nement sera supprim� par une m�thode du processus l�ger
	/// qui appellera WaitNextEvent ou par le destructeur du processus l�ger.
	///
	/// \param inEvent	�v�nement � poster
	/// \throws TDCLException si un probl�me est survenu
	///
	void PostEvent( TDCLEvent* inEvent );

	///
	/// R�veille le processus l�ger.
	///
	/// Remarque: l'utilisation de WakeUp/Sleep est exclusive de l'utilisation de
	/// WaitNextEvent/PostEvent.
	///
	inline void WakeUp( void )
		{
			mThread->WakeUp();
		}

	///
	/// M�thode ex�cut�e dans le processus.
	///
	virtual void Run( void ) = 0;

	///
	/// M�thode appel�e par le processus l�ger. C'est cette m�thode
	/// qui se charge d'appeler la m�thode Run ci-dessus.
	///
	void DoRun( void );

	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e.
	/// Lorsque cette m�thode retourne, le processus est termin�.
	///
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void HandleException( TDCLException* inException ) = 0;

protected:
	///
	/// R�cup�re le prochain �v�nement en attendant au plus inMilliseconds
	/// (en millisecondes). Si aucun �v�nement n'est arriv�, retourne nil.
	/// Si le masque n'est pas kAnyEventMask, alors on attend inMilliseconds
	/// au plus entre deux �v�nements. L'arriv�e d'�v�nements qui ne cadrent
	/// pas avec le masque peut rallonger l'attente.
	///
	/// Cette m�thode appelle Sleep.
	///
	/// Remarque importante: l'appelant doit supprimer l'�v�nement avec
	/// delete.
	///
	/// \param inEventMask		masque pour les �v�nements � attendre.
	/// \param inMilliseconds	temps � attendre au maximum.
	/// \return un pointeur vers l'�v�nement ou \c nil.
	/// \throws TDCLException si un probl�me est survenu
	///
	TDCLEvent* WaitNextEvent(
			KUInt32 inEventMask = TDCLEvent::kAnyEventMask,
			KUInt32 inMilliseconds = IDCLThreads::IThread::kForever );

	///
	/// Dort. Cette m�thode doit �tre appel�e par le processus.
	///
	/// Remarque: l'utilisation de WakeUp/Sleep est exclusive de l'utilisation de
	/// WaitNextEvent/PostEvent.
	///
	/// \param inMilliseconds	temps � dormir au maximum.
	/// \return \c true si on a dormi tout le temps, \c false sinon.
	///
	inline Boolean Sleep(
			KUInt32 inMilliseconds = IDCLThreads::IThread::kForever )
		{
			return mThread->Sleep( inMilliseconds );
		}

	///
	/// D�termine l'�tat du processus l�ger.
	///
	/// \return l'�tat du processus l�ger.
	///
	inline IDCLThreads::EState GetThreadState( void )
		{
			return mThread->GetState();
		}

	///
	/// Donne du temps aux autres processus.
	/// Cette m�thode est appel�e � partir de la m�thode
	/// Run de TDCLThread ou du processus l�ger principal.
	///
	inline	void	Yield( void )
		{
			mThreadsIntf->Yield();
		}

	///
	/// Accesseur sur la fabrique de processus l�gers
	///
	/// \return une r�f�rence sur l'interface sur les processus l�gers.
	///
	inline	IDCLThreads*	GetThreadsIntf( void )
			{
				return mThreadsIntf;
			}

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLThread( const TDCLThread& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLThread& operator = ( const TDCLThread& inCopy );

	/// \name Variables priv�es.
	IDCLThreads::IThread*		mThread;			///< Processus l�ger syst�me
													///< associ�.
	IDCLThreads::ISemaphore*	mQueueSemaphore;	///< Mutex sur la liste des �v�nements.
	TDCLEvent*					mNextEvent;			///< Pointeur sur le prochain
													///< �v�nement ou \c nil.
	TDCLEvent*					mLastEvent;			///< Pointeur sur le prochain
													///< �v�nement ou \c nil.
	IDCLThreads*				mThreadsIntf;		///< Interface pour les processus l�gers.
};

#endif
		// _TDCLTHREAD_H

// ============================================================================== //
// I have sacrificed time, health, and fortune, in the desire to complete these   //
// Calculating Engines.  I have also declined several offers of great personal    //
// advantage to myself.  But, notwithstanding the sacrifice of these advantages   //
// for the purpose of maturing an engine of almost intellectual power, and        //
// after expending from my own private fortune a larger sum than the government   //
// of England has spent on that machine, the execution of which it only           //
// commenced, I have received neither an acknowledgement of my labors, not even   //
// the offer of those honors or rewards which are allowed to fall within the      //
// reach of men who devote themselves to purely scientific investigations...      //
//         If the work upon which I have bestowed so much time and thought were   //
// a mere triumph over mechanical difficulties, or simply curious, or if the      //
// execution of such engines were of doubtful practicability or utility, some     //
// justification might be found for the course which has been taken; but I        //
// venture to assert that no mathematician who has a reputation to lose will      //
// ever publicly express an opinion that such a machine would be useless if       //
// made, and that no man distinguished as a civil engineer will venture to        //
// declare the construction of such machinery impracticable...                    //
//         And at a period when the progress of physical science is obstructed    //
// by that exhausting intellectual and manual labor, indispensable for its        //
// advancement, which it is the object of the Analytical Engine to relieve, I     //
// think the application of machinery in aid of the most complicated and abtruse  //
// calculations can no longer be deemed unworthy of the attention of the country. //
// In fact, there is no reason why mental as well as bodily labor should not      //
// be economized by the aid of machinery.                                         //
//                 -- Charles Babbage, "The Life of a Philosopher"                //
// ============================================================================== //
