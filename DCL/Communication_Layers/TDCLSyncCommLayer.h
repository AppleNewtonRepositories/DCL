// ==============================
// Fichier:			TDCLSyncCommLayer.h
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
// The Original Code is TDCLSyncCommLayer.h.
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
// $Id: TDCLSyncCommLayer.h,v 1.3 2004/11/24 14:08:54 paul Exp $
// ===========

#ifndef _TDCLSYNCCOMMLAYER_H
#define _TDCLSYNCCOMMLAYER_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/TDCLCommLayer.h>
#include <DCL/Interfaces/TDCLThread.h>
#include <DCL/Communication_Layers/TDCLPipe.h>

// Pr�-d�clarations.
class IDCLThreads;

///
/// Classe pour une interface de communication synchrone qui requiert
/// donc un processus l�ger s�par�.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLSyncCommLayer
	:
		public TDCLCommLayer,
		protected TDCLThread
{
public:
	///
	/// Constructeur.
	///
	/// Enregistre le nombre maximum de connexion dans \c mMaxPipeCount.
	/// Enregistre aussi \p inFlushAvailable et \p inTimeout dans les champs
	/// priv�s correspondants.
	///
	/// \remark ce constructeur est publique, mais la classe est abstraite.
	///
	/// \param inThreadsIntf	interface pour les processus l�gers.
	/// \param inFlushAvailable	si la couche de communication sait vider la
	///							m�moire tampon de sortie.
	///							Si la couche de communication ne sait pas le
	///							faire, l'appelant devra attendre avant de
	///							fermer la connexion.
	/// \param inMaxPipeCount	nombre maximum de connexion simultan�es.
	///							0 signifie pas de limite.
	///
	TDCLSyncCommLayer(
			IDCLThreads* inThreadsIntf,
			Boolean	inFlushAvailable = false,
			KUInt32	inMaxPipeCount = kDefaultPipeCount
			);
	
	///
	/// Commence � �couter.
	/// Lance le processus l�ger.
	///
	/// \param inServer	serveur � pr�venir lorsqu'une requ�te est arriv�e.
	/// \throws TDCLException si le serveur est d�j� en train d'�couter.
	///
	virtual void		StartListening( TDCLServer* inServer );

	///
	/// Arr�te d'�couter, i.e. arr�te d'accepter les requ�tes de connexions.
	/// Dit au processus l�ger de s'arr�ter une fois que DoStopListening a termin�.
	/// Ne fait rien si on n'est pas en train d'�couter.
	///
	virtual void		StopListening( void );

protected:
	///
	/// M�thode appel�e dans la m�thode Run juste avant la boucle qui appelle
	/// WaitForIncomingRequest.
	///
	virtual	void		DoStartListening( void ) = 0;

	///
	/// Arr�te d'�couter, i.e. arr�te d'accepter les requ�tes de connexions.
	/// Cette m�thode doit d'abord interrompre l'attente dans la m�thode Run
	/// et ceci ne doit pas avoir de cons�quence si on n'est pas en train d'attendre dans
	/// cette m�thode.
	/// Attention aux possible probl�me d'attente/de r�veil.
	///
	virtual	void		DoStopListening( void ) = 0;

	///
	/// Attend qu'une requ�te se pr�sente. Cette m�thode est synchrone (c'est l'int�r�t
	/// de cette classe). Elle retourne si une requ�te est pr�sente ou si elle a �t�
	/// interrompue par DoStopListening.
	///
	/// \return \c true si une requ�te est pr�sente, \c false si la m�thode a �t�
	/// interrompue (ou si on n'�coute plus).
	///
	virtual Boolean 	WaitForIncomingRequest( void ) = 0;

	///
	/// Retourne un objet connexion repr�sentant le canal de communication avec le client
	/// ou \c nil s'il n'y a pas de requ�te de connexion pr�sente.
	/// C'est un objet cr�� avec \c new. L'appelant devra le supprimer.
	/// Cette m�thode appelle DoAccept et ensuite r�veille le processus l�ger pour attendre la
	/// pr�sence de nouvelles requ�tes.
	///
	/// \return un nouvel objet TDCLPipe cr�� avec \c new repr�sentant la connexion ou \c nil.
	///
	virtual	TDCLPipe*	Accept( void );
	
	///
	/// Refuse la premi�re requ�te de connexion.
	/// Ne fait rien si aucune connexion n'est pr�sente.
	/// Cette m�thode appelle DoRefuse et ensuite r�veille le processus l�ger pour attendre la
	/// pr�sence de nouvelles requ�tes.
	///
	virtual	void		Refuse( void );
	
	///
	/// Retourne un objet connexion repr�sentant le canal de communication avec le client
	/// ou \c nil s'il n'y a pas de requ�te de connexion pr�sente.
	/// C'est un objet cr�� avec \c new. L'appelant devra le supprimer.
	///
	/// \return un nouvel objet TDCLPipe cr�� avec \c new repr�sentant la connexion ou \c nil.
	///
	virtual	TDCLPipe*	DoAccept( void ) = 0;
	
	///
	/// Refuse la premi�re requ�te de connexion.
	/// Ne fait rien si aucune connexion n'est pr�sente.
	///
	virtual	void		DoRefuse( void ) = 0;
	
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
	/// On donne tous les droits a la classe fille.
	///
	class TSyncPipe;
	friend class TSyncPipe;

	///
	/// Class pour les connexions synchrone.
	///
	class TSyncPipe
		:
			public TDCLPipe,
			protected TDCLThread
	{
	public:
		/// La classe m�re est une amie.
		friend class TDCLSyncCommLayer;

		///
		/// Constructeur.
		/// Remplit les champs priv�s.
		///
		/// \param inThreadsIntf	interface pour les processus l�gers.
		/// \param inCommLayer		couche de communication � laquelle est
		///							rattach�e la connexion.
		///
		TSyncPipe(
				IDCLThreads* inThreadsIntf,
				TDCLSyncCommLayer*	inCommLayer );

		///
		/// Attend que des donn�es se pr�sentent. Cette m�thode est synchrone (c'est l'int�r�t
		/// de cette classe). Elle retourne si des donn�es sont pr�sentes ou si elle a �t�
		/// interrompue par Disconnect.
		///
		/// \return \c true si des donn�es sont pr�sentes, \c false si la m�thode a �t�
		/// interrompue.
		///
		virtual Boolean 	WaitForIncomingData( void ) = 0;

		///
		/// D�connecte le canal de communication avec le client.
		/// Appelle DoDisconnect et attend que le processus l�ger ait termin�.
		///
		/// \remark	une fois que cette m�thode est appel�e, l'objet connexion est inutilisable.
		/// 		Il peut �tre supprim� par l'appelant � tout instant.
		///
		virtual	void		Disconnect( void );

		///
		/// D�connecte effectivement le canal de communication avec le client.
		/// Cette m�thode doit envoyer une interruption pour que WaitForIncomingData
		/// retourne.
		///
		virtual	void		DoDisconnect( void ) = 0;

		///
		/// M�thode appel�e par le lien pour dire qu'il est connect�
		/// via cette connexion. Cette m�thode est appel�e juste avant
		/// que des donn�es soient �chang�es.
		///
		/// Lance le processus l�ger et appelle la m�thode par d�faut.
		///
		/// \return l'interface de communication.
		///
		virtual	TDCLCommLayer*	Connected( TDCLLink* inLink );

		///
		/// M�thode appel�e par le lien pour dire qu'il souhaite
		/// �tre pr�venu d�s que des donn�es sont pr�sentes.
		/// Au d�part, l'interface de communication ne pr�vient
		/// pas le lien de la pr�sence de donn�es.
		///
		virtual	void		ClearDataPresent( void );

		///
		/// M�thode appel�e lorsqu'une exception n'est pas intercept�e.
		/// Lorsque cette m�thode retourne, le processus est termin�.
		///
		/// \param inException	l'exception si c'est une TDCLException,
		///			\c nil sinon.
		///
		virtual void HandleException( TDCLException* inException );

	protected:
		///
		/// M�thode ex�cut�e dans le processus.
		/// Boucle tant que WaitForIncomingData retourne \c true. � chaque fois que
		/// cette derni�re m�thode retourne \c true, envoie un �v�nement au serveur.
		///
		virtual void Run( void );
	};
};

#endif
		// _TDCLSYNCCOMMLAYER_H

// ====================================================================== //
// Established technology tends to persist in the face of new technology. //
//                 -- G. Blaauw, one of the designers of System 360       //
// ====================================================================== //
