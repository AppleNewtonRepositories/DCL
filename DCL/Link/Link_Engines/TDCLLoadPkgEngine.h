// ==============================
// Fichier:			TDCLLoadPkgEngine.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			10/5/2003
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
// The Original Code is TDCLLoadPkgEngine.h.
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
// $Id: TDCLLoadPkgEngine.h,v 1.4 2004/11/24 14:09:05 paul Exp $
// ===========

#ifndef _TDCLLOADPKGENGINE_H
#define _TDCLLOADPKGENGINE_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/Link_Engines/TDCLLinkEngine.h>
#include <DCL/Interfaces/TDCLFSItemRef.h>

///
/// Classe pour le moteur d'installation de paquet.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class TDCLLoadPkgEngine
	:
		public TDCLLinkEngine
{
public:
	///
	/// Constructeur � partir d'un lien.
	///
	/// \param inLink	r�f�rence sur le lien.
	///
	TDCLLoadPkgEngine( TDCLFullDockLink* inLink );
	
	///
	/// M�thode appel�e par le lien pour installer un paquet.
	///
	/// \param inPackage	paquet � installer.
	/// \throws TDCLException si une erreur est survenue.
	///
	void			InstallPackage(
								TDCLFSItemRef inPackage );

	///
	/// M�thode appel�e pour g�rer des commandes venant du Newton.
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return \c true si le moteur continue, \c false sinon
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual	Boolean	ProcessDockCommand(
									TDCLDockCommand* inCommand,
									Boolean* outProcessed );

protected:
	///
	/// M�thode appel�e pour indiquer qu'on commence � installer le paquet.
	/// Cette m�thode doit initialiser la progression d'installation ou un truc
	/// approchant. Par d�faut ne fait rien.
	///
	/// \param inPackageName	nom du paquet install�.
	///
	virtual void		StartInstallingPackage( const KUInt16* inPackageName );

	///
	/// M�thode appel�e pour indiquer la progression de l'installation.
	/// Par d�faut ne fait rien.
	///
	/// \param inProgress	progression de l'installation (valeur entre 0 et 1)
	///
	virtual void		InstallationProgress( double inProgress );

private:
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
		// _TDCLLOADPKGENGINE_H

// ============================================================================ //
// To say that UNIX is doomed is pretty rabid, OS/2 will certainly play a role, //
// but you don't build a hundred million instructions per second multiprocessor //
// micro and then try to run it on OS/2.  I mean, get serious.                  //
//                 -- William Zachmann, International Data Corp                 //
// ============================================================================ //
