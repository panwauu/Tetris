#include <SFML/Graphics.hpp>
#include <time.h>
#include "tetris.h"
#include "iostream"

using namespace sf;

// Missing points:
// Advanced control (like start and stuff)
// Variable size of the game and the window
// Nicer background

int main() {
	srand(time(NULL));

	tetris game(10, 20);

	Texture t1, t2, t3;
	t1.loadFromFile("images/tiles.png");
	t2.loadFromFile("images/background.png");
	t3.loadFromFile("images/frame.png");

	Sprite s(t1), background(t2), frame(t3);

	// Predefine operators
	double timer = 0, delay;
	Clock clock;

	sf::RenderWindow window(VideoMode(320, 480), "TETRIS");

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;

		Event e;
		while(window.pollEvent(e)){
			if (e.type == Event::Closed) window.close();

			if (e.type == Event::KeyPressed) {
				if (e.key.code == Keyboard::Up) game.rotate_tetrimino();
				if (e.key.code == Keyboard::Right) game.translate_tetrimino(1);
				if (e.key.code == Keyboard::Left) game.translate_tetrimino(-1);
			}
		}

		// PROPAGATE TIME //
		delay = game.getDelay();
		if (Keyboard::isKeyPressed(Keyboard::Down)) delay = 0.05;

		if (timer > delay)
		{
			if (game.lower_tetrimino() == 0) {
				window.close();
			}
			
			timer = 0;
			std::cout << "Level: " << game.getLevel() << "; Points: " << game.getPoints() << std::endl;
		}

		// ELIMINATE LINES //
		game.line_elimination();
		
		// DRAW FIELD //
		game.display(window, s, background, frame);
	}

	std::cout << "You failed!" << std::endl;
	std::cout << "Level: " << game.getLevel() << "; Points: " << game.getPoints() << std::endl;


	return 0;
}
