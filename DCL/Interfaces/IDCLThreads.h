// ==============================
// Fichier:			IDCLThreads.h
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
// The Original Code is IDCLThreads.h.
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
// $Id: IDCLThreads.h,v 1.6 2006/02/12 01:23:56 pguyot Exp $
// ===========

#ifndef __IDCLTHREADS__
#define __IDCLTHREADS__

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>

class TDCLThread;

///
/// Interface pour g�rer les processus l�gers.
/// Cette classe doit �tre d�riv�e pour chaque plateforme ou
/// application.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.6 $
///
/// \test	UTestThreads
///
class IDCLThreads
{
public:
	///
	/// Etats possibles d'un processus l�ger.
	///
	enum EState {
		kStopped,		///< Arr�t�.
		kRunning,		///< En train de tourner (n'a pas forc�ment le CPU)
		kSuspended,		///< Suspendu (attend un appel � la m�thode Resume)
		kSleeping		///< Endormi (par la m�thode Sleep) (attend WakeUp)
	};
	
	///
	/// Destructor.
	///
	virtual	~IDCLThreads( void ) {};

	///
	/// Donne du temps aux autres processus.
	/// Cette m�thode est appel�e � partir de la m�thode
	/// Run de TDCLThread ou du processus l�ger principal.
	///
	virtual	void	Yield( void ) = 0;	

	///
	/// Abstraction pour les processus l�gers.
	///
	/// Cette interface est utilis�e par TDCLThread (qui doit �tre d�riv� pour
	/// les objets qui doivent �tre dans des processus l�gers).
	///
	/// Ces objets peuvent �tre en train de tourner (Running) ou pas, et s'ils
	/// sont en train de tourner, ils peuvent �tres suspendus ou pas.
	///
	class IThread
	{
	public:
		///
		/// Constantes sp�cifiques � IThread.	
		enum {
			kForever = 0	///< Dort jusqu'� ce que WakeUp soit appel�
		};

		///
		/// Constructeur � partir d'un objet TDCLThread.
		///
		/// \param inThreadedObject		objet � associ� au processus l�ger.
		///
		inline IThread( TDCLThread* inThreadedObject )
			:
				mThreadedObject( inThreadedObject )
			{
			}

		///
		/// Destructor.
		///
		virtual ~IThread( void ) {};

		///
		/// Accesseur sur l'objet TDCLThread.
		///
		/// \return l'objet TDCLThread associ�.
		///
		inline TDCLThread* GetThreadedObject( void )
			{
				return mThreadedObject;
			}

		///
		/// D�marre le processus.
		///
		/// Appelle la m�thode Run de TDCLThread dans le nouveau
		/// processus l�ger.
		/// Lance une exception si le processus l�ger n'est pas arr�t�.
		///
		/// \throws TDCLException si le processus l�ger n'est pas arr�t�.
		///
		virtual void	Start( void ) = 0;

		///
		/// Arr�te le processus (de mani�re violente).
		///
		/// Lance une exception si le processus l�ger est arr�t�.
		///
		/// \throws TDCLException si le processus l�ger est arr�t�.
		///
		virtual void	Stop( void ) = 0;

		///
		/// Suspend le processus l�ger.
		/// Cette m�thode peut �tre appel�e � partir d'un autre processus
		/// l�ger.
		/// Lance une exception si le processus l�ger est arr�t�, mais
		/// est silencieux si le processus est suspendu.
		///
		/// \throws TDCLException si le processus l�ger est arr�t�.
		///
		virtual	void	Suspend( void ) = 0;

		///
		/// Reprend le processus l�ger.
		/// Cette m�thode est appel�e � partir d'un autre processus l�ger.
		/// Lance une exception si le processus l�ger n'est pas arr�t�.
		/// mais est silencieux si le processus n'est pas suspendu.
		///
		/// \throws TDCLException si le processus l�ger est arr�t�.
		///
		virtual	void	Resume( void ) = 0;
	
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
		/// \return	\c true si l'on a dormi tout le temps demand�, \c false si
		///			on a �t� interrompu.
		///
		virtual	Boolean	Sleep( KUInt32 inMillisecs = kForever ) = 0;

		///
		/// R�veille un processus qui dort.
		/// Incr�mente le compteur des r�veils.
		/// Suivant les classes concr�tes, d�sactive les interruptions
		/// ou utilise les variables de condition.
		///
		virtual	void	WakeUp( void ) = 0;

		///
		/// D�termine l'�tat du processus.
		///
		/// \return l'�tat du processus (arr�t�, actif, suspendu)
		///
		virtual	EState	GetState( void ) = 0;

	private:
		///
		/// Constructeur par copie volontairement indisponible.
		///
		/// \param inCopy		objet � copier
		///
		IThread( const IThread& inCopy );

		///
		/// Op�rateur d'assignation volontairement indisponible.
		///
		/// \param inCopy		objet � copier
		///
		IThread& operator = ( const IThread& inCopy );

		/// \name Variables priv�es.
		TDCLThread*		mThreadedObject;	///< Processus l�ger associ�.
	};

	///
	/// Abstraction pour les s�maphores.
	///
	/// Ce s�maphore sert dans deux cas d'usage:
	///
	/// 1/ protection d'une ressource.
	/// Acquisition
	/// 				Acquisition
	/// Lib�ration
	///					Lib�ration
	///
	/// 2/ synchronisation
	/// Acquisition
	///	Acquisition
	///					Lib�ration
	///	Lib�ration
	/// 
	///
	class ISemaphore
	{
	public:
		///
		/// Destructor.
		///
		virtual	~ISemaphore( void ) {};

		///
		/// Verrouille le s�maphore.
		///
		virtual	void		Acquire( void ) = 0;
		
		///
		/// Lib�re un processus l�ger (au hasard) du s�maphore.
		///
		virtual	void		Release( void ) = 0;
	};

	///
	/// Cr�e un objet s�maphore. � surcharger pour chaque plateforme.
	///
	/// \return un nouvel objet s�maphore
	///
	virtual ISemaphore*	CreateSemaphore( void ) = 0;

private:
	///
	/// Seule la classe TDCLThread peut construire des threads.
	friend class TDCLThread;

	///
	/// Cr�e un objet IThread. � surcharger pour chaque plateforme.
	///
	/// \param inThreadedObject		objet associ� � passer comme param�tre
	///								pour IThread
	/// \return un nouvel objet IThread
	///
	virtual IThread*	CreateThread( TDCLThread* inThreadedObject ) = 0;
};

#endif
		// __IDCLTHREADS__

// =========================================================== //
// I haven't lost my mind -- it's backed up on tape somewhere. //
// =========================================================== //
