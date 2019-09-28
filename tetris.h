#pragma once

#include <stdlib.h>
#include <SFML/Graphics.hpp>
#include <iostream>

class tetris
{
private:
	static short _tetrominos[7][4];
	static unsigned short level_up;
	static unsigned short level_max;
	static double delay_start;
	static double delay_decay_rate;
	short** field;
	unsigned short _X;
	unsigned short _Y;
	struct tetrimino {
		short x[4] = {0,0,0,0};
		short y[4] = {0,0,0,0};
		unsigned short Color = 0;
	}current,aux;
	unsigned int points;
	unsigned short level;
	unsigned short row_counter;
	double delay;
	void change_delay();

public:
	tetris(unsigned short X, unsigned short Y);
	~tetris();
	void new_tetrimino();
	void rotate_tetrimino();
	void translate_tetrimino(short dx);
	bool lower_tetrimino();
	bool collision_check();
	void line_elimination();
	void display(sf::RenderWindow& window, sf::Sprite s, sf::Sprite background, sf::Sprite frame);
	unsigned int getPoints();
	unsigned short getLevel();
	double getDelay();
};

