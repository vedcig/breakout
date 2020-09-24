#include "board.h"

Board::Board()
{
    mBridge.setOutlineColor(sf::Color::Red);
    mBridge.setOutlineThickness(5);
    mBridge.setSize(sf::Vector2f(100, 15));
    mBridge.setPosition(200,360);
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    //target.draw(mText, states);
    target.draw(mBridge, states);
}

int Board::update(int x){

    mBridge.setPosition(sf::Vector2f(200, 360) + sf::Vector2f(x, 0.f));

    return x;
}



