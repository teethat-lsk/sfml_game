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
	if (!this->textures["SKELETON_SHEET"].loadFromFile("Resources/Sprites/Skeleton/Skeleton.png"))
		std::cout << "ERROR GameStste cant load Enemy texture" << "/n"  ;
	if (!this->textures["HP_BAR"].loadFromFile("Resources/Images/hpbar.png"))
		std::cout << "ERROR GameStste cant load HP-bar" << "/n";
}

void GameState::initializePauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);
	
	this->pauseMenu->addButton("CONTINUE", 350.f, "CONTINUE");
	this->pauseMenu->addButton("QUIT", 450.f, "QUIT");
}

void GameState::initializeCharacters()
{
	this->player = new Player(150+this->score/50,500, 500, this->textures["PLAYER_SHEET"]);
	//this->skeleton = new Skeleton(500.f, 500.f, this->textures["ENEMY_SHEET"],0);
	
	//this->skeleton->set_pt(this->player);
	
	//this->skeleton(50, 50, textures["SKELETON_SHEET"]);
}

void GameState::initializeView()
{
	this->view.setSize(sf::Vector2f(this->window->getSize().x,this->window->getSize().y));
	this->view.setCenter(sf::Vector2f(this->window->getSize().x/2,this->window->getSize().y));
}

void GameState::spawnEnemy()
{
	
//	this->enemy["skeleton"] = new Skeleton(rand()%1000, rand()%500, textures["SKELETON_SHEET"]);
	this->skeleton = new Skeleton(80+this->score/30,1000+(this->score*10),this->player->getPosition().x+rand() % 100, this->player->getPosition().y + rand() % 100, textures["SKELETON_SHEET"]);
	this->spawnTimer = this->spawnClock.getElapsedTime();
	//std::cout << this->spawnTimer.asMilliseconds() << "\n";
	
	if (this->skeletonArmy.size() < maxEnemy)
	{
		
		/*if (this->spawnTimer.asMilliseconds() - this->timer.asMilliseconds() > 2000)
		{
			this->enemyArmy.push_back(this->enemy["skeleton"]);
			std::cout << "wtf" << "\n";
			this->timer.asMilliseconds() = this->spawnTimer.asMilliseconds();
		}*/
		//std::cout << this->spawnTimer.asMilliseconds() - timer.asMilliseconds() << " DB\n";
		if (this->spawnTimer.asMilliseconds()-this->timer.asMilliseconds() > 2000/*-this->score/100 */)
		{
			this->skeletonArmy.push_back(this->skeleton);
			std::cout << "wtf" << "\n";
			timer = spawnTimer;
			
		}
		
		//std::cout << this->spawnTimer.asMilliseconds() << "\n";
	}
}

void GameState::moveEnemy(const float& deltatime)
{
	
	
	
		for (int i = 0; i < this->skeletonArmy.size(); i++)
		{
			if (!this->collisionCheck(this->player->getHbcenter(), this->player->getHbrad(), skeletonArmy[i]->getHbcenter(), skeletonArmy[i]->getHbrad())) {
				
				
				

				if (this->skeletonArmy[i]->getPosition().x > this->player->getPosition().x)
				{
					this->skeletonArmy[i]->move(-1.f, 0.f, deltatime);
				}
				if (this->skeletonArmy[i]->getPosition().x < this->player->getPosition().x)
				{
					this->skeletonArmy[i]->move(1.f, 0.f, deltatime);
				}
				if (this->skeletonArmy[i]->getPosition().y > this->player->getPosition().y)
				{
					this->skeletonArmy[i]->move(0.f, -1.f, deltatime);
				}
				if (this->skeletonArmy[i]->getPosition().y < this->player->getPosition().y)
				{
					this->skeletonArmy[i]->move(0.f, 1.f, deltatime);
				}
			}
			
		}
}

const bool GameState::collisionCheck(sf::Vector2f center1, sf::Vector2f rad1, sf::Vector2f center2, sf::Vector2f rad2) const
{
	if (abs(center1.x - center2.x) - (rad1.x + rad2.x) < 0 && abs(center1.y - center2.y) - (rad1.y + rad2.y) < 0)
	{

		return true;

	}
	return false;
}



//Constructor Destructor
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys,states)
{
	srand(time(NULL));
	this->hpBar.setTexture(this->textures["HP_BAR"]);
	this->scoretext.setFont(this->font);
	this->scoretext.setCharacterSize(35);
	this->scoretext.setFillColor(sf::Color::Red);
	this->scoretext.setOutlineColor(sf::Color::White);
	this->scoretext.setOutlineThickness(2);
	
	
	this->enemyCount = 0;
	this->maxEnemy = 20;
	this->initializeKeybinds();
	this->initializeFont();
	this->initializeTexture();
	this->initializePauseMenu();
	this->initializeCharacters();
	this->initializeView();
	this->spawnTimer = this->spawnClock.getElapsedTime();
	this->collidTimer = this->collidClock.getElapsedTime();

	//sf::Time spawnTimer = sf::seconds(this->spawnClock.getElapsedTime().asSeconds());
	
}

GameState::~GameState()
{
	delete this->player;
	delete this->skeleton;
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
	this->collidTimer = this->collidClock.getElapsedTime();
	
	scoretext.setString(std::to_string(this->score));
	scoretext.setPosition(this->player->getposition().x, this->player->getPosition().y - 350);

	if (this->player->getHealth() <= 0)
	{
		this->endState();

	}
	this->updateMousePosition(&this->view);
	this->updateKeytime(deltaTime);
	this->updateInput(deltaTime);
	
	if (!this->pause) //unpause
	{
		//std::cout << this->collision->getCollided() << std::endl;
		this->updateView(deltaTime);
		this->updatePlayerInput(deltaTime);
		this->player->update(deltaTime);
		
		
		this->spawnEnemy();
		this->moveEnemy(deltaTime);
		////////////////////////
		//////HEALTH UPDATE/////
		///////////////////////
		if (this->player->getHealth() > 0) {
			this->player->health->update(this->player->getPosition().x - 30.f, this->player->getPosition().y - 10, this->player->getPosition().x - 10.f, this->player->getPosition().y - 5);
		}
		
		for (int k=0 ; k<this->skeletonArmy.size();k++) 
		{
			
			skeletonArmy[k]->update(deltaTime);
			////////////////////////////////////////////////
			////////////////Collision Check////////////////
			///////////////////////////////////////////////
			
			
			
				
			
			if (this->collisionCheck(this->player->getHbcenter(), this->player->getHbrad(), skeletonArmy[k]->getHbcenter(), skeletonArmy[k]->getHbrad()))
			{
			
				std::cout << this->player->getattacktype() << std::endl;
				/*if (this->player->getattacktype()==3)
				{
					this->skeletonArmy[k]->health->damage(30);
				}
				if (this->player->getattacktype() == 2)
				{
					this->skeletonArmy[k]->health->damage(60);
				}*/
				if (this->player->getattacktype() )
				{
					this->skeletonArmy[k]->health->damage(this->player->getdamage()+this->score/100);
				}
				
				
				
				///////////////////////////////////////
				//////////////DAMAGE/////////////////
				///////////////////////////////////////
								
				//std::cout << this->collidTimer.asSeconds() - this->collidTime.asSeconds() << std::endl;
				
				if(this->collidTime == sf::milliseconds(0))
				{
					
					this->collidTime = this->collidTimer;

					
				}
				else
				{
					//std::cout << this->collidTimer.asSeconds() - this->collidTime.asSeconds() << " " << k << std::endl;
					if (this->collidTimer.asMilliseconds() - this->collidTime.asMilliseconds() > 200)
					{
												
						std::cout << "FUCKKKKKKKKKKKKKKKKKKKKKKKKK" << std::endl;
						this->player->health->damage(50+score/100);
						this->collidTime = sf::milliseconds(0);
					}

				}

			}
			else 
			{
				collidTime = sf::milliseconds(0);
			}
		}
		//std::cout<<this->collidTimer.asMilliseconds()<<std::endl;
		
		
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
   // target->draw(this->player->getSprite());
	//target->draw(this->skeleton.getSprite());
	this->player->render(*target);
	for (int i = 0 ;i<this->skeletonArmy.size();i++)
	{
		skeletonArmy[i]->render(*target);
		skeletonArmy[i]->health->render(*target);
		
		if (skeletonArmy[i]->getHealth() < 0)
		{
			delete this->skeletonArmy[i];
			
			this->skeletonArmy.erase(this->skeletonArmy.begin() + i);
			this->score += 10;
			
		}
		

	}
	//render from Player (which have allllll stuff of the Entity) which is called in this class as "player"  
		//Entity::render		//Entity::render(sf::windowRender* target) {target->draw(this->sprite);}
									
									//"target" tranform to "window" ===> draw() on window
	this->player->health->render(*target);
	//this->enemyArmy->render(*target);
	//std::cout << enemyArmy.size() << std::endl;
	//std::cout << this->player->health->gethealth() << std::endl;
	//for (auto& i : this->skeletonArmy) {
	//	/*std::cout << this->player->getHbcenter().x << " " << this->player->getHbrad().x << std::endl;
	//	std::cout << i->getHbcenter().x << " " << i->getHbrad().x << std::endl << std::endl;*/
	//}
	
	target->draw(this->scoretext);

	if (this->pause) // pause memu
	{
		target->setView(this->window->getDefaultView());
		pauseMenu->render(*target);
	}
}

long GameState::getScore()
{
	return this->score;
}


