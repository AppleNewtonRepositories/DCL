// ==============================
// Fichier:			TDCLMacCarbonFolder.h
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
// The Original Code is TDCLMacCarbonFolder.h.
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
// $Id: TDCLMacCarbonFolder.h,v 1.5 2004/11/24 14:09:02 paul Exp $
// ===========

#ifndef _TDCLMACCARBONFOLDER_H
#define _TDCLMACCARBONFOLDER_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/MacOS/TDCLMacFolder.h>

// DCL
#include <DCL/Interfaces/MacOS/TDCLMacFiles.h>

// MacOS
#if TARGET_OS_MACOS
#include <Folders.h>
#else
#include <CoreServices/CoreServices.h>
#endif

///
/// Classe pour .
///
/// \author Nicolas Zinovieff <krugazor@free.fr>
/// \version $Revision: 1.5 $
///
/// \test	aucun test d�fini.
///
class TDCLMacCarbonFolder
	:
		public TDCLMacFolder
{
public:
	///
	/// Constructeur � partir d'un FSRef.
	///
	/// \param inFilesIntf		interface pour les fichiers.
	/// \param inRef			r�f�rence sur le fichier.
	///
	TDCLMacCarbonFolder( TDCLMacFiles* inFilesIntf, const FSRef* inRef );

	///
	/// R�cup�re une r�f�rence sur un �l�ment dans ce dossier.
	/// Retourne nil si l'�l�ment n'existe pas.
	///
	/// \param inName		nom de l'�l�ment.
	/// \param inVolRefNum	r�f�rence du volume (utilis� pour le bureau).
	///						Ce param�tre est ignor�.
	/// \return un objet TDCLFSItem repr�sentant cet �l�ment ou \c nil si aucun
	///			�l�ment de ce nom n'existe. Cet �l�ment est la propri�t� de l'appelant
	///			qui doit le supprimer.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual	TDCLFSItemRef		GetItemByName(
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
	virtual	TDCLFSItemRef		CreateFile(
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
	virtual	TDCLFSItemRef		CreateFolder( const KUInt16* inName );

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
	/// \return un tableau de n+1 TDCLFSItemRef. Le dernier �l�ment est une r�f�rence
	///			sur \c nil. Le tableau est allou� avec malloc.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual TDCLFSItemRef*	GetItems( void );

	///
	/// Retourne un tableau avec tous les �l�ments d'un dossier.
	///
	/// \param inFilesIntf	interface pour les fichiers.
	/// \param inRef		r�f�rence sur le dossier dont on veut les �l�ments.
	/// \param outCount		en sortie, si ce n'est pas \c nil, le nombre 
	///						d'�l�ments (n)
	/// \return un tableau de n+1 TDCLFSItemRef. Le dernier �l�ment est une r�f�rence
	///			sur \c nil. Le tableau est allou� avec malloc.
	/// \throw TDCLException si un probl�me est survenu.
	///
	static TDCLFSItemRef*		GetFolderItems(
								TDCLMacFiles* inFilesIntf,
								const FSRef* inRef,
								KUInt32* outCount = nil );

private:
	/// On autorise TDCLMacCarbonFile d'appeler GetRef.
	friend class TDCLMacCarbonFile;

	///
	/// La classe TDCLMacCarbonDesktopFolder cr�e des objets de type TDCLMacCarbonFile.
	///
	friend class TDCLMacCarbonDesktopFolder;
	
	///
	/// Constructeur � partir d'un dossier parent et d'un FSRef.
	/// La r�f�rence doit correspondre au dossier.
	///
	/// \param inFilesIntf		interface pour les fichiers.
	/// \param inParentFolder	dossier parent.
	/// \param inRef			r�f�rence sur le fichier.
	///
	TDCLMacCarbonFolder(
						TDCLMacFiles* inFilesIntf,
						TDCLFSItemRef inParentFolder,
						const FSRef* inRef );

	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLMacCarbonFolder( const TDCLMacCarbonFolder& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLMacCarbonFolder& operator = ( const TDCLMacCarbonFolder& inCopy );

	///
	/// R�cup�re le FSRef sur le dossier.
	///
	/// \return mRef
	///
	inline const FSRef* GetRef( void ) const
		{
			return &mRef;
		};
	
	///
	/// Construit l'objet TDCLFolder parent. Cette m�thode n'est appel�e
	/// que si n�cessaire.
	///
	/// \return une r�f�rence sur un objet repr�sentant le dossier parent ou sur \c nil.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual TDCLFSItemRef	MakeParentFolder( void ) const;

	///
	/// Construit le nom de l'objet. C'est une cha�ne unicode UTF-16 qui est allou�e
	/// avec malloc. Cette m�thode n'est appel�e que si n�cessaire (au plus une fois).
	///
	/// \return le nom allou� avec malloc.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual KUInt16*	MakeName( void ) const;

	///
	/// D�termine si le dossier est un disque.
	///
	/// \return \c true si le dossier est le dossier racine d'un disque.
	///
	virtual Boolean		IsVolume( void ) const;

	///
	/// D�termine si le dossier est sur le bureau.
	///
	/// \return \c true si le dossier est sur le bureau, \c false sinon.
	///
	virtual Boolean		IsOnDesktop( void ) const;

	///
	/// R�cup�re la r�f�rence sur le volume o� se trouve le fichier.
	///
	/// \return le volume o� se trouve le fichier.
	///
	virtual short		GetVRefNum( void ) const;

	///
	/// Initialise mVRefNum, mIsVolume, mParentRef et mIsOnDesktop.
	///
	///�\throws TDCLException si un probl�me est survenu.
	///
	void				Init( void );

	/// \name Variables	
	FSRef 				mRef;			///< the FSRef
	FSVolumeRefNum		mVRefNum;		///< R�f�rence du volume.
	Boolean				mIsVolume;		///< Si on est un volume.
	FSRef				mParentRef;		///< R�f�rence sur le parent (invalide
										///< si on a mIsVolume)
	Boolean				mIsOnDesktop;	///< Si on est sur le bureau.
};

#endif
		// _TDCLMACCARBONFOLDER_H

// ====================================================================== //
// "The first rule of magic is simple.  Don't waste your time waving your //
// hands and hoping when a rock or a club will do."                       //
//   -- McCloctnik the Lucid                                              //
// ====================================================================== //