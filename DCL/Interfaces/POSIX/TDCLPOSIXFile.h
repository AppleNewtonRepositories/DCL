// ==============================
// Fichier:			TDCLPOSIXFile.h
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
// The Original Code is TDCLPOSIXFile.h.
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
// $Id: TDCLPOSIXFile.h,v 1.9 2004/11/24 14:09:02 paul Exp $
// ===========

#ifndef _TDCLPOSIXFILE_H
#define _TDCLPOSIXFILE_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/TDCLFile.h>

// ANSI C
#include <stdio.h>

class TDCLPOSIXFiles;

///
/// Classe pour les fichiers dans un environnement POSIX.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.9 $
///
/// \test	aucun test d�fini.
///
class TDCLPOSIXFile
	:
		public TDCLFile
{
public:
	///
	/// Constructeur � partir de l'interface POSIXFiles et d'un chemin complet.
	/// Le dossier parent sera cr��.
	///
	/// \param inFilesIntf		interface pour les fichiers.
	/// \param inPath			chemin complet vers le fichier.
	///
	TDCLPOSIXFile(
				TDCLPOSIXFiles* inFilesIntf,
				const char* inPath );

	///
	/// Destructeur.
	/// Ferme le fichier.
	///
	virtual ~TDCLPOSIXFile( void );

	///
	/// Ouvre le fichier.
	///
	/// \param inReadOnly	si le fichier doit �tre ouvert en lecture seule
	/// \throws TDCLIOException si l'ouverture a �chou�.
	///
	virtual void		Open( Boolean inReadOnly );	

	///
	/// Cr�e le fichier.
	///
	/// \throws TDCLIOException si la cr�ation a �chou�.
	///
	virtual void		Create( void );	

	///
	/// Supprime le fichier.
	///
	/// \throws TDCLIOException si la suppression a �chou�.
	///
	virtual void		Delete( void );	

	///
	/// Determine si le fichier est ouvert.
	///
	/// \return \c true si le fichier est ouvert, \c false sinon.
	///
	virtual Boolean		IsOpen( void ) const;

	///
	/// Determine si le fichier est ouvert en lecture seule.
	///
	/// \return \c true si le fichier est ouvert en lecture seule,
	///			\c false sinon. Le r�sultat est ind�termin� si le fichier
	///			n'est pas ouvert.
	///
	virtual Boolean		IsReadOnly( void ) const;

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

	///
	/// Retourne la longueur (logique) du fichier.
	///
	/// \return la taille du fichier, en octets.
	///
	virtual KUInt64		GetLength( void );
	
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
	/// Vous souhaitez probablement appeler la m�thode close dans votre
	/// destructeur.
	/// Ne fait rien si le fichier n'�tait pas ouvert.
	///
	virtual void		Close( void );

	///
	/// R�cup�re le type du fichier sous forme de cha�ne NewtonScript.
	/// C'est ce qui est retourn� au Newton pour affichage dans
	/// le butineur.
	///
	/// \return une cha�ne NewtonScript avec le type du fichier.
	///
	virtual TDCLNSRef	GetKind( void ) const;
	
	///
	/// R�cup�re la date de cr�ation au format des dates Newton
	/// (minutes depuis 1904).
	/// Ce n'est pas vraiment la date de cr�ation pour les fichiers POSIX,
	/// mais �a ira vu l'utilisation qu'on en fait.
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

private:
	///
	/// La classe TDCLPOSIXDirBase cr�e des objets de type TDCLPOSIXFile
	///
	friend class TDCLPOSIXDirBase;

	///
	/// Constructeur � partir de l'interface POSIXFiles, d'un dossier parent
	/// et d'un chemin complet.
	///
	/// \param inFilesIntf		interface pour les fichiers.
	/// \param inParentFolder	dossier parent.
	///							(\c nil signifie que MakeParentFolder sera
	///							appel� plus tard).
	/// \param inPath			chemin complet vers le fichier.
	///
	TDCLPOSIXFile(
				TDCLPOSIXFiles* inFilesIntf,
				TDCLFSItemRef inParentFolder,
				const char* inPath );

	///
	/// Cr�e l'objet repr�sentant le dossier parent d'un objet donn�.
	///
	/// \param	inFilesIntf	interface pour les fichiers.
	/// \param	inPath chemin sur l'objet dont on veut le dossier parent.
	/// \return le dossier parent.
	///
	static TDCLFSItemRef	DoMakeParentFolder(
								TDCLPOSIXFiles* inFilesIntf,
								const char* inPath );

	///
	/// Construit le nom de l'objet. C'est une cha�ne unicode UTF-16 qui est allou�e
	/// avec malloc. Cette m�thode n'est appel�e que si n�cessaire (au plus une fois).
	///
	/// \return le nom allou� avec malloc.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual KUInt16*	MakeName( void ) const;

	///
	/// Construit l'objet TDCLFolder parent. Cette m�thode n'est
	/// appel�e que si l'objet parent qui a �t� fourni est \c nil.
	///
	/// \return le parent de \c this.
	///
	virtual TDCLFSItemRef	MakeParentFolder( void ) const;

	/// \name Variables
	FILE*				mFile;		///< R�f�rence sur le fichier (C 89),
									///< \c nil si le fichier n'a pas �t�
									///< ouvert.
	const char*			mPath;		///< Chemin du fichier.
	Boolean				mReadOnly;	///< Si le fichier a �t� ouvert en lecture seule.
};

#endif
		// _TDCLPOSIXFILE_H

// =========================================== //
// Your mode of life will be changed to ASCII. //
// =========================================== //
