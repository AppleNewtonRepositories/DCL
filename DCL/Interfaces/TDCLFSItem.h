// ==============================
// Fichier:			TDCLFSItem.h
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
// The Original Code is TDCLFSItem.h.
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
// $Id: TDCLFSItem.h,v 1.3 2004/11/24 14:08:59 paul Exp $
// ===========

#ifndef __TDCLFSITEM__
#define __TDCLFSITEM__

#include <DCL/Headers/DCLDefinitions.h>
#include <K/Misc/TRefCounter.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>
#include <DCL/Interfaces/TDCLFSItemRef.h>
#include <DCL/Interfaces/IDCLFiles.h>

// Pr�-d�clarations.
class TDCLFolder;
class IDCLFiles;

///
/// Classe pour un �l�ment sur un syst�me de fichiers.
///
/// Pour le moment, les seuls �l�ments sont des fichiers ou des dossiers. Mais
/// ceci est susceptible de changer.
///
/// Le butinage dans le syst�me de fichier se fait comme suit:
/// - il existe un �l�ment racine, le plus souvent virtuel, qui n'a pas de dossier parent.
/// - seuls les �l�ments que le Newton cherche � voir sont cr��s.
/// - les �l�ments disposent tous d'un compteur de r�f�rence pour un nombre minimum
///   d'occurrences en m�moire.
/// - les fichiers ne sont a priori r�f�renc�s qu'une seule fois (on peut toutefois imaginer
///   que les dossiers gardent en cache une liste des fichiers).
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLFSItem
	:
		private TRefCounter
{
	/// La classe qui s'occupe des r�f�rences est une amie.
	friend class TDCLFSItemRef;

public:
	///
	/// Diff�rents types d'�l�ments.
	/// La classe de l'�l�ment doit concorder avec le type.
	///
	enum EFSItemClass {
		kFile,			///< l'�l�ment est un TDCLFile
		kFolder			///< l'�l�ment est un TDCLFolder
	};
	
	///
	/// Destructeur.
	/// D�cr�mente le compteur de r�f�rence du dossier parent
	/// (et supprime ce dossier si n�cessaire)
	///
	virtual ~TDCLFSItem( void );

	///
	/// Accesseur sur la classe.
	///
	/// \return la classe de l'�l�ment.
	///
	inline	EFSItemClass	GetClass( void )
		{
			return mClass;
		}

	///
	/// R�cup�re le nom de l'�l�ment.
	///
	/// \return le nom de l'�l�ment, en UTF-16 (cette cha�ne appartient � l'objet
	///			TDCLFSItem).
	///
	const KUInt16*		GetName( void );

	///
	/// R�cup�re le chemin de l'�l�ment. Cette m�thode est r�cursive (on appelle
	/// la m�thode du dossier parent).
	/// Cette m�thode appelle la m�thode ToFrame.
	///
	/// \return le chemin de l'objet pour le butinage.
	///
	virtual TDCLNSRef	GetPath( void );

	///
	/// R�cup�re le dossier parent de l'�l�ment.
	/// Ce dossier peut �tre \c nil si l'�l�ment est l'�l�ment racine.
	/// Ce dossier est cr�� si n�cessaire et appartient � l'objet FSItem.
	/// Note: cette m�thode ne doit �tre d�riv�e que dans la classe TDCLRootFolder.
	///
	/// \return un objet repr�sentant le dossier parent ou \c nil.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual TDCLFSItemRef	GetParentFolder( void );

	///
	/// R�cup�re la description de l'�l�ment sous forme de structure.
	/// Cette description est utilis�e pour:
	/// - le chemin
	/// - la liste des �l�ments d'un dossier
	///
	/// \return la description de l'objet pour le butinage.
	///
	virtual TDCLNSRef	ToFrame( void ) = 0;

protected:
	///
	/// Change le nom de l'�l�ment en interne.
	/// Cette m�thode ne doit �tre appel�e que si le nom (mName) vaut nil.
	/// Il ne s'agit pas de renommer le fichier.
	///
	/// \param inName	le nom de l'�l�ment, en UTF-16 (cette cha�ne appartient
	///					ensuite � l'objet TDCLFSItem et sera lib�r�e avec free).
	/// \throw TDCLException si le nom existe d�j�.
	///
	void				SetName( KUInt16* inName );

	///
	/// Constructeur � partir du type d'�l�ment et d'un dossier parent (optionel)
	/// La r�f�rence du dossier parent est incr�ment�e.
	///
	/// \param inFilesIntf		interface sur les fichiers.
	/// \param inItemClass		classe de l'�l�ment.
	/// \param inParentFolder	dossier parent (\c nil signifie que MakeParentFolder sera
	///							appel� plus tard).
	///
	TDCLFSItem(
			IDCLFiles* inFilesIntf,
			EFSItemClass inItemClass,
			TDCLFSItemRef inParentFolder );
	
	///
	/// Accesseur sur l'interface pour les fichiers.
	///
	/// \return l'interface pour les fichiers.
	///
	inline IDCLFiles* GetFilesIntf( void ) const
		{
			return mFilesIntf;
		}

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLFSItem( const TDCLFSItem& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLFSItem& operator = ( const TDCLFSItem& inCopy );

	///
	/// Construit l'objet TDCLFolder parent. Cette m�thode n'est appel�e
	/// que si n�cessaire.
	///
	/// \return un objet repr�sentant le dossier parent ou \c nil.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual TDCLFSItemRef	MakeParentFolder( void ) const = 0;

	///
	/// Construit le nom de l'objet. C'est une cha�ne unicode UTF-16 qui est allou�e
	/// avec malloc. Cette m�thode n'est appel�e que si n�cessaire (au plus une fois).
	///
	/// \return le nom allou� avec malloc.
	/// \throw TDCLException si un probl�me est survenu.
	///
	virtual KUInt16*		MakeName( void ) const = 0;

	/// \name Variables
	IDCLFiles*		mFilesIntf;		///< Interface pour les fichiers.
	EFSItemClass	mClass;			///< Classe de l'�l�ment.
	TDCLFSItemRef	mParentFolder;	///< Parent de l'�l�ment (\c nil tant qu'il n'est
									///< pas cr��)
	KUInt16*		mName;			///< Nom de l'�l�ment (\c nil tant qu'il n'est
									///< pas cr��)
};

#endif
		// __TDCLFSITEM__

// ==================================================================== //
// If the code and the comments disagree, then both are probably wrong. //
//                 -- Norm Schryer                                      //
// ==================================================================== //
