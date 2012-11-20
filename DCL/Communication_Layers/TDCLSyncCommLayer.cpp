// ==============================
// Fichier:			TDCLSyncCommLayer.cp
// Projet:			Desktop Connection Library
//
// Cr�� le:			28/3/2003
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
// The Original Code is TDCLSyncCommLayer.cp.
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
// $Id: TDCLSyncCommLayer.cp,v 1.3 2004/11/24 14:08:54 paul Exp $
// ===========

#include <DCL/Headers/DCLDefinitions.h>
#include <DCL/Communication_Layers/TDCLSyncCommLayer.h>

// DCL
#include <DCL/Exceptions/Errors/TDCLBadStateError.h>
#include <DCL/Link/TDCLLink.h>
#include <DCL/Server/TDCLServer.h>

// -------------------------------------------------------------------------- //
//  * TDCLSyncCommLayer( IDCLThreads*, Boolean, KUInt32 )
// -------------------------------------------------------------------------- //
TDCLSyncCommLayer::TDCLSyncCommLayer(
					IDCLThreads* inThreadsIntf,
					Boolean	inFlushAvailable /* = false */,
					KUInt32	inMaxPipeCount /* = kDefaultPipeCount */
				)
	:
		TDCLCommLayer( inFlushAvailable, inMaxPipeCount ),
		TDCLThread( inThreadsIntf )
{
}

// ------------------------------------------------------------------------- //
//  *�StartListening( TDCLServer* )
// ------------------------------------------------------------------------- //
void
TDCLSyncCommLayer::StartListening( TDCLServer* inServer )
{
	// Exception si on est d�j� en train d'�couter.
	if (GetServer())
	{
		throw DCLBadStateError;
	}
	
	// Enregistrement du serveur.
	SetServer( inServer );
	
	// D�marrage du processus l�ger.
	// Celui-ci appellera DoStartListening.
	Start();
}

// ------------------------------------------------------------------------- //
//  *�StopListening( void )
// ------------------------------------------------------------------------- //
void
TDCLSyncCommLayer::StopListening( void )
{
	// On ne fait rien si on n'est pas en train d'�couter.
	if (GetServer())
	{
		// On appelle la m�thode qui fait vraiment le travail.
		try {
			DoStopListening();
		
			// R�veil du processus l�ger
			WakeUp();

			// On attend que le processus l�ger termine.
			while (GetThreadState() != IDCLThreads::kStopped)
			{
				Yield();
			}
		} catch ( ... ) {
			// On reste silencieux.
		}
		
		SetServer( nil );
	}
}

// ------------------------------------------------------------------------- //
//  *�Run( void )
// ------------------------------------------------------------------------- //
void
TDCLSyncCommLayer::Run( void )
{
	// On commence � �couter.
	DoStartListening();
	
	// Ay�, on �coute.
	GetServer()->WaitingConnection( this );

	// On attend qu'une requ�te soit pr�sente.
	while ( WaitForIncomingRequest() )
	{
		// Une requ�te vient d'arriver. On pr�vient le serveur.
		TDCLServer* theServer = GetServer();
		
		if (theServer)
		{
			theServer->RequestPresent( this );
		} else {
			break;
		}

		(void) Sleep();	// On attend que la requ�te soit accept�e ou refus�e.
	}
}

// ------------------------------------------------------------------------- //
//  * Accept( void )
// ------------------------------------------------------------------------- //
TDCLPipe*
TDCLSyncCommLayer::Accept( void )
{
	TDCLPipe* thePipe = DoAccept();

	// R�veil du processus l�ger (pour la prochaine requ�te).
	WakeUp();

	return thePipe;
}

// ------------------------------------------------------------------------- //
//  * Refuse( void )
// ------------------------------------------------------------------------- //
void
TDCLSyncCommLayer::Refuse( void )
{
	DoRefuse();
	
	// R�veil du processus l�ger (pour la prochaine requ�te).
	WakeUp();
}

// --------------------------------------------------------------------------------	//
//  *�HandleException( TDCLException* )
// --------------------------------------------------------------------------------	//
void
TDCLSyncCommLayer::HandleException( TDCLException* inException )
{
	// On transmet au serveur.
	GetServer()->HandleCommLayerException( this, inException );
}

// --------------------------------------------------------------------------------	//
//  *�TSyncPipe( IDCLThreads*, TDCLSyncCommLayer* )
// --------------------------------------------------------------------------------	//
TDCLSyncCommLayer::TSyncPipe::TSyncPipe(
					IDCLThreads* inThreadsIntf, TDCLSyncCommLayer* inCommLayer )
	:
		TDCLPipe( inCommLayer ),
		TDCLThread( inThreadsIntf )
{
}

// --------------------------------------------------------------------------------	//
//  *�Disconnect( void )
// --------------------------------------------------------------------------------	//
void
TDCLSyncCommLayer::TSyncPipe::Disconnect( void )
{
	if (GetLink())
	{
		// On appelle la m�thode qui fait vraiment le travail.
		DoDisconnect();
		
		// On rel�che le processus s'il attendait
		WakeUp();
		
		// On attend que le processus l�ger termine.
		while (GetThreadState() != IDCLThreads::kStopped)
		{
			Yield();
		}
	}
}

// --------------------------------------------------------------------------------	//
//  *�Connected( TDCLLink* )
// --------------------------------------------------------------------------------	//
TDCLCommLayer*
TDCLSyncCommLayer::TSyncPipe::Connected( TDCLLink* inLink )
{
	// Appel de la m�thode par d�faut.
	TDCLCommLayer* theResult = TDCLPipe::Connected( inLink );
	
	// D�marrage du processus l�ger.
	Start();
	
	return theResult;
}

// --------------------------------------------------------------------------------	//
//  *�ClearDataPresent( void )
// --------------------------------------------------------------------------------	//
void
TDCLSyncCommLayer::TSyncPipe::ClearDataPresent( void )
{
	WakeUp();
}

// --------------------------------------------------------------------------------	//
//  *�Run( void )
// --------------------------------------------------------------------------------	//
void
TDCLSyncCommLayer::TSyncPipe::Run( void )
{
	do {
		(void) Sleep();	// On attend que le lien nous demande si on veut des donn�es.

		if ( WaitForIncomingData() )
		{
			// Des donn�es viennent d'arriver. On pr�vient le lien.
			GetLink()->DataPresent();
		} else {
			break;
		}
	} while ( true );
}

// --------------------------------------------------------------------------------	//
//  *�HandleException( TDCLException* )
// --------------------------------------------------------------------------------	//
void
TDCLSyncCommLayer::TSyncPipe::HandleException( TDCLException* inException )
{
	// On transmet � la couche de communication.
	((TDCLSyncCommLayer*) GetCommLayer())->HandleException( inException );
}

// ============================================================= //
// Sendmail may be safely run set-user-id to root.               //
//                 -- Eric Allman, "Sendmail Installation Guide" //
// ============================================================= //
