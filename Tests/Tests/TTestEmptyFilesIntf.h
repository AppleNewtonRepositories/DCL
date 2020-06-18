//==============================
// Fichier:			TTestEmptyFilesIntf.h
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
// $Id: TTestEmptyFilesIntf.h,v 1.6 2003/12/28 07:04:50 paul Exp $
// ===========

#ifndef _TTESTEMPTYFILESINTF_H
#define _TTESTEMPTYFILESINTF_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/IDCLFiles.h>

///
/// Classe pour indiquer le type de syst�me de fichier.
/// La m�thode \c GetRootFolder lance une exception.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.6 $
///
class TTestEmptyFilesIntf
	:
		public IDCLFiles
{
public:
	///
	/// Retourne le code du type de la plateforme tel qu'il sera indiqu� au Newton
	/// (Mac ou Windows).
	/// Cette classe de test renvoie \c TDCLDockCommand::kMac_DType
	///
	/// \return \c TDCLDockCommand::kMac_DType
	///
	virtual KUInt32	GetKind( void );

	///
	/// D�termine le dossier bureau ou le dossier racine pour un disque donn�.
	///
	/// \param inRootName	nom du disque (pour "Windows", si le Newton croit
	///						que nous sommes un Mac, ce param�tre sera \c nil)
	/// \return rien du tout
	/// \throws DCLNotImplementedError dans tous les cas.
	///
	virtual TDCLFSItemRef	GetRootFolder( const KUInt16* inRootName = nil );

	///
	/// D�termine le nombre de dossiers racine.
	///
	/// \return rien du tout
	/// \throws DCLNotImplementedError dans tous les cas.
	///
	virtual KUInt32			CountRootFolders( void ) const;

	///
	/// R�cup�re le nom du n-i�me dossier racine.
	/// Le nom appartient � l'objet IDCLFiles.
	///
	/// \param inFolderIndex	un indice de dossier racine, entre 0 et
	///							CountRootFolders() - 1.
	/// \return rien du tout
	/// \throws DCLNotImplementedError dans tous les cas.
	///
	virtual const KUInt16*	GetRootFolderName( KUInt32 inFolderIndex ) const;
};

#endif
		// _TTESTEMPTYFILESINTF_H

// ============================================================ //
// Think of it!  With VLSI we can pack 100 ENIACs in 1 sq. cm.! //
// ============================================================ //
