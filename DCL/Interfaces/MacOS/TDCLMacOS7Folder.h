// ==============================
// Fichier:			TDCLMacOS7Folder.h
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
// The Original Code is TDCLMacOS7Folder.h.
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
// $Id: TDCLMacOS7Folder.h,v 1.3 2004/11/24 14:09:00 paul Exp $
// ===========

#ifndef _TDCLMACOS7FOLDER_H
#define _TDCLMACOS7FOLDER_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/MacOS/TDCLMacFolder.h>

// DCL
#include <DCL/Interfaces/MacOS/TDCLMacFiles.h>

///
/// Classe pour les dossiers sous MacOS.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLMacOS7Folder
	:
		public TDCLMacFolder
{
public:
	///
	/// Constructeur � partir d'un volume et d'un ID de dossier.
	///
	/// \param	inFilesIntf	interface pour les fichiers
	/// \param	inVRefNum	r�f�rence sur le volume.
	/// \param	inDirID		ID du dossier.
	///
	TDCLMacOS7Folder(
					TDCLMacFiles* inFilesIntf,
					short inVRefNum,
					long inDirID );

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
								OSType inCreator = TDCLMacFiles::kCreator,
								OSType inFileType = TDCLMacFiles::kFileType );

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
	///			dernier pointeur est \c nil. Le tableau est allou� avec new.
	///			Ces �l�ments sont la propri�t� de l'appelant qui doit les supprimer.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual TDCLFSItemRef*	GetItems( void );

private:
	///
	/// Constructeur par d�faut volontairement indisponible.
	///
	TDCLMacOS7Folder( void );

	///
	/// Constructeur � partir d'un dossier parent et d'un ID de dossier.
	///
	/// \param	inFilesIntf	interface pour les fichiers
	/// \param	inParentFolder	dossier parent.
	/// \param	inDirID			ID du dossier.
	///
	TDCLMacOS7Folder(
				TDCLMacFiles* inFilesIntf,
				TDCLFSItemRef inParentFolder,
				long inDirID );

	///
	/// Retourne l'ID du dossier parent.
	///
	/// \return l'ID du dossier parent.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual long			GetParentID( void ) const;

	///
	/// Construit l'objet TDCLFolder parent. Cette m�thode n'est appel�e
	/// que si n�cessaire.
	///
	/// \return un objet repr�sentant le dossier parent ou \c nil.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual TDCLFSItemRef	MakeParentFolder( void ) const;

	///
	/// Construit un FSSpec pour un �l�ment dans ce dossier � partir
	/// de son nom.
	///
	/// \param inName		le nom de l'�l�ment en UTF-16.
	/// \param outFSSPec	en sortie, le FSSpec.
	/// \return \c true si l'�l�ment existe, \c false si le fichier
	///			n'existe pas.
	/// \throw TDCLException si un probl�me est survenu.
	///
	Boolean					MakeFSSpecForItem(
									const KUInt16* inName,
									FSSpec* outFSSPec ) const;

	///
	/// Construit le nom de l'objet. C'est une cha�ne unicode UTF-16 qui est allou�e
	/// avec malloc. Cette m�thode n'est appel�e que si n�cessaire (au plus une fois).
	///
	/// \return le nom allou� avec malloc.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual KUInt16*		MakeName( void ) const;

	///
	/// D�termine si le dossier est un disque.
	///
	/// \return \c true si le dossier est le dossier racine d'un disque.
	///
	virtual Boolean			IsVolume( void ) const;

	///
	/// D�termine si le dossier est sur le bureau.
	///
	/// \return \c true si le dossier est sur le bureau, \c false sinon.
	///
	virtual Boolean			IsOnDesktop( void ) const;

	///
	/// R�cup�re la r�f�rence sur le volume o� se trouve le dossier.
	///
	/// \return le volume o� se trouve le dossier.
	///
	virtual short			GetVRefNum( void ) const;

	/// \name Variables

	short		mVRefNum;	///< Identifiant du volume o� se trouve le dossier
	long		mDirID;		///< Identifiant du dossier sur le volume
};

#endif
		// _TDCLMACOS7FOLDER_H

// ========================================================================== //
// On two occasions I have been asked [by members of Parliament!], "Pray, Mr. //
// Babbage, if you put into the machine wrong figures, will the right answers //
// come out?"  I am not able rightly to apprehend the kind of confusion of    //
// ideas that could provoke such a question.                                  //
//                 -- Charles Babbage                                         //
// ========================================================================== //