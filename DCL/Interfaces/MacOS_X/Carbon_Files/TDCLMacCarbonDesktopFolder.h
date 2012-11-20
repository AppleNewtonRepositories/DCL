// ==============================
// Fichier:			TDCLMacCarbonDesktopFolder.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			13/1/2003
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
// The Original Code is TDCLMacCarbonDesktopFolder.h.
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
// $Id: TDCLMacCarbonDesktopFolder.h,v 1.4 2004/11/24 14:09:01 paul Exp $
// ===========

#ifndef _TDCLMACCARBONDESKTOPFOLDER_H
#define _TDCLMACCARBONDESKTOPFOLDER_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/MacOS_X/Carbon_Files/TDCLMacCarbonFolder.h>

// Pr�-d�clarations
class TDCLMacFiles;

///
/// Classe pour le bureau sous MacOS X.
/// C'est un faux dossier.
/// Contient tous les �l�ments sur le bureau de l'utilisateur plus les volumes.
/// Num�rotation: d'abord les �l�ments sur le bureau puis les volumes.
///
/// \author Nicolas Zinovieff <krugazor@free.fr>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class TDCLMacCarbonDesktopFolder
	:
		public TDCLMacDesktopFolder
{
public:
	///
	/// R�cup�re une r�f�rence sur un �l�ment dans ce dossier.
	/// Retourne nil si l'�l�ment n'existe pas.
	///
	/// \param inName		nom de l'�l�ment.
	/// \param inVolRefNum	r�f�rence du volume. Ce param�tre est utilis� en concordance
	///						avec la m�thode ToFrame.
	/// \return un objet TDCLFSItem repr�sentant cet �l�ment ou \c nil si aucun
	///			�l�ment de ce nom n'existe. Cet �l�ment est la propri�t� de l'appelant
	///			qui doit le supprimer.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual	TDCLFSItemRef	GetItemByName(
									const KUInt16* inName,
									KSInt32 inVolRefNum = 0 );

	///
	/// Cr�e un fichier d'un nom donn� dans ce dossier.
	///
	/// \param inName		nom du fichier � cr�er.
	/// \return un objet TDCLFile repr�sentant ce nouveau fichier. Ce fichier
	///			est la propri�t� de l'appelant qui doit le supprimer.
	/// \throw TDCLException si un probl�me est survenu, y compris si le fichier
	///			existe d�j�.
	///
	virtual	TDCLFSItemRef	CreateFile( const KUInt16* inName );

	///
	/// Cr�e un dossier d'un nom donn� dans ce dossier.
	///
	/// \param inName		nom du dossier � cr�er.
	/// \return un objet TDCLFolder repr�sentant ce nouveau dossier. Ce dossier
	///			est la propri�t� de l'appelant qui doit le supprimer.
	/// \throw TDCLException si un probl�me est survenu, y compris si le dossier
	///			existe d�j�.
	///
	virtual	TDCLFSItemRef	CreateFolder( const KUInt16* inName );

	///
	/// Compte les �l�ments dans ce dossier.
	/// Notez que ce nombre peut changer juste apr�s l'appel � cette fonction.
	///
	/// \return le nombre d'�l�ment dans le dossier.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual KUInt32			CountElements( void );

	///
	/// Retourne un tableau avec tous les �l�ments du dossier.
	/// Notez que ces �l�ments peuvent dispara�tre juste apr�s l'appel � cette fonction
	/// et d'autres �l�ments peuvent appara�tre.
	///
	/// \return un tableau de n+1 pointeurs sur des TDCLFSItem. Le
	///			dernier pointeur est \c nil. Le tableau est allou� avec malloc.
	///			Ces �l�ments sont la propri�t� de l'appelant qui doit les supprimer.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual TDCLFSItemRef*	GetItems( void );

private:
	/// Seule la classe TDCLMacFiles peut construire des objets de notre classe.
	friend class TDCLMacFiles;

	///
	/// Constructeur � partir de l'interface sur les fichiers.
	///
	/// \param inFilesIntf		interface pour les fichiers.
	///
	TDCLMacCarbonDesktopFolder( TDCLMacFiles* inFilesIntf );
	
	/// \name Variables
	FSRef					mDesktopFolderRef; ///< R�f�rence sur le bureau.
};

#endif
		// _TDCLMACCARBONDESKTOPFOLDER_H

// ===================================================================== //
// If there is a possibility of several things going wrong, the one that //
// will cause the most damage will be the one to go wrong.               //
// ===================================================================== //