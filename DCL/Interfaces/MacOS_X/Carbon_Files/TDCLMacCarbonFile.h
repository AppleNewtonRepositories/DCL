// ==============================
// Fichier:			TDCLMacCarbonFile.h
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
// The Original Code is TDCLMacCarbonFile.h.
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
// $Id: TDCLMacCarbonFile.h,v 1.9 2004/11/24 14:09:01 paul Exp $
// ===========

#ifndef _TDCLMACCARBONFILE_H
#define _TDCLMACCARBONFILE_H

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Interfaces/MacOS/TDCLMacFile.h>
#include <DCL/Interfaces/MacOS_X/Carbon_Files/TDCLMacCarbonFolder.h>
#include <DCL/Interfaces/MacOS_X/Carbon_Files/TDCLMacCarbonDesktopFolder.h>

// MacOS
#if TARGET_OS_MACOS
#include <Files.h>
#else
#include <CoreServices/CoreServices.h>
#endif

///
/// Classe pour les fichiers sur Mac utilisant les FSRef.
/// Requiert CarbonLib ou MacOS X.
///
/// \author Nicolas Zinovieff <krugazor@free.fr>
/// \version $Revision: 1.9 $
///
/// \test	aucun test d�fini.
///
class TDCLMacCarbonFile
	:
		public TDCLMacFile
{
public:
	///
	/// Constructeur pour un fichier existant � partir d'un FSRef uniquement.
	/// Cr�e l'objet repr�sentant le dossier parent.
	///
	/// \param inFilesIntf	interface pour les fichiers.
	/// \param inFSRef	r�f�rence sur le fichier
	///
	TDCLMacCarbonFile( TDCLMacFiles* inFilesIntf, const FSRef* inFSRef );

	///
	/// Destructeur.
	/// Ferme le fichier.
	///
	virtual ~TDCLMacCarbonFile( void );

	///
	/// Ouvre le fichier.
	///
	/// \param inReadOnly	si le fichier doit �tre ouvert en lecture seule
	/// \throws TDCLIOException si l'ouverture a �chou�.
	///
	virtual void		Open( Boolean inReadOnly );

	///
	/// Cr�e le fichier avec un code cr�ateur et un type donn�s.
	///
	/// \param inCreator	code cr�ateur du fichier � cr�er.
	/// \param inFileType	type du fichier � cr�er.
	/// \throws TDCLIOException si la cr�ation a �chou�.
	///
	virtual void		Create(
							OSType inCreator = TDCLMacFiles::kCreator,
							OSType inFileType = TDCLMacFiles::kFileType );

	///
	/// Change les codes type et cr�ateur.
	///
	/// \param inCreator	nouveau code cr�ateur du fichier.
	/// \param inFileType	nouveau type du fichier.
	/// \throws TDCLIOException si la cr�ation a �chou�.
	///
	virtual void		SetMetaData(
							OSType inCreator,
							OSType inFileType );

	/// \name interface TDCLFile

	///
	/// Supprime le fichier.
	///
	/// \throws TDCLIOException si la suppression a �chou�.
	///
	virtual void		Delete( void );

	///
	/// Retourne la longueur (logique) du fichier.
	///
	/// \return la taille du fichier, en octets.
	///
	virtual KUInt64		GetLength( void );
	
	///
	/// D�place le curseur dans le fichier. Peut lancer une exception
	/// pour indiquer que la fin du fichier a �t� atteinte.
	///
	/// \param inPos	nouvelle position du curseur
	/// \param inMode	d�finit l'origine de inPos
	/// \throws TDCLPositionException si la fin du fichier (ou le d�but) est
	///			d�pass�e.
	/// \throws TDCLBadStateError si le fichier n'est pas ouvert.
	///
	virtual void		SetCursor( KSInt64 inPos, ECursorMode inMode );

	///
	/// D�termine la position du curseur dans le fichier.
	///
	/// \return la position du curseur dans le fichier.
	/// \throws TDCLBadStateError si le fichier n'est pas ouvert.
	///
	virtual KSInt64		GetCursor( void );

	/// \name interface entr�e/sortie

	///
	/// Lit des octets.
	///
	/// \param outBuffer	m�moire tampon pour les octets lus.
	/// \param ioCount		nombre d'octets � lire en entr�e, lus en sortie.
	///						Cette valeur est mise � jour avant que 
	///						l'exception ne soit lanc�e si un probl�me est
	///						survenu.
	/// \throws TDCLIOException	si un probl�me est survenu (autre que EOF)
	///
	virtual	void		Read( void* outBuffer, KUInt32* ioCount );
	
	///
	/// Ecrit des octets.
	///
	/// \param inBuffer		m�moire tampon pour les octets � �crire.
	/// \param ioCount		nombre d'octets � �crire en entr�e, �cris en
	///						sortie. Cette valeur est mise � jour avant que
	///						l'exception ne soit lanc�e si un probl�me est
	///						survenu.
	/// \throws TDCLIOException	si un probl�me est survenu.
	///
	virtual	void		Write( const void* inBuffer, KUInt32* ioCount );

	///
	/// Vide la m�moire tampon de sortie.
	///
	/// \throws TDCLIOException	si un probl�me est survenu.
	///
	virtual void		FlushOutput( void );
	
	///
	/// Ferme le fichier.
	/// Ne fait rien si le fichier n'�tait pas ouvert.
	/// Cette m�thode est appel�e par le destructeur.
	///
	virtual void		Close( void );

	///
	/// R�cup�re le type du fichier sous forme de cha�ne NewtonScript.
	/// C'est ce qui est retourn� au Newton.
	///
	/// \return une cha�ne NewtonScript avec le type du fichier.
	///
	virtual TDCLNSRef	GetKind( void ) const;
	
	///
	/// R�cup�re la date de cr�ation au format des dates Newton
	/// (minutes depuis 1904).
	///
	/// \return la date de cr�ation du fichier.
	///
	virtual KUInt32		GetCreationDate( void ) const;

	///
	/// R�cup�re la date de modification au format des dates Newton
	/// (minutes depuis 1904).
	///
	/// \return la date de modification du fichier.
	///
	virtual KUInt32		GetModificationDate( void ) const;

	///
	/// R�cup�re le chemin du fichier dans une forme lisible par
	/// l'utilisateur. Ce chemin n'a pas d'autre fonction que
	/// d'�tre affich� sur le Newton.
	///
	/// \return le chemin du fichier dans une cha�ne NewtonScript.
	///
	virtual TDCLNSRef	GetStringPath( void ) const;

	///
	/// R�cup�re l'ic�ne du fichier sous forme de binaire noir et blanc
	/// 32x32.
	///
	/// \return l'ic�ne du fichier.
	///
	virtual TDCLNSRef	GetIcon( void ) const;

private:
	///
	/// La classe TDCLMacCarbonFolder cr�e les objets de type TDCLMacCarbonFile.
	///
	friend class TDCLMacCarbonFolder;
	
	/// Pareil pour la classe TDCLMacCarbonDesktopFolder.
	friend class TDCLMacCarbonDesktopFolder;

	///
	/// Constructeur � partir d'un dossier parent et d'un FSRef pour un
	/// fichier *existant* dans un dossier.
	///
	/// \param inFilesIntf	interface pour les fichiers.
	/// \param inFolder	dossier o� se trouve le fichier (peut-�tre le bureau)
	/// \param inFSRef	r�f�rence sur le fichier
	///
	TDCLMacCarbonFile(
					TDCLMacFiles* inFilesIntf,
					TDCLFSItemRef inFolder,
					const FSRef* inFSRef );

	///
	/// Constructeur � partir d'un dossier parent et d'un FSRef pour un
	/// fichier n'existant pas forc�ment dans un dossier.
	/// Ce constructeur doit �tre appel� par un objet TDCLMacCarbonFolder.
	/// Le nom du fichier est copi�.
	/// De plus, inFSRef doit correspondre � inFolder et inName.
	///
	/// \param inFilesIntf	interface pour les fichiers.
	/// \param inFolder	dossier o� se trouve le fichier.
	/// \param inFSRef	r�f�rence sur le fichier.
	///					Si c'est nul, la r�f�rence est cr��e.
	/// \param inName	nom du fichier (cha�ne UTF-16 avec terminateur nul).
	///
	TDCLMacCarbonFile(
					TDCLMacFiles* inFilesIntf,
					TDCLFSItemRef inFolder,
					const FSRef* inFSRef,
					const KUInt16* inName );

	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLMacCarbonFile( const TDCLMacCarbonFile& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLMacCarbonFile& operator = ( const TDCLMacCarbonFile& inCopy );

	///
	/// \brief Cr�e l'objet repr�sentant le dossier parent d'un objet donn�.
	///
	/// \param	inFilesIntf	interface pour les fichiers.
	/// \param	outIsOnDesktop en sortie, si le fichier est sur le bureau.
	/// \param	inFSRef r�f�rence sur l'objet dont on veut le dossier parent.
	/// \return le dossier parent (peut-�tre le bureau).
	///
	static TDCLFSItemRef	DoMakeParentFolder(
								TDCLMacFiles* inFilesIntf,
								Boolean* outIsOnDesktop,
								const FSRef* inFSRef );

	///
	/// Cr�e le nom du fichier.
	///
	/// \return le nom du fichier en UTF-16 (cette cha�ne est allou�e avec
	///			malloc).
	/// \throw TDCLIOException si un probl�me est survenu.
	///
	virtual KUInt16*	MakeName( void ) const;

	///
	/// Cr�e le FSRef.
	/// M�thode appel�e lorsque mRefIsValid est \c false et qu'on a besoin
	/// de mRef.
	///
	/// \throw TDCLIOException si un probl�me est survenu (en particulier
	///			si le fichier n'existe pas).
	///
	void				CreateFSRef( void );

	///
	/// D�termine si le fichier est sur le bureau.
	///
	/// \return \c true si le fichier est sur le bureau, \c false sinon.
	///
	virtual Boolean		IsOnDesktop( void ) const;

	///
	/// R�cup�re la r�f�rence sur le volume o� se trouve le fichier.
	///
	/// \return le volume o� se trouve le fichier.
	///
	virtual short		GetVRefNum( void ) const;

	///
	/// Construit l'objet TDCLFolder parent. Cette m�thode n'est
	/// appel�e que si l'objet parent qui a �t� fourni est \c nil.
	/// Met � jour mIsOnDesktop.
	///
	/// \return le parent de \c this.
	///
	virtual TDCLFSItemRef	MakeParentFolder( void ) const;

	/// \name Variables
	
	FSRef			mRef;			///< Le FSRef repr�sentant ce fichier.
	Boolean			mRefIsValid;	///< Si le FSRef est valide.
	FSRef			mParentRef;		///< Le FSRef sur le parent.
	KSInt16			mOpenedFork;	///< the ID of opened fork
	FSVolumeRefNum	mVRefNum;		///< R�f�rence du volume.
	mutable Boolean	mIsOnDesktop;	///< Si le fichier est sur le bureau.
};

#endif
		// _TDCLMACCARBONFILE_H

// ================================================================ //
// Government lies, and newspapers lie, but in a democracy they are //
// different lies.                                                  //
// ================================================================ //