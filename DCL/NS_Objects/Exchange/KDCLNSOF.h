// ==============================
// Fichier:			KDCLNSOF.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			15/10/2002
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
// The Original Code is KDCLNSOF.h.
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
// $Id: KDCLNSOF.h,v 1.3 2004/11/24 14:09:05 paul Exp $
// ===========

#ifndef __KDCLNSOF__
#define __KDCLNSOF__

#include <DCL/Headers/DCLDefinitions.h>

///
/// Classe pour les constantes sp�cifiques du format NSOF.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class KDCLNSOF
{
public:

	/// Constantes pour le format NSOF
	enum {
		kImmediate			= 0,
		kCharacter			= 1,
		kUnicodeCharacter	= 2,
		kBinaryObject		= 3,
		kArray				= 4,
		kPlainArray			= 5,
		kFrame				= 6,
		kSymbol				= 7,
		kString				= 8,
		kPrecedent			= 9,
		kNIL				= 10,
		kSmallRect			= 11,
		kLargeBinary		= 12,
		
		kNSOFVersion		= 0x02	///< Num�ro de version du format NSOF.
	};
};

#endif
		// __KDCLNSOF__

// ================================================= //
// Help!  I'm trapped in a Chinese computer factory! //
// ================================================= //
