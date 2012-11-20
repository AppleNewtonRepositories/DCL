// ==============================
// Fichier:			TDCLNSFrame.cp
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
// The Original Code is TDCLNSFrame.cp.
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
// $Id: TDCLNSFrame.cp,v 1.11 2004/11/24 14:09:07 paul Exp $
// ===========

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Objects/TDCLNSFrame.h>

// C++
#include <new>

// ANSI C
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// DCL
#include <DCL/Exceptions/Errors/TDCLBadParamError.h>
#include <DCL/Exceptions/Errors/TDCLLimitReachedError.h>
#include <DCL/Exceptions/Errors/TDCLMemError.h>
#include <DCL/NS_Objects/Exchange/TDCLNSEncoder.h>
#include <DCL/NS_Objects/Exchange/TDCLNSOFDecoder.h>
#include <DCL/NS_Objects/Exchange/TDCLNSOFEncoder.h>
#include <DCL/NS_Objects/Exchange/TDCLPkgDecoder.h>
#include <DCL/NS_Objects/Exchange/TDCLPkgEncoder.h>
#include <DCL/NS_Objects/Exchange/TDCLXMLEncoder.h>
#include <DCL/NS_Objects/Objects/TDCLNSArray.h>
#include <DCL/NS_Objects/Objects/TDCLNSSymbol.h>
#include <DCL/NS_Objects/Objects/KDCLSYM.h>
#include <DCL/Streams/TDCLRandomAccessStream.h>
#include <DCL/Streams/TDCLStream.h>

// ------------------------------------------------------------------------- //
//  * TDCLNSFrame( void )
// ------------------------------------------------------------------------- //
TDCLNSFrame::TDCLNSFrame( void )
	:
		mLength( 0 ),
		mCapacity( 0 ),
		mKeys( nil ),
		mValues( nil ),
		mKeysAreSorted( true ),
		mIsFunction( false )
{
	mKeys = (TDCLNSRef*) ::malloc( kListChunkSize * sizeof (TDCLNSRef) );
	mValues = (TDCLNSRef*) ::malloc( kListChunkSize * sizeof (TDCLNSRef) );
	
	mCapacity = kListChunkSize;

	if ((mKeys == nil) || (mValues == nil))
	{
		throw DCLMemError;
	}
}

// ------------------------------------------------------------------------- //
//  * TDCLNSFrame( KUInt32 )
// ------------------------------------------------------------------------- //
TDCLNSFrame::TDCLNSFrame( KUInt32 inCapacity )
	:
		mLength( 0 ),
		mCapacity( inCapacity ),
		mKeys( nil ),
		mValues( nil ),
		mKeysAreSorted( true ),
		mIsFunction( false )
{
	mKeys = (TDCLNSRef*) ::malloc( inCapacity * sizeof (TDCLNSRef) );
	mValues = (TDCLNSRef*) ::malloc( inCapacity * sizeof (TDCLNSRef) );

	if (inCapacity > 0)
	{
		if ((mKeys == nil) || (mValues == nil))
		{
			throw DCLMemError;
		}
	}
}

// ------------------------------------------------------------------------- //
//  * TDCLNSFrame( const TDCLNSFrame& )
// ------------------------------------------------------------------------- //
TDCLNSFrame::TDCLNSFrame( const TDCLNSFrame& inCopy )
	:
		TDCLNSObject( inCopy ),
		mLength( inCopy.mLength ),
		mCapacity( inCopy.mLength ),
		mKeys( nil ),
		mValues( nil ),
		mKeysAreSorted( inCopy.mKeysAreSorted ),
		mIsFunction( inCopy.mIsFunction )
{
	// Copie des valeurs et des cl�s.
	KUInt32 nbPairs = mLength;
	mKeys = (TDCLNSRef*) ::malloc( nbPairs * sizeof (TDCLNSRef) );
	mValues = (TDCLNSRef*) ::malloc( nbPairs * sizeof (TDCLNSRef) );
	
	if (nbPairs > 0)
	{
		if ((mKeys == nil) || (mValues == nil))
		{
			throw DCLMemError;
		}

		KUInt32 indexPairs;
		for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
		{
			// Copie de la cl�.
			new ( &mKeys[indexPairs] ) TDCLNSRef( inCopy.mKeys[indexPairs] );

			// Copie de la valeur.
			new ( &mValues[indexPairs] ) TDCLNSRef( inCopy.mValues[indexPairs] );
		}
	}
}

// ------------------------------------------------------------------------- //
//  * ~TDCLNSFrame( void )
// ------------------------------------------------------------------------- //
TDCLNSFrame::~TDCLNSFrame( void )
{
	// Suppression des cl�s et des r�f�rences.
	if ((mKeys != nil) && (mValues != nil))
	{
		KUInt32 nbPairs = mLength;
		KUInt32 indexPairs;
		for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
		{
			mKeys[indexPairs].TDCLNSRef::~TDCLNSRef();
			mValues[indexPairs].TDCLNSRef::~TDCLNSRef();
		}
	
		::free( mKeys );
		::free( mValues );
	} else {
		// Echec lors de l'initialisation.
		if (mKeys != nil)
		{
			::free( mKeys );
		}

		if (mValues != nil)
		{
			::free( mValues );
		}
	}
}

// ------------------------------------------------------------------------- //
//  * operator = ( const TDCLNSFrame& inCopy )
// ------------------------------------------------------------------------- //
TDCLNSFrame&
TDCLNSFrame::operator = ( const TDCLNSFrame& inCopy )
{
	// Suppression des anciennes r�f�rences.
	KUInt32 nbPairs = mLength;
	KUInt32 indexPairs;
	for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
	{
		mKeys[indexPairs].TDCLNSRef::~TDCLNSRef();
		mValues[indexPairs].TDCLNSRef::~TDCLNSRef();
	}

	// Copie des nouvelles valeurs et des cl�s.
	nbPairs = inCopy.mLength;
	mLength = nbPairs;
	mKeys = (TDCLNSRef*) ::realloc( mKeys, nbPairs * sizeof (TDCLNSRef) );
	mValues = (TDCLNSRef*) ::realloc( mValues, nbPairs * sizeof (TDCLNSRef) );
	
	if (nbPairs > 0)
	{
		if ((mKeys == nil) || (mValues == nil))
		{
			throw DCLMemError;
		}

		for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
		{
			// Copie de la cl�.
			new ( &mKeys[indexPairs] ) TDCLNSRef( inCopy.mKeys[indexPairs] );

			// Copie de la valeur.
			new ( &mValues[indexPairs] ) TDCLNSRef( inCopy.mValues[indexPairs] );
		}
	}
	
	return *this;
}

// ------------------------------------------------------------------------- //
//  * IsFrame( void ) const
// ------------------------------------------------------------------------- //
Boolean
TDCLNSFrame::IsFrame( void ) const
{
	return true;
}

// ------------------------------------------------------------------------- //
//  * IsFunction( void ) const
// ------------------------------------------------------------------------- //
Boolean
TDCLNSFrame::IsFunction( void ) const
{
	return mIsFunction;
}

// ------------------------------------------------------------------------- //
//  * HasSlot( const TDCLNSSymbol& ) const
// ------------------------------------------------------------------------- //
Boolean
TDCLNSFrame::HasSlot( const TDCLNSSymbol& inSymbol ) const
{
	Boolean theResult = false;	// Supposons que la cl� ne soit pas l�.
	
	// Index de la cl�, si elle est dans le dictionnaire.
	KUInt32 indexKey;
	theResult = GetKeyIndex( inSymbol, &indexKey );
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * RemoveSlot( const TDCLNSSymbol& )
// ------------------------------------------------------------------------- //
Boolean
TDCLNSFrame::RemoveSlot( const TDCLNSSymbol& inSymbol )
{
	Boolean theResult = false;	// Supposons que la cl� ne soit pas l�.
	
	// Index de la cl�, si elle est dans le dictionnaire.
	KUInt32 indexKey;
	theResult = GetKeyIndex( inSymbol, &indexKey );
	
	if (theResult)
	{
		mValues[indexKey].TDCLNSRef::~TDCLNSRef();
		mKeys[indexKey].TDCLNSRef::~TDCLNSRef();
		
		mLength--;

		// Il faut donc tirer les cl�s/valeurs avant le point
		// de suppression avec un memmove (les zones se recouvrent).
		(void) ::memmove(
				(void*) &mKeys[indexKey],
				(const void*) &mKeys[indexKey + 1],
				(mLength - indexKey) * sizeof (TDCLNSRef) );
		(void) ::memmove(
				(void*) &mValues[indexKey],
				(const void*) &mValues[indexKey + 1],
				(mLength - indexKey) * sizeof (TDCLNSRef) );
		
		
		// Si la structure �tait une fonction et que l'�l�ment
		// supprim� est la classe, alors la structure n'est plus
		// une fonction.
		if (mIsFunction && (inSymbol == KDCLSYM::kSYMclass.ToSymbol()))
		{
			mIsFunction = false;
		}
	}
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * Get( const TDCLNSSymbol& ) const
// ------------------------------------------------------------------------- //
TDCLNSRef
TDCLNSFrame::Get( const TDCLNSSymbol& inSymbol ) const
{
	TDCLNSRef theResult;	// Supposons que la cl� ne soit pas l�.

	// Index de la cl�, si elle est dans le dictionnaire.
	KUInt32 indexKey;
	if (GetKeyIndex( inSymbol, &indexKey ))
	{
		theResult = mValues[indexKey];
	}
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * GetKey( KUInt32 ) const
// ------------------------------------------------------------------------- //
TDCLNSRef
TDCLNSFrame::GetKey( KUInt32 inIndex ) const
{
	if (inIndex >= mLength)
	{
		throw DCLBadParamError;
	}

	return mKeys[inIndex];
}

// ------------------------------------------------------------------------- //
//  * GetValue( KUInt32 ) const
// ------------------------------------------------------------------------- //
TDCLNSRef
TDCLNSFrame::GetValue( KUInt32 inIndex ) const
{
	if (inIndex >= mLength)
	{
		throw DCLBadParamError;
	}

	return mValues[inIndex];
}

// ------------------------------------------------------------------------- //
//  * Set( const TDCLNSRef&, const TDCLNSRef& )
// ------------------------------------------------------------------------- //
void
TDCLNSFrame::Set( const TDCLNSRef& inSymbol, const TDCLNSRef& inNewValue )
{
	TDCLNSSymbol& theSymbol = inSymbol.ToSymbol();

	// Index de la cl�, si elle est dans le dictionnaire.
	KUInt32 indexKey = mLength;
	if (GetKeyIndex( theSymbol, &indexKey ))
	{
		// Ceci appelle l'op�rateur d'assignation.
		// Lib�ration de l'ancienne valeur, copie de la nouvelle.
		mValues[indexKey] = inNewValue;
	} else {
		// Ici, il y a une petite astuce.
		// Si la structure n'est pas tri�e mais devrait l'�tre avec l'ajout
		// de la nouvelle paire, il faut la trier.
		
		// Agrandissement de la structure si n�cessaire.
		if (mLength == mCapacity)
		{
			mCapacity += kListChunkSize;
			mKeys = (TDCLNSRef*) ::realloc(
						mKeys,
						mCapacity * sizeof (TDCLNSRef) );
			mValues = (TDCLNSRef*) ::realloc(
						mValues,
						mCapacity * sizeof (TDCLNSRef) );
		}

		if (indexKey < mLength)
		{
			// Je rajoute la nouvelle cl� au milieu.
			// Il faut donc pousser les cl�s/valeurs avant le point
			// d'insertion avec un memmove (les zones se recouvrent).
			(void) ::memmove(
					(void*) &mKeys[indexKey + 1],
					(const void*) &mKeys[indexKey],
					(mLength - indexKey) * sizeof (TDCLNSRef) );
			(void) ::memmove(
					(void*) &mValues[indexKey + 1],
					(const void*) &mValues[indexKey],
					(mLength - indexKey) * sizeof (TDCLNSRef) );
		}
		mLength++;

		// Initialisation de ces �l�ments dans le tableau.
		// (c'est une fausse assignation, les �l�ments ici sont
		// des copies de ce qu'on a en indexKey + 1 ou les derniers
		// �l�ments non intialis�s).
		new ( &mKeys[indexKey] ) TDCLNSRef( inSymbol );
		new ( &mValues[indexKey] ) TDCLNSRef( inNewValue );
		
		// Tri si n�cessaire de la structure.
		if (!mIsFunction && !mKeysAreSorted && (mLength > kSortThreshold))
		{
			// Vue la taille de la liste, on peut y aller avec un insertion sort.
			KUInt32 indexRemoved;
			for (indexRemoved = 0; indexRemoved < mLength; indexRemoved++)
			{
				TDCLNSRef removedKey = mKeys[indexRemoved];
				TDCLNSRef removedValue = mValues[indexRemoved];
				TDCLNSSymbol& removedKeySym = removedKey.ToSymbol();
				
				KUInt32 indexInserted;
				for (
						indexInserted = indexRemoved;
						indexInserted > 0;
						indexInserted--)
				{
					// Si la cl� supprim�e est plus petite que la cl� pr�c�dente,
					// on inverse.
					if (
						removedKeySym.Compare(
							mKeys[indexInserted - 1].ToSymbol()) < 0)
					{
						mKeys[indexInserted] = mKeys[indexInserted - 1];
						mValues[indexInserted] = mValues[indexInserted - 1];
					} else {
						break;
					}
				}
				if (indexInserted != indexRemoved)
				{
					mKeys[indexInserted] = removedKey;
					mValues[indexInserted] = removedValue;
				}
			}
			
			mKeysAreSorted = true;
		}
	}
}

// ------------------------------------------------------------------------- //
//  * Clone( void ) const
// ------------------------------------------------------------------------- //
TDCLNSObject*
TDCLNSFrame::Clone( void ) const
{
	return new TDCLNSFrame( *this );
}

// ------------------------------------------------------------------------- //
//  * GetKeyIndex( const TDCLNSSymbol&, KUInt32* ) const
// ------------------------------------------------------------------------- //
Boolean
TDCLNSFrame::GetKeyIndex( const TDCLNSSymbol& inSymbol, KUInt32* outIndex ) const
{
	// On suppose que la cl� n'est pas pr�sente.
	Boolean theResult = false;
	
	// Boucle sur tous les symboles, sauf si le dictionnaire est tri�.
	// (remarque: on n'a pas d'index).
	KUInt32 indexKeys;			// index pour it�rer.
	KUInt32 nbKeys = mLength;	// Nombre de cl�s (plus rapide)
	Boolean sorted = mKeysAreSorted;	// Si les cl�s sont tri�es.
	
	for (indexKeys = 0; indexKeys < nbKeys; indexKeys++)
	{
		// Cet entier vaut 0 si les symboles sont �gaux,
		// > 0 si la cl� est sup�rieure au symbole, < 0 dans le cas inverse.
		int comparison = ((TDCLNSSymbol&) mKeys[indexKeys]).Compare( inSymbol );
		
		if (comparison == 0)
		{
			theResult = true;
			break;
		}
		
		if (sorted && (comparison > 0))
		{
			// Les cl�s sont tri�es et le param�tre est sup�rieur � une cl�:
			// il n'est pas dans le dictionnaire.
			break;
		}
	}
	
	// Dans tous les cas, on met dans outIndex l'index courant.
	// C'est l'index de la cl� si elle a �t� trouv�e, l'index suivant si la
	// structure est tri�e, la taille de la structure sinon.
	*outIndex = indexKeys;
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * ClassOf( void ) const
// ------------------------------------------------------------------------- //
TDCLNSRef
TDCLNSFrame::ClassOf( void ) const
{
	TDCLNSRef theResult;
	if (HasSlot( KDCLSYM::kSYMclass ))
	{
		theResult = Get( KDCLSYM::kSYMclass );
	} else {
		theResult = KDCLSYM::kSYMframe;
	}
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * PrimClassOf( void ) const
// ------------------------------------------------------------------------- //
TDCLNSRef
TDCLNSFrame::PrimClassOf( void ) const
{
	return KDCLSYM::kSYMframe;
}

// ------------------------------------------------------------------------- //
//  * SetClass( const TDCLNSRef& )
// ------------------------------------------------------------------------- //
void
TDCLNSFrame::SetClass( const TDCLNSRef& inClass )
{
	Set( KDCLSYM::kSYMclass, inClass );
}

// ------------------------------------------------------------------------- //
//  * FromNSOF( TDCLNSOFDecoder* )
// ------------------------------------------------------------------------- //
TDCLNSFrame*
TDCLNSFrame::FromNSOF( TDCLNSOFDecoder* inDecoder )
{
	TDCLStream* theStream = inDecoder->GetInputStream();
	
	KUInt32 nbPairs = theStream->GetXLong();
	KUInt32 indexPairs;

	// Cr�ation de l'objet.
	TDCLNSFrame* theResult = new TDCLNSFrame( nbPairs );
	
	// Cette structure n'est pas tri�e (vu que je vais ajouter les cl�s sans
	// appeler la m�thode Set).
	theResult->mKeysAreSorted = false;

	// Ajout de l'objet dans la liste des objets r�f�renc�s.
	inDecoder->AddObjectToList( TDCLNSRef( theResult ) );

	// Cr�ation des symboles
	// Attention au risque de fuite de m�moire. On se prot�ge avec un try/catch.
	try {
		for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
		{
			new ( &theResult->mKeys[ indexPairs ] )
				TDCLNSRef( inDecoder->GetNextObject() );
		}
	} catch ( ... ) {
		nbPairs = indexPairs;
		for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
		{
			theResult->mKeys[ indexPairs ].TDCLNSRef::~TDCLNSRef();
		}		

		throw;	// rethrow
	}

	// Cr�ation des valeurs
	try {
		for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
		{
			new ( &theResult->mValues[ indexPairs ] )
				TDCLNSRef( inDecoder->GetNextObject() );
		}
	} catch ( ... ) {
		KUInt32 nbValues = indexPairs;
		
		for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
		{
			theResult->mKeys[ indexPairs ].TDCLNSRef::~TDCLNSRef();
		}		
		for (indexPairs = 0; indexPairs < nbValues; indexPairs++)
		{
			theResult->mValues[ indexPairs ].TDCLNSRef::~TDCLNSRef();
		}
		
		throw;	// rethrow
	}
	
	// Mise � jour de la taille.
	theResult->mLength = nbPairs;
	
	// Est-ce une fonction?
	// (m�me test que sur le Newton)
	if (nbPairs >= 1)
	{
		if ((theResult->mKeys[0] == KDCLSYM::kSYMclass)
			&& ((theResult->mValues[0] == TDCLNSRef::Ref( 50 ))
			|| (theResult->mValues[0] == KDCLSYM::kSYMCodeBlock)))
		{
			theResult->mIsFunction = true;
		}
	}
	
	return theResult;
}

// ------------------------------------------------------------------------- //
//  * FromNSOFAsRect( TDCLNSOFDecoder* )
// ------------------------------------------------------------------------- //
TDCLNSFrame*
TDCLNSFrame::FromNSOFAsRect( TDCLNSOFDecoder* inDecoder )
{
	TDCLStream* theStream = inDecoder->GetInputStream();
	
	// Cr�ation de l'objet.
	TDCLNSFrame* theResult = new TDCLNSFrame( 4 );

	// Ajout de l'objet dans la liste des objets r�f�renc�s.
	inDecoder->AddObjectToList( TDCLNSRef( theResult ) );

	// Ici, on pourrait trier les cl�s.
	theResult->mKeysAreSorted = false;
	
	// Haut
	KUInt8 theByte =theStream->GetByte();
	new ( &theResult->mKeys[0] ) TDCLNSRef( KDCLSYM::kSYMtop );
	new ( &theResult->mValues[0] ) TDCLNSRef( TDCLNSRef::MakeInt( theByte ) );
	theResult->mLength++;

	// Gauche
	theByte = theStream->GetByte();
	new ( &theResult->mKeys[1] ) TDCLNSRef( KDCLSYM::kSYMleft );
	new ( &theResult->mValues[1] ) TDCLNSRef( TDCLNSRef::MakeInt( theByte ) );
	theResult->mLength++;

	// Bas
	theByte = theStream->GetByte();
	new ( &theResult->mKeys[2] ) TDCLNSRef( KDCLSYM::kSYMbottom );
	new ( &theResult->mValues[2] ) TDCLNSRef( TDCLNSRef::MakeInt( theByte ) );
	theResult->mLength++;

	// Droite
	theByte = theStream->GetByte();
	new ( &theResult->mKeys[3] ) TDCLNSRef( KDCLSYM::kSYMright );
	new ( &theResult->mValues[3] ) TDCLNSRef( TDCLNSRef::MakeInt( theByte ) );
	theResult->mLength++;

	return theResult;
}

// ------------------------------------------------------------------------- //
//  * FromPkg( TDCLPkgDecoder* )
// ------------------------------------------------------------------------- //
TDCLNSFrame*
TDCLNSFrame::FromPkg( TDCLPkgDecoder* inDecoder )
{
	TDCLRandomAccessStream* theStream = inDecoder->GetInputStream();

	// D�calage de l'objet.
	KUInt32 theObjectOffset = inDecoder->GetCurrentStreamOffset();
	
	// D'abord, c'est la structure avec les valeurs.

	// Taille
	KUInt32 theFirstLong = theStream->GetLong();
	KUInt32 nbPairs = ((theFirstLong >> TDCLPkgDecoder::kSizeShift) - 12) / 4;
	
	// On passe le deuxi�me long.
	(void) theStream->GetLong();

	// Cr�ation de l'objet. Je mets tout plein de NIL.
	TDCLNSFrame* theResult = new TDCLNSFrame( nbPairs );
	
	// Ajout de l'objet dans la liste des objets r�f�renc�s.
	inDecoder->AddObjectToList( TDCLNSRef( theResult ), theObjectOffset );

	// R�cup�ration de la carte.
	TDCLNSRef theMap = inDecoder->GetNextObject();
	
	TDCLNSArray& theMapAsArray = theMap.ToArray();
	KSInt32 theMapFlags = theMapAsArray.ClassOf().ToInt();
	
	theResult->mKeysAreSorted = (theMapFlags & TDCLPkgDecoder::kMapSorted) != 0;
	
	// Remplissage des cl�s � partir de la fin.
	KUInt32 indexPairs = nbPairs - 1;
	try {
		do {
			KUInt32 indexKeys = theMapAsArray.GetLength() - 1;
			for (; indexKeys > 0; indexKeys--)
			{
				new ( &theResult->mKeys[indexPairs--] )
					TDCLNSRef( theMapAsArray.Get(indexKeys) );
			}
			
			if (theMapAsArray.Get(0) == TDCLNSRef::kNILREF)
			{
				break;
			} else {
				theMapAsArray = theMapAsArray.Get(0).ToArray();
			}
		} while (true);
	} catch ( ... ) {
		for (; indexPairs < nbPairs; indexPairs++)
		{
			theResult->mKeys[ indexPairs ].TDCLNSRef::~TDCLNSRef();
		}		
		
		throw;	// rethrow
	}
	
	// Ensuite, on remplit les valeurs.
	try {
		for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
		{
			new ( &theResult->mValues[ indexPairs ] )
				TDCLNSRef( inDecoder->GetNextObject() );
		}
	} catch ( ... ) {
		KUInt32 nbValues = indexPairs;
		
		for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
		{
			theResult->mKeys[ indexPairs ].TDCLNSRef::~TDCLNSRef();
		}		
		for (indexPairs = 0; indexPairs < nbValues; indexPairs++)
		{
			theResult->mValues[ indexPairs ].TDCLNSRef::~TDCLNSRef();
		}
		
		throw;	// rethrow
	}
	
	// Mise � jour de la taille.
	theResult->mLength = nbPairs;
	
	// Est-ce une fonction?
	// (m�me test que sur le Newton)
	if ((nbPairs >= 1) && (!theResult->mKeysAreSorted))
	{
		if ((theResult->mKeys[0] == KDCLSYM::kSYMclass)
			&& ((theResult->mValues[0] == TDCLNSRef::Ref( 50 ))
			|| (theResult->mValues[0] == KDCLSYM::kSYMCodeBlock)))
		{
			theResult->mIsFunction = true;
		}
	}

	return theResult;
}

// ------------------------------------------------------------------------- //
//  * ToXML( TDCLXMLEncoder*, KUInt32 ) const
// ------------------------------------------------------------------------- //
void
TDCLNSFrame::ToXML(
				TDCLXMLEncoder*		inEncoder,
				KUInt32				inObjectID ) const
{
	// R�cup�ration du flux de sortie.
	TDCLStream* theOutputStream = inEncoder->GetOutputStream();
	
	// Balise de d�but avec l'ID.
	char theOutputStr[32]; 	// Suffisant.
	(void) ::sprintf( theOutputStr, "<frame id=\"n%lu\">", inObjectID );
	theOutputStream->PutString( theOutputStr );

	inEncoder->IncrementLevel();
	
	// Ensuite, chacun des �l�ments.
	KUInt32 nbPairs = mLength;
	KUInt32 indexPairs;
	for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
	{
		inEncoder->PutTabulations();
		
		// Balise de d�but, premi�re partie.
		theOutputStream->PutString( "<slot symbol=\"" );
		
		// Ajout du symbole.
		const char* theSymbol = ((TDCLNSSymbol&) mKeys[indexPairs]).GetString();
		inEncoder->Print8BitsWithEntities( (KUInt8*) theSymbol );

		// Balise de d�but, fin.
		theOutputStream->PutString( "\">" );

		inEncoder->IncrementLevel();
		inEncoder->PutTabulations();
		
		// Ajout de la valeur.
		inEncoder->AddObject( mValues[indexPairs] );
		
		inEncoder->DecrementLevel();
		inEncoder->PutTabulations();
		
		// Balise de fin.
		theOutputStream->PutString( "</slot>" );
	}
	
	inEncoder->DecrementLevel();
	inEncoder->PutTabulations();
	
	// Balise de fin.
	theOutputStream->PutString( "</frame>" );
}

// ------------------------------------------------------------------------- //
//  * ToNSOF( TDCLNSOFEncoder* ) const
// ------------------------------------------------------------------------- //
void
TDCLNSFrame::ToNSOF(
				TDCLNSOFEncoder* inEncoder ) const
{
	// R�cup�ration du flux de sortie.
	TDCLStream* theOutputStream = inEncoder->GetOutputStream();
	
	// C'est peut-�tre un rectangle.
	KUInt32 nbPairs = mLength;
	Boolean isRect = false;
	KUInt8 rectVals[4];
	if ( nbPairs == 4 )
	{
		do {
			TDCLNSRef theTop = Get( KDCLSYM::kSYMtop );
			if (!theTop.IsInt())
			{
				break;
			}
			
			KSInt32 theValue = theTop.ToInt();
			if ((theValue >= 0) && (theValue <= 255))
			{
				rectVals[0] = (KUInt8) theValue;
			}

			TDCLNSRef theLeft = Get( KDCLSYM::kSYMleft );
			if (!theLeft.IsInt())
			{
				break;
			}
			
			theValue = theLeft.ToInt();
			if ((theValue >= 0) && (theValue <= 255))
			{
				rectVals[1] = (KUInt8) theValue;
			}

			TDCLNSRef theBottom = Get( KDCLSYM::kSYMbottom );
			if (!theBottom.IsInt())
			{
				break;
			}
			
			theValue = theBottom.ToInt();
			if ((theValue >= 0) && (theValue <= 255))
			{
				rectVals[2] = (KUInt8) theValue;
			}

			TDCLNSRef theRight = Get( KDCLSYM::kSYMright );
			if (!theRight.IsInt())
			{
				break;
			}
			
			theValue = theRight.ToInt();
			if ((theValue >= 0) && (theValue <= 255))
			{
				rectVals[3] = (KUInt8) theValue;
			}
			
			isRect = true;
		} while ( false );
	}
	
	if (isRect)
	{
		// Ecriture du type.
		theOutputStream->PutByte( KDCLNSOF::kSmallRect );
		
		// Ecriture des 4 valeurs.
		int indexVals;
		for (indexVals = 0; indexVals < 4; indexVals++)
		{
			theOutputStream->PutByte( rectVals[indexVals] );
		}
	} else {
		// Ecriture du type.
		theOutputStream->PutByte( KDCLNSOF::kFrame );
	
		// Ecriture de la taille.
		theOutputStream->PutXLong( nbPairs );
	
		// Ecriture des cl�s.
		KUInt32 indexPairs;
		for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
		{
			// Ajout de la cl�.
			inEncoder->AddObject( mKeys[indexPairs] );
		}

		// Ecriture des valeurs
		for (indexPairs = 0; indexPairs < nbPairs; indexPairs++)
		{
			// Ajout des r�f�rences.
			inEncoder->AddObject( mValues[indexPairs] );
		}
	}
}

// ------------------------------------------------------------------------- //
//  * ToText( TDCLTextEncoder* ) const
// ------------------------------------------------------------------------- //
void
TDCLNSFrame::ToText(
				TDCLTextEncoder* /* inEncoder */ ) const
{
}

// ------------------------------------------------------------------------- //
//  * ToPkg( TDCLPkgEncoder* ) const
// ------------------------------------------------------------------------- //
void
TDCLNSFrame::ToPkg(
				TDCLPkgEncoder* inEncoder,
				KUInt32* ioOffset ) const
{
	// R�cup�ration du flux de sortie.
	TDCLStream* theOutputStream = inEncoder->GetOutputStream();
	
	// Les valeurs d'abord.
	// Ecriture du nombre d'�l�ments.
	KUInt32 nbItems = mLength;
	KUInt32 theSize = (nbItems * 4) + 12;

	KUInt32 mapOffset = *ioOffset + theSize;

	inEncoder->AlignOffset( &mapOffset );
	
	if (theSize > TDCLPkgEncoder::kMaxSize)
	{
		throw DCLLimitReachedError;
	}
	
	// �criture de l'ent�te.
	theOutputStream->PutLong(
		(theSize << TDCLPkgEncoder::kSizeShift)
		| TDCLPkgEncoder::kObjFlagHeader
		| TDCLPkgEncoder::kObjSlotted 
		| TDCLPkgEncoder::kObjFrame );
	
	theOutputStream->PutLong( 0 );
	
	// Pointeur sur la carte.
	theOutputStream->PutLong( mapOffset + 1 );
	
	// Mise � jour du d�calage.
	*ioOffset += 12;

	// Ajout des valeurs.
	KUInt32 indexItems;
	for ( indexItems = 0; indexItems < nbItems; indexItems++ )
	{
		inEncoder->AddObject( mValues[ indexItems ] );
	}

	// Alignement.
	inEncoder->AlignStream( ioOffset );
	
	KASSERT( *ioOffset == mapOffset );
	
	// Ensuite, les cl�s.
	KSInt32 theMapClass = 0;
	if (mKeysAreSorted)
	{
		theMapClass = TDCLPkgEncoder::kMapSorted;
	}
	if (HasSlot( KDCLSYM::kSYM_proto ))
	{
		theMapClass |= TDCLPkgEncoder::kMapProto;
	}
		
	theSize = (nbItems * 4) + 16;

	theOutputStream->PutLong(
		(theSize << TDCLPkgEncoder::kSizeShift)
		| TDCLPkgEncoder::kObjFlagHeader
		| TDCLPkgEncoder::kObjSlotted );
	
	theOutputStream->PutLong( 0 );

	// Mise � jour du d�calage.
	*ioOffset += 8;

	// Classe.
	inEncoder->AddObject( TDCLNSRef::MakeInt( theMapClass ) );

	// On n'a pas de super-map.
	inEncoder->AddObject( TDCLNSRef::kNILREF );

	// Ajout des symboles.
	for ( indexItems = 0; indexItems < nbItems; indexItems++ )
	{
		inEncoder->AddObject( mKeys[ indexItems ] );
	}
}

// ====================================================================== //
// Real computer scientists don't program in assembler.  They don't write //
// in anything less portable than a number two pencil.                    //
// ====================================================================== //
