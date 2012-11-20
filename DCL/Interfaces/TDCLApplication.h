// ==============================
// Fichier:			TDCLApplication.h
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
// The Original Code is TDCLApplication.h.
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
// $Id: TDCLApplication.h,v 1.4 2004/11/24 14:08:59 paul Exp $
// ===========

#ifndef __TDCLAPPLICATION__
#define __TDCLAPPLICATION__

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Headers/DCLErrorMessages.h>

// Pr�-d�clarations
class IDCLFiles;
class IDCLThreads;
class TDCLAppCommand;
class TDCLCommLayer;
class TDCLDockCommand;
class TDCLException;
class TDCLLink;
class TDCLLinkEngine;
class TDCLServer;

///
/// Classe pour g�rer � la fois les abstractions sp�cifiques � une
/// plateforme et l'int�raction des �l�ments de la DCL avec l'application
/// h�te.
///
/// Cette classe doit �tre d�riv�e pour chaque application. Elle
/// fournit des objets qui permettent d'effectuer les t�ches de
/// bases. Ces objets sont d�truits par le constructeur de TDCLApplication.
///
/// <b>Attention</b>: les m�thodes appel�es pour pr�venir d'�v�nements
/// de la DCL sont appel�es dans des processus l�gers diff�rents. Il faut
/// sans doute un m�canisme de notification pour r�cup�rer ces �v�nements
/// dans le processus l�ger principal de l'application. Cf l'exemple
/// TDCLObjCApplication.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class TDCLApplication
{
public:
	/// \name constructeur et destructeur

	///
	/// Constructeur par d�faut.
	///
	TDCLApplication( void );

	///
	/// Destructeur.
	///
	virtual ~TDCLApplication( void );

	/// \name abstractions
	
	///
	/// Retourne l'abstraction pour les fichiers.
	///
	/// \return une abstraction pour utiliser les fichiers.
	///
	IDCLFiles*		GetFilesIntf( void );
	
	///
	/// Retourne l'abstraction pour les processus l�gers.
	///
	/// \return une abstraction pour les processus l�gers.
	///
	IDCLThreads*	GetThreadsIntf( void );

	/// \name Interface TDCLApplication

	///
	/// M�thode appel�e lorsque le serveur commence � �couter sur une interface donn�e.
	/// Cette m�thode est appel� par le serveur.
	/// Elle permet, par exemple, d'afficher un dialogue.
	///
	/// \param inServer	serveur qui commence � �couter
	/// \param inLayer	couche de communication qui attend la connexion.
	///
	virtual	void	WaitConnection( TDCLServer* inServer, TDCLCommLayer* inLayer ) = 0;

	///
	/// M�thode appel�e par le serveur pour indiquer que la connexion a �t� �tablie.
	/// Le param�tre est l'interface de communication avec le Newton.
	///
	/// \param inLink	le lien courant
	/// \param inLayer	couche de communication connect�e.
	///
	virtual	void	Connected( TDCLLink* inLink, TDCLCommLayer* inLayer ) = 0;

	///
	/// M�thode appel�e par le serveur une fois que le nom est connu.
	/// Cette m�thode permet de copier le nom et d'afficher le nom pour l'utilisateur
	/// afin de confirmer la bonne connexion avec le Newton.
	///
	/// \param inLink	le lien courant
	/// \param inName	nom de l'utilisateur (officiellement, nom du Newton). Ce pointeur
	///					est la propri�t� du lien.
	///	
	virtual	void	ConnectedToNewtonDevice( TDCLLink* inLink, const KUInt16* inName ) = 0;

	///
	/// M�thode appel�e lorsque le lien est d�connect�
	/// (ceci peut prendre du temps).
	///
	/// \param inLink	le lien courant
	///
	virtual void	Disconnecting( TDCLLink* inLink ) = 0;
	
	///
	/// M�thode appel�e lorsque le lien a �t� d�connect� (juste avant
	/// que le nom ne soit lib�r�).
	///
	/// \param inLink	le lien courant
	///
	virtual void	Disconnected( TDCLLink* inLink ) = 0;

	///
	/// M�thode appel�e lorsque le serveur quitte.
	/// Cette m�thode est appel�e par le processus l�ger du serveur juste avant
	/// qu'il ne se termine (remarque: si une exception est arriv�e, cette
	/// m�thode ne sera pas appel�e).
	///
	/// \param inServer	serveur qui quitte
	///
	virtual	void	ServerIsDown( TDCLServer* inServer ) = 0;

	///
	/// M�thode appel�e lorsque l'utilisateur a annul�.
	///
	/// \param inLink	le lien courant
	///
	virtual void	Cancel( TDCLLink* inLink ) = 0;
	
	///
	/// M�thode appel�e lorsqu'un d�lai de temporisation
	/// est d�pass�.
	///
	/// \param inLink	le lien courant
	///
	virtual	void	Timeout( TDCLLink* inLink ) = 0;

	///
	/// M�thode appel�e lorsqu'une commande de l'application commence � �tre ex�cut�e.
	///
	/// \param inLink		le lien qui ex�cute la commande.
	/// \param inCommand	la commande qui est en train d'�tre ex�cut�e
	///
	virtual void 	AppCommandBeingProcessed(
							TDCLLink* inLink,
							TDCLAppCommand* inCommand ) = 0;

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
							TDCLException* inException ) = 0;

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
							TDCLLinkEngine* inEngine ) = 0;

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
							TDCLException* inException ) = 0;

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
							TDCLException* inException ) = 0;

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
							TDCLException* inException ) = 0;

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
							TDCLException* inException ) = 0;

protected:
	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e dans
	/// le processus l�ger. Cette m�thode est appel�e dans ce processus l�ger
	/// qui se termine lorsque la m�thode retourne.
	///
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void 	HandleException( TDCLException* inException ) = 0;

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLApplication( const TDCLApplication& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLApplication& operator = ( const TDCLApplication& inCopy );

	///
	/// Retourne l'abstraction pour les fichiers.
	/// Cette m�thode est appel�e la premi�re fois que
	/// GetFilesIntf est appel�e.
	///
	/// \return une abstraction pour utiliser les fichiers.
	///
	virtual IDCLFiles*		CreateFilesIntf( void ) = 0;
	
	///
	/// Retourne l'abstraction pour les processus l�gers.
	/// Cette m�thode est appel�e la premi�re fois que
	/// GetThreadsIntf est appel�e.
	///
	/// \return une abstraction pour les processus l�gers.
	///
	virtual IDCLThreads*	CreateThreadsIntf( void ) = 0;

	/// \name Variables priv�es
	
	IDCLFiles*		mFilesIntf;		///< Abstraction pour les fichiers.
	IDCLThreads*	mThreadsIntf;	///< Abstraction pour les processus l�gers.
};

#endif
		// __TDCLAPPLICATION__

// ========================================================================== //
// You can now buy more gates with less specifications than at any other time //
// in history.                                                                //
//                 -- Kenneth Parker                                          //
// ========================================================================== //
