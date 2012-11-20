// ==============================
// Fichier:			TDCLCommToolBox.cp
// Projet:			Desktop Connection Library
//
// Cr�� le:			20/01/2000
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
// The Original Code is TDCLCommToolBox.cp.
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
// $Id: TDCLCommToolBox.h,v 1.6 2004/11/24 18:11:02 paul Exp $
// ===========

#ifndef __TDCLCOMMTOOLBOX__
#define __TDCLCOMMTOOLBOX__

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/TDCLCommLayer.h>

// V�rification de la cible.
#if !TARGET_OS_MACOS
	#error "The Communication Toolbox is only available on MacOS < X"
#endif

// MacOS
#ifdef __MWERKS__
	#pragma	warn_resultnotused	off
#endif

#include <Connections.h>

#ifdef __MWERKS__
	#pragma	warn_resultnotused	on
#endif

// DCL
#include <DCL/Communication_Layers/TDCLPipe.h>

#warning TDCLCommToolBox compiles but is no longer functional

class IDCLThreads;

///
/// Classe pour une couche de communication utilisant la Communication ToolBox.
/// Cette classe est initialis�e � partir d'un nom d'outil CTB et d'une cha�ne
/// de configuration. Le constructeur a aussi besoin de l'interface parce qu'il
/// faut appeler Yield de temps en temps pour les outils CTB un peu bogu�s.
///
/// \author	Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.6 $
///
/// \test	aucun test d�fini.
///
class TDCLCommToolBox
	:
		public TDCLCommLayer
{
public:
	///
	/// Constructeur public.
	/// Le nombre de connexions et la temporisation pour cette couche de
	/// communication sont d�finies comme des constantes.
	/// Les sous-classes devront probablement utiliser plut�t l'autre
	/// constructeur.
	///
	/// \param inToolName		nom de l'outil de communication � utiliser
	/// \param inConfigString	cha�ne de configuration pour l'outil de
	///							communication.
	/// \param inThreadsIntf	interface pour les processus l�gers
	/// \param inMaxPipeCount	nombre de connexions simultan�es maximum.
	/// \param inTimeout		d�lai de temporisation.
	///
	TDCLCommToolBox(
				const char* inToolName,
				const char* inConfigString,
				IDCLThreads* inThreadsIntf,
				KUInt32	inMaxPipeCount = kDefaultPipeCount,
				long inTimeout = kDefaultTimeout
			);

	///
	/// Destructeur.
	///
	virtual				~TDCLCommToolBox( void );
	
protected:
	///
	/// Commence � �couter.
	///
	virtual	void		DoStartListening( void );

	///
	/// Arr�te d'�couter, i.e. arr�te d'accepter les requ�tes de connexions.
	///
	virtual	void		DoStopListening( void );

	// Returns true if there is a present connection request (in which case
	// Accept will return a pipe connected to the client).
//	virtual	Boolean		ConnectionRequestPresent( void );

	///
	/// Retourne un objet connexion repr�sentant le canal de communication avec
	/// le client ou \c nil s'il n'y a pas de requ�te de connexion pr�sente.
	/// C'est un objet cr�� avec \c new. L'appelant devra le supprimer.
	///
	/// \return un nouvel objet TDCLPipe cr�� avec \c new repr�sentant la
	///			connexion ou \c nil.
	///
	virtual	TDCLPipe*	Accept( void );
	
	///
	/// Refuse la premi�re requ�te de connexion.
	/// Ne fait rien si aucune connexion n'est pr�sente.
	///
	virtual	void		Refuse( void );

	///
	/// M�thode appel�e pour perdre du temps.
	///
	/// Elle est appel�e (par l'impl�mentation par d�faut de TDCLPipe::Idle par
	/// exemple) � intervalles r�guliers.
	///
	/// Appelle CMIdle avec le ConnHandle et mInterface->Yield.
	///
	virtual	void		Idle( void );

	///
	/// Change la temporisation pour les nouvelles connexions.
	/// La temporisation est exprim�e au format TDCLCommLayer.
	///
	/// \param inTimeout	nouvelle temporisation au format \c TDCLCommLayer
	///
	virtual	void		SetTimeout( long inTimeout );

	///
	/// R�cup�re la temporisation utilis�e pour les nouvelles connexions.
	/// La temporisation est exprim�e au format TDCLCommLayer.
	///
	/// \return la temporisation au format \c TDCLCommLayer
	///
	virtual	long		GetTimeout( void );

	///
	/// M�thode appel�e par TDCLPipe::Disconnect() pour indiquer qu'une
	/// connexion a �t� ferm�e. D�cr�mente le compteur des connexions ouvertes.
	/// R�cup�re l'indice de la connexion et met la r�f�rence ConnHandle
	/// correspondante � \c nil.
	///
	/// \param inPipe	connexion qui a �t� ferm�e
	///
	virtual	void		Disconnected( TDCLPipe* inPipe );

	///
	/// D�termine si les outils de communications CTB sont disponibles.
	///
	/// \return \c true si la CTB est disponible, \c false sinon.
	///
	static	Boolean		IsAvailable( void );

	///
	/// Convert a timeout from seconds (or one of the constants) to CTB.
	///
	/// \param inSecsTimeout	d�lai de temporisation en secondes.
	/// \return un temps au format CTB.
	///
	static	long		ConvertTimeoutFromSeconds( long inSecsTimeout );

	///
	/// Convert a timeout from CTB to seconds.
	///
	/// \param inCTBTimeout	d�lai de temporisation au format CTB
	/// \return un nombre de secondes.
	///
	static	long		ConvertTimeoutToSeconds( long inCTBTimeout );

protected:
	///
	/// Constructor and initializer for sub-classes.
	/// This constructor does not call Init. It's for base classes that want to
	/// process their configuration strings and call Init later.
	///
	TDCLCommToolBox(
			IDCLThreads* inThreadsIntf,
			KUInt32	inMaxPipeCount = kDefaultPipeCount,
			long	inTimeout = kDefaultTimeout
		);

	///
	/// Initialize all the layer, including the tool and the table of 
	/// connections.
	///
	void		Init( const char* inToolName, const char* inConfigString );

#ifdef MPW_COMPILERS_WORKAROUND
	// Sounds like a bug in MrCpp 5.0.0d3c1 and SCpp 8.9.0d3e1
	// It complains in TDCLFoo::IsAvailable() that this method isn't
	// accessible. If I remove static keywords, it no longer complains.
public:
#endif

	///
	/// D�termine si un outil de communication est disponible.
	///
	/// \param inToolName	nom de l'outil � tester.
	/// \return \c true si l'outil de communication est disponible, \c false
	///			sinon.
	///
	static	Boolean		IsAvailable( const char* inToolName );
	
private:
	///
	/// Classe pour une connexion.
	///
	class TCTBPipe
		:
			public TDCLPipe
	{
	public:
		friend class TDCLCommToolBox;
		
		// Destructor closes the connection if it wasn't closed yet.
		virtual				~TCTBPipe( void );
	
		///
		/// Lit des octets.
		///
		/// \param outBuffer	m�moire tampon pour les octets lus.
		/// \param ioCount		nombre d'octets � lire en entr�e, lus en
		///						sortie. Cette valeur est mise � jour avant que
		///						l'exception ne soit lanc�e si un probl�me est
		///						survenu.
		/// \throws TDCLException	si un probl�me est survenu (autre que EOF)
		///
		virtual	void		DoRead( void* outBuffer, KUInt32* ioCount );

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
		virtual	void		DoWrite( const void* inBuffer, KUInt32* ioCount );
		
		///
		/// D�termine si des octets sont disponibles dans la m�moire tampon
		/// d'entr�e.
		///
		/// \return \c true s'il y a des octets disponibles, \c false sinon.
		///
		virtual	Boolean		BytesAvailable( void );

		// Flush does not work with CTB. So we use default implementation.
		
		///
		/// D�connecte le canal de communication avec le client.
		///
		/// L'impl�mentation par d�faut appelle la m�thode
		/// Disconnected( TDCLPipe* ) de TDCLCommLayer.
		///
		/// \remark	une fois que cette m�thode est appel�e, l'objet connexion
		///			est inutilisable. Il peut �tre supprim� par l'appelant �
		///			tout instant.
		///
		virtual	void		Disconnect( void );
		
		///
		/// M�thode appel�e pour indiquer que c'est le moment de perdre un peu
		/// de temps.
		///
		/// Certaines couches de communication ont besoin de ceci.
		/// L'impl�mentation par d�faut appelle la m�thode Idle( void ) de la
		/// couche de communication.
		///
		virtual	void		Idle( void );

		///
		/// R�cup�re la temporisation pour cette connexion.
		///
		/// \return la temporisation au format \c TDCLCommLayer.
		///
		virtual	long		GetTimeout( void );

		///
		/// Change la temporisation pour cette connexion.
		///
		/// \param inTimeout	temporisation au format \c TDCLCommLayer.
		///
		virtual	void		SetTimeout( long inTimeout );

	protected:
		///
		/// Constructeur prot�g�.
		///
		/// \param inCommLayer	r�f�rence sur la couche de communication.
		/// \param inConnHandle	r�f�rence sur la connexion.
		/// \param inTimeout	d�lai de temporisation (format CTB).
		// You're not supposed to create TCTBPipes yourself.
		TCTBPipe(
					TDCLCommToolBox*	inCommLayer,
					ConnHandle			inConnHandle,
					long				inTimeout
				);

		///
		/// Accesseur sur la r�f�rence CTB de la connexion.
		///
		/// \return la r�f�rence CTB de la connexion.
		///
		inline	ConnHandle	GetConnHandle( void )
			{
				return mConnection;
			}

	private:
		long				mTimeout;		///< timeout in ticks, suitable for
											///< CTB functions.
		ConnHandle			mConnection;	///< our connection handle.
	};
	
	///
	/// Create a new connection handle from the tool proc ID and the tool
	/// config string.
	///
	ConnHandle			GetNewConnHandle( void );

	///
	/// Initialize the CTB
	///
	static	void		InitCTB( void );

	///
	/// Start listening on a new ConnHandle (stored into mCurrentConnHandle).
	/// Also looks for a new nextIndex if current isn't fine.
	/// Do nothing if mCurrentConnHandle is not nil.
	///
	void				DoListen( void );

	enum {
		kCTBDefaultPipeCount	=	10,
		kCTBDefaultTimeout		=	1800,	///< 30 secondes.
		kCTBNoTimeout			=	-1
	};
	
	enum ECTBState {
		kUninitialized,		///< Startup state
		kNotAvailable,		///< CTB isn't available
		kInitialized		///< CTB is available and initialized.
	};

	short				mToolProcID;		///< ProcID associated with the
											///< tool name.
	char*				mToolConfig;		///< Tool configuration string
											///< (copied by the Init method).
	ConnHandle			mCurrentConnHandle;	///< Current connection handle
											///< (listening)
	KUInt32				mCurrentPipeCount;	///< Number of pipes currently
											///< instantiated.
	long				mTimeout;			///< Timeout in CTB format (ticks)
	IDCLThreads*		mThreadsIntf;		///< Required to Yield a little
											///< bit.
	static ECTBState	gCTBState;			///< Whether the CTB is
											///< initialized/available or not.
	Boolean				mListening;			///< Whether we are listening or
											///< not.
};

#endif
		// __TDCLCOMMTOOLBOX__

// ========================================== //
// The first version always gets thrown away. //
// ========================================== //