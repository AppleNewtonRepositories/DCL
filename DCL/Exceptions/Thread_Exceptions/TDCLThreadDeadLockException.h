// ==============================
// Fichier:			TDCLThreadDeadLockException.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			30/4/2004
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
// The Original Code is TDCLThreadDeadLockException.h.
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
// $Id: TDCLThreadDeadLockException.h,v 1.3 2004/11/24 14:08:58 paul Exp $
// ===========

#ifndef _TDCLTHREADDEADLOCKEXCEPTION_H
#define _TDCLTHREADDEADLOCKEXCEPTION_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Exceptions/Thread_Exceptions/TDCLThreadException.h>

/// \name macros pour l'origine de l'exception
//@{
#if kDCLDebugFILEandLINE
	#define DCLThreadDeadLock							\
		TDCLThreadDeadLockException( __FILE__, __LINE__ )
	#define DCLPlatformThreadDeadLock( inError )		\
		TDCLThreadDeadLockException( __FILE__, __LINE__, inError )
#else
	#define DCLThreadDeadLock							\
		TDCLThreadDeadLockException()
	#define DCLPlatformThreadDeadLock( inError )		\
		TDCLThreadDeadLockException( inError )
#endif
//@}

///
/// Classe pour une exception d�tectant une �treinte mortelle.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLThreadDeadLockException
	:
		public TDCLThreadException
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
	TDCLThreadDeadLockException(
			const char* inFileName,
			KUInt32 inLine,
			KSInt32 inError = 0 );
#else
	///
	/// Constructeur � partir du code de l'erreur seul.
	///
	/// \param inError		code d'erreur
	///
	TDCLThreadDeadLockException( KSInt32 inError = 0 );
#endif
};

#endif
		// _TDCLTHREADDEADLOCKEXCEPTION_H

// =================================== //
// You're already carrying the sphere! //
// =================================== //
