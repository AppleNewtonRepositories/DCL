// ==============================
// Fichier:			TDCLPkgEncoder.h
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
// The Original Code is TDCLPkgEncoder.h.
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
// $Id: TDCLPkgEncoder.h,v 1.8 2004/11/24 14:09:06 paul Exp $
// ===========

#ifndef _TDCLPKGENCODER_H
#define _TDCLPKGENCODER_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/NS_Objects/Exchange/TDCLNSEncoder.h>
#include <DCL/NS_Objects/Exchange/KDCLPkg.h>

class TDCLRandomAccessStream;

///
/// Classe pour l'encodage au format paquet.
/// Le format est d�crit dans Newton Formats.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.8 $
///
/// \test	UTestPkg
///
class TDCLPkgEncoder
	:
		public TDCLNSEncoder,
		public KDCLPkg
{
public:
	///
	/// Constructeur � partir d'un flux et d'un d�calage dans le flux.
	/// Ce d�calage correspond au nombre d'octets d�j� �crits dans le
	/// paquet et le m�me d�calage devra �tre utilis� pour le d�codage.
	///
	/// \param inStream		flux utilis� par cet encodeur.
	/// \param inOffset		d�calage pour l'encodage des r�f�rences.
	/// \param inFourBytesPadding	si on aligne sur 4 octets (NewtonOS 2.x
	///						uniquement). Par d�faut, l'alignement est sur
	///						8 octets.
	///
	TDCLPkgEncoder(
			TDCLRandomAccessStream* inStream,
			KUInt32 inOffset,
			Boolean inFourBytesPadding = false );

	///
	/// Constructeur � partir d'un flux. Le d�calage est la position
	/// actuelle du flux.
	///
	/// \param inStream		flux utilis� par cet encodeur.
	/// \param inFourBytesPadding	si on aligne sur 4 octets (NewtonOS 2.x
	///						uniquement). Par d�faut, l'alignement est sur
	///						8 octets.
	///
	TDCLPkgEncoder(
			TDCLRandomAccessStream* inStream,
			Boolean inFourBytesPadding = false );

	///
	/// Destructeur.
	///
	virtual ~TDCLPkgEncoder( void );

	///
	/// Accesseur sur le flux de sortie.
	///
	/// \return le flux de sortie sur lequel �crire les donn�es.
	///
	inline TDCLRandomAccessStream* GetOutputStream( void ) const
		{
			return (TDCLRandomAccessStream*)
				TDCLNSEncoder::GetOutputStream();
		}

	///
	/// Ajoute un objet dans le flux.
	/// M�thode appel�e r�cursivement par les m�thodes ToPkg des objets.
	///
	/// \param inObject		r�f�rence de l'objet � ajouter
	///
	virtual void	AddObject( const TDCLNSRef& inObject );

	///
	/// D�termine le d�calage du prochain objet.
	///
	/// \return le d�calage vers le prochain objet dans le flux.
	///
	inline KUInt32	GetNextObjectOffset( void ) const
		{
			return mOffset;
		}

	///
	/// Aligne une positiond dans le flux, sans modifier le flux, par
	/// rapport � un d�calage donn� en suivant \c mFourBytesPadding.
	///
	/// \param inOffset	en entr�e, d�calage courant, en sortie, d�calage
	///					apr�s l'alignement.
	///
	void			AlignOffset( KUInt32* inOffset ) const;

	///
	/// Aligne le flux si n�cessaire par rapport � un d�calage donn� en suivant
	/// \c mFourBytesPadding.
	///
	/// \param inOffset	en entr�e, d�calage courant, en sortie, d�calage
	///					apr�s l'alignement.
	///
	void			AlignStream( KUInt32* inOffset ) const;

	///
	/// D�termine si le flux est align� sur 8 octets ou 4.
	///
	/// \return \c true si l'alignement se fait sur 4 octets.
	///
	inline Boolean	IsFourBytesPadded( void ) const
		{
			return mFourBytesPadding;
		}

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

private:
	///
	/// Cr�e la pile et �crit l'ent�te (le premier tableau).
	///
	void			Init( void );

	///
	/// Constantes pour cette classe.
	///
	enum {
		kStackChunkSize		= 10,	///< Incr�ment de la pile lorsqu'elle est pleine.
		kStackDecrThreshold	= 50	///< D�cr�ment de la pile lorsqu'elle se vide.
	};
	
	///
	/// Structure pour les objets dans la pile.
	///
	struct SStackItem {
		TDCLNSObject*		fObjectPtr;	///< Pointeur sur l'objet.
		KSInt64				fPtrOffset;	///< D�calage vers le pointeur dans le flux.
	};
	
	///
	/// Pousse un objet dans la pile.
	///
	/// \param inObject		r�f�rence sur l'objet � stocker dans la pile.
	///
	void			PushToStack( const TDCLNSRef& inObject );

	KSInt64			mOriginOffset;			///< D�calage du d�but du paquet
											///< dans le flux.
	KUInt32			mOffset;				///< D�calage courant dans le flux.
	KUInt32			mPartOffset;			///< D�calage de la partie par
											///< rapport au d�but du paquet.
	Boolean			mFourBytesPadding;		///< Alignement sur 4 octets (au lieu
											///< de 8).
	SStackItem*		mStack;					///< Pile des objets � stocker.
	KUInt32			mStackAllocatedSize;	///< Nombre d'�l�ments que la pile
											///< peut contenir.
	KUInt32			mStackSize;				///< Nombre d'�l�ments que la pile
											///< contient.
	Boolean			mInSlottedObject;		///< Si le flux est dans un objet.
};

#endif
		// _TDCLPKGENCODER_H

// ======================================= //
// I wish you humans would leave me alone. //
// ======================================= //
