// ==============================
// Fichier:			TDCLCommLayer.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			23/08/2000
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
// The Original Code is TDCLCommLayer.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2000-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLCommLayer.h,v 1.4 2004/11/24 14:08:53 paul Exp $
// ===========

#ifndef __TDCLCOMMLAYER__
#define __TDCLCOMMLAYER__

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>

// Pr�-d�clarations
class TDCLPipe;
class TDCLServer;

///
/// Classe abstraite pour les couches de communication.
/// Ceci est la classe de base pour les couches asynchrones. Les couches
/// synchrones doivent d�river de TDCLSyncCommLayer.
///
/// Les couches de communications comprennent:
/// - des utilitaires concernant la couche (surtout une fonction pour
///		d�termine si la couche est disponible)
/// - un serveur qui g�re une ou plusieurs connexions.
///
/// Par asynchrone, j'entends qu'il y a un m�canisme de rappel de la part
/// du syst�me. Exemple typique: OpenTransport avec la fonction 'Notify'.
/// Par synchrone, j'entends qu'il n'y a pas de tel m�canisme. Exemple typique:
/// bsd sockets. Dans ce cas, le mieux est d'utiliser les appels bloquants.
///
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \todo	revoir les temporisations.
/// \test	UTestCommLayers
///
class TDCLCommLayer
{
public:
	enum {
		kDefaultPipeCount	=	0	///< nombre maximal de connexions par
									///< d�faut. 0 veut dire pas de limite.
	};
	
	/// Constantes pour le d�lai de temporisation.
	enum {
		kNoTimeout			=	-1, ///< pas de temporisation
		kDefaultTimeout		=	0	///< temporisation par d�faut (d�pend de la
									///< couche de communication)
	};

	///
	/// Constructeur.
	///
	/// Enregistre le nombre maximum de connexion dans \c mMaxPipeCount.
	/// Enregistre aussi \p inFlushAvailable et \p inTimeout dans les champs
	/// priv�s correspondants.
	///
	/// \remark ce constructeur est public, mais la classe est abstraite.
	///
	/// \param inFlushAvailable	si la couche de communication sait vider la
	///							m�moire tampon de sortie.
	///							Si la couche de communication ne sait pas le
	///							faire, l'appelant devra attendre avant de
	///							fermer la connexion.
	/// \param inMaxPipeCount	nombre maximum de connexion simultan�es.
	///							0 signifie pas de limite.
	///
						TDCLCommLayer(
								Boolean	inFlushAvailable = false,
								KUInt32	inMaxPipeCount = kDefaultPipeCount
							);
	
	///
	/// Destructeur.
	/// Celui-ci ne fait rien. Le destructeur des sous-classes ne doit pas
	/// supprimer les connexions qui restent, c'est � l'appelant de le faire.
	/// Cependant, l'appelant doit pouvoir fermer toutes les connexions,
	/// supprimer la couche de communication et ne supprimer les objets
	/// connexions qu'apr�s.
	///
	virtual				~TDCLCommLayer( void ) {}
	
	/// \name interface serveur

	///
	/// Commence � �couter.
	/// Cette m�thode appelle DoStartListening (qui est la m�thode �
	/// surcharger).
	///
	/// \param inServer	serveur � pr�venir lorsqu'une requ�te est arriv�e.
	/// \throws TDCLException si le serveur est d�j� en train d'�couter.
	///
	virtual void		StartListening( TDCLServer* inServer );

	///
	/// Arr�te d'�couter, i.e. arr�te d'accepter les requ�tes de connexions.
	/// Cette m�thode appelle DoStopListening (qui est la m�thode �
	/// surcharger).
	/// Ne fait rien si on n'est pas en train d'�couter.
	///
	virtual void		StopListening( void );

	///
	/// Retourne un objet connexion repr�sentant le canal de communication avec
	/// le client ou \c nil s'il n'y a pas de requ�te de connexion pr�sente.
	/// C'est un objet cr�� avec \c new. L'appelant devra le supprimer.
	///
	/// \return un nouvel objet TDCLPipe cr�� avec \c new repr�sentant la
	///			connexion ou \c nil.
	///
	virtual	TDCLPipe*	Accept( void ) = 0;
	
	///
	/// Refuse la premi�re requ�te de connexion.
	/// Ne fait rien si aucune connexion n'est pr�sente.
	///
	virtual	void		Refuse( void ) = 0;

	///
	/// D�termine si la couche de communication sait vider la m�moire tampon de
	/// sortie.
	///
	/// Certaines couches de communication ne savent pas le faire.
	///
	/// \return \c true si la couche de communication sait le faire, \c false
	/// sinon.
	///
	inline	Boolean		FlushAvailable( void )
		{
			return mFlushAvailable;
		}
	
	///
	/// M�thode appel�e pour perdre du temps.
	///
	/// Elle est appel�e (par l'impl�mentation par d�faut de TDCLPipe::Idle par
	/// exemple) � intervalles r�guliers.
	///
	/// L'impl�mentation par d�faut ne fait rien.
	///
	virtual	void		Idle( void );

	///
	/// Change la temporisation pour les nouvelles connexions.
	/// La temporisation est exprim�e au format TDCLCommLayer.
	///
	/// \param inTimeout	nouvelle temporisation au format \c TDCLCommLayer
	///
	virtual	void		SetTimeout( long inTimeout ) = 0;

	///
	/// R�cup�re la temporisation utilis�e pour les nouvelles connexions.
	/// La temporisation est exprim�e au format TDCLCommLayer.
	///
	/// \return la temporisation au format \c TDCLCommLayer
	///
	virtual	long		GetTimeout( void ) = 0;

	///
	/// M�thode appel�e par TDCLPipe::Disconnect() pour indiquer qu'une
	/// connexion a �t� ferm�e. D�cr�mente le compteur des connexions ouvertes.
	///
	/// \param inPipe	connexion qui a �t� ferm�e
	///
	virtual	void		Disconnected( TDCLPipe* inPipe ) = 0;

protected:
	///
	/// Commence effectivement � �couter.
	///
	virtual	void		DoStartListening( void ) = 0;

	///
	/// Arr�te d'�couter, i.e. arr�te d'accepter les requ�tes de connexions.
	///
	virtual	void		DoStopListening( void ) = 0;


	///
	/// S�lecteur sur mFlushAvailable.
	///
	/// \param inNewFlushAvailable	\c true pour dire que cette couche de
	/// 							communication sait vider la m�moire tampon
	///								de sortie, \c false sinon.
	///
	inline	void		SetFlushAvailable( Boolean inNewFlushAvailable )
		{
			mFlushAvailable = inNewFlushAvailable;
		}

	///
	/// Accesseur sur le nombre maximum de connexions ouvertes.
	///
	/// \return le nombre maximum de connexions que le serveur peut g�rer � la
	///			fois.
	///
	inline	KUInt32		GetMaxPipeCount( void ) const
		{
			return mMaxPipeCount;
		}
		
	///
	/// S�lecteur sur le nombre maximum de connexions ouvertes.
	///
	/// \param inMaxPipeCount	nombre maximum de connexions que le serveur
	///							peut g�rer � la fois.
	///
	inline	void		SetMaxPipeCount( KUInt32 inMaxPipeCount )
		{
			mMaxPipeCount = inMaxPipeCount;
		}

	///
	/// Accesseur sur le serveur associ� (\c nil lorsqu'on n'�coute pas).
	///
	/// \return le serveur associ� � cette couche de communication.
	///
	inline	TDCLServer*	GetServer( void ) const
		{
			return mServer;
		}
		
	///
	/// S�lecteur sur le serveur associ�.
	/// (utilis� uniquement si StartListening est surcharg�e).
	///
	/// \param inServer	nouveau serveur
	///
	inline	void		SetServer( TDCLServer* inServer )
		{
			mServer = inServer;
		}

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLCommLayer( const TDCLCommLayer& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLCommLayer& operator = ( const TDCLCommLayer& inCopy );

	Boolean				mFlushAvailable;	///< Si cette couche de
											///< communication sait vider la
											///< m�moire tampon.
	KUInt32				mMaxPipeCount;		///< Nombre maximum de connexion
											///< que ce serveur peut g�rer � la
											///< fois.
	TDCLServer*			mServer;			///< Serveur associ� � l'interface
											///< de communication.
};

#endif
		// __TDCLCOMMLAYER__

// ====================================================================== //
// Il y en a qui ne savent pas d�baller leur ordinateur de la bo�te       //
// d'emballage. Faudrait aussi pr�voir une doc l�-dessus (parce que celle //
// fournie avec la bo�te, il y a plein de mots et pas beaucoup d'images)  //
// -+- Jaco in Guide du Linuxien pervers - "[OUI] � fcol.deballage" -+-   //
// ====================================================================== //
