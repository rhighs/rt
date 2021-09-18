#!/bin/bash
make
OUTDIR="./out/"
OUTNAME="out.ppm"
OUT=${OUTDIR}${OUTNAME}
./ray > $OUT
xdg-open $OUT &>/dev/null & disown
