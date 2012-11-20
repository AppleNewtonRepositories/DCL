// ==============================
// Fichier:			TDCLNSEncoder.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			06/08/2002
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
// The Original Code is TDCLNSEncoder.h.
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
// $Id: TDCLNSEncoder.h,v 1.5 2004/11/24 14:09:05 paul Exp $
// ===========

#ifndef __TDCLNSENCODER__
#define __TDCLNSENCODER__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Exchange/TDCLNSCodec.h>

// DCL
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>

class TDCLNSObject;
class TDCLStream;

///
/// Classe pour l'encodage d'objets NS. Elle g�re la liste des objets avec les IDs.
/// Un objet peut demander l'ID courant ou chercher si un objet est d�j� dans la liste.
/// (les structures NewtonScript ne sont pas des arbres mais des DAG).
/// Cette classe est abstraite.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.5 $
///
/// \test	UTestNSOF
///
class TDCLNSEncoder
	:
		private TDCLNSCodec
{
public:
	///
	/// Destructeur.
	///
	virtual ~TDCLNSEncoder( void );

	///
	/// Ajoute un objet dans un flux donn�.
	/// Cette m�thode commence par regarder si l'objet est un imm�diat
	/// ou pas. Si c'est un imm�diat, elle appelle PutRef, sinon elle
	/// appelle PutObject.
	/// Cette m�thode ajoute l'objet ou une r�f�rence si l'objet est
	/// d�j� dans la liste.
	/// Remarque: la comparaison n'est faite que sur les pointeurs.
	///
	/// \param inObject		r�f�rence de l'objet � ajouter
	///
	virtual void	AddObject( const TDCLNSRef& inObject );

	///
	/// Accesseur sur le flux de sortie.
	///
	/// \return le flux de sortie sur lequel �crire les donn�es.
	///
	inline TDCLStream* GetOutputStream( void ) const
		{
			return GetStream();
		}

	///
	/// D�termine si un objet est d�j� dans la liste.
	///
	/// \param inObject			objet � chercher dans la liste.
	/// \param outObjectID		en sortie, identifiant de l'objet, non
	///							renseign� si \c nil.
	/// \param outObjectCookie	en sortie, biscuit associ� � l'objet (idem).
	/// \return \c true si l'objet a d�j� �t� encod�.
	///
	Boolean WasObjectEncoded(
				TDCLNSObject* inObject,
				KUInt32* outObjectID,
				KUIntPtr* outObjectCookie );

protected:
	///
	/// Constructeur � partir d'un flux.
	///
	/// \param inStream		flux o� �crire les donn�es encod�es.
	///
	TDCLNSEncoder( TDCLStream* inStream );

	///
	/// Met dans le flux la r�f�rence d'un objet d�j� encod�.
	///
	/// \param inRefID		r�f�rence de l'objet ajout�.
	/// \param inCookie		en entr�e, biscuit laiss� par PutObject
	///						lorsque l'objet a �t� ajout� la premi�re fois.
	///
	virtual void	PutPrecedent( KUInt32 inRefID, KUIntPtr inCookie ) = 0;

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
						KUIntPtr* outCookie ) = 0;

	///
	/// Met dans le flux un imm�diat donn�.
	///
	/// \param inRef		r�f�rence � ajouter.
	///
	virtual void	PutRef( const TDCLNSRef& inRef ) = 0;

	///
	/// D�termine si l'objet donn� peut �tre r�f�renc� par un "precedent".
	///
	/// Sert pour les symboles. NSOF dit oui, Text et XML disent non.
	/// Par d�faut, retourne \c true.
	///
	/// \param inObject		objet consid�r�.
	/// \return \c true si l'objet peut �tre r�f�renc�, \c false sinon.
	///
	virtual Boolean	CanHavePrecedentID( TDCLNSObject* inObject );
	
private:
	///
	/// Constructeur par d�faut non disponible.
	///
	TDCLNSEncoder( void );
};

#endif
		// __TDCLNSENCODER__

// ========================================================================= //
// A LISP programmer knows the value of everything, but the cost of nothing. //
//                 -- Alan Perlis                                            //
// ========================================================================= //
