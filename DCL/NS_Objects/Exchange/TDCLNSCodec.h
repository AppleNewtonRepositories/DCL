// ==============================
// Fichier:			TDCLNSCodec.h
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
// The Original Code is TDCLNSCodec.h.
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
// $Id: TDCLNSCodec.h,v 1.6 2004/11/24 14:09:05 paul Exp $
// ===========

#ifndef __TDCLNSCODEC__
#define __TDCLNSCODEC__

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>

class TDCLNSObject;
class TDCLStream;

///
/// Classe de base pour les encodeurs/d�codeurs d'objets NS sur un flux.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.6 $
///
/// \test	UTestNSOF
///
class TDCLNSCodec
{
public:
	///
	/// Destructeur.
	///
	virtual ~TDCLNSCodec( void );

	///
	/// Accesseur sur le flux associ�.
	///
	/// \return le flux o� on �crit/lit les donn�es.
	///
	inline TDCLStream* GetStream( void ) const
		{
			return mStream;
		}

protected:
	///
	/// Constructeur � partir d'un flux.
	///
	/// \param inStream		flux o� lire/�crire les donn�es.
	///
	TDCLNSCodec( TDCLStream* inStream );

	///
	/// Accesseur sur le nombre d'�l�ments.
	///
	/// \return le nombre d'�l�ments dans la liste.
	///
	inline KUInt32	GetListSize( void )
		{
			return mListSize;
		}

	///
	/// Accesseur sur un �l�ment donn�.
	///
	/// \param inIndex	index de l'�l�ment � retourner.
	/// \return le n-i�me �l�ment de la liste.
	///
	inline TDCLNSRef	GetListItemObject( KUInt32 inIndex )
		{
			return mList[inIndex].fObject;
		}

	///
	/// Accesseur sur le pointeur sur le biscuit.
	///
	/// \param inIndex	index du biscuit � retourner.
	/// \return un pointeur sur le n-i�me biscuit de la liste.
	///
	inline KUIntPtr*	GetListItemCookie( KUInt32 inIndex )
		{
			return &mList[inIndex].fCookie;
		}

	///
	/// Ajoute un objet dans la liste des objets.
	/// Retourne son ID.
	///
	/// \param inObject		objet � ajouter. Ceci doit �tre un pointeur.
	/// \param inCookie		biscuit � stocker avec l'objet.
	/// \return ID de cet objet.
	///
	KUInt32				AddObjectToList(
								const TDCLNSRef& inObject,
								KUIntPtr inCookie = 0 );

private:
	///
	/// Constructeur par d�faut non disponible.
	///
	TDCLNSCodec( void );

	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLNSCodec( const TDCLNSCodec& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLNSCodec& operator = ( const TDCLNSCodec& inCopy );

	///
	/// Constantes pour cette classe.
	///
	enum {
		kListChunkSize	= 10	///< Incr�ment de la liste lorsqu'elle est pleine.
	};

	///
	/// Structure pour la liste avec l'objet et le biscuit.
	///
	struct SListItem {
		TDCLNSRef	fObject;	///< Objet.
		KUIntPtr	fCookie;	///< Biscuit.
	};

	/// \name Variables Priv�es

	SListItem*		mList;				///< Liste des objets. L'indice dans
										///< cette liste est l'ID.
	KUInt32			mListAllocatedSize;	///< Nombre d'�l�ments que la liste
										///< peut contenir.
	KUInt32			mListSize;			///< Nombre d'�l�ments que la liste
										///< contient.
	TDCLStream*		mStream;			///< Flux utilis� par ce codec.
};

#endif
		// __TDCLNSCODEC__

// ========================================================================= //
// It is easier to write an incorrect program than understand a correct one. //
// ========================================================================= //
