#pragma once

#include "State.h"
#include "Button.h"
#include<vector>
#include<algorithm>
#include <fstream>
using namespace std;
class HighScores :
	public State
{
public:
	HighScores(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~HighScores();
	void updateButton();
	void updateInput(const float& deltaTime);//update input (any subclass) state
	void update(const float& deltaTime);//update input and  others (any subclass)
	void render(sf::RenderTarget* target = nullptr);//draw the updated object to the window (any subclass)
	void saveScore(std::string name, unsigned long score);
	void renderButton(sf::RenderTarget& target);
private:
	
	sf::Texture backgroundTexture;
	sf::RectangleShape backGround;
	sf::RectangleShape scoreBoard;
	sf::Font font;
	sf::Text nameText[5];
	sf::Text scoreText[5];
	std::ifstream scorefile;
	std::map<std::string, Button*> buttons;
	
	void initializeButton();
	void textModify();
	void initializeKeybinds() ;
	
	

};
