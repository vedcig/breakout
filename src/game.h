#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <memory>
#include <random>

#include "ball.h"
#include "board.h"
#include "tilemap.h"
#include "score.h"

class Game{
public:
    Game();
    void run();

    int leftRight = 0;
    int a = 16;
    int c[16] = {3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3};
    int i = 0;
    int k[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int l[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int n = 0;
    int x = 0;
    int y = 0;

    int isNotGameOver() const;

    sf::SoundBuffer buffer1;
    sf::SoundBuffer buffer2;

    sf::Sound sound1;
    sf::Sound sound2;


private:

    sf::RenderWindow mWindow;
    // Vanjski okvir
    Board mBoard;

    TileMap map;

    sf::RectangleShape mRectangle;
    // Kugle.
    std::vector<std::unique_ptr<Ball> > mBall;

    Score mScore;

    int mGameOver = 3;

    bool checkSpace(Ball * pball);




    float mDx;
    float mDy;

    bool mIsMovingLeft = false;
    bool mIsMovingRight = false;

    // Za generiranje slučajnih brojeva
    std::default_random_engine mRand;

    void processEvents();
    int update(sf::Time dt);
    void render();

    // Postavi kugle u inicijalne pozicije
    void initPositions(std::size_t nBalls, float radius);
    void initPositions2(std::size_t nBalls, float radius);
    // Daj kuglama inicijalne brzine. maxVel je maksimalna moguća brzina. 
    void initVelocity(float maxVel);

    // Provjeri koliziju sa zidom i promjeni brzinu kuglice na adekvatan način
    int checkForCollisionsWithWalls(Ball * pball, sf::Time dt, int x1);
    // Provjeri koliziju kuglice pball s ostali kuglicama i promjeni brzine 
    // na odgovarajući način.
    void checkForCollisionsWithBalls(Ball * pball, sf::Time dt) const;


};



