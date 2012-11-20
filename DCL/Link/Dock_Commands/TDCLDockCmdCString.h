// ==============================
// Fichier:			TDCLDockCmdCString.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			13/4/2003
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
// The Original Code is TDCLDockCmdCString.h.
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
// $Id: TDCLDockCmdCString.h,v 1.3 2004/11/24 14:09:03 paul Exp $
// ===========

#ifndef _TDCLDOCKCMDCSTRING_H
#define _TDCLDOCKCMDCSTRING_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/Dock_Commands/TDCLDockCommand.h>

// DCL
#include <DCL/NS_Objects/Objects/TDCLNSString.h>

///
/// Classe pour une commande du dock contenant une cha�ne UTF-16.
/// termin�e par un nul.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLDockCmdCString
	:
		public TDCLDockCommand
{
public:
	///
	/// Constructeur � partir d'une commande et d'une cha�ne.
	///
	/// \param inCommand	identifiant de la commande.
	/// \param inString		la cha�ne composant cette commande (copi�e)
	///
	TDCLDockCmdCString( KUInt32 inCommand, const KUInt16* inString );

	///
	/// Constructeur � partir d'une commande et d'une cha�ne NS.
	///
	/// \param inCommand	identifiant de la commande.
	/// \param inString		la cha�ne composant cette commande (copi�e)
	///
	TDCLDockCmdCString( KUInt32 inCommand, const TDCLNSString& inString );

	///
	/// Constructeur � partir d'une m�moire tampon et d'une taille.
	///
	/// \param inCommand	identifiant de la commande.
	/// \param inBufferSize	taille de la m�moire tampon
	/// \param inBuffer		m�moire tampon (copi�e)
	///
	TDCLDockCmdCString( KUInt32 inCommand, KUInt32 inBufferSize, void* inBuffer );

	///
	/// Destructeur.
	///
	virtual ~TDCLDockCmdCString( void );

	///
	/// Accesseur sur la cha�ne.
	///
	/// \return la cha�ne composant cette commande.
	///
	inline const KUInt16*	GetString( void ) const
		{
			return mString;
		}
protected:
	///
	/// M�thode pour r�cup�rer un pointeur sur les donn�es afin de les
	/// envoyer au Newton.
	///
	/// \return un pointeur sur la cha�ne
	///
	virtual const void*		GetData( void );
	
	///
	/// M�thode pour conna�tre la taille des donn�es afin de les envoyer
	/// au Newton.
	///
	/// \return mLength
	///
	virtual	KUInt32			GetLength( void ) const;

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLDockCmdCString( const TDCLDockCmdCString& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLDockCmdCString& operator = ( const TDCLDockCmdCString& inCopy );

	/// \name Variables

	KUInt16*	mString;		///< Cha�ne.
	KUInt32		mLength;		///< Taille de la cha�ne (avec le terminateur, en octets).
};

#endif
		// _TDCLDOCKCMDCSTRING_H

// =========================================================================== //
//         One day a student came to Moon and said, "I understand how to make  //
// a better garbage collector.  We must keep a reference count of the pointers //
// to each cons."                                                              //
//         Moon patiently told the student the following story -- "One day a   //
// student came to Moon and said, "I understand how to make a better garbage   //
// collector..."                                                               //
// =========================================================================== //
