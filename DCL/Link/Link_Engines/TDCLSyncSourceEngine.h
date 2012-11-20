// ==============================
// Fichier:			TDCLSyncSourceEngine.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			28/12/2003
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
// The Original Code is TDCLSyncSourceEngine.h.
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
// $Id: TDCLSyncSourceEngine.h,v 1.4 2004/11/24 14:09:05 paul Exp $
// ===========

#ifndef _TDCLSYNCSOURCEENGINE_H
#define _TDCLSYNCSOURCEENGINE_H

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Link/Link_Engines/TDCLSyncEngine.h>
#include <DCL/NS_Objects/Objects/TDCLNSFrame.h>
#include <DCL/NS_Objects/Objects/TDCLNSString.h>
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>

///
/// Interface pour g�rer la synchronisation entre une source et une ou plusieurs
/// soupes.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class TDCLSyncSourceEngine
{
public:
	///
	/// Politique globale pour la synchronisation.
	///
	enum
	{
		kSameKey_ConsiderFirstOnly	= 0,	///< En cas d'enregistrements multiples
											///< avec une cl� donn�e, consid�re uniquement
											///< le premier
		kSameKey_ConsiderNewestOnly	= 1,	///< Idem, mais avec le plus r�cent
		kSameKey_DeleteOthers		= 2,	///< Supprime les autre cl�s
		kSameKey_AskUser			= 4,	///< Demande � l'utilisateur en cas
											///< d'enregistrements avec la m�me cl�.
		kOnlyOnNewtonCopyToMac		= 0,	///< Copie les enregistrements seulement sur
											///< le Newton
		kOnlyOnNewtonSkip			= 8,	///< Ignore les enregistrements seulement sur
											///< le Newton
		kOnlyOnNewtonDelete			= 16,	///< Supprime les enregistrements seulement
											///< sur le Newton
		kOnlyOnMacCopyToNewton		= 0,	///< Copie les enregistrements seulement sur
											///< le Mac.
		kOnlyOnMacSkip				= 32,	///< Ignore les enregistrements seulement sur
											///< le Mac.
		kOnlyOnMacDelete			= 64	///< Supprime les enregistrements seulement
											///< sur le Mac.
	};

	///
	/// �tat d'un enregistrement provenant du Newton
	///
	enum ESyncModification
	{
		kCompleteSync		= 0,	///< La synchronisation est compl�te
		kNewEntry			= 1,	///< Nouvel enregistrement depuis la derni�re
									///< synchronisation
		kModifiedEntry		= 2,	///< Enregistrement modifi� depuis la derni�re
									///< synchronisation
		kDeletedEntry		= 3		///< Enregistrement supprim� depuis la derni�re
									///< synchronisation
	};

	///
	/// R�sultat d'une synchronisation avec un �l�ment.
	///
	enum ESyncResult
	{
		kUnchanged		= 0,	// L'entr�e n'a pas �t� modifi�e.
		kModified		= 1,	// L'entr�e a �t� modifi�e.
		kDeleted		= 2		// L'entr�e doit �tre supprim�e.
	};
	
	///
	/// Initialisation du moteur avant de commencer la synchronisation.
	/// Retourne le num�ro de la version. Si la version ne correspond pas
	/// aux donn�es enregistr�es, on proc�dera � une synchronisation compl�te.
	///
	/// \param inNewtonTime	heure courante sur le Newton.
	/// \return le num�ro de la version.
	///
	virtual KUInt16		Init( KSInt32 inNewtonTime ) = 0;
	
	///
	/// V�rifie que deux enregistrements n'ont pas la m�me cl�.
	/// Cette m�thode est appel�e tant qu'elle retourne vrai.
	///
	/// \param outSummaries		tableau des r�sum�s des enregistrements, par ordre
	///							de date de modification (TDCLNSArray de TDCLNSString)
	/// \param outKey			cl� partag�e par ces deux enregistrements
	/// \return \c true si deux enregistrements ont la m�me cl�, \c false sinon.
	///
	virtual bool		NextCommonKey(
								TDCLNSRef* outSummaries,
								TDCLNSRef* outKey ) = 0;
	
	///
	/// M�thode appel�e pour r�gler un conflit avec les cl�s d�tect� avec la pr�c�dente
	/// m�thode.
	///
	/// \param inKey			cl� concern�e.
	/// \param inRecordIndex	indice de l'enregistrement conserv�.
	/// \param inDeleteOthers	si les autres enregistrements doivent �tre supprim�s.
	///
	virtual void		HandleCommonKey(
								const TDCLNSRef& inKey,
								KUInt32 inRecordIndex,
								bool inDeleteOthers ) = 0;

	///
	/// Compare deux cl�s.
	///
	/// \param inFirstKey	premi�re cl� � comparer
	/// \param inSecondKey	deuxi�me cl� � comparer
	/// \return \c 0 si les deux cl�s sont identiques, un entier n�gatif
	///			si \c inFirstKey est inf�rieure � \c inSecondKey,
	///			un entier positif dans le cas contraire.
	///
	virtual int			CompareKeys(
								const TDCLNSRef& inFirstKey,
								const TDCLNSRef& inSecondKey ) = 0;

	///
	/// D�termine la liste des soupes � synchroniser.
	///
	/// \return une liste de soupes � synchroniser (dans un tableau TDCLNSArray,
	///			chaque �l�ment est un TDCLNSString).
	///
	virtual TDCLNSRef	GetSoupNames( void ) = 0;

	///
	/// D�termine si les donn�es de la source ont une date de modification, auquel
	/// cas on peut optimiser la synchronisation.
	///
	/// \return \c true si on peut optimiser la synchronisation en utilisant la date
	///			de la derni�re synchronisation.
	///
	virtual Boolean		HasModificationDate( void ) = 0;

	///
	/// Retourne les donn�es de synchronisation telles que sauvegard�es par
	/// SetSyncEngineData. Ces donn�es permettent de savoir quel est l'�tat
	/// de la synchronisation la derni�re fois qu'elle a eu lieu. Ces donn�es sont
	/// g�r�es par TDCLSyncEngine et peuvent �tre s�rialis�es avec les encodeurs/
	/// d�codeurs d�riv�s de TDCLNSCodec.
	/// Si aucune donn�e n'a encore �t� enregistr�e, il faut retourner
	/// \c NILREF.
	///
	/// \return les donn�es de synchronisation telles que sauvegard�es par
	/// la source.
	///
	virtual TDCLNSRef	GetSyncEngineData( void ) = 0;

	///
	/// Enregistre les donn�es de synchronisation pour la prochaine
	/// synchronisation.
	///
	/// \param inSyncData	donn�es de synchronisation � enregistrer.
	///
	virtual void		SetSyncEngineData( const TDCLNSRef& inSyncData ) = 0;

	///
	/// D�termine si un enregistrement sur le Newton doit �tre synchronis�.
	///
	/// \param inSoupName		nom de la soupe � laquelle appartient l'enregistrement.
	/// \param inNewtonEntry	enregistrement de la soupe.
	/// \return \c true si l'enregistrement doit �tre synchronis�.
	///
	virtual Boolean		FilterEntry(
								const TDCLNSString& inSoupName,
								const TDCLNSFrame& inNewtonEntry ) = 0;

	///
	/// R�cup�re une cl� pour un enregistrement sur le Newton donn�.
	///
	/// \param inSoupName		nom de la soupe � laquelle appartient l'enregistrement.
	/// \param inNewtonEntry	enregistrement de la soupe dont on veut une cl�.
	///
	virtual TDCLNSRef	GetEntryKey(
								const TDCLNSString& inSoupName,
								const TDCLNSFrame& inNewtonEntry ) = 0;

	///
	/// Extraction d'un r�sum� de l'entr�e dans une cha�ne NS.
	///
	/// \param inSoupName		nom de la soupe � laquelle appartient l'enregistrement.
	/// \param inNewtonEntry	enregistrement de la soupe dont on veut un r�sum�.
	/// \return le r�sum� de l'entr�e (cha�ne NS)
	///
	virtual TDCLNSRef	GetEntrySummary(
								const TDCLNSString& inSoupName,
								const TDCLNSFrame& inNewtonEntry ) = 0;

	///
	/// Synchronise un enregistrement ajout� au Newton depuis la derni�re synchronisation.
	/// Cette m�thode a comme param�tre la cl� donn�e par \c GetEntryKey.
	///
	/// \param inModification		type de modification depuis la derni�re
	///								synchronisation.
	/// \param inNewtonLastSyncTime	date de la derni�re synchronisation sur le
	///								Newton.
	/// \param inSoupName			nom de la soupe.
	/// \param inEntryKey			cl� pour l'enregistrement fournie par
	///								GetEntryKey.
	/// \param inNewtonEntry		enregistrement de la soupe � synchroniser,
	///								ou \c nil si l'entr�e a �t� supprim�e ou
	///								n'a pas �t� modifi�e.
	/// \return un code qui d�termine ce que le moteur doit faire avec cette
	///			entr�e. Si inNewtonEntry �tait \c nil et que cette m�thode
	///			retourne kModified, l'entr�e sera t�l�charg�e du Newton pour
	///			�tre modifi�e.
	///
	virtual ESyncResult	SyncNewtonEntry(
								ESyncModification inModification,
								KSInt32 inNewtonLastSyncTime,
								const TDCLNSString& inSoupName,
								const TDCLNSRef& inEntryKey,
								const TDCLNSRef& inNewtonEntry ) = 0;

	///
	/// R�cup�re une nouvelle entr�e � ajouter ou \c NILREF.
	/// Cette m�thode n'est appel�e que pour le magasin par d�faut.
	/// Elle est appel�e tant que le r�sultat n'est pas \c NILREF.
	///
	/// \return une nouvelle entr�e � ajouter � cette soupe ou \c NILREF.
	///
	virtual TDCLNSRef	GetNextNewEntry( void ) = 0;
};

#endif
		// _TDCLSYNCSOURCEENGINE_H

// =============== //
// PURGE COMPLETE. //
// =============== //
