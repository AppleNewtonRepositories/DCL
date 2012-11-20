// ==============================
// Fichier:			TDCLEvent.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			28/3/2003
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
// The Original Code is TDCLEvent.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2003-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLEvent.h,v 1.3 2004/11/24 14:08:59 paul Exp $
// ===========

#ifndef _TDCLEVENT_H
#define _TDCLEVENT_H

#include <DCL/Headers/DCLDefinitions.h>

///
/// Classe pour les �v�nements envoy�s entre processus l�gers.
/// Un processus l�ger dort normalement tant qu'un tel �v�nement
/// n'a pas �t� envoy�.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLEvent
{
public:
	///
	/// Types d'�v�nements et masques pour filtrer avec WaitNextEvent.
	///
	enum EEventKind {
		kServerEvent		= 0x00000001,
		kServerEventMask	= kServerEvent,
		
		kLinkEvent			= 0x00000002,	///< �v�nements pour le lien (autre que les commandes)
		kIdleAppCommand		= 0x00000004,	///< Messages trait�s lorsque
											///< le lien est inactif
		kKbdAppCommand		= 0x00000008,	///< Messages trait�s lorsque
											///< le lien est en mode clavier
		kAnyAppCommandMask	= kIdleAppCommand | kKbdAppCommand,
		kAnyLinkEventMask	= kLinkEvent | kAnyAppCommandMask,
		
		kAnyEventMask		= 0xFFFFFFFF
	};

	///
	/// Identifiants pour les �v�nements.	
	/// Les identifiants en minuscule sont r�serv�s.
	///
	enum EEventID {
		// Messages re�us par le serveur.
		kStopServer			= FOUR_CHAR_CODE('stop'),	///< Il faut arr�ter le serveur.
		kWaitingConnection	= FOUR_CHAR_CODE('wait'),	///< Ay�, on attend le Newton (inData: l'objet TDCLCommLayer)
		kIncomingRequest	= FOUR_CHAR_CODE('toc '), 	///< Une connexion vient d'arriver (inData: l'objet TDCLCommLayer)
		kDisconnected		= FOUR_CHAR_CODE('disc'), 	///< Le lien a �t� d�connect� (inData: l'objet TDCLLink)

		// Messages re�us par le lien.
		kDisconnectLink		= FOUR_CHAR_CODE('disl'), 	///< Il faut d�connecter le lien.
		kCloseLink			= FOUR_CHAR_CODE('clsl'),	///< Il faut fermer le lien (il a �t� d�connect�).
		kBytesAvailable		= FOUR_CHAR_CODE('byta'),	///< Des octets sont disponibles.

		// Commandes
		kInstallPackage 	= FOUR_CHAR_CODE('inst'),	///< Commande pour installer un paquet.
										///< Le param�tre est un TFile.
										///< L'objet doit �tre un TDCLAppCmdFile.
		kStartUsingKeyboard = FOUR_CHAR_CODE('skbd'),	///< Commande pour commencer � utiliser le clavier.
		kEndUsingKeyboard 	= FOUR_CHAR_CODE('ekbd'),	///< Commande pour arr�ter d'utiliser le clavier.
		kSendCharacter 		= FOUR_CHAR_CODE('kbdc'),	///< Commande pour envoyer un caract�re.
										///< Le param�tre est constitu� de deux mots de 16 bits.
										///< L'objet doit �tre un TDCLAppKbdChar
		kSendString 		= FOUR_CHAR_CODE('kbds'),	///< Commande pour envoyer une cha�ne.
										///< Le param�tre est une cha�ne.
										///< L'objet doit �tre un TDCLAppKbdString
		kSynchronize	 	= FOUR_CHAR_CODE('sync')	///< Commande pour synchroniser.
	};

	///
	/// Constructeur � partir d'un type, d'un ID et de donn�es associ�es.
	///
	/// \param inEventKind	type (pour filtrer avec WaitNextEvent)
	/// \param inEventID	ID de l'�v�nement
	/// \param inData		donn�es associ�es � l'�v�nement.
	///
	TDCLEvent( EEventKind inEventKind, EEventID inEventID, void* inData = nil );

	///
	/// Constructeur par copie.
	/// Ne copie pas les pointeurs sur les autres �v�nements.
	///
	/// \param inCopy		objet � copier
	///
	TDCLEvent( const TDCLEvent& inCopy );

	///
	/// Destructeur.
	///
	virtual ~TDCLEvent( void );

	///
	/// Accesseur sur le type de l'�v�nement
	///
	/// \return	le type de cet �v�nement
	///
	inline EEventKind	GetEventKind( void ) const
		{
			return mEventKind;
		}

	///
	/// Accesseur sur l'ID de l'�v�nement
	///
	/// \return	l'ID de cet �v�nement
	///
	inline EEventID		GetEventID( void ) const
		{
			return mEventID;
		}

	///
	/// Accesseur sur les donn�es de l'�v�nement
	///
	/// \return	les donn�es de cet �v�nement
	///
	inline void*		GetEventData( void )
		{
			return mEventData;
		}

protected:
	///
	/// S�lecteur sur les donn�es de l'�v�nement
	///
	/// \param inEventData	nouvelles donn�es de l'�v�nement.
	///
	inline void			SetEventData( void* inEventData )
		{
			mEventData = inEventData;
		}

private:
	///
	/// La classe TDCLThread est une amie.
	/// C'est elle qui g�re la liste d'�v�nements.
	///
	friend class TDCLThread;
	
	///
	/// Accesseur sur l'�v�nement suivant.
	///
	/// \return	le pointeur sur l'�v�nement suivant
	///
	inline TDCLEvent*	GetNextEvent( void ) const
		{
			return mNextEvent;
		}

	///
	/// S�lecteur pour l'�v�nement suivant.
	///
	/// \param	inNextEvent	�v�nement suivant.
	///
	inline void	SetNextEvent( TDCLEvent* inNextEvent )
		{
			mNextEvent = inNextEvent;
		}

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLEvent& operator = ( const TDCLEvent& inCopy );

	/// \name Variables
	EEventKind		mEventKind;	///< Type de l'�v�nement.
	EEventID		mEventID;	///< ID de l'�v�nement.
	void*			mEventData;	///< Donn�es associ�es � l'�v�nement.
	TDCLEvent*		mNextEvent;	///< Pointeur sur l'�v�nement suivant
};

#endif
		// _TDCLEVENT_H

// =================================================== //
// You can tune a piano, but you can't tuna fish.      //
//                                                     //
// You can tune a filesystem, but you can't tuna fish. //
//                 -- from the tunefs(8) man page      //
// =================================================== //
