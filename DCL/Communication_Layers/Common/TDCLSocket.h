// ==============================
// Fichier:			TDCLSocket.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			29/3/2003
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
// The Original Code is TDCLSocket.h.
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
// $Id: TDCLSocket.h,v 1.7 2004/11/24 14:08:54 paul Exp $
// ===========

#ifndef _TDCLSOCKET_H
#define _TDCLSOCKET_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/TDCLSyncCommLayer.h>

#if !TARGET_OS_COMPAT_POSIX
	#error TDCLSocket requiert la compatibilit� POSIX
#endif

// POSIX
#include <sys/types.h>

///
/// Classe de base pour une couche de communication utilisant des "sockets".
/// Pour l'instant, on a deux sous-classes: MacOS X ADSP et BSD Sockets.
/// Ces couches de communication doivent utiliser select(3).
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.7 $
///
/// \test	UTestCommLayers
///
class TDCLSocket
	:
		public TDCLSyncCommLayer
{
public:
	///
	/// Constantes pour TDCLSocket
	///
	enum {
		kMaxSocketBackLog		= 128,	///< taille maximale de la file
										///< d'attente
		kSocketDefaultTimeout	= 30	///< (en secondes)
	};
	
	///
	/// Unique constructeur, � partir d'une interface pour les processus l�gers
	/// et du nombre maximum de connexions.
	///
	/// \param inThreadsIntf	interface pour les processus l�gers.
	/// \param inMaxPipeCount	nombre maximal de connexion simultan�es
	///							autoris�es.
	/// \param inTimeout		temporisation maximale � attendre lors
	///							d'op�ration d'E/S (format \c TDCLCommLayer)
	///
	TDCLSocket(
		IDCLThreads*	inThreadsIntf,
		KUInt32			inMaxPipeCount = kDefaultPipeCount,
		long			inTimeout = kDefaultTimeout
		);

	///
	/// Appelle StopListening() et ferme les interfaces.
	/// Cette m�thode doit �tre appel�e par les destructeurs des sous-classes.
	///
	void				Destroy( void );

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

	/// \name Interface TDCLSocket
	
	///
	/// Cr�e l'interface de communication pour �couter, la lie et �coute.
	///
	/// \param	inBackLogSize	taille de la liste des requ�tes (peut �tre
	///			inf�rieure � cette valeur si la couche ne g�re pas de liste
	///			aussi grande).
	/// \return une r�f�rence vers l'interface de communication ou un nombre
	///			n�gatif si une erreur est survenue. Le code de l'erreur est
	///			dans errno.
	///
	virtual int			SocketBindAndListen( KUInt32 inBackLogSize ) = 0;
	
	///
	/// Ferme une interface de communication.
	///
	/// \param inCookie	biscuit du client, \c nil pour le serveur.
	/// \param inSocket interface de communication � fermer.
	/// \return \c 0 ou un nombre n�gatif si une erreur est survenue. Le code
	///			de l'erreur est dans errno.
	///
	virtual int			DoClose( void* inCookie, int inSocket ) = 0;
	
	///
	/// Attend qu'une requ�te arrive et accepte cette requ�te.
	/// Si l'interface de communication est ensuite ferm�e, la requ�te sera
	/// refus�e.
	///
	/// \param outCookie		en sortie, biscuit du client.
	/// \param inServerSocket	interface de communication qui attend la requ�te.
	/// \return la r�f�rence vers la nouvelle interface de communication pour
	///			le client, 0 si on a �t� interrompu ou un nombre n�gatif si une
	///			erreur est survenue. Le code de l'erreur est dans \c errno.
	///
	virtual int			DoAccept( void** outCookie, int inServerSocket ) = 0;
	
	///
	/// Configure une interface de communication (client).
	/// Par d�faut ne fait rien.
	///
	/// \param inCookie	biscuit du client (fourni par DoAccept).
	/// \param inSocket interface de communication � configurer.
	/// \return un nombre n�gatif si une erreur est survenue, 0 si tout va
	///			bien.
	///
	virtual int			SetupClientSocket( void* inCookie, int inSocket );

	///
	/// Lit des octets depuis une interface de communication. L'interface
	/// doit attendre que le d�lai de temporisation soit �coul� avant de
	/// retourner une erreur si les donn�es ne sont pas pr�sentes.
	///
	/// \param inCookie			biscuit du client (fourni par DoAccept).
	/// \param inSocket			interface de communication o� lire.
	/// \param outBuffer		m�moire tampon o� mettre les octets lus.
	/// \param inCount			nombre d'octets � lire.
	/// \return le nombre d'octet effectivement lu ou un nombre n�gatif si une
	///			erreur est survenue. Le code de l'erreur est dans \c errno.
	///
	virtual int			Recv(
							void* inCookie,
							int inSocket,
							void* outBuffer,
							size_t inCount ) = 0;
	
	///
	/// Envoie des octets vers une interface de communication. L'interface
	/// doit attendre que le d�lai de temporisation soit �coul� avant de
	/// retourner une erreur si les donn�es ne sont pas envoy�es.
	///
	/// \param inCookie			biscuit du client (fourni par DoAccept).
	/// \param inClientSocket	interface de communication o� �crire.
	/// \param inBuffer			m�moire tampon o� se trouvent les octets �
	///							envoyer.
	/// \param inCount			nombre d'octets � lire.
	/// \return le nombre d'octet effectivement �crits ou un nombre n�gatif si
	///			une erreur est survenue. Le code de l'erreur est dans \c errno.
	///
	virtual int			Send(
							void* inCookie,
							int inClientSocket,
							const void* inBuffer,
							size_t inCount ) = 0;
	
	///
	/// Change la temporisation pour une interface de communication.
	/// La temporisation est exprim�e en secondes, 0 signifie pas de
	/// temporisation.
	/// Par d�faut ne fait rien, la temporisation est g�r�e dans les boucles
	/// de TSocketPipe::Read et de TSocketPipe::Write.
	///
	/// \param inCookie		biscuit du client (fourni par DoAccept).
	/// \param inSocket		interface de communication � r�gler.
	/// \param inTimeout	temporisation (en secondes)
	/// \return \c 0 si tout va bien ou un nombre n�gatif si une erreur est
	///			survenue. Le code de l'erreur est dans \c errno.
	///
	virtual	int			SetClientSocketTimeout(
							void* inCookie,
							int inSocket,
							long inTimeout );

	///
	/// D�termine la taille de la m�moire tampon de TDCLBufferedPipe � utiliser.
	/// Par d�faut, utilise la taille par d�faut.
	///
	/// \return la taille de la m�moire tampon pour TDCLBufferedPipe
	///
	virtual KUInt32		GetBufferedPipeBufferSize( void ) const;

	///
	/// Accesseur sur l'interface de communication qui �coute.
	///
	/// \return	la r�f�rence sur l'interface de communication du serveur
	///
	inline int			GetServerSocket( void )
		{
			return mServerSocket;
		}

private:
	///
	/// Droits pour la classe fille.
	///
	class TSocketPipe;
	friend class TSocketPipe;
	
	///
	/// Class pour les connexions.
	///
	class TSocketPipe
		:
			public TSyncPipe
	{
	public:
		/// La classe m�re est une amie.
		friend class TDCLSocket;

		///
		/// Destructeur. Ferme la connexion si elle n'�tait pas d�j� ferm�e.
		///		
		virtual				~TSocketPipe( void );

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
		/// \param inCookie			biscuit du client.
		/// \param inCommLayer		couche de communication � laquelle la
		///							connexion appartient.
		/// \param inClientSocket	descripteur de fichier de l'interface de
		///							connexion.
		/// \param inTimeout		temporisation pour cette connexion.
		///
		TSocketPipe(
				void*			inCookie,
				TDCLSocket*		inCommLayer,
				int				inClientSocket,
				long			inTimeout
			);

		///
		/// Accesseur sur le descripteur de fichier de l'interface de
		/// connexion.
		///
		/// \return descripteur de fichier de l'interface de connexion.
		///
		inline	int	GetClientSocket( void )
			{
				return mClientSocket;
			}
	
	private:
		/// \name Variables

		void*	 		mClientCookie;			///< Biscuit du client.
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
	
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLSocket( const TDCLSocket& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLSocket& operator = ( const TDCLSocket& inCopy );

	/// \name Variables priv�es.
	
	int			mServerSocket;			///< Descripteur de fichier de
										///< l'interface de communication du
										///< serveur.
	KUInt32		mCurrentPipeCount;		///< Nombre de connexions ouvertes.
	KUInt32		mBackLogSize;			///< Taille de la file d'attente de
										///< listen.
	long		mTimeout;				///< Temporisation au format
										///< \c TDCLCommLayer (nombre de
										///< secondes + constantes)
	int			mPublicPairMember;		///< �l�ment public de la "socket pair"
	int			mPrivatePairMember;		///< �l�ment priv� (= thread) de la
										///< "socket pair"
	Boolean		mSocketsAreClosed;		///< Si les sockets sont ferm�es.
};

#endif
		// _TDCLSOCKET_H

// ========================================================================= //
//         The FIELD GUIDE to NORTH AMERICAN MALES                           //
//                                                                           //
// SPECIES:        Cranial Males                                             //
// SUBSPECIES:     The Hacker (homo computatis)                              //
// Description:                                                              //
//         Gangly and frail, the hacker has a high forehead and thinning     //
//         hair.  Head disproportionately large and crooked forward,         //
//         complexion wan and sightly gray from CRT illumination.  He has    //
//         heavy black-rimmed glasses and a look of intense concentration,   //
//         which may be due to a software problem or to a pork-and-bean      //
//         breakfast.                                                        //
// Feathering:                                                               //
//         HOMO COMPUTATIS saw a Brylcreem ad fifteen years ago and believed //
//         it.  Consequently, crest is greased down, except for the cowlick. //
// Song:                                                                     //
//         A rather plaintive "Is it up?"                                    //
// ========================================================================= //
