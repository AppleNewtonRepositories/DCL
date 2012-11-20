// ==============================
// Fichier:			TDCLXADSPSocket.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			25/4/2004
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
// The Original Code is TDCLXADSPSocket.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLXADSPSocket.h,v 1.3 2004/11/24 14:08:55 paul Exp $
// ===========

#ifndef _TDCLXADSPSOCKET_H
#define _TDCLXADSPSOCKET_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/TDCLThread.h>

// DCL
#include <DCL/Interfaces/IDCLThreads.h>

///
/// Classe pour l'�mulation socket BSD des sockets ADSP.
/// Les sockets ADSP sous MacOS X:
/// - n'utilisent pas send/recv
/// - g�rent tr�s mal select
/// Cette classe g�re l'�mulation des sockets ADSP connect�es (uniquement).
/// Elle fonctionne avec un processus l�ger qui lit tout ce qui se pr�sente
/// et l'envoie sur une socket pair.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLXADSPSocket
	:
		protected TDCLThread
{
public:
	///
	/// Constructeur � partir d'une socket ADSP
	///
	/// \param inThreadsIntf	interface pour les processus l�gers
	/// \param inADSPSocket		interface de communication ADSP.
	///
	TDCLXADSPSocket(
			IDCLThreads* inThreadsIntf,
			int inADSPSocket );

	///
	/// Destructeur.
	///
	virtual ~TDCLXADSPSocket( void );

	///
	/// Accesseur sur la socket publique.
	///
	/// \return l'interface de communication BSD publique.
	///
	inline int	GetBSDSocket( void )
		{
			return mPublicPairMember;
		}

	///
	/// Ferme la paire et l'interface ADSP.
	/// Ceci a aussi pour cons�quence de sortir de la boucle du processus
	/// l�ger.
	///
	void			Close( void );

	///
	/// D�termine si une exception est survenue.
	///
	/// \return \c true si une exception est survenue.
	///
	inline Boolean	HadException( void ) const
		{
			return mHadException;
		}

	///
	/// D�termine l'exception qui est survenue.
	///
	/// \return l'exception survenue ou \c nil si ce n'est pas une
	///			TDCLException.
	///
	inline TDCLException*	GetException( void ) const
		{
			return mException;
		}

private:
	///
	/// M�thode ex�cut�e dans le processus.
	/// Boucle tant que WaitForIncomingRequest retourne \c true. � chaque fois que
	/// cette derni�re m�thode retourne \c true, envoie un �v�nement au serveur.
	///
	virtual void Run( void );

	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e.
	/// Lorsque cette m�thode retourne, le processus est termin�.
	///
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void HandleException( TDCLException* inException );

	///
	/// M�thode appel�e lorsqu'une erreur est survenue.
	/// Lance une exception si n�cessaire.
	///
	/// \return \c true si l'erreur est EBADF (socket ferm�e)
	///
	Boolean 	HandleError( void ) const;

	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLXADSPSocket( const TDCLXADSPSocket& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLXADSPSocket& operator = ( const TDCLXADSPSocket& inCopy );

	/// \name Variables
	int				mADSPSocket;			///< Interface ADSP.
	int				mPublicPairMember;		///< �l�ment public de la
											///< "socket pair"
	int				mPrivatePairMember;		///< �l�ment priv� (= thread) de la
											///< "socket pair"
	Boolean			mSocketsAreClosed;		///< Si les sockets sont ferm�es.
	TDCLException*	mException;				///< Exception
	Boolean			mHadException;			///< Si une exception est survenue.
};

#endif
		// _TDCLXADSPSOCKET_H

// ================ //
// /usr/news/gotcha //
// ================ //
