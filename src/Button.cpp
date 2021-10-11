#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text,unsigned textSize,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor, 
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color)
{
	this->buttonState = BTN_IDLE;

	this->buttonShape.setPosition(sf::Vector2f(x, y));
	this->buttonShape.setSize(sf::Vector2f(width, height));
	this->buttonShape.setFillColor(this->idleColor);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Red);
	this->text.setCharacterSize(textSize);
		
	this->text.setPosition(
		this->buttonShape.getPosition().x +	(this->buttonShape.getGlobalBounds().width / 2.f)   - (this->text.getGlobalBounds().width/2.f ),
		this->buttonShape.getPosition().y +	(this->buttonShape.getGlobalBounds().height / 2.f)  - (this->text.getGlobalBounds().height/2.f));

	//BUG : text.getGlobalBounds() is always 0  ????  solved:  call initializeFornt() in MainMenuState

	//std::cout << this->text.getGlobalBounds().width;
	
	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	
}

Button::~Button()
{
}

//accesser
const bool Button::isPressed() const
{
	if(this->buttonState==BTN_ACTIVE)
	return true;


	return false;
}



void Button::update(const sf::Vector2i& mousePosWindow)
{
	//update bool for hover and active button

	// Idle
		this->buttonState = BTN_IDLE;
	
	//Hover
	if (this->buttonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosWindow)))
	{
		this->buttonState = BTN_HOVER;
	
	// Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}
	switch (this->buttonState)
	{
	case BTN_IDLE :
		this->buttonShape.setFillColor(this->idleColor);
		this->text.setFillColor(this->textIdleColor);
		//this->buttonShape.setOutlineColor(this->outlineIdleColor);
		break;
	case BTN_HOVER:
		this->buttonShape.setFillColor(this->hoverColor);
		this->text.setFillColor(this->textHoverColor);
		//this->buttonShape.setOutlineColor(this->outlineHoverColor);
		break;
	case BTN_ACTIVE:
		this->buttonShape.setFillColor(this->activeColor);
		this->text.setFillColor(this->textActiveColor);
		//this->buttonShape.setOutlineColor(this->outlineActiveColor);
		break;
	default:
		this->buttonShape.setFillColor(sf::Color::Red);
		this->text.setFillColor(sf::Color::Blue);
		//this->buttonShape.setOutlineColor(sf::Color::Green);
		break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->buttonShape);
	target.draw(this->text);
}
