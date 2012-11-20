// ==============================
// Fichier:			TDCLMacFolder.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			10/1/2003
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
// The Original Code is TDCLMacFolder.h.
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
// $Id: TDCLMacFolder.h,v 1.5 2004/11/24 14:09:00 paul Exp $
// ===========

#ifndef _TDCLMACFOLDER_H
#define _TDCLMACFOLDER_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/TDCLFolder.h>

// MacOS
#if TARGET_OS_MACOS
	#include <Files.h>
#else
	#include <CoreServices/CoreServices.h>
#endif

// DCL
#include <DCL/Interfaces/MacOS/TDCLMacFiles.h>

///
/// Classe pour l'abstraction d'un dossier sous MacOS
/// (y compris en version porno).
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.5 $
///
/// \test	aucun test d�fini.
///
class TDCLMacFolder
	:
		public TDCLFolder
{
public:
	///
	/// Cr�e un fichier d'un nom, d'un code cr�ateur et d'un type donn�s dans
	/// ce dossier.
	///
	/// \param inName		nom du fichier � cr�er.
	/// \param inCreator	code cr�ateur du fichier � cr�er.
	/// \param inFileType	type du fichier � cr�er.
	/// \return un objet TDCLFile repr�sentant ce nouveau fichier. Ce fichier
	///			est la propri�t� de l'appelant qui doit le supprimer.
	/// \throw TDCLException si un probl�me est survenu, y compris si le fichier
	///			existe d�j�.
	///
	virtual	TDCLFSItemRef	CreateFile(
								const KUInt16* inName,
								OSType inCreator,
								OSType inFileType ) = 0;

	///
	/// Cr�e un fichier d'un nom donn� dans ce dossier. Appelle la m�thode
	/// CreateFile avec le type et le code cr�ateur par d�faut.
	///
	/// \param inName		nom du fichier � cr�er.
	/// \return un objet TDCLFile repr�sentant ce nouveau fichier. Ce fichier
	///			est la propri�t� de l'appelant qui doit le supprimer.
	/// \throw TDCLException si un probl�me est survenu, y compris si le fichier
	///			existe d�j�.
	///
	inline virtual	TDCLFSItemRef	CreateFile( const KUInt16* inName )
		{
			return CreateFile(
				inName, TDCLMacFiles::kCreator, TDCLMacFiles::kFileType );
		}

protected:
	///
	/// Constructeur � partir d'un dossier parent (optionnel).
	///
	/// \param inFilesIntf		interface pour les fichiers.
	/// \param inParentFolder	dossier parent (ou \c nil si celui-ci sera cr��
	///							plus tard).
	///
	TDCLMacFolder(
				TDCLMacFiles* inFilesIntf,
				TDCLFSItemRef inParentFolder = TDCLFSItemRef() );

	///
	/// R�cup�re la description de l'�l�ment sous forme de structure.
	/// Ajoute les informations sur le volume si on est sur le bureau.
	///
	/// \return la description de l'objet pour le butinage.
	///
	virtual TDCLNSRef	ToFrame( void );

private:
	///
	/// D�termine si le dossier est un disque.
	///
	/// \return \c true si le dossier est le dossier racine d'un disque.
	///
	virtual Boolean		IsVolume( void ) const = 0;

	///
	/// D�termine si le dossier est sur le bureau.
	///
	/// \return \c true si le dossier est sur le bureau, \c false sinon.
	///
	virtual Boolean		IsOnDesktop( void ) const = 0;

	///
	/// R�cup�re la r�f�rence sur le volume o� se trouve le dossier.
	///
	/// \return le volume o� se trouve le dossier.
	///
	virtual short		GetVRefNum( void ) const = 0;
};

#endif
		// _TDCLMACFOLDER_H

// =================================================================== //
// The value of a program is proportional to the weight of its output. //
// =================================================================== //
