#include "State.h"



State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->states = states;
	this->quit = false;
	this->pause = false;
	
	this->supportedKeys = supportedKeys; 

	this->keyTimeMax = 4.f;
	this->keyTime = 0.f;

}

State::~State()
{
}

//Accessor
const bool& State::getQuit() const
{
	// TODO: insert return statement here
	return this->quit;
}

const bool State::getKeytime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

/*void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
	{
		this->quit = true;
	}
}*/

void State::endState()
{
	this->quit = true;
	//std::cout << "End the STATE" << "\n";
}

void State::pauseState()
{
	this->pause = true;
}

void State::unpauseState()
{
	this->pause = false;
}

void State::updateKeytime(const float& deltaTime)
{
	if (this->keyTime < this->keyTimeMax) 
	{
		this->keyTime += 10.f *deltaTime;
	}
}

void State::updateMousePosition(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	
	if (view)
		this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	


	this->window->setView(this->window->getDefaultView());
}


