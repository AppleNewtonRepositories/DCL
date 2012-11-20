// ==============================
// Fichier:			TDCLBrowseEngine.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			8/4/2003
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
// The Original Code is TDCLBrowseEngine.h.
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
// $Id: TDCLBrowseEngine.h,v 1.3 2004/11/24 14:09:04 paul Exp $
// ===========

#ifndef _TDCLBROWSEENGINE_H
#define _TDCLBROWSEENGINE_H

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Interfaces/TDCLFSItemRef.h>
#include <DCL/Link/TDCLFullDockLink.h>
#include <DCL/Link/Link_Engines/TDCLLinkEngine.h>
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>

// Pr�-d�clarations
class TDCLFolder;
class TDCLPipe;
class IDCLFiles;

///
/// Classe pour le moteur de butinage.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
/// \todo	g�rer le butinage sur Windoze.
///
class TDCLBrowseEngine
	:
		public TDCLLinkEngine
{
public:
	///
	/// Constructeur � partir d'un dossier par d�faut.
	///
	/// \param inLink			r�f�rence sur le lien dont nous faisons le travail.
	/// \param inDefaultFolder	dossier de d�part (si \c nil, on prend le dossier racine)
	///
	TDCLBrowseEngine(
				TDCLFullDockLink* inLink,
				TDCLFSItemRef inDefaultFolder = TDCLFSItemRef() );

	///
	/// Commence le butinage. Cette m�thode est appel�e juste apr�s
	/// avoir accept� le butinage aupr�s du Newton. Elle doit
	/// envoyer une commande kDResult au Newton pour accepter le butinage.
	///
	/// \param inFileTypes	type de fichiers
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual void StartBrowsing( const TDCLNSRef& inFileTypes );

	///
	/// M�thode appel�e pour g�rer des commandes venant du Newton.
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le prochain �tat du lien (l'�tat actuel �tant kRunning),
	///			par exemple kRunning ou kDisconnecting (DoDisconnect est appel�
	///			dans la boucle)
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual	Boolean		ProcessDockCommand(
									TDCLDockCommand* inCommand,
									Boolean* outProcessed );

protected:
	///
	/// R�cup�re les �l�ments du dossier courant.
	///
	/// \return un tableau contenant les �l�ments du dossier courant.
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual TDCLNSRef GetFilesAndFolders( void );


	///
	/// Installe un paquet.
	/// Appelle la m�thode du lien.
	/// Cette m�thode est surtout l� pour les sous-classes de cette classe.
	///
	/// \param inPackage	paquet � installer.
	/// \throws TDCLException si une erreur est survenue.
	///
	inline void DoInstallPackage( TDCLFSItemRef inPackage )
		{
			GetLink()->DoInstallPackage( inPackage );
		}

	///
	/// R�cup�ration d'un �l�ment � partir du dossier courant et d'une information
	/// de nom venant du Newton.
	///
	/// \param inFileName	nom (cha�ne ou structure avec le nom dans Name et d'autres
	///						informations comme le volume dans whichVol)
	/// \return une r�f�rence vers le fichier ou \c nil.
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual TDCLFSItemRef	GetFile( const TDCLNSRef& inFileName );

	///
	/// R�cup�ration d'informations sur un �l�ment.
	///
	/// \param inFileName	nom (cha�ne ou structure, pass� � GetFile)
	/// \return une structure NewtonScript comprenant les informations � envoyer au Newton.
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual TDCLNSRef		GetFileInfo( const TDCLNSRef& inFileName );

	///
	/// Changement du chemin courant � partir d'un nouveau chemin.
	///
	/// \param inPath		chemin tel qu'envoy� par le Newton.
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual void 			SetPath( const TDCLNSRef& inPath );

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLBrowseEngine( const TDCLBrowseEngine& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLBrowseEngine& operator = ( const TDCLBrowseEngine& inCopy );

	/// \name Variables

	IDCLFiles*				mFilesIntf;			///< Interface pour les fichiers.
	TDCLFSItemRef			mCurrentFolderRef;	///< R�f�rence sur le dossier courant.
	TDCLFolder*				mCurrentFolder;		///< Dossier courant.
	Boolean					mIsMac;				///< Si on r�agit comme un Mac.
	TDCLNSRef				mFileTypes;			///< Types des fichiers.
};

#endif
		// _TDCLBROWSEENGINE_H

// ========================================================================= //
// It must be remembered that there is nothing more difficult to plan, more  //
// doubtful of success, nor more dangerous to manage, than the creation of   //
// a new system.  For the initiator has the emnity of all who would profit   //
// by the preservation of the old institutions and merely lukewarm defenders //
// in those who would gain by the new ones.                                  //
//                 -- Niccolo Machiavelli, 1513                              //
// ========================================================================= //
