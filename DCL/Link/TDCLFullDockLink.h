// ==============================
// Fichier:			TDCLFullDockLink.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			22/06/2002
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
// The Original Code is TDCLFullDockLink.h.
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
// $Id: TDCLFullDockLink.h,v 1.3 2004/11/24 14:09:02 paul Exp $
// ===========

#ifndef _TDCLFULLDOCKLINK_H
#define _TDCLFULLDOCKLINK_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/IDCLFiles.h>
#include <DCL/Link/TDCLDockLink.h>

// DCL
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>

// Pr�-d�clarations

class TDCLApplication;
class TDCLFile;
class TDCLBrowseEngine;
class TDCLKeyboardEngine;
class TDCLLoadPkgEngine;
class TDCLLinkEngine;
class TDCLSyncEngine;

///
/// Classe pour un lien qui g�re l'ensemble des commandes document�es.
/// 
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLFullDockLink
	:
		public TDCLDockLink
{
public:
	///
	/// La classe TDCLBrowseEngine doit pouvoir appeler les m�thodes virtuelles
	/// de cette classe pour effectuer des op�rations demand�es pendant le butinage.
	///
	friend class TDCLBrowseEngine;
	
	enum {
		// Command sets this class supports.
		kNilSet				= 0,
		kFileBrowsingSet	= 1,	// Depending on the other sets,
									// the request to browse command will lead to an error or not.
		kInstallPackageSet	= 2,
		kSyncSet			= 4,
		kKeyboardSet		= 8,
		kAllSets			= 15
	};

	///
	/// Constructeur unique.
	///
	/// \param inApplication	application qui g�re ce lien
	/// \param inWhatToProcess	entier qui d�termine les ensembles de commandes � g�rer
	/// \param inIcons			entier qui d�termine les ic�nes � afficher dans le dock du Newton
	///
	TDCLFullDockLink(
					TDCLApplication* inApplication,
					KUInt32 inWhatToProcess = kAllSets,
					KUInt32 inIcons = kAllIcons );

	///
	/// Destructeur.
	///
	~TDCLFullDockLink( void );

	/// \name Interface avec l'appliaction.
	
	///
	/// Indique au Newton que l'on souhaite installer un paquet et installe
	/// un paquet. (Cette m�thode est en fait asynchrone et poste un �v�nement
	/// pour le lien).
	///
	/// \param inPackage	paquet � installer.
	/// \return \c true si le lien �tait connect�, \c false sinon (auquel cas
	///			le paquet ne sera pas install�).
	///
	Boolean InstallPackage( TDCLFSItemRef inPackage );
		
	///
	/// Indique au Newton que l'on souhaite utiliser le clavier et
	/// utilise le clavier.
	///
	/// \return \c true si le lien �tait connect�, \c false sinon (auquel cas
	///			le paquet ne sera pas install�).
	///
	Boolean StartUsingKeyboard( void );

	///
	/// Envoie une cha�ne au Newton. Asynchrone aussi.
	///
	/// \remark cette cha�ne est envoy�e si le lien est connect� et sera trait�e
	/// 		si le lien �tait en mode clavier, sinon une erreur sera retourn�e
	///			� l'application dans AppCommandProcessed.
	/// \param inString		cha�ne � envoyer (copi�e)
	/// \return \c true si le lien �tait connect�, \c false sinon (auquel cas
	///			le paquet ne sera pas install�).
	///
	Boolean SendKeyboardString( const KUInt16* inString );
		
	///
	/// Envoie un caract�re au Newton.
	///
	/// \remark comme la m�thode pr�c�dente.
	/// \param inChar		caract�re � envoyer
	/// \param inFlags		drapeaux (permet en th�orie d'envoyer des modificateurs)
	/// \return \c true si le lien �tait connect�, \c false sinon (auquel cas
	///			le paquet ne sera pas install�).
	///
	Boolean SendKeyboardChar( KUInt16 inChar, KUInt16 inFlags );
		
	///
	/// Arr�te d'utiliser le clavier.
	///
	/// \remark comme les deux m�thodes pr�c�dentes.
	/// \return \c true si le lien �tait connect�, \c false sinon (auquel cas
	///			le paquet ne sera pas install�).
	///
	Boolean StopUsingKeyboard( void );
		
	///
	/// Indique au Newton que l'on souhaite synchroniser et effectue
	/// cette synchronisation.
	///
	/// \remark comme les m�thodes pr�c�dentes.
	/// \return \c true si le lien �tait connect�, \c false sinon (auquel cas
	///			le paquet ne sera pas install�).
	///
	Boolean Synchronize( void );

protected:
	///
	/// M�thode appel�e pour g�rer des commandes venant du Newton.
	/// Cette classe g�re les commandes en fonction de l'ensemble
	/// d�termin� par le constructeur.
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le prochain �tat du lien (l'�tat actuel �tant kRunning),
	///			par exemple kRunning ou kDisconnecting (DoDisconnect est appel�
	///			dans la boucle)
	///
	virtual	EState		ProcessDockCommand(
								TDCLDockCommand* inCommand,
								Boolean* outProcessed );

	///
	/// M�thode appel�e pour g�rer des commandes venant de l'application.
	/// Toutes les commandes sont g�r�es, quelque soit mHandledCommandSets.
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le prochain �tat du lien (l'�tat actuel �tant kRunning)
	///
	virtual	EState		ProcessAppCommand(
								TDCLAppCommand* inCommand,
								Boolean* outProcessed );

	///
	/// Installe v�ritablement un paquet.
	///
	/// \param inPackage	paquet � installer.
	/// \throws TDCLException si une erreur est survenue.
	///
	void DoInstallPackage( TDCLFSItemRef inPackage );
	
	///
	/// Effectue le butinage.
	///
	/// \param inFileTypes	types des fichiers que le Newton veut butiner
	/// \throws TDCLException si une erreur est survenue.
	///
	void DoBrowse( const TDCLNSRef& inFileTypes );

	///
	/// Effectue v�ritablement la synchronisation.
	///
	/// \throws TDCLException si une erreur est survenue.
	///
	void DoSynchronize( void );

	///
	/// Utilise v�ritablement le clavier.
	///
	/// \throws TDCLException si une erreur est survenue.
	///
	void DoUseKeyboard( void );

	///
	/// D�termine les commandes de l'application que le lien
	/// peut traiter. Cette m�thode est appel�e � chaque fois que le
	/// lien va attendre un �v�nement.
	///
	/// Demande � un �ventuel moteur de lien courant, sinon
	/// on demande � la classe m�re.
	///
	/// \return le masque pour les commandes de l'application
	///
	virtual KUInt32				GetAppCommandMask( void );

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLFullDockLink( const TDCLFullDockLink& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLFullDockLink& operator = ( const TDCLFullDockLink& inCopy );

	///
	/// R�cup�re le moteur de butinage.
	/// Par d�faut, retourne mDefaultBrowseEngine.
	///
	/// \return une r�f�rence sur le moteur de butinage.
	///
	virtual TDCLBrowseEngine*	GetBrowseEngine( void );

	///
	/// R�cup�re le moteur d'installation des paquets.
	/// Par d�faut, retourne mDefaultLoadPkgEngine;
	///
	/// \return une r�f�rence sur le moteur d'installation des paquets.
	///
	virtual TDCLLoadPkgEngine*	GetLoadPkgEngine( void );

	///
	/// R�cup�re le gestionnaire de clavier.
	/// Par d�faut, retourne \c nil.
	///
	/// \return une r�f�rence sur le moteur de synchronisation.
	///
	virtual TDCLKeyboardEngine*	GetKeyboardEngine( void );

	///
	/// R�cup�re le moteur de synchronisation.
	/// Par d�faut, retourne \c nil.
	///
	/// \return une r�f�rence sur le moteur de synchronisation.
	///
	virtual TDCLSyncEngine*		GetSyncEngine( void );

	///
	/// Envoie une requ�te (pour commencer une op�ration) et lit le
	/// message d'erreur.
	///
	/// \param inRequest	requ�te � envoyer.
	/// \throws TDCLException si une erreur est survenue.
	///
	void SendRequest( KUInt32 inRequest );

	/// \name Variables
	KUInt32				mHandledCommandSets;	///< Ensemble des commandes
												///< � g�rer.
	TDCLLinkEngine*		mCurrentEngine;			///< le moteur courant (\c nil
												///< si aucun moteur ne g�re les commandes)
	TDCLBrowseEngine*	mDefaultBrowseEngine;	///< Moteur de butinage par d�faut.
	TDCLLoadPkgEngine*	mDefaultLoadPkgEngine;	///< Moteur d'installation par d�faut.
};

#endif
		// _TDCLFULLDOCKLINK_H

// ==================================================================== //
// "The algorithm to do that is extremely nasty.  You might want to mug //
// someone with it."                                                    //
//                 -- M. Devine, Computer Science 340                   //
// ==================================================================== //
