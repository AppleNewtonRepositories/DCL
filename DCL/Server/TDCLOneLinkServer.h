// ==============================
// Fichier:			TDCLOneLinkServer.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			3/4/2003
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
// The Original Code is TDCLOneLinkServer.h.
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
// $Id: TDCLOneLinkServer.h,v 1.5 2004/11/24 14:09:08 paul Exp $
// ===========

#ifndef _TDCLONELINKSERVER_H
#define _TDCLONELINKSERVER_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Server/TDCLServer.h>

///
/// Classe pour un serveur avec un seul lien et plusieurs couches de
/// communication. C'est un serveur de type NCU.
///
/// Il faut d'abord cr�er le lien (parce que le lien suppose que le
/// serveur pr�-existe).
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.5 $
///
/// \test	aucun test d�fini.
///
class TDCLOneLinkServer
	:
		public TDCLServer
{
public:
	///
	/// Cr�ateur � partir d'une application.
	///
	/// \param inApplication	application pr�venue de l'activit� du serveur.
	///
	TDCLOneLinkServer( TDCLApplication* inApplication );
	
	///
	/// Fixe le lien.
	///
	/// \param inLink		lien � utiliser lorsqu'une connexion est �tablie.
	///
	inline void			SetLink( TDCLLink* inLink )
		{
			mLink = inLink;
		}

	///
	/// Destructeur.
	///
	virtual	~TDCLOneLinkServer( void );

	///
	/// Ajoute une couche de communication.
	/// Cette m�thode peut �tre appel�e m�me si le serveur tourne.
	/// La couche de communication devra �tre supprim�e par l'application.
	///
	/// \param inLayer	la couche � ajouter au serveur.
	///
	void		AddCommLayer( TDCLCommLayer* inLayer );
	
	///
	/// Enl�ve une couche de communication.
	/// Cette m�thode peut �tre appel�e m�me si le serveur tourne.
	/// La couche de communication devra �tre supprim�e par l'application.
	/// Ne fait rien si la couche n'est pas dans la liste.
	///
	/// \param inLayer	la couche � supprimer du serveur.
	///
	void		RemoveCommLayer( TDCLCommLayer* inLayer );
	
	///
	/// Fonction utilis�e pour d�terminer si le serveur est "actif" ou non.
	///
	/// \return true si le serveur est d�j� connect�, false sinon.
	///
	TDCLLink*			GetConnectionLink( void );

protected:
	///
	/// Commence � �couter.
	/// Cette m�thode est appel�e lorsque le serveur est d�marr� (depuis
	/// le processus l�ger du serveur).
	///
	virtual	void		DoStartListening( void );

	///
	/// Arr�te le serveur.
	///
	virtual	void		DoStop( void );
	
	///
	/// Ferme toutes les connexions brutalement.
	///
	virtual	void		DoKill( void );

	///
	/// G�re l'arriv�e d'une nouvelle connexion.
	///
	/// \param inCommLayer	interface de communication qui a re�u la requ�te.
	/// \throws TDCLException si un probl�me est survenu.
	///
	virtual EState		HandleIncomingConnection(
								TDCLCommLayer* inCommLayer );

	///
	/// M�thode appel�e dans le processus l�ger du serveur pour indiquer
	/// qu'un lien a �t� d�connect� et qu'il faut fermer l'interface de
	/// communication.
	///
	/// \param inLink	le lien qui a �t� d�connect�.
	/// \return le nouvel �tat du serveur.
	/// \throws TDCLException si un probl�me est survenu.
	///
	virtual	EState		HandleLinkDisconnection( TDCLLink* inLink );

	///
	/// M�thode appel�e par le serveur lorsque rien ne se passe.
	/// Elle permet d'appeler Idle sur les interfaces de communication qui en
	/// ont besoin.
	///
	virtual	void		DoIdle( void );

	///
	/// Accesseur sur le lien.
	///
	/// \return le lien � utiliser lorsqu'une connexion est �tablie.
	///
	inline TDCLLink*		GetLink( void )
		{
			return mLink;
		}
private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLOneLinkServer( const TDCLOneLinkServer& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLOneLinkServer& operator = ( const TDCLOneLinkServer& inCopy );

	/// \name Variables
	
	TDCLLink*					mLink;			///< R�f�rence sur l'unique
												///< lien.
	TDCLPipe*					mPipe;			///< R�f�rence sur la
												///< connexion, \c nil si on
												///< n'est pas connect�.
	TDCLCommLayer**				mCommLayers;	///< Liste des couches de
												///< communication.
	KUInt32						mNbCommLayers;	///< Nombre d'�l�ments dans la
												///< liste pr�c�dente.
	IDCLThreads::ISemaphore*	mListMutex;		///< Mutex sur la liste
												///< pr�c�dente.
};

#endif
		// _TDCLONELINKSERVER_H

// =========================== //
// Memory fault -- brain fried //
// =========================== //
