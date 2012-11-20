// ==============================
// Fichier:			TDCLLink.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			28/06/2000
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
// The Original Code is TDCLLink.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2000-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLLink.h,v 1.6 2004/11/24 14:09:03 paul Exp $
// ===========

#ifndef _TDCLLINK_H
#define _TDCLLINK_H

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Communication_Layers/TDCLCommLayer.h>
#include <DCL/Interfaces/TDCLThread.h>
#include <DCL/Link/Dock_Commands/TDCLDockCommand.h>

class TDCLApplication;
class TDCLAppCommand;
class TDCLServer;
class TDCLPipe;

///
/// Classe abstraite pour les liens.
///
/// Un lien est une connexion avec un Newton donn� et fournit des services.
///
/// Le lien est repr�sent� par un processus l�ger. Il it�re dans une boucle en
/// attendant:
/// - des donn�es du Newton
/// - l'expiration d'une temporisation (permet d'appeler Idle).
/// - un appel du serveur ou de l'application.
///
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.6 $
///
/// \test	aucun test d�fini.
///
class TDCLLink
	:
		private TDCLThread
{
public:
	///
	/// Constantes pour cette classe.
	///
	enum {
		kDefaultIdlePeriod	= 15000	///< Temps d'attente en millisecondes entre
									///< entre les appels � Idle.
	};
	
	///
	/// Etat du lien.
	///
	enum EState {
		kDisconnected,	///< D�connect� (le processus l�ger ne tourne pas)
		kConnecting,	///< En train de se connecter (la connexion avec le Newton
						///< est �tablie)
		kConnected,		///< Connect� au Newton (la phase de connexion est finie)
		kRunning,		///< En train d'�changer des donn�es avec le Newton.
		kDisconnecting,	///< On est en train de se d�connecter.
		kUnknown		///< Etat inconnu.
	};

	///
	/// Accesseur sur l'application.
	///
	/// \return un pointeur sur l'application.
	///	
	inline TDCLApplication*	GetApplication( void )
		{
			return mApplication;
		}
	
	// --- connection parameters ---
	
	// General note regarding connection parameters:
	// These are to be set before the connection is initiated (it's useless otherwise).
	// They are initialized by the constructor with the values you passed to it.
	
	// Connection type: parameters used in the kDInitiateDocking command.
	// The 8 session types are defined in TDCLDockCommand.
	// There are in fact two constants that you want to use:
	//	TDCLDockCommand::kNone_SType (the default). Perfect for general connection.
	//	TDCLDockCommand::kLoadPackage_SType: the proper constant for package loading.
	
	///
	/// Accesseur sur le type de la connexion.
	/// Le type est utilis� avec ;a commande kDInitiateDocking.
	/// Les constantes utilisables sont d�finies dans TDCLDockCommand.
	/// Il y a deux constantes habituelles:
	/// - TDCLDockCommand::kNone_SType (valeur par d�faut): pour une connexion
	///		g�n�rale.
	/// - TDCLDockCommand::kLoadPackage_SType: pour l'installation de paquets.
	///
	/// \return le type de la connexion.
	///
	inline KUInt32		GetType( void )
		{
			return mType;
		}
	
	///
	/// S�lecteur sur le type de la connexion.
	///
	/// \param inType	nouveau type de la connexion
	/// \see GetType
	///
	inline void			SetType( KUInt32 inType )
		{
			mType = inType;
		}

	/// \name interface avec le serveur/l'application.

	///
	/// M�thode asynchrone pour connecter le Newton.
	/// D�marre le processus l�ger.
	///
	/// \param inPipe	Interface de communication associ�e au lien.
	/// \param inServer	Serveur qui g�re l'interface de communication.
	/// \return \c true si le lien �tait d�connect�, \c false sinon.
	///
	Boolean				Connect( TDCLPipe* inPipe, TDCLServer* inServer );
		
	///
	/// M�thode asynchrone pour d�connecter le Newton.
	/// Envoie un �v�nement au processus l�ger pour qu'il se d�connecte.
	/// Ne fait rien si le processus l�ger n'�tait pas d�marr�.
	/// Ceci est la m�thode souple pour d�connecter.
	///
	/// \return \c true si le lien �tait connect�, \c false sinon.
	///
	Boolean				Disconnect( void );
		
	///
	/// M�thode invoqu�e lorsque l'interface de connexion a �t� ferm�e.
	///
	/// \return \c true si le lien �tait connect�, \c false sinon.
	///
	Boolean				Close( void );

	///
	/// D�termine si le lien est connect�.
	///
	/// \return \c true si le lien est connect�, \c false sinon.
	///
	Boolean				IsConnected( void );

	///
	/// D�termine si le lien est occup� � ex�cuter une commande.
	///
	/// \return \c true si le lien est occup�, \c false sinon.
	///
	inline Boolean		IsBusy( void )
		{
			return mIsBusy;
		}

	///
	/// Accesseur sur l'interface de communication.
	///
	/// \return un pointeur sur l'interface de communication.
	///
	inline TDCLPipe* 	GetPipe( void )
		{
			return mPipe;
		}

	///
	/// M�thode appel�e par l'interface de communication pour dire que
	/// des donn�es sont pr�sentes. Cette m�thode est appel�e une seule fois
	/// et sera rappell�e lorsque le lien aura appel� ClearDataRequest.
	/// Cette m�thode envoie un �v�nement au processus l�ger du serveur.
	///
	void				DataPresent( void );

	///
	/// Accesseur sur le nom du Newton.
	/// Ceci est en fait le nom du possesseur du Newton.
	///
	/// \return le pointeur sur le nom du Newton.
	///
	inline const KUInt16*	GetNewtonName( void )
		{
			return mNewtonName;
		}

	///
	/// Accesseur sur un nombre identifiant le Newton de fa�on plus ou
	/// moins unique.
	/// Ceci ne peut pas �tre le num�ro de s�rie mat�riel du Newton vu que
	/// (a) les Newton 2.0 n'en ont pas, (b) c'est une valeur sur 32 bits.
	/// Je pense que c'est d�riv� de l'ID du magasin ou un truc dans le genre.
	///
	/// \return l'ID du Newton
	///
	inline KUInt32			GetNewtonID( void )
		{
			return mNewtonID;
		}
	
	///
	/// Accesseur sur le champ TGestaltSystemInfo.fManufacturer.
	/// Cf <NewtonGestalt.h>
	///
	/// \return la valeur de TGestaltSystemInfo.fManufacturer
	///
	inline KUInt32			GetManufacturer( void )
		{
			return mManufacturer;
		}

	///
	/// Accesseur sur le champ TGestaltSystemInfo.fMachineType
	/// Cf <NewtonGestalt.h>
	///
	/// \return la valeur de TGestaltSystemInfo.fMachineType
	///
	inline KUInt32			GetMachineType( void )
		{
			return mMachineType;
		}

	///
	/// Accesseur sur le champ TGestaltSystemInfo.fROMVersion
	/// Cf <NewtonGestalt.h>
	///
	/// \return la valeur de TGestaltSystemInfo.fROMVersion
	///
	inline KUInt32			GetROMVersion( void )
		{
			return mROMVersion;
		}

	///
	/// Accesseur sur le champ TGestaltSystemInfo.fROMStage
	/// Cf <NewtonGestalt.h>
	///
	/// \return la valeur de TGestaltSystemInfo.fROMStage
	///
	inline KUInt32			GetROMStage( void )
		{
			return mROMStage;
		}

	///
	/// Accesseur sur le champ TGestaltSystemInfo.fRAMSize
	/// Cf <NewtonGestalt.h>
	///
	/// \return la valeur de TGestaltSystemInfo.fRAMSize
	///
	inline KUInt32			GetRAMSize( void )
		{
			return mRAMSize;
		}

	///
	/// Accesseur sur le champ TGestaltSystemInfo.fScreenHeight
	/// Cf <NewtonGestalt.h>
	///
	/// \return la valeur de TGestaltSystemInfo.fScreenHeight
	///
	inline KUInt32			GetScreenHeight( void )
		{
			return mScreenHeight;
		}

	///
	/// Accesseur sur le champ TGestaltSystemInfo.fScreenWidth
	/// Cf <NewtonGestalt.h>
	///
	/// \return la valeur de TGestaltSystemInfo.fScreenWidth
	///
	inline KUInt32			GetScreenWidth( void )
		{
			return mScreenWidth;
		}
	inline KUInt32			GetSystemUpdate( void )
		{
			return mSystemUpdate;
		}
	inline KUInt32			GetNOSVersion( void )
		{
			return mNOSVersion;
		}
	inline KUInt32			GetInternalStoreSig( void )
		{
			return mInternalStoreSig;
		}

	///
	/// Accesseur sur le champ TGestaltSystemInfo.fScreenResolution.v
	/// Cf <NewtonGestalt.h>
	///
	/// \return la valeur de TGestaltSystemInfo.fScreenResolution.v
	///
	inline KUInt32			GetVertScreenRes( void )
		{
			return mVertScreenRes;
		}

	///
	/// Accesseur sur le champ TGestaltSystemInfo.fScreenResolution.h
	/// Cf <NewtonGestalt.h>
	///
	/// \return la valeur de TGestaltSystemInfo.fScreenResolution.h
	///
	inline KUInt32			GetHoriScreenRes( void )
		{
			return mHoriScreenRes;
		}

	///
	/// Accesseur sur le champ TGestaltSystemInfo.fScreenDepth
	/// Cf <NewtonGestalt.h>
	///
	/// \return la valeur de TGestaltSystemInfo.fScreenDepth
	///
	inline KUInt32			GetScreenDepth( void )
		{
			return mScreenDepth;
		}
	
protected:
	///
	/// Constantes prot�g�es.
	///
	enum {
		kDefaultTimeout	=	30	///< Valeur par d�faut de la temporisation
								///< pass�e au Newton avec kDSetTimeout.
	};

	///
	/// Constructeur unique.
	///
	/// \param inApplication	interface avec l'application.
	/// \param inType			type de connexion (expliqu� plus haut)
	/// \param inIdlePeriod		fr�quence des appels � Idle.
	/// \see GetType()
	///
	TDCLLink(
		TDCLApplication* inApplication,
		KUInt32 inType = TDCLDockCommand::kNone_SType,
		KUInt32 inIdlePeriod = kDefaultIdlePeriod );
	
	///
	/// Destructeur.
	/// Indique que le lien a �t� d�connect� si n�cessaire.
	///
	virtual		~TDCLLink( void );

	///
	/// Poste une commande � effectuer.
	/// Trois cas se pr�sentent:
	/// - le lien n'est pas �tabli, la m�thode retourne \c false.
	/// - le lien �tait �tabli, la m�thode retourne \c true et
	///		envoie un �v�nement.
	///		- l'�v�nement est r�cup�r�, la commande est pass�e �
	///			ProcessAppCommand et puis � TDCLApplication::AppCommandProcessed,
	///			enfin l'�v�nement sera supprim� avec delete par le lien.
	///		- l'�v�nement n'est pas r�cup�r� avant que lien ne soit
	///			interrompu, la commande sera supprim�e lorsque le processus
	///			l�ger sera termin� avec delete.
	///		- un probl�me est survenu dans AppCommandProcessed, la commande
	///			sera supprim�e avec delete.
	///
	/// \return \c true si le lien �tait �tabli, \c false sinon.
	///
	Boolean				PostAppCommand( TDCLAppCommand* inCommand );

	///
	/// M�thode synchrone pour connecter le Newton.
	/// Peut �tre surcharg�e.
	/// Cette m�thode est appel�e dans le processus l�ger du lien et effectue
	/// le dialogue minimal pour la connexion:
	///
	/// Desktop			Newton
	///				<- kDRequestToDock
	/// kDInitiateDocking ->
	///				<- kDNewtonName
	///
	/// \throws TDCLException si un probl�me est survenu.
	///
	virtual void		DoConnect( void );

	///
	/// M�thode synchrone pour d�connecter le Newton.
	/// Peut �tre surcharg�e.
	/// Cette m�thode est appel�e dans le processus l�ger du lien et envoie la
	/// commande kDDisconnect au Newton
	///
	/// Desktop			Newton
	/// kDDisconnect ->
	///
	virtual void		DoDisconnect( void );


	///
	/// M�thode appel�e lorsque le Newton a envoy� une commande.
	///
	/// Cette m�thode est appel�e pour toutes les commandes intercept�es
	/// dans la boucle principale.
	/// Les protocoles peuvent �changer des commandes avec le Newton sans
	/// qu'elles soient trait�es dans la boucle principale.
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e. Si la valeur est
	///						\c false, une exception est lev�e dans la boucle.
	/// \return le prochain �tat du lien (l'�tat actuel �tant kRunning),
	///			par exemple kRunning ou kDisconnecting (DoDisconnect est appel�
	///			dans la boucle)
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual	EState	ProcessDockCommand(
								TDCLDockCommand* inCommand,
								Boolean* outProcessed ) = 0;

	///
	/// M�thode appel�e lorsqu'on a re�u une commande de l'application.
	/// La commande est supprim�e une fois que cette m�thode retourne.
	/// Cette classe ne fait rien -- retourne kRunning et met false dans
	/// \c outProcessed.
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e. Si la valeur est
	///						\c false, une exception est lev�e dans la boucle.
	/// \return le prochain �tat du lien (l'�tat actuel �tant kRunning)
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual	EState	ProcessAppCommand(
								TDCLAppCommand* inCommand,
								Boolean* outProcessed );

	///
	/// M�thode appel�e de temps en temps lorsqu'on n'a pas de nouvelles
	/// ni de l'application du Newton.
	///
	/// Par d�faut, appelle Yield.
	/// Il faudrait en fait dire bonjour.
	///
	/// \return le prochain �tat du lien (l'�tat actuel �tant kRunning)
	///
	virtual	EState			Idle( void );

	///
	/// Boucle principale du lien.
	/// Attend:
	/// - un d�passement de la temporisation pour appeler Idle
	/// - des donn�es du Newton (lit alors toute la commande)
	/// - un appel de l'application.
	///
	virtual void	Run( void );

	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e.
	/// Lorsque cette m�thode retourne, le processus est termin�.
	///
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void HandleException( TDCLException* inException );

	///
	/// M�thode invoqu�e lorsque le processus de connexion est
	/// termin�.
	///
	/// Cette m�thode appelle l'interface des messages pour lui dire et lui
	/// transmet le nom du Newton.
	///
	virtual void		Connected( void );

	///
	/// M�thode invoqu�e lorsque le processus de d�connexion est
	/// termin�.
	///
	/// Elle appelle l'interface des messages pour lui dire.
	/// Elle lib�re aussi le nom du Newton dont on n'a plus besoin.
	///
	virtual void		Disconnected( void );

	///
	/// D�termine les commandes de l'application que le lien
	/// peut traiter. Cette m�thode est appel�e � chaque fois que le
	/// lien va attendre un �v�nement. Par d�faut, le lien peut traiter
	/// toutes les commandes d'application.
	///
	/// \return le masque pour les commandes de l'application
	///
	virtual KUInt32		GetAppCommandMask( void );

	///
	/// Receive a link specfic command. This function blocks
	/// until completion.
	///
	/// \return the received command.
	///
	virtual TDCLDockCommand* ReceiveCommand( void );

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLLink( const TDCLLink& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLLink& operator = ( const TDCLLink& inCopy );

	///
	/// M�thode appel�e par la boucle du processus l�ger pour faire le boulot.
	///
	/// \return le nouvel �tat.
	///
	EState		TransitionFromRunning( void );

protected:
	///
	/// Constantes pour cette classe.
	///
	enum {
		kClosingTimeout	= 5		// Number of seconds to wait with pipes that do not support
								// flush after having sent the disconnect command.
								// 5 seconds is enough on my mac with ADSP CTB tool.
	};

	/// \name Variables priv�es.
	TDCLPipe*					mPipe;				///< Interface de communication.
													///< \c nil si on n'est pas connect�.
	TDCLServer*					mServer;			///< Serveur qui g�re l'interface de
													///< communication.
	TDCLApplication* 			mApplication;		///< R�f�rence sur l'application.
	IDCLThreads::ISemaphore*	mStateMutex;		///< S�maphore sur l'�tat.
	EState						mState;				///< Etat.
	KUInt32						mType;				///< Type de connexion Dock.
	KUInt32						mIdlePeriod;		///< Temps en millisecondes entre les
													///< appels � Idle
	Boolean						mIsBusy;			///< Si le lien est occup�.
	
	/// \name Informations sur le Newton.
	const KUInt16*				mNewtonName;		///< Nom du (possesseur du) Newton
	KUInt32						mNewtonID;			///< Identifiant unique (?)
	KUInt32						mManufacturer;		///< Tel que fourni par Gestalt
	KUInt32						mMachineType;		///< Idem
	KUInt32						mROMVersion;		///< Idem
	KUInt32						mROMStage;			///< Idem
	KUInt32						mRAMSize;			///< Idem
	KUInt32						mScreenHeight;		///< Idem, en pixels.
	KUInt32						mScreenWidth;		///< Idem, en pixels.
	KUInt32						mSystemUpdate;		///< Non nul s'il y a une rustine.
	KUInt32						mNOSVersion;		///< Version du format NSOF, je suppose.
													///< (Newton Object System)
	KUInt32						mInternalStoreSig;	///< Comme le nom l'indique.
	KUInt32						mVertScreenRes;		///< Nombre de pixels par pouce sur la
													///< hauteur.
	KUInt32						mHoriScreenRes;		///< Nombre de pixels par pouce sur la
													///< longueur.
	KUInt32						mScreenDepth;		///< Profondeur en bits (e.g. 1 ou 4)
};

#endif
		// _TDCLLINK_H

// ========================================================================== //
// Why do we want intelligent terminals  when there are so many stupid users? //
// ========================================================================== //
