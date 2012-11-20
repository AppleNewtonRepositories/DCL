// ==============================
// Fichier:			TDCLFile.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			04/02/2003
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
// The Original Code is TDCLFile.h.
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
// $Id: TDCLFile.h,v 1.9 2004/11/24 14:08:59 paul Exp $
// ===========

#ifndef __TDCLFILE__
#define __TDCLFILE__

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Exceptions/IO_Exceptions/TDCLIOException.h>
#include <DCL/Exceptions/IO_Exceptions/TDCLPositionException.h>
#include <DCL/Interfaces/TDCLFSItem.h>
#include <DCL/Streams/TDCLRandomAccessStream.h>

///
/// Classe pour les fichiers.
///
/// Cette classe est purement virtuelle. Elle doit �tre d�riv�e pour chaque
/// plateforme afin de stocker les informations concernant les fichiers.
/// C'est une bonne id�e d'appeler la m�thode \c Close dans le destructeur.
///
/// Les fichiers peuvent �tre de vrais fichiers ou des ressources, en fait
/// n'importe quoi qui ressemble un peu � un fichier.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.9 $
///
/// \test	aucun test d�fini.
///
class TDCLFile
	:
		public TDCLFSItem,
		public TDCLRandomAccessStream
{		
public:
	///
	/// Ouvre le fichier.
	///
	/// \param inReadOnly	si le fichier doit �tre ouvert en lecture seule
	/// \throws TDCLIOException si l'ouverture a �chou�.
	///
	virtual void		Open( Boolean inReadOnly ) = 0;	

	///
	/// Cr�e le fichier.
	///
	/// \throws TDCLIOException si la cr�ation a �chou�.
	///
	virtual void		Create( void ) = 0;	

	///
	/// Supprime le fichier.
	///
	/// \throws TDCLIOException si la suppression a �chou�.
	///
	virtual void		Delete( void ) = 0;	

	///
	/// Determine si le fichier est ouvert.
	///
	/// \return \c true si le fichier est ouvert, \c false sinon.
	///
	virtual Boolean		IsOpen( void ) const = 0;

	///
	/// Determine si le fichier est ouvert en lecture seule.
	///
	/// \return \c true si le fichier est ouvert en lecture seule,
	///			\c false sinon. Le r�sultat est ind�termin� si le fichier
	///			n'est pas ouvert.
	///
	virtual Boolean		IsReadOnly( void ) const = 0;
	
	///
	/// Retourne la longueur (logique) du fichier.
	///
	/// \return la taille du fichier, en octets.
	///
	virtual KUInt64		GetLength( void ) = 0;
	
	///
	/// R�cup�re l'octet suivant sans avancer le curseur.
	/// Par d�faut, lit le fichier pour un octet et retourne en arri�re.
	///
	/// \return l'octet lu.
	/// \throws TDCLIOException	si un probl�me est survenu (y compris si la
	///							fin du fichier est rencontr�e)
	///
	virtual	KUInt8		PeekByte( void );

	///
	/// Ferme le fichier.
	/// Vous souhaitez probablement appeler la m�thode close dans votre
	/// destructeur.
	/// Ne fait rien si le fichier n'�tait pas ouvert.
	///
	virtual void		Close( void ) = 0;

	///
	/// R�cup�re la description de l'�l�ment sous forme de structure.
	/// Retourne une structure avec type: 'file.
	///
	/// \return la description de l'objet pour le butinage.
	///
	virtual TDCLNSRef	ToFrame( void );
	
	///
	/// R�cup�re le type du fichier sous forme de cha�ne NewtonScript.
	/// C'est ce qui est retourn� au Newton pour affichage dans
	/// le butineur.
	///
	/// \return une cha�ne NewtonScript avec le type du fichier.
	///
	virtual TDCLNSRef	GetKind( void ) const = 0;
	
	///
	/// R�cup�re la date de cr�ation au format des dates Newton
	/// (minutes depuis 1904).
	///
	/// \return la date de cr�ation du fichier.
	///
	virtual KUInt32		GetCreationDate( void ) const = 0;

	///
	/// R�cup�re la date de modification au format des dates Newton
	/// (minutes depuis 1904).
	///
	/// \return la date de modification du fichier.
	///
	virtual KUInt32		GetModificationDate( void ) const = 0;

	///
	/// R�cup�re le chemin du fichier dans une forme lisible par
	/// l'utilisateur. Ce chemin n'a pas d'autre fonction que
	/// d'�tre affich� sur le Newton.
	///
	/// \return le chemin du fichier dans une cha�ne NewtonScript.
	///
	virtual TDCLNSRef	GetStringPath( void ) const = 0;

	///
	/// R�cup�re l'ic�ne du fichier sous forme de binaire noir et blanc
	/// 32x32. Si le r�sultat est \c nil, l'ic�ne n'est pas envoy�e au
	/// Newton.
	/// Par d�faut renvoie \c nil.
	///
	/// \return l'ic�ne du fichier ou \c nil.
	///
	virtual TDCLNSRef	GetIcon( void ) const;

	///
	/// D�termine si le fichier est un paquet.
	/// Appelle TDCLPackage::IsPackage, mais retourne \c false en cas
	/// d'exception.
	///
	/// \return \c true si le fichier est un paquet, \c false sinon.
	///
	Boolean				IsPackage( void );

protected:
	///
	/// Constructeur prot�g� � partir d'un dossier.
	/// Ce constructeur doit (g�n�ralement?) �tre appel� par une
	/// extension de la classe avec une extension de la classe
	/// TDCLFolder compatible.
	///
	/// \param inFilesIntf		interface pour les fichiers.
	/// \param inParentFolder	dossier o� se trouve le fichier.
	///					c'est aussi le dossier qui a cr�� l'objet.
	///					(\c nil signifie que MakeParentFolder sera
	///					appel� plus tard).
	///
	TDCLFile( IDCLFiles* inFilesIntf, TDCLFSItemRef inParentFolder );

	///
	/// Construit l'objet TDCLFolder parent. Cette m�thode n'est
	/// normalement jamais appel�e puisque l'objet parent a �t� fourni
	/// comme param�tre au constructeur ci-dessus.
	///
	/// \throws TDCLNotImplementedException
	///
	virtual TDCLFSItemRef	MakeParentFolder( void ) const;
};

#endif
		// __TDCLFILE__

// ======================================================================== //
// Congratulations!  You are the one-millionth user to log into our system. //
// If there's anything special we can do for you, anything at all, don't    //
// hesitate to ask!                                                         //
// ======================================================================== //
