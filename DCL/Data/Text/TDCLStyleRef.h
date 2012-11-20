// ==============================
// Fichier:			TDCLStyleRef.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			19/3/2004
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
// The Original Code is TDCLStyleRef.h.
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
// $Id: TDCLStyleRef.h,v 1.4 2004/11/24 14:08:56 paul Exp $
// ===========

#ifndef _TDCLSTYLEREF_H
#define _TDCLSTYLEREF_H

#include <DCL/Headers/DCLDefinitions.h>

class TDCLFontSpecification;
class TDCLPicture;

///
/// Classe pour une r�f�rence sur un sp�cification de style texte ou une
/// image.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class TDCLStyleRef
{
public:
	///
	/// Constructeur par d�faut.
	///
	TDCLStyleRef( void );

	///
	/// Constructeur � partir d'une sp�cification de style de texte.
	///
	/// \param inTextStyle	style de texte.
	///
	TDCLStyleRef( TDCLFontSpecification* inTextStyle );

	///
	/// Constructeur � partir d'une image.
	///
	/// \param inPicture	image.
	///
	TDCLStyleRef( TDCLPicture* inPicture );

	///
	/// Destructeur.
	///
	~TDCLStyleRef( void );

	///
	/// Constructeur par copie.
	/// Incr�mente la r�f�rence.
	///
	/// \param inCopy		objet � copier
	///
	TDCLStyleRef( const TDCLStyleRef& inCopy );

	///
	/// Op�rateur d'assignation.
	/// Idem.
	///
	/// \param inCopy		objet � copier
	///
	TDCLStyleRef& operator = ( const TDCLStyleRef& inCopy );

	///
	/// D�termine si cette r�f�rence pointe sur un style de texte.
	///
	/// \return \c true si cette r�f�rence pointe sur un style de texte,
	///			\c false si elle pointe sur une image ou sur rien.
	///
	inline Boolean	IsFontSpecification( void ) const
		{
			return (mFontSpecification != nil);
		}

	///
	/// D�termine si cette r�f�rence pointe sur une image.
	///
	/// \return \c true si cette r�f�rence pointe sur une image,
	///			\c false si elle pointe sur un style ou sur rien.
	///
	inline Boolean	IsPicture( void ) const
		{
			return (mPicture != nil);
		}

	///
	/// Retourne la r�f�rence sous forme de style de texte
	/// (v�rifie que c'est un style de texte)
	///
	/// \throws TDCLClassCastException si la r�f�rence ne pointe pas sur
	///			une sp�cification de style de texte.
	///
	operator TDCLFontSpecification& () const;

	///
	/// Retourne la r�f�rence sous forme d'image.
	/// (v�rifie que c'est une image)
	///
	/// \throws TDCLClassCastException si la r�f�rence ne pointe pas sur
	///			une image.
	///
	operator TDCLPicture& () const;

private:
	/// \name Variables
	TDCLFontSpecification*	mFontSpecification;	///< Sp�cification sur le style
												///< de texte ou \c nil si ce
												///< n'est pas un style de
												///< texte.
	TDCLPicture*			mPicture;			///< Sp�cification sur
												///< l'image ou \c nil si ce
												///< n'est pas une image.
};

#endif
		// _TDCLSTYLEREF_H

// ============================================== //
// The Macintosh is Xerox technology at its best. //
// ============================================== //
