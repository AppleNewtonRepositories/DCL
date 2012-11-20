// ==============================
// Fichier:			TDCLFolder.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			09/02/2003
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
// The Original Code is TDCLFolder.h.
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
// $Id: TDCLFolder.h,v 1.3 2004/11/24 14:08:59 paul Exp $
// ===========

#ifndef __TDCLFOLDER__
#define __TDCLFOLDER__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/TDCLFSItem.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>
#include <DCL/Interfaces/TDCLFSItemRef.h>

class TDCLFile;

///
/// Classe pour l'abstraction d'un dossier.
/// Un dossier contient des fichiers. On peut parcourir la liste des �l�ments,
/// ouvrir/cr�er/supprimer un �l�ment particulier.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLFolder
	:
		public TDCLFSItem
{
public:
	///
	/// R�cup�re une r�f�rence sur un �l�ment dans ce dossier.
	/// Retourne nil si l'�l�ment n'existe pas.
	///
	/// \param inName		nom de l'�l�ment.
	/// \param inVolRefNum	r�f�rence du volume (utilis� pour le bureau).
	///						Ce param�tre peut �tre ignor� si le Newton ne nous prend
	///						pas pour un Mac.
	/// \return un objet TDCLFSItem repr�sentant cet �l�ment ou \c nil si aucun
	///			�l�ment de ce nom n'existe. Cet �l�ment est la propri�t� de l'appelant
	///			qui doit le supprimer.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual	TDCLFSItemRef	GetItemByName( const KUInt16* inName, KSInt32 inVolRefNum = 0 ) = 0;

	///
	/// Cr�e un fichier d'un nom donn� dans ce dossier.
	///
	/// \param inName		nom du fichier � cr�er.
	/// \return un objet TDCLFile repr�sentant ce nouveau fichier. Ce fichier
	///			est la propri�t� de l'appelant qui doit le supprimer.
	/// \throw TDCLException si un probl�me est survenu, y compris si le fichier
	///			existe d�j�.
	///
	virtual	TDCLFSItemRef	CreateFile( const KUInt16* inName ) = 0;

	///
	/// Cr�e un dossier d'un nom donn� dans ce dossier.
	///
	/// \param inName		nom du dossier � cr�er.
	/// \return un objet TDCLFolder repr�sentant ce nouveau dossier. Ce dossier
	///			est la propri�t� de l'appelant qui doit le supprimer.
	/// \throw TDCLException si un probl�me est survenu, y compris si le dossier
	///			existe d�j�.
	///
	virtual	TDCLFSItemRef	CreateFolder( const KUInt16* inName ) = 0;

	///
	/// Compte les �l�ments dans ce dossier.
	/// Notez que ce nombre peut changer juste apr�s l'appel � cette fonction.
	///
	/// \return le nombre d'�l�ment dans le dossier.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual KUInt32			CountElements( void ) = 0;

	///
	/// Retourne un tableau avec tous les �l�ments du dossier.
	/// Notez que ces �l�ments peuvent dispara�tre juste apr�s l'appel � cette fonction
	/// et d'autres �l�ments peuvent appara�tre.
	///
	/// \return un tableau de n+1 TDCLFSItemRef. Le dernier �l�ment est une r�f�rence
	///			sur \c nil. Le tableau est allou� avec malloc.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual TDCLFSItemRef*	GetItems( void ) = 0;

	///
	/// R�cup�re la description de l'�l�ment sous forme de structure.
	/// Retourne une structure avec type: 'folder.
	///
	/// \return la description de l'objet pour le butinage.
	///
	virtual TDCLNSRef		ToFrame( void );

protected:
	///
	/// Constructeur � partir d'un dossier parent (optionnel).
	///
	/// \param inFilesIntf		interface pour les fichiers.
	/// \param inParentFolder	dossier parent (ou \c nil si celui-ci sera cr�� plus tard).
	///
	TDCLFolder( IDCLFiles* inFilesIntf, TDCLFSItemRef inParentFolder = TDCLFSItemRef() );
};

#endif
		// __TDCLFOLDER__

// =========================================================================== //
// Algol-60 surely must be regarded as the most important programming language //
// yet developed.                                                              //
//                 -- T. Cheatham                                              //
// =========================================================================== //
