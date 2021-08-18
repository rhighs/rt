#!/bin/bash
make
OUTDIR="./out/"
OUTNAME="out.ppm"
OUT=${OUTDIR}${OUTNAME}
./ray > $OUT
okular $OUT &>/dev/null & disown
