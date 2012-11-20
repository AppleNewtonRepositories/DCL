// ==============================
// Fichier:			TDCLNSArray.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			07/08/2002
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
// The Original Code is TDCLNSArray.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2002-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLNSArray.h,v 1.7 2004/11/24 14:09:07 paul Exp $
// ===========

#ifndef __TDCLNSARRAY__
#define __TDCLNSARRAY__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Objects/TDCLNSObject.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>
#include <DCL/Exceptions/TDCLNSException.h>
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>

class TDCLStream;
class TDCLNSEncoder;
class TDCLNSSymbol;
class TDCLNSOFDecoder;
class TDCLPkgDecoder;

///
/// Classe pour un tableau NewtonScript.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.7 $
///
/// \test	aucun test d�fini.
///
class TDCLNSArray
					:	public TDCLNSObject
{
public:
	///
	/// Constructeur par d�faut.
	/// Cr�e un tableau vide.
	///
	TDCLNSArray( void );

	///
	/// Constructeur par copie.
	/// Duplique les �l�ments (les r�f�rences seront incr�ment�es)
	///
	/// \param inCopy	objet � copier.
	///
	explicit TDCLNSArray( const TDCLNSArray& inCopy );

	///
	/// Constructeur par � partir d'une taille et d'un �l�ment.
	/// Cr�e un tableau rempli de cet �l�ment.
	///
	/// \param inSize	taille du tableau
	/// \param inRef	r�f�rence sur l'�l�ment � mettre dans le tableau.
	///
	TDCLNSArray( KUInt32 inSize, const TDCLNSRef& inRef = TDCLNSRef::kNILREF );

	///
	/// Destructeur.
	///
	virtual ~TDCLNSArray( void );

	///
	/// Op�rateur d'assignation.
	///
	/// \param inCopy		objet � copier
	///
	TDCLNSArray& operator = ( const TDCLNSArray& inCopy );

	///
	/// D�termine si cet objet est un tableau.
	///
	/// \return \c false
	///
	virtual Boolean IsArray( void ) const;

	///
	/// Accesseur sur un �l�ment du tableau
	///
	/// \param inIndex	index de l'�l�ment � r�cup�rer.
	/// \throws TDCLNSException si l'index est en dehors du domaine de ce tableau.
	///
	TDCLNSRef	Get( KUInt32 inIndex ) const;

	///
	/// S�lecteur sur un �l�ment du tableau
	///
	/// \param inIndex	index de l'�l�ment � changer.
	/// \param inItem	�l�ment � mettre dans le tableau.
	/// \throws TDCLNSException si l'index est en dehors du domaine de ce tableau.
	///
	void		Set( KUInt32 inIndex, const TDCLNSRef& inItem );

	///
	/// Ajout d'un �l�ment dans le tableau (� la fin).
	///
	/// \param inItem	�l�ment � ajouter au tableau.
	///
	void		Add( const TDCLNSRef& inItem );

	///
	/// Suppression d'un �l�ment dans le tableau (� la fin).
	/// Le tableau est r�tr�ci.
	///
	/// \param inIndex	indice de l'�l�ment � supprimer du tableau.
	///
	void		RemoveSlot( KUInt32 inIndex );

	///
	/// Ajout d'un �l�ment au milieu du tableau.
	/// Le tableau est agrandi.
	///
	/// \param inIndex	indice de l'�l�ment une fois ins�r� dans le tableau.
	///					0 ins�rera l'�l�ment au d�but du tableau. mLength
	///					l'ins�rera � la fin.
	/// \param inItem	�l�ment � ins�rer.
	///
	void		Insert( KUInt32 inIndex, const TDCLNSRef& inItem );

	///
	/// Cr�e une copie de surface de la structure.
	/// Appelle le constructeur par copie.
	///
	/// \return une copie de surface de this.
	///
	virtual TDCLNSObject*	Clone( void ) const;

	///
	/// Cr�e un objet � partir d'un flux NSOF
	///
	/// \param inDecoder	d�codeur NSOF associ� � un flux donn�.
	/// \param isPlain		\c true si la classe du tableau est 'array
	///						et qu'il ne faut pas la lire, \c false sinon
	/// \return un nouvel objet � partir de ce flux
	///
	static	TDCLNSArray*	FromNSOF(
								TDCLNSOFDecoder* inDecoder,
								Boolean isPlain );

	///
	/// Cr�e un objet � partir d'un paquet.
	///
	/// \param inDecoder	d�codeur Pkg associ� � un flux donn�.
	/// \return un nouvel objet � partir de ce flux
	///
	static	TDCLNSArray*	FromPkg( TDCLPkgDecoder* inDecoder );

	///
	/// D�termine la classe de ce tableau.
	/// Ce n'est pas forc�ment un symbole.
	///
	/// \return une r�f�rence vers la classe de ce tableau.
	///
	virtual TDCLNSRef ClassOf( void ) const;

	///
	/// D�termine la classe primaire de ce tableau.
	/// Il s'agit forc�ment d'un symbole.
	///
	/// \return une r�f�rence vers la classe primaire de ce tableau.
	///
	virtual TDCLNSRef PrimClassOf( void ) const;

	///
	/// Change la classe de ce tableau.
	/// Ce n'est pas forc�ment un symbole.
	///
	/// \param	inClass un objet qui sert de nouvelle classe � ce tableau.
	/// \throws TDCLNSException si une erreur est survenue.
	///
	virtual void SetClass( const TDCLNSRef& inClass );

	///
	/// Accesseur sur la taille du tableau.
	///
	/// \return la taille du tableau (le nombre d'�l�ments dans le tableau)
	///
	inline KUInt32	GetLength( void ) const
		{
			return mSize;
		}

private:
	/// \name Interface IStreamable
	
	///
	/// Cr�e une repr�sentation XML du tableau.
	/// Comprend la balise de d�but, les donn�es et la balise de fin.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	/// \param inObjectID		ID de l'objet dans ce flux.
	///
	virtual void ToXML(
				TDCLXMLEncoder* inEncoder,
				KUInt32			inObjectID ) const;

	///
	/// Cr�e une repr�sentation NSOF du tableau.
	/// Comprend le type et les donn�es.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	virtual void ToNSOF(
				TDCLNSOFEncoder* inEncoder ) const;

	///
	/// Cr�e une repr�sentation sous forme de texte du tableau.
	/// Comprend les crochets et les donn�es.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	virtual void ToText(
				TDCLTextEncoder* inEncoder ) const;
	
	///
	/// Cr�e une repr�sentation du tableau pour mettre dans un
	/// paquet.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder	encodeur pour le paquet.
	/// \param ioOffset		en entr�e et en sortie, d�calage par rapport
	///						au paquet.
	///
	virtual void ToPkg( TDCLPkgEncoder* inEncoder, KUInt32* ioOffset ) const;

	/// \name Variables Priv�es
	
	TDCLNSRef			mClass;		///< Classe du tableau
	KUInt32				mSize;		///< Nombre d'�l�ments dans le tableau
	TDCLNSRef*			mItems;		///< El�ments du tableau
};

#endif
		// __TDCLNSARRAY__

// ========================================================================= //
// Don't get suckered in by the comments -- they can be terribly misleading. //
// Debug only code.                                                          //
//                 -- Dave Storer                                            //
// ========================================================================= //
