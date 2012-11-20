// ==============================
// Fichier:			TDCLMacOS7DesktopFolder.h
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
// The Original Code is TDCLMacOS7DesktopFolder.h.
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
// $Id: TDCLMacOS7DesktopFolder.h,v 1.3 2004/11/24 14:09:00 paul Exp $
// ===========

#ifndef _TDCLMACOS7DESKTOPFOLDER_H
#define _TDCLMACOS7DESKTOPFOLDER_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/MacOS/TDCLMacDesktopFolder.h>

///
/// Classe de base pour le dossier repr�sentant le bureau sous
/// MacOS.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLMacOS7DesktopFolder
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
	///			dernier pointeur est \c nil. Le tableau est allou� avec new.
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
	TDCLMacOS7DesktopFolder( TDCLMacFiles* inFilesIntf );
};

#endif
		// _TDCLMACDESKTOPFOLDER_H

// ============================================================================== //
//         A program should be light and agile, its subroutines connected like a  //
// strings of pearls.  The spirit and intent of the program should be retained    //
// throughout.  There should be neither too little nor too much, neither needless //
// loops nor useless variables, neither lack of structure nor overwhelming        //
// rigidity.                                                                      //
//         A program should follow the 'Law of Least Astonishment'.  What is this //
// law?  It is simply that the program should always respond to the user in the   //
// way that astonishes him least.                                                 //
//         A program, no matter how complex, should act as a single unit.  The    //
// program should be directed by the logic within rather than by outward          //
// appearances.                                                                   //
//         If the program fails in these requirements, it will be in a state of   //
// disorder and confusion.  The only way to correct this is to rewrite the        //
// program.                                                                       //
//                 -- Geoffrey James, "The Tao of Programming"                    //
// ============================================================================== //