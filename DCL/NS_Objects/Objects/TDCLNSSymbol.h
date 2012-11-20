// ==============================
// Fichier:			TDCLNSSymbol.h
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
// The Original Code is TDCLNSSymbol.h.
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
// $Id: TDCLNSSymbol.h,v 1.7 2004/11/24 14:09:07 paul Exp $
// ===========

#ifndef __TDCLNSSYMBOL__
#define __TDCLNSSYMBOL__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Objects/TDCLNSObject.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>

class TDCLNSOFDecoder;
class TDCLPkgDecoder;

///
/// Classe pour les symboles NewtonScript.
///
/// Le point sur les symboles 8 bits.
/// ---------------------------------
///
/// Les symboles ne contiennent normalement que des caract�res entre 32 et 127.
/// Cependant, NTK et WinNTK peuvent, dans certaines circonstances, cr�er des
/// symboles 8 bits. Chacun calcule la valeur de hachage en mettant la cha�ne
/// en majuscule, mais chacun le fait dans l'encodage du syst�me
/// (Windows, MacRoman). Le Newton en revanche supprime froidement les accents
/// lorsqu'on tente de cr�er des symboles 8 bits.
///
/// Je suppose qu'un symbole 8 bits ne pourra �tre d�clar� comme �gal � un autre
/// symbole 8 bits que si ce symbole est construit � la main ou a �t� cr�� par
/// le m�me programme (WinNTK ou NTK) afin que la cha�ne soit la m�me et que la
/// valeur de hachage soit aussi la m�me.
///
/// Pour la DCL, les choses se passent ainsi:
/// - comme sur Newton et NTK/WinNTK, les tests d'ordre et d'�galit� commencent
///   par la valeur de hachage.
/// - les constructeurs normaux traduisent les cha�nes avec des s�quences \\u.
/// - il y a un constructeur avec une cha�ne 8 bits et une valeur de hachage.
/// - les symboles dans les paquets sont lus avec la valeur de hachage du
///   paquet.
/// - la cha�ne est consid�r�e comme th�oriquement sur 7 bits mais pour
///   l'export XML, elle est trait�e comme une cha�ne Latin1.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.7 $
///
/// \test	aucun test d�fini.
///
class TDCLNSSymbol
	:
		public TDCLNSObject
{
public:
	///
	/// Constructeur � partir d'une cha�ne de caract�re ISO-8859-1
	///
	/// La cha�ne est convertie en ASCII 32/127 (avec des slash-u-code-slash-u).
	///
	/// \param inString		cha�ne de caract�re pour ce symbole.
	///
	TDCLNSSymbol( const char* inString );

	///
	/// Constructeur � partir d'une cha�ne ASCII et d'une valeur de hachage.
	///
	/// \param inString		cha�ne de caract�re pour ce symbole.
	/// \param inHashCode	valeur de hachage pour la cha�ne.
	///
	TDCLNSSymbol( const char* inString, KUInt32 inHashCode );

	///
	/// Constructeur � partir d'une cha�ne de caract�re UCS-2.
	///
	/// La cha�ne est convertie en ASCII 32/127 (avec des slash-u-code-slash-u).
	///
	/// \param inString 	cha�ne de caract�re pour ce symbole.
	///
	TDCLNSSymbol( const KUInt16* inString );

	///
	/// Constructeur par copie.
	/// La cha�ne est copi�e.
	///
	/// \param inCopy 		objet � copier
	///
	TDCLNSSymbol( const TDCLNSSymbol& inCopy );

	///
	/// Op�rateur d'assignation.
	/// La cha�ne est copi�e.
	///
	/// \param inCopy		objet � copier
	///
	TDCLNSSymbol& operator = ( const TDCLNSSymbol& inCopy );

	///
	/// Destructeur.
	///
	virtual ~TDCLNSSymbol( void );

	///
	/// D�termine si cet objet est un symbole.
	///
	/// \return \c false
	///
	virtual Boolean IsSymbol( void ) const;

	///
	/// Accesseur sur la valeur de hachage.
	///
	/// \return 	la valeur de hachage.
	///
	inline KUInt32 GetHashCode( void ) const
		{
			return mHashCode;
		}

	///
	/// Accesseur sur la cha�ne
	///
	/// \return 	la cha�ne (encod�e en ASCII 32/127), termin�e par un nul.
	///
	inline const char* GetString( void ) const
		{
			return mString;
		}
	
	///
	/// Op�rateur pour faire de m�me.
	///
	/// \return		la cha�ne (encod�e en ASCII 32/127), termin�e par un nul.
	///
	inline operator const char*() const
		{
			return mString;
		}

	///
	/// Compare \c this � un autre symbole.
	///
	/// La comparaison fonctionne ainsi:
	/// - d'abord les valeurs de hachage sont compar�es.
	/// - ensuite, si elles sont �gales, les cha�nes sont compar�es selon
	///   l'ordre lexicographique.
	///
	/// \param	inAlter		symbole avec lequel se comparer
	/// \return	un entier:
	///			- 0 si les deux symboles sont �gaux.
	///			- un entier n�gatif si \c this est plus petit que \p inAlter
	///			- un entier positif si \c this est plus grand que \p inAlter
	int Compare( const TDCLNSSymbol& inAlter ) const;

	///
	/// Cr�e une copie de surface du symbole.
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
	static	TDCLNSSymbol*	FromNSOF( TDCLNSOFDecoder* inDecoder );

	///
	/// Cr�e un objet � partir d'un paquet.
	///
	/// \param inDecoder	d�codeur Pkg associ� � un flux donn�.
	/// \return un nouvel objet � partir de ce flux
	///
	static	TDCLNSSymbol*	FromPkg( TDCLPkgDecoder* inDecoder );

	///
	/// D�termine la classe de ce symbole.
	/// Ce n'est pas forc�ment un symbole.
	///
	/// \return une r�f�rence vers la classe de ce symbole.
	///
	virtual TDCLNSRef ClassOf( void ) const;

	///
	/// D�termine la classe primaire de ce symbole.
	/// Il s'agit forc�ment d'un symbole.
	///
	/// \return une r�f�rence vers la classe primaire de ce symbole.
	///
	virtual TDCLNSRef PrimClassOf( void ) const;

	///
	/// D�termine si le symbole this est une sous-classe d'un symbole donn�.
	/// I.e. s'il est de la forme super.foo.
	/// Remarque: si le param�tre est �gal � this, on retourne aussi \c true.
	///
	/// \return une r�f�rence vers la classe primaire de ce symbole.
	///
	Boolean IsSubClass( const TDCLNSSymbol& inSuper ) const;

	///
	/// Change la classe de ce symbole.
	/// Ceci n'est pas possible avec la DCL (mais �a l'est avec NewtonOS).
	/// Si on change la classe d'un symbole sous NewtonOS, l'objet est
	/// transform� en un binaire.
	/// Les symboles dans la DCL sont en lecture seule.
	///
	/// \param	inClass un objet qui sert de nouvelle classe � ce binaire.
	/// \throws TDCLNSException pour indiquer que l'objet est en lecture
	///			seule.
	///
	virtual void SetClass( const TDCLNSRef& inClass );

	///
	/// Calcule la valeur de hachage d'une cha�ne.
	/// La cha�ne doit �tre compos�e de caract�res entre 32 et 127.
	///
	/// \param	inString	cha�ne � hacher.
	/// \return	valeur de hachage comme sp�cifi�e dans Newton Formats.
	///
	static KUInt32	HashFunction( const char* inString );

private:
	///
	/// Constantes pour cette classe.
	///
	enum {
		kHashMagic = 0x9E3779B9		///< Et oui, le hash, c'est magique.
	};

	///
	/// Constructeur � partir d'un flux et d'un nombre d'octets.
	/// La cha�ne est lue telle quelle.
	///
	/// \param inStream		flux
	/// \param inNbChars	nombre d'octets � lire (sans le z�ro final)
	///
	TDCLNSSymbol( TDCLStream* inStream, KUInt32 inNbChars );

	///
	/// Constructeur � partir d'un flux et d'un nombre d'octets et d'une valeur
	/// de hachage.
	/// La cha�ne est lue telle quelle.
	///
	/// \param inStream		flux
	/// \param inNbChars	nombre d'octets � lire (sans le z�ro final)
	/// \param inHashCode	valeur de hachage.
	///
	TDCLNSSymbol(
			TDCLStream* inStream,
			KUInt32 inNbChars,
			KUInt32 inHashCode );

	///
	/// Convertit une cha�ne ISO-8859-1 en ASCII 32/127
	///
	/// \param	inString	cha�ne � convertir.
	/// \return la nouvelle cha�ne, allou�e avec malloc.
	///
	static char*	ToASCII32_127( const char* inString );

	///
	/// Convertit une cha�ne UCS-2 en ASCII 32/127
	///
	/// \param	inString	cha�ne � convertir.
	/// \return la nouvelle cha�ne, allou�e avec malloc.
	///
	static char*	ToASCII32_127( const KUInt16* inString );

	/// \name Interface IStreamable
	
	///
	/// Cr�e une repr�sentation XML du symbole.
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
	/// Cr�e une repr�sentation NSOF du symbole.
	/// Comprend le type et les donn�es.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	virtual void ToNSOF(
				TDCLNSOFEncoder* inEncoder ) const;

	///
	/// Cr�e une repr�sentation sous forme de texte du symbole.
	/// Comprend les crochets et les donn�es.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	virtual void ToText(
				TDCLTextEncoder* inEncoder ) const;

	///
	/// Cr�e une repr�sentation du symbole � mettre dans un
	/// paquet.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder	encodeur pour le paquet.
	/// \param ioOffset		en entr�e et en sortie, d�calage par rapport
	///						au paquet.
	///
	virtual void ToPkg( TDCLPkgEncoder* inEncoder, KUInt32* ioOffset ) const;

	/// \name Variables Priv�es
		
	const char*				mString;	///< Cha�ne de caract�re pour ce symbole.
	const KUInt32			mHashCode;	///< Valeur de hachage (doit �tre
										///< apr�s!)
};

#endif
		// __TDCLNSSYMBOL__

// ============================================================================== //
//         The wise programmer is told about the Tao and follows it.  The average //
// programmer is told about the Tao and searches for it.  The foolish programmer  //
// is told about the Tao and laughs at it.  If it were not for laughter, there    //
// would be no Tao.                                                               //
//         The highest sounds are the hardest to hear.  Going forward is a way to //
// retreat.  Greater talent shows itself late in life.  Even a perfect program    //
// still has bugs.                                                                //
//                 -- Geoffrey James, "The Tao of Programming"                    //
// ============================================================================== //
