#pragma once
#include <SFML/Graphics.hpp>

class Score : public sf::Drawable, public sf::Transformable{
public:
    Score();
    // Dodaj broj obrisanih i aktualiziraj rezultat.
    void addNoCompleted(int n);
    // Postavi Game over string
    void setGameOver();
    // Aktualizacija ispisa
    void update();

    int getScore();

    void getLevel(int n);
    void getLife(int n);
private:
    sf::Font mFont;
    sf::Text mScoreText;
    sf::Text mGameOverText;
    sf::Text mLevelText;
    sf::Text mLifeText;
    int mScore = 0;
    // Eventualne dodatne varijable dolaze ovdje

    // Iscrtavanje.
    void draw(sf::RenderTarget & target, sf::RenderStates states) const override;
};
