// ==============================
// Fichier:			TDCLFDSerialPort.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			4/4/2003
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
// The Original Code is TDCLFDSerialPort.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k,
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2003-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//   Simon Stapleton <simon@tufty.co.uk>
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLFDSerialPort.h,v 1.4 2004/11/24 14:08:55 paul Exp $
// ===========

#ifndef _TDCLFDSERIALPORT_H
#define _TDCLFDSERIALPORT_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/TDCLSyncCommLayer.h>

// POSIX
#include <termios.h>

///
/// Classe pour une couche de communication � base d'un port s�rie acc�d�
/// via un descripteur de fichier. C'est un port s�rie Unix (dans /dev/) qui
/// r�pond aux appels classiques fctl & co.
/// La communication sur ce port s�rie se fait par d�faut avec la compression
/// MNP.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	UTestCommLayers
///
class TDCLFDSerialPort
	:
		public TDCLSyncCommLayer
{
public:
    /// Modes of the associated pipe
    enum {
        kModePlain,
        kModeMNP,
        kModeHammer
    };

	///
	/// Unique constructeur � partir du chemin vers le port s�rie.
	/// Si ce chemin est \c nil, il devra �tre pr�cis� dans la m�thode
	/// Init.
	///
	/// \param inThreadsIntf	interface pour les processus l�gers
	/// \param inDevPath		chemin vers le port s�rie (copi�)
	/// \param inBaud			vitesse de la connexion (38400: vitesse par d�faut
	///							du Newton).
	/// \param inMode			pipe mode
	///
	TDCLFDSerialPort(
				IDCLThreads* inThreadsIntf,
				const char* inDevPath,
				long inBaud,
				KUInt32 inMode );

	///
	/// Unique constructeur � partir du chemin vers le port s�rie.
	/// Si ce chemin est \c nil, il devra �tre pr�cis� dans la m�thode
	/// Init.
	///
	/// \param inThreadsIntf	interface pour les processus l�gers
	/// \param inDevPath		chemin vers le port s�rie (copi�)
	/// \param inBaud			vitesse de la connexion (38400: vitesse par d�faut
	///							du Newton).
	/// \param inUseMNP			si on fait de la compression MNP.
	///
	TDCLFDSerialPort(
				IDCLThreads* inThreadsIntf,
				const char* inDevPath,
				long inBaud = 38400,
				Boolean inUseMNP = true );

	///
	/// Destructeur.
	/// Arr�te le serveur.
	///
	virtual ~TDCLFDSerialPort( void );
	
	/// \name interface serveur

	///
	/// Retourne un objet connexion repr�sentant le canal de communication
	/// avec le client ou \c nil s'il n'y a pas de requ�te de connexion
	/// pr�sente.
	/// Ce doit �tre un objet cr�� avec new. L'appelant devra le supprimer.
	///
	/// \return	un nouvel objet TPipe cr�� avec new repr�sentant la connexion
	///			ou \c nil.
	///
	virtual	TDCLPipe*	DoAccept( void );

	///
	/// Refuse la premi�re requ�te de connexion.
	/// Ne fait rien si aucune connexion n'est pr�sente.
	///
	virtual	void		DoRefuse( void );

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
	/// M�thode appel�e par TPipe::Disconnect() pour indiquer qu'une connexion
	/// a �t� ferm�e. D�cr�mente le compteur des connexions ouvertes.
	///
	/// \param inPipe	connexion qui a �t� ferm�e
	///
	virtual	void		Disconnected( TDCLPipe* inPipe );

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
	/// Attend qu'une requ�te se pr�sente.
	///
	/// \return \c true si une requ�te est pr�sente, \c false si la m�thode a �t�
	/// interrompue.
	///
	virtual	Boolean		WaitForIncomingRequest( void );

	///
	/// Accesseur sur l'interface de communication.
	///
	/// \return	la r�f�rence sur l'interface de communication.
	///
	inline int			GetSerialFD( void )
		{
			return mSerialFD;
		}

	///
	/// Initialise l'interface de communication pour un chemin BSD donn�.
	/// Cette m�thode permet de ne pas fournir le chemin dans le constructeur.
	/// Elle ne doit pas �tre appel�e plus d'une fois ou si un chemin a �t�
	/// sp�cifi� dans le constructeur.
	///
	void				Init( const char* inDevPath );

	///
	/// Attend des donn�es (m�thode bloquante).
	///
	/// \return \c true si des donn�es sont pr�sentes, \c false sinon.
	///
	Boolean				Select( void );

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLFDSerialPort( const TDCLFDSerialPort& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLFDSerialPort& operator = ( const TDCLFDSerialPort& inCopy );

	///
	/// Ouvre et configure le port s�rie.
	///
	/// \throws TDCLIOException si un probl�me est survenu.
	///
	void				OpenAndConfigure( void );

	///
	/// Ferme et rouvre le port s�rie.
	///
	/// \throws TDCLIOException si un probl�me est survenu.
	///
	void				Reset( void );

	///
	/// On donne tous les droits a la classe fille.
	///
	class TFDSerialPortPipe;
	friend class TFDSerialPortPipe;

	///
	/// Class pour les connexions.
	///
	class TFDSerialPortPipe
		:
			public TSyncPipe
	{
	public:
		/// La classe m�re est une amie.
		friend class TDCLFDSerialPort;

		///
		/// Destructeur. Ferme la connexion si elle n'�tait pas d�j� ferm�e.
		///		
		virtual				~TFDSerialPortPipe( void );

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
		/// D�termine quel est le nombre d'octets disponibles dans la m�moire tampon d'entr�e.
		///
		/// \return le nombre d'octets disponibles.
		///
		virtual	Boolean		BytesAvailable( void );

		///
		/// Attend que des donn�es se pr�sentent. Cette m�thode est synchrone (c'est l'int�r�t
		/// de cette classe). Elle retourne si des donn�es sont pr�sentes ou si elle a �t�
		/// interrompue par Disconnect.
		///
		/// \return \c true si une requ�te est pr�sente, \c false si la m�thode a �t�
		/// interrompue.
		///
		virtual Boolean 	WaitForIncomingData( void );

		///
		/// D�connecte le canal de communication avec le client.
		///
		/// \remark	une fois que cette m�thode est appel�e, l'objet connexion est inutilisable.
		/// 		Il peut �tre supprim� par l'appelant � tout instant.
		///
		virtual	void		DoDisconnect( void );
		
		///
		/// R�cup�re la temporisation pour cette connexion.
		/// La temporisation est exprim�e en secondes ou c'est une des constantes
		/// de TDCLCommLayer (dit "format TDCLCommLayer").
		///
		/// \return la temporisation au format TDCLCommLayer.
		///
		virtual	long		GetTimeout( void );

		///
		/// Change la temporisation pour cette connexion.
		/// La temporisation est exprim�e en secondes ou c'est une des constantes
		/// de TDCLCommLayer.
		///
		/// \param inTimeout	temporisation au format TDCLCommLayer.
		///
		virtual	void		SetTimeout( long inTimeout );

	protected:
		///
		/// Constructeur.
		/// Vous n'�tes pas suppos�s cr�er des TSocketPipe vous-m�mes.
		///
		/// \param inCommLayer		couche de communication � laquelle la connexion
		///							appartient.
		///
		TFDSerialPortPipe(
				TDCLFDSerialPort*	inCommLayer
			);

	private:
		int						mSerialFD;			///< Descripteur de fichier de l'interface
													///< de connexion.
		long					mTimeout;			///< Temporisation pour cette
													///< interface.
		Boolean					mDisconnected;		///< Si la connexion a �t� rompue par le client.
		FILE*					mLog;
	};
	
	/// \name Variables

	Boolean						mIsConnected;		///< Si une connexion est ouverte.
	int							mSerialFD;			///< Descripteur de fichier de l'interface
													///< de communication.
	char*						mDevPath;			///< Chemin vers le fichier BSD.
	long						mBaud;				///< Vitesse du lien en baud.
	KUInt32						mPipeMode;			///< On utilise MNP?
	struct termios				mOriginalOptions;	///< Options originales.
	Boolean						mReset;				///< Si on est en train de r�initialiser
													///< le fichier.
	Boolean						mDisconnecting;		///< Si on est en train de se d�connecter.
	Boolean						mRequestPresent;	///< Si une requ�te est pr�sente.
	IDCLThreads::ISemaphore*	mResetMutex;		///< S�maphore pour bloquer
													///< Select lors de la r�initialisation.
	IDCLThreads::ISemaphore*	mWaitRequestMutex;	///< S�maphore pour bloquer
													///< Select tant qu'on n'est pas connect�.
	long						mTimeout;			///< Temporisation pour cette
													///< interface.
};

#endif
		// _TDCLFDSERIALPORT_H

// ================================================== //
// The less time planning, the more time programming. //
// ================================================== //
