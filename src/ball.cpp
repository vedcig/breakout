#include "game.h"

// Ovdje dolazi vaš kod.

Ball::Ball()
{
    mCircle.setOutlineColor(sf::Color::Red);
    mCircle.setOutlineThickness(5);

}
void Ball::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //target.draw(mText, states);
    target.draw(mCircle, states);
}
