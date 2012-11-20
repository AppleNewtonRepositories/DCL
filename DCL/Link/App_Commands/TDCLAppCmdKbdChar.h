// ==============================
// Fichier:			TDCLAppCmdKbdChar.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			11/4/2003
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
// The Original Code is TDCLAppCmdKbdChar.h.
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
// $Id: TDCLAppCmdKbdChar.h,v 1.3 2004/11/24 14:09:03 paul Exp $
// ===========

#ifndef _TDCLAPPCMDKBDCHAR_H
#define _TDCLAPPCMDKBDCHAR_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/App_Commands/TDCLAppCommand.h>

///
/// Classe pour une commande pour envoyer un seul caract�re au Newton.
/// Ce caract�re peut comprendre une touche et un code pour savoir si la
/// touche pomme �tait enfonc�e (en th�orie).
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLAppCmdKbdChar
	:
		public TDCLAppCommand
{
public:
	///
	/// Constructeur � partir de la touche et de drapeaux pour indiquer
	/// les touches modificatrices.
	///
	/// \param inChar		caract�re
	/// \param inFlags		�tat de la touche. Permet en th�orie de dire que
	///						la touche commande est enfonc�e, mais le Newton
	///						ne semble pas le g�rer.
	///
	TDCLAppCmdKbdChar( KUInt16 inChar, KUInt16 inFlags );

private:
	/// \name Variables
	KUInt16			mData[2];	///< Donn�es pour cette commande.
};

#endif
		// _TDCLAPPCMDKBDCHAR_H

// ==================================================================== //
// I am not now, nor have I ever been, a member of the demigodic party. //
//                 -- Dennis Ritchie                                    //
// ==================================================================== //
