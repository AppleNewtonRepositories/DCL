#!/bin/bash
# ==============================
# Fichier:			test-ns-references.sh
# Projet:			(Desktop Connection Library)
# Ecrit par:		Paul Guyot (pguyot@kallisys.net)
#
# Cr�� le:			3/5/2003
# Tabulation:		4 espaces
#
# Copyright:		� 2003 by Paul Guyot.
# 					Tous droits r�serv�s pour tous pays.
# Licence:			Licence R�flexive Kallisys
# 					http://www.kallisys.org/reflexive/
# ===========
# $Id: test-ns-references.sh,v 1.4 2004/01/03 08:59:03 paul Exp $
# ===========

. common.sh $*

set -e
perl tests.pl "$DCLTESTS" ns-references-debugstr
perl tests.pl "$DCLTESTS" ns-references-kill

## ================================================================ ##
## In the long run, every program becomes rococco, and then rubble. ##
##                 -- Alan Perlis                                   ##
## ================================================================ ##
