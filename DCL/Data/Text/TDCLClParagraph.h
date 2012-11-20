// ==============================
// Fichier:			TDCLClParagraph.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			20/3/2004
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
// The Original Code is TDCLClParagraph.h.
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
// $Id: TDCLClParagraph.h,v 1.3 2004/11/24 14:08:56 paul Exp $
// ===========

#ifndef _TDCLCLPARAGRAPH_H
#define _TDCLCLPARAGRAPH_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Data/Text/TDCLRichText.h>

// DCL
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>

class TDCLNSFrame;
class TDCLNSString;

///
/// Classe pour un paragraphe avec style clParagraph.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLClParagraph
	:
		public TDCLRichText
{
public:
	///
	/// Constructeur par d�faut.
	/// Cr�e un texte vide.
	///
	TDCLClParagraph( void );

	///
	/// Constructeur � partir de donn�es Newton.
	///
	/// \param inDataFrame	structure Newton telle qu'on peut la trouver dans
	///						les notes (clParagraph).
	///
	TDCLClParagraph( const TDCLNSRef& inDataFrame );

	///
	/// Constructeur par copie.
	///
	/// \param inCopy	autre paragraphe Newton (copi�)
	///
	TDCLClParagraph( const TDCLClParagraph& inCopy );

	///
	/// Constructeur � partir d'un autre texte avec styles.
	///
	/// \param inCopy	autre texte avec styles.
	///
	TDCLClParagraph( const TDCLRichText& inCopy );

	///
	/// Destructeur.
	///
	virtual ~TDCLClParagraph( void ) {};

	///
	/// Concat�ne avec un autre texte riche.
	///
	virtual void Catenate( const TDCLRichText& inAlter );

	///
	/// R�cup�re la taille du texte, i.e. le nombre de
	/// caract�res.
	///
	/// \return la taille du texte, en caract�res.
	///
	virtual KUInt32 GetSize( void ) const;

	///
	/// Copie n caract�res du texte.
	///
	/// \param inOffset		d�calage � partir duquel copier les caract�res.
	/// \param inCount		nombre de caract�res � copier.
	/// \param outChars		m�moire tampon o� stocker les caract�res.
	///
	virtual void	GetText(
						KUInt32 inOffset,
						KUInt32 inCount,
						KUInt16* outChars ) const;

	///
	/// D�termine le nombre de styles.
	///
	/// \return le nombre de styles.
	///
	virtual KUInt32 CountStyleRuns( void ) const;

	///
	/// Retourne l'indice du d�but du i-�me style.
	///
	/// \param inStyleRunIndex	indice du style dont on veut le d�but (base 0).
	/// \return l'indice du caract�re o� commence le i-�me style.
	///
	virtual KUInt32	GetStyleRunStart( KUInt32 inStyleRunIndex ) const;

	///
	/// Retourne la longueur du i-�me style.
	///
	/// \param inStyleRunIndex	indice du style dont on veut la longueur.
	/// \return le nombre de caract�res du i-�me style.
	///
	virtual KUInt32	GetStyleRunLength( KUInt32 inStyleRunIndex ) const;

	///
	/// Retourne une r�f�rence sur le n-i�me style du texte.
	///
	/// \param inStyleRunIndex	index du style � retourner (base 0).
	/// \return le n-i�me style du paragraphe.
	///
	virtual TDCLStyleRef	GetStyle( KUInt32 inStyleRunIndex ) const;

	///
	/// Modifie le style du texte entre deux caract�res.
	/// Si le style ajout� est un graphique, le texte entre les ...
	/// 
	///
	/// \param inTextIndex	d�but du bout du texte dont on veut changer le style
	/// \param inTextLength	longueur du texte dont on veut changer le style
	/// \param inStyle		style � appliquer � ce texte.
	///
	virtual void			SetStyle(
								KUInt32 inTextIndex,
								KUInt32 inTextLength,
								TDCLStyleRef inStyle );

private:
	/// \name Variables
	TDCLNSRef				mFrameRef;	///< R�f�rence sur la structure.
	TDCLNSFrame*			mFrame;		///< La structure (�vite les
										///< conversions multiples)
};

#endif
		// _TDCLCLPARAGRAPH_H

// ========================================================================== //
// Real computer scientists don't write code.  They occasionally tinker with  //
// `programming systems', but those are so high level that they hardly count  //
// (and rarely count accurately; precision is for applications).              //
// ========================================================================== //
