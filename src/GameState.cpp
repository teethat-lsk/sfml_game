#include "GameState.h"

//Initialize functions



void GameState::initializeKeybinds()
{
	this->keybinds["Move_Left"] = this->supportedKeys->at("A");
	this->keybinds["Move_Right"] = this->supportedKeys->at("D");
	this->keybinds["Move_Up"] = this->supportedKeys->at("W");
	this->keybinds["Move_Down"] = this->supportedKeys->at("S");
	this->keybinds["Pause"] = this->supportedKeys->at("Escape");
	/*
	this->keybinds["ATTACK_1"] = this->supportedKeys->at("ATTACK_1");
	this->keybinds["ATTACK_2"] = this->supportedKeys->at("ATTACK_2");
	this->keybinds["ATTACK_3"] = this->supportedKeys->at("ATTACK_3");
	this->keybinds["SHIELD"] = this->supportedKeys->at("SHIELD");
	this->keybinds["ROLL"] = this->supportedKeys->at("ROLL");
	*/

}

void GameState::initButton()
{
	this->buttons["MAINMENU"] = new Button(100.f, 600.f, 300.f, 100.f,
		&this->font, "MAINMENU", 30,
		sf::Color::Transparent, sf::Color::White, sf::Color::Transparent, sf::Color::White, sf::Color::Black, sf::Color::Black);
}

void GameState::initbg()
{
	this->gamebg.setSize(sf::Vector2f(5000.f, 5000.f));
	this->gamebg.setTexture(&this->textures["Gamebg"]);
	
	this->gamebg2.setSize(sf::Vector2f(5000.f, 5000.f));
	this->gamebg2.setTexture(&this->textures["Gamebg2"]);
	
}




void GameState::initializeFont()
{
	if (!font.loadFromFile("Font/Cream Peach.ttf"))
	{
		std::cout << "ERROR MAINMENU LOADING FONT";
	}
	if (!name.loadFromFile("Font/So Sweet Honey.ttf"))
	{
		std::cout << "ERROR MAINMENU LOADING FONT";
	}
}

void GameState::initializeTexture()
{
	if (!this->textures["Gamebg"].loadFromFile("Resources/Images/map1.png"))
		std::cout << "ERROR Game state cant load bg texture " << "/n";
	if (!this->textures["Gamebg2"].loadFromFile("Resources/Images/map2.png"))
		std::cout << "ERROR Game state cant load bg texture " << "/n";
	if (!this->textures["Deadbg"].loadFromFile("Resources/Images/dead.png"))
		std::cout << "ERROR GameStste cant load deadbg texture" << "/n";


	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Sprites/Player/Player.png"))
		std::cout << "ERROR Game state cant load player texture " << "/n";
	if (!this->textures["SKELETON_SHEET"].loadFromFile("Resources/Sprites/Skeleton/Skeleton.png"))
		std::cout << "ERROR GameStste cant load Enemy texture" << "/n";
	if (!this->textures["MINOTAUR"].loadFromFile("Resources/Sprites/Minotaur2.png"))
		std::cout << "ERROR GameStste cant load Minotaur texture" << "/n";
	if (!this->textures["BOSS"].loadFromFile("Resources/Sprites/BOSS.png"))
		std::cout << "ERROR GameStste cant load BOSS texture" << "/n";

	if (!this->textures["ITEM"].loadFromFile("Resources/Images/item.png"))
		std::cout << "ERROR GameStste cant load ITEM texture" << "/n";
	if (!this->textures["HP_BAR"].loadFromFile("Resources/Images/hpbar.png"))
		std::cout << "ERROR GameStste cant load HP-bar" << "/n";
}

void GameState::initializePauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);

	this->pauseMenu->addButton("CONTINUE", 350.f, "CONTINUE");
	this->pauseMenu->addButton("QUIT", 450.f, "QUIT");
}
void GameState::initializeDeadMenu()
{
	/*this->deadMenu = new Deadmenu(*this->window, this->font, this->event);

	this->deadMenu->addButton("MAINMENU", 350.f, "MAINMENU");*/
	
}

void GameState::initializeCharacters()
{
	this->player = new Player(200 + this->score / 100, 2500, 2500, this->textures["PLAYER_SHEET"]);
	//this->skeleton = new Skeleton(500.f, 500.f, this->textures["ENEMY_SHEET"],0);

	//this->skeleton->set_pt(this->player);

	//this->skeleton(50, 50, textures["SKELETON_SHEET"]);
}

void GameState::initializeView()
{
	this->view.setSize(sf::Vector2f(this->window->getSize().x, this->window->getSize().y));
	this->view.setCenter(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y));
}

void GameState::spawnEnemy()
{
	/////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////Skeleton/////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
	//	this->enemy["skeleton"] = new Skeleton(rand()%1000, rand()%500, textures["SKELETON_SHEET"]);
	this->skeleton = new Skeleton(60 + this->score / 30, 500 + (this->score * 10), ((rand()+500)%1000)+score, ((rand()+500) % 1000)+score, textures["SKELETON_SHEET"]);
	this->spawnTimer = this->spawnClock.getElapsedTime();
	//std::cout << this->spawnTimer.asMilliseconds() << "\n";

	if (this->skeletonArmy.size() < maxEnemy)
	{

		
		if (this->spawnTimer.asMilliseconds() - this->timer.asMilliseconds() > 4000-this->score/10/*-this->score/100 */&&this->player->getHealth()>0)
		{
			this->skeletonArmy.push_back(this->skeleton);
			std::cout << "wtf" << "\n";
			timer = spawnTimer;

		}

		//std::cout << this->spawnTimer.asMilliseconds() << "\n";
	}
	//////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////item//////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
	this->itm = new itembot(((rand() + 500) % 1000) + score, ((rand() + 500) % 1000) + score, textures["ITEM"]);
	//this->spawnTimer = this->spawnClock.getElapsedTime();
	//std::cout << this->spawnTimer.asMilliseconds() << "\n";

	if (this->item.size() < 3)
	{

		
		if (this->itemClock.getElapsedTime().asSeconds() > 30-this->score/50)
		{
			this->item.push_back(this->itm);
			std::cout << "item!!!!!!!" << std::endl;
			this->itemClock.restart();
		}

		//std::cout << this->spawnTimer.asMilliseconds() << "\n";
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////MINOTAUR//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////
	this->minotaur = new Minotaur(3000+this->score/10,((rand() + 500) % 1000) + score, ((rand() + 500) % 1000) + score, textures["MINOTAUR"]);
	//this->spawnTimer = this->spawnClock.getElapsedTime();
	//std::cout << this->spawnTimer.asMilliseconds() << "\n";

	if (this->minotaurArmy.size() < 3)
	{


		if (this->minoClock.getElapsedTime().asSeconds() > 40)
		{
			this->minotaurArmy.push_back(this->minotaur);
			std::cout << "Minotaur" << std::endl;
			this->minoClock.restart();
		}

		//std::cout << this->spawnTimer.asMilliseconds() << "\n";
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////BOSS//////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	this->boss = new Boss(200 + score / 10, 6000 + this->score * 10, ((rand() + 500) % 1000) + score, ((rand() + 500) % 1000) + score, textures["BOSS"]);
	//this->spawnTimer = this->spawnClock.getElapsedTime();
	//std::cout << this->spawnTimer.asMilliseconds() << "\n";

	if (this->bossArmy.size() <  1 && this->score % 200==0 && this->score >300) ////////////////Gimmic////////////////////// BOSS every score%200==0
	{


		
		
		
			if (this->bossClock.getElapsedTime().asSeconds() > 3)
			this->bossArmy.push_back(this->boss);
		
		
		

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
	
	for (int j = 0; j < this->item.size(); j++)
	{
		if (!this->collisionCheck(this->player->getHbcenter(), this->player->getHbrad(), item[j]->getHbcenter(), item[j]->getHbrad())) {




			if (this->item[j]->getPosition().x > this->player->getPosition().x)
			{
				this->item[j]->move(-1.f, 0.f, deltatime);
			}
			if (this->item[j]->getPosition().x < this->player->getPosition().x)
			{
				this->item[j]->move(1.f, 0.f, deltatime);
			}
			if (this->item[j]->getPosition().y > this->player->getPosition().y)
			{
				this->item[j]->move(0.f, -1.f, deltatime);
			}
			if (this->item[j]->getPosition().y < this->player->getPosition().y)
			{
				this->item[j]->move(0.f, 1.f, deltatime);
			}
		}

	}

	for (int j = 0; j < this->minotaurArmy.size(); j++)
	{
		if (!this->collisionCheck(this->player->getHbcenter(), this->player->getHbrad(), minotaurArmy[j]->getHbcenter(), minotaurArmy[j]->getHbrad())) {




			if (this->minotaurArmy[j]->getPosition().x+35 > this->player->getPosition().x)
			{
				this->minotaurArmy[j]->move(-1.f, 0.f, deltatime);
			}
			if (this->minotaurArmy[j]->getPosition().x+35 < this->player->getPosition().x)
			{
				this->minotaurArmy[j]->move(1.f, 0.f, deltatime);
			}
			if (this->minotaurArmy[j]->getPosition().y+50 > this->player->getPosition().y)
			{
				this->minotaurArmy[j]->move(0.f, -1.f, deltatime);
			}
			if (this->minotaurArmy[j]->getPosition().y +50< this->player->getPosition().y)
			{
				this->minotaurArmy[j]->move(0.f, 1.f, deltatime);
			}
		}

	}

	for (int j = 0; j < this->bossArmy.size(); j++)
	{
		if (!this->collisionCheck(this->player->getHbcenter(), this->player->getHbrad(), bossArmy[j]->getHbcenter(), bossArmy[j]->getHbrad())) {




			if (this->bossArmy[j]->getPosition().x + 10 > this->player->getPosition().x)
			{
				this->bossArmy[j]->move(-1.f, 0.f, deltatime);
			}
			if (this->bossArmy[j]->getPosition().x +10 < this->player->getPosition().x)
			{
				this->bossArmy[j]->move(1.f, 0.f, deltatime);
			}
			if (this->bossArmy[j]->getPosition().y +30 > this->player->getPosition().y)
			{
				this->bossArmy[j]->move(0.f, -1.f, deltatime);
			}
			if (this->bossArmy[j]->getPosition().y +30 < this->player->getPosition().y)
			{
				this->bossArmy[j]->move(0.f, 1.f, deltatime);
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
GameState::GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,sf::String playername,sf::Event* event )
	: State(window, supportedKeys, states)
{
	this->event = event;
	

	srand(time(NULL));
	this->hpBar.setTexture(this->textures["HP_BAR"]);
	this->scoretext.setFont(this->font);
	this->scoretext.setCharacterSize(35);
	this->scoretext.setFillColor(sf::Color::Red);
	this->scoretext.setOutlineColor(sf::Color::White);
	this->scoretext.setOutlineThickness(2);
	this->playername = playername;


	this->enemyCount = 0;
	this->maxEnemy = 20+this->score/50;
	this->initializeKeybinds();
	this->initializeFont();
	this->initializeTexture();
	this->initbg();
	
	this->initializePauseMenu();
	this->initializeCharacters();
	this->initializeView();
	this->initButton();
	/*this->initInput();
	this->initInputBox();*/
	this->initPlayername();
	this->spawnTimer = this->spawnClock.getElapsedTime();
	this->collidTimer = this->collidClock.getElapsedTime();

	//sf::Time spawnTimer = sf::seconds(this->spawnClock.getElapsedTime().asSeconds());

}

GameState::~GameState()
{
	delete this->player;
	delete this->skeleton;
	delete this->pauseMenu;
	delete this->itm;
	delete this->minotaur;
	delete this->boss;
	

	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}


}



void GameState::updateView(const float& deltaTime)
{
	this->view.setCenter(this->player->getPosition());
}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
	{
		this->highscore->saveScore(this->playername,this->score);
		this->endState();
	}
	if (this->pauseMenu->isButtonPressed("CONTINUE"))
	{
		this->unpauseState();
	}


}

void GameState::updateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Pause"))) && this->getKeytime())
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
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Left")))&&this->player->getHbcenter().x>400)
		this->player->move(-1.0f, 0.0f, deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Down"))) && this->player->getHbcenter().y <4600)
		this->player->move(0.0f, 1.0f, deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Right"))) && this->player->getHbcenter().x < 4600)
		this->player->move(1.0f, 0.0f, deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("Move_Up"))) && this->player->getHbcenter().y >400)
		this->player->move(0.0f, -1.0f, deltaTime);




	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		this->quit = true;*/
		/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
			std::cout << "wtf" << std::endl;*/

}


void GameState::update(const float& deltaTime)
{
	this->updateMousePosition();
	

	scoretext.setString(std::to_string(this->score));
	scoretext.setPosition(this->player->getposition().x, this->player->getPosition().y - 350);

	
	this->updateMousePosition(&this->view);
	this->updateKeytime(deltaTime);
	this->updateInput(deltaTime);

	if (!this->pause) //unpause
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
		{
			this->player->health->damage(2000);
		}
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
		
		
			////////////////////////////////////////////////
			////////////////Collision Check////////////////
			///////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*if (cursorClock.getElapsedTime().asSeconds() > 3)
	{
		cursorClock.restart()
	}*/
	////////////////////////////////////////////////skeleton////////////////////////////////////////////////////////////
		for (int k = 0; k < this->skeletonArmy.size(); k++)
		{

			skeletonArmy[k]->update(deltaTime);
			
					   			 		  
			if (this->collisionCheck(this->player->getHbcenter(), this->player->getHbrad(), skeletonArmy[k]->getHbcenter(), skeletonArmy[k]->getHbrad()))
			{
				this->collidTimer = this->collidClock.getElapsedTime();
				//std::cout << this->player->getattacktype() << std::endl;
				/*if (this->player->getattacktype()==3)
				{
					this->skeletonArmy[k]->health->damage(30);
				}
				if (this->player->getattacktype() == 2)
				{
					this->skeletonArmy[k]->health->damage(60);
				}*/
				switch(this->player->getattacktype())
				{
				case 1: this->skeletonArmy[k]->health->damage(20 + this->score / 10); break;
					
				case 2 : this->skeletonArmy[k]->health->damage(65 + this->score / 10); break;

				case 3 : this->skeletonArmy[k]->health->damage(30 + this->score / 10); break;

					//this->skeletonArmy[k]->health->damage(this->player->getdamage() + this->score / 100);
				}



				///////////////////////////////////////
				//////////////DAMAGE///////////////////
				///////////////////////////////////////

				//std::cout << this->collidTimer.asSeconds() - this->collidTime.asSeconds() << std::endl;
				if (collidClock.getElapsedTime().asMilliseconds() > 700)
				{
					std::cout << "FUCKKKKKKKKKKKKKKKKKKKKKKKKK" << std::endl;
					this->player->health->damage(50 + score / 5);
					this->collidClock.restart();
				}


			}
			
		}
		/////////////////////////////////////////////////////minotaur///////////////////////////////////////////////////////////
		for (int k = 0; k < this->minotaurArmy.size(); k++)
		{

			minotaurArmy[k]->update(deltaTime);


			if (this->collisionCheck(this->player->getHbcenter(), this->player->getHbrad(), minotaurArmy[k]->getHbcenter(), minotaurArmy[k]->getHbrad()))
			{
				this->collidTimer = this->collidClock.getElapsedTime();
				//std::cout << this->player->getattacktype() << std::endl;
				/*if (this->player->getattacktype()==3)
				{
					this->skeletonArmy[k]->health->damage(30);
				}
				if (this->player->getattacktype() == 2)
				{
					this->skeletonArmy[k]->health->damage(60);
				}*/
				switch (this->player->getattacktype())
				{
				case 1: this->minotaurArmy[k]->health->damage(80 + this->score / 10); break;

				case 2: this->minotaurArmy[k]->health->damage(30 + this->score / 100); break;

				case 3: this->minotaurArmy[k]->health->damage(20 + this->score / 100); break;

					//this->skeletonArmy[k]->health->damage(this->player->getdamage() + this->score / 100);
				}



				///////////////////////////////////////
				//////////////DAMAGE///////////////////
				///////////////////////////////////////

				//std::cout << this->collidTimer.asSeconds() - this->collidTime.asSeconds() << std::endl;
				if (collidClock.getElapsedTime().asMilliseconds() > 700)
				{
					std::cout << "FUCKKKKKKKKKKKKKKKKKKKKKKKKK" << std::endl;
					this->player->health->damage(30 + score / 10);
					this->collidClock.restart();
				}


			}

		}
		/////////////////////////////////////////////////////////////////////////////////////////
		///////////////////////////////////BOSS////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////
		for (int k = 0; k < this->bossArmy.size(); k++)
		{

			bossArmy[k]->update(deltaTime);


			if (this->collisionCheck(this->player->getHbcenter(), this->player->getHbrad(), bossArmy[k]->getHbcenter(), bossArmy[k]->getHbrad()))
			{
				this->collidTimer = this->collidClock.getElapsedTime();
				//std::cout << this->player->getattacktype() << std::endl;
				/*if (this->player->getattacktype()==3)
				{
					this->skeletonArmy[k]->health->damage(30);
				}
				if (this->player->getattacktype() == 2)
				{
					this->skeletonArmy[k]->health->damage(60);
				}*/
				switch (this->player->getattacktype())
				{
				case 1: this->bossArmy[k]->health->damage(30 + this->score / 100); break;

				case 2: this->bossArmy[k]->health->damage(50 + this->score / 100); break;

				case 3: this->bossArmy[k]->health->damage(25 + this->score / 100); break;

					//this->skeletonArmy[k]->health->damage(this->player->getdamage() + this->score / 100);
				}



				///////////////////////////////////////
				//////////////DAMAGE///////////////////
				///////////////////////////////////////

				//std::cout << this->collidTimer.asSeconds() - this->collidTime.asSeconds() << std::endl;
				if (collidClock.getElapsedTime().asMilliseconds() > 1800-this->score)
				{
					std::cout << "FUCKKKKKKKKKKKKKKKKKKKKKKKKK" << std::endl;
					this->player->health->damage(150 + score / 100);
					this->collidClock.restart();
				}


			}

		}
				////////////////////////////////////////////////
				////////////////Collision Check////////////////
				///////////////////////////////////////////////

		///////////////////////////////////item///////////////////////////////////////////////////////
		for (int l = 0; l < this->item.size(); l++)
		{
			item[l]->update(deltaTime);
			if (this->collisionCheck(this->player->getHbcenter(), this->player->getHbrad(), item[l]->getHbcenter(), item[l]->getHbrad()))
			{
				this->player->health->damage((-500)-(this->score/10));
				delete this->item[l];

				this->item.erase(this->item.begin() + l);
				break;

			}

		}
		
		///////////////////////////////////item///////////////////////////////////////////////////////

		
	}
	
	else if (this->pause)//pause
	{

		this->pauseMenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}

}

void GameState::render(sf::RenderTarget* target)
{

	
	
	if (!target)
	{
		target = this->window;
	}
	target->setView(this->view);
	
	
	
	if (score < 400)target->draw(this->gamebg);
	else target->draw(this->gamebg2);

	
	
	if (this->player->getHealth() > 0)
	{
		



		//this->map.render(*target);
	   // target->draw(this->player->getSprite());
		//target->draw(this->skeleton.getSprite());
		this->player->render(*target);
		for (int i = 0; i < this->skeletonArmy.size(); i++)
		{
			skeletonArmy[i]->render(*target);
			skeletonArmy[i]->health->render(*target);

			if (skeletonArmy[i]->getHealth() <= 0)
			{
				delete this->skeletonArmy[i];

				this->skeletonArmy.erase(this->skeletonArmy.begin() + i);
				this->score += 10;
				break;

			}


		}
		for (int i = 0; i < this->minotaurArmy.size(); i++)
		{
			minotaurArmy[i]->render(*target);
			minotaurArmy[i]->health->render(*target);

			if (minotaurArmy[i]->getHealth() <= 0)
			{
				delete this->minotaurArmy[i];

				this->minotaurArmy.erase(this->minotaurArmy.begin() + i);
				this->score += 30;
				break;

			}


		}

		for (int i = 0; i < this->bossArmy.size(); i++)
		{
			bossArmy[i]->render(*target);
			bossArmy[i]->health->render(*target);

			if (bossArmy[i]->getHealth() <= 0)
			{
				delete this->bossArmy[i];

				this->bossArmy.erase(this->bossArmy.begin() + i);
				this->score += 50;
				break;

			}


		}

		for (int i = 0; i < this->item.size(); i++)
		{
			item[i]->render(*target);
			
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
	else
	{
		this->highscore->saveScore(this->playername, this->score);
		std::cout << "SAVEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << std::endl;
		target->draw(this->deadbg);
		if (this->returnClock.getElapsedTime().asSeconds() > 10)
		{
			this->returnClock.restart();
			endState();
		}
		
		//add BG 
		//endState();
		//target->draw(this->inputBox);

		//if (this->blink)//always true
		//{
		//	target->draw(this->cursor);
		//}

		//target->draw(this->playerName);
		//target->draw(this->inputName);
		//renderButton(*target);

	}
}

void GameState::updateButton()
{
	for (auto& it : this->buttons) // if there is any iterator remain in the buttons
	{
		it.second->update(this->mousePosWindow); //update() from button.cpp ==> update color of button and button states
	}
	
	//Quit the game
	
}

void GameState::renderButton(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target); //render() from button.cpp ==> buttonShape.draw and text.draw
	}


	//Position checking for placing stuff on the screen
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 30);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(20);
	std::stringstream position;
	position << this->mousePosView.x << " , " << this->mousePosView.y;

	mouseText.setString(position.str());
	target.draw(mouseText);

}


//name

void GameState::collectScore()
{
	this->highscore->saveScore(this->playername,this->score);
}

void GameState::updateCursor()
{
	this->cursorTime += this->cursorClock.restart().asSeconds();
	if (this->cursorTime >= 0.5)
	{
		cursorTime = 0;
		this->blink = !blink;
	}
	if (this->event->type == sf::Event::EventType::TextEntered)
	{

		if (lastchar != this->event->text.unicode && this->event->key.code == 8 && this->playerInput.length() > 0)
		{
			//std::cout << "wtf" << std::endl;
			this->lastchar = this->event->text.unicode;
			this->playerInput.erase(this->playerInput.length() - 1);
			this->playerName.setString(this->playerInput);
			this->cursor.setPosition(805 + this->playerName.getGlobalBounds().width + 1, 105);
		}
		//sf::Keyboard::Key
		if (lastchar != this->event->text.unicode && this->playerInput.length() < 15 && (this->event->text.unicode >= 'A' && this->event->text.unicode <= 'Z' || this->event->text.unicode >= 'a' && this->event->text.unicode <= 'z' || this->event->text.unicode >= '0' && this->event->text.unicode <= '9'))
		{
			//std::cout << "wtf" << std::endl;
			this->lastchar = this->event->text.unicode;
			this->playerInput += this->event->text.unicode;
			this->playerName.setString(playerInput);
			this->cursor.setPosition(805 + this->playerName.getGlobalBounds().width + 1, 105);
			std::cout << this->event->text.unicode << std::endl;
			//std::cout << this->playerInput << std::endl;
		}


	}
	if (this->event->type == sf::Event::EventType::KeyReleased && this->lastchar != ' ')
	{
		this->lastchar = ' ';
	}


}

void GameState::initInput()
{
	this->inputName.setFont(this->name);
	this->inputName.setCharacterSize(25);
	this->inputName.setOutlineColor(sf::Color::Black);
	this->inputName.setOutlineThickness(2.f);
	this->inputName.setFillColor(sf::Color::White);
	this->inputName.setPosition(sf::Vector2f(805, 80));
	this->inputName.setString("PlayerName ");
}

void GameState::initInputBox()
{
	this->inputBox.setSize(sf::Vector2f(300.f, 50.f));
	this->inputBox.setPosition(800.f, 100.f);
	this->inputBox.setFillColor(sf::Color(70, 70, 70, 200));
	this->inputBox.setOutlineThickness(3);
	this->inputBox.setOutlineColor(sf::Color(80, 10, 10, 250));
}

void GameState::initPlayername()
{
	this->playerName.setFont(this->name);
	this->playerName.setCharacterSize(30);
	this->playerName.setOutlineColor(sf::Color::Black);
	this->playerName.setOutlineThickness(1.f);
	this->playerName.setFillColor(sf::Color::White);
	this->playerName.setPosition(sf::Vector2f(805, 105));
}

