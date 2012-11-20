// ==============================
// Fichier:			TDCLNSCodec.cp
// Projet:			Desktop Connection Library
//
// Cr�� le:			22/10/2002
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
// The Original Code is TDCLNSCodec.cp.
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
// $Id: TDCLNSCodec.cp,v 1.5 2004/11/24 14:09:05 paul Exp $
// ===========

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Exchange/TDCLNSCodec.h>

// C++
#include <new>

// ANSI C
#include <stdlib.h>

// ------------------------------------------------------------------------- //
//  * TDCLNSCodec( TDCLStream* )
// ------------------------------------------------------------------------- //
TDCLNSCodec::TDCLNSCodec( TDCLStream* inStream )
	:
		mList( nil ),
		mListAllocatedSize( 0 ),
		mListSize( 0 ),
		mStream( inStream )
{
	mList = (SListItem*) ::malloc( kListChunkSize * sizeof( SListItem ) );
	mListAllocatedSize = kListChunkSize;
}

// ------------------------------------------------------------------------- //
//  * ~TDCLNSCodec( void )
// ------------------------------------------------------------------------- //
TDCLNSCodec::~TDCLNSCodec( void )
{
	if (mList)
	{
		KUInt32 nbItems = mListSize;
		KUInt32 indexItems;
		for (indexItems = 0; indexItems < nbItems; indexItems++)
		{
			mList[indexItems].fObject.TDCLNSRef::~TDCLNSRef();
		}
	
		::free( mList );
	}
}

// ------------------------------------------------------------------------- //
//  * AddObjectToList( const TDCLNSRef&, KUIntPtr inCookie )
// ------------------------------------------------------------------------- //
KUInt32
TDCLNSCodec::AddObjectToList(
				const TDCLNSRef& inObject,
				KUIntPtr inCookie /* = 0 */ )
{
	// Redimension de la liste si n�cessaire.
	if (mListSize == mListAllocatedSize)
	{
		mListAllocatedSize += kListChunkSize;
		mList = (SListItem*)
			::realloc( mList, mListAllocatedSize * sizeof( SListItem ));
	}
	
	KUInt32 objectID = mListSize;
	
	mList[mListSize].fCookie = inCookie;
	new ( &mList[mListSize++].fObject ) TDCLNSRef( inObject );
	
	return objectID;
}

// ============================================================= //
// In computing, the mean time to failure keeps getting shorter. //
// ============================================================= //
