// ==============================
// Fichier:			UDCLMacCarbonUtils.h
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
// The Original Code is UDCLMacCarbonUtils.h.
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
// $Id: UDCLMacCarbonUtils.h,v 1.4 2004/11/24 14:09:01 paul Exp $
// ===========

#ifndef _UDCLMACCARBONUTILS_H
#define _UDCLMACCARBONUTILS_H

#include <DCL/Headers/DCLDefinitions.h>

// MacOS
#if TARGET_OS_MACOS
#include <Files.h>
#else
#include <CoreServices/CoreServices.h>
#endif

// DCL
#include <DCL/NS_Objects/Objects/TDCLNSString.h>

///
/// Classe pour des utilitaires sp�cifiques � Carbon.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class UDCLMacCarbonUtils
{
public:
	///
	/// Conversion d'un nom HFS+ en Unicode normal en utilisant les TEC.
	///
	/// \param inHFSPlusName	le nom HFS+
	/// \return le nom en unicode normal allou� avec malloc.
	///
	static KUInt16*		HFSPlusToNewtonUnicode(
							const HFSUniStr255* inHFSPlusName );

	///
	/// Conversion d'une cha�ne CF en cha�ne NS.
	///
	/// \param inCFStringRef	cha�ne CF � convertir
	/// \return une nouvelle cha�ne NS avec le contenu de la cha�ne CF.
	///
	static TDCLNSRef	CFToNSString( CFStringRef inCFStringRef );

	///
	/// Conversion d'une cha�ne NewtonScript en cha�ne CF.
	///
	/// \param inNSString	cha�ne NS � convertir
	/// \return une nouvelle cha�ne CF avec le contenu de la cha�ne NS.
	///
	static CFStringRef	NSToCFString( const TDCLNSString& inNSString );

	///
	/// Conversion d'une cha�ne CFStringRef en une cha�ne C allou�e avec
	/// \c malloc. La cha�ne C est encod�e en MacRoman.
	///
	/// \param inCFStringRef la cha�ne CF � convertir.
	/// \return une cha�ne C allou�e avec \c malloc
	///
	static const char*	CFToCString( CFStringRef inCFStringRef );
};

#endif
		// _UDCLMACCARBONUTILS_H

// ================================= //
// Vitamin C deficiency is apauling. //
// ================================= //