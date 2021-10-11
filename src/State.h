#pragma once
#include "Button.h"
#include"Skeleton.h"
#include"Minotaur.h"

class State
{
private:

protected:
	sf::RenderWindow* window;

	std::stack<State*>* states;

	std::map<std::string, int> keybinds;

	std::map<std::string, int>* supportedKeys;
	bool quit;
	bool pause;
	float keyTime;
	float keyTimeMax;

	sf::Vector2i mousePosWindow;
	sf::Vector2i mousePosScreen;
	sf::Vector2f mousePosView;
	//resources
	std::map<std::string, sf::Texture> textures;
	//function
	virtual void initializeKeybinds() = 0;

public:

	
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	//Accessor
	const bool& getQuit() const;
	const bool getKeytime();

	//virtual void checkForQuit();
	
	 void endState();
	 void pauseState();
	 void unpauseState();

	virtual void updateInput(const float& deltaTime) = 0;//update input (any subclass) state
	virtual void updateKeytime(const float& deltaTime);
	virtual void updateMousePosition(sf::View *view = NULL);
	virtual void update(const float& deltaTime) = 0;//update input and  others (any subclass)
	virtual void render(sf::RenderTarget* target = nullptr) = 0;//draw the updated object to the window (any subclass)

};

