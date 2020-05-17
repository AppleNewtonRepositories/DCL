#!/bin/bash
# ==============================
# Fichier:			common.sh
# Projet:			(Desktop Connection Library)
# Ecrit par:		Paul Guyot (pguyot@kallisys.net)
#
# Cr�� le:			2/5/2003
# Tabulation:		4 espaces
#
# Copyright:		� 2003 by Paul Guyot.
# 					Tous droits r�serv�s pour tous pays.
# Licence:			Licence R�flexive Kallisys
# 					http://www.kallisys.org/reflexive/
# ===========
# $Id: common.sh,v 1.8 2003/06/21 15:58:37 paul Exp $
# ===========

if [ $# -ne 1 ]; then
	echo "Nombre invalide d'arguments."
	echo "Syntaxe: $0 <chemin vers DCLTests>"
	exit 1
fi

LC_CTYPE=
LANG=

# D�termination de la racine de la DCL � partir de PWD.
# Comme ce script est appel� par . common.sh dans les diff�rents scripts des
# tests, on peut supposer que PWD est le dossier des scripts.
DCL="$PWD/../../"

# Ex�cutable pour faire les tests.
DCLTESTS="$1"

# R�pertoire pour les fichiers temporaires.
TMPDIR=/tmp

# Fichier ma�tre
MASTERFILE=$TMPDIR/dcl-tests-$$-master

# Fichier de sortie
OUTFILE=$TMPDIR/dcl-tests-$$-out

# Test d�sactiv�.
NOTAVAILFILE=$TMPDIR/dcl-tests-$$-notavail

# Nettoyage des fichiers pr�c�dents (pour les �checs pr�c�dents).
rm -f $TMPDIR/dcl-tests-*

cat > $NOTAVAILFILE << ENDNOTAVAIL
Test non disponible pour cette plateforme
ENDNOTAVAIL

# M�thode pour comparer.
compare() {
	if [ `diff -u $NOTAVAILFILE $OUTFILE | wc -l` -ne "0" ]
	then
		if [ `diff -u $MASTERFILE $OUTFILE | tee /dev/stderr | wc -l` -ne "0" ]
		then
			echo "$0 : ECHEC"
			exit 1
		else
			echo "$0 : SUCCES"
		fi
	else
		echo "$0 : NON DISPONIBLE"
	fi
}

## ====================================================================== ##
## Prof:    So the American government went to IBM to come up with a data ##
##          encryption standard and they came up with ...                 ##
## Student: EBCDIC!"                                                      ##
## ====================================================================== ##
