//==============================
// Fichier:			TTestServer.h
// Projet:			(Desktop Connection Library)
// Ecrit par:		Paul Guyot (pguyot@kallisys.net)
// 
// Cr�� le:			17/6/2003
// Tabulation:		4 espaces
// 
// Copyright:		� 2003 by Paul Guyot.
// 					Tous droits r�serv�s pour tous pays.
// Licence:			Licence R�flexive Kallisys
// 					http://www.kallisys.org/reflexive/
// ===========
// $Id: TTestServer.h,v 1.5 2003/09/17 10:43:49 paul Exp $
// ===========

#ifndef _TTESTSERVER_H
#define _TTESTSERVER_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Server/TDCLServer.h>

// ANSI C
#include <stdio.h>

class TDCLLogApplication;

///
/// Classe pour un serveur qui raconte sa vie sur radio stdout.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.5 $
///
class TTestServer
	:
		public TDCLServer
{
public:
	///
	/// Constructeur � partir d'une r�f�rence sur l'application.
	///
	/// \param inApplication	interface avec le syst�me h�te.
	///
	TTestServer( TDCLLogApplication* inApplication );

	///
	/// Commence � �couter.
	/// Cette m�thode est appel�e lorsque le serveur est d�marr� (depuis
	/// le processus l�ger du serveur).
	///
	virtual	void		DoStartListening( void );

	///
	/// Arr�te le serveur.
	///
	virtual	void		DoStop( void );
	
	///
	/// Ferme toutes les connexions brutalement.
	///
	virtual	void		DoKill( void );

	///
	/// G�re l'arriv�e d'une nouvelle connexion.
	///
	/// \param inCommLayer	interface de communication qui a re�u la requ�te.
	/// \return le nouvel �tat du serveur.
	/// \throws TDCLException si un probl�me est survenu.
	///
	virtual EState		HandleIncomingConnection(
								TDCLCommLayer* inCommLayer );

	///
	/// M�thode appel�e dans le processus l�ger du serveur pour indiquer
	/// qu'un lien a �t� d�connect� et qu'il faut fermer l'interface de
	/// communication.
	///
	/// \param inLink	le lien qui a �t� d�connect�.
	/// \return le nouvel �tat du serveur.
	/// \throws TDCLException si un probl�me est survenu.
	///
	virtual	EState		HandleLinkDisconnection( TDCLLink* inLink );

	///
	/// M�thode appel�e par le serveur lorsque rien ne se passe.
	/// Elle permet d'appeler Idle sur les interfaces de communication qui en
	/// ont besoin.
	///
	virtual	void		DoIdle( void );

private:
	FILE*				mLogFile; ///< Reference sur le flux.
};

#endif
		// _TTESTSERVER_H

// =============================================================================== //
// "This is lemma 1.1.  We start a new chapter so the numbers all go back to one." //
//                 -- Prof. Seager, C&O 351                                        //
// =============================================================================== //
