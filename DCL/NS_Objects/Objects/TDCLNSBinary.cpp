// ==============================
// Fichier:			TDCLNSBinary.cp
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
// The Original Code is TDCLNSBinary.cp.
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
// $Id: TDCLNSBinary.cp,v 1.10 2004/11/24 18:11:38 paul Exp $
// ===========

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Objects/TDCLNSBinary.h>

// ANSI C
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// K
#include <K/Misc/UBase64.h>
#include <K/Unicode/UUTF16Conv.h>

// DCL
#include <DCL/Exceptions/Errors/TDCLMemError.h>
#include <DCL/Exceptions/Errors/TDCLNotImplementedError.h>
#include <DCL/Exceptions/Errors/TDCLLimitReachedError.h>
#include <DCL/NS_Objects/Exchange/TDCLNSOFEncoder.h>
#include <DCL/NS_Objects/Exchange/TDCLNSOFDecoder.h>
#include <DCL/NS_Objects/Exchange/TDCLPkgEncoder.h>
#include <DCL/NS_Objects/Exchange/TDCLPkgDecoder.h>
#include <DCL/NS_Objects/Exchange/TDCLXMLEncoder.h>
#include <DCL/NS_Objects/Objects/TDCLNSString.h>
#include <DCL/NS_Objects/Objects/TDCLNSSymbol.h>
#include <DCL/NS_Objects/Objects/KDCLSYM.h>
#include <DCL/Streams/TDCLRandomAccessStream.h>
#include <DCL/Streams/TDCLStream.h>

#warning TODO: handle compressed binaries

// ------------------------------------------------------------------------- //
//  * TDCLNSBinary( const TDCLNSRef&, KUInt32 )
// ------------------------------------------------------------------------- //
TDCLNSBinary::TDCLNSBinary(
					const TDCLNSRef& inClass /* = KDCLSYM::kSYMbinary */,
					KUInt32 inSize /* = 0 */ )
	:
		mClass( inClass ),
		mBuffer( nil ),
		mBufferSize( inSize )
{
	mBuffer = ::malloc( inSize );
	
	if (inSize > 0)
	{
		if (mBuffer == nil)
		{
			throw DCLMemError;
		}
	}
}

// ------------------------------------------------------------------------- //
//  * TDCLNSBinary( const TDCLNSBinary& )
// ------------------------------------------------------------------------- //
TDCLNSBinary::TDCLNSBinary( const TDCLNSBinary& inCopy )
	:
		TDCLNSObject( inCopy ),
		mClass( inCopy.mClass ),
		mBuffer( nil ),
		mBufferSize( inCopy.mBufferSize )
{
	KUInt32 theSize = mBufferSize;
	mBuffer = ::malloc( theSize );
	
	if (theSize > 0)
	{
		if (mBuffer == nil)
		{
			throw DCLMemError;
		}
	
		// Copie des donn�es.
		(void) ::memcpy( mBuffer, inCopy.GetPointer(), theSize );
	}
}

// ------------------------------------------------------------------------- //
//  * TDCLNSBinary( const void*, KUInt32, const TDCLNSRef& )
// ------------------------------------------------------------------------- //
TDCLNSBinary::TDCLNSBinary(
				const void* inData,
				KUInt32 inLength,
				const TDCLNSRef& inClass /* = KDCLSYM::kSYMbinary */ )
	:
		mClass( inClass ),
		mBuffer( nil ),
		mBufferSize( inLength )
{
	// Allocation de la m�moire tampon.
	mBuffer = ::malloc( inLength );
	
	if (inLength > 0)
	{
		if (mBuffer == nil)
		{
			throw DCLMemError;
		}
	
		// Copie des donn�es.
		(void) ::memcpy( mBuffer, inData, inLength );
	}
}

// ------------------------------------------------------------------------- //
//  * TDCLNSBinary( TDCLStream*, KUInt32, const TDCLNSRef& )
// ------------------------------------------------------------------------- //
TDCLNSBinary::TDCLNSBinary(
				TDCLStream* inStream,
				KUInt32 inLength,
				const TDCLNSRef& inClass /* = KDCLSYM::kSYMbinary */ )
	:
		mClass( inClass ),
		mBuffer( nil ),
		mBufferSize( inLength )
{
	// Allocation de la m�moire tampon.
	mBuffer = ::malloc( inLength );
	
	if (inLength > 0)
	{
		if (mBuffer == nil)
		{
			throw DCLMemError;
		}
	
		// Lecture des donn�es.
		KUInt32 indexData;
		for (indexData = 0; indexData < inLength; indexData++)
		{
			((KUInt8*) mBuffer)[indexData] = inStream->GetByte();
		}
	}
}

// ------------------------------------------------------------------------- //
//  * TDCLNSBinary( void*, KUInt32, const TDCLNSRef& )
// ------------------------------------------------------------------------- //
TDCLNSBinary::TDCLNSBinary(
				void* inData,
				KUInt32 inLength,
				const TDCLNSRef& inClass )
	:
		mClass( inClass ),
		mBuffer( inData ),
		mBufferSize( inLength )
{
}

// ------------------------------------------------------------------------- //
//  * ~TDCLNSBinary( void )
// ------------------------------------------------------------------------- //
TDCLNSBinary::~TDCLNSBinary( void )
{
	if (mBuffer)
	{
		::free( mBuffer );
	}
}

// ------------------------------------------------------------------------- //
//  * operator = ( const TDCLNSBinary& inCopy )
// ------------------------------------------------------------------------- //
TDCLNSBinary&
TDCLNSBinary::operator = ( const TDCLNSBinary& inCopy )
{
	KUInt32 theSize = inCopy.mBufferSize;
	mBufferSize = theSize;
	mBuffer = ::realloc( mBuffer, theSize );
	
	if (theSize > 0)
	{
		if (mBuffer == nil)
		{
			throw DCLMemError;
		}
	
		// Copie des donn�es.
		(void) ::memcpy( mBuffer, inCopy.GetPointer(), theSize );
	}
	
	return *this;
}

// ------------------------------------------------------------------------- //
//  * IsBinary( void ) const
// ------------------------------------------------------------------------- //
Boolean
TDCLNSBinary::IsBinary( void ) const
{
	return true;
}

// ------------------------------------------------------------------------- //
//  * IsString( void ) const
// ------------------------------------------------------------------------- //
Boolean
TDCLNSBinary::IsString( void ) const
{
	Boolean theResult = false;
	if ((mClass == KDCLSYM::kSYMstring) || (mClass == KDCLSYM::kSYMname))
	{
		theResult = true;
	} else {
		if (mClass.IsSymbol())
		{
			theResult =
				((TDCLNSSymbol&) mClass).IsSubClass(KDCLSYM::kSYMstring);			
		}
	}
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * SetLength( KUInt32 )
// ------------------------------------------------------------------------- //
void
TDCLNSBinary::SetLength( KUInt32 inLength )
{
	mBuffer = ::realloc( mBuffer, inLength );

	if (inLength > 0)
	{
		if (mBuffer == nil)
		{
			throw DCLMemError;
		}
	}
	
	mBufferSize = inLength;
}

// ------------------------------------------------------------------------- //
//  * Clone( void ) const
// ------------------------------------------------------------------------- //
TDCLNSObject*
TDCLNSBinary::Clone( void ) const
{
	return new TDCLNSBinary( *this );
}

// ------------------------------------------------------------------------- //
//  * ClassOf( void ) const
// ------------------------------------------------------------------------- //
TDCLNSRef
TDCLNSBinary::ClassOf( void ) const
{
	return mClass;
}

// ------------------------------------------------------------------------- //
//  * PrimClassOf( void ) const
// ------------------------------------------------------------------------- //
TDCLNSRef
TDCLNSBinary::PrimClassOf( void ) const
{
	return KDCLSYM::kSYMbinary;
}

// ------------------------------------------------------------------------- //
//  * SetClass( const TDCLNSRef& )
// ------------------------------------------------------------------------- //
void
TDCLNSBinary::SetClass( const TDCLNSRef& inClass )
{
	mClass = inClass;
}

// ------------------------------------------------------------------------- //
//  * ToXML( TDCLXMLEncoder*, KUInt32 ) const
// ------------------------------------------------------------------------- //
void
TDCLNSBinary::ToXML(
				TDCLXMLEncoder*		inEncoder,
				KUInt32				inObjectID ) const
{
	// R�cup�ration du flux de sortie.
	TDCLStream* theOutputStream = inEncoder->GetOutputStream();

	char theOutputStr[32]; 	// Suffisant � chaque fois
							// (c'est pour les balises).

	// S'agit-il d'une cha�ne?
	Boolean isString = false;
	// Dois-je inclure la classe?
	Boolean putClass = true;
	
	if (mClass == KDCLSYM::kSYMstring)
	{
		isString = true;
		putClass = false;
	} else {
		isString = IsString();
	}
	
	if (isString)
	{
		(void) ::sprintf( theOutputStr, "<string id=\"n%lu\">", inObjectID );
		theOutputStream->PutString( theOutputStr );
	} else {
		(void) ::sprintf( theOutputStr, "<binary id=\"n%lu\">", inObjectID );
		theOutputStream->PutString( theOutputStr );
	}

	inEncoder->IncrementLevel();

	// Dois-je inclure une classe?
	if (putClass)
	{
		inEncoder->PutTabulations();
		theOutputStream->PutString( "<class>" );		
		inEncoder->AddObject( mClass );
		theOutputStream->PutString( "</class>" );
	}

	KUInt32 nbBytes = mBufferSize;

	// Balise de d�but pour la valeur.
	inEncoder->PutTabulations();
	theOutputStream->PutString( "<value>" );
	if (isString)
	{
		// Ai-je un terminateur dans la cha�ne?
		KUInt16* theData = (KUInt16*) mBuffer;
		KUInt32 strLen = nbBytes / 2;
		if (theData[ strLen ] == 0)
		{
			strLen--;
		}
		
		// Conversion en UTF-8 (au maximum 3 fois la taille).
		KUInt32 utf8Len = (3 * strLen) + 1;
		KUInt8* theUTF8Str = (KUInt8*) new KUInt8[ utf8Len ];

		// assert( ... != kInputExhausted)
		(void) UUTF16Conv::ToUTF8(
				theData, (size_t*) &strLen,
				theUTF8Str, (size_t*) &utf8Len );

		// Ajout du terminateur.
		theUTF8Str[utf8Len] = '\0';
		
		// Ecriture avec remplacement des caract�res sp�ciaux
		// par des entit�s.
		inEncoder->PrintUTF8WithEntities( theUTF8Str );

		// Lib�ration de la m�moire.
		delete [] theUTF8Str;
	} else {
		// Encodage en Base64.
		// Allocation de la m�moire tampon pour le Base64.
		KUInt32 theBase64Size = ((nbBytes + 2) / 3) * 4;
		
		KUInt8* theBase64Buffer = new KUInt8[ theBase64Size ];
		UBase64::Encode( mBuffer, theBase64Buffer, nbBytes );
		
		// Affichage sur radio OutputStream.
		// En fait, je vais le faire par paquets de 32 caract�res
		// (plus zoli).
		
		inEncoder->IncrementLevel();

		KUInt32 indexBase64;
		for ( indexBase64 = 0; indexBase64 < theBase64Size; indexBase64 += 32 )
		{
			inEncoder->PutTabulations();
			KUInt32 theAmount = theBase64Size - indexBase64;
			if (theAmount > 32)
			{
				theAmount = 32;
			}
			
			theOutputStream->Write(
							&theBase64Buffer[indexBase64], &theAmount );
		}
		
		// Lib�ration de la m�moire
		delete [] theBase64Buffer;
	
		// Retour d'un niveau et tabulations avant </value> pour le binaire.	
		inEncoder->DecrementLevel();
		inEncoder->PutTabulations();
	}
	// Balise de fin pour la valeur.
	theOutputStream->PutString( "</value>" );

	inEncoder->DecrementLevel();
	inEncoder->PutTabulations();

	// Balise de fin pour l'objet.
	if (isString)
	{
		theOutputStream->PutString( "</string>" );
	} else {
		theOutputStream->PutString( "</binary>" );
	}
}

// ------------------------------------------------------------------------- //
//  * FromNSOF( TDCLNSOFDecoder* )
// ------------------------------------------------------------------------- //
TDCLNSBinary*
TDCLNSBinary::FromNSOF( TDCLNSOFDecoder* inDecoder )
{
	TDCLStream* theStream = inDecoder->GetInputStream();
	
	KUInt32 nbBytes = theStream->GetXLong();
	
	// Cr�ation de l'objet (sans la classe parce que la classe
	// peut �tre ou contenir l'objet qui doit donc �tre dans la
	// liste des r�f�rences avant).
	TDCLNSBinary* theResult =
		new TDCLNSBinary( KDCLSYM::kSYMbinary, nbBytes );

	// Ajout de l'objet dans la liste des objets r�f�renc�s.
	inDecoder->AddObjectToList( TDCLNSRef( theResult ) );

	// Lecture de la classe.
	theResult->mClass = inDecoder->GetNextObject();

	// Lecture des donn�es.
	KUInt32 indexData;
	for (indexData = 0; indexData < nbBytes; indexData++)
	{
		((KUInt8*) theResult->mBuffer)[indexData] = theStream->GetByte();
	}

	return theResult;
}

// ------------------------------------------------------------------------- //
//  * FromNSOFAsLargeBinary( TDCLNSOFDecoder* )
// ------------------------------------------------------------------------- //
TDCLNSBinary*
TDCLNSBinary::FromNSOFAsLargeBinary( TDCLNSOFDecoder* inDecoder )
{
	TDCLStream* theStream = inDecoder->GetInputStream();
	
	// Cr�ation de l'objet (sans la classe parce que la classe
	// peut �tre ou contenir l'objet qui doit donc �tre dans la
	// liste des r�f�rences avant).
	TDCLNSBinary* theResult =
		new TDCLNSBinary( KDCLSYM::kSYMbinary );

	// Ajout de l'objet dans la liste des objets r�f�renc�s.
	inDecoder->AddObjectToList( TDCLNSRef( theResult ) );

	// Lecture de la classe.
	theResult->mClass = inDecoder->GetNextObject();

	// Lecture du drapeau compress�.
	KUInt8 isCompressed = theStream->GetByte();

	// Taille des donn�es.
	KUInt32 nbBytes = theStream->GetLong();

	// Nom du compresseur.
	KUInt32 nbCharsInCompanderName = theStream->GetLong();

	// Param�tres du compresseur.
	KUInt32 nbBytesOfCompanderParams = theStream->GetLong();

	// On ignore le long r�serv�.
	(void) theStream->GetLong();
	
	// Nom du compresseur
	KUInt8* theCompanderName =
						(KUInt8*) ::malloc( nbCharsInCompanderName + 1 );
	
	KUInt32 indexData;
	for (indexData = 0; indexData < nbCharsInCompanderName; indexData++)
	{
		theCompanderName[indexData] = theStream->GetByte();
	}

	// Terminateur.
	theCompanderName[nbCharsInCompanderName] = '\0';

	// Param�tres du compresseur.
	KUInt8* theCompanderParams =
						(KUInt8*) ::malloc( nbBytesOfCompanderParams );
	for (indexData = 0; indexData < nbBytesOfCompanderParams; indexData++)
	{
		theCompanderParams[indexData] = theStream->GetByte();
	}
	
	// Lecture des donn�es.
	KUInt8* theData = (KUInt8*) ::malloc( nbBytes );
	for (indexData = 0; indexData < nbBytes; indexData++)
	{
		theData[indexData] = theStream->GetByte();
	}

	try {
		// D�compression.
		if (!isCompressed)
		{
			theResult->SetLength( nbBytes );
			(void) ::memcpy( theResult->mBuffer, theData, nbBytes );
		} else {
#warning Could the Newton send us compressed binaries?
			throw DCLNotImplementedError;
		}
	} catch ( ... ) {
		::free( theCompanderName );
		::free( theCompanderParams );
		::free( theData );
		
		throw; // On relance.
	}

	::free( theCompanderName );
	::free( theCompanderParams );
	::free( theData );
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * FromPkg( TDCLPkgDecoder* )
// ------------------------------------------------------------------------- //
TDCLNSBinary*
TDCLNSBinary::FromPkg( TDCLPkgDecoder* inDecoder )
{
	TDCLStream* theStream = inDecoder->GetInputStream();

	// D�calage de l'objet.
	KUInt32 theObjectOffset = inDecoder->GetCurrentStreamOffset();
	
	// Taille
	KUInt32 theFirstLong = theStream->GetLong();
	KUInt32 nbBytes = (theFirstLong >> TDCLPkgDecoder::kSizeShift) - 12;
	
	// On passe le deuxi�me long.
	(void) theStream->GetLong();
	
	// Cr�ation de l'objet (sans la classe parce que la classe
	// peut �tre ou contenir l'objet qui doit donc �tre dans la
	// liste des r�f�rences avant).
	TDCLNSBinary* theResult =
		new TDCLNSBinary( KDCLSYM::kSYMbinary, nbBytes );

	// Ajout de l'objet dans la liste des objets r�f�renc�s.
	inDecoder->AddObjectToList( TDCLNSRef( theResult ), theObjectOffset );

	// Lecture de la classe.
	theResult->mClass = inDecoder->GetNextObject();

	// Lecture des donn�es.
	KUInt32 indexData;
	for (indexData = 0; indexData < nbBytes; indexData++)
	{
		((KUInt8*) theResult->mBuffer)[indexData] = theStream->GetByte();
	}

	return theResult;
}

// ------------------------------------------------------------------------- //
//  * ToNSOF( TDCLNSOFEncoder* ) const
// ------------------------------------------------------------------------- //
void
TDCLNSBinary::ToNSOF(
				TDCLNSOFEncoder* inEncoder ) const
{
	// R�cup�ration du flux de sortie.
	TDCLStream* theOutputStream = inEncoder->GetOutputStream();
	
	KUInt32 nbBytes = mBufferSize;

	// D�termination du type: il peut s'agir d'une cha�ne.
	if (mClass == KDCLSYM::kSYMstring)
	{
		// Ecriture du type.
		theOutputStream->PutByte( KDCLNSOF::kString );

		// Puis la taille des donn�es.
		theOutputStream->PutXLong( nbBytes );
	} else {
		// Ecriture du type.
		theOutputStream->PutByte( KDCLNSOF::kBinaryObject );

		// Puis la taille des donn�es.
		theOutputStream->PutXLong( nbBytes );
	
		// Ecriture de la classe
		inEncoder->AddObject( mClass );
	}
	
	// Puis les donn�es.
	KUInt8* theData = (KUInt8*) mBuffer;
	
	KUInt32 indexBytes;
	for ( indexBytes = 0; indexBytes < nbBytes; indexBytes++ )
	{
		theOutputStream->PutByte( theData[ indexBytes ] );
	}
}

// ------------------------------------------------------------------------- //
//  * ToText( TDCLTextEncoder* ) const
// ------------------------------------------------------------------------- //
void
TDCLNSBinary::ToText(
				TDCLTextEncoder* /* inEncoder */ ) const
{
}

// ------------------------------------------------------------------------- //
//  * ToPkg( TDCLPkgEncoder* ) const
// ------------------------------------------------------------------------- //
void
TDCLNSBinary::ToPkg(
				TDCLPkgEncoder* inEncoder,
				KUInt32* ioOffset ) const
{
	// R�cup�ration du flux de sortie.
	TDCLStream* theOutputStream = inEncoder->GetOutputStream();
	
	KUInt32 nbBytes = mBufferSize;
	KUInt32 theSize = nbBytes + 12;
	
	if (theSize > TDCLPkgEncoder::kMaxSize)
	{
		throw DCLLimitReachedError;
	}
	
	// �criture de l'ent�te.
	theOutputStream->PutLong(
		(theSize << TDCLPkgEncoder::kSizeShift)
		| TDCLPkgEncoder::kObjFlagHeader );
	
	theOutputStream->PutLong( 0 );
	
	*ioOffset += 8;

	// Classe.
	inEncoder->AddObject( mClass );
	
	// Donn�es binaires.
	KUInt8* theData = (KUInt8*) mBuffer;
	KUInt32 indexBytes;
	for ( indexBytes = 0; indexBytes < nbBytes; indexBytes++ )
	{
		theOutputStream->PutByte( theData[ indexBytes ] );
	}
	
	*ioOffset += nbBytes;
}

// ========================================================================= //
// Hacker's Guide To Cooking:                                                //
// 2 pkg. cream cheese (the mushy white stuff in silver wrappings that       //
//         doesn't really come from Philadelphia after all; anyway, about 16 //
//         oz.)                                                              //
// 1 tsp. vanilla  extract  (which is more alcohol than vanilla and pretty   //
//         strong so this part you *GOTTA* measure)                          //
// 1/4 cup sugar (but honey works fine too)                                  //
// 8 oz. Cool Whip (the fluffy stuff devoid of nutritional value that you    //
//         can squirt all over your friends and lick off...)                 //
// "Blend all together until creamy with no lumps."  This is where you get   //
//         to join(1) all the raw data in a big buffer and then filter it    //
//         through merge(1m) with the -thick option, I mean, it starts out   //
//         ultra lumpy and icky looking and you have to work hard to mix it. //
//         Try an electric beater if you have a cat(1) that can climb        //
//         wall(1s) to lick it off the ceiling(3m).                          //
// "Pour into a graham cracker crust..."  Aha, the BUGS section at last.     //
//         You just happened  to have a GCC sitting around under /etc/food,  //
//         right?  If not, don't panic(8), merely crumble a rand(3m) handful //
//         of innocent GCs into a suitable tempfile and mix in some melted   //
//         butter.                                                           //
// "...and  refrigerate for an hour."  Leave the  recipe's  stdout in a      //
//         fridge for 3.6E6 milliseconds while you work on cleaning up       //
//         stderr, and by time out your cheesecake will be ready for stdin.  //
// ========================================================================= //
