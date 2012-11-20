// ==============================
// Fichier:			TDCLNSSymbol.cp
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
// The Original Code is TDCLNSSymbol.cp.
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
// $Id: TDCLNSSymbol.cp,v 1.9 2004/11/24 14:09:07 paul Exp $
// ===========

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Objects/TDCLNSSymbol.h>

// ANSI C
#include <stdlib.h>
#include <string.h>

// DCL
#include <DCL/Exceptions/TDCLNSException.h>
#include <DCL/Exceptions/Errors/TDCLLimitReachedError.h>
#include <DCL/Exceptions/Errors/TDCLMemError.h>
#include <DCL/NS_Objects/Exchange/TDCLNSOFDecoder.h>
#include <DCL/NS_Objects/Exchange/TDCLNSOFEncoder.h>
#include <DCL/NS_Objects/Exchange/TDCLPkgDecoder.h>
#include <DCL/NS_Objects/Exchange/TDCLPkgEncoder.h>
#include <DCL/NS_Objects/Exchange/TDCLTextEncoder.h>
#include <DCL/NS_Objects/Exchange/TDCLXMLEncoder.h>
#include <DCL/NS_Objects/Objects/KDCLSYM.h>
#include <DCL/Streams/TDCLRandomAccessStream.h>
#include <DCL/Streams/TDCLStream.h>

// ------------------------------------------------------------------------- //
//  * TDCLNSSymbol( const char* )
// ------------------------------------------------------------------------- //
TDCLNSSymbol::TDCLNSSymbol( const char* inString )
	:
		TDCLNSObject(),
// Ceci passe (12.6.2.5) parce que les champs sont dans cet ordre.
		mString( ToASCII32_127( inString ) ),
		mHashCode( HashFunction( mString ) )
{
}

// ------------------------------------------------------------------------- //
//  * TDCLNSSymbol( const KUInt16* )
// ------------------------------------------------------------------------- //
TDCLNSSymbol::TDCLNSSymbol( const KUInt16* inString )
	:
		TDCLNSObject(),
// Idem.
		mString( ToASCII32_127( inString ) ),
		mHashCode( HashFunction( mString ) )
{
}

// ------------------------------------------------------------------------- //
//  * TDCLNSSymbol( const char*, KUInt32 )
// ------------------------------------------------------------------------- //
TDCLNSSymbol::TDCLNSSymbol( const char* inString, KUInt32 inHashCode )
	:
		TDCLNSObject(),
		mString( nil ),
		mHashCode( inHashCode )
{
	// Copie de la cha�ne
	size_t theStrLen = ::strlen( inString );
	mString = (const char*) ::malloc( theStrLen + 1 );
	
	if (mString == nil)
	{
		throw DCLMemError;
	}
	
	(void) ::memcpy( (void*) mString, inString, theStrLen + 1 );
}

// ------------------------------------------------------------------------- //
//  * TDCLNSSymbol( const TDCLNSSymbol& )
// ------------------------------------------------------------------------- //
TDCLNSSymbol::TDCLNSSymbol( const TDCLNSSymbol& inCopy )
	:
		TDCLNSObject( inCopy ),
		mString( nil ),
		mHashCode( inCopy.mHashCode )
{
	// Copie de la cha�ne
	size_t theStrLen = ::strlen( inCopy.mString );
	mString = (const char*) ::malloc( theStrLen + 1 );
	
	if (mString == nil)
	{
		throw DCLMemError;
	}
	
	(void) ::memcpy( (void*) mString, inCopy.mString, theStrLen + 1 );
}

// ------------------------------------------------------------------------- //
//  * TDCLNSSymbol( TDCLStream*, KUInt32 )
// ------------------------------------------------------------------------- //
TDCLNSSymbol::TDCLNSSymbol( TDCLStream* inStream, KUInt32 inNbChars )
	:
		mString( (char*) inStream->GetCString( inNbChars ) ),
		mHashCode( HashFunction( mString ) )
{
}

// ------------------------------------------------------------------------- //
//  * TDCLNSSymbol( TDCLStream*, KUInt32, KUInt32 )
// ------------------------------------------------------------------------- //
TDCLNSSymbol::TDCLNSSymbol(
				TDCLStream* inStream,
				KUInt32 inNbChars,
				KUInt32 inHashCode )
	:
		mString( (char*) inStream->GetCString( inNbChars ) ),
		mHashCode( inHashCode )
{
}

// ------------------------------------------------------------------------- //
//  * ~TDCLNSSymbol( void )
// ------------------------------------------------------------------------- //
TDCLNSSymbol::~TDCLNSSymbol( void )
{
	if (mString != nil)
	{
		::free( (void*) mString );
	}
}

// ------------------------------------------------------------------------- //
//  * TDCLNSSymbol( const TDCLNSSymbol& )
// ------------------------------------------------------------------------- //
TDCLNSSymbol&
TDCLNSSymbol::operator = ( const TDCLNSSymbol& inCopy )
{
	// Lib�ration de la cha�ne pr�c�dente.
	if (mString != nil)
	{
		::free( (void*) mString );
	}

	// Copie de la cha�ne
	unsigned long theStrLen = ::strlen( inCopy.mString );
	mString = (const char*) ::malloc( theStrLen + 1 );
	
	if (mString == nil)
	{
		throw DCLMemError;
	}
	
	(void) ::memcpy( (void*) mString, inCopy.mString, theStrLen + 1 );
	
	return *this;
}

// ------------------------------------------------------------------------- //
//  * IsSymbol( void ) const
// ------------------------------------------------------------------------- //
Boolean
TDCLNSSymbol::IsSymbol( void ) const
{
	return true;
}

// ------------------------------------------------------------------------- //
//  * Compare( const TDCLNSSymbol& ) const
// ------------------------------------------------------------------------- //
int
TDCLNSSymbol::Compare( const TDCLNSSymbol& inAlter ) const
{
	int theResult = 0;
	
	// Comparaison de la valeur de hachage.
	KUInt32 alterHC = inAlter.GetHashCode();	// Valeur de hachage de l'autre symbole.
	if (mHashCode < alterHC)
	{
		theResult = -1;
	} else if (mHashCode > alterHC) {
		theResult = 1;
	} else {
		// Comparaison lexicographique.
		// Cette comparaison n'est pas sensible � la casse.
		const char* alterString = inAlter.GetString();	// Cha�ne de l'autre symbole.
		const char* thisString = mString;				// Curseur sur notre cha�ne.
		do {
			char thisChar = *thisString;		// caract�re de cette cha�ne.
			char alterChar = *alterString;		// caract�re de l'autre cha�ne.
			
			if ((thisChar < alterChar)
					&& ((thisChar < 'A')
						|| (thisChar > 'Z')
						|| ((thisChar - 'A' + 'a') != alterChar)))
			{
				theResult = -1;
				break;
			} else if ((thisChar > alterChar)
					&& ((thisChar < 'a')
						|| (thisChar > 'z')
						|| ((thisChar - 'a' + 'A') != alterChar)))
			{
				theResult = 1;
				break;
			} else {
				if (thisChar == '\0') {
					break;	// Comparaison termin�e.
				}
			}
			
			thisString++;
			alterString++;
		} while( true );
	}
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * ClassOf( void ) const
// ------------------------------------------------------------------------- //
TDCLNSRef
TDCLNSSymbol::ClassOf( void ) const
{
	return KDCLSYM::kSYMsymbol;
}

// ------------------------------------------------------------------------- //
//  * PrimClassOf( void ) const
// ------------------------------------------------------------------------- //
TDCLNSRef
TDCLNSSymbol::PrimClassOf( void ) const
{
	return KDCLSYM::kSYMsymbol;
}

// ------------------------------------------------------------------------- //
//  * IsSubClass( const TDCLNSSymbol& ) const
// ------------------------------------------------------------------------- //
Boolean
TDCLNSSymbol::IsSubClass( const TDCLNSSymbol& inSuper ) const
{
	Boolean theResult = false;

	// Comparaison lexicographique.
	// Cette comparaison n'est pas sensible � la casse.
	const char* superString = inSuper.GetString();	// Cha�ne de l'autre symbole.
	const char* thisString = mString;				// Curseur sur notre cha�ne.
	do {
		char thisChar = *thisString;	// caract�re de cette cha�ne.
		char superChar = *superString;	// caract�re de l'autre cha�ne.
		
		if (superChar == '\0')
		{
			if (thisChar == '\0')
			{
				// Egalit�.
				theResult = true;
				break;
			} else {
				// V�rifions que this a bien un point.
				if (thisChar == '.')
				{
					theResult = true;
				}
				
				break;
			}
		} else if ((thisChar < superChar)
				&& ((thisChar < 'A')
					|| (thisChar > 'Z')
					|| ((thisChar - 'A' + 'a') != superChar)))
		{
			break;
		} else if ((thisChar > superChar)
				&& ((thisChar < 'a')
					|| (thisChar > 'z')
					|| ((thisChar - 'a' + 'A') != superChar)))
		{
			break;
		}
		
		thisString++;
		superString++;
	} while( true );
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * SetClass( const TDCLNSRef& )
// ------------------------------------------------------------------------- //
void
TDCLNSSymbol::SetClass( const TDCLNSRef& /* inClass */ )
{
	throw DCLNS( kNSErrObjectReadOnly );
}

// ------------------------------------------------------------------------- //
//  * ToASCII32_127( const char* )
// ------------------------------------------------------------------------- //
char*
TDCLNSSymbol::ToASCII32_127( const char* inString )
{
	// Conversion en ASCII 32/127.
	// On d�termine la taille de la future cha�ne.
	int asciiStringLength = 0;	// Taille de la future cha�ne
	int isoStringLength = 0;	// Taille de la cha�ne en entr�e.
	int indexISOString;
	for (indexISOString = 0; ; indexISOString++)
	{
		signed char theChar = (signed char) inString[indexISOString];
		if (theChar == '\0')
		{
			break;
		}
		
		if (theChar < 32)
		{
			asciiStringLength += 7; // "\uABCD\"
		}
		
		isoStringLength++;
		asciiStringLength++;
	}
	
	char* theResult = (char*) ::malloc( (unsigned long) asciiStringLength + 1 );
	int indexAsciiString = 0;
	for (
			indexISOString = 0;
			indexISOString < isoStringLength;
			indexISOString++)
	{
		signed char theChar = (signed char) inString[indexISOString];
		if (theChar >= 32)
		{
			theResult[indexAsciiString++] = theChar;
		} else {
			theResult[indexAsciiString++] = '\\';
			theResult[indexAsciiString++] = 'u';
			theResult[indexAsciiString++] = '0';
			theResult[indexAsciiString++] = '0';
			int theDigit = (theChar >> 4) & 0x0F;
			if (theDigit > 9)
			{
				theResult[indexAsciiString++] = (char) (theDigit + '0');
			} else {
				theResult[indexAsciiString++] = (char) (theDigit + 'A' - 10);
			}
			theDigit = theChar & 0x0F;
			if (theDigit > 9)
			{
				theResult[indexAsciiString++] = (char) (theDigit + '0');
			} else {
				theResult[indexAsciiString++] = (char) (theDigit + 'A' - 10);
			}
			theResult[indexAsciiString++] = '\\';
			theResult[indexAsciiString++] = 'u';
		}
	}
	
	theResult[ indexAsciiString ] = '\0';
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * ToASCII32_127( const KUInt16* )
// ------------------------------------------------------------------------- //
char*
TDCLNSSymbol::ToASCII32_127( const KUInt16* inString )
{
	// Conversion en ASCII 32/127.
	// On d�termine la taille de la future cha�ne.
	int asciiStringLength = 0;	// Taille de la future cha�ne
	int uniStringLength = 0;	// Taille de la cha�ne en entr�e.
	int indexUniString;
	for (indexUniString = 0; ; indexUniString++)
	{
		KUInt16 theChar = inString[indexUniString];
		if (theChar == 0)
		{
			break;
		}
		
		if ((theChar < 32) || (theChar > 127))
		{
			asciiStringLength += 7; // "\uABCD\"
		}
		
		uniStringLength++;
		asciiStringLength++;
	}
	
	char* theResult = (char*) ::malloc( (unsigned long) asciiStringLength + 1 );
	int indexAsciiString = 0;
	for (
			indexUniString = 0;
			indexUniString < uniStringLength;
			indexUniString++)
	{
		KUInt16 theChar = inString[indexUniString];
		if ((theChar >= 32) && (theChar <= 127))
		{
			theResult[indexAsciiString++] = (char) theChar;
		} else {
			theResult[indexAsciiString++] = '\\';
			theResult[indexAsciiString++] = 'u';
			int theDigit = (theChar >> 12) & 0x0F;
			if (theDigit > 9)
			{
				theResult[indexAsciiString++] = (char) (theDigit + '0');
			} else {
				theResult[indexAsciiString++] = (char) (theDigit + 'A' - 10);
			}
			theDigit = (theChar >> 8) & 0x0F;
			if (theDigit > 9)
			{
				theResult[indexAsciiString++] = (char) (theDigit + '0');
			} else {
				theResult[indexAsciiString++] = (char) (theDigit + 'A' - 10);
			}
			theDigit = (theChar >> 4) & 0x0F;
			if (theDigit > 9)
			{
				theResult[indexAsciiString++] = (char) (theDigit + '0');
			} else {
				theResult[indexAsciiString++] = (char) (theDigit + 'A' - 10);
			}
			theDigit = theChar & 0x0F;
			if (theDigit > 9)
			{
				theResult[indexAsciiString++] = (char) (theDigit + '0');
			} else {
				theResult[indexAsciiString++] = (char) (theDigit + 'A' - 10);
			}
			theResult[indexAsciiString++] = '\\';
			theResult[indexAsciiString++] = 'u';
		}
	}
	
	theResult[ indexAsciiString ] = '\0';
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * HashFunction( const char* )
// ------------------------------------------------------------------------- //
KUInt32
TDCLNSSymbol::HashFunction( const char* inString ) {
	KUInt32 theResult = 0;
	while ( *inString ) {
		char theCharacter = *inString++;	// Caract�re courant.

		if ((theCharacter >= 'a') && (theCharacter <= 'z'))
		{
			theResult = theResult + theCharacter - ('a' - 'A');
		} else {
			theResult = theResult + theCharacter;
		}
	}
	
	return (theResult * kHashMagic);
}

// ------------------------------------------------------------------------- //
//  * Clone( void ) const
// ------------------------------------------------------------------------- //
TDCLNSObject*
TDCLNSSymbol::Clone( void ) const
{
	return new TDCLNSSymbol( *this );
}

// ------------------------------------------------------------------------- //
//  * FromNSOF( TDCLNSOFDecoder* )
// ------------------------------------------------------------------------- //
TDCLNSSymbol*
TDCLNSSymbol::FromNSOF( TDCLNSOFDecoder* inDecoder )
{
	TDCLStream* theStream = inDecoder->GetInputStream();
	
	KUInt32 nbChars = theStream->GetXLong();

	// Cr�ation de l'objet.
	TDCLNSSymbol* theResult = new TDCLNSSymbol( theStream, nbChars );

	// Ajout du symbole dans la liste des objets r�f�renc�s.
	inDecoder->AddObjectToList( TDCLNSRef( theResult ) );

	return theResult;
}

// ------------------------------------------------------------------------- //
//  * FromPkg( TDCLPkgDecoder* )
// ------------------------------------------------------------------------- //
TDCLNSSymbol*
TDCLNSSymbol::FromPkg( TDCLPkgDecoder* inDecoder )
{
	TDCLStream* theStream = inDecoder->GetInputStream();

	// D�calage de l'objet.
	KUInt32 theObjectOffset = inDecoder->GetCurrentStreamOffset();
	
	// Taille
	KUInt32 theFirstLong = theStream->GetLong();
	KUInt32 nbChars = (theFirstLong >> TDCLPkgDecoder::kSizeShift) - 16;
	
	// On passe le deuxi�me long et le troisi�me long.
	(void) theStream->GetLong();
	(void) theStream->GetLong();
	
	// Valeur de hachage.
	// Cf le point sur les symboles 8 bits dans TDCLNSSymbol.h
	KUInt32 theHashCode = theStream->GetLong();
	
	// Cr�ation de l'objet
	TDCLNSSymbol* theResult =
		new TDCLNSSymbol( theStream, nbChars, theHashCode );

	// Ajout du symbole dans la liste des objets r�f�renc�s.
	inDecoder->AddObjectToList( TDCLNSRef( theResult ), theObjectOffset );

	return theResult;
}

// ------------------------------------------------------------------------- //
//  * ToXML( TDCLXMLEncoder*, KUInt32 ) const
// ------------------------------------------------------------------------- //
void
TDCLNSSymbol::ToXML(
				TDCLXMLEncoder*		inEncoder,
				KUInt32				/* inObjectID */ ) const
{
	// R�cup�ration du flux.
	TDCLStream* theOutputStream = inEncoder->GetOutputStream();
	
	// Ajout de <symbol>
	theOutputStream->PutString( "<symbol>" );
	
	// En th�orie, la cha�ne est en ASCII 7 bits.
	// En pratique, on a pu nous fournir du Latin 1
	// (en fait, c'est uniquement pour �viter d'avoir un XML incorrect,
	// WinNTK met du Latin1 et NTK met du MacRoman, on interpr�te tout
	// ceci joyeusement comme du Latin1).

	// Ecriture avec remplacement des caract�res sp�ciaux
	// par des entit�s.
	inEncoder->Print8BitsWithEntities( (const KUInt8*) mString );

	// Ajout de </symbol>
	theOutputStream->PutString( "</symbol>" );	
}

// ------------------------------------------------------------------------- //
//  * ToNSOF( TDCLNSOFEncoder* ) const
// ------------------------------------------------------------------------- //
void
TDCLNSSymbol::ToNSOF( TDCLNSOFEncoder* inEncoder ) const
{
	// R�cup�ration du flux de sortie.
	TDCLStream* theOutputStream = inEncoder->GetOutputStream();
	
	// Ecriture du type.
	theOutputStream->PutByte( KDCLNSOF::kSymbol );

	// Ecriture du nombre de caract�res.
	size_t nbChars = ::strlen( mString );
	theOutputStream->PutXLong( nbChars );
	
	// Puis les caract�res.
	size_t indexChars;
	for ( indexChars = 0; indexChars < nbChars; indexChars++ )
	{
		theOutputStream->PutByte( (KUInt8) mString[ indexChars ] );
	}
}

// ------------------------------------------------------------------------- //
//  * ToText( TDCLTextEncoder* ) const
// ------------------------------------------------------------------------- //
void
TDCLNSSymbol::ToText( TDCLTextEncoder* /* inEncoder */ ) const
{
}

// ------------------------------------------------------------------------- //
//  * ToPkg( TDCLPkgEncoder* ) const
// ------------------------------------------------------------------------- //
void
TDCLNSSymbol::ToPkg(
				TDCLPkgEncoder* inEncoder,
				KUInt32* ioOffset ) const
{
	// R�cup�ration du flux de sortie.
	TDCLStream* theOutputStream = inEncoder->GetOutputStream();
	
	KUInt32 nbBytes = ::strlen( mString ) + 1;
	KUInt32 theSize = nbBytes + 16;
	
	if (theSize > TDCLPkgEncoder::kMaxSize)
	{
		throw DCLLimitReachedError;
	}
	
	// �criture de l'ent�te.
	theOutputStream->PutLong(
		(theSize << TDCLPkgEncoder::kSizeShift)
		| TDCLPkgEncoder::kObjFlagHeader );
	
	theOutputStream->PutLong( 0 );
	
	// Classe sp�ciale.
	theOutputStream->PutLong( TDCLPkgEncoder::kSymbolClass );
	
	// Hash.
	theOutputStream->PutLong( mHashCode );
	
	// Cha�ne de caract�re.
	KUInt32 indexBytes;
	for ( indexBytes = 0; indexBytes < nbBytes; indexBytes++ )
	{
		theOutputStream->PutByte( (KUInt8) mString[ indexBytes ] );
	}
	
	*ioOffset += theSize;
}

// ==================================================================== //
//         THE LESSER-KNOWN PROGRAMMING LANGUAGES #13: SLOBOL           //
//                                                                      //
// SLOBOL is best known for the speed, or lack of it, of its compiler.  //
// Although many compilers allow you to take a coffee break while they  //
// compile, SLOBOL compilers allow you to travel to Bolivia to pick the //
// coffee.  Forty-three programmers are known to have died of boredom   //
// sitting at their terminals while waiting for a SLOBOL program to     //
// compile.  Weary SLOBOL programmers often turn to a related (but      //
// infinitely faster) language, COCAINE.                                //
// ==================================================================== //
