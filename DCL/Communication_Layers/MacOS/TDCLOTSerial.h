// ==============================
// Fichier:			TDCLOTSerial.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			27/01/2002
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
// The Original Code is TDCLOTSerial.h.
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
// $Id: TDCLOTSerial.h,v 1.3 2004/11/24 14:08:54 paul Exp $
// ===========

#ifndef __TDCLOTSERIAL__
#define __TDCLOTSERIAL__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/MacOS/TDCLOpenTransport.h>

///
/// Classe pour la couche de communication port s�rie avec OpenTransport
/// (avec compression MNP fournie par TDCLMNPPipe).
/// 
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
/// \todo	� terminer (il faut surcharger la m�thode qui cr�e les EP et
///			avoir notre propre classe d'EP)
///
class TDCLOTSerial
	:
		public TDCLOpenTransport
{
public:
	///
	/// Constructeur.
	///
	/// \param inThreadsIntf	interface pour les threads (utilis�e pour Yield).
	/// \param inPort			index du port s�rie (base 0)
	/// \param inBaud			vitesse du port s�rie (par d�faut, 38400, la
	///							vitesse par d�faut sur le Newton)
	/// \param inTimeout		d�lai de temporisation, format CommLayer.
	///
	TDCLOTSerial(
			IDCLThreads* inThreadsIntf,
			unsigned long inPort,
			long inBaud = 38400,
			long inTimeout = kDefaultTimeout
		);

	///
	/// V�rifie que le service est disponible.
	///
	/// \return \c true si le service est disponible, \c false sinon.
	///
	static	Boolean		IsAvailable( void );

	///
	/// D�termine le nom d'un port s�rie. Utile pour �tre sympa avec l'utilisateur.
	/// Retourne une cha�ne allou�e avec malloc.
	///
	/// \param inIndex			index du port s�rie (base 0)
	/// \return une cha�ne allou�e avec malloc ou nil si le port n'existe pas.
	///
	static	char*		GetSerialPortName( unsigned long inIndex );

	///
	/// D�termine le nombre de ports s�rie disponibles.
	///
	/// \return le nombre de ports s�rie (n) sur cette machine. L'index du port
	///			pour les autres m�thodes doit �tre entre 0 et n - 1.
	///
	static	unsigned long	CountSerialPorts( void );

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

private:
	
	///
	/// D�termine la cha�ne de configuration pour un port s�rie donn� et
	/// le nom � montrer � l'utilisateur. Si le port n'existe pas, aucun
	/// des param�tres n'est modifi�.
	///
	/// \param inIndex			index du port s�rie (base 0)
	/// \param outConfigStr		cha�ne (allou�e par l'appelant) pour la
	///							configuration. Si elle vaut \c nil, elle
	///							n'est pas remplie.
	/// \param outNameStr		pointeur vers une cha�ne allou�e par cette
	///							m�thode avec malloc qui contient le nom
	///							du port s�rie. Rien n'est allou� si ce
	///							pointeur vaut nil.
	/// \return \c true si le port a �t� trouv�, \c false sinon.
	///
	static	Boolean		GetSerialPortInfos(
										unsigned long inIndex,
										char outConfigStr[36],
										char** outNameStr );

	/// \name variables priv�es
	long				mBaud;	///< vitesse du port s�rie
};

#endif
		// __TDCLOTSERIAL__

// ====================================================================== //
// Documentation is like sex: when it is good, it is very, very good; and //
// when it is bad, it is better than nothing.                             //
//                 -- Dick Brandon                                        //
// ====================================================================== //