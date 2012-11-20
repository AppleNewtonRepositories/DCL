// ==============================
// Fichier:			TDCLDockCmdPassword.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			27/08/2001
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
// The Original Code is TDCLDockCmdPassword.h.
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
// $Id: TDCLDockCmdPassword.h,v 1.3 2004/11/24 14:09:04 paul Exp $
// ===========

#ifndef __TDCLDOCKCMDPASSWORD__
#define __TDCLDOCKCMDPASSWORD__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/Dock_Commands/TDCLDockCommand.h>

///
/// Classe pour la gestion du mot de passe.
/// Permet de cr�er ou de v�rifier un mot de passe.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLDockCmdPassword
	:
		public TDCLDockCommand
{
public:

	///
	/// Constructeur � partir des donn�es qui viennent du Newton.
	/// Ces donn�es sont converties avec le boutien local.
	///
	/// \param inLength	taille des donn�es
	/// \param inData	donn�es
	///
	TDCLDockCmdPassword( KUInt32 inLength, const void* inData );

	///
	/// Constructeur pour une commande Password � envoyer.
	///
	/// \param inChallenge	d�fi
	/// \param inPassword	mot de passe (\c nil signifie le mot de passe vide)
	///
	TDCLDockCmdPassword(
						const KUInt32 inChallenge[2],
						const KUInt16* inPassword = nil );

	///
	/// Cr�e un d�fi � l'aide de deux nombres al�atoires.
	///
	/// \param outChallenge	en sortie, deux nombres al�atoires pour le d�fi.
	///
	static	void	CreateChallenge( KUInt32 outChallenge[2] );

	///
	/// V�rifie le mot de passe � partir du d�fi envoy� au Newton.
	///
	/// \param inChallenge	d�fi que nous avons envoy� au Newton.
	/// \param inPassword	mot de passe � v�rifier (\c nil signifie le mot de
	///						passe vide)
	/// \return \c true si les donn�es renvoy�es par le Newton correspond au
	///			d�fi et au mot de passe.
	///
	Boolean	VerifyPassword(
						const KUInt32 inChallenge[2],
						const KUInt16* inPassword = nil );

protected:
	///
	/// M�thode appel�e pour r�cup�rer la taille de la commande avant de
	/// l'envoyer.
	///
	/// \return la taille de la commande
	///
	virtual	KUInt32			GetLength( void ) const;

	///
	/// M�thode appel�e pour r�cup�rer les donn�es � envoyer.
	///
	/// \return un pointeur sur les donn�es � envoyer.
	///
	virtual const void*		GetData( void );

private:
	/// \name Variables
	
	KUInt32	mCipheredChallenge[2];	///< D�fi crypt� par le mot de passe
									///< (en grand-boutien)
};

#endif
		// __TDCLDOCKCMDPASSWORD__

// ================================= //
// Put no trust in cryptic comments. //
// ================================= //
