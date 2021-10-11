#pragma once
#include"GameState.h"
#include"MainMenuState.h"

class Game
{
private:
	//Variables
	sf::RenderWindow* window;
	sf::Event sfEvent;

	sf::Clock deltaTimeClock;
	float deltaTime;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;
	std::vector<sf::VideoMode> videoMode;
	sf::ContextSettings windowSetting;

	MainMenuState* mainMenu;
	
	//Initialization
	void initializeVariables();
	void initializeWindow();
	void initializeStates();
	void initializeKeys();



public:
	//Constructors/Deconstructors 
	Game();
	virtual ~Game();



	std::string name;
	long score;
	//Function

	//Regular
	void endApplication();

	//Update
	void updateDeltaTime();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();



};

