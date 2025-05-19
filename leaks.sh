#!bin/sh

EXEC=cube3d
ARGS=maps/hard_map.cub
SAVE=--save
valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --show-reachable=yes --track-origins=yes ./$EXEC $ARGS #$SAVE
