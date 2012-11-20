// ==============================
// Fichier:			TDCLNSFrame.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			06/08/2002
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
// The Original Code is TDCLNSFrame.h.
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
// $Id: TDCLNSFrame.h,v 1.9 2004/11/24 14:09:07 paul Exp $
// ===========

#ifndef __TDCLNSFRAME__
#define __TDCLNSFRAME__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Objects/TDCLNSObject.h>

// DCL
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>
#include <DCL/NS_Objects/Objects/IStreamable.h>
#include <DCL/NS_Objects/Objects/TDCLNSSymbol.h>
#include <DCL/Exceptions/TDCLException.h>

class TDCLNSOFDecoder;
class TDCLXMLEncoder;
class TDCLNSOFEncoder;
class TDCLTextEncoder;
class TDCLPkgEncoder;

///
/// Classe pour une Frame. Une Frame est un dictionnaire d'objets NewtonScript,
/// les cl�s sont des symboles.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.9 $
///
/// \test	UTestNS::GetWalterSmith
/// \test	UTestNS::TestFrameKeysSort
///
class TDCLNSFrame
	:
		public TDCLNSObject
{
public:
	///
	/// Constructeur par d�faut.
	///
	TDCLNSFrame( void );

	///
	/// Constructeur par copie.
	/// Equivalent � Clone.
	/// Duplique les cl�s et les valeurs (les r�f�rences seront incr�ment�es)
	///
	/// \param inCopy	objet � copier.
	///
	explicit TDCLNSFrame( const TDCLNSFrame& inCopy );

	///
	/// Destructeur.
	///
	virtual ~TDCLNSFrame( void );

	///
	/// Op�rateur d'assignation.
	///
	/// \param inCopy		objet � copier
	///
	TDCLNSFrame& operator = ( const TDCLNSFrame& inCopy );

	///
	/// D�termine si cet objet est une structure.
	///
	/// \return \c true
	///
	virtual Boolean 	IsFrame( void ) const;

	///
	/// D�termine si cet objet est une fonction.
	///
	/// \return \c mIsFunction
	///
	virtual Boolean 	IsFunction( void ) const;

	///
	/// D�termine si une cl� existe dans le dictionnaire.
	///
	/// \param inSymbol	cl� � tester.
	/// \return \c true si la cl� existe, \c false sinon.
	///
	Boolean				HasSlot( const TDCLNSSymbol& inSymbol ) const;

	///
	/// D�termine si une cl� existe dans le dictionnaire.
	///
	/// \param inSymbol	cl� � tester, sous forme de cha�ne ISO-8859-1.
	/// \return \c true si la cl� existe, \c false sinon.
	///
	inline Boolean		HasSlot( const char* inSymbol ) const
		{
			return HasSlot( TDCLNSSymbol( inSymbol ) );
		}

	///
	/// Supprime une cl� du dictionnaire.
	///
	/// \param inSymbol	cl� � supprimer.
	/// \return \c true si la cl� existait, \c false sinon.
	///
	Boolean				RemoveSlot( const TDCLNSSymbol& inSymbol );

	///
	/// Supprime une cl� du dictionnaire.
	///
	/// \param inSymbol	cl� � supprimer, sous forme de cha�ne ISO-8859-1.
	/// \return \c true si la cl� existait, \c false sinon.
	///
	inline Boolean		RemoveSlot( const char* inSymbol )
		{
			return RemoveSlot( TDCLNSSymbol( inSymbol ) );
		}

	///
	/// Accesseur sur un �l�ment.
	///
	/// \param inSymbol	cl� pour acc�der � l'�l�ment.
	/// \return la r�f�rence de l'objet r�f�renc� par la cl� ou
	///			NIL s'il n'y en a pas.
	///
	TDCLNSRef			Get( const TDCLNSSymbol& inSymbol ) const;

	///
	/// Accesseur sur un �l�ment.
	///
	/// \param inSymbol		cl� pour acc�der � l'�l�ment, sous forme de cha�ne
	///						ISO 8859-1
	/// \return la r�f�rence de l'objet r�f�renc� par la cl� ou
	///			NIL s'il n'y en a pas.
	///
	inline TDCLNSRef	Get( const char* inSymbol ) const
		{
			return Get( TDCLNSSymbol( inSymbol ) );
		}		

	///
	/// Accesseur sur une cl� � partir d'un indice.
	/// Utilis� pour it�rer sur les �l�ments de la structure.
	///
	/// \param inIndex	indice de la cl� � r�cup�rer.
	/// \return la r�f�rence de la inIndex-i�me cl�
	/// \throws TDCLException si la structure est plus petite que �a
	///
	TDCLNSRef			GetKey( KUInt32 inIndex ) const;

	///
	/// Accesseur sur un �l�ment � partir d'un indice.
	/// Utilis� pour it�rer sur les �l�ments de la structure.
	///
	/// \param inIndex	indice de l'�l�ment � r�cup�rer.
	/// \return la r�f�rence du inIndex-i�me objet
	/// \throws TDCLException si la structure est plus petite que �a
	///
	TDCLNSRef			GetValue( KUInt32 inIndex ) const;

	///
	/// S�lecteur sur un �l�ment.
	///
	/// \param inSymbol		cl� pour acc�der � l'�l�ment.
	/// \param inNewValue	nouvelle valeur pour cette cl�.
	///
	void				Set(
							const TDCLNSRef& inSymbol,
							const TDCLNSRef& inNewValue );

	///
	/// S�lecteur sur un �l�ment.
	///
	/// \param inSymbol		cl� pour acc�der � l'�l�ment.
	/// \param inNewValue	nouvelle valeur pour cette cl�.
	///
	inline void			Set(
							const TDCLNSSymbol& inSymbol,
							const TDCLNSRef& inNewValue )
		{
			Set( TDCLNSRef(inSymbol.Clone()), inNewValue );
		}

	///
	/// S�lecteur sur un �l�ment.
	///
	/// \param inSymbol		cl� pour acc�der � l'�l�ment, sous forme de cha�ne
	///						ISO 8859-1
	/// \param inNewValue	nouvelle valeur pour cette cl�.
	///
	inline void		Set( const char* inSymbol, const TDCLNSRef& inNewValue )
		{
			Set( TDCLNSRef::MakeSymbol( inSymbol ), inNewValue );
		}

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
	/// \return un nouvel objet � partir de ce flux
	///
	static	TDCLNSFrame*	FromNSOF( TDCLNSOFDecoder* inDecoder );
		
	///
	/// Cr�e un objet rectangle � partir d'un flux NSOF.
	/// �a n'est pas clair dans Newton Formats, mais les 4 coordonn�es
	/// doivent �tre entre 0 et 255 (ce sont des octets non sign�s).
	///
	/// \param inDecoder	d�codeur NSOF associ� � un flux donn�.
	/// \return un nouvel objet � partir de ce flux
	///
	static	TDCLNSFrame*	FromNSOFAsRect( TDCLNSOFDecoder* inDecoder );
		
	///
	/// Cr�e un objet � partir d'un paquet.
	///
	/// \param inDecoder	d�codeur Pkg associ� � un flux donn�.
	/// \return un nouvel objet � partir de ce flux
	///
	static	TDCLNSFrame*	FromPkg( TDCLPkgDecoder* inDecoder );

	///
	/// D�termine la classe de cette structure.
	/// Ce n'est pas forc�ment un symbole.
	///
	/// \return une r�f�rence vers la classe de cette structure.
	///
	virtual TDCLNSRef ClassOf( void ) const;

	///
	/// D�termine la classe primaire de cette structure.
	/// Il s'agit forc�ment d'un symbole.
	///
	/// \return une r�f�rence vers la classe primaire de cette structure.
	///
	virtual TDCLNSRef PrimClassOf( void ) const;

	///
	/// Change la classe de cette structure.
	/// Ce n'est pas forc�ment un symbole.
	///
	/// \param	inClass un objet qui sert de nouvelle classe � cette structure.
	/// \throws TDCLNSException si une erreur est survenue.
	///
	virtual void SetClass( const TDCLNSRef& inClass );

	///
	/// Accesseur sur la taille de la structure.
	///
	/// \return la taille de la structure (le nombre de paire)
	///
	inline KUInt32	GetLength( void ) const
		{
			return mLength;
		}

protected:
	///
	/// S�lecteur sur mKeysAreSorted
	///
	/// \param inKeysAreSorted	si les cl�s sont tri�es.
	///
	inline void		SetKeysAreSorted( Boolean inKeysAreSorted )
		{
			mKeysAreSorted = inKeysAreSorted;
		}

	///
	/// S�lecteur sur mIsFunction
	///
	/// \param inIsFunction		si la structure est une fonction.
	///
	inline void		SetIsFunction( Boolean inIsFunction )
		{
			mIsFunction = inIsFunction;
		}

private:
	///
	/// Constantes pour cette classe.
	///
	enum {
		kListChunkSize	= 10,	///< Incr�ment des listes lorsqu'elles sont pleines.
		kSortThreshold	= 20	///< Seuil � partir duquel il vaut mieux trier la liste.
	};

	///
	/// Constructeur � partir d'une capacit�.
	///
	/// \param inCapacity	nombre de paire � allouer.
	///
	TDCLNSFrame( KUInt32 inCapacity );

	///
	/// D�termine l'index d'une cl�, si elle est pr�sente (ou l'index ou ins�rer
	/// la cl� si elle n'est pas dans la liste).
	///
	/// \param inSymbol		cl� � chercher
	/// \param outIndex		index de la cl� ou index o� mettre la cl� si elle
	///						n'est pas pr�sente (taille de la structure si elle n'est
	///						pas tri�e).
	/// \return \c true si la cl� a �t� trouv�e, \c false sinon.
	///
	Boolean		GetKeyIndex( const TDCLNSSymbol& inSymbol, KUInt32* outIndex ) const;

	/// \name Interface IStreamable
	// @{
	///
	/// Cr�e une repr�sentation XML de la structure.
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
	/// Cr�e une repr�sentation NSOF de la structure.
	/// Comprend le type et les donn�es.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	virtual void ToNSOF( TDCLNSOFEncoder* inEncoder ) const;

	///
	/// Cr�e une repr�sentation sous forme de texte de la structure.
	/// Comprend les accolades et les donn�es.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	virtual void ToText( TDCLTextEncoder* inEncoder ) const;

	///
	/// Cr�e une repr�sentation de la structure pour mettre dans un
	/// paquet.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder	encodeur pour le paquet.
	/// \param ioOffset		en entr�e et en sortie, d�calage par rapport
	///						au paquet.
	///
	virtual void ToPkg( TDCLPkgEncoder* inEncoder, KUInt32* ioOffset ) const;
	// @}

	// M�me format que sur le Newton, sauf pour le coup des cartes.
	// taille, cl�s, valeurs.
	KUInt32					mLength;		///< Nombre d'�l�ments.
	KUInt32					mCapacity;		///< Capacit� des listes.
	TDCLNSRef*				mKeys;			///< Liste des cl�s
	TDCLNSRef*				mValues;		///< Liste des valeurs.
	Boolean					mKeysAreSorted;	///< Indique que les cl�s sont tri�es.
	Boolean					mIsFunction;	///< Si la structure est une fonction.
};

#endif
		// __TDCLNSFRAME__

// =========================================================================== //
// Some programming languages manage to absorb change, but withstand progress. //
//                 -- Epigrams in Programming, ACM SIGPLAN Sept. 1982          //
// =========================================================================== //
