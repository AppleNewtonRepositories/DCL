// ==============================
// Fichier:			TDCLSyncEngine.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			7/4/2003
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
// The Original Code is TDCLSyncEngine.h.
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
// $Id: TDCLSyncEngine.h,v 1.7 2004/11/24 14:09:05 paul Exp $
// ===========

#ifndef _TDCLSYNCENGINE_H
#define _TDCLSYNCENGINE_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/Link_Engines/TDCLLinkEngine.h>

// DCL
#include <DCL/NS_Objects/Objects/TDCLNSString.h>
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>

// Pr�-d�clarations.
class TDCLSyncSourceEngine;

///
/// Classe pour le moteur de synchronisation.
///
/// Ce moteur fonctionne avec des sources.
/// Les synchronisations sont totales ou partielles. Elles peuvent �tre
/// partielles (optimis�es) lorsqu'elles ont �t� faites dans le pass�,
/// gr�ce aux commandes qui demandent au Newton la liste des entr�es et
/// la liste des entr�es modifi�es (on en d�duit ainsi la liste des
/// entr�es supprim�es).
///
/// Une synchronisation non optimis�e proc�de ainsi:
/// - on commence (g�n�ralement) par dresser une liste des entr�es sur le
/// serveur
/// - on t�l�charge ensuite les entr�es du Newton et on filtre celles qui
/// sont concern�es par la synchronisation.
/// - on v�rifie ensuite que les entr�es concern�es ont toutes une cl� unique.
/// Dans le cas contraire, on ne traite qu'une entr�e par cl�.
/// - on synchronise ensuite les entr�es du Newton une par une. La source peut
/// modifier, supprimer ou laisser une entr�e inchang�e. Lors d'une
/// synchronisation non optimis�e, la source n'a aucune donn�e sur le serveur
/// et donc elle ne fait que modifier (lors d'une unification) ou laisser
/// inchang�es les entr�es.
/// - on ajoute enfin les nouvelles entr�es sur le Newton (les entr�es du
/// serveur qui n'avaient pas d'�quivalent).
///
/// Une synchronisation optimis�e proc�de ainsi:
/// - on dresse la liste des entr�es sur le serveur ainsi que celles qui
/// ont �t� modifi�es, qui ont �t� cr��es et celles qui ont �t� supprim�es.
/// - on r�cup�re du Newton la liste des entr�es et des entr�es modifi�es et on
/// en d�duit la liste des entr�es supprim�es et des nouvelles entr�es.
/// - on t�l�charge les nouvelles entr�es et les entr�es modifi�es. On filtre
/// les nouvelles entr�es. On v�rifie que les entr�es modifi�es ne sont pas
/// filtr�es, sinon on consid�re qu'il s'agit d'une suppression. On v�rifie
/// qu'elles ont la m�me cl� qu'avant, sinon on consid�re qu'il s'agit d'une
/// suppression et d'une cr�ation.
/// - on synchronise toutes les entr�es du Newton, mais on fournit \c nil � la
/// m�thode SyncNewtonEntry pour l'entr�e si l'entr�e du Newton a �t� supprim�e
/// ou n'a pas �t� modifi�e (auquel cas elle n'a pas �t� t�l�charg�e).
/// - on ajoute enfin les nouvelles entr�es sur le Newton (les nouvelles
/// entr�es du serveur qui n'avaient pas d'�quivalent).
/// 
/// Chaque source garde trace de ce qui a �t� synchronis�. Ces donn�es sont
/// g�r�es par la pr�sente classe, avec le format suivant:
///
/// {
/// 	formatMajor: 1,
///		formatMinor: 0,
///		version: _entier_,						// version de la source.
///		newtons: [
///			{
///				newtonID: _newton ID_,			// (binaire de 32 bits)
///				internalStoreSig: _signature_,	// entier Newton
///				stores: [
///					{
///						signature: _signature_, // entier Newton
///						lastSyncDate: _date_,	// (binaire de 32 bits)
///												// (date fournie par le Newton)
///						soups: [
///							{
///								name: _nom_,	// cha�ne NS
///								entries: [
///								{
///									index: x,	// indice (entier)
///									key: cle,	// cl�
///								}, ...
///								]
///							},
///							// [...]
///						],
///					},
///					// [...]
///				]
///			},
///			// [...]
///	}
///	
/// Diagramme d'�tats (par rapport au Newton):
///					
/// \image html TDCLSyncEngine-State-Diagram.png
/// \image latex TDCLSyncEngine-State-Diagram.eps "TDCLSyncEngine State Diagram" width=20cm
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.7 $
///
/// \test	aucun test d�fini.
///
class TDCLSyncEngine
	:
		public TDCLLinkEngine
{
public:
	///
	/// Constructeur � partir d'un lien.
	///
	/// \param inLink	r�f�rence sur le lien.
	///
	TDCLSyncEngine( TDCLFullDockLink* inLink );
	
	///
	/// Destructeur. Lib�re la m�moire.
	///
	~TDCLSyncEngine( void );
	
	///
	/// M�thode appel�e par le lien pour commencer la synchronisation.
	/// Par d�faut demande les options de synchronisation au Newton et
	/// initialise le tableau avec les r�sultats.
	///
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual	void	StartSynchronizing( void );
	
	///
	/// Interrompt la synchronisation.
	/// L'interruption est asynchrone.
	///
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual	void	StopSynchronizing( void );
	
	///
	/// M�thode appel�e pour g�rer des commandes venant du Newton.
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return \c true si le moteur continue, \c false sinon
	/// \throws TDCLException si une erreur est survenue.
	///
	virtual	Boolean	ProcessDockCommand(
									TDCLDockCommand* inCommand,
									Boolean* outProcessed );

	///
	/// Progression de la synchronisation.
	///
	enum EProgressState {
		kSynchronizing1xPackages,	///< Synchronisation des paquets 1.x.
									///< - source = nil
									///< - entry index/count: indice sur les
									///<   paquets.
		kSynchronizingPatches,		///< Synchronisation des rustines.
									///< - source = nil
									///< - entry index/count: indice sur les
									///<   rustines.
		kFetchingEntries,			///< R�cup�ration des entr�es.
		kModifyingEntries,			///< Modification des entr�es.
		kAddingEntries				///< Ajout de nouvelles entr�es.
									///< - store index/count sans signification
	};

protected:
	///
	/// Etat du moteur de synchronisation.
	///
	enum EState {
		kUninitialized,				///< StartSynchronizing n'a pas �t� appel�.
		kWFOptions,					///< On attend les options du Newton
		kWFStoreNames,				///< On attend les noms des magasins.
		kWFPreliminaryTime,			///< On attend la premi�re commande
									///< kDCurrentTime.
		kWFSetStoreResult,			///< On vient de changer de magasin et on
									///< attend le r�sultat (rustines & paquets).
		kWFPackageIDs,				///< On attend les identifiants des paquets.
		kWFSetStoreResult2,			///< On vient de changer de magasin et on
									///< attend le r�sultat (sources).
		kWFStoreSyncTime,			///< On attend la commande kDCurrentTime
									///< pour le magasin (sources).
		kWFSoupInfo,				///< On attend les informations sur une
									///< soupe (avant de la synchroniser).
		kWFSoupIDs,					///< On attend la liste de toutes les
									///< entr�es.
		kWFChangedIDs,				///< On attend la liste des entr�es
									///< modifi�es.
		kWFEntry,					///< On attend la prochaine entr�e.
		kWFSetStoreToDefaultResult,	///< On attend le r�sultat apr�s avoir
									///< chang� le magasin courant.
		kWFModifiedResult,			///< On attend le r�sultat de la
									///< modification ou de la suppression.
		kWFAddedID,					///< On attend confirmation pour l'ajout.
		kEnd,						///< Fin
		kInterrupted				///< Interruption
	};
	
	///
	/// Si on synchronise les informations syst�me (les rustines).
	/// Par d�faut, on ne les synchronise pas.
	///
	/// \return \c true si on synchronise les informations syst�me, \c false
	/// 		sinon.
	///
	virtual Boolean				DoSynchronizePatches( void );

	///
	/// Si on synchronise les paquets.
	/// Uniquement appel�e si mDoPackages vaut \c true.
	/// Par d�faut, on ne les synchronise pas.
	///
	/// \return \c true si on synchronise les paquets, \c false sinon.
	///
	virtual Boolean				DoSynchronizePackages( void );

	///
	/// (Re)met le curseur sur les sources au d�but.
	/// Par d�faut, ne fait rien.
	///
	virtual void				ResetSourceCursor( void );

	///
	/// R�cup�re un pointeur sur la source suivante ou \c nil s'il n'y a plus
	/// de source.
	/// Par d�faut, retourne \c nil.
	///
	virtual TDCLSyncSourceEngine*	GetNextSourceEngine( void );

	///
	/// Etat de la progression.
	/// Par d�faut ne fait rien.
	///
	/// \param inCurrentState		�tat de la progression.
	/// \param inCurrentSource		\c nil ou la source courante.
	/// \param inStoreIndex			\c 0 ou indice du magasin.
	/// \param inStoreCount			\c 0 ou nombre de magasins.
	/// \param inEntryIndex			\c 0 ou indice de l'entr�e.
	/// \param inEntryCount			\c 0 ou nombre d'entr�es.
	///
	virtual void				SyncProgress(
									EProgressState inCurrentState,
									TDCLSyncSourceEngine* inCurrentSource,
									KUInt32 inStoreIndex,
									KUInt32 inStoreCount,
									KUInt32 inEntryIndex,
									KUInt32 inEntryCount );

	///
	/// Passe � la prochaine source.
	///
	/// \return le nouvel �tat, \c kEnd si on a fini.
	///
	EState						SyncNextSource( void );

	///
	/// D�termine la prochaine soupe (�ventuellement, change de magasin ou
	/// termine la synchronisation) et envoie ce qu'il faut au Newton pour
	/// synchroniser cette soupe.
	///
	/// \return le nouvel �tat, \c kEnd si on a fini.
	///
	EState						SyncNextSoup( void );

	///
	/// R�cup�re l'entr�e suivante de la soupe.
	///
	/// \return le nouvel �tat, \c kEnd si on a fini.
	///
	EState						FetchNextEntry( void );

	///
	/// Synchronise les entr�es.
	/// Commence par g�rer les entr�es avec les m�mes cl�s.
	///
	/// \return le nouvel �tat, \c kEnd si on a fini.
	///
	EState						SyncEntries( void );

	///
	/// Synchronise l'entr�e suivante.
	///
	/// \return le nouvel �tat, \c kEnd si on a fini.
	///
	EState						SyncNextEntry( void );

	///
	/// Accesseur sur les options.
	/// C'est un objet envoy� par le Newton.
	///
	/// \return une r�f�rence sur les options.
	///
	inline TDCLNSRef&			GetSyncOptions( void )
		{
			return mSyncOptions;
		}

	///
	/// Accesseur sur l'�tat.
	///
	/// \return l'�tat du moteur de synchronisation
	///
	inline EState				GetState( void ) const
		{
			return mState;
		}

	///
	/// S�lecteur sur l'�tat.
	///
	/// \param inNewState nouvel �tat du moteur de synchronisation
	///
	inline void					SetState( EState inNewState )
		{
			mState = inNewState;
		}

	///
	/// Accesseur sur l'heure du Newton.
	///
	/// \return la date au d�but de la synchronisation
	///
	inline KSInt32				GetNewtonTime( void ) const
		{
			return mNewtonTime;
		}

	///
	/// Normalise une adresse �lectronique Newton.
	/// Pour le moment, cette m�thode n'appelle aucune fonction sur le Newton,
	/// mais � terme, il faudra sans doute appeler NormalizeAddress sur le
	/// Newton. Comme \c NormalizeAddress sur le Newton, si l'objet pass� en
	/// param�tre n'est pas une cha�ne, il est retourn� tel quel.
	///
	/// \param inOriginalEmail	adresse �lectronique sur le Newton (sa classe
	///							est utilis�e) pour d�termine le syst�me de
	///							courrier �lectronique associ�.
	/// \return la cha�ne originale ou une nouvelle cha�ne normalis�e.
	///
	static TDCLNSRef			NormalizeAddress(
									const TDCLNSRef& inOriginalEmail );

	///
	/// R�cup�re une repr�sentation sous forme de cha�ne du syst�me de courrier
	/// �lectronique d'une adresse �lectronique donn�e.
	/// Pour le moment, cette m�thode n'appelle aucune fonction sur le Newton,
	/// mais � terme, il faudra sans doute regarder du c�t� de la variable globale
	/// EmailSystemsRegistrar (elle doit s'appeler comme �a).
	///
	/// \param inEmailAddress	adresse �lectronique sur le Newton (c'est sa
	///							classe qui compte)
	/// \return une cha�ne repr�sentant le syst�me de courrier d'une adresse
	///			donn�e ou NILREF si l'objet pass� en entr�e n'a pas l'air
	///			d'�tre une adresse �lectronique.
	///
	static TDCLNSRef			GetEmailSystemName(
									const TDCLNSRef& inEmailAddress );

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLSyncEngine( const TDCLSyncEngine& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLSyncEngine& operator = ( const TDCLSyncEngine& inCopy );

	///
	/// Fonction de transition
	/// kUnitialized -> kWFOptions
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromUninitialized(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFOptions -> kWFStoreNames, kWFPreliminaryTime
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFOptions(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFStoreNames -> kWFPreliminaryTime
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFStoreNames(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFPreliminaryTime -> kWFSetStoreResult, kWFSetStoreResult2
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFPreliminaryTime(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFSetStoreResult -> kWFPackageIDs
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFSetStoreResult(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFPackageIDs -> exception.
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFPackageIDs(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFSetStoreResult2 -> kWFStoreSyncTime, kWFSoupInfo
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFSetStoreResult2(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFStoreSyncTime -> kWFSoupInfo
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFStoreSyncTime(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFSoupInfo -> kWFSoupIDs
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFSoupInfo(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFSoupIDs -> kWFChangedIDs, kWFEntry
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFSoupIDs(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFChangedIDs -> kWFEntry
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFChangedIDs(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFEntry -> kWFEntry, kWFModifiedResult
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFEntry(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFModifiedResult -> kWFModifiedResult, kWFSetStoreToDefaultResult
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFModifiedResult(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFSetStoreToDefaultResult -> kWFAddedID
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFSetStoreToDefaultResult(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kWFAddedID -> kWFAddedID, kWFSoupInfo, kWFSetStoreResult2, kEnd
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromWFAddedID(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Fonction de transition
	/// kInterrupted -> kEnd
	///
	/// \param inCommand	commande re�ue.
	/// \param outProcessed	si la commande a �t� trait�e.
	/// \return le nouvel �tat
	/// \throws TDCLException si une erreur est survenue.
	///
	EState						TransitionFromInterrupted(
										TDCLDockCommand* inCommand,
										Boolean* outProcessed );

	///
	/// Cr�e une structure NewtonScript avec des informations sur le Newton
	/// connect�.
	/// Modifie aussi la variable mSyncDataStoresArray en cons�quence.
	///
	/// \return une telle structure.
	///
	TDCLNSRef					CreateCurrentNewtonFrame( void );

	///
	/// Cr�e la structure NewtonScript pour les donn�es de synchronisation de
	/// la source courante. Cr�e une structure pour le Newton courant.
	/// Stocke cette structure dans \c mSyncData.
	/// Modifie aussi la variable \c mSyncDataStoresArray en cons�quence.
	///
	/// \param inSourceVersion	version de la source
	///
	void						CreateSyncData(
										const TDCLNSRef& inSourceVersion );

	///
	/// Recherche le Newton courant dans les donn�es de synchronisation.
	/// S'il n'est pas pr�sent, cr�e une structure et l'ajoute dans les
	/// donn�es de synchronisation (\c mSyncData).
	/// Modifie la variable \c mSyncDataStoresArray.
	///
	void						LookForCurrentNewtonInSyncData( void );

	///
	/// R�cup�re la structure sur le magasin courant des donn�es de
	/// synchronisation ou en cr�e une s'il n'y en a pas. Met � jour
	/// \c mSyncDataSoupsArray.
	///
	/// Retourne la structure sur le magasin courant dans les donn�es de
	/// synchronisation.
	///
	/// \param outLastSyncDate	en sortie, date de la derni�re synchronisation.
	///
	TDCLNSFrame&				GetCurrentStoreFrame(
										KUInt32* outLastSyncDate = nil );
	
	///
	/// R�cup�re la cl� d'une entr�e � partir de la liste des entr�es des
	/// donn�es de synchronisation. On en profite pour supprimer l'entr�e de la
	/// liste dans les donn�es de synchronisation (ceci afin de rep�rer les
	/// entr�es qui ont �t� supprim�es). Si l'entr�e n'est pas dans la liste
	/// des entr�es connues, retourne \c NILREF.
	///
	TDCLNSRef					GetEntryKeyFromSyncData(
										const TDCLNSRef& inID );
	
	/// \name Variables

	TDCLNSRef			mSyncOptions;	///< Options pour la synchronisation
										///< (envoy�es par le Newton).
	Boolean				mDoPackages;	///< Si on fait les paquets.
	Boolean				mSyncAll;		///< Si on synchronise tout.
	TDCLNSRef			mStoresRef;		///< Liste des magasins (r�f�rence)
	TDCLNSArray*		mStores;		///< Liste des magasins
	KUInt32				mStoresCount;	///< Nombre de magasins � synchroniser.
	EState				mState;			///< Etat du moteur de synchronisation.
	KSInt32				mNewtonTime;	///< Heure sur le Newton.
	KUInt32				mStoreIndex;	///< Indice du magasin synchronis�.
	TDCLNSRef			mSoups;			///< Liste des soupes
	TDCLNSArray*		mSoupsArray;	///< Liste des soupes (idem, mais
										///< d�r�f�renc�)
	KSInt32				mSoupsCount;	///< Nombre de soupes � synchroniser.
	KSInt32				mSoupIndex;		///< Indice de la soupe synchronis�e.
	TDCLNSRef			mSyncData;		///< Donn�es de synchronisation pour la
										///< source.
	TDCLNSArray*		mSyncDataStoresArray;
										///< Tableau sur les magasins dans les
										///< donn�es de synchronisation pour la
										///< source.
	TDCLNSArray*		mSyncDataSoupsArray;
										///< Tableau sur les soupes du magasin
										///< courant dans les donn�es de
										///< synchronisation pour la source.
	TDCLNSArray*		mSyncDataEntriesArray;
										///< Tableau sur les entr�es de la
										///< soupe courante dans les donn�es de
										///< synchronisation pour la source.
	TDCLNSRef			mSoupInfo;		///< Information sur la soupe courante.
	TDCLNSString*		mSoupName;		///< Nom de la soupe.
	TDCLNSRef			mEntries;		///< Entr�es de la soupe courante
	TDCLNSArray*		mEntriesArray;	///< Entr�es de la soupe courante
										///< (d�ref.)
	KUInt32				mEntriesCount;	///< Nombre d'entr�es de la soupe
										///< courante synchro.	
	KSInt32				mEntryIndex;	///< Indice sur les entr�es.
	TDCLNSFrame*		mCurrentEntry;	///< Entr�e courante (dans le tableau).
	TDCLSyncSourceEngine*
						mCurrentSourceEngine;
										///< Moteur pour la source en cours.
	Boolean				mAddingEntries;	///< Si on ajoute les entr�es.
	Boolean				mCompleteSync;	///< Si on fait une synchronisation
										///< compl�te ou pas.
	Boolean				mInterrupted;	///< Si on a �t� interrompu.
};

#endif
		// _TDCLSYNCENGINE_H

// ============================================ //
// A nasty looking dwarf throws a knife at you. //
// ============================================ //
