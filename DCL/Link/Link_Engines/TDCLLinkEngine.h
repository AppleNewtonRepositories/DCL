// ==============================
// Fichier:			TDCLLinkEngine.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			10/4/2003
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
// The Original Code is TDCLLinkEngine.h.
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
// $Id: TDCLLinkEngine.h,v 1.3 2004/11/24 14:09:05 paul Exp $
// ===========

#ifndef _TDCLLINKENGINE_H
#define _TDCLLINKENGINE_H

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Link/TDCLLink.h>

// Pr�-d�clarations.
class TDCLDockCommand;
class TDCLFullDockLink;

///
/// Classe de base pour les moteurs du lien.
/// Ces moteurs prennent le relai du FullDockLink lorsqu'une commande est en route.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLLinkEngine
{
public:
	///
	/// Constructeur � partir d'une r�f�rence sur le lien.
	///
	/// \param inLink	r�f�rence sur le lien.
	///
	TDCLLinkEngine( TDCLFullDockLink* inLink );

	///
	/// Destructeur.
	///
	virtual ~TDCLLinkEngine( void );

	///
	/// M�thode appel�e pour g�rer des commandes venant du Newton.
	/// Par d�faut retourne \c true et met outProcessed � \c false.
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return \c true si le moteur continue, \c false sinon
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual	Boolean		ProcessDockCommand(
									TDCLDockCommand* inCommand,
									Boolean* outProcessed );

	///
	/// M�thode appel�e pour g�rer des commandes venant de l'application.
	/// Par d�faut retourne \c true et met outProcessed � \c false.
	///
	/// \param inCommand	commande � ex�cuter.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return \c true si le moteur continue, \c false sinon
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual	Boolean		ProcessAppCommand(
									TDCLAppCommand* inCommand,
									Boolean* outProcessed );

	///
	/// M�thode appel�e par le lien pour signifier que le travail du
	/// moteur est termin�.
	/// Par d�faut ne fait rien.
	///
	virtual void				WorkIsOver( void );

	///
	/// D�termine les commandes de l'application que le lien
	/// peut traiter. Cette m�thode est appel�e � chaque fois que le
	/// lien va attendre un �v�nement. Par d�faut, on accepte toutes
	/// les commandes d'application sauf les commandes envoy�es lorsqu'on
	/// est oisif.
	///
	/// \return le masque pour les commandes de l'application
	///
	virtual KUInt32				GetAppCommandMask( void );

protected:
	///
	/// Accesseur sur le lien.
	///
	inline TDCLFullDockLink*	GetLink( void ) const
		{
			return mLink;
		}

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLLinkEngine( const TDCLLinkEngine& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLLinkEngine& operator = ( const TDCLLinkEngine& inCopy );

	/// \name Variables
	TDCLFullDockLink*			mLink;			///< R�f�rence sur le lien.
};

#endif
		// _TDCLLINKENGINE_H

// ============================================================================ //
// I think there's a world market for about five computers.                     //
//                 -- attr. Thomas J. Watson (Chairman of the Board, IBM), 1943 //
// ============================================================================ //
