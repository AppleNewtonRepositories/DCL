// ==============================
// Fichier:			TDCLFSItemRef.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			9/4/2003
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
// The Original Code is TDCLFSItemRef.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2003-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLFSItemRef.h,v 1.3 2004/11/24 14:08:59 paul Exp $
// ===========

#ifndef _TDCLFSITEMREF_H
#define _TDCLFSITEMREF_H

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Exceptions/TDCLClassCastException.h>

// Pr�-d�clarations
class TDCLFSItem;
class TDCLFile;
class TDCLFolder;

///
/// Classe pour une r�f�rence sur un objet de type TDCLFSItem.
/// Ceci permet d'�viter les fuites de m�moire.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLFSItemRef
{
public:
	///
	/// Constructeur � partir d'un objet TDCLFSItem.
	///
	/// \param inItem	objet TDCLFSItem � r�f�rencer
	///
	TDCLFSItemRef( TDCLFSItem* inItem = nil );

	///
	/// Destructeur.
	///
	~TDCLFSItemRef( void );

	///
	/// Constructeur par copie.
	/// Incr�mente la r�f�rence.
	///
	/// \param inCopy		objet � copier
	///
	TDCLFSItemRef( const TDCLFSItemRef& inCopy );

	///
	/// Op�rateur d'assignation.
	/// Idem.
	///
	/// \param inCopy		objet � copier
	///
	TDCLFSItemRef& operator = ( const TDCLFSItemRef& inCopy );

	///
	/// Op�rateur de d�r�f�rencement.
	/// Retourne l'objet TDCLFSItem
	///
	inline TDCLFSItem& operator * () const
		{
			return *mFSItem;
		}

	///
	/// Op�rateur de d�r�f�rencement.
	/// Retourne l'objet TDCLFSItem
	///
	inline TDCLFSItem* operator -> () const
		{
			return mFSItem;
		}

	///
	/// Retourne l'objet TDCLFSItem sous forme de fichier
	/// (v�rifie que c'est un fichier)
	///
	/// \throws TDCLClassCastException si l'objet n'est pas un fichier.
	///
	operator TDCLFile* () const;

	///
	/// Retourne l'objet TDCLFSItem sous forme de dossier
	/// (v�rifie que c'est un dossier)
	///
	/// \throws TDCLClassCastException si l'objet n'est pas un dossier.
	///
	operator TDCLFolder* () const;

	///
	/// Accesseur sur l'objet TDCLFSItem.
	///
	inline TDCLFSItem* GetFSItem( void ) const
		{
			return mFSItem;
		}

private:
	/// \name Variables
	TDCLFSItem*		mFSItem;	///< Objet r�f�renc�.
};

#endif
		// _TDCLFSITEMREF_H

// =================================== //
// The world is not octal despite DEC. //
// =================================== //
