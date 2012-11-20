// ==============================
// Fichier:			TDCLObjCApplication.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			30/3/2003
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
// The Original Code is TDCLObjCApplication.h.
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
// $Id: TDCLObjCApplication.h,v 1.3 2004/11/24 14:09:01 paul Exp $
// ===========

#ifndef _TDCLOBJCAPPLICATION_H
#define _TDCLOBJCAPPLICATION_H

#include <DCL/Interfaces/TDCLApplication.h>

#if !TARGET_OS_OPENSTEP
	#error TDCLObjCApplication ne fonctionne que sur OSX/OpenSTEP.
#endif

#include <objc/objc.h>
#include <CoreFoundation/CFString.h>

// Pr�-d�clarations
class TDCLLink;
class TDCLAppCommand;
class TDCLException;
class TDCLDockCommand;
class TDCLLinkEngine;

//
// L'objet Cocoa g�rant les messages doit suivre le protocole IDCLObjCApplication
//
// Prototypes des eveloppes. Ces enveloppes sont d�finies dans
// TDCLObjCApplication.mm
//
void TDCLObjCAppl_WaitConnection( id inCocoaObject, TDCLServer* inServer, TDCLCommLayer* inLayer );
void TDCLObjCAppl_Connected( id inCocoaObject, TDCLLink* inLink, TDCLCommLayer* inLayer );
void TDCLObjCAppl_ConnectedToNewtonDevice( id inCocoaObject, TDCLLink* inLink, CFStringRef inName );
void TDCLObjCAppl_Disconnecting( id inCocoaObject, TDCLLink* inLink );
void TDCLObjCAppl_Disconnected( id inCocoaObject, TDCLLink* inLink );
void TDCLObjCAppl_ServerIsDown( id inCocoaObject, TDCLServer* inServer );
void TDCLObjCAppl_Cancel( id inCocoaObject, TDCLLink* inLink );
void TDCLObjCAppl_Timeout( id inCocoaObject, TDCLLink* inLink );
void TDCLObjCAppl_AppCommandBeingProcessed( id inCocoaObject, TDCLLink* inLink, TDCLAppCommand* inCommand );
void TDCLObjCAppl_AppCommandProcessed( id inCocoaObject, TDCLLink* inLink, TDCLAppCommand* inCommand, TDCLException* inException );
void TDCLObjCAppl_DockCommandBeingProcessed( id inCocoaObject, TDCLLink* inLink, TDCLDockCommand* inCommand, TDCLLinkEngine* inEngine );
void TDCLObjCAppl_DockCommandProcessed( id inCocoaObject, TDCLLink* inLink, TDCLLinkEngine* inEngine, TDCLException* inException );
void TDCLObjCAppl_HandleServerException( id inCocoaObject, TDCLServer* inServer, TDCLException* inException );
void TDCLObjCAppl_HandleCommLayerException( id inCocoaObject, TDCLCommLayer* inCommLayer, TDCLException* inException );
void TDCLObjCAppl_HandleLinkException( id inCocoaObject, TDCLLink* inLink, TDCLException* inException );
void TDCLObjCAppl_HandleException( id inCocoaObject, TDCLException* inException );
IDCLFiles* TDCLObjCAppl_CreateFilesIntf( id inCocoaObject );
IDCLThreads* TDCLObjCAppl_CreateThreadsIntf( id inCocoaObject );

///
/// Classe pour une enveloppe autour d'un objet ObjC g�rant l'interface TDCLApplication.
/// Cette classe appelle les m�thodes de l'objet Cocoa pass� en param�tre du
/// constructeur (comme id).
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLObjCApplication
	:
		public TDCLApplication
{
public:
	///
	/// Constructeur � partir d'un id d'objet Cocoa.
	///
	/// \param inCocoaObject	object cocoa appel�
	///
	TDCLObjCApplication( id inCocoaObject );

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
	/// M�thode appel�e lorsqu'une commande commence � �tre ex�cut�e.
	///
	/// \param inLink		le lien qui a ex�cute la commande.
	/// \param inCommand	la commande qui est en train d'�tre ex�cut�e
	///
	virtual void 	AppCommandBeingProcessed(
							TDCLLink* inLink,
							TDCLAppCommand* inCommand );

	///
	/// M�thode appel�e lorsqu'une commande ex�cut�e par l'application est termin�e.
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
	/// \param inLink		le lien qui a ex�cute la commande.
	/// \param inCommand	la commande qui est en train d'�tre ex�cut�e
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

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLObjCApplication( const TDCLObjCApplication& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLObjCApplication& operator = ( const TDCLObjCApplication& inCopy );

	///
	/// Retourne l'abstraction pour les fichiers.
	/// Cette m�thode est appel�e la premi�re fois que
	/// GetFilesIntf est appel�e.
	///
	/// \return une abstraction pour utiliser les fichiers.
	///
	virtual IDCLFiles*		CreateFilesIntf( void );
	
	///
	/// Retourne l'abstraction pour les processus l�gers.
	/// Cette m�thode est appel�e la premi�re fois que
	/// GetThreadsIntf est appel�e.
	///
	/// \return une abstraction pour les processus l�gers.
	///
	virtual IDCLThreads*	CreateThreadsIntf( void );

	/// \name Variables priv�es
	id								mCocoaObject;
};

#endif
		// _TDCLOBJCAPPLICATION_H

// ============================================================================== //
// Dear Emily:                                                                    //
//         I recently read an article that said, "reply by mail, I'll summarize." //
// What should I do?                                                              //
//                 -- Doubtful                                                    //
//                                                                                //
// Dear Doubtful:                                                                 //
//         Post your response to the whole net.  That request applies only to     //
// dumb people who don't have something interesting to say.  Your postings are    //
// much more worthwhile than other people's, so it would be a waste to reply by   //
// mail.                                                                          //
//                 -- Emily Postnews Answers Your Questions on Netiquette         //
// ============================================================================== //