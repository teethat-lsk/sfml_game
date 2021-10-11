#include "Game.h"



//Static Function

void Game::initializeVariables()
{
	/*
	this->window = NULL;
	this->deltaTime = 0.0f;
	*///this->mainMenu= sfevent
}

//Initialization
void Game::initializeWindow()
{
	/*Create a SFML Window */
	std::ifstream ifs("Config/window.initial.txt");
	this->videoMode = sf::VideoMode::getFullscreenModes();
	std::string title = "None";
	sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
	unsigned framerate_limit = 1;
	bool fullscreen = false;
	bool verticla_sync_enable = false;
	unsigned antialiasing_level = 0;
	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> fullscreen;
		ifs >> framerate_limit;
		ifs >> verticla_sync_enable;
		ifs >> antialiasing_level;
	}
	ifs.close();

	this->windowSetting.antialiasingLevel = antialiasing_level;
	
	if(1/*fullscreen*/)
		this->window = new sf::RenderWindow(window_bounds, title,sf::Style::Fullscreen,windowSetting);
	else
		this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSetting);
	
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(verticla_sync_enable);
	
}

void Game::initializeKeys()
{
	
	this->supportedKeys["Escape"]=sf::Keyboard::Key::Escape;
	this->supportedKeys["A"]= sf::Keyboard::Key::A;
	this->supportedKeys["D"]= sf::Keyboard::Key::D;
	this->supportedKeys["W"]= sf::Keyboard::Key::W;
	this->supportedKeys["S"]= sf::Keyboard::Key::S;
	/*
	this->supportedKeys["ATTACK_1"] = sf::Keyboard::Key::J;
	this->supportedKeys["ATTACK_2"] = sf::Keyboard::Key::K;
	this->supportedKeys["ATTACK_3"] = sf::Keyboard::Key::L;
	this->supportedKeys["SHIELD"] = sf::Keyboard::Key::H;
	this->supportedKeys["ROLL"] = sf::Keyboard::Key::Space;
	*/
}

void Game::initializeStates()
{
	
	this->states.push(new MainMenuState(this->window, &this->supportedKeys,&this->states, &this->sfEvent));
	//this->states.push(new GameState(this->window, &this->supportedKeys));
}
	



//Constructors/Deconstructors 
Game::Game()
{
	this->initializeWindow();
	this->initializeKeys();
	this->initializeStates();


}
Game::~Game()
{
	delete this->window;
	while (!this->states.empty())
	{
		
		delete this->states.top(); //remove data that pointer holding
		this->states.pop(); // remove the pointer
	}
	delete this->mainMenu;
}

//Function
void Game::endApplication()
{
	std::cout << "Ending Application" << std::endl;
}

void Game::updateDeltaTime()
{
	/*update deltaTime with the time it takes to render one frame ->  Depending on what the hell you do in the game*/
	this->deltaTime = deltaTimeClock.restart().asSeconds();
	/*deltaTime check*/
	//system("cls");/*clear screen*/
	//std::cout << this->deltaTime;
}



//Functions
void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
	
	
}
void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->deltaTime);// call "update"(pure virtual)from State(supper class) will use "update"
													//from Gamestate or MainmenuState(subclass) which is push to stack.top() 
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Application end
	else
	{
		this->endApplication();
		this->window->close();
	}
}
void Game::render()
{
	this->window->clear();
	//Render items
	if (!this->states.empty())
	{
		this->states.top()->render();//call "render()" (pure virtual)from State(supper class) will use "render()" 
									//from Gamestate or MainmenuState(subclass) which is push to stack.top() 
	}
	this->window->display();

}
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDeltaTime();
		this->update();
		this->render();
	}
}



