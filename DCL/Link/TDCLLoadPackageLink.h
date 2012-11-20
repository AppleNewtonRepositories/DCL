// ==============================
// Fichier:			TDCLLoadPackageLink.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			13/08/2001
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
// The Original Code is TDCLLoadPackageLink.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2001-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLLoadPackageLink.h,v 1.3 2004/11/24 14:09:03 paul Exp $
// ===========

#ifndef __TDCLLOADPACKAGELINK__
#define __TDCLLOADPACKAGELINK__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/TDCLLink.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>
#include <DCL/Interfaces/TDCLFSItemRef.h>

// Pr�-d�clarations.
class TDCLApplication;

///
/// Classe pour un lien qui g�re le sous-protocole d'installation de paquets.
/// 
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
//
class TDCLLoadPackageLink
	:
		public TDCLLink
{
public:
	///
	/// Constructeur � partir d'une application.
	///
	/// \param inApplication	application qui g�re ce line.
	///
	TDCLLoadPackageLink( TDCLApplication* inApplication );

	///
	/// M�thode synchrone pour connecter le Newton.
	/// Appelle d'abord TDCLLink::DoConnect pour le d�but.
	/// Ensuite, on lance l'installation de paquets:
	///
	/// kDSetTimeout ->
	///				<- kDResult
	///
	/// Normalement, vous n'avez pas besoin de surcharger cette m�thode.
	///
	virtual void		DoConnect ( void );

	///
	/// Installe un paquet. (Cette m�thode est en fait asynchrone et poste un �v�nement
	/// pour le lien).
	///
	/// \param inPackage	paquet � installer.
	/// \return \c true si le lien �tait connect�, \c false sinon (auquel cas
	///			le paquet ne sera pas install�).
	///
	Boolean InstallPackage( TDCLFSItemRef inPackage );

protected:
	///
	/// M�thode appel�e pour indiquer qu'on commence � installer le paquet.
	/// Cette m�thode doit initialiser la progression d'installation ou un truc
	/// approchant. Par d�faut ne fait rien.
	///
	virtual void		StartInstallingPackage( void );

	///
	/// M�thode appel�e pour indiquer la progression de l'installation.
	/// Par d�faut ne fait rien.
	///
	/// \param inProgress	progression de l'installation (valeur entre 0 et 1)
	///
	virtual void		InstallationProgress( double inProgress );

private:
	///
	/// Installe v�ritablement un paquet.
	///
	/// \param inPackage	paquet � installer.
	/// \throws TDCLException si une erreur est survenue.
	///
	void DoInstallPackage( TDCLFSItemRef inPackage );

	///
	/// M�thode appel�e lorsqu'on a re�u une commande de l'application.
	/// La commande est supprim�e une fois que cette m�thode retourne.
	/// Cette classe ne traite que la commande d'installation de paquet.
	/// Remarque: cette commande n'est pas trait�e comme le fait TDCLFullDockLink.
	/// Ici, nous n'indiquons pas au Newton que nous allons installer un paquet.
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e. Si la valeur est
	///						\c false, une exception est lev�e dans la boucle.
	/// \return le prochain �tat du lien (l'�tat actuel �tant kRunning)
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual	EState	ProcessAppCommand(
								TDCLAppCommand* inCommand,
								Boolean* outProcessed );

	///
	/// M�thode appel�e par \c SendCommand pour savoir la progression de
	/// l'envoi du paquet.
	///
	/// \param inRefCon		biscuit (en fait \c this)
	/// \param inProgress	progression entre 0 et 1
	///
	static void					ProgressFunc(
										void* inRefCon,
										double inProgress );
};

#endif
		// __TDCLLOADPACKAGELINK__

// ====================================================================== //
// Systems have sub-systems and sub-systems have sub-systems and so on ad //
// infinitum -- which is why we're always starting over.                  //
//                 -- Epigrams in Programming, ACM SIGPLAN Sept. 1982     //
// ====================================================================== //
