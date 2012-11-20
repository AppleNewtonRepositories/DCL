// ==============================
// Fichier:			TDCLPOSIXDir.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			22/6/2003
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
// The Original Code is TDCLPOSIXDir.h.
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
// $Id: TDCLPOSIXDir.h,v 1.5 2004/11/24 14:09:02 paul Exp $
// ===========

#ifndef _TDCLPOSIXDIR_H
#define _TDCLPOSIXDIR_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/POSIX/TDCLPOSIXDirBase.h>

// DCL
#include <DCL/Interfaces/POSIX/TDCLPOSIXFiles.h>

///
/// Classe pour un dossier ANSI C/POSIX.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.5 $
///
/// \test	aucun test d�fini.
///
class TDCLPOSIXDir
	:
		public TDCLPOSIXDirBase
{
protected:
	friend class TDCLPOSIXDirBase;
	friend class TDCLPOSIXFile;

	///
	/// Constructeur � partir d'un dossier parent (facultatif) et d'un chemin.
	/// Le dossier parent doit �tre compatible avec la classe du fichier.
	///
	/// \param inFilesIntf	interface pour les fichiers.
	/// \param inFolder		dossier parent (peut �tre \c nil)
	/// \param inPath		chemin complet vers le dossier.
	///
	TDCLPOSIXDir(
			TDCLPOSIXFiles* inFilesIntf,
			TDCLFSItemRef inFolder,
			const char* inPath );

private:
	///
	/// Construit l'objet TDCLFolder parent. Cette m�thode n'est appel�e
	/// que si n�cessaire.
	///
	/// \return une r�f�rence sur un objet repr�sentant le dossier parent ou sur \c nil.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual TDCLFSItemRef	MakeParentFolder( void ) const;
};

#endif
		// _TDCLPOSIXDIR_H

// =================================================== //
// "It runs like _x, where _x is something unsavory" //
//                 -- Prof. Romas Aleliunas, CS 435    //
// =================================================== //
