// ==============================
// Fichier:			TDCLCTBMNPSerial.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			22/01/2002
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
// The Original Code is TDCLCTBMNPSerial.h.
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
// $Id: TDCLCTBMNPSerial.h,v 1.4 2004/11/24 14:08:54 paul Exp $
// ===========

#ifndef _TDCLCTBMNPSERIAL_H
#define _TDCLCTBMNPSERIAL_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/MacOS/TDCLCommToolBox.h>

///
/// Classe pour la couche de communication port s�rie avec la CTB (avec
/// compression MNP inclue dans la CTB).
/// 
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \todo	revoir les temporisations.
/// \test	aucun test d�fini.
///
class TDCLCTBMNPSerial
	:
		public TDCLCommToolBox
{
public:
	///
	/// Constructeur.
	///
	/// \param inThreadsIntf	interface pour les threads (utilis�e pour
	///							Yield).
	/// \param inPort			index du port s�rie (base 0)
	/// \param inBaud			vitesse du port s�rie (par d�faut, 38400, la
	///							vitesse par d�faut sur le Newton)
	/// \param inTimeout		d�lai de temporisation, format CommLayer.
	///
	TDCLCTBMNPSerial(
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
	static	Boolean			IsAvailable( void );

	///
	/// D�termine le nom d'un port s�rie. Utile pour �tre sympa avec
	/// l'utilisateur. Retourne une cha�ne allou�e avec malloc.
	///
	/// \param inIndex			index du port s�rie (base 0)
	/// \return une cha�ne allou�e avec malloc ou nil si le port n'existe pas.
	///
	static	char*			GetSerialPortName( unsigned long inIndex );

	///
	/// D�termine le nombre de ports s�rie disponibles.
	///
	/// \return le nombre de ports s�rie (n) sur cette machine. L'index du port
	///			pour les autres m�thodes doit �tre entre 0 et n - 1.
	///
	static	unsigned long	CountSerialPorts( void );
};

#endif
		// _TDCLCTBMNPSERIAL_H

// ========================================================================= //
// A year spent in artificial intelligence is enough to make one believe in  //
// God.                                                                      //
// ========================================================================= //
