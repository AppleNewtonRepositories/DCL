// ==============================
// Fichier:			TDCLTextEncoder.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			16/10/2002
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
// The Original Code is TDCLTextEncoder.h.
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
// $Id: TDCLTextEncoder.h,v 1.4 2004/11/24 14:09:07 paul Exp $
// ===========

#ifndef __TDCLTEXTENCODER__
#define __TDCLTEXTENCODER__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Exchange/TDCLNSEncoder.h>

///
/// Classe pour l'encodage sous forme de texte.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class TDCLTextEncoder
			:
				public TDCLNSEncoder
{
public:
	///
	/// Constructeur � partir d'un flux.
	///
	/// \param inStream		flux o� �crire les donn�es encod�es.
	///
	TDCLTextEncoder( TDCLStream* inStream );

	///
	/// Destructeur.
	///
	virtual ~TDCLTextEncoder( void );

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

	///
	/// D�termine si l'objet donn� peut �tre r�f�renc� par un "precedent".
	///
	/// Retourne \c false pour les symboles, \c true sinon.
	///
	/// \param inObject		objet consid�r�.
	/// \return \c true si l'objet peut �tre r�f�renc�, \c false sinon.
	///
	virtual Boolean	CanHavePrecedentID( TDCLNSObject* inObject );
};

#endif
		// __TDCLTEXTENCODER__

// ============================================================== //
// Computers are unreliable, but humans are even more unreliable. //
// Any system which depends on human reliability is unreliable.   //
//                 -- Gilb                                        //
// ============================================================== //
