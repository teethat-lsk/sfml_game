#pragma once

#include"State.h"
#include "itembot.h"
#include"Minotaur.h"
#include"HighScores.h"
#include"Boss.h"
#include "PauseMenu.h"
#include <math.h>



class GameState :
	public State
{
private:
	PauseMenu* pauseMenu;
	
	
	sf::Event* event;
	Player* player;
	Skeleton* skeleton;
	itembot* itm;
	Minotaur* minotaur;
	HighScores* highscore;
	Boss* boss;
	//Enemy* enemy;
	//Skeleton* skeleton;
	sf::View view;
	sf::Font font;
	sf::Sprite hpBar;
	
	//TileMap map;
	
	//function
	void initializeKeybinds(); 
	void initializeFont();
	void initializeTexture();
	void initializePauseMenu();
	void initializeCharacters();
	void initializeView();
	void spawnEnemy();
	void moveEnemy(const float& deltaTime);
	void initializeDeadMenu();
	const bool collisionCheck(sf::Vector2f center1, sf::Vector2f rad1, sf::Vector2f center2, sf::Vector2f rad2) const;
	

	
	 int enemyCount;
	 int maxEnemy;
	 

	 std::vector<Skeleton*> skeletonArmy;
	 std::vector<itembot*> item;
	 std::vector<Minotaur*> minotaurArmy;
	 std::vector<Boss*> bossArmy;
	 
	 //std::vector< Enemy* > enemyArmy;
	
	

	 sf::Clock spawnClock; 
	 sf::Clock collidClock;
	 sf::Clock attackClock;
	 float attackTime;
	 sf::Time spawnTimer;
	 sf::Time collidTime;
	 sf::Time timer;
	 sf::Time collidTimer;
	 sf::Clock returnClock;
	 sf::Clock itemClock;
	 sf::Clock minoClock;
	 sf::Clock bossClock;
	
	
	 float cursorTime;
	 char lastchar;
	 bool blink;
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
	
	 sf::Font name;
	 sf::Music music;
	 std::map<std::string, Button*> buttons;
	 
	 sf::Text scoretext;
	 long score = 0;

	 


	 sf::RectangleShape gamebg;  sf::Texture gamebgtex;
	 sf::RectangleShape gamebg2;  sf::Texture gamebgtex2;
	 sf::RectangleShape deadbg;	 sf::Texture deadbdtex;



public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states,sf::String playername,sf::Event* event );
	virtual ~GameState();


	

	//function

	void updateView(const float& deltaTime);
	void updatePauseMenuButtons();
	void updateInput(const float& deltaTime);
	void updatePlayerInput(const float& deltaTime);
	void update(const float& deltaTime);
	void render(sf::RenderTarget* target= nullptr );

	void updateButton();
	void renderButton(sf::RenderTarget& target);
	
	
	void collectScore();
	void updateCursor();
	void initInput();
	void initInputBox();
	void initPlayername();
	void initButton();
	void initbg(); 
	
};
