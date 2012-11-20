// ==============================
// Fichier:			TDCLAppCmdFile.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			10/4/2003
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
// The Original Code is TDCLAppCmdFile.h.
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
// $Id: TDCLAppCmdFile.h,v 1.3 2004/11/24 14:09:03 paul Exp $
// ===========

#ifndef _TDCLAPPCMDFILE_H
#define _TDCLAPPCMDFILE_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/App_Commands/TDCLAppCommand.h>

// DCL
#include <DCL/Interfaces/TDCLFSItemRef.h>

///
/// Classe pour une commande contenant une r�f�rence sur un fichier.
/// Elle permet d'�viter les fuites de m�moire, la r�f�rence sur le fichier
/// sera d�cr�ment�e.
/// L'acc�s au fichier peut se faire de deux mani�res:
/// - GetEventData (en transformant le pointeur en TDCLFSItem*)
/// - GetFileRef (le r�sultat est une r�f�rence)
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLAppCmdFile
	:
		public TDCLAppCommand
{
public:
	///
	/// Constructeur � partir d'un fichier.
	///
	/// \param inCommandKind	type de la commande.
	/// \param inCommandID		identifiant de la commande.
	/// \param inFileRef		r�f�rence sur le fichier.
	///
	TDCLAppCmdFile(
				EEventKind inCommandKind,
				EEventID inCommandID,
				TDCLFSItemRef& inFileRef );

	///
	/// Accesseur sur le fichier.
	///
	/// \return une r�f�rence sur le fichier
	///
	inline TDCLFSItemRef	GetFileRef( void )
		{
			return mFileRef;
		}

private:
	/// \name Variables
	TDCLFSItemRef		mFileRef;	/// R�f�rence sur le fichier.
};

#endif
		// _TDCLAPPCMDFILE_H

// ============================================================================= //
//                       THE STORY OF CREATION                                   //
//                                or                                             //
//                          THE MYTH OF URK                                      //
//                                                                               //
// In the beginning there was data.  The data was without form and null, and     //
// darkness was upon the face of the console; and the Spirit of IBM was moving   //
// over the face of the market.  And DEC said, "Let there be registers;" and     //
// there were registers.  And DEC saw that they carried; and DEC separated the   //
// data from the instructions.  DEC called the data Stack, and the instructions  //
// they called Code.  And there was evening and there was morning, one interrupt //
// ...                                                                           //
//                 -- Rico Tudor                                                 //
// ============================================================================= //
