#pragma once
#ifndef _TETRIS_CPP
#define _TETRIS_CPP

#include "tetris.h"

tetris::tetris(unsigned short X, unsigned short Y) :_X(X), _Y(Y)
{
	field = new short[X][Y];
	for (int i = 0; i < Y; i++)
		for (int j = 0; j < X; j++)
			field[i][j] = -1;
}

#endif