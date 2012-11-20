// ==============================
// Fichier:			TDCLXADSP.h
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
// The Original Code is TDCLXADSP.h.
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
// $Id: TDCLXADSP.h,v 1.9 2004/11/24 14:08:55 paul Exp $
// ===========

#ifndef __TDCLXADSP__
#define __TDCLXADSP__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/TDCLSyncCommLayer.h>

#ifdef __MWERKS__
	#pragma	warn_resultnotused	off
	#pragma	warn_implicitconv	off
	#pragma	warn_extracomma		off
#endif

#include <sys/types.h>
#include <sys/socket.h>

// AppleTalk dans Kernel.Framework
#include <netat/appletalk.h>
#include <netat/atp.h>

// AppleTalk dans AppleTalk.Framework
// (n'est pas dans le syst�me mais dans Darwin)
extern "C" {
#include "at_proto.h"
}

#ifdef __MWERKS__
	#pragma	warn_resultnotused	on
	#pragma	warn_implicitconv	reset
	#pragma	warn_extracomma		reset
#endif

#if !TARGET_OS_OPENSTEP
	#error "X ADSP n'est disponible que sur OS X"
#endif

///
/// Cette classe g�re le lien ADSP sur MacOS X.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \author Nicolas Zinovieff <krugazor@poulet.org>
/// \version $Revision: 1.9 $
///
class TDCLXADSP
	:
		public TDCLSyncCommLayer
{
public:
	///
	/// Constantes pour la classe TDCLXADSP
	///
	enum {
		kMaxADSPPipeCount		= 1024,	///< nombre maximal de connexions par d�faut.
										///< En ADSP/X, c'est 1024.
		kXADSPDefaultTimeout	= 30	///< Temps par d�faut (en secondes)
	};

	///
	/// Unique constructeur, � partir d'une interface, d'un nom de machine,
	/// du nombre maximum de connexions et du timeout.
	///
	/// Le nombre de connexions et le timeout pour cette couche de
	/// communication sont d�finies comme des constantes.
	///
	/// \param inThreadsIntf	interface pour les processus l�gers.
	/// \param inMachineName	nom de la machine, utilis�e dans l'adresse
	///							NBP. nil signifie que l'on va chercher le nom dans
	///							les pr�f�rences syst�mes.
	/// \param inMaxPipeCount	nombre maximal de connexion simultan�es autoris�es.
	/// \param inTimeout		temporisation
	///
	TDCLXADSP(
			IDCLThreads*	inThreadsIntf,
			const char*		inMachineName = nil,
			KUInt32			inMaxPipeCount = kMaxADSPPipeCount,
			long			inTimeout = kDefaultTimeout );

	///
	/// Destructeur.
	/// Appelle StopListening().
	///
	virtual				~TDCLXADSP( void );
	
	/// \name utilitaires

	///
	/// D�termine si ADSP est disponible.
	///
	/// \return true si ADSP est disponible.
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
	/// M�thode appel�e dans la m�thode Run juste avant la boucle qui appelle
	/// WaitForIncomingRequest.
	///
	/// Enregistre le service AppleTalk (NBP).
	///
	virtual	void		DoStartListening( void );

	///
	/// Arr�te d'�couter, i.e. arr�te d'accepter les requ�tes de connexions.
	/// Cette m�thode doit d'abord interrompre l'attente dans la m�thode Run
	/// et ceci ne doit pas avoir de cons�quence si on n'est pas en train d'attendre dans
	/// cette m�thode.
	/// Attention aux possible probl�me d'attente/de r�veil.
	///
	/// D�senregistre le service AppleTalk (NBP).
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

	///
	/// Cr�e l'interface de communication pour �couter, la lie et �coute.
	///
	/// \return une r�f�rence vers l'interface de communication ou un nombre
	///			n�gatif si une erreur est survenue. Le code de l'erreur est
	///			dans errno.
	///
	int					SocketBindAndListen( void );

private:
	///
	/// Droits pour la classe fille.
	///
	class TXADSPPipe;
	friend class TXADSPPipe;
	
	///
	/// Class pour les connexions.
	///
	class TXADSPPipe
		:
			public TSyncPipe
	{
	public:
		/// La classe m�re est une amie.
		friend class TDCLXADSP;

		///
		/// Destructeur. Ferme la connexion si elle n'�tait pas d�j� ferm�e.
		///		
		virtual				~TXADSPPipe( void );

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
		TXADSPPipe(
				TDCLXADSP*	inCommLayer,
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
		KUInt8			mNextByte;				///< Octet suivant.
		Boolean			mHasNextByte;			///< Si on a l'octet suivant.
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
	at_entity_t		mMachineEntity;			///< R�f�rence sur l'entit� ADSP.
};

#endif
		// __TDCLXADSP__

// =============================================================================== //
// "This is lemma 1.1.  We start a new chapter so the numbers all go back to one." //
//                 -- Prof. Seager, C&O 351                                        //
// =============================================================================== //