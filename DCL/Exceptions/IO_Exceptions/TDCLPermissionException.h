// ==============================
// Fichier:			TDCLPermissionException.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			31/7/2003
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
// The Original Code is TDCLPermissionException.h.
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
// $Id: TDCLPermissionException.h,v 1.3 2004/11/24 14:08:57 paul Exp $
// ===========

#ifndef _TDCLPERMISSIONEXCEPTION_H
#define _TDCLPERMISSIONEXCEPTION_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Exceptions/IO_Exceptions/TDCLIOException.h>

/// \name macros pour l'origine de l'exception
//@{
#if kDCLDebugFILEandLINE
	#define DCLPermission						\
		TDCLPermissionException( __FILE__, __LINE__ )
	#define DCLPlatformPermission( inError )		\
		TDCLPermissionException( __FILE__, __LINE__, inError )
#else
	#define DCLPermission						\
		TDCLPermissionException()
	#define DCLPlatformPermission( inError )		\
		TDCLPermissionException( inError )
#endif
//@}

///
/// Classe pour une exception signifiant que l'op�ration a �chou� parce qu'on n'a pas les droits
/// n�cessaires.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLPermissionException
	:
		public TDCLIOException
{
public:
#if kDCLDebugFILEandLINE
	///
	/// Constructeur � partir du code de l'erreur, du nom de fichier
	/// et du num�ro de ligne.
	///
	/// \param inFileName	nom du fichier. N'est pas copi�.
	/// \param inLine		num�ro de ligne.
	/// \param inError		code d'erreur
	///
	TDCLPermissionException(
			const char* inFileName,
			KUInt32 inLine,
			KSInt32 inError = 0 );
#else
	///
	/// Constructeur � partir du code de l'erreur seul.
	///
	/// \param inError		code d'erreur
	///
	TDCLPermissionException( KSInt32 inError = 0 );
#endif
};

#endif
		// _TDCLPERMISSIONEXCEPTION_H

// ===================================== //
// Multics is security spelled sideways. //
// ===================================== //
