#!bin/sh

EXEC=cube3d
ARGS=maps/test_map.cub
SAVE=--save
valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --show-reachable=yes --track-origins=yes ./$EXEC $ARGS #$SAVE
