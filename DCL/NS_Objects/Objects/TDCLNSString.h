// ==============================
// Fichier:			TDCLNSString.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			21/10/2002
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
// The Original Code is TDCLNSString.h.
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
// $Id: TDCLNSString.h,v 1.5 2004/11/24 14:09:07 paul Exp $
// ===========

#ifndef __TDCLNSSTRING__
#define __TDCLNSSTRING__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Objects/TDCLNSBinary.h>

// K
#include <K/Unicode/UUTF16CStr.h>

class TDCLStream;

///
/// Classe pour les cha�nes NewtonScript.
/// Ces cha�nes sont stock�es au format UCS-2.
///
/// Cette classe est un peu particuli�re. Elle n'a aucun destructeur
/// virtuel ou membre parce qu'en fait, les objets de cette classe doivent
/// correspondre exactement � ceux de \c TDCLNSBinary qui sont des cha�nes, vu
/// que seule la classe diff�rencient les cha�nes parmi les binaires.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.5 $
///
/// \test	UTestNS::CatenateStrings
///
class TDCLNSString
	:
		public TDCLNSBinary	
{
public:
	///
	/// Constructeur � partir d'une cha�ne ISO 8859-1.
	///
	/// \param inString		cha�ne de caract�res consid�r�e.
	///
	TDCLNSString( const char* inString );

	///
	/// Constructeur � partir d'une cha�ne UCS-2.
	///
	/// \param inString		cha�ne de caract�res consid�r�e.
	///
	TDCLNSString( const KUInt16* inString );

	///
	/// Cr�ateur pour une cha�ne � partir d'une suite de caract�res UCS-2.
	/// \param inString		suite de caract�res consid�r�e.
	/// \param inSize		nombre de caract�res.
	///
	TDCLNSString( const KUInt16* inString, KUInt32 inSize );

	///
	/// Constructeur � partir d'un flux et d'une taille.
	///
	/// \param inStream		flux o� lire les donn�es.
	/// \param inLength		nombre d'octets � lire
	///						(2 * taille de la cha�ne avec terminateur)
	///
	TDCLNSString(
			TDCLStream* inStream,
			KUInt32 inLength );

	///
	/// Cr�e un objet � partir d'un flux NSOF
	///
	/// \param inDecoder	d�codeur NSOF associ� � un flux donn�.
	/// \return un nouvel objet � partir de ce flux
	///
	static	TDCLNSString*	FromNSOF( TDCLNSOFDecoder* inDecoder );

	///
	/// Compare cette cha�ne avec une autre cha�ne ISO 8859-1.
	///
	/// \return \c true si les deux cha�nes sont �gales � la casse pr�s.
	///
	Boolean StrEqual( const char* inAlter ) const;

	///
	/// Compare cette cha�ne avec une autre cha�ne unicode.
	///
	/// \return \c true si les deux cha�nes sont �gales � la casse pr�s.
	///
	Boolean StrEqual( const KUInt16* inAlter ) const;

	///
	/// Compare cette cha�ne avec une autre cha�ne.
	///
	/// \return \c true si les deux cha�nes sont �gales � la casse pr�s.
	///
	Boolean StrEqual( const TDCLNSString& inAlter ) const;

	///
	/// Accesseur sur la cha�ne.
	/// Valide tant que la cha�ne n'est pas redimensionn�e.
	///
	/// \return la cha�ne en unicode.
	///
	inline KUInt16* GetString( void )
		{
			return (KUInt16*) GetPointer();
		}

	///
	/// Accesseur sur la cha�ne.
	/// Comme le pr�c�dent mais en lecture seule.
	///
	/// \return la cha�ne en unicode.
	///
	inline const KUInt16* GetString( void ) const
		{
			return (const KUInt16*) GetPointer();
		}

	///
	/// Accesseur sur la taille de la cha�ne.
	/// Comme StrLen sur Newton.
	///
	/// \return la taille de la cha�ne.
	///
	inline KUInt32 GetStrLen( void ) const
		{
			return UUTF16CStr::StrLen( GetString() );
		}

	///
	/// Concat�nation.
	///
	/// \param inAlter	cha�ne avec laquelle concat�ner cette cha�ne.
	/// \return	une nouvelle cha�ne compos�e de cette cha�ne et de la cha�ne
	///			inAlter.
	///
	inline TDCLNSString* Catenate( const TDCLNSString& inAlter ) const
		{
			return Catenate( inAlter.GetString() );
		}

	///
	/// Concat�nation.
	///
	/// \param inAlter	cha�ne avec laquelle concat�ner cette cha�ne.
	/// \return	une nouvelle cha�ne compos�e de cette cha�ne et de la cha�ne
	///			inAlter.
	///
	TDCLNSString* Catenate( const char* inAlter ) const;

	///
	/// Concat�nation.
	///
	/// \param inAlter	cha�ne avec laquelle concat�ner cette cha�ne.
	/// \return	une nouvelle cha�ne compos�e de cette cha�ne et de la cha�ne
	///			inAlter.
	///
	TDCLNSString* Catenate( const KUInt16* inAlter ) const;

	///
	/// Concat�nation avec espace.
	///
	/// \param inAlter	cha�ne avec laquelle concat�ner cette cha�ne.
	/// \return	une nouvelle cha�ne compos�e de cette cha�ne et de la cha�ne
	///			inAlter, les deux cha�nes �tant s�par�es par une espace.
	///
	inline TDCLNSString* CatenateWithSpace( const TDCLNSString& inAlter ) const
		{
			return CatenateWithSpace( inAlter.GetString() );
		}

	///
	/// Concat�nation avec espace.
	///
	/// \param inAlter	cha�ne avec laquelle concat�ner cette cha�ne.
	/// \return	une nouvelle cha�ne compos�e de cette cha�ne et de la cha�ne
	///			inAlter, les deux cha�nes �tant s�par�es par une espace.
	///
	TDCLNSString* CatenateWithSpace( const char* inAlter ) const;

	///
	/// Concat�nation avec espace.
	///
	/// \param inAlter	cha�ne avec laquelle concat�ner cette cha�ne.
	/// \return	une nouvelle cha�ne compos�e de cette cha�ne et de la cha�ne
	///			inAlter, les deux cha�nes �tant s�par�es par une espace.
	///
	TDCLNSString* CatenateWithSpace( const KUInt16* inAlter ) const;

private:
	///
	/// Constructeur � partir d'une cha�ne UCS-2 et d'une taille.
	/// Ce constructeur ne sert que pour la concat�nation.
	///
	TDCLNSString( KUInt16* inBuffer, KUInt32 inData );

	///
	/// Constructeur par d�faut volontairement indisponible.
	///
	TDCLNSString( void );
	
	///
	/// Espace en UTF-16.
	///
	static const KUInt16 kSpaceChar;
};

#endif
		// __TDCLNSSTRING__

// ========================================================================= //
// Think of your family tonight.  Try to crawl home after the computer       //
// crashes.                                                                  //
// ========================================================================= //
