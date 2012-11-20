// ==============================
// Fichier:			TDCLAppCmdString.h
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
// The Original Code is TDCLAppCmdString.h.
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
// $Id: TDCLAppCmdString.h,v 1.3 2004/11/24 14:09:03 paul Exp $
// ===========

#ifndef _TDCLAPPCMDSTRING_H
#define _TDCLAPPCMDSTRING_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/App_Commands/TDCLAppCommand.h>

///
/// Classe pour une commande contenant une cha�ne. La cha�ne est copi�e
/// et la copie est lib�r�e avec cette commande.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLAppCmdString
	:
		public TDCLAppCommand
{
public:
	///
	/// Constructeur � partir d'une cha�ne.
	///
	/// \param inCommandKind	Type de la commande.
	/// \param inCommandID		Identifiant de la commande
	/// \param inString			cha�ne (copi�e)
	///
	TDCLAppCmdString(
				EEventKind inCommandKind,
				EEventID inCommandID,
				const KUInt16* inString );

	///
	/// Destructeur.
	/// Lib�re la cha�ne.
	///
	virtual ~TDCLAppCmdString( void );
};

#endif
		// _TDCLAPPCMDSTRING_H

// ============================================================= //
// C++ is the best example of second-system effect since OS/360. //
// ============================================================= //
