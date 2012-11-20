// ==============================
// Fichier:			TDCLBufferedPipe.h
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
// The Original Code is TDCLBufferedPipe.h.
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
// $Id: TDCLBufferedPipe.h,v 1.3 2004/11/24 14:08:53 paul Exp $
// ===========

#ifndef __TDCLBUFFEREDPIPE__
#define __TDCLBUFFEREDPIPE__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/TDCLPipeProxy.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>

///
/// Classe pour une connexion avec m�moire tampon. Utilisable surtout
/// pour les communications par paquets.
/// La m�moire tampon ne sert qu'en sortie.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TDCLBufferedPipe
	:
		public TDCLPipeProxy
{
public:
	///
	/// Constantes pour cette classe.
	///
	enum {
		kDefaultBufferCapacity	=	1024	///< 1 KB
	};
	
	///
	/// Constructeur � partir d'une connexion
	/// et d'une taille de m�moire tampon.
	///
	/// \param inSubPipe		connexion pour laquelle cette m�moire tampon sert
	/// \param inBufferCapacity	taille de la m�moire tampon.
	///
	TDCLBufferedPipe(
			TDCLPipe* inSubPipe,
			KUInt32 inBufferCapacity = kDefaultBufferCapacity );

	///
	/// Destructeur.
	///
	virtual ~TDCLBufferedPipe( void );

	///
	/// Lit des octets.
	///
	/// \param outBuffer	m�moire tampon pour les octets lus.
	/// \param ioCount		nombre d'octets � lire en entr�e, lus en sortie.
	///						Cette valeur est mise � jour avant que 
	///						l'exception ne soit lanc�e si un probl�me est
	///						survenu.
	/// \throws TDCLException	si un probl�me est survenu (autre que EOF)
	///
	virtual	void		Read( void* outBuffer, KUInt32* ioCount );

	///
	/// Ecrit des octets.
	///
	/// \param inBuffer		m�moire tampon pour les octets � �crire.
	/// \param ioCount		nombre d'octets � �crire en entr�e, �cris en
	///						sortie. Cette valeur est mise � jour avant que
	///						l'exception ne soit lanc�e si un probl�me est
	///						survenu.
	/// \throws TDCLException	si un probl�me est survenu.
	///
	virtual	void		Write( const void* inBuffer, KUInt32* ioCount );

	///
	/// Vide la m�moire tampon de sortie.
	///
	/// \throws TDCLException	si un probl�me est survenu.
	///
	virtual void		FlushOutput( void );

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLBufferedPipe( const TDCLBufferedPipe& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLBufferedPipe& operator = ( const TDCLBufferedPipe& inCopy );

	/// \name Variables
	void*				mBuffer;			///< M�moire tampon
	KUInt32				mBufferSize;		///< Utilisation de la m�moire
											///< tampon
	KUInt32				mBufferCapacity;	///< Taille de la m�moire tampon
};

#endif
		// __TDCLBUFFEREDPIPE__

// =========================================================================== //
// Our documentation manager was showing her 2 year old son around the office. //
// He was introduced to me, at which time he pointed out that we were both     //
// holding bags of popcorn.  We were both holding bottles of juice.  But only  //
// *__he* had a lollipop.                                                    //
//         He asked his mother, "Why doesn't HE have a lollipop?"              //
//         Her reply: "He can have a lollipop any time he wants to.  That's    //
// what it means to be a programmer."                                          //
// =========================================================================== //
