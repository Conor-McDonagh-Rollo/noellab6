#include "Game.h"

Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "Lab 6" },
	m_exitGame{ false } //when true game will exit
{
	setup(); // load texture
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}

void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if (sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::KeyReleased == newEvent.type)
		{
			processKeyReleases(newEvent);
		}
	}
}

void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::D == t_event.key.code)
	{
		right = true;
	}
	if (sf::Keyboard::A == t_event.key.code)
	{
		left = true;
	}
}

void Game::processKeyReleases(sf::Event t_event)
{
	if (sf::Keyboard::D == t_event.key.code)
	{
		right = false;
	}
	if (sf::Keyboard::A == t_event.key.code)
	{
		left = false;
	}
}

//time interval per frame
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
	level.update(player.getGlobalBounds());
	if (level.reset) setup();
	if (right) player.move(5, 0);
	if (left) player.move(-5, 0);
	if (player.getPosition().x < 0 || player.getPosition().x > 760) setup();
	if (text.getPosition().y < 350) text.move(0.f,2.f);
}

// draw the frame and then switch buffers
void Game::render()
{
	m_window.clear(sf::Color::White);

	m_window.draw(bg);
	level.draw(m_window);
	m_window.draw(player);
	m_window.draw(text);

	m_window.display();
}

void Game::setup()
{
	playertex.loadFromFile("ASSETS/IMAGES/player.png");
	player.setTexture(playertex);
	player.setPosition(360, 540);
	bgtex.loadFromFile("ASSETS/IMAGES/bg.png");
	bg.setTexture(bgtex);
	level.setup();
	texttex.loadFromFile("ASSETS/IMAGES/text.png");
	text.setTexture(texttex);
	text.setPosition(100,2500);
}
