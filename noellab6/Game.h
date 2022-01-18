#pragma once
#include <Level.h>
#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	void run();
private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void processKeyReleases(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	void setup();

	Level level;

	sf::Texture bgtex;
	sf::Sprite bg;

	sf::Texture texttex;
	sf::Sprite text;

	sf::Texture playertex;
	sf::Sprite player;
	bool right = false;
	bool left = false;

	sf::RenderWindow m_window; // main SFML window
	bool m_exitGame; // control exiting game
};

