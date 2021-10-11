#include "Enemy.h"

Enemy::Enemy(float x, float y, sf::Texture& texture_sheet)
{

}

Enemy::~Enemy()
{

}


void Enemy::render(sf::RenderTarget& target)
{
	target.draw(this->sprite); //target = window => target->draw = window->draw
	if (this->hitboxComponent)
		this->hitboxComponent->render(target);
}


const sf::Vector2f& Enemy::getHitboxPosition() const
{
	return this->hitboxComponent->getPosition();
	// TODO: insert return statement here
}

const sf::FloatRect Enemy::getHitboxGlobalBound() const
{
	return this->hitboxComponent->getGlobalBound();
}








