// ==============================
// Fichier:			TDCLDockCmdTwoNSObjects.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			1/11/2003
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
// The Original Code is TDCLDockCmdTwoNSObjects.h.
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
// $Id: TDCLDockCmdTwoNSObjects.h,v 1.3 2004/11/24 14:09:04 paul Exp $
// ===========

#ifndef _TDCLDOCKCMDTWONSOBJECTS_H
#define _TDCLDOCKCMDTWONSOBJECTS_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/Dock_Commands/TDCLDockCommand.h>

// DCL
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>

///
/// Classe pour une commande Dock avec deux objets NS.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLDockCmdTwoNSObjects
	:
		public TDCLDockCommand
{
public:
	///
	/// Constructeur par d�faut.
	///
	TDCLDockCmdTwoNSObjects( void );

	///
	/// Constructeur pour l'envoi de deux objets NewtonScript � partir de
	/// r�f�rences.
	///
	/// \param inCommand		code d�finissant la commande
	/// \param inFirstObject	r�f�rence sur le premier objet
	/// \param inSecondObject	r�f�rence sur le second objet
	///
	TDCLDockCmdTwoNSObjects(
				KUInt32 inCommand,
				const TDCLNSRef& inFirstObject,
				const TDCLNSRef& inSecondObject );

	///
	/// Constructeur pour la r�ception d'un objet NewtonScript.
	///
	/// \param inCommand	code d�finissant la commande
	/// \param inLength		longueur des donn�es
	/// \param inData		donn�es
	///
	TDCLDockCmdTwoNSObjects(
				KUInt32 inCommand,
				KUInt32 inLength,
				const void* inData );
	
	///
	/// Destructeur.
	///
	/// Lib�re la m�moire tampon.
	///
	virtual ~TDCLDockCmdTwoNSObjects( void );

	///
	/// Retourne un tableau avec les deux objets cr��s � partir de la m�moire
	/// tampon. Retourne \c NILREF si la m�moire tampon n'a pas �t� allou�e.
	///
	/// \return une r�f�rence vers un tableau contenant deux nouveaux objets
	///			ou \c NILREF.
	///
	TDCLNSRef				GetObjects( void ) const;

	///
	/// Remplace les objets dans la m�moire tampon.
	///
	/// \param inFirstObject	r�f�rence sur le premier objet
	/// \param inSecondObject	r�f�rence sur le second objet
	///
	void					SetObjects(
								const TDCLNSRef& inFirstObject,
								const TDCLNSRef& inSecondObject );

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
	TDCLDockCmdTwoNSObjects( const TDCLDockCmdTwoNSObjects& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLDockCmdTwoNSObjects& operator =
							( const TDCLDockCmdTwoNSObjects& inCopy );

	/// \name Variables
	void*		mBuffer;		///< M�moire tampon
	KUInt32		mBufferSize;	///< Taille allou�e de la m�moire tampon
};

#endif
		// _TDCLDOCKCMDTWONSOBJECTS_H

// ========================================================================= //
// Real programmers disdain structured programming.  Structured programming  //
// is for compulsive neurotics who were prematurely toilet-trained.  They    //
// wear neckties and carefully line up pencils on otherwise clear desks.     //
// ========================================================================= //
