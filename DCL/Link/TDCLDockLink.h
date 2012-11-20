// ==============================
// Fichier:			TDCLDockLink.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			13/08/2001
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
// The Original Code is TDCLDockLink.h.
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
// $Id: TDCLDockLink.h,v 1.3 2004/11/24 14:09:02 paul Exp $
// ===========

#ifndef _TDCLDOCKLINK_H
#define _TDCLDOCKLINK_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/TDCLLink.h>

///
/// Classe pour un lien minimal.
/// Les commandes du Newton qui sont g�r�es sont kDHello et kDDisconnect.
///
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLDockLink
	:
		public TDCLLink
{
public:
	///
	/// Ic�nes pour le param�tre inIcons du constructeur.
	/// Un jour, nous pourrons mettre nos propres ic�nes dans le dialogue du dock.
	///
	/// La pr�sence de l'ic�ne signifie que l'utilisateur peut la cliquer
	/// et donc qu'il faut g�rer le protocole associ�.
	///
	enum {
		kNoIcon				= 0,	///< Pas d'ic�ne
		kBackupIcon			= 1,	///< Ic�ne pour la sauvegarde.
		kRestoreIcon		= 2,	///< Ic�ne de restauration.
		kInstallIcon		= 4,	///< Ic�ne d'installation de paquet.
		kImportIcon			= 8,	///< Ic�ne d'importation de documents (sauf Works)
	  	kSyncIcon			= 16,	///< Ic�ne de synchronisation
		kKeyboardIcon		= 32,	///< Ic�ne pour utiliser le clavier
		kAllIcons			= 63	///< Constante pour utiliser toutes les ic�nes.
	};

protected:
	///
	/// Constructeur unique.
	///
	/// \param inApplication	R�f�rence sur l'application.	
	/// \param inIcons			les ic�nes que l'on veut montrer dans
	///							l'application Dock sur sur le Newton.
	///
	TDCLDockLink(
			TDCLApplication* inApplication,
			KUInt32 inIcons = kAllIcons );
							
	///
	/// M�thode synchrone pour connecter le Newton.
	///
	/// Appelle d'abord TDCLLink::DoConnect pour le d�but du dialogue:
	///
	/// Desktop			Newton
	///				<- kDRequestToDock
	/// kDInitiateDocking ->
	///				<- kDNewtonName
	///
	/// Puis continue avec le dialogue suivant:
	///
	/// kDDesktopInfo ->
	///				<- kDNewtonInfo
	/// kDWhichIcons ->
	///				<- kDResult
	/// kDSetTimeout ->
	///				<- kDPassword
	/// kDPassword ->
	///				<- kDResult
	///
	/// \throws TDCLException si un probl�me est survenu.
	///
	virtual void		DoConnect( void );	

	///
	/// M�thode appel�e pour g�rer des commandes venant du Newton.
	/// Cette classe ne g�re que kDHello et kDDisconnect.
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le prochain �tat du lien (l'�tat actuel �tant kRunning),
	///			par exemple kRunning ou kDisconnecting (DoDisconnect est appel�
	///			dans la boucle)
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual	EState		ProcessDockCommand(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	///	M�thode pour r�cup�rer le mot de passe.
	/// Le mot de passe appartient au lien et n'est pas lib�r� par l'appelant.
	/// La m�thode par d�faut fournit \c nil qui veut dire pas de mot de passe
	/// (la cha�ne vide). Au moment o� cette m�thode est appel�e, l'identit� du
	/// Newton est connu (NewtonName a �t� re�u et les m�thodes de TDCLLink
	/// retournent des donn�es coh�rentes).
	///
	/// \return le mot de passe ou \c nil
	///
	virtual const KUInt16*	GetPassword( void );
	
	///
	/// Accesseur sur les ic�nes.
	///
	/// \return les ic�nes pour la prochaine connexion.
	///
	inline KUInt32 GetIcons( void ) const
		{
			return mIcons;
		}
	
	///
	/// S�lecteur sur les ic�nes.
	/// Remarque: ceci n'a d'effet que pour la prochaine connexion.
	///
	/// \param inNewIcons les nouvelles ic�nes pour la prochaine connexion.
	///
	inline void SetIcons( KUInt32 inNewIcons )
		{
			mIcons = inNewIcons;
		}

private:
	/// \name Variables priv�es.
	KUInt32				mIcons;	///< param�tre pour les ic�nes
};

#endif
		// _TDCLDOCKLINK_H

// ========================================================================= //
// Let the machine do the dirty work.                                        //
//                 -- "Elements of Programming Style", Kernighan and Ritchie //
// ========================================================================= //
