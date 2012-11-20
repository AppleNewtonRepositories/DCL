// ==============================
// Fichier:			TDCLBSDSocket.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			29/07/2002
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
// The Original Code is TDCLBSDSocket.h.
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
// $Id: TDCLBSDSocket.h,v 1.9 2004/11/24 14:08:55 paul Exp $
// ===========

#ifndef __TDCLBSDSOCKET__
#define __TDCLBSDSOCKET__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/TDCLSyncCommLayer.h>

#if !TARGET_OS_COMPAT_POSIX
	#error TDCLBSDSocket requiert la compatibilit� POSIX
#endif

// POSIX
#include <sys/types.h>

///
/// Cette classe g�re les sockets BSD sur toutes les plateformes qui le supportent.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \author Nicolas Zinovieff <krugazor@poulet.org>
/// \version $Revision: 1.9 $
///
class TDCLBSDSocket
	:
		public TDCLSyncCommLayer
{
public:
	///
	/// Constantes pour TDCLBSDSocket
	///
	enum {
		kBSDSocketMaxBackLogSize	= 128,	///< Taille maximale de la file d'attente
		kIANAAssignedPort			= 3679,	///< Port pour newton-dock
		kBSDSocketDefaultTimeout	= 30	///< Temps par d�faut (en secondes)
	};
	
	///
	/// Unique constructeur, � partir d'un num�ro de port,
	/// et du nombre maximum de connexions.
	///
	/// Le nombre de connexions et le timeout pour cette couche de
	/// communication sont d�finies comme des constantes.
	///
	/// \param inThreadsIntf	interface pour les processus l�gers.
	/// \param inPort			le port sur lequel on d�sire �couter.
	/// \param inMaxPipeCount	nombre maximal de connexion simultan�es autoris�es.
	/// \param inTimeout		temporisation
	///
	TDCLBSDSocket(
			IDCLThreads*	inThreadsIntf,
			unsigned short	inPort = kIANAAssignedPort,
			KUInt32			inMaxPipeCount = kDefaultPipeCount,
			long			inTimeout = kDefaultTimeout );

	///
	/// Destructeur.
	/// Appelle Destroy().
	///
	virtual				~TDCLBSDSocket( void );

	/// \name utilitaires

	///
	/// D�termine si les sockets bsd sont disponibles.
	///
	/// \return \c true si les sockets bsd sont disponibles.
	///
	static	Boolean		IsAvailable( void );

	/// \name interface serveur

	///
	/// Change la temporisation pour les nouvelles connexions.
	/// La temporisation est exprim�e au format \c TDCLCommLayer.
	///
	/// \param inTimeout	nouvelle temporisation au format \c TDCLCommLayer
	///
	virtual	void		SetTimeout( long inTimeout );

	///
	/// R�cup�re la temporisation utilis�e pour les nouvelles connexions.
	/// La temporisation est exprim�e au format \c TDCLCommLayer.
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
	/// \return \c true si une requ�te est pr�sente, \c false si la m�thode a
	///			�t� interrompue.
	///
	virtual	Boolean		WaitForIncomingRequest( void );

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

private:
	///
	/// Cr�e l'interface de communication pour �couter, la lie et �coute.
	///
	/// \return une r�f�rence vers l'interface de communication ou un nombre
	///			n�gatif si une erreur est survenue. Le code de l'erreur est
	///			dans errno.
	///
	int			SocketBindAndListen( void );

	///
	/// Droits pour la classe fille.
	///
	class TBSDSocketPipe;
	friend class TBSDSocketPipe;
	
	///
	/// Class pour les connexions.
	///
	class TBSDSocketPipe
		:
			public TSyncPipe
	{
	public:
		/// La classe m�re est une amie.
		friend class TDCLBSDSocket;

		///
		/// Destructeur. Ferme la connexion si elle n'�tait pas d�j� ferm�e.
		///		
		virtual				~TBSDSocketPipe( void );

		///
		/// D�termine si des octets sont disponibles dans la m�moire tampon
		/// d'entr�e.
		///
		/// \return \c true si des octets sont disponibles, \c false sinon.
		///
		virtual	Boolean		BytesAvailable( void );

		///
		/// R�cup�re la temporisation pour cette connexion.
		/// La temporisation est exprim�e en secondes ou c'est une des
		/// constantes de TDCLCommLayer (dit "format \c TDCLCommLayer").
		///
		/// \return la temporisation au format \c TDCLCommLayer.
		///
		virtual	long		GetTimeout( void );

		///
		/// Change la temporisation pour cette connexion.
		/// La temporisation est exprim�e en secondes ou c'est une des
		/// constantes de \c TDCLCommLayer.
		///
		/// \param inTimeout	temporisation au format \c TDCLCommLayer.
		///
		virtual	void		SetTimeout( long inTimeout );

		///
		/// Attend que des donn�es se pr�sentent. Cette m�thode est synchrone
		/// (c'est l'int�r�t de cette classe). Elle retourne si des donn�es
		/// sont pr�sentes ou si elle a �t� interrompue par Disconnect.
		///
		/// \return \c true si une requ�te est pr�sente, \c false si la m�thode
		///			a �t� interrompue.
		///
		virtual Boolean 	WaitForIncomingData( void );

		///
		/// D�connecte le canal de communication avec le client.
		///
		/// \remark	une fois que cette m�thode est appel�e, l'objet connexion
		///			est inutilisable. Il peut �tre supprim� par l'appelant �
		///			tout instant.
		///
		virtual	void		DoDisconnect( void );
		
		///
		/// Lit des octets.
		///
		/// \param outBuffer	m�moire tampon pour les octets lus.
		/// \param ioCount		nombre d'octets � lire en entr�e, lus en
		///						sortie. Cette valeur est mise � jour avant que
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
		
	protected:
		///
		/// Constructeur.
		/// Utilis� par la classe TDCLSocket.
		///
		/// \param inCommLayer		couche de communication � laquelle la
		///							connexion appartient.
		/// \param inClientSocket	descripteur de fichier de l'interface de
		///							connexion.
		/// \param inTimeout		temporisation pour cette connexion.
		///
		TBSDSocketPipe(
				TDCLBSDSocket*	inCommLayer,
				int				inClientSocket,
				long			inTimeout
			);
	
	private:
		/// \name Variables

		int				mClientSocket;			///< R�f�rence sur l'interface
												///< de communication.
		long			mTimeout;				///< Temporisation pour cette
												///< interface.
		int				mPublicPairMember;		///< �l�ment public de la
												///< "socket pair"
		int				mPrivatePairMember;		///< �l�ment priv� (= thread)
												///< de la "socket pair"
		Boolean			mClientSocketIsClosed;	///< Si l'interface de
												///< communication est ferm�e.
	};
	

	/// \name Variables priv�es.
	int				mServerSocket;			///< Descripteur de fichier de
											///< l'interface de communication
											///< du serveur.
	KUInt32			mCurrentPipeCount;		///< Nombre de connexions ouvertes.
	KUInt32			mBackLogSize;			///< Taille de la file d'attente de
											///< listen.
	long			mTimeout;				///< Temporisation au format
											///< \c TDCLCommLayer (nombre de
											///< secondes + constantes)
	int				mPublicPairMember;		///< �l�ment public de la "socket
											///< pair"
	int				mPrivatePairMember;		///< �l�ment priv� (= thread) de la
											///< "socket pair"
	Boolean			mSocketsAreClosed;		///< Si les sockets sont ferm�es.
	unsigned short	mPort;					///< Le port sur lequel on ecoute.
};
#endif
		// __TDCLBSDSOCKET__
		
// =============================================================================== //
// "What's the use of a good quotation if you can't change it?"                    //
//                 -- Dr. Who                                                      //
// =============================================================================== //
