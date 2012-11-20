// ==============================
// Fichier:			TDCLPipe.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			26/10/2002
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
// The Original Code is TDCLPipe.h.
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
// $Id: TDCLPipe.h,v 1.4 2004/11/24 14:08:53 paul Exp $
// ===========

#ifndef __TDCLPIPE__
#define __TDCLPIPE__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Streams/TDCLStream.h>

// DCL
#include <DCL/Communication_Layers/TDCLCommLayer.h>

// Pr�-d�clarations.
class TDCLPipeProxy;
class TDCLLink;

///
/// Classe pour une connexion physique avec le Newton.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class TDCLPipe
	:
		public TDCLStream
{
public:
	///
	/// Constructeur.
	/// Remplit les champs priv�s.
	///
	/// \param inCommLayer	couche de communication � laquelle est
	///						rattach�e la connexion.
	///
	TDCLPipe( TDCLCommLayer* inCommLayer );

	///
	/// Destructeur.
	/// Celui-ci ne fait rien. Le destructeur des sous-classes doit fermer
	/// la connexion si ceci n'est pas d�j� fait.
	///
	virtual	~TDCLPipe( void ) {}

	///
	/// D�termine si des octets sont disponibles dans la m�moire tampon
	/// d'entr�e.
	///
	/// \return \c true s'il y a des octets disponibles, \c false sinon.
	///
	virtual	Boolean		BytesAvailable( void ) = 0;
	
	///
	/// Vide la m�moire tampon de sortie et retourne une fois que toutes les
	/// donn�es ont �t� envoy�es.
	///
	/// Utile pour s'assurer que tout a �t� envoy�.
	/// L'impl�mentation par d�faut ne fait rien.
	///
	/// \throws TDCLException	si un probl�me est survenu.
	///
	virtual	void		FlushOutput( void );
	
	///
	/// D�connecte le canal de communication avec le client.
	///
	/// L'impl�mentation par d�faut appelle la m�thode
	/// \c Disconnected( TDCLPipe* ) de TDCLCommLayer.
	///
	/// \remark	une fois que cette m�thode est appel�e, l'objet connexion est
	///			inutilisable. Il peut �tre supprim� par l'appelant � tout
	///			instant.
	///
	virtual	void		Disconnect( void );

	///
	/// D�termine si cette connexion sait vider la m�moire tampon de sortie.
	///
	/// Certaines couches de communication ne savent pas vider la m�moire tampon
	/// de sortie. Dans ce cas, l'appelant devra attendre un petit peu avant
	/// d'appeler Disconnect.
	/// \remark il faut quand m�me appeler FlushOutput. En effet, si les donn�es
	///			sont mise dans une m�moire tampon, il faut vider cette m�moire
	///			tampon.
	///
	/// \return	\c true si la couche de communication sait vider la m�moire
	///			tampon de sortie, \c false sinon.
	///
	inline	Boolean		FlushAvailable( void )
		{
			return mCommLayer->FlushAvailable();
		}

	///
	/// M�thode appel�e pour indiquer que c'est le moment de perdre un peu
	/// de temps.
	///
	/// Certaines couches de communication ont besoin de ceci. L'impl�mentation
	/// par d�faut appelle la m�thode Idle( void ) de la couche de
	/// communication.
	///
	virtual	void		Idle( void );

	///
	/// R�cup�re la temporisation pour cette connexion.
	/// La temporisation est exprim�e en secondes ou c'est une des constantes
	/// d�finies plus haut.
	///
	/// \return la temporisation au format TDCLCommLayer.
	///
	virtual	long		GetTimeout( void ) = 0;

	///
	/// Change la temporisation pour cette connexion.
	/// La temporisation est exprim�e en secondes ou c'est une des constantes
	/// d�finies plus haut.
	///
	/// \param inTimeout	temporisation au format TDCLCommLayer.
	///
	virtual	void		SetTimeout( long inTimeout ) = 0;

	///
	/// R�cup�re l'octet suivant sans avancer le curseur.
	/// Par d�faut, ceci n'est pas possible. Renvoie donc une exception.
	///
	/// \return l'octet lu.
	/// \throws TDCLException
	///
	virtual	KUInt8		PeekByte( void );

	///
	/// M�thode appel�e par le lien pour dire qu'il est connect� via cette
	/// connexion. Cette m�thode est appel�e juste avant que des donn�es soient
	/// �chang�es. Cette m�thode retourne l'interface de communication comme �a
	/// le lien peut la transmettre � l'application.
	///
	/// Par d�faut r�gle mLink.
	///
	/// \param inLink	lien qui est connect�.
	/// \return l'interface de communication.
	///
	virtual	TDCLCommLayer*	Connected( TDCLLink* inLink );

	///
	/// M�thode appel�e par le lien pour dire qu'il souhaite
	/// �tre pr�venu d�s que des donn�es sont pr�sentes.
	/// Au d�part, l'interface de communication ne pr�vient
	/// pas le lien de la pr�sence de donn�es.
	///
	/// Remarque: chaque appel � cette m�thode induit (au moins) un message
	/// envoy� au lien. Comme les messages sont asynchrones, le lien doit
	/// v�rifier lorsqu'il a un tel message que des donn�es sont pr�sentes
	/// (en appelant BytesAvailable).
	///
	virtual	void		ClearDataPresent( void ) = 0;

protected:
	///
	/// Le constructeur de la classe mandataire a besoin d'acc�der � la couche
	/// de communication.
	///
	friend class TDCLPipeProxy;

	///
	/// Accesseur sur la couche de communication.
	///
	/// Il est prot�g� parce que les appelant n'ont pas besoin d'y avoir acc�s.
	///
	/// \return	la couche de communication associ�e � cette connexion.
	///
	inline	TDCLCommLayer*	GetCommLayer( void )
		{
			return mCommLayer;
		}

	///
	/// Accesseur sur le lien associ� (\c nil lorsqu'on n'est pas connect�).
	///
	/// \return le lien associ� � cette connexion.
	///
	inline	TDCLLink*	GetLink( void ) const
		{
			return mLink;
		}
		
	///
	/// S�lecteur sur le lien associ�.
	///
	/// \param inLink	nouveau lien
	///
	inline	void		SetLink( TDCLLink* inLink )
		{
			mLink = inLink;
		}

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLPipe( const TDCLPipe& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLPipe& operator = ( const TDCLPipe& inCopy );

	/// \name Variables.
	
	TDCLCommLayer*	mCommLayer;	///< Couche de communication associ�e � cette
								///< connexion.
	TDCLLink*		mLink;		///< Lien associ� � cette connexion.
};

#endif
		// __TDCLPIPE__

// =================================================================== //
// "One basic notion underlying Usenet is that it is a cooperative."   //
//                                                                     //
// Having been on USENET for going on ten years, I disagree with this. //
// The basic notion underlying USENET is the flame.                    //
//                 -- Chuq Von Rospach                                 //
// =================================================================== //
