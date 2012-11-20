// ==============================
// Fichier:			TDCLDockCmdNSObject.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			17/01/2002
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
// The Original Code is TDCLDockCmdNSObject.h.
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
// $Id: TDCLDockCmdNSObject.h,v 1.4 2004/11/24 14:09:04 paul Exp $
// ===========

#ifndef __TDCLDOCKCMDNSOBJECT__
#define __TDCLDOCKCMDNSOBJECT__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/Dock_Commands/TDCLDockCommand.h>

// DCL
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>

///
/// Classe pour une commande du Dock dont les donn�es sont un objet NewtonScript.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class TDCLDockCmdNSObject
	:
		public TDCLDockCommand
{
public:
	///
	/// Constructeur par d�faut.
	///
	TDCLDockCmdNSObject( void );

	///
	/// Constructeur pour l'envoi d'un objet NewtonScript � partir
	/// d'une r�f�rence.
	///
	/// \param inCommand	code d�finissant la commande
	/// \param inObject		r�f�rence sur l'objet
	///
	TDCLDockCmdNSObject(
				KUInt32 inCommand,
				const TDCLNSRef& inObject );

	///
	/// Constructeur pour la r�ception d'un objet NewtonScript.
	///
	/// \param inCommand	code d�finissant la commande
	/// \param inLength		longueur des donn�es
	/// \param inData		donn�es
	///
	TDCLDockCmdNSObject(
				KUInt32 inCommand,
				KUInt32 inLength,
				const void* inData );
	
	///
	/// Destructeur.
	///
	/// Lib�re la m�moire tampon.
	///
	virtual		~TDCLDockCmdNSObject( void );

	///
	/// Retourne un nouvel objet cr�� � partir de la m�moire tampon.
	/// Retourne NILREF si la m�moire tampon n'a pas �t� allou�e.
	///
	/// \return une r�f�rence vers un nouvel objet ou NILREF.
	///
	TDCLNSRef				GetObject( void ) const;

	///
	/// Remplace l'objet dans la m�moire tampon.
	///
	/// \param inObject		r�f�rence sur l'objet
	///
	void					SetObject( const TDCLNSRef& inObject );

protected:
	///
	/// R�cup�re le pointeur sur les donn�es.
	///
	/// \return le pointeur sur la m�moire tampon.
	///
	virtual const void*		GetData( void );
	
	///
	/// R�cup�re la taille des donn�es.
	///
	/// \return la taille de la m�moire tampon
	///
	virtual	KUInt32			GetLength( void ) const;

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLDockCmdNSObject( const TDCLDockCmdNSObject& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLDockCmdNSObject& operator = ( const TDCLDockCmdNSObject& inCopy );

	/// \name Variables
	void*		mBuffer;		///< M�moire tampon
	KUInt32		mBufferSize;	///< Taille allou�e de la m�moire tampon
};

#endif
		// __TDCLDOCKCMDNSOBJECT__

// ================================================= //
// [It is] best to confuse only one issue at a time. //
//                 -- K&R                            //
// ================================================= //
