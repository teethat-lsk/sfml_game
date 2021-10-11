#include "GameState.h"
//Initialize functions



void GameState::initializeKeybinds()
{
	this->keybinds["Move_Left"]=this->supportedKeys->at("A");
	this->keybinds["Move_Right"]= this->supportedKeys->at("D");
	this->keybinds["Move_Up"] =this->supportedKeys->at("W");
	this->keybinds["Move_Down"] =this->supportedKeys->at("S");
	this->keybinds["Pause"] = this->supportedKeys->at("Escape");
	/*
	this->keybinds["ATTACK_1"] = this->supportedKeys->at("ATTACK_1");
	this->keybinds["ATTACK_2"] = this->supportedKeys->at("ATTACK_2");
	this->keybinds["ATTACK_3"] = this->supportedKeys->at("ATTACK_3");
	this->keybinds["SHIELD"] = this->supportedKeys->at("SHIELD");
	this->keybinds["ROLL"] = this->supportedKeys->at("ROLL");
	*/
}

void GameState::initializeFont()
{
	if (!font.loadFromFile("Font/Cream Peach.ttf"))
	{
		std::cout << "ERROR MAINMENU LOADING FONT";
	}
}

void GameState::initializeTexture()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Sprites/Player/Player.png"))
		std::cout << "ERROR Game state cant load player texture " << "/n";
	if (!this->textures["ENEMY_SHEET"].loadFromFile("Resources/Sprites/Skeleton/Skeleton.png"))
		std::cout << "ERROR GameStste cant load Enemy texture" << "/n"  ;
}

void GameState::initializePauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);
	
	this->pauseMenu->addButton("CONTINUE", 350.f, "CONTINUE");
	this->pauseMenu->addButton("QUIT", 450.f, "QUIT");
}

void GameState::initializeCharacters()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
	this->skeleton = new Skeleton(500.f, 500.f, this->textures["ENEMY_SHEET"]);

}

void GameState::initializeView()
{
	this->view.setSize(sf::Vector2f(this->window->getSize().x,this->window->getSize().y));
	this->view.setCenter(sf::Vector2f(this->window->getSize().x/2,this->window->getSize().y));
}


//Constructor Destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys,states)
{
	
	this->initializeKeybinds();
	this->initializeFont();
	this->initializeTexture();
	this->initializePauseMenu();
	this->initializeCharacters();
	this->initializeView();
	
}

GameState::~GameState()
{
	delete this->player;
	delete this->enemy;
	delete this->pauseMenu;
}



void GameState::updateView(const float& deltaTime)
{
	this->view.setCenter(this->player->getPosition());
}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
	{
		this->endState();
	}
	if (this->pauseMenu->isButtonPressed("CONTINUE"))
	{
		this->unpauseState();
	}
	

}

void GameState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Pause")))&& this->getKeytime())
	{
		if (!this->pause) {
			
			this->pauseState();
			
		}
		else 
			this->unpauseState();
	}
} 

void GameState::updatePlayerInput(const float& deltaTime)
{
	
	//player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Left"))))
		this->player->move(-1.0f, 0.0f,deltaTime );
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Down"))))
		this->player->move( 0.0f, 1.0f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Right"))))
		this->player->move( 1.0f, 0.0f, deltaTime);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Up"))))
		this->player->move( 0.0f, -1.0f, deltaTime);
	
	
	

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		this->quit = true;*/
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
		std::cout << "wtf" << std::endl;*/
	
}

void GameState::update(const float& deltaTime)
{ 
	this->updateMousePosition(&this->view);
	this->updateKeytime(deltaTime);
	this->updateInput(deltaTime);
	
	if (!this->pause) //unpause
	{
		this->updateView(deltaTime);
		this->updatePlayerInput(deltaTime);
		this->player->update(deltaTime);
	}
	else //pause
	{

		this->pauseMenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	
	
	if (!target)
		target = this->window;

	target->setView(this->view);

	//this->map.render(*target);


	this->player->render(*target); //render from Player (which have allllll stuff of the Entity) which is called in this class as "player"  
		//Entity::render		//Entity::render(sf::windowRender* target) {target->draw(this->sprite);}
									
									//"target" tranform to "window" ===> draw() on window

	this->enemy->render(*target);
	

	if (this->pause) // pause memu
	{
		target->setView(this->window->getDefaultView());
		pauseMenu->render(*target);
	}
}


