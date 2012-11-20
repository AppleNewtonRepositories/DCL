// ==============================
// Fichier:			TDCLPThreads.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			26/1/2003
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
// The Original Code is TDCLPThreads.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2003-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLPThreads.h,v 1.7 2004/11/24 14:09:02 paul Exp $
// ===========

#ifndef _TDCLPTHREADS_H
#define _TDCLPTHREADS_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/IDCLThreads.h>

// POSIX
#include <pthread.h>

///
/// Mise en place de l'interface IDCLThreads avec les pthreads.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.7 $
///
/// \test	aucun test d�fini.
///
class TDCLPThreads
	:
		public IDCLThreads
{
public:
	///
	/// Donne du temps aux autres processus.
	/// Ne fait rien puisque les pthreads sont pr�emptifs.
	///
	virtual	void	Yield( void );

	///
	/// Cr�e un objet IThread. � surcharger pour chaque plateforme.
	///
	/// \param inThreadedObject		objet associ� � passer comme param�tre
	///								pour IThread
	/// \return un nouvel objet IThread
	///
	virtual IThread*	CreateThread( TDCLThread* inThreadedObject );

	///
	/// Cr�e un objet s�maphore. � surcharger pour chaque plateforme.
	///
	/// \return un nouvel objet s�maphore
	///
	virtual ISemaphore*	CreateSemaphore( void );

private:
	class TThread;
	
	///
	/// Classe pour un s�maphore.
	/// � l'inverse d'un mutex POSIX, le s�maphore dans la DCL peut:
	/// - bloqu� un processus l�ger avec deux acquisitions
	/// - �tre d�bloqu� par un autre processus l�ger
	///
	class TSemaphore
		:
			public ISemaphore
	{
	public:
		/// Le thread est un ami.
		/// (permet de r�cup�rer un pointeur sur l'objet pthread_mutex)
		friend class TThread;

		///
		/// Constructeur unique.
		///
		TSemaphore( void );
		
		///
		/// Destructeur.
		/// Le s�maphore ne doit pas �tre utilis�.
		///
		virtual				~TSemaphore( void );

		///
		/// Attend jusqu'� ce que le s�maphore soit lib�r� si n�cessaire
		/// puis acquiert le s�maphore.
		///
		virtual	void		Acquire ( void );
		
		///
		/// Lib�re un processus l�ger du s�maphore.
		///
		virtual	void		Release ( void );
	
	private:
		/// \name variables priv�es.		
		pthread_mutex_t		mMutex;		///< Mutex pour prot�ger le nombre
										///< de processus dans le s�maphore.
		KUInt32				mNbThreads;	///< Nombre de processus dans le
										///< s�maphore.
		pthread_cond_t		mWaitCond;	///< Variable de condition pour
										///< l'attente.
	};

	///
	/// Classe pour un processus l�ger.
	///
	class TThread
		:
			public IThread
	{
	public:
		///
		/// Constructeur � partir d'un client.
		///
		/// \param inThreadedObject	objet associ� au processus l�ger.
		///
		TThread( TDCLThread* inThreadedObject );
		
		///
		/// Destructeur.
		///
		/// \throws TDCLException si le processus l�ger n'est pas arr�t�.
		///
		virtual ~TThread( void );

		///
		/// D�marre le processus.
		///
		/// Appelle la m�thode Run de TDCLThread dans le nouveau
		/// processus l�ger.
		/// Lance une exception si le processus l�ger n'est pas arr�t�.
		///
		/// \throws TDCLException si le processus l�ger n'est pas arr�t�.
		///
		virtual void	Start( void );
		
		///
		/// Arr�te le processus (de mani�re violente).
		///
		/// Lance une exception si le processus l�ger est arr�t�.
		///
		/// \throws TDCLException si le processus l�ger est arr�t�.
		///
		virtual void	Stop( void );

		///
		/// Suspend le processus l�ger.
		/// Cette m�thode peut �tre appel�e � partir d'un autre processus
		/// l�ger.
		/// Lance une exception si le processus l�ger est arr�t�, mais
		/// est silencieux si le processus est suspendu.
		///
		/// \throws TDCLException si le processus l�ger est arr�t�.
		///
		virtual	void	Suspend( void );

		///
		/// Reprend le processus l�ger.
		/// Cette m�thode est appel�e � partir d'un autre processus l�ger.
		/// Lance une exception si le processus l�ger n'est pas arr�t�,
		/// mais est silencieux si le processus n'est pas suspendu.
		///
		/// \throws TDCLException si le processus l�ger est arr�t�.
		///
		virtual	void	Resume( void );
	
		///
		/// Dort pendant n millisecondes ou jusqu'� ce que la m�thode
		/// WakeUp soit appel�e.
		/// Note: le processus peut aussi dormir plus longtemps.
		/// Cette m�thode doit �tre appel�e par le processus courant.
		/// D�cr�mente le compteur des r�veils ou dort s'il est � z�ro.
		/// Utilise les variables de condition.
		///
		/// \param inMillisecs		nombre de millisecondes � dormir
		/// \return	\c true si l'on a dormi tout le temps demand�, \c false si on a �t�
		///			interrompu.
		///
		virtual	Boolean	Sleep( KUInt32 inMillisecs );

		///
		/// R�veille un processus qui dort.
		/// Incr�mente le compteur des r�veils.
		/// Utilise les variables de condition.
		///
		virtual	void	WakeUp( void );

		///
		/// D�termine l'�tat du processus.
		///
		/// \return l'�tat du processus (arr�t�, actif, suspendu)
		///
		virtual	EState	GetState( void );

	private:
		///
		/// Constructeur par d�faut volontairement indisponible.
		///
		TThread( void );
		
		///
		/// Constructeur par copie volontairement indisponible.
		///
		/// \param inCopy		objet � copier
		///
		TThread( const TThread& inCopy );

		///
		/// Op�rateur d'assignation volontairement indisponible.
		///
		/// \param inCopy		objet � copier
		///
		TThread& operator = ( const TThread& inCopy );

		///
		/// La fonction vraiment appel�e par le syst�me.
		/// Elle appelle la m�thode Run du client.
		///
		/// \param inThis	pointeur sur l'objet TThread.
		/// \return \c nil
		///
		static void* Run( TThread* inThis );

		///
		/// Fonction appel�e lorsque le signal SIGUSR1 est envoy�.
		/// Ne fait rien.
		///
		/// \param inSignal	signal envoy� (toujours SIGUSR1).
		///
		static void SignalUSR1( int inSignal );

		///
		/// Fonction appel�e lorsque le signal SIGUSR2 est envoy�.
		/// Appelle sigsuspend (on attend SIGUSR1 (seulement)).
		///
		/// \param inSignal	signal envoy� (toujours SIGUSR2).
		///
		static void SignalUSR2( int inSignal );

		///
		/// Acquisition du mutex mMutex.
		///
		void		AcquireMutex( void );

		///
		/// Lib�ration du mutex mMutex.
		///
		void		ReleaseMutex( void );
		
		/// \name variables priv�es.
		
		pthread_t		mThread;		///< Ben le processus l�ger.
		EState			mState;			///< L'�tat du processus.
		TSemaphore		mSyncSemaphore;	///< S�maphore utilis� pour
										///< synchroniser.
		pthread_mutex_t	mMutex;			///< Mutex pour prot�ger l'�tat.
		pthread_cond_t	mSleepCond;		///< Variable de condition pour
										///< Sleep/WakeUp.
		KUInt32			mWakeCount;		///< Compteur de r�veils.
	};
};

#endif
		// _TDCLPTHREADS_H

// =================================================================== //
// Man is the best computer we can put aboard a spacecraft ... and the //
// only one that can be mass produced with unskilled labor.            //
//                 -- Wernher von Braun                                //
// =================================================================== //
