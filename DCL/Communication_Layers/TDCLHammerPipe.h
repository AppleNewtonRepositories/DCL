// ==============================
// Fichier:			TDCLHammerPipe.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			27/01/2002
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
// The Original Code is TDCLHammerPipe.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k,
// Filip Zawadiak and Nicolas Zinovieff. Portions created by the Initial 
// Developers are Copyright (C) 1998-2004 the Initial Developers. All Rights
// Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Filip Zawadiak <philz@vyx.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
//
// Copyright (c) 2001 Filip Zawadiak <philz@vyx.net>
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
// 1. Redistributions of source code must retain the above copyright
//   notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright
//   notice, this list of conditions and the following disclaimer in the
//   documentation and/or other materials provided with the distribution.
// 3. The name of the author may not be used to endorse or promote products
//   derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
// IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
// OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
// THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// ===========
// $Id: TDCLHammerPipe.h,v 1.3 2004/11/24 14:08:53 paul Exp $
// ===========

#ifndef __TCL_HAMMERPIPE_
#define __TCL_HAMMERPIPE_

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/TDCLPipeProxy.h>

// DCL
#include <DCL/Exceptions/IO_Exceptions/TDCLIOException.h>

/// \author	Paul Guyot <pguyot@kallisys.net>
/// \author	Eckhart Koppen <eck@40hz.org>
/// \author	Filip Zawadiak <philz@vyx.net> (?)
/// \version $Revision: 1.3 $
///
class TDCLHammerPipe
	:
		public TDCLPipeProxy
{
public:
	///
	/// Constantes pour cette classe.
	///
	enum {
		kDefaultOutputMaxBufferSize	= 253,	///< 256 - 3.
		///< Le code de microcom donne 64+5. Philz donne 2K
		///< cependant il n'a pas de paquets plus gros que 256 (il tron�onne
		///< le paquet Newton � installer en morceaux de 128 octets). Le Newton
		///< n'aime pas mes paquets de 299 octets, en revanche, �a marche
		///< avec 253+3.
		kInputFrameIncrement		= 1024	///< 1 KB
	};

	///
	/// Constructeur � partir d'une couche de communication et d'une taille
	/// maximale de m�moire tampon de sortie.
	///
	/// \param inSubPipe				couche de communication sur laquelle
	///									faire de la compression MNP.
	/// \param inOutputMaxBufferSize	taille maximale de la m�moire tampon
	///									de sortie.
	///
	TDCLHammerPipe(
			TDCLPipe* inSubPipe,
			KUInt32 inOutputMaxBufferSize = kDefaultOutputMaxBufferSize );

	///
	/// Destructeur.
	///
	virtual ~TDCLHammerPipe( void );

	/// \name interface entr�e/sortie

	///
	/// Lit des octets.
	///
	/// \param outBuffer	m�moire tampon pour les octets lus.
	/// \param ioCount		nombre d'octets � lire en entr�e, lus en sortie.
	///						Cette valeur est mise � jour avant que 
	///						l'exception ne soit lanc�e si un probl�me est
	///						survenu.
	/// \throws TDCLIOException	si un probl�me est survenu (autre que EOF)
	///
	virtual	void		Read( void* outBuffer, KUInt32* ioCount );

	///
	/// Read one frame only
	///
	/// \param outBuffer	m�moire tampon pour les octets lus.
	/// \param ioCount		nombre d'octets � lire en entr�e, lus en sortie.
	///						Cette valeur est mise � jour avant que 
	///						l'exception ne soit lanc�e si un probl�me est
	///						survenu.
	/// \throws TDCLIOException	si un probl�me est survenu (autre que EOF)
	///
	virtual	void		ReadFrames( void* outBuffer, KUInt32* ioCount, bool inStopAfterOne );

	///
	/// Ecrit des octets.
	///
	/// \param inBuffer		m�moire tampon pour les octets � �crire.
	/// \param ioCount		nombre d'octets � �crire en entr�e, �cris en
	///						sortie. Cette valeur est mise � jour avant que
	///						l'exception ne soit lanc�e si un probl�me est
	///						survenu.
	/// \throws TDCLIOException	si un probl�me est survenu.
	///
	virtual	void		Write( const void* inBuffer, KUInt32* ioCount );

	///
	/// Vide la m�moire tampon de sortie.
	///
	/// \throws TDCLIOException	si un probl�me est survenu.
	///
	virtual void		FlushOutput( void );

	///
	/// D�termine si des octets sont disponibles dans la m�moire tampon d'entr�e.
	///
	/// \return \c true s'il y a des octets disponibles, \c false sinon.
	///
	virtual	Boolean		BytesAvailable( void );

	///
	/// D�connecte le canal de communication avec le client.
	///
	virtual	void		Disconnect( void );

	///
	/// M�thode appel�e par le lien pour dire qu'il est connect�
	/// via cette connexion. Cette m�thode est appel�e juste avant
	/// que des donn�es soient �chang�es.
	///
	/// Envoie l'ent�te MNP (et re�oit celui du Newton).
	///
	/// \return l'interface de communication.
	///
	virtual	TDCLCommLayer*	Connected( TDCLLink* inLink );

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLHammerPipe( const TDCLHammerPipe& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLHammerPipe& operator = ( const TDCLHammerPipe& inCopy );
	
	///
	/// Lecture d'une structure MNP depuis le Newton.
	///
	/// \param outFrame	un pointeur, allou� avec malloc, sur les donn�es d'une
	///					structure MNP d�cod�es.
	/// \param outSize	taille des donn�es.
	/// \throws TDCLIOException si un probl�me est survenu.
	///
	void	ReadFrame( KUInt8** outFrame, KUInt32* outSize );

	///
	/// �criture d'une structure vers le Newton.
	///
	/// \param inFrame	pointeur vers les donn�es d'une structure MNP.
	/// \param inSize	nombre d'octets des donn�es.
	/// \throws TDCLIOException si un probl�me est survenu.
	///
	void	WriteFrame( const KUInt8* inFrame, KUInt32 inSize );

	///
	/// Re�oit des donn�es du Newton.
	///
	/// \throws TDCLIOException	si un probl�me est survenu.
	///
	virtual void		ReceiveData( void );

	///
	/// Envoie des donn�es au Newton.
	///
	/// \throws TDCLIOException	si un probl�me est survenu.
	///
	virtual void		SendData( void );

	///
	/// Met � jour la somme de contr�le.
	///
	/// \param inCRC		l'ancienne somme de contr�le.
	/// \param inByte		octet dont on veut la somme de contr�le.
	/// \return la nouvelle somme de contr�le.
	///
	KUInt16	UpdateCRC16( KUInt16 inCRC, KUInt8 inByte );

	/// \name Constantes

	static const KUInt16	kCRC16Table[256];	///< Table pour le calcul de la
											///< somme de contr�le.
	static const KUInt8 SYN;	///< Caract�re SYN dans la transmission MNP.
	static const KUInt8 DLE;	///< Caract�re DLE dans la transmission MNP.
	static const KUInt8 STX;	///< Caract�re STX dans la transmission MNP.
	static const KUInt8 ETX;	///< Caract�re ETX dans la transmission MNP.
	static const KUInt8 LA;	///< Structure LA
	static const KUInt8 LT;	///< Structure LT
	static const KUInt8 kMNPHeader[24];		///< Ent�te MNP
	static const KUInt8 kMNPFooter[8];		///< S�rie d'octets envoy�s lors
											///< de la d�connexion.
	static const KUInt8 kDefaultCredits;

	/// \name Variables

	KUInt8*	mInputBuffer;			///< M�moire tampon d'entr�e.
	KUInt32	mInputBufferCapacity;	///< Contenance de la m�moire tampon d'entr�e.
	KUInt32	mInputBufferSize;		///< Taille de la m�moire tampon d'entr�e.
	KUInt32	mInputBufferCrsr;		///< Curseur sur la m�moire tampon d'entr�e.
	KUInt8*	mOutputBuffer;			///< M�moire tampon de sortie
	KUInt32	mOutputBufferCapacity;	///< Taille maximale de la m�moire tampon de sortie.
	KUInt32	mOutputBufferCrsr;		///< Index des prochains octets dans la m�moire
									///< tampon de sortie.
	KUInt8	mInputPacketIndex;		///< Indice du paquet d'entr�e.
	KUInt8	mOutputPacketIndex;		///< Indice du paquet de sortie.
};

#endif
		// __TCL_HAMMERPIPE_

// ====================================================================== //
// C makes it easy for you to shoot yourself in the foot.  C++ makes that //
// harder, but when you do, it blows away your whole leg.                 //
//                 -- Bjarne Stroustrup                                   //
// ====================================================================== //
