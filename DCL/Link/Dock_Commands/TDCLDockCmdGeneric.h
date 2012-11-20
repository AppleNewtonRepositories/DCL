// ==============================
// Fichier:			TDCLDockCmdGeneric.h
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
// The Original Code is TDCLDockCmdGeneric.h.
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
// $Id: TDCLDockCmdGeneric.h,v 1.3 2004/11/24 14:09:04 paul Exp $
// ===========

#ifndef __TDCLDOCKCMDGENERIC__
#define __TDCLDOCKCMDGENERIC__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Link/Dock_Commands/TDCLDockCommand.h>

///
/// Classe pour une commande du dock avec des donn�es quelconques.
/// (s'il n'y a pas de donn�es, autant utiliser TDCLDockCmdNoData, s'il
/// n'y a qu'un long, c'est TDCLDockCmdSingleLong qui convient le mieux).
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLDockCmdGeneric
	:
		public TDCLDockCommand
{
public:
	///
	/// Constructeur par d�faut.
	///
	TDCLDockCmdGeneric( void );
	
	///
	/// Constructeur � partir d'un identifiant de commande et des donn�es.
	///
	/// \param inCommand	identifiant pour la commande.
	/// \param inLength		taille des donn�es.
	/// \param inData		pointeur sur les donn�es (copi�es)
	///
	TDCLDockCmdGeneric(
					KUInt32 inCommand,
					KUInt32 inLength = 0,
					const void* inData = nil );

	///
	/// Destructeur.
	/// Lib�re la copie des donn�es.
	///
	virtual		~TDCLDockCmdGeneric( void );

	///
	/// S�lecteur sur l'identifiant de la commande.
	///
	/// \param inCommand	nouvel identifiant pour la commande.
	///
	inline	void	SetCommand( KUInt32 inCommand )
		{
			TDCLDockCommand::SetCommand( inCommand );
		};
	
	///
	/// Accesseur sur la taille des donn�es.
	///
	/// \return la taille des donn�es.
	///
	virtual	KUInt32			GetLength( void ) const;
	
	///
	/// S�lecteur sur la taille des donn�es.
	/// Redimensionne la m�moire tampon.
	///
	/// \param inLength		nouvelle taille des donn�es.
	///
	void					SetLength( KUInt32 inLength );

	///
	/// Accesseur sur les donn�es (pour pouvoir les changer).
	///
	/// \return le pointeur sur les donn�es.
	///
	inline	void*			GetDataPtr( void )
		{
			return mData;
		};
	
	///
	/// S�lecteur sur les donn�es.
	/// Copie les donn�es fournies en param�tre dans la m�moire
	/// tampon de la commande.
	///
	/// \param inData		donn�es � copier.
	///
	void					CopyData( const void* inData );

protected:
	///
	/// Accesseur sur les donn�es (en lecture seule).
	/// Utilis� pour envoyer la commande.
	///
	/// \return le pointeur sur les donn�es (non modifiables)
	///
	virtual const void*		GetData( void );

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLDockCmdGeneric( const TDCLDockCmdGeneric& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLDockCmdGeneric& operator = ( const TDCLDockCmdGeneric& inCopy );

	/// \name Variables

	KUInt32			mLength;	///< Taille de la m�moire tampon.
	void*			mData;		///< M�moire tampon avec les donn�es.
};

#endif
		// __TDCLDOCKCMDGENERIC__

// =============================================================== //
// System going down at 5 this afternoon to install scheduler bug. //
// =============================================================== //
