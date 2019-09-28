#include "tetris.h"

using namespace sf;

short tetris::_tetrominos[7][4]{
	1,3,5,7, // I-shape
	5,4,3,7, // T-shape
	4,5,6,7, // O-shape
	4,2,6,7, // L-shape
	5,3,6,7, // L-mirror-shape
	4,2,5,7, // Z-mirror-shape
	5,4,3,6 // Z-shape
};

unsigned short tetris::level_up = 2;

unsigned short tetris::level_max = 10;

double tetris::delay_start = 0.3;

double tetris::delay_decay_rate = 0.7;

void tetris::change_delay()
{
	delay = delay_start* delay_decay_rate;
}

tetris::tetris(unsigned short X, unsigned short Y) :_X(X), _Y(Y), points(0), level(1), row_counter(0), delay(delay_start)
{
	field = new short* [X];
	for (int i = 0; i < X; ++i)
		field[i] = new short[Y];
	for (int i = 0; i < X; i++)
		for (int j = 0; j < Y; j++)
			field[i][j] = -1;

	new_tetrimino();
	aux = current;
}

tetris::~tetris() {
	for (int i = 0; i < _X; ++i)
		delete[] field[i];
	delete[] field;
}

void tetris::new_tetrimino()
{
	current.Color = rand() % 8;
	int n = rand() % 7;
	for (int i = 0; i < 4; i++) {
		current.x[i] = _tetrominos[n][i] % 2 + _X / 2 -1;
		current.y[i] = _tetrominos[n][i] / 2;
	}
}

void tetris::rotate_tetrimino()
{
	aux = current;

	short x_middle = current.x[0];
	short y_middle = current.y[0];
	for (int i = 0; i < 4; i++) {
		int x = current.y[i] - y_middle;
		int y = current.x[i] - x_middle;
		current.x[i] = x_middle - x;
		current.y[i] = y_middle + y;
	}

	if (!collision_check()) {
		current = aux;
	}
}

void tetris::translate_tetrimino(short dx)
{
	aux = current;
	for (int i = 0; i < 4; i++) {current.x[i] += dx; }
	if (!collision_check()) {
		current = aux;
	}
}

bool tetris::lower_tetrimino()
{
	aux = current;

	// lower the tetrimonio
	for (int i = 0; i < 4; i++) {current.y[i] += 1; }

	// check if it sits on the lower one
	if (!collision_check())
	{
		for (int i = 0; i < 4; i++) field[aux.x[i]][aux.y[i]] = aux.Color;
		new_tetrimino();
	}

	// check if new tetrimonio is colliding
	if (!collision_check()) {
		return 0;
	}
	
	return 1;
}

// return 1 if no collision and 0 if colliding
bool tetris::collision_check()
{
	bool collision_free = 1;

	for (int i = 0; i < 4; i++)
		if (current.x[i] < 0 || current.x[i] >= _X || current.y[i] >= _Y) collision_free = 0;
		else if (field[current.x[i]][current.y[i]] >= 0) collision_free = 0;

	return collision_free;
}

// eliminates all lines that are filled completely
void tetris::line_elimination()
{
	int k = _Y - 1;

	// iterate from bottom to top
	for (int i = _Y - 1; i > 0; i--) {
		// check if line is filled
		int count = 0;
		for (int j = 0; j < _X; j++) {
			if (field[j][i] >= 0) count++;
			field[j][k] = field[j][i];
		}
		if (count < _X) k--;
	}

	// calculate points for finished lines - (40 for 1, 100 for 2, 300 for 3, 1200 for 4)*levelnumber
	if (k == 1) points += 1 * 40;
	else if (k == 2) points += level * 100;
	else if (k == 3) points += level * 300;
	else if (k == 4) points += level * 1200;

	// perform level ups
	row_counter += k;
	if (row_counter >= level_up) {
		row_counter = 0;
		if (level < level_max) {
			level++;
			change_delay();
		}
	}

}

void tetris::display(sf::RenderWindow& window, sf::Sprite s, sf::Sprite background, sf::Sprite frame)
{
	window.clear(Color::White);
	window.draw(background);

	for (int i = 0; i < _X; i++)
		for (int j = 0; j < _Y; j++)
		{
			if (field[i][j] < 0) continue;
			s.setTextureRect(IntRect(field[i][j] * 18, 0, 18, 18));
			s.setPosition(i * 18, j * 18);
			s.move(28, 31); //offset
			window.draw(s);
		}

	for (int i = 0; i < 4; i++)
	{
		s.setTextureRect(IntRect(current.Color * 18, 0, 18, 18));
		s.setPosition(current.x[i] * 18, current.y[i] * 18);
		s.move(28, 31); //offset
		window.draw(s);
	}

	window.draw(frame);
	window.display();
}

unsigned int tetris::getPoints()
{
	return points;
}

unsigned short tetris::getLevel()
{
	return level;
}

double tetris::getDelay()
{
	return delay;
}


