// ==============================
// Fichier:			TDCLPkgNOSPart.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			6/4/2004
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
// The Original Code is TDCLPkgNOSPart.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLPkgNOSPart.h,v 1.7 2004/11/24 14:09:08 paul Exp $
// ===========

#ifndef _TDCLPKGNOSPART_H
#define _TDCLPKGNOSPART_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Package/TDCLPkgPart.h>

// DCL
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>

///
/// Classe pour une partie contenant un objet NS encod� au format paquet.
///
/// Les modifications apport�es � l'objet doivent �tre notifi�es pour que
/// l'objet soit r�-encod�. Par ailleurs, l'objet ne doit �tre acc�d� que
/// par un processus l�ger � la fois, i.e. il ne doit pas �tre encod�
/// pendant qu'il est modifi�.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.7 $
///
/// \test	aucun test d�fini.
///
class TDCLPkgNOSPart
	:
		public TDCLPkgPart
{
public:
	///
	/// Constructeur � partir d'un objet NewtonScript.
	/// Si l'objet est modifi� apr�s la construction de la partie, il faut
	/// appeler la m�thode Dirty avant tout encodage. (en fait, ce n'est pas
	/// n�cessaire la premi�re fois).
	///
	/// \param inObject	objet en question.
	/// \param inFourBytesPadding	si on encode avec un alignement sur 32 bits
	///								(vs 64).
	///
	TDCLPkgNOSPart(
			const TDCLNSRef& inObject,
			Boolean inFourBytesPadding = false );

	///
	/// Constructeur � partir de donn�es et d'un d�calage.
	/// L'objet n'est d�cod� que lorsque ce sera demand�.
	///
	TDCLPkgNOSPart( KUInt32 inOffset, const void* inData, KUInt32 inSize );

	///
	/// Destructeur.
	///
	virtual ~TDCLPkgNOSPart( void );

	///
	/// D�termine si la partie est un objet NewtonScript, i.e.
	/// si cette partie est de la classe TDCLPkgNOSPart.
	/// Oui.
	///
	/// \return \c true.
	///
	virtual Boolean	IsNOSPart( void ) const;

	///
	/// Retourne l'objet de cette partie (la d�code si n�cessaire).
	/// Si l'objet a �t� modifi�, la m�thode Dirty doit �tre appel�e
	/// avant tout encodage pour s'assurer que l'objet sera r�encod�.
	///
	TDCLNSRef		GetObject( void );

	///
	/// Indique que l'objet a �t� modifi�.
	///
	void			Dirty( void );

private:
	///
	/// D�termine si les donn�es d�pendent du d�calage dans le paquet.
	/// Par d�faut, non (retourne \c false).
	///
	/// \return \c true si les donn�es d�pendent du d�calage dans le paquet.
	///
	virtual Boolean IsOffsetDependant( void ) const;

	///
	/// D�termine si la partie a �t� modifi�e et doit �tre r�-encod�e.
	/// Par d�faut, non.
	///
	/// \return \c true si les donn�es ont �t� modifi�es et doivent �tre
	///			r�-encod�es.
	///
	virtual Boolean IsDirty( void ) const;

	///
	/// Encode la partie pour un d�calage donn� (la d�code si n�cessaire).
	/// Par d�faut, ne fait rien.
	///
	/// \param inOffset				d�calage dans le paquet.
	/// \param ioBuffer				pointeur sur les donn�es
	///								(allou� avec malloc)
	/// \param ioSize				taille des donn�es (en entr�e et en sortie)
	///
	virtual void Encode(
					KUInt32 inOffset,
					void** ioBuffer,
					KUInt32* ioSize ) const;

	/// \name Variables
	TDCLNSRef				mObject;	///< Objet (ou nil s'il n'est pas encore
										///< d�cod�)
	mutable Boolean			mDirty;		///< Si l'objet a �t� modifi�.
	Boolean			mFourBytesPadding;	///< Si on aligne sur 32 bits (vs 64).
};

#endif
		// _TDCLPKGNOSPART_H

// ===================================================================== //
// The algorithm for finding the longest path in a graph is NP-complete. //
// For you systems people, that means it's *real slow*.                  //
//                 -- Bart Miller                                        //
// ===================================================================== //
