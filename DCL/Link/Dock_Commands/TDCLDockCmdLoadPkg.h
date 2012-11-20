// ==============================
// Fichier:			TDCLDockCmdLoadPkg.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			15/08/2001
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
// The Original Code is TDCLDockCmdLoadPkg.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2001-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLDockCmdLoadPkg.h,v 1.3 2004/11/24 14:09:04 paul Exp $
// ===========

#ifndef __TDCLDOCKCMDLOADPKG__
#define __TDCLDOCKCMDLOADPKG__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/Dock_Commands/TDCLDockCommand.h>

// DCL
#include <DCL/Interfaces/TDCLFSItemRef.h>

// Pr�-d�clarations
class TDCLStream;
class TDCLFile;

///
/// Classe pour la commande du Dock qui installe un paquet sur le Newton.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLDockCmdLoadPkg
	:
		public TDCLDockCommand
{
public:
	///
	/// Constructeur � partir d'une r�f�rence sur un fichier.
	///
	/// \param inPackage	r�f�rence sur le paquet � installer.
	///
	TDCLDockCmdLoadPkg( TDCLFSItemRef inPackage );
	
protected:
	///
	/// M�thode appel�e pour r�cup�rer la taille de la commande avant de
	/// l'envoyer.
	///
	/// \return la taille de la commande
	///
	virtual	KUInt32		GetLength( void ) const;
	
	///
	/// Envoie le corps de la commande.
	///
	/// \param inPipe				connexion pour �crire la commande.
	/// \param inLength				taille des donn�es � envoyer
	/// \param inProgressFuncPtr	fonction appel�e pour la progression
	///								(\c nil signifie qu'on ne pr�vient pas)
	///								Cette m�thode doit tenir compte du fait
	///								que 16 octets ont d�j� �t� envoy�s.
	/// \param inRefCon				biscuit pour inProgressFuncPtr
	///
	virtual	void			SendBody(
									TDCLStream* inPipe,
									KUInt32 inLength,
									ProgressFuncPtr inProgressFuncPtr,
									void* inRefCon );

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLDockCmdLoadPkg( const TDCLDockCmdLoadPkg& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLDockCmdLoadPkg& operator = ( const TDCLDockCmdLoadPkg& inCopy );

	///
	/// Constantes pour cette classe.
	///
	enum {
		kChunkSize		=	8192	///< Taille des paquets envoy�s au Newton.
	};

	/// \name Variables

	TDCLFSItemRef			mPackage;			///< R�f�rence sur le fichier.
	TDCLFile*				mPackageFile;		///< Fichier.	
};

#endif
		// __TDCLDOCKCMDLOADPKG__

// ======================================================================= //
// He's like a function -- he returns a value, in the form of his opinion. //
// It's up to you to cast it into a void or not.                           //
//                 -- Phil Lapsley                                         //
// ======================================================================= //
