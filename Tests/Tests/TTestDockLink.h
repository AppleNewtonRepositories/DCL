//==============================
// Fichier:			TTestDockLink.h
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
// $Id: TTestDockLink.h,v 1.3 2003/09/17 10:43:48 paul Exp $
// ===========

#ifndef _TTESTDOCKLINK_H
#define _TTESTDOCKLINK_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/TDCLDockLink.h>

///
/// Classe qui d�rive de TDCLDockLink et c'est tout.
/// Permet d'avoir un DockLink dans un test.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
class TTestDockLink
	:
		public TDCLDockLink
{
public:
	///
	/// Constructeur � partir de l'application.
	///
	TTestDockLink( TDCLApplication* inApplication );
};

#endif
		// _TTESTDOCKLINK_H

// =============================================== //
// The disks are getting full; purge a file today. //
// =============================================== //
