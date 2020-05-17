#!/bin/bash
#==============================
# Fichier:			testm-cl-cad-fdserial.sh
# Projet:			(Desktop Connection Library)
# Ecrit par:		Paul Guyot (pguyot@kallisys.net)
# 
# Cr�� le:			14/6/2003
# Tabulation:		4 espaces
# 
# Copyright:		� 2003 by Paul Guyot.
# 					Tous droits r�serv�s pour tous pays.
# Licence:			Licence R�flexive Kallisys
# 					http://www.kallisys.org/reflexive/
# ===========
# $Id: testm-cl-cad-fdserial.sh,v 1.2 2003/06/14 16:49:49 paul Exp $
# ===========

if [ $# -ne 1 ]; then
	echo "Nombre invalide d'arguments."
	echo "Syntaxe: $0 <chemin vers DCLTests> <port s�rie>"
	exit 1
fi

DEVPATH=$2
. common.sh $1

echo "Ceci est un test manuel. L'exp�rimentateur doit �valuer si le test s'est bien pass�."

"$DCLTESTS" cl-cad-fdserial $DEVPATH

## ========================================================= ##
## Unix is a Registered Bell of AT&T Trademark Laboratories. ##
##                 -- Donn Seeley                            ##
## ========================================================= ##
