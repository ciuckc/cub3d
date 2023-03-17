#!/bin/sh

MAPS=$(find $(PWD)/cub_maps/valid -name "*.cub")

EXEC=$(PWD)/cub3D

if test -f "$EXEC"; then
	make
fi

for MAP in $MAPS; do
	echo Doing the test $MAP
	$EXEC $MAP
done
