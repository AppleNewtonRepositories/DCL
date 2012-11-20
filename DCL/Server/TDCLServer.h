// ==============================
// Fichier:			TDCLServer.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			14/01/2002
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
// The Original Code is TDCLServer.h.
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
// $Id: TDCLServer.h,v 1.4 2004/11/24 14:09:08 paul Exp $
// ===========

#ifndef __TDCLSERVER__
#define __TDCLSERVER__

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Communication_Layers/TDCLCommLayer.h>
#include <DCL/Exceptions/TDCLException.h>
#include <DCL/Interfaces/TDCLApplication.h>
#include <DCL/Interfaces/IDCLThreads.h>
#include <DCL/Interfaces/TDCLThread.h>

class TDCLLink;

///
/// Classe abstraite pour les serveurs.
///
/// Un serveur �coute sur une ou plusieurs interfaces (pipes) et les associe �
/// un lien (link) lorsque le Newton se connecte.
/// Il peut alors cr�er plus d'interfaces ou tuer les interfaces pr�c�dentes ou
/// leur dire de ne plus �couter. Tout ceci d�pend de la sous-classe.
///
/// L'acc�s aux interfaces et aux liens doit �tre fait en
/// verrouillant/d�verrouillant les listes. Verrouiller les listes emp�che le
/// serveur de cr�er des nouveaux liens ou des nouvelles interfaces. Donc vous
/// devez les d�verrouiller d�s que possible.
///
/// Par ailleurs, le serveur comprend un s�maphore mutex pour prot�ger les
/// acc�s aux m�thodes Start/Stop/Kill.
///
/// Le serveur est repr�sent� par un processus l�ger qui g�n�ralement reste en
/// attente. La boucle est:
/// - Tant qu'il n'y a pas de connexion ou qu'il ne faut pas quitter, attendre.
/// - Faire ce qu'il y a � faire.
///
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class TDCLServer
	:
		private TDCLThread
{
public:
	///
	/// Le constructeur est public, mais la classe est abstraite.
	///
	/// \param inApplication	interface avec le syst�me h�te. Utilis�
	///							pour le s�maphore.
	///
	TDCLServer( TDCLApplication* inApplication );

	///
	/// Destructeur.
	/// Tue le serveur s'il est en train de tourner.
	///
	virtual	~TDCLServer( void );


	///
	/// Etats du serveur.
	///
	enum EState {
		kStopped,	///< Etat initial.
		kStarting,	///< Etat juste apr�s que Start ait �t� appel�.
		kRunning,	///< Etat une fois que DoStart a termin�.
		kStopping,	///< En cours d'arr�t.
		kUnknown	///< Etat inconnu (en cas d'exception)
	};	

	///
	/// D�marre le serveur.
	/// Ne fait rien si le serveur n'est pas � l'arr�t.
	/// Change l'�tat en kStarting si tout va bien.
	///
	/// \throws	TDCLException si un probl�me est survenu. Dans ce cas
	///			le serveur est maintenu dans l'�tat arr�t�.
	///
	void				Start( void );

	///
	/// Commence l'arr�t du serveur en douceur.
	/// Normalement asynchrone, mais ceci peut �tre synchrone.
	/// Ne fait rien si le serveur ne tourne pas.
	/// Change l'�tat en kStopping ou kStopped suivant que l'op�ration
	/// �tait asynchrone ou synchrone.
	///
	/// \throws	TDCLException si un probl�me est survenu. Dans ce cas
	///			le serveur est dans l'�tat inconnu (ne devrait pas arriver).
	///
	void				Stop( void );
	
	///
	/// Termine brutalement toute connexion (op�ration synchrone).
	/// Ne fait rien si le serveur ne tourne pas.
	/// Tue aussi les interfaces de communication qui sont en train de
	/// se fermer. Change l'�tat en kStopped.
	///
	/// \throws	TDCLException si un probl�me est survenu. Dans ce cas
	///			le serveur est dans l'�tat inconnu (ne devrait pas arriver).
	///
	void				Kill( void );

	///
	/// R�cup�re l'�tat du serveur.
	/// Note: cette m�thode utilise le s�maphore comme Start/Stop/Kill.
	///
	/// \return l'�tat actuel du serveur
	///
	EState				GetState( void );

	///
	/// M�thode appel�e par les couches de communication pour indiquer qu'une
	/// requ�te est pr�sente. Cette m�thode envoie un �v�nement au processus
	/// l�ger du serveur.
	///
	/// \param inCommLayer	couche de communication qui a re�u une requ�te.
	///
	void				RequestPresent( TDCLCommLayer* inCommLayer );

	///
	/// M�thode appel�e par les couches de communication pour indiquer qu'elles
	/// attendent une connexion. C'est le moment pour l'utilisateur de demander
	/// au Newton de se connecter.
	///
	/// \param inCommLayer	couche de communication qui attend.
	///
	void				WaitingConnection( TDCLCommLayer* inCommLayer );

	///
	/// M�thode appel�e par les liens pour indiquer qu'ils sont d�connect�s
	/// (i.e. que la communication avec le Newton est termin�e).
	///
	/// \param inLink		lien qui est d�connect�.
	///
	void				Disconnected( TDCLLink* inLink );

	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e dans
	/// le processus l�ger d'une/de la couche de communication.
	/// Cette m�thode pr�vient l'application.
	///
	/// \param inCommLayer	couche qui s'est vautr�e.
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void 		HandleCommLayerException(
							TDCLCommLayer* inCommLayer,
							TDCLException* inException );

protected:
	///
	/// M�thode appel�e lorsqu'on a re�u un �v�nement.
	/// Cette m�thode peut �tre d�riv�e si un serveur a besoin de recevoir
	/// des �v�nements non pr�vus.
	/// Par d�faut
	///
	/// \param 	inEvent	l'�v�nement re�u.
	/// \param 	outProcessed en sortie, \c true si l'�v�nement a �t� g�r�,
	///			inchang� sinon. Si l'�v�nement n'est pas g�r�, une exception
	///			sera lev�e.
	/// \return le nouvel �tat du serveur.
	///
	virtual EState		ProcessEvent(
							TDCLEvent* inEvent,
							Boolean* outProcessed );

	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e.
	/// Lorsque cette m�thode retourne, le processus est termin�.
	///
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void 		HandleException( TDCLException* inException );

	/// \name Interface TDCLThread
	
	///
	/// Cette m�thode est appel�e dans le processus l�ger du serveur.
	/// C'est la boucle principale du serveur.
	/// Cette boucle est termin�e lorsqu'une exception survient ou lorsque
	/// le serveur est arr�t�.
	///
	virtual void		Run( void );

	/// \name Interface TDCLServer
	
	///
	/// Commence � �couter.
	/// Cette m�thode est appel�e lorsque le serveur est d�marr� (depuis
	/// le processus l�ger du serveur).
	///
	virtual	void		DoStartListening( void ) = 0;

	///
	/// Arr�te le serveur.
	///
	virtual	void		DoStop( void ) = 0;
	
	///
	/// Ferme toutes les connexions brutalement.
	///
	virtual	void		DoKill( void ) = 0;

	///
	/// G�re l'arriv�e d'une nouvelle connexion.
	///
	/// \param inCommLayer	interface de communication qui a re�u la requ�te.
	/// \return le nouvel �tat du serveur.
	/// \throws TDCLException si un probl�me est survenu.
	///
	virtual EState		HandleIncomingConnection(
								TDCLCommLayer* inCommLayer ) = 0;

	///
	/// M�thode appel�e dans le processus l�ger du serveur pour indiquer
	/// qu'un lien a �t� d�connect� et qu'il faut fermer l'interface de
	/// communication.
	///
	/// \param inLink	le lien qui a �t� d�connect�.
	/// \return le nouvel �tat du serveur.
	/// \throws TDCLException si un probl�me est survenu.
	///
	virtual	EState		HandleLinkDisconnection( TDCLLink* inLink ) = 0;

	///
	/// M�thode appel�e par le serveur lorsque rien ne se passe.
	/// Elle permet d'appeler Idle sur les interfaces de communication qui en
	/// ont besoin.
	///
	virtual	void		DoIdle( void ) = 0;

	inline	TDCLApplication*	GetApplication( void )
			{
				return mApplication;
			}
	
private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLServer( const TDCLServer& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLServer& operator = ( const TDCLServer& inCopy );

	/// \name Variables

	TDCLApplication*			mApplication;	///< R�f�rence sur
												///< l'application.
	IDCLThreads::ISemaphore*	mStateMutex;	///< Mutex sur l'�tat.
	EState						mState;			///< Etat.
};

#endif
		// __TDCLSERVER__

// ============================================================= //
// APL is a natural extension of assembler language programming; //
// ...and is best for educational purposes.                      //
//                 -- A. Perlis                                  //
// ============================================================= //
