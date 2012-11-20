// ==============================
// Fichier:			TDCLOpenTransport.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			23/01/2002
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
// The Original Code is TDCLOpenTransport.h.
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
// $Id: TDCLOpenTransport.h,v 1.5 2004/11/24 14:08:55 paul Exp $
// ===========

#ifndef __TDCLOPENTRANSPORT__
#define __TDCLOPENTRANSPORT__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/TDCLCommLayer.h>

#if !TARGET_OS_MAC
	#error "OpenTransport est seulement disponible sur MacOS/MacOS X"
#endif

// Open Transport headers.
#if !CALL_NOT_IN_CARBON
	#ifndef OTCARBONAPPLICATION
		#define OTCARBONAPPLICATION 1
	#endif
#endif

#if TARGET_OS_MACOS
	// Bug dans les derniers UH: il faut Files.h
	#include <Files.h>
	#include <OpenTransport.h>
	#include <OpenTransportProviders.h>
#else
	#define OTOpenEndpoint(config, oflag, info, err) \
		OTOpenEndpointInContext(config, oflag, info, err, NULL)
	#define InitOpenTransport() \
		InitOpenTransportInContext(kInitOTForApplicationMask, NULL)
	#define CloseOpenTransport() \
		CloseOpenTransportInContext(NULL)
	#include <CoreServices/CoreServices.h>
#endif

// DCL
#include <DCL/Communication_Layers/TDCLPipe.h>
#include <DCL/Exceptions/TDCLNotAvailableException.h>

// Pr�-d�clarations
class IDCLThreads;

///
/// Classe pour la couche de communication OpenTransport.
///
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.5 $
///
/// \todo	revoir les temporisations.
/// \test	aucun test d�fini.
///
class TDCLOpenTransport
	:
		public TDCLCommLayer
{
public:
	///
	/// Constructeur publique pour cette classe.
	/// Le nombre de connexion et la temporisation par d�faut sont d�finies
	/// comme des constantes. Les sous-classes utiliseront probablement plut�t
	/// l'autre constructeur.
	///
	/// \param inConfiguration	configuration pour cette couche de
	///							communication. Cette configuration est clon�e.
	/// \param inLocalBindInfo	adresse du serveur. Copi�e.
	/// \param inThreadsIntf	interface sur les processus l�gers
	/// \param inMaxPipeCount	nombre maximum de connexion ouvertes en m�me
	///							temps.
	/// \param inTimeout		temporisation.
	///
	TDCLOpenTransport(
			OTConfigurationRef	inConfiguration,
			TBind*				inLocalBindInfo,
			IDCLThreads*		inThreadsIntf,
			KUInt32				inMaxPipeCount = kDefaultPipeCount,
			long				inTimeout = kDefaultTimeout
		);

	///
	/// Destructeur.
	/// Arr�te le serveur (i.e. d'�couter). D�cr�mente aussi le nombre de
	/// clients OpenTransport.
	/// 
	virtual				~TDCLOpenTransport( void );
	
	/// \name interface serveur

	///
	/// Retourne un objet connexion repr�sentant le canal de communication
	/// avec le client ou \c nil s'il n'y a pas de requ�te de connexion
	/// pr�sente.
	/// Ce doit �tre un objet cr�� avec new. L'appelant devra le supprimer.
	///
	/// \return	un nouvel objet TDCLPipe cr�� avec new repr�sentant la connexion
	///			ou \c nil.
	///
	virtual	TDCLPipe*	Accept( void );

	///
	/// Refuse la premi�re requ�te de connexion.
	/// Ne fait rien si aucune connexion n'est pr�sente.
	///
	virtual	void		Refuse( void );

	///
	/// Cette m�thode est appel�e par TDCLPipe::Idle.
	/// Appelle OTIdle et mInterface->Yield.
	///
	virtual	void		Idle( void );

	///
	/// Change la temporisation pour les nouvelles connexions.
	/// La temporisation est exprim�e au format TDCLCommLayer.
	///
	/// \param inTimeout	nouvelle temporisation au format \c TDCLCommLayer
	///
	virtual	void		SetTimeout( long inTimeout );

	///
	/// R�cup�re la temporisation utilis�e pour les nouvelles connexions.
	/// La temporisation est exprim�e au format TDCLCommLayer.
	///
	/// \return la temporisation au format \c TDCLCommLayer
	///
	virtual	long		GetTimeout( void );

	///
	/// M�thode appel�e par TDCLPipe::Disconnect() pour indiquer qu'une
	/// connexion a �t� ferm�e. D�cr�mente le compteur des connexions ouvertes.
	///
	/// \param inPipe	connexion qui a �t� ferm�e
	///
	virtual	void		Disconnected( TDCLPipe* inPipe );

	/// \name utilitaires

	///
	/// D�termine si OpenTransport est disponible.
	///
	/// \return	\c true si OpenTransport est disponible, \c false sinon.
	///
	static	Boolean		IsAvailable( void );
	
	///
	/// Ferme OpenTransport s'il n'est plus utilis�, i.e. s'il n'y a plus
	/// d'instance de cette classe.
	/// Cette m�thode est appel�e par le destructeur. Cependant, si vous avez
	/// appel� \c IsAvailable pour une sous-classe qui peut avoir besoin de OT
	/// et que finalement, vous d�cidez de ne pas utiliser OT, c'est une bonne
	/// id�e d'appeler cette m�thode pour fermer OT. �a ne peut pas faire de
	/// mal.
	///
	static	void		CloseOT( void );

protected:
	///
	/// Commence � �couter.
	///
	virtual	void		DoStartListening( void );

	///
	/// Arr�te d'�couter, i.e. arr�te d'accepter les requ�tes de connexions.
	///
	virtual	void		DoStopListening( void );

	///
	/// Initialise OpenTransport si requis et joue avec gOTState.
	///
	/// \throws TDCLNotAvailableException si OT n'est pas disponible.
	///
	static	void		InitOT( void );

	///
	/// Constructeur pour les sous-classes.
	/// Ce constructeur n'appelle pas Init. C'est pour les classes qui veulent
	/// g�rer leur configuration OT d'abord et appeler Init ensuite.
	///
	/// \param inThreadsIntf	interface sur les processus l�gers.
	/// \param inMaxPipeCount	nombre maximal de connexion simultan�es.
	/// \param inTimeout		d�lai de temporisation
	///
	TDCLOpenTransport(
					IDCLThreads* inThreadsIntf,
					KUInt32	inMaxPipeCount = kDefaultPipeCount,
					long	inTimeout = kDefaultTimeout
				);

	///
	/// Initialise la couche et incr�mente le compteur de couches OT ouvertes.
	///
	/// \param inConfiguration	configuration pour OT
	/// \param inLocalBindInfo	adresse locale du serveur.
	///
	void		Init(
					OTConfigurationRef inConfiguration,
					TBind* inLocalBindInfo
				);

private:

	///
	/// Classe pour une connexion avec OpenTransport.
	///
	class TOTPipe
		:
			public TDCLPipe
	{
	public:
		///
		/// La classe principale peut acc�der aux m�thodes prot�g�es et priv�es.
		///
		friend class TDCLOpenTransport;
		
		///
		/// Destructeur. Ferme la connexion si elle n'�tait pas d�j� ferm�e.
		///
		virtual				~TOTPipe( void );

		///
		/// Lit des octets.
		///
		/// \param outBuffer	m�moire tampon pour les octets lus.
		/// \param ioCount		nombre d'octets � lire en entr�e, lus en sortie.
		///						Cette valeur est mise � jour avant que 
		///						l'exception ne soit lanc�e si un probl�me est
		///						survenu.
		/// \throws TDCLIOException	si un probl�me est survenu (autre que EOF)
		///
		virtual	void		Read( void* outBuffer, KUInt32* ioCount );

		///
		/// Ecrit des octets.
		///
		/// \param inBuffer		m�moire tampon pour les octets � �crire.
		/// \param ioCount		nombre d'octets � �crire en entr�e, �cris en
		///						sortie. Cette valeur est mise � jour avant que
		///						l'exception ne soit lanc�e si un probl�me est
		///						survenu.
		/// \throws TDCLIOException	si un probl�me est survenu.
		///
		virtual	void		Write( const void* inBuffer, KUInt32* ioCount );
		
		///
		/// D�termine quel est le nombre d'octets disponibles dans la m�moire
		/// tampon d'entr�e.
		///
		/// \return le nombre d'octets disponibles.
		///
		virtual	Boolean		BytesAvailable( void );

		///
		/// Vide la m�moire tampon de sortie. Tout simplement.
		///
		virtual void		FlushOutput( void );
		
		///
		/// D�connecte le canal de communication avec le client.
		///
		/// \remark	une fois que cette m�thode est appel�e, l'objet connexion
		///			est inutilisable. Il peut �tre supprim� par l'appelant �
		///			tout instant.
		///
		virtual	void		Disconnect( void );
		
		///
		/// R�cup�re la temporisation pour cette connexion.
		/// La temporisation est exprim�e en secondes ou c'est une des
		/// constantes de TDCLCommLayer (dit "format TDCLCommLayer").
		///
		/// \return la temporisation au format TDCLCommLayer.
		///
		virtual	long		GetTimeout( void );

		///
		/// Change la temporisation pour cette connexion.
		/// La temporisation est exprim�e en secondes ou c'est une des
		/// constantes de TDCLCommLayer.
		///
		/// \param inTimeout	temporisation au format TDCLCommLayer.
		///
		virtual	void		SetTimeout( long inTimeout );

		///
		/// M�thode appel�e par le lien pour dire qu'il souhaite
		/// �tre pr�venu d�s que des donn�es sont pr�sentes.
		/// Au d�part, l'interface de communication ne pr�vient
		/// pas le lien de la pr�sence de donn�es.
		///
		virtual	void		ClearDataPresent( void );

	protected:
		///
		/// Constructeur unique.
		/// Il est prot�g� parce que seule les couches de communication doivent
		/// cr�er des connexions.
		///
		/// \param inCommLayer	couche de communication � laquelle est
		///						rattach�e la connexion.
		/// \param inEndpoint	interface de communication OpenTransport
		///						associ�e � la connexion.
		/// \param inTimeout	d�lai de temporisation au format TDCLCommLayer.
		///
		TOTPipe(
				TDCLOpenTransport*	inCommLayer,
				TEndpoint*			inEndpoint,
				long				inTimeout
				);

		///
		/// R�cup�re l'interface de communication OpenTransport associ�e �
		/// cette connexion.
		///
		/// \return l'interface de communication OpenTransport.
		///
		inline	TEndpoint*	GetEndpoint( void )
			{
				return mEndpoint;
			}
	
	private:
		///
		/// Constructeur par copie volontairement indisponible.
		///
		/// \param inCopy		objet � copier
		///
		TOTPipe( const TOTPipe& inCopy );

		///
		/// Op�rateur d'assignation volontairement indisponible.
		///
		/// \param inCopy		objet � copier
		///
		TOTPipe& operator = ( const TOTPipe& inCopy );

		///
		/// Fonction de notification OpenTransport pour g�rer la d�connexion.
		///
		/// \param inContext	contexte, ici objet connexion.
		/// \param inEvent		�v�nement qui est l'objet de la notification.
		/// \param inResult		r�sultat de cet �v�nement.
		/// \param inCookie		biscuit (inutilis�).
		static pascal void	Notify(
									void* inContext,
									OTEventCode inEvent,
									OTResult inResult,
									void* inCookie
								);

		/// \name Variables

		long			mTimeout;		///< temporisation au format
										///< TDCLCommLayer
		TEndpoint*		mEndpoint;		///< interface de communication
										///< OpenTransport pour cette
										///< connexion.
		Boolean			mDisconnected;	///< drapeau qui vaut true si la
										///< connexion a �t� ferm�e (par le
										///< client)
		OTNotifyUPP		mNotifierUPP;	///< UPP pour la fonction de
										///< notification.
		Boolean			mDataPresent;	///< Si on sait que des donn�es sont
										///< pr�sentes.
		
	};

	///
	/// La classe TOTPipe doit pouvoir acc�der aux m�thodes de cette classe.
	///
	friend class TOTPipe;

	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLOpenTransport( const TDCLOpenTransport& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLOpenTransport& operator = ( const TDCLOpenTransport& inCopy );

	///
	/// Cr�e un nouveau bout de connexion � partir de la configuration et
	/// de l'addresse locale.
	///
	/// \param forListening	si le nouveau bout de connexion doit �tre pour
	///						�couter
	/// \return un nouveau bout de connexion OT
	///
	TEndpoint*			GetNewEndpoint( Boolean forListening );

	///
	/// Gestionnaire d'�v�nements appel� par OT lors d'interruptions.
	///
	static pascal void	Notify(
								void* inContext,
								OTEventCode inEvent,
								OTResult inResult,
								void* inCookie );
	
	///
	/// Constantes pour cette classe.
	///
	enum {
		kOTMaxBackLogSize	=	128,	///< Nombre de requ�tes simultan�es
										///< g�r�es par Listen.
		kOTDefaultTimeout	=	30		///< D�lai de temporisation par
										///< d�faut (en secondes)
	};

	///
	/// Etat d'OpenTransport.
	///	
	enum EOTState {
		kUninitialized,		///< Etat initial
		kNotAvailable,		///< OT n'est pas disponible
		kInitialized,		///< OT est disponible et a �t� initialis�
		kAvailable			///< OT est disponiblel mais a �t� ferm� (ou n'a
							///< pas �t� initialis�)
	};

	/// \name Variables

	OTConfigurationRef	mConfiguration;		///< Configuration pour les bouts
											///< de connexion.
	TBind				mLocalBindInfo;		///< Adresse locale.
	KUInt32				mCurrentPipeCount;	///< Nombre de connexions ouvertes.
	TEndpoint*			mServerEndpoint;	///< Bout de connexion du serveur.
	
	long				mTimeout;			///< Temporisation au format
											///< TDCLCommLayer (nombre de
											///< secondes + constantes)
	IDCLThreads*		mThreadsIntf;		///< Interface pour les processus
											///< l�gers (pour Yield)
	static KUInt32		gInstanceCount;		///< Compteur sur lesinstances de
											///< TDCLOpenTransport pour fermer
											///< OpenTransport lorsqu'il n'est
											///< plus utilisi�.
											///< Note: some sub-classes might
											///< need to open OT to know if
											///< their service is available
											///< (typically Serial). In that
											///< case, OT will only be closed
											///< when last instance dies (or
											///< if you call
											///< CloseOpenTransport).
	static EOTState		gOTState;			///< Whether OpenTransport is
											///< available/initialized/closed.
	Boolean				mListening;			///< Whether we are listening or not
	OTNotifyUPP			mNotifierUPP;		///< R�f�rence sur le gestionnaire
											///< d'�v�nements.
};

#endif
		// __TDCLOPENTRANSPORT__

// ========================================================================== //
// The use of anthropomorphic terminology when dealing with computing systems //
// is a symptom of professional immaturity.                                   //
//                 -- Edsger Dijkstra                                         //
// ========================================================================== //
