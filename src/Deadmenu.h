#pragma once
#include"HighScores.h"

#include<vector>

#include<SFML\Graphics.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Window.hpp>
#include<SFML\Network.hpp>
#include<SFML\System.hpp>

#include<iostream>
#include<cstdlib>
#include<ctime>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>
class Deadmenu
{

private:
	sf::RectangleShape background;
	sf::RectangleShape container;
	sf::Texture bgTexture;


	HighScores* highscore;
	sf::Font& font;
	sf::Text text;
	sf::Event* event;

	


	float cursorTime;
	char lastchar;
	bool blink= true;
	std::ifstream scorefile;
	sf::Text playerName;
	std::string playerInput;
	sf::Text inputName;
	sf::RectangleShape inputBox;
	sf::String playername;
	sf::RectangleShape cursor;
	sf::Clock cursorClock;
	sf::Texture backgroundTexture;
	sf::RectangleShape backGround;

public:
	Deadmenu(sf::RenderWindow& window, sf::Font& font, sf::Event* event);
	virtual ~Deadmenu();

	// Function
	//const bool isButtonPressed(std::string key);
	//void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2i& mousePos);
	void render(sf::RenderTarget* target);
	void updateCursor();
	

};

