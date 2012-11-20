// ==============================
// Fichier:			TDCLPipeProxy.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			5/4/2003
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
// The Original Code is TDCLPipeProxy.h.
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
// $Id: TDCLPipeProxy.h,v 1.3 2004/11/24 14:08:54 paul Exp $
// ===========

#ifndef _TDCLPIPEPROXY_H
#define _TDCLPIPEPROXY_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/TDCLPipe.h>

///
/// Classe pour un mandataire sur une connexion. Utilis�e pour la compression
/// MNP et pour l'utilisation d'une m�moire tampon.
///
/// Les m�thodes de lecture et d'�criture doivent �tre mises en places par
/// les sous-classes. Pareil pour les m�thodes BytesAvailable et FlushOutput.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLPipeProxy
	:
		public TDCLPipe
{
public:
	///
	/// Constructeur � partir d'une connexion.
	/// Cette connexion sera d�truite par le destructeur de cette classe.
	///
	/// \param inSubPipe	connexion dont cette classe est le mandataire.
	///
	TDCLPipeProxy( TDCLPipe* inSubPipe );

	///
	/// Destructeur.
	/// D�truit la connexion dont cette classe est le mandataire.
	///
	virtual ~TDCLPipeProxy( void );
	
	///
	/// D�termine si des octets sont disponibles dans la m�moire tampon d'entr�e.
	/// Appelle la m�thode de la couche de connexion dont
	/// cette classe est le mandataire.
	///
	/// \return \c true s'il y a des octets disponibles, \c false sinon.
	///
	virtual	Boolean		BytesAvailable( void );

	///
	/// D�connecte le canal de communication avec le client.
	///
	/// \remark	une fois que cette m�thode est appel�e, l'objet connexion est inutilisable.
	/// 		Il peut �tre supprim� par l'appelant � tout instant.
	///
	virtual	void		Disconnect( void );

	///
	/// M�thode appel�e pour indiquer que c'est le moment de perdre un peu
	/// de temps.
	///
	/// Certaines couches de communication ont besoin de ceci.
	///
	virtual	void		Idle( void );

	///
	/// R�cup�re la temporisation pour cette connexion.
	/// La temporisation est exprim�e en secondes ou c'est une des constantes
	/// d�finies plus haut.
	///
	/// \return la temporisation au format TDCLCommLayer.
	///
	virtual	long		GetTimeout( void );

	///
	/// Change la temporisation pour cette connexion.
	/// La temporisation est exprim�e en secondes ou c'est une des constantes
	/// d�finies plus haut.
	///
	/// \param inTimeout	temporisation au format TDCLCommLayer.
	///
	virtual	void		SetTimeout( long inTimeout );

	///
	/// R�cup�re l'octet suivant sans avancer le curseur.
	///
	/// \return l'octet lu.
	/// \throws TDCLException si l'op�ration n'est pas possible.
	///
	virtual	KUInt8		PeekByte( void );

	///
	/// M�thode appel�e par le lien pour dire qu'il est connect�
	/// via cette connexion. Cette m�thode est appel�e juste avant
	/// que des donn�es soient �chang�es.
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
	virtual	void		ClearDataPresent( void );

protected:
	///
	/// Accesseur sur la connexion dont cette classe est le
	/// mandataire.
	///
	/// \return le pointeur sur l'objet connexion.
	///
	inline TDCLPipe*	GetSubPipe( void )
		{
			return mSubPipe;
		}

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLPipeProxy( const TDCLPipeProxy& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLPipeProxy& operator = ( const TDCLPipeProxy& inCopy );

	/// \name Variables.
	
	TDCLPipe*		mSubPipe;		///< Connexion dont cette classe est le mandataire.
};

#endif
		// _TDCLPIPEPROXY_H

// ================================================ //
// You will have a head crash on your private pack. //
// ================================================ //
