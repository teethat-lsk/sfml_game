#include "Deadmenu.h"

Deadmenu::Deadmenu(sf::RenderWindow& window, sf::Font& font, sf::Event* event)
:font(font)
{
	this->blink = true;
	this->event = event;
	this->bgTexture.loadFromFile("Resources/Images/dead.png");
	this->cursorTime = this->cursorClock.getElapsedTime().asSeconds();
	//background
	this->background.setTexture(&this->bgTexture);
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x),
		static_cast<float>(window.getSize().y)
	));

	/*this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x) / 4.f,
		static_cast<float>(window.getSize().y) / 2.f

	));*/

	this->container.setSize(sf::Vector2f(500,100));
	this->container.setFillColor(sf::Color(20, 20, 20, 50));
	this->container.setPosition(
		static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f,
		static_cast<float>(window.getSize().y) / 2.f - this->container.getSize().y / 2.f);


	this->text.setFont(font);
	this->text.setFillColor(sf::Color(255, 255, 255, 255));
	this->text.setCharacterSize(30);
	this->text.setString("Enter YOUR NAME");
	this->text.setPosition(this->container.getPosition().x + this->container.getSize().x / 2.f - this->text.getGlobalBounds().width / 2.f,
		this->container.getPosition().y + 20);

	this->inputName.setFont(font);
	this->inputName.setCharacterSize(25);
	this->inputName.setOutlineColor(sf::Color::Black);
	this->inputName.setOutlineThickness(2.f);
	this->inputName.setFillColor(sf::Color::White);
	this->inputName.setPosition(sf::Vector2f(805, 80));
	this->inputName.setString("PlayerName ");

	this->inputBox.setSize(sf::Vector2f(300.f, 50.f));
	this->inputBox.setPosition(800.f, 100.f);
	this->inputBox.setFillColor(sf::Color(70, 70, 70, 200));
	this->inputBox.setOutlineThickness(3);
	this->inputBox.setOutlineColor(sf::Color(80, 10, 10, 250));

	this->playerName.setFont(font);
	this->playerName.setCharacterSize(30);
	this->playerName.setOutlineColor(sf::Color::Black);
	this->playerName.setOutlineThickness(1.f);
	this->playerName.setFillColor(sf::Color::White);
	this->playerName.setPosition(sf::Vector2f(805, 105));

}

Deadmenu::~Deadmenu()
{

	/*auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}*/

}

//const bool Deadmenu::isButtonPressed(std::string key)
//{
//	return this->buttons[key]->isPressed();
//}

//void Deadmenu::addButton(const std::string key, float y, const std::string text)
//{
//	float width = 300;
//	float height = 100;
//	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - 150;
//
//	this->buttons[key] = new Button(x, y, width, height,
//		&this->font, text, 30,
//		sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent, sf::Color(70, 70, 70, 150), sf::Color(255, 255, 255, 255), sf::Color(255, 255, 255, 255));
//}

void Deadmenu::update(const sf::Vector2i& mousePosWindow)
{
	
	
	updateCursor();
}

void Deadmenu::render(sf::RenderTarget* target)
{
	target->draw(this->background);
	target->draw(this->container);
	
	target->draw(this->text);
	
	
	target->draw(this->inputBox);

	if (this->blink)//always true
	{
		target->draw(this->cursor);
	}

	target->draw(this->playerName);
	target->draw(this->inputName);
}

void Deadmenu::updateCursor()
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
