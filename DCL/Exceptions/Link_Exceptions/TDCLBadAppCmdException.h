// ==============================
// Fichier:			TDCLBadAppCmdException.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			12/5/2003
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
// The Original Code is TDCLBadAppCmdException.h.
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
// $Id: TDCLBadAppCmdException.h,v 1.3 2004/11/24 14:08:58 paul Exp $
// ===========

#ifndef _TDCLBADAPPCMDEXCEPTION_H
#define _TDCLBADAPPCMDEXCEPTION_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Exceptions/Link_Exceptions/TDCLLinkException.h>

/// \name macros pour l'origine de l'exception
//@{
#if kDCLDebugFILEandLINE
	#define DCLBadAppCmd							\
		TDCLBadAppCmdException( __FILE__, __LINE__ )
	#define DCLPlatformBadAppCmd( inError )			\
		TDCLBadAppCmdException( __FILE__, __LINE__, inError )
#else
	#define DCLBadAppCmd							\
		TDCLBadAppCmdException()
	#define DCLPlatformBadAppCmd( inError )			\
		TDCLBadAppCmdException( inError )
#endif
//@}

///
/// Classe pour une exception signifiant qu'une commande re�ue de l'application
/// n'a pas �t� trait�e parce que ne correspondant pas au lien.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLBadAppCmdException
	:
		public TDCLLinkException
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
	TDCLBadAppCmdException(
			const char* inFileName,
			KUInt32 inLine,
			KSInt32 inError = 0 );
#else
	///
	/// Constructeur � partir du code de l'erreur seul.
	///
	/// \param inError		code d'erreur
	///
	TDCLBadAppCmdException( KSInt32 inError = 0 );
#endif
};

#endif
		// _TDCLBADAPPCMDEXCEPTION_H

// ============================================================================= //
//         A novice asked the master: "I have a program that sometimes runs and  //
// sometimes aborts.  I have followed the rules of programming, yet I am totally //
// baffled. What is the reason for this?"                                        //
//         The master replied: "You are confused because you do not understand   //
// the Tao.  Only a fool expects rational behavior from his fellow humans.  Why  //
// do you expect it from a machine that humans have constructed?  Computers      //
// simulate determinism; only the Tao is perfect.                                //
//         The rules of programming are transitory; only the Tao is eternal.     //
// Therefore you must contemplate the Tao before you receive enlightenment."     //
//         "But how will I know when I have received enlightenment?" asked the   //
// novice.                                                                       //
//         "Your program will then run correctly," replied the master.           //
//                 -- Geoffrey James, "The Tao of Programming"                   //
// ============================================================================= //
