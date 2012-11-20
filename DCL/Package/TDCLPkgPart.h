// ==============================
// Fichier:			TDCLPkgPart.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			6/4/2004
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
// The Original Code is TDCLPkgPart.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLPkgPart.h,v 1.4 2004/11/24 14:09:08 paul Exp $
// ===========

#ifndef _TDCLPKGPART_H
#define _TDCLPKGPART_H

#include <DCL/Headers/DCLDefinitions.h>

///
/// Classe pour une partie dans un paquet.
/// La partie est repr�sent�e par une m�moire tampon tant qu'elle
/// n'est pas analys�e.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class TDCLPkgPart
{
public:
	///
	/// Constructeur par d�faut.
	/// L'ensemble des donn�es est vide.
	///
	TDCLPkgPart( void );

	///
	/// Constructeur � partir de donn�es.
	/// Les donn�es sont copi�es.
	///
	/// \param inOffset	d�calage dans le paquet.
	/// \param inData	donn�es (copi�es)
	/// \param inSize	taille des donn�es.
	///
	TDCLPkgPart( KUInt32 inOffset, const void* inData, KUInt32 inSize );

	///
	/// Destructeur.
	///
	virtual ~TDCLPkgPart( void );

	///
	/// D�termine si la partie est un objet NewtonScript, i.e.
	/// si cette partie est de la classe TDCLPkgNOSPart.
	/// Par d�faut, non.
	///
	/// \return \c true si l'objet est de la classe TDCLPkgNOSPart
	///
	virtual Boolean		IsNOSPart( void ) const;

	///
	/// D�termine la taille de la partie.
	/// R�-encode les donn�es si n�cessaire.
	///
	/// \param inOffset		d�calage par rapport au d�but du paquet.
	/// \return la taille des donn�es.
	///
	KUInt32				GetSize( KUInt32 inOffset ) const;

	///
	/// R�cup�re un pointeur sur les donn�es.
	/// R�-encode les donn�es si n�cessaire.
	///
	/// \param inOffset		d�calage par rapport au d�but du paquet.
	/// \return un pointeur sur les donn�es.
	///
	const void*			GetBuffer( KUInt32 inOffset ) const;

	///
	/// D�termine la taille de la partie.
	/// R�-encode les donn�es si n�cessaire.
	///
	/// \return la taille des donn�es.
	///
	inline KUInt32		GetSize( void ) const
		{
			return GetSize( mOffset );
		}

	///
	/// R�cup�re un pointeur sur les donn�es.
	/// R�-encode les donn�es si n�cessaire.
	///
	/// \return un pointeur sur les donn�es.
	///
	inline const void*	GetBuffer( void ) const
		{
			return GetBuffer( mOffset );
		}

	///
	/// R�cup�re le d�calage dans le paquet.
	///
	/// \return le d�calage dans le paquet.
	///
	inline KUInt32		GetOffset( void ) const
		{
			return mOffset;
		}

protected:
	///
	/// D�termine la taille de la partie afin de la d�coder.
	///
	/// \return la taille des donn�es.
	///
	inline KUInt32		DoGetSize( void ) const
		{
			return mSize;
		}

	///
	/// R�cup�re un pointeur sur les donn�es afin de les d�coder.
	///
	/// \return un pointeur sur les donn�es.
	///
	inline const void*	DoGetBuffer( void ) const
		{
			return mBuffer;
		}

private:
	///
	/// D�termine si les donn�es d�pendent du d�calage dans le paquet.
	/// Par d�faut, non (retourne \c false).
	///
	/// \return \c true si les donn�es d�pendent du d�calage dans le paquet.
	///
	virtual Boolean IsOffsetDependant( void ) const;

	///
	/// D�termine si la partie a �t� modifi�e et doit �tre r�-encod�e.
	/// Par d�faut, non.
	///
	/// \return \c true si les donn�es ont �t� modifi�es et doivent �tre
	///			r�-encod�es.
	///
	virtual Boolean IsDirty( void ) const;

	///
	/// Encode la partie pour un d�calage donn� (la d�code si n�cessaire).
	/// Par d�faut, ne fait rien.
	///
	/// \param inOffset		d�calage dans le paquet.
	/// \param ioBuffer		pointeur sur les donn�es (allou� avec malloc)
	/// \param ioSize		taille des donn�es (en entr�e et en sortie)
	///
	virtual void Encode(
					KUInt32 inOffset,
					void** ioBuffer,
					KUInt32* ioSize ) const;

	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLPkgPart( const TDCLPkgPart& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLPkgPart& operator = ( const TDCLPkgPart& inCopy );

	/// \name Variables
	mutable KUInt32		mOffset;			///< D�calage original.
	mutable void*		mBuffer;			///< Pointeur sur la m�moire tampon.
	mutable KUInt32		mSize;				///< Taille de la partie.
};

#endif
		// _TDCLPKGPART_H

// ======================================================================= //
// The nicest thing about the Alto is that it doesn't run faster at night. //
// ======================================================================= //
