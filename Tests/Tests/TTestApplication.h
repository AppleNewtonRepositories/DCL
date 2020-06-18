//==============================
// Fichier:			TTestApplication.h
// Projet:			(Desktop Connection Library)
// Ecrit par:		Paul Guyot (pguyot@kallisys.net)
// 
// Cr�� le:			17/6/2003
// Tabulation:		4 espaces
// 
// Copyright:		� 2003 by Paul Guyot.
// 					Tous droits r�serv�s pour tous pays.
// Licence:			Licence R�flexive Kallisys
// 					http://www.kallisys.org/reflexive/
// ===========
// $Id: TTestApplication.h,v 1.3 2003/09/17 10:43:48 paul Exp $
// ===========

#ifndef _TTESTAPPLICATION_H
#define _TTESTAPPLICATION_H

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Interfaces/Common/TDCLLogApplication.h>

///
/// Classe pour une application qui raconte sa vie sur stdout.
/// D�rive de TDCLLogApplication.
/// Remarque: stdout est ouvert avec un ::fopen.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.3 $
///
/// \test	aucun test d�fini.
///
class TTestApplication
	:
		public TDCLLogApplication
{
public:
	///
	/// Constructeur � partir d'une interface pour les processus l�gers.
	/// Les informations sont envoy�es sur stdout.
	///
	/// \param inThreadsIntf	interface pour les processus l�gers.
	///
	TTestApplication( IDCLThreads* inThreadsIntf );

	///
	/// Destructeur.
	///
	virtual ~TTestApplication( void );

	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e dans
	/// le processus l�ger d'un/du serveur.
	///
	/// \param inServer		serveur qui s'est vautr�.
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void 	HandleServerException(
							TDCLServer* inServer,
							TDCLException* inException );

	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e dans
	/// le processus l�ger d'une/de la couche de communication.
	///
	/// \param inCommLayer	couche qui s'est vautr�e.
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void 	HandleCommLayerException(
							TDCLCommLayer* inCommLayer,
							TDCLException* inException );

	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e dans
	/// le processus l�ger d'un/du lien.
	///
	/// \param inLink		lien qui s'est vautr�.
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void 	HandleLinkException(
							TDCLLink* inLink,
							TDCLException* inException );


protected:
	///
	/// M�thode appel�e lorsqu'une exception n'est pas intercept�e dans
	/// le processus l�ger. Cette m�thode est appel�e dans ce processus l�ger
	/// qui se termine lorsque la m�thode retourne.
	///
	/// \param inException	l'exception si c'est une TDCLException,
	///			\c nil sinon.
	///
	virtual void 	HandleException( TDCLException* inException );

	///
	/// M�thode appel�e lorsqu'une exception (quelconque) est arriv�e.
	/// Par d�faut, ne fait rien.
	///
	virtual void 	ExceptionOccurred( void );

private:
	///
	/// Constructeur par copie volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TTestApplication( const TTestApplication& inCopy );

	///
	/// Op�rateur d'assignation volontairement indisponible.
	///
	/// \param inCopy		objet � copier
	///
	TTestApplication& operator = ( const TTestApplication& inCopy );

	///
	/// Retourne l'abstraction pour les fichiers.
	/// Cette m�thode est appel�e la premi�re fois que
	/// GetFilesIntf est appel�e.
	///
	/// \return une abstraction pour utiliser les fichiers.
	///
	virtual IDCLFiles*		CreateFilesIntf( void );
	
	///
	/// Retourne l'abstraction pour les processus l�gers.
	/// Cette m�thode est appel�e la premi�re fois que
	/// GetThreadsIntf est appel�e.
	///
	/// \return une abstraction pour les processus l�gers.
	///
	virtual IDCLThreads*	CreateThreadsIntf( void );

	/// \name Variables

	IDCLThreads*				mThreadsIntf;	///< Interface pour les processus l�gers.
};

#endif
		// _TTESTAPPLICATION_H

// ======================================================================== //
// Real programmers don't bring brown-bag lunches.  If the vending machine  //
// doesn't sell it, they don't eat it.  Vending machines don't sell quiche. //
// ======================================================================== //
