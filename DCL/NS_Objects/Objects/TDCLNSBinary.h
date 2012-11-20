// ==============================
// Fichier:			TDCLNSBinary.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			07/08/2002
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
// The Original Code is TDCLNSBinary.h.
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
// $Id: TDCLNSBinary.h,v 1.5 2004/11/24 14:09:07 paul Exp $
// ===========

#ifndef __TDCLNSBINARY__
#define __TDCLNSBINARY__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Objects/TDCLNSObject.h>

// DCL
#include <DCL/Exceptions/TDCLException.h>
#include <DCL/NS_Objects/Objects/TDCLNSRef.h>
#include <DCL/NS_Objects/Objects/KDCLSYM.h>

class TDCLStream;
class TDCLNSEncoder;
class TDCLNSOFDecoder;
class TDCLPkgDecoder;

///
/// Classe pour les binaires NewtonScript.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.5 $
///
/// \test	aucun test d�fini.
///
class TDCLNSBinary
	:
		public TDCLNSObject
{
public:
	///
	/// Constructeur � partir d'une classe et d'une taille.
	/// Remarque: inClass est normalement un symbole. Mais comme sur le
	/// Newton, on peut prendre n'importe quel objet.
	///
	TDCLNSBinary(
			const TDCLNSRef& inClass = KDCLSYM::kSYMbinary,
			KUInt32 inSize = 0 );

	///
	/// Constructeur par copie.
	/// Les donn�es sont dupliqu�es.
	///
	/// \param inCopy	objet � copier.
	///
	explicit TDCLNSBinary( const TDCLNSBinary& inCopy );

	///
	/// Constructeur � partir d'un pointeur et d'une taille.
	///
	/// \param inData		donn�es pour le binaire (copi�es).
	/// \param inLength		taille, en octets, du binaire.
	/// \param inClass		classe du binaire.
	///
	TDCLNSBinary(
			const void* inData,
			KUInt32 inLength,
			const TDCLNSRef& inClass = KDCLSYM::kSYMbinary );

	///
	/// Constructeur � partir d'un flux et d'une taille.
	///
	/// \param inStream		flux o� lire les donn�es.
	/// \param inLength		nombre d'octets � lire
	/// \param inClass		classe du binaire.
	///
	TDCLNSBinary(
			TDCLStream* inStream,
			KUInt32 inLength,
			const TDCLNSRef& inClass = KDCLSYM::kSYMbinary );

	///
	/// Destructeur.
	/// Lib�re la m�moire tampon.
	///
	virtual ~TDCLNSBinary( void );

	///
	/// Op�rateur d'assignation.
	///
	/// \param inCopy		objet � copier
	///
	TDCLNSBinary& operator = ( const TDCLNSBinary& inCopy );

	///
	/// D�termine si cet objet est un binaire.
	///
	/// \return \c true
	///
	virtual Boolean IsBinary( void ) const;

	///
	/// D�termine si cet objet est une cha�ne.
	///
	/// \return \c true si la classe correspond.
	///
	virtual Boolean IsString( void ) const;

	///
	/// Accesseur sur la taille du binaire.
	///
	/// \return la taille du binaire
	///
	inline KUInt32	GetLength( void ) const
		{
			return mBufferSize;
		}
	
	///
	/// Redimensionne le binaire.
	///
	/// \param inLength		nouvelle taille du binaire
	///
	void	SetLength( KUInt32 inLength );
	
	///
	/// Accesseur sur les donn�es du binaire.
	///
	/// \return le pointeur sur le binaire (valide tant que le binaire
	///		n'est pas redimensionn�)
	///
	inline void*	GetPointer( void )
		{
			return mBuffer;
		}

	///
	/// Accesseur sur les donn�es du binaire, en lecture seule.
	///
	/// \return le pointeur sur le binaire (valide tant que le binaire
	///		n'est pas redimensionn�)
	///
	inline const void*	GetPointer( void ) const
		{
			return mBuffer;
		}
	
	///
	/// Cr�e une copie de surface de la cha�ne.
	/// Appelle le constructeur par copie.
	///
	/// \return une copie de surface de this.
	///
	virtual TDCLNSObject*	Clone( void ) const;

	///
	/// Cr�e un objet � partir d'un flux NSOF
	///
	/// \param inDecoder	d�codeur NSOF associ� � un flux donn�.
	/// \return un nouvel objet � partir de ce flux
	///
	static	TDCLNSBinary*	FromNSOF( TDCLNSOFDecoder* inDecoder );

	///
	/// Cr�e un objet � partir d'un flux NSOF (en tant que binaire large)
	///
	/// \param inDecoder	d�codeur NSOF associ� � un flux donn�.
	/// \return un nouvel objet � partir de ce flux
	///
	static	TDCLNSBinary*	FromNSOFAsLargeBinary( TDCLNSOFDecoder* inDecoder );

	///
	/// Cr�e un objet � partir d'un paquet.
	///
	/// \param inDecoder	d�codeur Pkg associ� � un flux donn�.
	/// \return un nouvel objet � partir de ce flux
	///
	static	TDCLNSBinary*	FromPkg( TDCLPkgDecoder* inDecoder );

	///
	/// D�termine la classe de ce binaire.
	/// Ce n'est pas forc�ment un symbole.
	///
	/// \return une r�f�rence vers la classe de ce binaire.
	///
	virtual TDCLNSRef ClassOf( void ) const;

	///
	/// D�termine la classe primaire de ce binaire.
	/// Il s'agit forc�ment d'un symbole.
	///
	/// \return une r�f�rence vers la classe primaire de ce binaire.
	///
	virtual TDCLNSRef PrimClassOf( void ) const;

	///
	/// Change la classe de ce binaire.
	/// Ce n'est pas forc�ment un symbole.
	///
	/// \param	inClass un objet qui sert de nouvelle classe � ce binaire.
	/// \throws TDCLNSException si une erreur est survenue.
	///
	virtual void SetClass( const TDCLNSRef& inClass );

protected:
	///
	/// Cr�e une repr�sentation NSOF du binaire.
	/// Comprend le type et les donn�es.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	virtual void ToNSOF( TDCLNSOFEncoder* inEncoder ) const;

	///
	/// Constructeur � partir d'une zone de m�moire d�j� allou�e.
	///
	/// \param inData		donn�es pour le binaire (non copi�es).
	/// \param inLength		taille, en octets, du binaire.
	/// \param inClass		classe du binaire.
	///
	TDCLNSBinary(
			void* inData,
			KUInt32 inLength,
			const TDCLNSRef& inClass = KDCLSYM::kSYMbinary );
	
private:
	///
	/// Constructeur par d�faut volontairement indisponible.
	///
	TDCLNSBinary( void );

	/// \name Interface IStreamable
	// @{
	///
	/// Cr�e une repr�sentation XML du binaire.
	/// Comprend la balise de d�but, les donn�es et la balise de fin.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	/// \param inObjectID		ID de l'objet dans ce flux.
	///
	virtual void ToXML(
				TDCLXMLEncoder* inEncoder,
				KUInt32			inObjectID ) const;

	///
	/// Cr�e une repr�sentation sous forme de texte du binaire.
	/// Comprend les chevrons et les donn�es.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder		encodeur avec la liste des objets d�j�
	///							encod�s pour les IDs.
	///
	virtual void ToText( TDCLTextEncoder* inEncoder ) const;

	///
	/// Cr�e une repr�sentation du binaire pour mettre dans un
	/// paquet.
	/// Appelle r�cursivement les m�thodes de l'encodeur.
	///
	/// \param inEncoder	encodeur pour le paquet.
	/// \param ioOffset		en entr�e et en sortie, d�calage par rapport
	///						au paquet.
	///
	virtual void ToPkg( TDCLPkgEncoder* inEncoder, KUInt32* ioOffset ) const;
	// @}
	
	/// \name Variables Priv�es
	TDCLNSRef		mClass;			///< Classe du binaire
	void*			mBuffer;		///< M�moire tampon
	KUInt32			mBufferSize;	///< Taille de la m�moire tampon
};

#endif
		// __TDCLNSBINARY__

// =========================================== //
// I've looked at the listing, and it's right! //
//                 -- Joel Halpern             //
// =========================================== //
