// ==============================
// Fichier:			TDCLDockCmdNewtonName.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			02/02/2001
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
// The Original Code is TDCLDockCmdNewtonName.h.
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
// $Id: TDCLDockCmdNewtonName.h,v 1.5 2004/11/24 14:09:04 paul Exp $
// ===========

#ifndef __TDCLDOCKCMDNEWTONNAME__
#define __TDCLDOCKCMDNEWTONNAME__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/Dock_Commands/TDCLDockCommand.h>

// K
#include <K/Defines/UByteSex.h>

///
/// Classe pour la commande comprenant le nom du Newton. Cette commande
/// comprend aussi des informations sur le Newton.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.5 $
///
/// \test	aucun test d�fini.
///
class TDCLDockCmdNewtonName
	:
		public TDCLDockCommand
{
public:
	///
	/// Constructeur (unique) � partir des donn�es (copi�es)
	///
	/// \param inLength		taille des donn�es.
	/// \param inData		donn�es (copi�es)
	///
	TDCLDockCmdNewtonName( KUInt32 inLength, const void* inData );

	///
	/// Destructeur.
	/// Lib�re le nom du Newton.
	///
	virtual					~TDCLDockCmdNewtonName( void );

	///
	/// Accesseur sur l'ID du Newton.
	///
	/// \return l'ID du Newton.
	///
	inline	KUInt32			GetNewtonUniqueID( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fNewtonUniqueID );
		}

	///
	/// Accesseur sur l'identifiant du constructeur du Newton.
	///
	/// \return l'identifiant du constructeur.
	///
	inline	KUInt32			GetManufacturer( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fManufacturer );
		}

	///
	/// Accesseur sur le type de machine.
	///
	/// \return le type de machine.
	///
	inline	KUInt32			GetMachineType( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fMachineType );
		}

	///
	/// Accesseur sur la version de la ROM.
	///
	/// \return la version de la ROM.
	///
	inline	KUInt32			GetROMVersion( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fROMVersion );
		}

	///
	/// Accesseur sur le niveau de rustines sur la ROM.
	///
	/// \return le niveau de rustines sur la ROM.
	///
	inline	KUInt32			GetROMStage( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fROMStage );
		}

	///
	/// Accesseur sur la quantiti� de RAM install�e.
	///
	/// \return la quantiti� de RAM install�e.
	///
	inline	KUInt32			GetRAMSize( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fRAMSize );
		}

	///
	/// Accesseur sur la hauteur de l'�cran en pixels.
	///
	/// \return la hauteur de l'�cran.
	///
	inline	KUInt32			GetScreenHeight( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fScreenHeight );
		}

	///
	/// Accesseur sur la largeur de l'�cran en pixels.
	///
	/// \return la largeur de l'�cran.
	///
	inline	KUInt32			GetScreenWidth( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fScreenWidth );
		}

	///
	/// Accesseur sur la version de la rustine install�e.
	///
	/// \return la version de la rustine install�e.
	///
	inline	KUInt32			GetSystemUpdate( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fSystemUpdate );
		}

	///
	/// Accesseur sur la version du format NSOF g�r�e.
	///
	/// \return la version du format NSOF g�r�e.
	///
	inline	KUInt32			GetNOSVersion( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fNOSVersion );
		}

	///
	/// Accesseur sur la signature du magasin interne.
	///
	/// \return la signature du magasin interne.
	///
	inline	KUInt32			GetInternalStoreSig( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fInternalStoreSig );
		}

	///
	/// Accesseur sur la r�solution verticale de l'�cran.
	///
	/// \return la r�solution verticale de l'�cran.
	///
	inline	KUInt32			GetVertScreenRes( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fVertScreenRes );
		}

	///
	/// Accesseur sur la r�solution horizontale de l'�cran.
	///
	/// \return la r�solution horizontale de l'�cran.
	///
	inline	KUInt32			GetHoriScreenRes( void )
		{
			return mVersionInfo.fHoriScreenRes;
		}

	///
	/// Accesseur sur la profondeur de l'�cran (nombre de bits par pixel).
	///
	/// \return la profondeur de l'�cran.
	///
	inline	KUInt32			GetScreenDepth( void )
		{
			return UByteSex_FromBigEndian( mVersionInfo.fScreenDepth );
		}

	///
	/// Accesseur sur le nom du Newton (le nom du possesseur).
	///
	/// \return le nom du Newton.
	///
	inline	const KUInt16*	GetNewtonName( void )
		{
			return mNewtonName;
		}

	///
	/// Accesseur sur la longueur du nom du Newton.
	/// (en caract�res, sans le terminateur)
	///
	/// \return la longueur du nom du Newton.
	///
	inline	const KUInt32	GetNameLength( void )
		{
			return mNameLength;
		}

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLDockCmdNewtonName( const TDCLDockCmdNewtonName& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLDockCmdNewtonName& operator = ( const TDCLDockCmdNewtonName& inCopy );

	///
	/// Structure pour les informations sur le Newton.
	///
	struct SVersionInfo {
		KUInt32		fLength;			///< longeur de cette structure en octets.
		KUInt32		fNewtonUniqueID;	///< identifiant unique pour le Newton
		KUInt32		fManufacturer;		///< Comme dans Gestalt.
		KUInt32		fMachineType;		///< idem
		KUInt32		fROMVersion;		///< idem
		KUInt32		fROMStage;			///< idem
		KUInt32		fRAMSize;			///< idem
		KUInt32		fScreenHeight;		///< hauteur, en pixels.
		KUInt32		fScreenWidth;		///< largeur, en pixels.
		KUInt32		fSystemUpdate;		///< version de la rustine.
		KUInt32		fNOSVersion;		///< version du Newton Object System/NSOF
		KUInt32		fInternalStoreSig;	///< Signature du magasin interne.
		KUInt32		fVertScreenRes;		///< R�solution verticale (ppi)
		KUInt32		fHoriScreenRes;		///< R�solution horizontale (ppi)
		KUInt32		fScreenDepth;		///< Profondeur (en bpp)
		KUInt32		fSystemFlags;		///< [2.1] Drapeaux divers:
										///< 1 = has serial number
										///< 2 = has target protocol
		KUInt32		fSerialNumber[2];	///< [2.1] Num�ro de s�rie.
		KUInt32		fTargetProtocol;	///< [2.1] ?
	};
	
	/// \name Variables

	SVersionInfo		mVersionInfo;	///< Informations sur le Newton.
	const KUInt16*		mNewtonName;	///< M�moire tampon avec le nom du Newton.
	KUInt32				mNameLength;	///< Taille en caract�res (sans le terminateur).
};

#endif
		// __TDCLDOCKCMDNEWTONNAME__

// ========================================================================= //
// Play Rogue, visit exotic locations, meet strange creatures and kill them. //
// ========================================================================= //
