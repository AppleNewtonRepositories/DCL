// ==============================
// Fichier:			TDCLMacThreads.h
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
// The Original Code is TDCLMacThreads.h.
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
// $Id: TDCLMacThreads.h,v 1.7 2004/11/24 14:09:01 paul Exp $
// ===========

#ifndef _TDCLMACTHREADS_H
#define _TDCLMACTHREADS_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/IDCLThreads.h>

// MacOS
#if TARGET_OS_MACOS
#include <OSUtils.h>
#include <Timer.h>
#include <Threads.h>
#else
#include <CoreServices/CoreServices.h>
#endif

///
/// Mise en place de l'interface IDCLThreads pour MacOS.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.7 $
///
/// \test	aucun test d�fini.
///
class TDCLMacThreads
	:
		public IDCLThreads
{
public:
	///
	/// Constructeur par d�faut.
	///
	TDCLMacThreads( void );	

	///
	/// Destructeur.
	///
	virtual ~TDCLMacThreads( void );	

	///
	/// Donne du temps aux autres processus.
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
	///
	/// S�maphore pour MacOS.
	///
	class TSemaphore
		:
			public ISemaphore
	{
	public:
		///
		/// Constructeur unique.
		/// � partir de inThreads pour pouvoir faire des Yield.
		///
		TSemaphore( TDCLMacThreads* inThreadsIntf );
		
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
		/// Lib�re le s�maphore.
		///
		virtual	void		Release ( void );
	
	private:
		/// \name variables priv�es.
		QHdr				mQueue;			///< Queue pour le s�maphore.
		TDCLMacThreads*		mThreads;		///< Objet IDCLThreads pour faire Yield.
		Boolean				mSemaphore;		///< Valeur du s�maphore.
	};

	///
	/// Processus l�ger pour MacOS (coop�ratif)
	///
	class TThread
		:
			public IThread
	{
	public:
		///
		/// Constructeur � partir d'un client.
		///
		/// \param inThreadsIntf	interface des processus l�gers.
		/// \param inThreadedObject	objet associ� au processus l�ger.
		///
		TThread( TDCLMacThreads* inThreadsIntf, TDCLThread* inThreadedObject );

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
		/// Suivant les classes concr�tes, d�sactive les interruptions
		/// ou utilise les variables de condition.
		///
		/// \param inMillisecs		nombre de millisecondes � dormir
		/// \return	\c true si l'on a dormi tout le temps demand�, \c false si on a �t�
		///			interrompu.
		///
		virtual	Boolean	Sleep( KUInt32 inMillisecs = kForever );

		///
		/// R�veille un processus qui dort.
		/// Incr�mente le compteur des r�veils.
		/// Suivant les classes concr�tes, d�sactive les interruptions
		/// ou utilise les variables de condition.
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
		/// La fonction vraiment appel�e par le syst�me.
		/// Elle appelle la m�thode Run du client.
		///
		/// \param inThis	pointeur sur l'objet TThread.
		/// \return \c nil
		///
		static pascal void* Run( TThread* inThis );

		/// \name variables priv�es.
		ThreadID		mThreadID;		///< L'ID du processus l�ger
		EState			mState;			///< L'�tat du processus.
		TSemaphore		mMutex;			///< S�maphore utilis� pour synchroniser
										///< l'�tat.
		ThreadEntryTPP	mRunTPP;		///< TPP pour Run.
		TDCLMacThreads*	mThreads;		///< Objet IDCLThreads pour la UPP qui nous r�veille.
		KUInt32			mWakeCount;		///< Compteur de r�veils.
	};

	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLMacThreads( const TDCLMacThreads& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLMacThreads& operator = ( const TDCLMacThreads& inCopy );

	///
	/// Fonction appel�e par la t�che du TimeManager qui va r�veiller
	/// le processus l�ger.
	///
	/// \param inTMTaskPtr	pointeur sur la structure TMTask.
	///
	static void TimerProc( TMTaskPtr inTMTaskPtr );
	
	/// \name variables priv�es.
	TimerUPP	mTimerProcUPP;	///< ProcPtr sur la fonction pr�c�dente.
	
	/// TThread a besoin d'acc�der la variable pr�c�dente.
	friend class TThread;
};

#endif
		// _TDCLMACTHREADS_H

// =========================================================================== //
// Our documentation manager was showing her 2 year old son around the office. //
// He was introduced to me, at which time he pointed out that we were both     //
// holding bags of popcorn.  We were both holding bottles of juice.  But only  //
// *__he* had a lollipop.                                                    //
//         He asked his mother, "Why doesn't HE have a lollipop?"              //
//         Her reply: "He can have a lollipop any time he wants to.  That's    //
// what it means to be a programmer."                                          //
// =========================================================================== //
