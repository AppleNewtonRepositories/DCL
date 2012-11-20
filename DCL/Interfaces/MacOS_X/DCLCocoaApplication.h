// ==============================
// Fichier:			DCLCocoaApplication.h
// Projet:			Desktop Connection Library
//
// Cr�� le:			30/3/2003
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
// The Original Code is DCLCocoaApplication.h.
//
// The Initial Developers of the Original Code are Paul Guyot, Michael Vac�k
// and Nicolas Zinovieff. Portions created by the Initial Developers are
// Copyright (C) 2003-2004 the Initial Developers. All Rights Reserved.
//
// Contributor(s):
//   Paul Guyot <pguyot@kallisys.net> (original author)
//   Michael Vac�k <mici@metastasis.net> (original author)
//   Nicolas Zinovieff <krugazor@poulet.org> (original author)
//
// ***** END LICENSE BLOCK *****
// ===========
// $Id: DCLCocoaApplication.h,v 1.6 2004/11/24 14:09:01 paul Exp $
// ===========

#ifndef _DCLCOCOAAPPLICATION_H
#define _DCLCOCOAAPPLICATION_H

#import <DCL/Headers/DCLDefinitions.h>
#import <DCL/Interfaces/MacOS_X/IDCLObjCApplication.h>

#ifdef __MWERKS__
	#pragma	warn_implicitconv	off
	#pragma	warn_extracomma		off
#endif

#import <Cocoa/Cocoa.h>

#ifdef __MWERKS__
	#pragma	warn_implicitconv	reset
	#pragma	warn_extracomma		reset
#endif

// Pr�-d�clarations.
class TDCLObjCApplication;
class IDCLFiles;
class IDCLThreads;

///
/// Classe pour une application Cocoa utilisant la DCL.
///
/// Cet objet g�re les �v�nements asynchrones (tout sauf les cr�ateurs des
/// interfaces) en utilisant des objets de la classe NSTimer envoy�s sur
/// la boucle de l'application (la boucle courante lorsque la m�thode
/// initWithController: est appel�e).
///
/// Par ailleurs, en Cocoa, si on fait du multit�che pr�emptif avec mettons
/// les pthreads, il faut cr�er au moins un objet de type NSTask pour que
/// certains �l�ments de Cocoa soient initialis�s. Cette classe cr�e un objet
/// NSTask bidon.
///
/// Pour utiliser cette classe, il faut cr�er un contr�leur qui adopte le
/// protocole IDCLObjCApplication et initialiser cette classe avec ce
/// contr�leur.
///
/// \author Paul Guyot <pguyot@kallisys.net>
/// \version $Revision: 1.6 $
///
/// \test	aucun test d�fini.
///
@interface DCLCocoaApplication : NSObject < IDCLObjCApplication >
{
	NSRunLoop*					mRunLoop;		///< Boucle qui g�re les �v�nements.
	id < IDCLObjCApplication >	mController;	///< R�f�rence sur le contr�leur.
	TDCLObjCApplication* 		mDCLAppl;		///< R�f�rence sur l'application DCL.
	IDCLFiles*					mFilesIntf;		///< Interface pour les fichiers.
	IDCLThreads*				mThreadsIntf;	///< Interface pour les processus l�gers.
}

///
/// Initialisation de l'objet.
///
/// \param inContoller	contr�leur associ�.
/// \return \c this
///
- (id) initWithController: (id < IDCLObjCApplication >) inController;

///
/// Cr�e une invocation pour le mandataire avec le s�lecteur donn�.
///
/// \param inSelector	s�lecteur consid�r�
/// \return une invocation pour ce s�lecteur
///
- (NSInvocation*) CreateInvocationWithSelector: (SEL) inSelector;

///
/// Envoie l'invocation sur la boucle.
///
/// \param inInvocation	invocation consid�r�e.
///
- (void) SendInvocation: (NSInvocation*) inInvocation;

///
/// M�thode du processus l�ger bidon.
/// Ne sert � rien (enfin, sert uniquement � dire � Cocoa qu'on fait du
/// multi-t�che pr�emptif)
///
/// \param ignoredArgs	arguments ignor�s.
///
- (void) DummyThreadEntryPoint: (id) ignoredArgs;

///
/// Accesseur sur l'application DCL
///
/// \return une r�f�rence sur l'application DCL.
///
- (TDCLObjCApplication*) GetDCLAppl;

@end

#endif
		// _DCLCOCOAAPPLICATION_H

// ========================================================================= //
// The net is like a vast sea of lutefisk with tiny dinosaur brains embedded //
// in it here and there. Any given spoonful will likely have an IQ of 1, but //
// occasional spoonfuls may have an IQ more than six times that!             //
//         -- James 'Kibo' Parry                                             //
// ========================================================================= //