// ==============================
// Fichier:			TDCLDockCmdDesktopInfo.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			02/02/2001
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
// The Original Code is TDCLDockCmdDesktopInfo.h.
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
// $Id: TDCLDockCmdDesktopInfo.h,v 1.3 2004/11/24 14:09:03 paul Exp $
// ===========

#ifndef __TDCLDOCKCMDDESKTOPINFO__
#define __TDCLDOCKCMDDESKTOPINFO__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/Dock_Commands/TDCLDockCommand.h>

// DCL
#include <DCL/Communication_Layers/TDCLCommLayer.h>

class TDCLStream;
class TDCLNSArray;

///
/// Classe pour la commande du Dock qui d�crit les informations sur le serveur.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLDockCmdDesktopInfo
	:
		public	TDCLDockCommand
{
public:
		///
		/// Constructeur � partir des informations sur le serveur.
		///
		/// \param inDesktopAppArray	Information sur le logiciel serveur
		///								sous forme de tableau NewtonScript.
		/// \param inEncKey1			Premi�re partie de la cl� pour se
		///								connecter. D�pend du d�fi DES.
		///	\param inEncKey2			Deuxi�me partie.
		/// \param inSelectiveBackup	Si on permet une sauvegarde s�lective.
		///								Ceci ne vaut que si on a d�j� une sauvegarde.
		/// \param inSessionType		Type de session.
		/// \param inPlatformKind		Type de plateforme (Win ou Mac).
		///
		TDCLDockCmdDesktopInfo(
				TDCLNSArray&	inDesktopAppArray,
				KUInt32			inEncKey1,
				KUInt32			inEncKey2,
				Boolean			inSelectiveBackup,
				KUInt32			inSessionType,
				KUInt32			inPlatformKind = kThis_DType );
		
		///
		/// Destructeur
		///										
		virtual			~TDCLDockCmdDesktopInfo( void );

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
	TDCLDockCmdDesktopInfo( const TDCLDockCmdDesktopInfo& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLDockCmdDesktopInfo& operator = ( const TDCLDockCmdDesktopInfo& inCopy );

	///
	/// Structure pour les informations sur le serveur.
	///
	struct SDesktopInfo
	{
		KUInt32		fProtocolVersion;		///< Version du protocole (kProtocolVersion)
		KUInt32		fDesktopType;			///< Type de l'OS (kMac_DType ou kWin_DType)
		KUInt32		fEncryptedKey[2];		///< Clef pour le d�fi DES
		KUInt32		fSessionType;			///< Type de session
		KUInt32		fAllowSelectiveSync;	///< Si on permet les sauvegardes/synchronisations
											///< partielle (uniquement si on d�j� une sauvegarde)
	};

	/// \name Variables

	SDesktopInfo	mDesktopInfo;			///< Informations sur le serveur
	KUInt32			mDesktopArraySize;		///< Taille du tableau au sujet du logiciel
	void*			mDesktopArrayPtr;		///< Pointeur sur le tableau
	KUInt32			mLength;				///< Taille totale de la commande
};

#endif
		// __TDCLDOCKCMDDESKTOPINFO__

// ============================================================================== //
//                                 UNIX Trix                                      //
//                                                                                //
// For those of you in the reseller business, here is a helpful tip that will     //
// save your support staff a few hours of precious time.  Before you send your    //
// next machine out to an untrained client, change the permissions on /etc/passwd //
// to 666 and make sure there is a copy somewhere on the disk.  Now when they     //
// forget the root password, you can easily login as an ordinary user and correct //
// the damage.  Having a bootable tape (for larger machines) is not a bad idea    //
// either.  If you need some help, give us a call.                                //
//                 -- CommUNIXque 1:1, ASCAR Business Systems                     //
// ============================================================================== //
