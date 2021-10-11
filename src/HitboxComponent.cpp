#include "HitboxComponent.h"



HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	:sprite(sprite),offsetX(offset_x),offsetY(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offsetX, this->sprite.getPosition().y + offsetY);
	this->hitbox.setSize(sf::Vector2f(width,height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	/*this->hitbox.setOutlineColor(sf::Color::Green);
	this->hitbox.setOutlineThickness(1.5f);*/
}

HitboxComponent::~HitboxComponent()
{
}

bool HitboxComponent::checkintersect(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offsetX, this->sprite.getPosition().y + offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
const sf::Vector2f& HitboxComponent::getPosition() const
{
	return this->hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::getGlobalBound() 
{
	return this->hitbox.getGlobalBounds();
}

sf::Vector2f HitboxComponent::getHbcenter()
{
	return sf::Vector2f(this->hitbox.getPosition().x+this->hitbox.getSize().x/2, 
						this->hitbox.getPosition().y + this->hitbox.getSize().y /2);
}

sf::Vector2f HitboxComponent::getHbrad()
{
	return sf::Vector2f(this->hitbox.getSize().x / 2, this->hitbox.getSize().y / 2);
}



