// ==============================
// Fichier:			TDCLMacOS7File.h
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
// The Original Code is TDCLMacOS7File.h.
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
// $Id: TDCLMacOS7File.h,v 1.7 2004/11/24 14:09:00 paul Exp $
// ===========

#ifndef __TDCLMACOS7FILE__
#define __TDCLMACOS7FILE__

#include <DCL/Headers/DCLDefinitions.h>

// MacOS
#include <Files.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>
#include <DCL/Interfaces/MacOS/TDCLMacFile.h>
#include <DCL/Streams/TDCLStream.h>

///
/// Classe pour les fichiers sur Mac utilisant les FSSpec.
/// Requiert InterfaceLib 7.1 ou plus r�cent.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.7 $
///
/// \test	aucun test d�fini.
///
class TDCLMacOS7File
	:
		public TDCLMacFile
{
public:
	///
	/// Constructeur � partir d'un FSSpec uniquement.
	/// Cr�e l'objet repr�sentant le dossier parent.
	///
	/// \param inFilesIntf	interface pour les fichiers.
	/// \param inFSSpec	r�f�rence sur le fichier
	/// \throws TDCLException si l'ouverture a �chou�.
	///
	TDCLMacOS7File(
					TDCLMacFiles* inFilesIntf,
					const FSSpec* inFSSpec );

	///
	/// Destructeur.
	/// Ferme le fichier.
	///
	virtual				~TDCLMacOS7File( void );

	///
	/// Ouvre le fichier.
	///
	/// \param inReadOnly	si le fichier doit �tre ouvert en lecture seule
	/// \throws TDCLException si l'ouverture a �chou�.
	///
	virtual void		Open( Boolean inReadOnly );

	///
	/// Cr�e le fichier avec un code cr�ateur et un type donn�s.
	///
	/// \param inCreator	code cr�ateur du fichier � cr�er.
	/// \param inFileType	type du fichier � cr�er.
	/// \throws TDCLException si la cr�ation a �chou�.
	///
	virtual void		Create(
							OSType inCreator = TDCLMacFiles::kCreator,
							OSType inFileType = TDCLMacFiles::kFileType );

	///
	/// Change les codes type et cr�ateur.
	///
	/// \param inCreator	nouveau code cr�ateur du fichier.
	/// \param inFileType	nouveau type du fichier.
	/// \throws TDCLException si la cr�ation a �chou�.
	///
	virtual void		SetMetaData(
							OSType inCreator,
							OSType inFileType );

	/// \name interface TDCLFile

	///
	/// Supprime le fichier.
	///
	/// \throws TDCLException si la suppression a �chou�.
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
	/// \throws TDCLException si la fin du fichier (ou le d�but) est d�pass�e.
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
	/// \throws TDCLException	si un probl�me est survenu (autre que EOF)
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
	/// \throws TDCLException	si un probl�me est survenu.
	///
	virtual	void		Write( const void* inBuffer, KUInt32* ioCount );

	///
	/// Vide la m�moire tampon de sortie.
	///
	/// \throws TDCLException	si un probl�me est survenu.
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
	/// La classe TDCLMacOS7Folder cr�e les objets de type TDCLMacOS7File.
	///
	friend class TDCLMacOS7Folder;

	///
	/// Constructeur priv� (cette classe ne peut pas �tre d�riv�e).
	/// Ce constructeur doit �tre appel� un objet TDCLMacOS7Folder.
	/// De plus, inFSSpec doit correspondre � inFolder.
	///
	/// \param inFilesIntf	interface pour les fichiers.
	/// \param inFolder		dossier o� se trouve le fichier.
	///						C'est aussi le dossier qui a cr�� l'objet.
	/// \param inFSSpec		sp�cification du dossier.
	///
	TDCLMacOS7File(
						TDCLMacFiles* inFilesIntf,
						TDCLFSItemRef inFolder,
						const FSSpec* inFSSpec );

	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLMacOS7File( const TDCLMacOS7File& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLMacOS7File& operator = ( const TDCLMacOS7File& inCopy );

	///
	/// Cr�e le nom du fichier.
	///
	/// \return le nom du fichier en UTF-16 (cette cha�ne est allou�e avec
	///			malloc).
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual KUInt16*	MakeName( void ) const;

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

	/// \name Variables
		
	FSSpec		mFileFSSpec;	///< Sp�cification du fichier sur le disque.
	short		mRefNum;		///< R�f�rence sur le fichier ouvert.
};

#endif
		// __TDCLMACOS7FILE__

// ======================================================================= //
// In a five year period we can get one superb programming language.  Only //
// we can't control when the five year period will begin.                  //
// ======================================================================= //