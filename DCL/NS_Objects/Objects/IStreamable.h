// ==============================
// Fichier:			IStreamable.h
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
// The Original Code is IStreamable.h.
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
// $Id: IStreamable.h,v 1.5 2006/02/12 01:23:56 pguyot Exp $
// ===========

#ifndef __ISTREAMABLE__
#define __ISTREAMABLE__

#include <DCL/Headers/DCLDefinitions.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>

class TDCLNSEncoder;
class TDCLXMLEncoder;
class TDCLNSOFEncoder;
class TDCLPkgEncoder;
class TDCLStream;
class TDCLTextEncoder;

///
/// Classe pour les objets qui peuvent �tre �crits et lus
/// dans/� partir d'un flux avec un encodeur/d�codeur.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.5 $
///
/// \test	aucun test d�fini.
///
class IStreamable
{
	friend class TDCLXMLEncoder;
	friend class TDCLNSOFEncoder;
	friend class TDCLTextEncoder;
	friend class TDCLPkgEncoder;

public:
	///
	/// Destructor.
	///
	virtual ~IStreamable( void ) {};

private:
	///
	/// Cr�e une repr�sentation XML de l'objet.
	/// Comprend la balise de d�but, les donn�es et la balise de fin.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	/// \param inObjectID		ID de l'objet dans ce flux.
	///
	virtual void ToXML(
				TDCLXMLEncoder* inEncoder,
				KUInt32			inObjectID ) const = 0;

	///
	/// Cr�e une repr�sentation NSOF de l'objet.
	/// Comprend le type et les donn�es.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	virtual void ToNSOF( TDCLNSOFEncoder* inEncoder ) const = 0;

	///
	/// Cr�e une repr�sentation sous forme de texte de l'objet.
	/// Comprend les s�parateurs et les donn�es.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	virtual void ToText( TDCLTextEncoder* inEncoder ) const = 0;

	///
	/// Cr�e une repr�sentation de l'objet pour mettre dans un
	/// paquet.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder	encodeur pour le paquet.
	/// \param ioOffset		en entr�e et en sortie, d�calage par rapport
	///						au paquet.
	///
	virtual void ToPkg( TDCLPkgEncoder* inEncoder, KUInt32* ioOffset ) const = 0;
};

#endif
		// __ISTREAMABLE__

// ===================================== //
// God is real, unless declared integer. //
// ===================================== //
