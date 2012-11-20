// ==============================
// Fichier:			TDCLPOSIXDirBase.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			20/9/2003
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
// The Original Code is TDCLPOSIXDirBase.h.
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
// $Id: TDCLPOSIXDirBase.h,v 1.3 2004/11/24 14:09:02 paul Exp $
// ===========

#ifndef _TDCLPOSIXDIRBASE_H
#define _TDCLPOSIXDIRBASE_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/TDCLFolder.h>

// SUSv2
#include <sys/types.h>
#include <dirent.h>

// DCL
#include <DCL/Interfaces/POSIX/TDCLPOSIXFiles.h>

///
/// Classe de base pour les r�pertoires POSIX.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLPOSIXDirBase
	:
		virtual public TDCLFolder
{
public:
	///
	/// Destructeur.
	/// Ferme le dossier.
	///
	virtual ~TDCLPOSIXDirBase( void );

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
	virtual	TDCLFSItemRef	GetItemByName( const KUInt16* inName, KSInt32 inVolRefNum = 0 );

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
	/// \return un tableau de n+1 TDCLFSItemRef. Le dernier �l�ment est une r�f�rence
	///			sur \c nil. Le tableau est allou� avec malloc.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual TDCLFSItemRef*	GetItems( void );

protected:
	///
	/// Constructeur � partir d'un dossier parent (facultatif) et d'un chemin.
	/// Le dossier parent doit �tre compatible avec la classe du fichier.
	///
	/// \param inFilesIntf	interface pour les fichiers.
	/// \param inFolder		dossier parent (peut �tre \c nil)
	/// \param inPath		chemin complet vers le dossier.
	///
	TDCLPOSIXDirBase(
			TDCLPOSIXFiles* inFilesIntf,
			TDCLFSItemRef inFolder,
			const char* inPath );

	///
	/// Accesseur sur le chemin.
	///
	/// \return une r�f�rence sur le chemin.
	///
	inline const char* GetPOSIXPath( void ) const
		{
			return mPath;
		}

private:
	///
	/// Construit le nom de l'objet. C'est une cha�ne unicode UTF-16 qui est allou�e
	/// avec malloc. Cette m�thode n'est appel�e que si n�cessaire (au plus une fois).
	///
	/// \return le nom allou� avec malloc.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual KUInt16*	MakeName( void ) const;

	///
	/// Ouvre le dossier � partir du chemin.
	///
	void			OpenDir( void );

	DIR*			mDirRef;	///< R�f�rence sur le dossier.
	const char*		mPath;		///< Chemin du dossier.
};

#endif
		// _TDCLPOSIXDIRBASE_H

// ======================================= //
// Building translators is good clean fun. //
//                 -- T. Cheatham          //
// ======================================= //
