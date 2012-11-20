// ==============================
// Fichier:			TDCLMemStream.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			19/10/2002
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
// The Original Code is TDCLMemStream.h.
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
// $Id: TDCLMemStream.h,v 1.6 2004/11/24 14:09:08 paul Exp $
// ===========

#ifndef __TDCLMEMSTREAM__
#define __TDCLMEMSTREAM__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Streams/TDCLRandomAccessStream.h>

///
/// Classe pour un flux maintenu en m�moire.
/// L'�criture remplit la m�moire tampon.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.6 $
///
/// \test	aucun test d�fini.
///
class TDCLMemStream
	:
		public TDCLRandomAccessStream
{
public:
	///
	/// Constructeur par d�faut.
	///
	TDCLMemStream( void );

	///
	/// Constructeur � partir d'une m�moire tampon.
	/// Les donn�es sont copi�es.
	///
	/// \param inBuffer		m�moire tampon o� se trouvent les donn�es
	///						� copier.
	/// \param inLength		taille en octets de cette m�moire tampon.
	///
	TDCLMemStream( const void* inBuffer, KUInt32 inLength );

	///
	/// Destructeur.
	///
	virtual ~TDCLMemStream( void );

	/// \name interface TDCLRandomAccessStream
	
	///
	/// D�termine la position du curseur dans le flux.
	///
	/// \return la position du curseur par rapport au d�but du flux.
	///
	virtual KSInt64 GetCursor( void );

	///
	/// D�place le curseur dans le flux. Peut lancer une exception
	/// pour indiquer que la fin du flux a �t� atteinte.
	///
	/// \param inPos	nouvelle position du curseur
	/// \param inMode	d�finit l'origine de \c inPos
	/// \throws TDCLPositionException si la fin du flux (ou le d�but) est
	///			d�pass�e.
	///
	virtual void SetCursor( KSInt64 inPos, ECursorMode inMode );

	/// \name interface entr�e/sortie

	///
	/// Lit des octets et avance le curseur dans la m�moire tampon.
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
	/// Accesseur sur la m�moire tampon.
	///
	/// \return le pointeur sur la m�moire tampon.
	///
	inline const void*	GetBuffer( void )
		{
			return mBuffer;
		}

	///
	/// Accesseur sur la taille de la m�moire tampon.
	///
	/// \return la taille de la m�moire tampon.
	///
	inline KUInt32		GetBufferSize( void )
		{
			return mBufferSize;
		}

	///
	/// R�cup�re l'octet suivant sans avancer le curseur.
	///
	/// \return l'octet lu.
	/// \throws TDCLIOException	si un probl�me est survenu (y compris si la
	///							fin du fichier est rencontr�e)
	///
	virtual	KUInt8		PeekByte( void );

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLMemStream( const TDCLMemStream& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLMemStream& operator = ( const TDCLMemStream& inCopy );

	///
	/// Constantes pour cette classe.
	///
	enum {
		kSizeIncrement	= 256	///< Nombre d'octets pour l'incr�ment
								///< de la m�moire tampon.
	};
	
	/// \name Variables

	void*		mBuffer;		///< M�moire tampon
	KUInt32		mBufferSize;	///< Taille de la m�moire tampon
	KUInt32		mAllocatedSize;	///< Taille allou�e de la m�moire
								///< tampon
	KUInt32		mCursor;		///< Curseur dans la m�moire tampon
								///< pour la lecture et l'�criture.
};

#endif
		// __TDCLMEMSTREAM__

// ===================================================================== //
// I have never seen anything fill up a vacuum so fast and still suck.   //
//                 -- Rob Pike, on X.                                    //
//                                                                       //
// Steve Jobs said two years ago that X is brain-damaged and it will be  //
// gone in two years.  He was half right.                                //
//                 -- Dennis Ritchie                                     //
//                                                                       //
// Dennis Ritchie is twice as bright as Steve Jobs, and only half wrong. //
//                 -- Jim Gettys                                         //
// ===================================================================== //
