// ==============================
// Fichier:			TDCLNSRef.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			30/06/2002
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
// The Original Code is TDCLNSRef.h.
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
// $Id: TDCLNSRef.h,v 1.11 2004/11/24 14:09:07 paul Exp $
// ===========

#ifndef __TDCLNSREF__
#define __TDCLNSREF__

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>
#include <DCL/Exceptions/TDCLNSException.h>
#include <DCL/NS_Objects/Objects/TDCLNSObject.h>
#include <DCL/NS_Objects/Objects/KDCLSYM.h>

class TDCLNSArray;
class TDCLNSBinary;
class TDCLNSEncoder;
class TDCLNSFrame;
class TDCLNSString;
class TDCLNSSymbol;
class TDCLStream;

///
/// Classe pour une r�f�rence sur un objet NewtonScript.
/// Une r�f�rence est un imm�diat ou un pointeur.
/// Cette classe ne contient volontairement qu'un KUIntPtr.
/// Si le type ne correspond pas � une op�ration donn�e,
/// on lance une exception.
///
/// Remarques g�n�rales sur l'utilisation des objets et des r�f�rences.
///
/// NewtonScript poss�de un ramasse-miettes. Cette classe vise � remplacer le
/// ramasse-miettes tout en �tant le plus facile d'utilisation possible. Il
/// faut respecter certaines r�gles pour � la fois �viter les fuites de m�moire
/// et les acc�s � des objets d�j� supprim�s et pour �viter que le code ne soit
/// trop lourd.
///
/// Aucun objet (pointeur) n'est copi� implicitement. Pour copier un objet,
/// il faut utiliser les m�thodes Clone, DeepClone et TotalClone qui ont la
/// m�me s�mantique que sur le Newton.
///
/// - 1. Valeur de retour des fonctions
///
/// Une r�f�rence est normalement ou le plus souvent une r�f�rence sur un
/// objet qui n'est pas sur la pile. Les fonctions MakeArray, MakeFrame, etc.
/// cr�ent de tels pointeurs, et le constructeur TDCLNSRef( TDCLNSObject* )
/// prend un pointeur.
///
/// C'est ce type de r�f�rence qu'il faut retourner. Une fonction ne doit
/// jamais retourner un objet directement (comme TDCLFrame, TDCLString, etc.).
/// � la rigueur, une fonction peut retourner un pointeur sur un objet,
/// l'appelant devant savoir qu'en faire.
///
/// - 2. Objets sur la pile
///
/// Pour des raisons d'efficacit�, on peut vouloir cr�er des objets
/// NewtonScript comme des tableaux ou des structures sur la pile. Certaines
/// fonctions prennent directement des r�f�rences vers des objets et donc ceci
/// ne pose aucun probl�me pour ces fonctions.
///
/// D'autres fonctions en revanche, notamment celles qui ins�rent des
/// r�f�rences dans des objets, prennent des r�f�rences comme param�tre. Il y a
/// une bonne raison pour cela, c'est qu'il ne faut (g�n�ralement) pas leur
/// donner une r�f�rence sur un objet cr�� sur la pile.
///
/// C'est quand m�me possible en cr�ant pour les appeler une r�f�rence sur ces
/// objets qui sont dans la pile. Ceci est possible gr�ce au constructeur
/// TDCLNSRef( TDCLNSObject& ). Ce constructeur doit �tre appel� partout o�
/// s'assure que l'objet r�f�rence dure plus longtemps que son utilisation.
///
/// N�anmoins, comme l'objet r�f�renc� est dans la pile, la r�f�rence ne doit
/// pas lui survivre. (remarque: si DCLDebugOn est d�fini, une exception sera
/// lanc�e si cette r�f�rence survit � l'objet).
///
/// Voici un exemple de code foireux:
/// <code>
/// TDCLNSRef TBar::Foo( void )
/// {
/// 	TDCLFrame myFrame;
///		myFrame.Set("bar", TDCLNSRef::MakeInt(3));
///		return TDCLNSRef(myFrame);
/// } // <-- plantage
/// </code>
/// (c'est pourquoi le mot cl� explicit est utilis�, afin d'emp�cher
/// <code>return myFrame;</code> qui appellerait implicitement le constructeur)
///
/// Voici un autre exemple, plus subtil:
/// <code>
/// TDCLNSRef TBar::Foo( TDCLNSRef& inFrame )
/// {
/// 	TDCLArray myArray;
///		inFrame.ToFrame().Set("bar", TDCLNSRef(myArray));
/// } // <-- plantage
/// </code>
/// (remarque: <code>inFrame.ToFrame().Set("bar", myArray);</code> ne compile
/// pas non plus mais appellerait aussi implicitement le constructeur)
///
/// Dans ces deux exemples, il faut utiliser des r�f�rences sur des objets
/// cr��s avec <code>new</code>.
/// Par exemple:
/// <code>
/// TDCLNSRef TBar::Foo( void )
/// {
///		TDCLNSRef myFrameRef = TDCLNSRef::MakeFrame();
/// 	TDCLFrame& myFrame = myFrameRef.ToFrame();
///		myFrame.Set("bar", TDCLNSRef::MakeInt(3));
///		return myFrameRef;
/// }
/// </code>
///
/// On peut aussi cloner l'objet si le renvoi de l'objet n'est pas s�r.
/// Par exemple:
/// <code>
/// TDCLNSRef TBar::Foo( TDCLNSFrame& inFrame )
/// {
/// 	TDCLArray myArray;
///		if (Unsure())
///		{
///			inFrame.Set("bar", TDCLNSRef(myArray.Clone()));
///		}
/// }
/// </code>
///
/// Les objets sur la pile doivent �tre cr��s dans le bon ordre.
/// <code>
/// {
/// 	TDCLArray myArray;
/// 	TDCLFrame myFrame;
///		myArray.Add( TDCLNSRef( myFrame ) );
/// } // <-- plantage
/// </code>
///
/// - 3. Param�tres des fonctions
///
/// Si le param�tre d'une fonction est de type TDCLNSRef, le constructeur par
/// copie de TDCLNSRef est appel�. Ceci introduit quelques op�rations souvent,
/// si ce n'est toujours, inutiles.
/// Pour �viter ceci, il faut consid�rer deux autres types possibles pour les
/// param�tres:
/// 	- <code>const TDCLNSRef&</code> si la r�f�rence sera copi�e au besoin
///		  dans le corps d'une fonction (normalement tout le temps le cas)
///		- <code>TDCLNSObject&</code> (e.g. <code>TDCLNSFrame&</code>) si
///		  l'objet ne sera pas r�f�renc� en dehors du corps de la fonction et
///		  que son type est connu -- dans ce cas, la fonction devra parfois
///		  construire une r�f�rence avec TDCLNSRef( TDCLNSObject& ).
///
/// - 4. V�rification du type & conversions
///
/// Si vous avez besoin d'effectuer plusieurs op�ration sur cet objet, il
/// est plus sage de stocker la r�f�rence dans une variable locale. En effet,
/// l'op�rateur v�rifie le type, et donc ne pas stocker va consister � v�rifier
/// le type � chaque conversion.
/// Exemple:
/// <code>
///		TDCLNSFrame& theFrame = (TDCLNSFrame&) inFrameRef;
///		TDCLNSRef theResult = TDCLNSRef::kNILREF;
///		if (theFrame.HasSlot( (TDCLNSSymbol&) inSymbolRef ))
///		{
///			theFrame.Get( (TDCLNSSymbol&) inSymbolRef2 ))
///		}
///		return theResult;
/// </code>
///
/// peut �tre remplac� par:
///
/// <code>
///		TDCLNSFrame& theFrame = (TDCLNSFrame&) inFrameRef;
///		TDCLNSSymbol& theSymbol = (TDCLNSSymbol&) inSymbolRef;
///		TDCLNSRef theResult = TDCLNSRef::kNILREF;
///		if (theFrame.HasSlot( theSymbol ))
///		{
///			theFrame.Get( theSymbol ))
///		}
///		return theResult;
/// </code>
///
/// Remarques:
///		- <code>(TDCLNSFrame&) inFrameRef</code> est �quivalent � l'appel
///		  � ToFrame()
///		- <code>(TDCLNSSymbol&) inSymbolRef2</code> est �quivalent � juste
///		  inSymbolRef2 dans ce cas.
///
/// Enfin, le mot cl� C++ explicit est utilis� pour vous emp�cher de faire
/// l'erreur suivante:
/// <code>
///		TDCLNSFrame theFrame = inFrameRef.ToFrame();
/// </code>
///
/// Cette ligne *copie* la structure (enfin, elle ne compile pas, mais si elle
/// compilait, cela conduirait � une copie).
///
///
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.11 $
///
/// \test	aucun test d�fini.
///
class TDCLNSRef
{
	friend class TDCLNSEncoder;
	friend class TDCLNSOFEncoder;
	friend class TDCLTextEncoder;
	friend class TDCLXMLEncoder;
	friend class TDCLPkgEncoder;
	friend class TDCLNSDecoder;
	friend class TDCLNSOFDecoder;
	friend class TDCLTextDecoder;
	friend class TDCLXMLDecoder;

public:
	/// \name Constructeurs et destructeurs publics

	///
	/// Constructeur par d�faut.
	/// Initialise la r�f�rence � kNILRefValue
	///
	TDCLNSRef( void );

	///
	/// Destructeur.
	/// D�cr�mente la r�f�rence s'il s'agit d'un pointeur.
	///
	~TDCLNSRef( void );
	
	///
	/// Constructeur par copie.
	/// Incr�mente la r�f�rence s'il s'agit d'un pointeur.
	///
	/// \param inCopy		r�f�rence � copier.
	///
	TDCLNSRef( const TDCLNSRef& inCopy );

	///
	/// Constructeur � partir d'un objet sur la pile.
	/// Non seulement l'objet NS n'est pas copi�, mais en plus une exception
	/// sera lanc�e si la r�f�rence continue d'exister apr�s l'objet et si
	/// <code>DCLDebugOn</code> est d�finie.
	/// Attention, ceci peut ne pas �tre ce que vous souhaitez.
	///
	/// \param inObject		objet � r�f�rencer.
	///
	explicit TDCLNSRef( TDCLNSObject& inObject );

	///
	/// Constructeur � partir d'un objet.
	/// L'objet NS n'est pas copi�.
	/// Attention, ceci peut ne pas �tre ce que vous souhaitez.
	///
	/// \param inObject		objet � r�f�rencer.
	///
	TDCLNSRef( TDCLNSObject* inObject );

	///
	/// Op�rateur d'assignation.
	/// D�cr�mente la copie de l'ancienne r�f�rence s'il s'agit
	/// d'un pointeur et incr�mente la nouvelle r�f�rence si
	/// n�cessaire.
	///
	/// \param inCopy		r�f�rence � copier.
	///
	TDCLNSRef& operator = ( const TDCLNSRef& inCopy );

	///
	/// Op�rateur d'assignation.
	/// D�cr�mente la copie de l'ancienne r�f�rence s'il s'agit
	/// d'un pointeur et incr�mente la nouvelle r�f�rence.
	///
	/// \param inObject		objet � r�f�rencer.
	///
	TDCLNSRef& operator = ( TDCLNSObject& inObject );

	///
	/// Op�rateur d'�galit�.
	/// Ceci est l'�galit� de surface. Deux TDCLRef sont
	/// �gaux si leur valeurs (mRef) sont �gales.
	/// Cependant, si ce sont tous deux des symboles, ils
	/// sont compar�s. Ceci donne un op�rateur s�mantiquement
	/// �quivalent � = en NewtonScript.
	///
	/// \param inAlter		r�f�rence � comparer.
	///
	Boolean operator == ( const TDCLNSRef& inAlter ) const;

	///
	/// Op�rateur d'in�galit�.
	/// La n�gation du pr�c�dent.
	///
	/// \param inAlter		r�f�rence � comparer.
	///
	inline Boolean operator != ( const TDCLNSRef& inAlter ) const
		{
			return !(*this == inAlter);
		}

	/// \name Fonctions sur la r�f�rence

	///
	/// Cr�ateur � partir d'une r�f�rence.
	///
	/// \param inRef	r�f�rence.
	/// \return un nouvel objet TDCLNSRef avec cette r�f�rence.
	///
	static TDCLNSRef Ref( KUIntPtr inRef );

	///
	/// R�cup�re la valeur de la r�f�rence.
	///
	/// \return la valeur de la r�f�rence.
	///
	inline KUIntPtr RefOf( void ) const
		{
			return mRef;
		}

	/// \name Constantes

	///
	/// Constante pour NIL.
	///
	static const TDCLNSRef kNILREF;

	///
	/// Constante pour TRUE.
	///
	static const TDCLNSRef kTRUEREF;

	///
	/// Constante pour Ref(50), la classe des fonctions.
	///
	static const TDCLNSRef kNewFuncClass;

	/// \name Cr�ateurs

	///
	/// Cr�ateur � partir d'un entier.
	///
	/// \param inInt	entier (sign�).
	/// \return un nouvel objet TDCLNSRef repr�sentant cet entier.
	///	\throws	TDCLNSException si les deux bits de poids fort (30 & 29)
	///			ne sont pas nuls.
	///
	static TDCLNSRef MakeInt( KSInt32 inInt );

	///
	/// Cr�ateur � partir d'un caract�re.
	///
	/// \param inChar	caract�re (Unicode).
	/// \return un nouvel objet TDCLNSRef repr�sentant ce caract�re.
	///
	static TDCLNSRef MakeChar( KUInt16 inChar );

	///
	/// Cr�ateur � partir d'un caract�re.
	///
	/// \param inChar	caract�re (ISO-8859-1).
	/// \return un nouvel objet TDCLNSRef repr�sentant ce caract�re.
	///
	inline static TDCLNSRef MakeChar( unsigned char inChar )
		{
			return MakeChar( (KUInt16) inChar );
		}

	///
	/// Cr�ateur � partir d'un bool�en.
	///
	/// \param inBoolean	bool�en.
	/// \return un nouvel objet TDCLNSRef repr�sentant ce bool�en.
	///
	static TDCLNSRef MakeBoolean( Boolean inBoolean );

	///
	/// Cr�ateur pour un pointeur magique.
	///
	/// \param inValue	valeur du pointeur magique (indice et table)
	/// \return un nouvel objet TDCLNSRef repr�sentant ce pointeur magique.
	///	\throws	TDCLNSException si l'indice ou le num�ro de la table sont trop
	///			grands.
	///
	static TDCLNSRef MakeMagicPtr( KUInt32 inValue );

	///
	/// Cr�ateur pour un pointeur magique.
	///
	/// \param inTable	table pour le pointeur magique.
	/// \param inIndex	indice du pointeur magique.
	/// \return un nouvel objet TDCLNSRef repr�sentant ce pointeur magique.
	///	\throws	TDCLNSException si l'indice ou le num�ro de la table sont trop
	///			grands.
	///
	static TDCLNSRef MakeMagicPtr( KUInt32 inTable, KUInt32 inIndex );

	///
	/// Cr�ateur pour une structure vide.
	///
	/// \return un nouvel objet TDCLNSRef repr�sentant une nouvelle structure.
	///
	static TDCLNSRef MakeFrame( void );

	///
	/// Cr�ateur pour une fonction vide.
	///
	/// \return un nouvel objet TDCLNSRef repr�sentant une nouvelle fonction.
	///
	static TDCLNSRef MakeFunction( void );

	///
	/// Cr�ateur pour un tableau.
	///
	/// \param inSize	taille du tableau
	/// \param inRef	valeur initiale pour les �l�ments du tableau
	/// \return un nouvel objet TDCLNSRef repr�sentant un nouveau tableau.
	///
	static TDCLNSRef MakeArray(
						KUInt32 inSize = 0,
						const TDCLNSRef& inRef = TDCLNSRef::kNILREF );

	///
	/// Cr�ateur pour un symbole � partir d'une cha�ne ISO-8859-1.
	///
	/// \param inString		cha�ne pour ce symbole.
	/// \return un nouvel objet TDCLNSRef repr�sentant un nouveau symbole.
	///
	static TDCLNSRef MakeSymbol( const char* inString );

	///
	/// Cr�ateur pour un symbole � partir d'une cha�ne UCS-2.
	///
	/// \param inString		cha�ne pour ce symbole.
	/// \return un nouvel objet TDCLNSRef repr�sentant un nouveau symbole.
	///
	static TDCLNSRef MakeSymbol( const KUInt16* inString );

	///
	/// Cr�ateur pour une cha�ne � partir d'une cha�ne ISO-8859-1.
	///
	/// \param inString		cha�ne consid�r�e.
	/// \return un nouvel objet TDCLNSRef repr�sentant une nouvelle cha�ne.
	///
	static TDCLNSRef MakeString( const char* inString );

	///
	/// Cr�ateur pour une cha�ne � partir d'une cha�ne UCS-2.
	///
	/// \param inString		cha�ne consid�r�e (termin�e par un nul).
	/// \return un nouvel objet TDCLNSRef repr�sentant une nouvelle cha�ne.
	///
	static TDCLNSRef MakeString( const KUInt16* inString );

	///
	/// Cr�ateur pour une cha�ne � partir d'une suite de caract�res UCS-2.
	///
	/// \param inString		suite de caract�res consid�r�e.
	/// \param inSize		nombre de caract�res.
	/// \return un nouvel objet TDCLNSRef repr�sentant une nouvelle cha�ne.
	///
	static TDCLNSRef MakeString( const KUInt16* inString, KUInt32 inSize );

	///
	/// Cr�ateur pour un binaire � partir d'un pointeur et d'une taille.
	/// La classe est la classe par d�faut.
	///
	/// \param inData		donn�es pour le binaire.
	/// \param inSize		taille des donn�es pour le binaire.
	/// \return un nouvel objet TDCLNSRef repr�sentant un nouveau binaire.
	///
	static TDCLNSRef MakeBinary(
							const void* inData,
							KUInt32 inSize );

	///
	/// Cr�ateur pour un binaire � partir d'un pointeur, d'une taille
	/// et d'une classe.
	///
	/// \param inData		donn�es pour le binaire.
	/// \param inSize		taille des donn�es pour le binaire.
	/// \param inClass		classe du binaire.
	/// \return un nouvel objet TDCLNSRef repr�sentant un nouveau binaire.
	///
	static TDCLNSRef MakeBinary(
							const void* inData,
							KUInt32 inSize,
							const TDCLNSRef& inClass );

	/// \name Tests sur le type

	///
	/// D�termine si la r�f�rence est un entier.
	///
	/// \return \c true si c'est un entier, \c false sinon.
	///
	inline Boolean IsInt( void ) const
		{
			return (mRef & kTagMask) == kIntegerTag;
		}

	///
	/// D�termine si la r�f�rence est un caract�re.
	///
	/// \return \c true si c'est un caract�re, \c false sinon.
	///
	inline Boolean IsChar( void ) const
		{
			return (mRef & (kTagMask | kImmedBitsMask)) == (kImmedTag | kImmedChar);
		}

	///
	/// D�termine si la r�f�rence est un bool�en (un des deux bool�ens).
	///
	/// \return \c true si c'est un bool�en, \c false sinon.
	///
	inline Boolean IsBoolean( void ) const
		{
			return (mRef == kNILRefValue) || (mRef == kTRUERefValue);
		}

	///
	/// D�termine si la r�f�rence est NIL.
	///
	/// \return \c true si c'est NIL, \c false sinon.
	///
	inline Boolean IsNIL( void ) const
		{
			return (mRef == kNILRefValue);
		}

	///
	/// D�termine si la r�f�rence est TRUE.
	///
	/// \return \c true si c'est TRUE, \c false sinon.
	///
	inline Boolean IsTRUE( void ) const
		{
			return (mRef == kTRUERefValue);
		}

	///
	/// D�termine si la r�f�rence est un pointeur (magique ou non).
	///
	/// \return \c true si c'est un pointeur, \c false sinon.
	///
	inline Boolean IsPtr( void ) const
		{
			return IsRealPtr() || IsMagicPtr();
		}

	///
	/// D�termine si la r�f�rence est un pointeur magique.
	///
	/// \return \c true si c'est un pointeur magique, \c false sinon.
	///
	inline Boolean IsMagicPtr( void ) const
		{
			return (mRef & kTagMask) == kMagicPtrTag;
		}

	///
	/// D�termine si la r�f�rence est un pointeur normal.
	///
	/// \return \c true si c'est un pointeur normal, \c false sinon.
	///
	inline Boolean IsRealPtr( void ) const
		{
			return (mRef & kTagMask) == kPointerTag;
		}

	///
	/// D�termine si la r�f�rence est un symbole.
	///
	/// \return \c true si c'est un symbole, \c false sinon.
	///
	inline Boolean IsSymbol( void ) const
		{
			return IsRealPtr() && GetPointer()->IsSymbol();
		}

	///
	/// D�termine si la r�f�rence est une structure.
	///
	/// \return \c true si c'est une structure, \c false sinon.
	///
	inline Boolean IsFrame( void ) const
		{
			return IsRealPtr() && GetPointer()->IsFrame();
		}

	///
	/// D�termine si la r�f�rence est un tableau.
	///
	/// \return \c true si c'est un tableau, \c false sinon.
	///
	inline Boolean IsArray( void ) const
		{
			return IsRealPtr() && GetPointer()->IsArray();
		}

	///
	/// D�termine si la r�f�rence est un binaire.
	///
	/// \return \c true si c'est un binaire, \c false sinon.
	///
	inline Boolean IsBinary( void ) const
		{
			return IsRealPtr() && GetPointer()->IsBinary();
		}

	///
	/// D�termine si la r�f�rence est une cha�ne.
	///
	/// \return \c true si c'est une cha�ne, \c false sinon.
	///
	inline Boolean IsString( void ) const
		{
			return IsRealPtr() && GetPointer()->IsString();
		}

	/// \name Conversion des imm�diats

	///
	/// R�cup�re l'entier repr�sent� par cette r�f�rence.
	///
	/// \return l'entier repr�sent� par cette r�f�rence.
	///	\throws	TDCLException si cette r�f�rence n'est pas un entier.
	///
	KSInt32 ToInt( void ) const;

	///
	/// R�cup�re le caract�re repr�sent� par cette r�f�rence.
	///
	/// \return le caract�re repr�sent� par cette r�f�rence (en unicode).
	///	\throws	TDCLException si cette r�f�rence n'est pas un caract�re.
	///
	KUInt16 ToChar( void ) const;

	///
	/// R�cup�re le pointeur magique repr�sent� par cette r�f�rence.
	///
	/// \return le pointeur magique repr�sent� par cette r�f�rence.
	///	\throws	TDCLException si cette r�f�rence n'est pas un pointeur magique.
	///
	KUInt32 ToMagicPtr( void ) const;

	///
	/// R�cup�re l'indice du pointeur magique repr�sent� par cette r�f�rence.
	///
	/// \return l'indice du pointeur magique.
	///	\throws	TDCLException si cette r�f�rence n'est pas un pointeur magique.
	///
	KUInt32 GetMagicPtrIndex( void ) const;

	///
	/// R�cup�re le num�ro de la table du pointeur magique repr�sent� par cette
	/// r�f�rence.
	///
	/// \return le num�ro de la table du pointeur magique.
	///	\throws	TDCLException si cette r�f�rence n'est pas un pointeur magique.
	///
	KUInt32 GetMagicPtrTable( void ) const;

	/// \name Fonctions g�n�rales

	///
	/// Copie l'objet r�f�renc� (s'il s'agit d'un pointeur).
	///
	/// \return une r�f�rence pointant vers une copie de l'objet.
	///
	TDCLNSRef Clone( void ) const;

	///
	/// Copie l'objet r�f�renc� en profondeur (s'il s'agit
	/// d'un pointeur).
	///
	/// \return une r�f�rence pointant vers une copie de l'objet.
	///
	TDCLNSRef DeepClone( void ) const;

	///
	/// Copie l'objet r�f�renc� en profondeur (s'il s'agit
	/// d'un pointeur).
	///
	/// \return une r�f�rence pointant vers une copie de l'objet.
	///
	TDCLNSRef TotalClone( void ) const;

	/// \name Fonctions sur la classe

	///
	/// D�termine la classe cet objet.
	/// Ce n'est pas forc�ment un symbole.
	///
	/// \return une r�f�rence vers la classe de cet objet.
	///
	TDCLNSRef ClassOf( void ) const;

	///
	/// D�termine la classe primaire de cet objet.
	/// Il s'agit forc�ment d'un symbole.
	///
	/// \return une r�f�rence vers la classe primaire de cet objet.
	///
	TDCLNSRef PrimClassOf( void ) const;

	///
	/// Change la classe de cet objet.
	/// Ceci n'est pas possible pour les imm�diats (lance
	/// kNSErrObjectPointerOfNonPtr) ou pour les symboles (cf TDCLNSSymbol.h)
	///
	/// \param	inClass un objet qui sert de nouvelle classe � cet objet.
	/// \return *this
	/// \throws TDCLNSException si une erreur est survenue.
	///
	TDCLNSRef SetClass( const TDCLNSRef& inClass );

	///
	/// Change la classe de cet objet.
	/// Ceci n'est pas possible pour les imm�diats (lance
	/// kNSErrObjectPointerOfNonPtr) ou pour les symboles (cf TDCLNSSymbol.h)
	///
	/// \param	inClass la nouvelle classe de l'objet
	/// \return *this
	/// \throws TDCLNSException si une erreur est survenue.
	///
	inline TDCLNSRef SetClass( const char* inClass )
		{
			return SetClass( MakeSymbol( inClass ) );
		}

	/// \name Fonctions sur les structures & les �l�ments

	/// \name Conversion vers TDCLNSObject&

	///
	/// Conversion vers TDCLNSSymbol&
	///
	/// \return une r�f�rence vers le TDCLNSSymbol point� par cet objet.
	/// \throw TDCLException si l'objet n'est pas un symbole.
	/// 
	inline operator TDCLNSSymbol& ( void ) const
		{
			return ToSymbol();
		}
	
	///
	/// Conversion vers TDCLNSSymbol&
	///
	/// \return une r�f�rence vers le TDCLNSSymbol point� par cet objet.
	/// \throw TDCLException si l'objet n'est pas un symbole.
	/// 
	TDCLNSSymbol& ToSymbol( void ) const;
	
	///
	/// Conversion vers TDCLNSFrame&
	///
	/// \return une r�f�rence vers la TDCLNSFrame point�e par cet objet.
	/// \throw TDCLException si l'objet n'est pas une structure.
	/// 
	inline operator TDCLNSFrame& ( void ) const
		{
			return ToFrame();
		}
	
	///
	/// Conversion vers TDCLNSFrame&
	///
	/// \return une r�f�rence vers la TDCLNSFrame point�e par cet objet.
	/// \throw TDCLException si l'objet n'est pas une structure.
	/// 
	TDCLNSFrame& ToFrame( void ) const;
	
	///
	/// Conversion vers TDCLNSArray&
	///
	/// \return une r�f�rence vers le TDCLNSArray point� par cet objet.
	/// \throw TDCLException si l'objet n'est pas un tableau.
	/// 
	inline operator TDCLNSArray& ( void ) const
		{
			return ToArray();
		}
	
	///
	/// Conversion vers TDCLNSArray&
	///
	/// \return une r�f�rence vers le TDCLNSArray point� par cet objet.
	/// \throw TDCLException si l'objet n'est pas un tableau.
	/// 
	TDCLNSArray& ToArray( void ) const;
	
	///
	/// Conversion vers TDCLNSBinary&
	///
	/// \return une r�f�rence vers la TDCLNSBinary point�e par cet objet.
	/// \throw TDCLException si l'objet n'est pas une cha�ne.
	/// 
	inline operator TDCLNSBinary& ( void ) const
		{
			return ToBinary();
		}
	
	///
	/// Conversion vers TDCLNSBinary&
	///
	/// \return une r�f�rence vers la TDCLNSBinary point�e par cet objet.
	/// \throw TDCLNSException si l'objet n'est pas une cha�ne.
	/// 
	TDCLNSBinary& ToBinary( void ) const;
	
	///
	/// Conversion vers TDCLNSString&
	///
	/// \return une r�f�rence vers la TDCLNSString point�e par cet objet.
	/// \throw TDCLException si l'objet n'est pas une cha�ne.
	/// 
	inline operator TDCLNSString& ( void ) const
		{
			return ToString();
		}
	
	///
	/// Conversion vers TDCLNSString&
	///
	/// \return une r�f�rence vers la TDCLNSString point�e par cet objet.
	/// \throw TDCLNSException si l'objet n'est pas une cha�ne.
	/// 
	TDCLNSString& ToString( void ) const;
	
	///
	/// Op�rateur de concat�nation.
	///
	/// \param inAlter		cha�ne � concat�ner avec cette cha�ne.
	/// \throw TDCLNSException si l'objet n'est pas une cha�ne.
	///
	TDCLNSRef operator & ( const TDCLNSRef& inAlter ) const;
	
	///
	/// Op�rateur de concat�nation.
	///
	/// \param inAlter		cha�ne � concat�ner avec cette cha�ne.
	/// \throw TDCLNSException si l'objet n'est pas une cha�ne.
	///
	TDCLNSRef operator & ( const char* inAlter ) const;
	
	///
	/// Op�rateur de concat�nation.
	///
	/// \param inAlter		cha�ne � concat�ner avec cette cha�ne.
	/// \throw TDCLNSException si l'objet n'est pas une cha�ne.
	///
	TDCLNSRef operator & ( const KUInt16* inAlter ) const;
	
	///
	/// Op�rateur de concat�nation avec une espace.
	///
	/// \param inAlter		cha�ne � concat�ner avec cette cha�ne.
	/// \throw TDCLNSException si l'objet n'est pas une cha�ne.
	///
	TDCLNSRef operator && ( const TDCLNSRef& inAlter ) const;

	///
	/// Op�rateur de concat�nation avec une espace.
	///
	/// \param inAlter		cha�ne � concat�ner avec cette cha�ne.
	/// \throw TDCLNSException si l'objet n'est pas une cha�ne.
	///
	TDCLNSRef operator && ( const char* inAlter ) const;

	///
	/// Op�rateur de concat�nation avec une espace.
	///
	/// \param inAlter		cha�ne � concat�ner avec cette cha�ne.
	/// \throw TDCLNSException si l'objet n'est pas une cha�ne.
	///
	TDCLNSRef operator && ( const KUInt16* inAlter ) const;

private:
	/// \name Constructeur priv�

	///
	/// Constructeur � partir d'une r�f�rence.
	/// Incr�mente la r�f�rence s'il s'agit d'un pointeur.
	///
	TDCLNSRef( KUIntPtr inRef );

	/// \name Gestion du pointeur

	///
	/// R�cup�re le pointeur sur l'objet.
	///
	inline TDCLNSObject* GetPointer( void ) const
		{
			return (TDCLNSObject*) (mRef - kPointerTag);
		}

	/// \name Interface Entr�e/Sortie

	///
	/// Cr�e une repr�sentation XML de la r�f�rence.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	void ToXML( TDCLXMLEncoder* inEncoder ) const;

	///
	/// Cr�e une repr�sentation NSOF de la r�f�rence.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	void ToNSOF( TDCLNSOFEncoder* inEncoder ) const;

	///
	/// Cr�e une repr�sentation sous forme de texte de la r�f�rence.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	void ToText( TDCLTextEncoder* inEncoder ) const;

	///
	/// Cr�e une repr�sentation pour un paquet de la r�f�rence.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	void ToPkg( TDCLPkgEncoder* inEncoder ) const;

	/// \name R�f�rence
	KUIntPtr	mRef;
	
	///
	/// Constantes pour la r�f�rence.
	///
	enum {
		kTagShift		= 0x2,
		kTagMask		= 0x3,		// 0b11
		kIntegerTag		= 0x0,		// 0b00
		kPointerTag		= 0x1,		// 0b01
		kImmedTag		= 0x2,		// 0b10
		kMagicPtrTag	= 0x3,		// 0b11

		kImmedBitsShift	= 0x4,
		kImmedBitsMask	= 0xC,		// 0b1100
		kImmedSpecial	= 0x0,		// 0b0000
		kImmedChar		= 0x4,		// 0b0100
		kImmedBoolean	= 0x8,		// 0b1000
		kImmedReserved	= 0xC,		// 0b1100
		
		kNILRefValue	= 0x2,		// Immed, Special, 0
		kTRUERefValue	= 0x1A,		// Immed, Boolean, 1

		kMagicPtrTShift	= 12,		// En plus des 2 bits pour le type.
		kMagicPtrIMask	= 0xFFF		// 0b1111 1111 1111
	};
};

#endif
		// __TDCLNSREF__

// ============================================================================= //
// I *____knew* I had some reason for not logging you off... If I could just //
// remember what it was.                                                         //
// ============================================================================= //
