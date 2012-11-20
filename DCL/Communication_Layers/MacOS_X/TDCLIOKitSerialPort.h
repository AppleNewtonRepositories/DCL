// ==============================
// Fichier:			TDCLIOKitSerialPort.h
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
// The Original Code is TDCLIOKitSerialPort.h.
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
// $Id: TDCLIOKitSerialPort.h,v 1.3 2004/11/24 14:08:55 paul Exp $
// ===========

#ifndef _TDCLIOKITSERIALPORT_H
#define _TDCLIOKITSERIALPORT_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/POSIX/TDCLFDSerialPort.h>

// ANSI C
#include <stdlib.h>

// MacOS X
#include <CoreFoundation/CFString.h>
#include <IOKit/IOKitLib.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>
#include <DCL/Exceptions/TDCLNotAvailableException.h>

///
/// Classe pour des ports s�rie sous MacOS X dont on obtient le nom
/// avec l'IOKit. Cette classe ne fait en fait pas grand chose sinon it�rer sur les ports
/// s�rie disponibles.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLIOKitSerialPort
	:
		public TDCLFDSerialPort
{
public:
	///
	/// Constructeur � partir d'un indice.
	///
	/// \param inThreadsIntf	interface pour les processus l�gers.
	/// \param inIndex			indice du port
	/// \param inBaud			vitesse du port
	///
	TDCLIOKitSerialPort(
				IDCLThreads* inThreadsIntf,
				KUInt32 inIndex,
				long inBaud = 38400 );

	///
	/// Constructeur � partir d'un chemin BSD sous forme de cha�ne CFStringRef.
	/// C'est le constructeur pr�f�r� (stocker l'indice du port n'est pas tip top).
	///
	/// \param inThreadsIntf	interface pour les processus l�gers.
	/// \param inDevPath		chemin du port
	/// \param inBaud			vitesse du port
	///
	TDCLIOKitSerialPort(
				IDCLThreads* inThreadsIntf,
				CFStringRef inDevPath,
				long inBaud = 38400 );

	///
	/// Destructeur.
	///
	virtual ~TDCLIOKitSerialPort( void );

	///
	/// D�termine le nom d'un port s�rie. Utile pour �tre sympa avec l'utilisateur.
	///
	/// \param inIndex			index du port s�rie (base 0)
	/// \return le nom du port ou \c nil si le port n'existe pas.
	///
	static	CFStringRef	GetSerialPortName( KUInt32 inIndex );

	///
	/// D�termine le nom d'un port s�rie avec son nom. Utile pour �tre sympa avec
	/// l'utilisateur. Cette m�thode retourne \c nil si le port n'existe pas.
	/// Remarque: cette m�thode compare avec la base I/O Kit.
	///
	/// \param inDevPath		chemin BSD du port s�rie.
	/// \return le nom du port ou \c nil si le port n'existe pas.
	///
	static	CFStringRef	GetSerialPortName( CFStringRef inDevPath );

	///
	/// D�termine si un port s�rie existe � partir de son chemin.
	/// Remarque: cette m�thode compare avec la base I/O Kit.
	///
	/// \param inDevPath		chemin BSD du port s�rie.
	/// \return \c true si le port existe, \c false sinon.
	///
	static	Boolean		IsAvailable( CFStringRef inDevPath );

	///
	/// D�termine le chemin BSD d'un port s�rie.
	///
	/// \param inIndex			index du port s�rie (base 0)
	/// \return le chemin BSD du port ou \c nil si le port n'existe pas.
	///
	static	CFStringRef	GetSerialPortPath( KUInt32 inIndex );

	///
	/// D�termine le nombre de ports s�rie disponibles.
	///
	/// \return le nombre de ports s�rie (n) sur cette machine. L'index du port
	///			pour les autres m�thodes doit �tre entre 0 et n - 1.
	///
	static	KUInt32	CountSerialPorts( void );

private:
	///
	/// R�cup�re un it�rateur sur les ports s�rie.
	///
	/// \param outIterator	en sortie, it�rateur sur les ports s�rie. L'it�rateur
	///						doit �tre lib�r� par l'appelant. Il n'est
	///						pas allou� si une exception est lanc�e.
	/// \throws TDCLNotAvailableException s'il n'y a pas de port s�rie.
	///
	static void GetSerialPortsIterator( io_iterator_t* outIterator );

	///
	/// Transforme une cha�ne CFStringRef en cha�ne US-ASCII allou�e avec malloc.
	///
	/// \param inStringRef	cha�ne CFStringRef.
	/// \return la cha�ne en US-ASCII allou�e avec malloc
	///
	static	char*	CFStringRefToCStr( CFStringRef inStringRef );
};

#endif
		// _TDCLIOKITSERIALPORT_H

// ==================================================================== //
// Real Users are afraid they'll break the machine -- but they're never //
// afraid to break your face.                                           //
// ==================================================================== //