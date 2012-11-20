// ==============================
// Fichier:			TDCLXMLEncoder.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			16/10/2002
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
// The Original Code is TDCLXMLEncoder.h.
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
// $Id: TDCLXMLEncoder.h,v 1.6 2004/11/24 14:09:07 paul Exp $
// ===========

#ifndef __TDCLXMLENCODER__
#define __TDCLXMLENCODER__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Exchange/TDCLNSEncoder.h>

///
/// Classe pour l'encodage au format XML.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.6 $
///
/// \test	aucun test d�fini.
///
class TDCLXMLEncoder
	:
		public TDCLNSEncoder
{
public:
	///
	/// Constructeur � partir d'un flux.
	///
	/// \param inStream		flux o� �crire les donn�es encod�es.
	///
	TDCLXMLEncoder( TDCLStream* inStream );

	///
	/// Destructeur.
	///
	virtual ~TDCLXMLEncoder( void );

	///
	/// Met des tabulations (en fonction du niveau) dans le flux de sortie.
	/// Commence par une fin de ligne.
	/// Pour faire zoli.
	///
	void			PutTabulations( void );

	///
	/// Incr�mente le niveau (pour les tabulations)
	///
	inline void		IncrementLevel( void )
		{
			mLevel++;
		}

	///
	/// D�cr�mente le niveau (pour les tabulations)
	///
	inline void		DecrementLevel( void )
		{
			mLevel--;
			// Ici, il faudrait un petit assert des familles.
		}

	///
	/// Ecrit une cha�ne (UTF-8, termin�e par un caract�re nul)
	/// en rempla�ant les caract�res &, <, >, " et ' par des
	/// entit�s.
	///
	/// \param	inString	cha�ne � �crire au format UTF-8 et
	///						termin�e par un caract�re nul qui
	///						n'est pas �crit.
	///
	void			PrintUTF8WithEntities( const KUInt8* inString );

	///
	/// Ecrit une cha�ne ASCII (termin�e par un caract�re nul)
	/// en rempla�ant les caract�res &, <, >, " et ' et les caract�res
	/// 8 bits par des entit�s.
	///
	/// \param	inString	cha�ne � �crire au format ASCII et
	///						termin�e par un caract�re nul qui
	///						n'est pas �crit.
	///
	void			Print8BitsWithEntities( const KUInt8* inString );

protected:
	///
	/// Met dans le flux la r�f�rence d'un objet d�j� encod�.
	///
	/// \param inRefID		r�f�rence de l'objet ajout�.
	/// \param inCookie		en entr�e, biscuit laiss� par PutObject
	///						lorsque l'objet a �t� ajout� la premi�re fois.
	///
	virtual void	PutPrecedent( KUInt32 inRefID, KUIntPtr inCookie );

	///
	/// Met dans le flux un objet donn�.
	///
	/// \param inObject		objet � ajouter.
	/// \param inObjectID	ID de l'objet � ajouter, -1 si CanHavePrecedentID
	///						a retourn� \c false.
	/// \param outCookie	en sortie, biscuit pass� par la suite �
	///						PutPrecedent, \c nil si CanHavePrecedentID a
	///						retourn� \c false.
	///
	virtual void	PutObject(
						const TDCLNSObject* inObject,
						KUInt32 inObjectID,
						KUIntPtr* outCookie );

	///
	/// Met dans le flux une r�f�rence ou un imm�diat donn�s.
	///
	/// \param inRef		r�f�rence � ajouter.
	///
	virtual void	PutRef( const TDCLNSRef& inRef );

	///
	/// D�termine si l'objet donn� peut �tre r�f�renc� par un "precedent".
	///
	/// Retourne \c false pour les symboles, \c true sinon.
	///
	/// \param inObject		objet consid�r�.
	/// \return \c true si l'objet peut �tre r�f�renc�, \c false sinon.
	///
	virtual Boolean	CanHavePrecedentID( TDCLNSObject* inObject );

private:
	KUInt32				mLevel;	///< Niveau (pour les tabulations)
	
	///< Constantes.
	static const char*	kXMLHeader;			///< Ent�te XML (<?xml version ...)
	static const char*	kDOCTYPEElement;	///< El�ment DOCTYPE avec l'URL
};

#endif
		// __TDCLXMLENCODER__

// ========================================================================== //
// `Lasu' Releases SAG 0.3 -- Freeware Book Takes Paves For New World Order   //
// by staff writers                                                           //
//                                                                            //
//         ...                                                                //
//         The SAG is one of the major products developed via the Information //
// Superhighway, the brain child of Al Gore, US Vice President.  The ISHW     //
// is being developed with massive govenment funding, since studies show      //
// that it already has more than four hundred users, three years before       //
// the first prototypes are ready.  Asked whether he was worried about the    //
// foreign influence in an expensive American Dream, the vice president       //
// said, ``Finland?  Oh, we've already bought them, but we haven't told       //
// anyone yet.  They're great at building model airplanes as well.  And _I   //
// can spell potato.''  House representatives are not mollified, however,     //
// wanting to see the terms of the deal first, fearing another Alaska.        //
//         Rumors about the SAG release have imbalanced the American stock    //
// market for weeks.  Several major publishing houses reached an all time     //
// low in the New York Stock Exchange, while publicly competing for the       //
// publishing agreement with Mr. Wirzenius.  The negotiations did not work    //
// out, tough.  ``Not enough dough,'' says the author, although spokesmen     //
// at both Prentice-Hall and Playboy, Inc., claim the author was incapable    //
// of expressing his wishes in a coherent form during face to face talks,     //
// preferring to communicate via e-mail.  ``He kept muttering something       //
// about jiffies and pegs,'' they say.                                        //
//         ...                                                                //
//                 -- Lars Wirzenius <wirzeniu@cs.helsinki.fi>                //
//                    [comp.os.linux.announce]                                //
// ========================================================================== //
