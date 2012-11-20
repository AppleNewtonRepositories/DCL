// ==============================
// Fichier:			TDCLLogApplication.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			31/3/2003
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
// The Original Code is TDCLLogApplication.h.
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
// $Id: TDCLLogApplication.h,v 1.3 2004/11/24 14:09:00 paul Exp $
// ===========

#ifndef _TDCLLOGAPPLICATION_H
#define _TDCLLOGAPPLICATION_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/TDCLApplication.h>

// ANSI C
#include <stdio.h>

///
/// Classe pour une application qui �crit tous les messages dans un fichier.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLLogApplication
	:
		public TDCLApplication
{
public:
	///
	/// Constructeur � partir d'une r�f�rence sur le fichier � utiliser.
	///
	/// \param inLogFile	fichier o� �crire tout ce qui se passe.
	///
	TDCLLogApplication( FILE* inLogFile );

	///
	/// M�thode appel�e lorsque le serveur commence � �couter sur une interface donn�e.
	/// Cette m�thode est appel� par le serveur.
	/// Elle permet d'afficher un dialogue.
	///
	/// \param inServer	serveur qui attend la connexion.
	/// \param inLayer	couche de communication qui attend la connexion.
	///
	virtual	void	WaitConnection( TDCLServer* inServer, TDCLCommLayer* inLayer );

	///
	/// M�thode appel�e par le serveur pour indiquer que la connexion a �t� �tablie.
	/// Le param�tre est l'interface de communication avec le Newton.
	///
	/// \param inLink	le lien courant
	/// \param inLayer	couche de communication connect�e.
	///
	virtual	void	Connected( TDCLLink* inLink, TDCLCommLayer* inLayer );

	///
	/// M�thode appel�e par le serveur une fois que le nom est connu.
	/// Cette m�thode permet de copier le nom et d'afficher le nom pour l'utilisateur
	/// afin de confirmer la bonne connexion avec le Newton.
	///
	/// \param inLink	le lien courant
	/// \param inName	nom de l'utilisateur (officiellement, nom du Newton). Ce pointeur
	///					est la propri�t� du lien.
	///	
	virtual	void	ConnectedToNewtonDevice( TDCLLink* inLink, const KUInt16* inName );

	///
	/// M�thode appel�e lorsque le lien est d�connect�
	/// (ceci peut prendre du temps).
	///
	/// \param inLink	le lien courant
	///
	virtual void	Disconnecting( TDCLLink* inLink );
	
	///
	/// M�thode appel�e lorsque le lien a �t� d�connect� (juste avant
	/// que le nom ne soit lib�r�).
	///
	/// \param inLink	le lien courant
	///
	virtual void	Disconnected( TDCLLink* inLink );

	///
	/// M�thode appel�e lorsque le serveur quitte.
	/// Cette m�thode est appel�e par le processus l�ger du serveur juste avant
	/// qu'il ne se termine (remarque: si une exception est arriv�e, cette
	/// m�thode ne sera pas appel�e).
	///
	/// \param inServer	serveur qui quitte
	///
	virtual	void	ServerIsDown( TDCLServer* inServer );

	///
	/// M�thode appel�e lorsque l'utilisateur a annul�.
	///
	/// \param inLink	le lien courant
	///
	virtual void	Cancel( TDCLLink* inLink );
	
	///
	/// M�thode appel�e lorsqu'un d�lai de temporisation
	/// est d�pass�.
	///
	/// \param inLink	le lien courant
	///
	virtual	void	Timeout( TDCLLink* inLink );

	///
	/// M�thode appel�e lorsqu'une commande de l'application commence � �tre ex�cut�e.
	///
	/// \param inLink		le lien qui ex�cute la commande.
	/// \param inCommand	la commande qui est en train d'�tre ex�cut�e
	///
	virtual void 	AppCommandBeingProcessed(
							TDCLLink* inLink,
							TDCLAppCommand* inCommand );

	///
	/// M�thode appel�e lorsqu'une commande de l'application ex�cut�e par le lien
	/// est termin�e.
	///
	/// \param inLink		le lien qui a ex�cut� la commande.
	/// \param inCommand	la commande qui a �t� ex�cut�e
	/// \param inException	l'exception si la commande a �chou� (nil si elle a r�ussi).
	///
	virtual void 	AppCommandProcessed(
							TDCLLink* inLink,
							TDCLAppCommand* inCommand,
							TDCLException* inException );

	///
	/// M�thode appel�e lorsqu'une commande du Newton commence � �tre ex�cut�e.
	///
	/// \param inLink		le lien qui ex�cute la commande.
	/// \param inCommand	la commande qui commence � �tre ex�cut�e
	/// \param inEngine		le moteur qui ex�cute la commande.
	///
	virtual void 	DockCommandBeingProcessed(
							TDCLLink* inLink,
							TDCLDockCommand* inCommand,
							TDCLLinkEngine* inEngine );

	///
	/// M�thode appel�e lorsqu'une commande du Newton ex�cut�e par le lien
	/// est termin�e.
	///
	/// \param inLink		le lien qui a ex�cut� la commande.
	/// \param inEngine		le moteur qui a ex�cut� la commande.
	/// \param inException	l'exception si la commande a �chou� (nil si elle a r�ussi).
	///
	virtual void 	DockCommandProcessed(
							TDCLLink* inLink,
							TDCLLinkEngine* inEngine,
							TDCLException* inException );

	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e dans
	/// le processus l�ger d'un/du serveur.
	///
	/// \param inServer		serveur qui s'est vautr�.
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void 	HandleServerException(
							TDCLServer* inServer,
							TDCLException* inException );

	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e dans
	/// le processus l�ger d'une/de la couche de communication.
	///
	/// \param inCommLayer	couche qui s'est vautr�e.
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void 	HandleCommLayerException(
							TDCLCommLayer* inCommLayer,
							TDCLException* inException );

	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e dans
	/// le processus l�ger d'un/du lien.
	///
	/// \param inLink		lien qui s'est vautr�.
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void 	HandleLinkException(
							TDCLLink* inLink,
							TDCLException* inException );

	///
	/// Accesseur sur le fichier de log.
	/// Permet d'envoyer d'autres informations sur le fichier.
	///
	inline FILE*	GetLogFile( void )
		{
			return mLogFile;
		}

protected:
	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e dans
	/// le processus l�ger. Cette m�thode est appel�e dans ce processus l�ger
	/// qui se termine lorsque la m�thode retourne.
	///
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void 	HandleException( TDCLException* inException );

protected:
	/// \name Protected variables
	FILE*			mLogFile;		///< Fichier journal.

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLLogApplication( const TDCLLogApplication& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLLogApplication& operator = ( const TDCLLogApplication& inCopy );

	///
	/// Affiche une exception sur le fichier journal.
	///
	/// \param inException	l'exception � afficher (peut �tre \c nil si
	///						ce n'est pas une TDCLException)
	///
	virtual void	LogException( TDCLException* inException );

};

#endif
		// _TDCLLOGAPPLICATION_H

// ========================================================================== //
// You can now buy more gates with less specifications than at any other time //
// in history.                                                                //
//                 -- Kenneth Parker                                          //
// ========================================================================== //
