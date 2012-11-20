// ==============================
// Fichier:			TDCLPkgDecoder.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			21/2/2004
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
// The Original Code is TDCLPkgDecoder.h.
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
// $Id: TDCLPkgDecoder.h,v 1.9 2004/11/24 14:09:05 paul Exp $
// ===========

#ifndef _TDCLPKGDECODER_H
#define _TDCLPKGDECODER_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Exchange/TDCLNSDecoder.h>
#include <DCL/NS_Objects/Exchange/KDCLPkg.h>
#include <DCL/Streams/TDCLRandomAccessStream.h>

///
/// Classe pour le d�codeur du format paquet.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.9 $
///
/// \test	UTestPkg
///
class TDCLPkgDecoder
	:
		public TDCLNSDecoder,
		public KDCLPkg
{
public:
	///
	/// Constructeur � partir d'un flux et d'un d�calage dans le flux.
	/// C'est le d�calage depuis le d�but du paquet. Le m�me d�calage
	/// a d� �tre utilis� lors de l'encodage.
	///
	/// \param inStream		flux o� lire les donn�es.
	/// \param inOffset		d�calage pour l'encodage des r�f�rences.
	///
	TDCLPkgDecoder(
			TDCLRandomAccessStream* inStream,
			KUInt32 inOffset );

	///
	/// Constructeur � partir d'un flux. Le d�calage est la position
	/// actuelle du flux.
	///
	/// \param inStream		flux utilis� par cet encodeur.
	///
	TDCLPkgDecoder( TDCLRandomAccessStream* inStream );

	///
	/// Destructeur.
	///
	virtual ~TDCLPkgDecoder( void );

	///
	/// Cr�e l'objet suivant. Lit le tableau initial.
	/// Positionne ensuite le flux sur les octets apr�s le dernier objet,
	/// �ventuellement apr�s des octets d'alignement.
	///
	/// \return une r�f�rence vers l'objet suivant.
	///
	virtual TDCLNSRef	GetNextObject( void );

	///
	/// Accesseur sur le flux de lecture.
	///
	/// \return le flux o� lire les donn�es.
	///
	inline TDCLRandomAccessStream* GetInputStream( void ) const
		{
			return (TDCLRandomAccessStream*)
				TDCLNSDecoder::GetInputStream();
		}

	///
	/// Accesseur sur le d�calage dans le flux de lecture.
	/// Cette m�thode est utilis�e pour d�terminer le d�calage d'un objet lorsqu'il
	/// est d�cod�.
	///
	/// \return le d�calage du flux par rapport au d�but du paquet.
	///
	inline KUInt32 GetCurrentStreamOffset( void ) const
		{
			return (KUInt32) (GetInputStream()->GetCursor() - mOriginOffset);
		}

	///
	/// Ajoute un objet dans la liste des objets.
	///
	/// \param inObject		objet � ajouter
	/// \param inOffset		d�calage de l'objet dans le flux par rapport au
	///						d�but du paquet.
	///
	inline void	AddObjectToList(
					const TDCLNSRef& inObject,
					KUInt32 inOffset )
		{
			TDCLNSDecoder::AddObjectToList( inObject, (KUIntPtr) inOffset );
		}

	///
	/// Accesseur sur l'alignement.
	///
	/// \return \c true si l'alignement se fait sur 8 octets.
	///
	inline Boolean		GetFourBytesPadding( void )
		{
			return mFourBytesPadding;
		}

private:
	///
	/// Lecture du premier tableau.
	/// Positionne le flux sur le pointeur vers le premier objet.
	///
	/// \param inStream		flux � lire.
	///
	void		ReadFirstArray( TDCLRandomAccessStream* inStream );
	
	KSInt64		mOriginOffset;		///< D�calage dans le flux du d�but du paquet.
	KSInt64		mMaxOffset;			///< D�calage maximal.
	Boolean		mTopLevel;			///< Si on est � la racine de l'arbre de r�cursion.
	Boolean		mFourBytesPadding;	///< Si l'alignement se fait sur 8 octets.
};

#endif
		// _TDCLPKGDECODER_H

// =========================================================================== //
// Thus spake the master programmer:                                           //
//         "A well-written program is its own heaven; a poorly-written program //
// is its own hell."                                                           //
//                 -- Geoffrey James, "The Tao of Programming"                 //
// =========================================================================== //
