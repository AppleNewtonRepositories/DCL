// ==============================
// Fichier:			TDCLException.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			11/02/2001
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
// The Original Code is TDCLException.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2001-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLException.h,v 1.5 2006/02/12 01:23:56 pguyot Exp $
// ===========

#ifndef _TDCLEXCEPTION_H
#define _TDCLEXCEPTION_H

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Headers/DCLErrorMessages.h>

///
/// Classe de base pour les exceptions dans la DCL.
///
/// Strat�gie pour les exceptions:
/// Il existe plusieurs classes d'exception, chaque classe correspondant � un
/// code qui peut-�tre obtenu ici.
///
/// Toutes les exceptions peuvent aussi avoir un code d'erreur venant de la
/// plateforme.
///
/// Suivant le drapeau \c kDCLDebugFILEandLINE, les exceptions comprennent
/// le nom du fichier et la ligne (il y a deux constructeurs).
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.5 $
///
/// \test	aucun test d�fini.
///
class TDCLException
{
public:

	///
	/// Codes pour les classes d'exception.
	///
	enum ExCode {
		/// \name Errors
		exBadParamError,		///< TDCLBadParamError
		exBadStateError,		///< TDCLBadStateError
		exLimitReachedError,	///< TDCLLimitReachedError
		exMemError,				///< TDCLMemError
		exNotImplementedError,	///< TDCLNotImplementedError
		exUnknownError,			///< TDCLUnknownError

		/// \name IO Exceptions
		
		exDoesntExist,			///< TDCLDoesntExistException
		exEOF,					///< TDCLEOFException
		exExistsAlready,		///< TDCLExistsAlreadyException
		exFull,					///< TDCLFullException
		exPermission,			///< TDCLPermissionException
		exPosition,				///< TDCLPositionException
		exReadOnly,				///< TDCLReadOnlyException
		exTimeout,				///< TDCLTimeoutException
		
		/// \name Link Exceptions
		exBadAppCmd,			///< TDCLBadAppCmdException
		exBadDockCmd,			///< TDCLBadDockCmdException
		exUnexpDockCmd,			///< TDCLUnexpDockCmdException
		
		/// \name Thread Exceptions
		exSemaphoreBusy,		///< TDCLSemaphoreBusyException
		exThreadActive,			///< TDCLThreadActiveException
		exThreadStopped,		///< TDCLThreadStoppedException
		exThreadDeadLock,		///< TDCLThreadDeadLockException
		
		/// \name Other Exceptions
		exClassCast,			///< TDCLClassCastException
		exNewton,				///< TDCLNewtonException
		exNotAvailable,			///< TDCLNotAvailableException
		exNS,					///< TDCLNSException
		exUserCancelled,		///< TDCLUserCancelledException

		/// \name Inspector Exceptions
		exBadInspectorCmd
	};

	///
	/// Accesseur sur le code d'exception
	///
	/// \return	le code d'exception.
	///
	inline	ExCode			GetExCode( void ) const
		{
			return mExCode;
		}
	
	///
	/// Accesseur sur le code d'erreur associ� avec l'exception.
	/// Ce code peut �tre z�ro si aucun code d'erreur n'est associ�.
	///
	/// \return	le code d'erreur.
	///
	inline	KSInt32			GetError( void ) const
		{
			return mError;
		}

	///
	/// D�termine le nom de l'exception.
	/// Par d�faut, utilise le code.
	///
	virtual const char*		GetExceptionName( void ) const;

#if kDCLDebugFILEandLINE

	///
	/// Accesseur sur le nom du fichier o� l'exception a �t�
	/// lanc�e.
	///
	/// \return	le nom du fichier. Celui-ci est normalement une constante
	///			g�n�r�e par le compilateur.
	///
	inline	const char*		GetFileName( void ) const
		{
			return mFileName;
		}

	///
	/// Accesseur sur le num�ro de ligne o� l'exception a �t�
	/// lanc�e.
	///
	/// \return	le num�ro de ligne.
	///
	inline	KUInt32			GetLine( void ) const
		{
			return mLine;
		}
#endif

#if kDCLDebugFILEandLINE
	///
	/// Constructeur par copie (si kDCLDebugFILEandLINE n'est pas � 1,
	/// on utilise le constructeur par copie par d�faut).
	///
	/// \param inCopy		objet � copier.
	///
	TDCLException( const TDCLException& inCopy );
#endif

	///
	/// Destructor.
	///
	virtual ~TDCLException( void ) {};

protected:
#if kDCLDebugFILEandLINE
	///
	/// Constructeur � partir du code de l'exception, d'un code d'erreur, du
	/// nom de fichier et du num�ro de ligne.
	///
	/// \param inExCode		code de l'exception.
	/// \param inError		code d'erreur.
	/// \param inFileName	nom du fichier. N'est pas copi�.
	/// \param inLine		num�ro de ligne.
	///
	TDCLException(
			ExCode inExCode,
			KSInt32 inError,
			const char* inFileName,
			KUInt32 inLine );
#else
	///
	/// Constructeur � partir du code de l'exception et de l'erreur seuls.
	///
	/// \param inExCode		code de l'exception.
	/// \param inError		code d'erreur
	///
	TDCLException( ExCode inExCode, KSInt32 inError );
#endif

private:
	///
	/// Constructeur par d�faut non disponible.
	///
	TDCLException( void );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLException& operator = ( const TDCLException& inCopy );

	/// \name Variables

	ExCode					mExCode;		///< Code de l'exception
	KSInt32					mError;			///< Erreur li�e � l'exception
#if kDCLDebugFILEandLINE
	const char*				mFileName;		///< Nom du fichier o� l'exception
											///< a �t� lanc�e
	KUInt32					mLine;			///< Num�ro de la ligne.
#endif
};

#endif
		// _TDCLEXCEPTION_H

// =============================================================================== //
// Real Programmers don't write in FORTRAN.  FORTRAN is for pipe stress freaks and //
// crystallography weenies.  FORTRAN is for wimp engineers who wear white socks.   //
// =============================================================================== //
