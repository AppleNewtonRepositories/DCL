// ==============================
// Fichier:			TDCLMacFile.h
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
// The Original Code is TDCLMacFile.h.
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
// $Id: TDCLMacFile.h,v 1.5 2004/11/24 14:09:00 paul Exp $
// ===========

#ifndef __TDCLMACFILE__
#define __TDCLMACFILE__

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Exceptions/IO_Exceptions/TDCLIOException.h>
#include <DCL/Interfaces/TDCLFile.h>
#include <DCL/Interfaces/MacOS/TDCLMacFiles.h>
#include <DCL/Streams/TDCLStream.h>

// MacOS
#if TARGET_OS_MACOS
	#include <Files.h>
#else
	#include <CoreServices/CoreServices.h>
#endif

class TDCLFolder;

///
/// Classe de base pour les fichiers sous MacOS. Cette classe est d�riv�e
/// en une classe pour les fichiers version classique et une classe pour les
/// fichiers version porno.
///
/// La particularit� de cette classe ne r�side que dans la m�thode Create qui
/// a le code type et le code cr�ateur.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.5 $
///
/// \test	aucun test d�fini.
///
class TDCLMacFile
	:
		public TDCLFile
{
public:
	///
	/// Cr�e le fichier avec un code cr�ateur et un type donn�s.
	///
	/// \param inCreator	code cr�ateur du fichier � cr�er.
	/// \param inFileType	type du fichier � cr�er.
	/// \throws TDCLIOException si la cr�ation a �chou�.
	///
	virtual void		Create(
							OSType inCreator,
							OSType inFileType ) = 0;

	///
	/// Cr�e le fichier.
	///
	/// \throws TDCLIOException si la cr�ation a �chou�.
	///
	inline virtual void		Create( void )
		{
			Create( TDCLMacFiles::kCreator, TDCLMacFiles::kFileType );
		}

	///
	/// Change les codes type et cr�ateur.
	///
	/// \param inCreator	nouveau code cr�ateur du fichier.
	/// \param inFileType	nouveau type du fichier.
	/// \throws TDCLIOException si la cr�ation a �chou�.
	///
	virtual void	SetMetaData(
							OSType inCreator,
							OSType inFileType ) = 0;

	/// \name interface TDCLFile

	///
	/// D�termine si le fichier est ouvert.
	///
	/// \return \c true si le fichier est ouvert, \c false sinon.
	///
	virtual Boolean		IsOpen( void ) const;

	///
	/// D�termine si le fichier est ouvert en lecture seule.
	///
	/// \return \c true si le fichier est ouvert en lecture seule,
	///			\c false sinon. Le r�sultat est ind�termin� si le fichier
	///			n'est pas ouvert.
	///
	virtual Boolean		IsReadOnly( void ) const;

	///
	/// R�cup�re la description de l'�l�ment sous forme de structure.
	/// Ajoute 'whichVol � la structure si le fichier est sur le bureau.
	///
	/// \return la description de l'objet pour le butinage.
	///
	virtual TDCLNSRef	ToFrame( void );

protected:
	///
	/// Constructeur � partir d'un dossier parent.
	/// Le dossier parent doit �tre compatible avec la classe du fichier.
	///
	/// \param inFilesIntf	interface pour les fichiers.
	/// \param inFolder		dossier parent.
	///						(\c nil signifie que MakeParentFolder sera
	///							appel� plus tard).
	///
	TDCLMacFile( TDCLMacFiles* inFilesIntf, TDCLFSItemRef inFolder );

	///
	/// M�thode appel�e par les sous-classes lorsque le fichier est ouvert.
	///
	/// \param inReadOnly	si le fichier est en lecture seule.
	///
	void DoOpen( Boolean inReadOnly );
	
	///
	/// M�thode appel�e par les sous-classes lorsque le fichier est ferm�.
	///
	void DoClose( void );

	///
	/// Change les codes type et cr�ateur d'un fichier repr�sent� par
	/// son FSSpec.
	///
	/// \param inFSSpec		r�f�rence sur le fichier.
	/// \param inCreator	nouveau code cr�ateur du fichier.
	/// \param inFileType	nouveau type du fichier.
	/// \throws TDCLIOException si la cr�ation a �chou�.
	///
	static void	DoSetMetaData(
							const FSSpec* inFSSpec,
							OSType inCreator,
							OSType inFileType );
	
private:
	///
	/// D�termine si le fichier est sur le bureau.
	///
	/// \return \c true si le fichier est sur le bureau, \c false sinon.
	///
	virtual Boolean		IsOnDesktop( void ) const = 0;
	
	///
	/// R�cup�re la r�f�rence sur le volume o� se trouve le fichier.
	///
	/// \return le volume o� se trouve le fichier.
	///
	virtual short		GetVRefNum( void ) const = 0;

	/// \name variables priv�es
	
	Boolean				mReadOnly;		///< Si le fichier a �t� ouvert en
										///< lecture seule.
	Boolean				mIsOpen;		///< Si le fichier est ouvert.
};

#endif
		// __TDCLMACFILE__

// ========================================================================= //
// An interpretation I satisfies a sentence in the table language if and     //
// only if each entry in the table designates the value of the function      //
// designated by the function constant in the upper-left corner applied to   //
// the objects designated by the corresponding row and column labels.        //
//              -- Genesereth & Nilsson, "Logical foundations of Artificial  //
//                    Intelligence"                                          //
// ========================================================================= //
