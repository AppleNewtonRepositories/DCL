// ==============================
// Fichier:			TDCLStream.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			19/01/2002
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
// The Original Code is TDCLStream.h.
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
// $Id: TDCLStream.h,v 1.4 2004/11/24 14:09:08 paul Exp $
// ===========

#ifndef __TDCLSTREAM__
#define __TDCLSTREAM__

#include <DCL/Headers/DCLDefinitions.h>

///
/// Une classe pour les objets qui peuvent �crire/lire des octets.
///
/// Utilis�e pour les connexions et les fichiers.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.4 $
///
/// \test	aucun test d�fini.
///
class TDCLStream
{
public:
		///
		/// Destructeur.
		///
		virtual				~TDCLStream( void ) {}

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
		virtual	void		Read( void* outBuffer, KUInt32* ioCount ) = 0;

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
		virtual	void		Write( const void* inBuffer, KUInt32* ioCount ) = 0;

		///
		/// Vide la m�moire tampon de sortie.
		///
		/// \throws TDCLIOException	si un probl�me est survenu.
		///
		virtual void		FlushOutput( void ) = 0;

		/// \name fonctions utilitaires
		
		///
		/// Lit n caract�res 8 bits au format C. Un caract�re nul est ajout�
		/// � la fin.
		///
		/// La cha�ne est allou�e avec malloc.
		///
		/// \param	inNbChars		le nombre de caract�res � lire.
		/// \return la cha�ne de caract�re allou�e avec malloc.
		/// \throws TDCLIOException	si un probl�me est survenu (y compris si la
		///							fin du fichier est rencontr�e)
		///
		virtual	KUInt8*		GetCString( KUInt32 inNbChars );

		///
		/// Lit des caract�res 8 bits et s'arr�te d�s qu'un caract�re nul
		/// est trouv�. Met ce caract�re nul � la fin de la cha�ne retourn�e
		/// en r�sultat.
		///
		/// La cha�ne est allou�e avec malloc.
		///
		/// \return la cha�ne de caract�re allou�e avec malloc.
		/// \throws TDCLIOException	si un probl�me est survenu (y compris si la
		///							fin du fichier est rencontr�e)
		///
		virtual	KUInt8*		GetCString( void );

		///
		/// Ecrit une cha�ne de caract�res 8 bits au format C (termin�e par un
		/// caract�re nul).
		///
		/// \param inString	la cha�ne � �crire.
		/// \throws TDCLIOException	si un probl�me est survenu.
		///
		virtual	void		PutCString( const KUInt8* inString );

		///
		/// Ecrit une cha�ne de caract�res 8 bits. La diff�rence
		/// avec la m�thode pr�c�dente est qu'ici, on n'�crit pas le
		/// caract�re nul.
		///
		/// \param inString	la cha�ne � �crire.
		/// \throws TDCLIOException	si un probl�me est survenu.
		///
		virtual	void		PutString( const char* inString );

		///
		/// Lit une cha�ne de caract�res unicode (UTF-16) au format C
		/// (termin�e par un caract�re nul).
		///
		/// La cha�ne est allou�e avec malloc.
		///
		/// \return la cha�ne de caract�re allou�e avec malloc.
		/// \throws TDCLIOException	si un probl�me est survenu (y compris si la
		///							fin du fichier est rencontr�e)
		///
		virtual	KUInt16*	GetUniString( void );

		///
		/// Ecrit une cha�ne de caract�res unicode (UTF-16) au format C
		/// (termin�e par un caract�re nul).
		///
		/// \param inString	la cha�ne � �crire.
		/// \throws TDCLIOException	si un probl�me est survenu.
		///
		virtual	void		PutUniString( const KUInt16* inString );

		///
		/// Lit un mot de 32 bits (grand indien)
		///
		/// \return le long lu.
		/// \throws TDCLIOException	si un probl�me est survenu (y compris si la
		///							fin du fichier est rencontr�e)
		///
		virtual	KUInt32		GetLong( void );

		///
		/// Ecrit un mot de 32 bits (grand indien)
		///
		/// \param	inLong	le long � �crire.
		/// \throws TDCLIOException	si un probl�me est survenu.
		///
		virtual	void		PutLong( const KUInt32 inLong );

		///
		/// Lit un mot de 32 bits (grand indien) au format XLong.
		/// Si le mot est entre 0 et 254, il tient sur un octet.
		/// Sinon, il tient sur 5 octets.
		///
		/// \return le long lu.
		/// \throws TDCLIOException	si un probl�me est survenu (y compris si la
		///							fin du fichier est rencontr�e)
		///
		virtual	KUInt32		GetXLong( void );

		///
		/// Ecrit un mot de 32 bits (grand indien) au format XLong.
		/// Si le mot est entre 0 et 254, il tient sur un octet.
		/// Sinon, il tient sur 5 octets.
		///
		/// \param	inLong	le long � �crire.
		/// \throws TDCLIOException	si un probl�me est survenu.
		///
		virtual	void		PutXLong( const KUInt32 inLong );

		///
		/// Lit un mot de 16 bits (traduction depuis le grand indien)
		///
		/// \return le mot lu.
		/// \throws TDCLIOException	si un probl�me est survenu (y compris si la
		///							fin du fichier est rencontr�e)
		///
		virtual	KUInt16		GetShort( void );

		///
		/// Ecrit un mot de 16 bits (traduction vers le grand indien)
		///
		/// \param	inShort	le mot � �crire.
		/// \throws TDCLIOException	si un probl�me est survenu.
		///
		virtual	void		PutShort( const KUInt16 inShort );

		///
		/// Lit un octet.
		///
		/// \return l'octet lu.
		/// \throws TDCLIOException	si un probl�me est survenu (y compris si la
		///							fin du fichier est rencontr�e)
		///
		virtual	KUInt8		GetByte( void );

		///
		/// Ecrit un octet.
		///
		/// \param	inByte	l'octet � �crire.
		/// \throws TDCLIOException	si un probl�me est survenu.
		///
		virtual	void		PutByte( const KUInt8 inByte );

		///
		/// R�cup�re l'octet suivant sans avancer le curseur.
		///
		/// \return l'octet lu.
		/// \throws TDCLIOException	si un probl�me est survenu (y compris si la
		///							fin du fichier est rencontr�e)
		///
		virtual	KUInt8		PeekByte( void ) = 0;
};

#endif
		// __TDCLSTREAM__

// ========================================================================= //
// As part of an ongoing effort to keep you, the Fortune reader, abreast of  //
// the valuable information the daily crosses the USENET, Fortune presents:  //
//                                                                           //
// News articles that answer *your* questions, #1:                           //
//                                                                           //
//         Newsgroups: comp.sources.d                                        //
//         Subject: how do I run C code received from sources                //
//         Keywords: C sources                                               //
//         Distribution: na                                                  //
//                                                                           //
//         I do not know how to run the C programs that are posted in the    //
//         sources newsgroup.  I save the files, edit them to remove the     //
//         headers, and change the mode so that they are executable, but I   //
//         cannot get them to run.  (I have never written a C program        //
//         before.)                                                          //
//                                                                           //
//         Must they be compiled?  With what compiler?  How do I do this?    //
//         If I compile them, is an object code file generated or must I     //
//         generate                                                          //
//         it explicitly with the > character?  Is there something else that //
//         must be done?                                                     //
// ========================================================================= //
