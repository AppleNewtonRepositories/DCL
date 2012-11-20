// ==============================
// Fichier:			TDCLNSOFEncoder.h
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
// The Original Code is TDCLNSOFEncoder.h.
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
// $Id: TDCLNSOFEncoder.h,v 1.4 2004/11/24 14:09:05 paul Exp $
// ===========

#ifndef __TDCLNSOFENCODER__
#define __TDCLNSOFENCODER__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Exchange/KDCLNSOF.h>
#include <DCL/NS_Objects/Exchange/TDCLNSEncoder.h>

///
/// Classe pour l'encodage au format NSOF.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	UTestNSOF
///
class TDCLNSOFEncoder
	:
		public TDCLNSEncoder,
		public KDCLNSOF
{
public:
	///
	/// Constructeur � partir d'un flux.
	///
	/// \param inStream		flux utilis� par cet encodeur.
	///
	TDCLNSOFEncoder( TDCLStream* inStream );

	///
	/// Destructeur.
	///
	virtual ~TDCLNSOFEncoder( void );

protected:
	///
	/// Met dans le flux la r�f�rence d'un objet d�j� encod�.
	///
	/// \param inRefID		r�f�rence de l'objet ajout�.
	/// \param inCookie		en entr�e, biscuit laiss� par PutObject
	///						lorsque l'objet a �t� ajout� la premi�re fois.
	///
	virtual void	PutPrecedent( KUInt32 inRefID, KUIntPtr inCookie );

	///
	/// Met dans le flux un objet donn�.
	///
	/// \param inObject		objet � ajouter.
	/// \param inObjectID	ID de l'objet � ajouter, -1 si CanHavePrecedentID
	///						a retourn� \c false.
	/// \param outCookie	en sortie, biscuit pass� par la suite �
	///						PutPrecedent, \c nil si CanHavePrecedentID a
	///						retourn� \c false.
	///
	virtual void	PutObject(
						const TDCLNSObject* inObject,
						KUInt32 inObjectID,
						KUIntPtr* outCookie );
	///
	/// Met dans le flux une r�f�rence ou un imm�diat donn�s.
	///
	/// \param inRef		r�f�rence � ajouter.
	///
	virtual void	PutRef( const TDCLNSRef& inRef );
};

#endif
		// __TDCLNSOFENCODER__

// ============================================================================ //
// Build a system that even a fool can use and only a fool will want to use it. //
// ============================================================================ //
