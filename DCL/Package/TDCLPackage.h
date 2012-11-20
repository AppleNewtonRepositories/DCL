// ==============================
// Fichier:			TDCLPackage.h
// Projet:			Desktop Connection Library
// 
// Cr�� le:			29/10/2003
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
// The Original Code is TDCLPackage.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 1999-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: TDCLPackage.h,v 1.16 2004/11/24 14:09:08 paul Exp $
// ===========

#ifndef _TDCLPACKAGE_H
#define _TDCLPACKAGE_H

#include <DCL/Headers/DCLDefinitions.h>

class TDCLFile;
class TDCLStream;
class TDCLPkgPart;

///
/// Classe pour un paquet Newton.
/// D�riv� de TNewtonPackage (interne).
///
/// Cette classe g�re essentiellement le catalogue des paquets. Lorsqu'un objet
/// de cette classe est cr�� � partir d'une m�moire tampon ou d'un fichier, les
/// donn�es des parties sont copi�es. Elles ne sont analys�es que la premi�re
/// fois qu'elles sont acc�d�es.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.16 $
///
/// \test	aucun test d�fini.
///
class TDCLPackage
{
public:
	///
	/// Drapeaux pour SPackageDirectory
	/// Les autres bits sont r�serv�s et doivent �tre � z�ro.
	///
	enum {
		/// Les parties du paquet doivent �tre supprim�es imm�diatement
		/// apr�s l'installation. Lorsqu'un paquet avec ce drapeau � un est
		/// activ�, le syst�me active ses parties puis ensuite les d�sactive
		/// sans proc�der � la d�sactivation normale des parties (comme
		/// appeler removeScript). Ceci n'est recommand� que pour les paquets
		/// en une seule partie de type 'auto'.
		///
		/// N�anmoins, les mise � jour syst�me ont ce bit � un, m�me si elles
		/// sont compos�es de plusieurs parties.
		kDirAutoRemoveFlag				= 0x80000000,
		
		/// Marque le paquet comme prot�g� pour la copie. Ce drapeau ne sert
		/// que parce que les logiciels qui copient les paquets le respectent.
		/// Ce n'est pas un verrou absolu contre la copie.
		/// Le syst�me refuse d'envoyer par infra-rouge ou par courrier
		/// �lectronique les paquets avec ce bit � un. Un tel paquet peut
		/// n�anmoins �tre sauvegard� sur une carte ou synchronis� avec un
		/// ordinateur de bureau, donc les utilisateurs peuvent le copier. Ils
		/// peuvent aussi utiliser EEUnprotect.
		kDirCopyProtectFlag				= 0x40000000,
		
		/// Indique au syst�me qu'il ne doit pas compresser le paquet (par
		/// d�faut les paquets sont compress�s).
		kDirNoCompressionFlag			= 0x10000000,

		/// Indique que le paquet contient des informations de relogement.
		/// Ce drapeau n'est valide que pour les paquets de type "package1".	
		kDirRelocationFlag				= 0x04000000,

		/// Sp�cifie que le paquet doit �tre compress� avec une m�thode plus
		/// rapide mais moins efficace. Ce drapeau n'est valide que pour les
		/// paquets de type "package1" et n'est pris en compte que si le
		/// drapeau kDirNoCompressionFlag n'est pas � un.
		kDirUseFasterCompressionFlag	= 0x02000000,
		
		/// Indique que le paquet a une signature num�rique qui certifie
		/// qu'il fonctionne sur Watson.
		/// La signature est dans une partie de type raw et fait 32 bits.
		/// C'est tout ce que je sais pour le moment.
		kWatsonSignaturePresentFlag		= 0x01000000
	};
	
	/// Signature pour un paquet sans information de relogement.
	static const KUInt8	kNOS1CompatibleSignature[8];
	
	/// Signature pour un paquet qui ne fonctionne que sur NewtonOS 2.x.
	static const KUInt8 kNOS1IncompatibleSignature[8];

	///
	/// Drapeaux pour SPartEntry.
	/// Les autres bits sont r�serv�s et doivent �tre � z�ro.
	///
	enum {
		/// La partie est un protocole.
		kPartProtocolPart	= 0x00000000,
		
		/// La partie est compos�e d'objets NewtonScript (au format Pkg)
		kPartNOSPart		= 0x00000001,
		
		/// La partie est compos�e de donn�es brutes.
		kPartRawPart		= 0x00000002,
		
		/// Masque pour le type de partie.
		kPartTypeMask		= 0x00000003,
		
		/// Uniquement pour les protocoles: pr�cise que le protocole doit �tre
		/// enregistr� lorsque le paquet est activ�.
		kPartAutoLoadFlag	= 0x00000010,
		
		/// Uniquement pour les protocoles: pr�cise que le protocole doit �tre
		/// d�senregistr� lorsque le paquet est d�sactiv�. Normalement � un
		/// lorsque kPartAutoLoadFlag est � un.
		kPartAutoRemoveFlag	= 0x00000020,
		
		/// Sp�cifie que le gestionnaire dans le syst�me correspondant au type
		/// de la partie doit �tre appel�. Normalement � un sauf si les
		/// sp�cifications pour le type de partie indiquent le contraire.
		kPartNotifyFlag		= 0x00000080,
		
		/// Sp�cifie que la partie doit �tre copi�e en m�moire avant d'�tre
		/// activ�e. Ne doit �tre utilis� que pour les parties (normalement des
		/// protocoles) qui ne tol�rent pas le m�canisme de gestion de m�moire
		/// virtuelle.
		kPartAutoCopyFlag	= 0x00000100
	};
	
	///
	/// Types des parties.
	///
	enum {
		kFormPart	= FOUR_CHAR_CODE('form'),	///< Application
		kBookPart	= FOUR_CHAR_CODE('book'),	///< Livre
		kAutoPart	= FOUR_CHAR_CODE('auto'),	///< Applications invisibles
		kFontPart	= FOUR_CHAR_CODE('font'),	///< Polices suppl�mentaires
		kDictPart	= FOUR_CHAR_CODE('dict'),	///< Dictionnaires
												///< suppl�mentaires
		kStorePart	= FOUR_CHAR_CODE('soup')	///< Magasin avec des soupes en
												///< lecture seule.
	};
	
	///
	/// Identifiants des paquets (non utilis� par NTK, probablement non
	/// utilis�s par le syst�me).
	///
	enum {
		kDefaultID		= FOUR_CHAR_CODE('xxxx'),	///< Identifiant par d�faut.
		kSystemUpdateID	= FOUR_CHAR_CODE('ptch'),	///< Identifiant utilis� par
													///< les rustines.
		kSoundCodecID	= FOUR_CHAR_CODE('codt')	///< Identifiant utilis� par
													///< les Codec.
	};
	
	enum {
		// La taille maximale autoris�e par NTK est 28 caract�res.
		// (apparemment, NewtonOS en autorise 31).
		kPackageNameMaxLength	= 28,	///< Taille maximale, en caract�res,
										///< du nom.
		kCopyrightMaxLength		= 63	///< Taille maximale, en caract�res,
										///< de la cha�ne avec le copyright.
	};
	
	///
	/// Les structures 'InfoRef' permettent de faire r�f�rence � des donn�es de
	/// taille variable dans la partie donn�es du catalogue.
	///
	struct SInfoRef {
		KUInt16		fOffset;	///< D�calage depuis le d�but de la zone des
								///< donn�es.
		KUInt16		fLength;	///< Taille des donn�es (en octets).
	};
	
	///
	/// Catalogue des paquets.
	///
	struct SPackageDirectory {
		KUInt8		fSignature[8];	///< Signature (format du paquet)
		KUInt32		fPackageID;		///< Type (e.g. kDefaultID).
		KUInt32		fFlags;			///< Drapeaux (e.g. kDirAutoRemoveFlag).
		KUInt32		fVersion;		///< Nombre arbitraire pour la version.
									///< Plus grand signifie plus r�cent
									///< pour le syst�me.
		SInfoRef	fCopyright;		///< Cha�ne UCS-2 avec la notice copyright
									///< (�ventuellement vide)
		SInfoRef	fName;			///< Cha�ne UCS-2 avec le nom du paquet.
									///< C'est normalement un identifiant
									///< unique avec en pr�fixe, la signature
									///< du d�veloppeur.
		KUInt32		fSize;			///< Taille du paquet en octets, y compris
									///< le catalogue.
		KUInt32		fCreationDate;	///< Date de cr�ation, en secondes depuis
									///< le 1/01/1904
		KUInt32		fReserved1;		///< R�serv� (doit �tre 0).
		KUInt32		fReserved2;		///< R�serv� (doit �tre 0).
		KUInt32		fDirectorySize;	///< Taille du catalogue avec les entr�es
									///< et les donn�es.
		KUInt32		fNumParts;		///< Nombre de parties dans le paquet.
		// SPartEntry fParts[fNumParts]
		// KUInt8 fVariableLengthData[];
	};
	
	///
	/// Apr�s SPackageDirectory se trouve, pour chaque partie, une structure de
	/// ce type. On fait parfois r�f�rence aux parties par leur num�ro,
	/// celui-ci est l'indice dans le catalogue commen�ant par 0.
	///
	struct SPartEntry {
		KUInt32		fOffset;		///< D�calage, par rapport � la partie
									///< donn�es (i.e. apr�s
									///< le catalogue) des donn�es de cette
									///< partie. Multiple
									///< de 4, g�n�ralement 0 pour la premi�re
									///< partie.
		KUInt32		fSize;			///< Taille en octets.
		KUInt32		fSize2;			///< Encore la taille, en octets (copie de
									///< fSize).
		KUInt32		fType;			///< Type de la partie.
		KUInt32		fReserved1;		///< R�serv� (doit �tre 0).
		KUInt32		fFlags;			///< Drapeaux (e.g. kPartProtocolPart).
		SInfoRef	fInfo;			///< Bloc de donn�es pass� au gestionnaire
									///< de parties lorsque la partie est
									///< activ�e. Le contenu est sp�cifi� par
									///< le type de partie.
		KUInt32		fReserved2;		///< R�serv� (doit �tre 0).
	};

	///
	/// Constructeur par d�faut.
	/// Cr�e un paquet vide.
	///
	TDCLPackage( void );

	///
	/// Constructeur � partir d'un fichier.
	/// Ouvre le fichier, le lit enti�rement, le referme et
	/// analyse le paquet.
	/// Si le fichier �tait ouvert, il est restitu� dans l'�tat dans lequel
	/// il �tait.
	///
	/// \param inFile	fichier consid�r�.
	/// \throws DCLException si le fichier n'est pas un paquet.
	///
	TDCLPackage( TDCLFile* inFile );

	///
	/// Constructeur � partir d'un flux. Lit le paquet enti�rement.
	///
	/// \param inStream	flux consid�r�.
	/// \throws DCLException si le fichier n'est pas un paquet.
	///
	TDCLPackage( TDCLStream* inStream );

	///
	/// Constructeur � partir d'une m�moire tampon.
	/// La m�moire tampon est copi�e.
	/// Analyse le catalogue et copie les donn�es des parties.
	///
	/// \param inBuffer	m�moire tampon
	/// \param inSize	taille de la m�moire tampon.
	/// \throws DCLException si la m�moire tampon n'est pas un paquet.
	///
	TDCLPackage( const KUInt8* inBuffer, KUInt32 inSize );

	///
	/// Destructeur.
	/// Supprime toutes les donn�es qui tra�nent.
	///
	~TDCLPackage( void );

	///
	/// Rapide test pour savoir si le fichier consid�r� est un
	/// paquet ou non.
	/// Ouvre le fichier si il �tait ferm�, lit 8 octets puis le referme.
	/// Si le fichier �tait ouvert, il est restitu� dans l'�tat dans lequel
	/// il �tait.
	///
	/// \param inFile	fichier � consid�rer.
	/// \return \c true si le fichier semble �tre un paquet, \c false sinon.
	///
	static Boolean IsPackage( TDCLFile* inFile );

	///
	/// Compile et �crit le paquet sur un flux.
	///
	/// \param inOutStream	flux de sortie.
	///
	void	WriteToStream( TDCLStream* inOutStream ) const;
	
	///
	/// Accesseur sur la compatibilit� du paquet.
	///
	/// \return \c true si le paquet est compatible avec NOS 1.x.
	///
	inline Boolean		IsNOS1Compatible( void ) const
		{
			return mNOS1Compatible;
		}

	///
	/// S�lecteur sur la version du paquet.
	///
	/// \param inNOS1Compatible		si le paquet est compatible NOS 1.x
	///
	inline void			SetNOS1Compatible( Boolean inNOS1Compatible )
		{
			mNOS1Compatible = inNOS1Compatible;
		}

	///
	/// Accesseur sur l'identifiant du paquet.
	///
	/// \return l'identifiant du paquet.
	///
	inline KUInt32		GetPackageID( void ) const
		{
			return mPackageID;
		}

	///
	/// S�lecteur sur l'identifiant du paquet.
	///
	/// \param inID					identifiant du paquet.
	///
	inline void			SetPackageID( KUInt32 inID )
		{
			mPackageID = inID;
		}

	///
	/// Accesseur sur les drapeaux du paquet.
	///
	/// \return les drapeaux du paquet.
	///
	inline KUInt32		GetPackageFlags( void ) const
		{
			return mPackageFlags;
		}

	///
	/// S�lecteur sur les drapeaux du paquet.
	///
	/// \param inFlags				drapeaux du paquet.
	///
	inline void			SetPackageFlags( KUInt32 inFlags )
		{
			mPackageFlags = inFlags;
		}

	///
	/// Accesseur sur le drapeau kDirAutoRemoveFlag
	///
	/// \return \c true si le drapeau kDirAutoRemoveFlag est � un.
	///
	inline Boolean		GetAutoRemove( void ) const
		{
			return ((GetPackageFlags() & kDirAutoRemoveFlag) != 0);
		}

	///
	/// S�lecteur sur le drapeau kDirAutoRemoveFlag
	///
	/// \param inAutoRemove		nouvelle valeur du drapeau
	///
	inline void			SetAutoRemove( Boolean inAutoRemove )
		{
			SetPackageFlags(
					inAutoRemove ?
						GetPackageFlags() | kDirAutoRemoveFlag
						: GetPackageFlags() &~ kDirAutoRemoveFlag );
		}

	///
	/// Accesseur sur le drapeau kDirCopyProtectFlag
	///
	/// \return \c true si le drapeau kDirCopyProtectFlag est � un.
	///
	inline Boolean		GetCopyProtect( void ) const
		{
			return ((GetPackageFlags() & kDirCopyProtectFlag) != 0);
		}

	///
	/// S�lecteur sur le drapeau kDirCopyProtectFlag
	///
	/// \param inCopyProtect	nouvelle valeur du drapeau
	///
	inline void			SetCopyProtect( Boolean inCopyProtect )
		{
			SetPackageFlags(
					inCopyProtect ?
						GetPackageFlags() | kDirCopyProtectFlag
						: GetPackageFlags() &~ kDirCopyProtectFlag );
		}

	///
	/// Accesseur sur le drapeau kDirNoCompressionFlag
	///
	/// \return \c true si le drapeau kDirNoCompressionFlag est � un.
	///
	inline Boolean		GetNoCompression( void ) const
		{
			return ((GetPackageFlags() & kDirNoCompressionFlag) != 0);
		}

	///
	/// S�lecteur sur le drapeau kDirNoCompressionFlag.
	/// Si mis � un, change kDirUseFasterCompressionFlag � z�ro.
	///
	/// \param inNoCompression	nouvelle valeur du drapeau
	///
	inline void			SetNoCompression( Boolean inNoCompression )
		{
			SetPackageFlags(
					inNoCompression ?
						(GetPackageFlags() &~ kDirUseFasterCompressionFlag)
							| kDirNoCompressionFlag
						: GetPackageFlags() &~ kDirNoCompressionFlag );
		}

	///
	/// Accesseur sur le drapeau kDirUseFasterCompressionFlag
	///
	/// \return \c true si le drapeau kDirUseFasterCompressionFlag est � un.
	///
	inline Boolean		GetUseFasterCompression( void ) const
		{
			return ((GetPackageFlags() & kDirUseFasterCompressionFlag) != 0);
		}

	///
	/// S�lecteur sur le drapeau kDirUseFasterCompressionFlag.
	/// Si celui-ci est mis � \c true, le paquet n'est plus compatible NOS 1.x.
	///
	/// \param inUseFasterCompression	nouvelle valeur du drapeau
	///
	inline void			SetUseFasterCompression(
											Boolean inUseFasterCompression )
		{
			if (inUseFasterCompression)
			{
				mNOS1Compatible = false;
				SetPackageFlags(
						GetPackageFlags() | kDirUseFasterCompressionFlag );
			} else {
				SetPackageFlags(
						GetPackageFlags() &~ kDirUseFasterCompressionFlag );
			}
		}

	///
	/// Accesseur sur la version du paquet.
	///
	/// \return la version du paquet.
	///
	inline KUInt32		GetPackageVersion( void ) const
		{
			return mVersion;
		}

	///
	/// S�lecteur sur la version du paquet.
	///
	/// \param inVersion			version du paquet.
	///
	inline void			SetPackageVersion( KUInt32 inVersion )
		{
			mVersion = inVersion;
		}

	///
	/// Accesseur sur la date de cr�ation du paquet.
	///
	/// \return la date de cr�ation du paquet (secondes depuis le 1/01/1904).
	///
	inline KUInt32		GetCreationDate( void ) const
		{
			return mCreationDate;
		}

	///
	/// S�lecteur sur la date de cr�ation du paquet.
	///
	/// \param inCreationDate		date de cr�ation
	///								(secondes depuis le 1/01/1904)
	///
	inline void			SetCreationDate( KUInt32 inCreationDate )
		{
			mCreationDate = inCreationDate;
		}

	///
	/// Accesseur sur la cha�ne de copyright.
	///
	/// \return la cha�ne de copyright (UCS-2, grand boutien).
	///
	inline const KUInt16*	GetCopyrightString( void ) const
		{
			return mCopyrightStr;
		}

	///
	/// S�lecteur sur la cha�ne de copyright (UCS-2, grand boutien).
	///
	/// \param inCopyrightStr	nouvelle cha�ne de Copyright (copi�e).
	///
	void			SetCopyrightString( const KUInt16* inCopyrightStr );

	///
	/// S�lecteur sur la cha�ne de copyright (Latin-1).
	///
	/// \param inCopyrightStr	nouvelle cha�ne de Copyright (copi�e).
	///
	void			SetCopyrightString( const char* inCopyrightStr );

	///
	/// Accesseur sur le nom du paquet.
	///
	/// \return le nom (UCS-2, grand boutien)
	///
	inline const KUInt16*	GetPackageName( void ) const
		{
			return mNameStr;
		}

	///
	/// S�lecteur sur le nom du paquet (UCS-2, grand boutien).
	///
	/// \param inNameStr	nouveau nom (copi�).
	///
	void			SetPackageName( const KUInt16* inNameStr );

	///
	/// S�lecteur sur le nom du paquet (Latin-1)
	///
	/// \param inNameStr	nouveau nom (copi�).
	///
	void			SetPackageName( const char* inNameStr );

	///
	/// Accesseur sur le nombre de parties dans le paquet.
	///
	/// \return le nombre de parties
	///
	inline KUInt32		GetNumParts( void ) const
		{
			return mNumParts;
		}
	
	///
	/// Accesseur sur le type de la n-i�me partie.
	///
	/// \param inPartIndex	indice de la partie consid�r�e.
	///
	inline KUInt32		GetPartType( KUInt32 inPartIndex ) const
		{
			KASSERT( inPartIndex < mNumParts );
			return mParts[inPartIndex].fType;
		}

	///
	/// S�lecteur sur le type de la n-i�me partie.
	///
	/// \param inPartIndex	indice de la partie consid�r�e.
	/// \param inPartType	nouveau type de la partie.
	///
	inline void			SetPartType( KUInt32 inPartIndex, KUInt32 inPartType )
		{
			KASSERT( inPartIndex < mNumParts );
			mParts[inPartIndex].fType = inPartType;
		}
	
	///
	/// Accesseur sur les drapeaux de la n-i�me partie.
	///
	/// \param inPartIndex	indice de la partie consid�r�e.
	///
	inline KUInt32		GetPartFlags( KUInt32 inPartIndex ) const
		{
			KASSERT( inPartIndex < mNumParts );
			return mParts[inPartIndex].fFlags;
		}

	///
	/// S�lecteur sur les drapeaux de la n-i�me partie.
	///
	/// \param inPartIndex	indice de la partie consid�r�e.
	/// \param inPartFlags	nouveaux drapeaux de la partie.
	///
	inline void			SetPartFlags(
							KUInt32 inPartIndex,
							KUInt32 inPartFlags )
		{
			KASSERT( inPartIndex < mNumParts );
			mParts[inPartIndex].fFlags = inPartFlags;
		}

	///
	/// Accesseur sur les informations pour le gestionnaire de la n-i�me
	/// partie.
	///
	/// \param inPartIndex	indice de la partie consid�r�e.
	/// \param outSize		la taille des informations.
	/// \return les informations pour le gestionnaire.
	///
	inline const KUInt8*	GetPartHandlerInfo(
									KUInt32 inPartIndex,
									KUInt32* outSize ) const
		{
			KASSERT( inPartIndex < mNumParts );
			// Ici, les donn�es doivent �tre en m�moire (elles ne sont sur
			// le disque que pendant l'analyse du paquet)
			KASSERT( mParts[inPartIndex].fInfoData != nil );
			*outSize = mParts[inPartIndex].fInfoSize;
			return mParts[inPartIndex].fInfoData;
		}

	///
	/// Accesseur sur la n-i�me partie. [const]
	///
	/// \param inPartIndex	indice de la partie consid�r�e.
	/// \return la n-i�me partie.
	///
	inline const TDCLPkgPart*	GetPart( KUInt32 inPartIndex ) const
		{
			KASSERT( inPartIndex < mNumParts );
			// Ici, les donn�es doivent �tre en m�moire (elles ne sont sur
			// le disque que pendant l'analyse du paquet)
			KASSERT( mParts[inPartIndex].fPart != nil );
			return mParts[inPartIndex].fPart;
		}

	///
	/// Accesseur sur la n-i�me partie.
	///
	/// \param inPartIndex	indice de la partie consid�r�e.
	/// \return la n-i�me partie.
	///
	inline TDCLPkgPart*		GetPart( KUInt32 inPartIndex )
		{
			KASSERT( inPartIndex < mNumParts );
			// Ici, les donn�es doivent �tre en m�moire (elles ne sont sur
			// le disque que pendant l'analyse du paquet)
			KASSERT( mParts[inPartIndex].fPart != nil );
			return mParts[inPartIndex].fPart;
		}

	///
	/// Ajoute une partie � la fin du paquet.
	/// Les donn�es pour le gestionnaire sont d�termin�es par d�faut.
	/// La partie n'est pas dupliqu�e mais sera supprim�e par le destructeur.
	///
	/// \param inType		type de la partie.
	/// \param inFlags		drapeaux pour la partie.
	/// \param inPart		partie (non copi�e, sera supprim�e par le
	///						destructeur).
	/// \return l'indice de la partie.
	///
	KUInt32 				AddPart(
								KUInt32 inType,
								KUInt32 inFlags,
								TDCLPkgPart* inPart );

	///
	/// Ajoute une partie � la fin du paquet.
	/// La partie n'est pas dupliqu�e mais sera supprim�e par le destructeur.
	///
	/// \param inType		type de la partie.
	/// \param inFlags		drapeaux pour la partie.
	/// \param inInfoSize	taille des informations pour le gestionnaire.
	/// \param inInfoData	donn�es pour le gestionnaire (copi�es).
	/// \param inPart		partie (non copi�e, sera supprim�e par le
	///						destructeur).
	/// \return l'indice de la partie.
	///
	KUInt32 				AddPart(
								KUInt32 inType,
								KUInt32 inFlags,
								KUInt32 inInfoSize,
								const KUInt8* inInfoData,
								TDCLPkgPart* inPart );

	///
	/// Supprime une partie du paquet.
	///
	/// \param inPartIndex	indice de la partie � supprimer. 
	///
	void 				RemovePart( KUInt32 inPartIndex );

private:
	///
	/// Donn�es par d�faut pour le gestionnaire (en fait, une cha�ne qui
	/// indique la provenance du paquet).
	///
	static const char* const kDefaultHandlerInfoData;

	///
	/// Structure pour les donn�es de localisation des parties dans le paquet.
	///
	struct SPartLocation {
		KUInt32		fInfoOffset;	///< D�calage des donn�es pour le
									///< gestionnaire.
		KUInt32		fDataOffset;	///< D�calage des donn�es de la partie.
		KUInt32		fDataSize;		///< Taille des donn�es de la partie.
	};

	///
	/// Structure pour les donn�es conserv�es sur les parties.
	///
	struct SPartData {
		KUInt32			fType;		///< Type de la partie.
		KUInt32			fFlags;		///< Drapeaux de la partie.
		KUInt32			fInfoSize;	///< Taille des donn�es pour le
									///< gestionnaire.
		KUInt8*			fInfoData;	///< Donn�es pour le gestionnaire.
		TDCLPkgPart*	fPart;		///< Donn�es de la partie.
	};
		
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLPackage( const TDCLPackage& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TDCLPackage& operator = ( const TDCLPackage& inCopy );
	
	///
	/// Lecture du paquet � partir d'un flux.
	/// Lance une exception en cas de probl�me.
	///
	/// \param inStream		flux � lire.
	///
	void			ReadPackage( TDCLStream* inStream );

	/// \name Variables
	Boolean			mNOS1Compatible;///< Si le paquet est compatible 1.x.
	KUInt32			mPackageID;		///< ID (e.g. kDefaultID).
	KUInt32			mPackageFlags;	///< Drapeaux (e.g. kDirAutoRemoveFlag).
	KUInt32			mVersion;		///< Nombre arbitraire pour la version.
									///< Plus grand signifie plus r�cent pour
									///< le syst�me.
	KUInt32			mCreationDate;	///< Date de cr�ation, en secondes depuis
									///< le 1/01/1904
	KUInt16*		mCopyrightStr;	///< Cha�ne pour le copyright
	KUInt16*		mNameStr;		///< Cha�ne pour le nom.
	KUInt32			mNumParts;		///< Nombre de parties dans le paquet.
	SPartData*		mParts;			///< Parties.
};

#endif
		// _TDCLPACKAGE_H

// ===================================================================== //
// When someone says "I want a programming language in which I need only //
// say what I wish done," give him a lollipop.                           //
// ===================================================================== //
