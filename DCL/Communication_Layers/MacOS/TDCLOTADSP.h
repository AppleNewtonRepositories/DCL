// ==============================
// Fichier:			TDCLOTADSP.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			25/01/2002
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
// The Original Code is TDCLOTADSP.h.
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
// $Id: TDCLOTADSP.h,v 1.3 2004/11/24 14:08:54 paul Exp $
// ===========

#ifndef __TDCLOTADSP__
#define __TDCLOTADSP__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/MacOS/TDCLOpenTransport.h>

///
/// Classe pour la couche de communication AppleTalk ADSP avec OpenTransport.
///
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
/// \remark	sous MacOS X, OpenTransport ne permet pas l'ADSP.
///
class TDCLOTADSP
	:
		public TDCLOpenTransport
{
public:
	///
	/// Constantes pour la classe TDCLOTADSP
	///
	enum {
		kMaxADSPPipeCount	=	1024	///< nombre maximal de connexions par d�faut.
										///< En ADSP/OT, c'est 1024.
	};
	
	///
	/// Constructeur.
	///
	/// \param inThreadsIntf	interface pour les threads (utilis�e pour Yield).
	/// \param inMachineName	nom de la machine (si nil, on demande au syst�me)
	/// \param inMaxPipeCount	nombre maximum de connexion en m�me temps.
	/// \param inTimeout		d�lai de temporisation, format CommLayer.
	///
	TDCLOTADSP(
			IDCLThreads*	inThreadsIntf,
			const char*		inMachineName = nil,
			KUInt32			inMaxPipeCount = kMaxADSPPipeCount,
			long			inTimeout = kDefaultTimeout
		);
	
	///
	/// V�rifie que le service est disponible.
	///
	/// \return \c true si le service est disponible, \c false sinon.
	///
	static	Boolean		IsAvailable ( void );
};

#endif
		// __TDCLOTADSP__

// ============================================================================= //
// As in Protestant Europe, by contrast, where sects divided endlessly into      //
// smaller competing sects and no church dominated any other, all is different   //
// in the fragmented world of IBM.  That realm is now a chaos of conflicting     //
// norms and standards that not even IBM can hope to control.  You can buy a     //
// computer that works like an IBM machine but contains nothing made or sold by  //
// IBM itself.  Renegades from IBM constantly set up rival firms and establish   //
// standards of their own.  When IBM recently abandoned some of its original     //
// standards and decreed new ones, many of its rivals declared a puritan         //
// allegiance to IBM's original faith, and denounced the company as a divisive   //
// innovator.  Still, the IBM world is united by its distrust of icons and       //
// imagery.  IBM's screens are designed for language, not pictures.  Graven      //
// images may be tolerated by the luxurious cults, but the true IBM faith relies //
// on the austerity of the word.                                                 //
//                 -- Edward Mendelson, "The New Republic", February 22, 1988    //
// ============================================================================= //