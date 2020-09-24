#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

class Board : public sf::Drawable, public sf::Transformable {
public:
    Board();

    int update(int x);

    float mVelocity;

    sf::RectangleShape mBridge;

private:

    void draw (sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // BOARD_H
