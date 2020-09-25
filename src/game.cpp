#include "game.h"
#include "board.h"
#include <iostream>
#include <cmath>

// Ovdje dolazi vaš kod

Game::Game() : mWindow(sf::VideoMode(512, 400), "SFML mWindow")
{

    mRectangle.setSize(sf::Vector2f(512 - 5 * 2, 400));
    mRectangle.setOutlineColor(sf::Color::Red);
    mRectangle.setOutlineThickness(5);
    mRectangle.setPosition(5, 5);

    initPositions(1, 10);
}

void Game::run()
{

    sf::Clock clock;

    for (int t = 0; t < 3; ++t){

    initVelocity(200 + t * 100);
    sf::Time protekloVrijeme = sf::Time::Zero;
    sf::Time dt = sf::seconds(1.0/60.f);

    int level[] =
        {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1,
            3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
        };

    int d;
    bool e = false;

    buffer2.loadFromFile("Grenade.wav");
    sound2.setBuffer(buffer2);

    buffer1.loadFromFile("Glass_Break.wav");
    sound1.setBuffer(buffer1);


    while (mWindow.isOpen())
    {

        processEvents();
        protekloVrijeme += clock.restart();
        while (protekloVrijeme >= dt){
            protekloVrijeme -= dt;
            processEvents();
            int x = update(dt);

            for (int i = 0; i < mBall.size(); ++i){
                d = checkForCollisionsWithWalls(mBall[i].get(), dt, x);
                if (level[d] != 2)
                    level[d] = 4;

                checkForCollisionsWithBalls(mBall[i].get(), dt);
                e = checkSpace(mBall[i].get());


                mScore.addNoCompleted(n);
                mScore.update();

            }
        }
        map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 3);
        if (e && mGameOver > 0){
            initPositions2(1, 10);
            initVelocity(200 + t * 100);
        }
        render();
        mScore.getLevel(t+1);
        mScore.getLife(mGameOver);
        if (mScore.getScore() == 460 + t * 460)
            break;

    }

    }
}

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        switch(event.type){
            case sf::Event::Closed:
                mWindow.close();
            case sf::Event::KeyPressed:
                if( event.key.code == sf::Keyboard::Left)  mIsMovingLeft  = true;
                if( event.key.code == sf::Keyboard::Right) mIsMovingRight = true;
                break;
            case sf::Event::KeyReleased:
                if( event.key.code == sf::Keyboard::Left)  mIsMovingLeft  = false;
                if( event.key.code == sf::Keyboard::Right) mIsMovingRight = false;
                break;
        }
    }
}

int Game::update(sf::Time dt)
{
    if (Game::isNotGameOver() > 0){
        sf::Vector2f movement;
        for (int i = 0; i < mBall.size(); ++i){
            movement = mBall[i]->mVelocity;
            mBall[i]->mCircle.move(movement * dt.asSeconds());
        }


        if (mIsMovingLeft && leftRight > -200)
            leftRight += -1;
        if (mIsMovingRight && leftRight < 200)
            leftRight += 1;

        mIsMovingLeft = false;
        mIsMovingRight = false;

    }
    else{
        mScore.setGameOver();
    }
    return mBoard.update(leftRight * 5);
}

void Game::render()
{
    mWindow.clear();
    mWindow.draw(mRectangle);
    mWindow.draw(mBoard);
    mWindow.draw(map);
    mWindow.draw(mScore);
	// Treba iscrtati kuglice  !!!
    for (int i = 0; i < mBall.size(); ++i){
        mWindow.draw(*mBall[i]);
    }
    mWindow.display();
}

void Game::initPositions(std::size_t nBalls, float radius)
{
    std::uniform_real_distribution<float> uniform_dist(32 * 3 + radius, 400 - 145);  // smanjio malo varijancu
    std::vector<sf::Vector2f> v;
    for (int i = 0; i < nBalls; ++i){
		double vx = uniform_dist(mRand);
		double vy = uniform_dist(mRand);
        //std::cout << vx << " , " << vy << std::endl;
		// Morate rezati poziciju da bude unutar pravokutnika i da se kuglice ne sijeku/dodiruju
        v.push_back (sf::Vector2f(vx,vy));
	}
//    Ball b;
//    b.Ball::setRadius(radius);
    for (int i = 0; i < nBalls; ++i){
//        b.sf::Transformable::setPosition(v[i]);
//        mBall.push_back(std::unique_ptr<Ball>(&b));  // NE MOŽE SE unique_ptr koristiti sa statički alociranim 
		                                             // objektom
	    mBall.push_back(std::unique_ptr<Ball>(new Ball)); 	
        mBall.back()->mCircle.setPosition(v[i]);
        mBall.back()->setRadius(radius);
    }
}

void Game::initPositions2(std::size_t nBalls, float radius){
    std::uniform_real_distribution<float> uniform_dist(32 * 3 + radius, 400 - 200);  // smanjio malo varijancu
    std::vector<sf::Vector2f> v;
    for (int i = 0; i < nBalls; ++i){
        double vx = uniform_dist(mRand);
        double vy = uniform_dist(mRand);
        // Morate rezati poziciju da bude unutar pravokutnika i da se kuglice ne sijeku/dodiruju
        v.push_back (sf::Vector2f(vx,vy));
    }
    for (int i = 0; i < nBalls; ++i){
        mBall.pop_back();

        mBall.push_back(std::unique_ptr<Ball>(new Ball));
        mBall.back()->mCircle.setPosition(v[i]);
        mBall.back()->setRadius(radius);
    }

}

void Game::initVelocity(float maxVel)
{
    std::uniform_real_distribution<float> uniform_dist(-maxVel/sqrt(2), maxVel/sqrt(2));
    float a, b;
    for (int i = 0; i < mBall.size(); ++i){
        a = 0.f;
        b = 0.f;

        while (std::abs(a) < maxVel/sqrt(2) * 3.f / 4 || std::abs(b) < maxVel/sqrt(2) * 3.f / 4){
            a = uniform_dist(mRand);
            b = uniform_dist(mRand);
        }
        mBall[i]->mVelocity.x = a;
        mBall[i]->mVelocity.y = b;
    }

}

int Game::checkForCollisionsWithWalls(Ball * pball, sf::Time dt, int x1)
{
    if ((pball->mCircle.getPosition().x <= (pball->getRadius() - 5)) || (pball->mCircle.getPosition().x >= (512 - 5 - 2 * pball->getRadius()))){
        pball->mVelocity.x = -pball->mVelocity.x;
    }

    if ((pball->mCircle.getPosition().y >= (360 - 15 - 10 - pball->getRadius())) && ((pball->mCircle.getPosition().x >= 200 - 5 + x1) && (pball->mCircle.getPosition().x <= 300 + 5 + x1))){
        pball->mVelocity.y = -pball->mVelocity.y;
    }

    if (i == 0){
        if (pball->mCircle.getPosition().y <= 32 * 3 + 5){
            sound2.play();
            pball->mVelocity.y = -pball->mVelocity.y;
            a = (int)round(pball->mCircle.getPosition().x / 512.f * 16);
            c[a] = 2;
            ++i;
            ++n;


        }
    }
    else{
        for (int j = 0; j < 16; ++j){
            if (pball->mCircle.getPosition().x >= j / 16.f * 512 && pball->mCircle.getPosition().x <= j / 16.f * 512 + 32){
            if (c[j] == 0){
                if (pball->mCircle.getPosition().y <= 32 * 0 + 5)
                {
                    pball->mVelocity.y = -pball->mVelocity.y;
                    if (j == 2 && pball->mVelocity.x > 0 || j == 4 && pball->mVelocity.x < 0 && x == 0){
                        ++l[3];
                        if (l[3] == 1 || l[3] == 2){
                            sound1.play();
                            return 16 * 3;
                        }
                        ++n;
                        ++x;
                        sound2.play();
                        return 3;
                    }
                    if (j == 11 && pball->mVelocity.x > 0 || j == 13 && pball->mVelocity.x < 0 && y == 0){
                        ++l[12];
                        if (l[12] == 1 || l[12] == 2){
                            sound1.play();
                            return 16 * 3;
                        }
                        ++n;
                        ++y;
                        sound2.play();
                        return 12;
                    }
                    return 16 * 3;
                }
            }
            else if (c[j] == 1){
                if (pball->mCircle.getPosition().y <= 32 * 1 + 5)
                {
                        pball->mVelocity.y = -pball->mVelocity.y;
                        ++l[j];
                        if (l[j] == 1 || l[j] == 2){
                            sound1.play();
                            return 16 * 3;
                        }

                        sound2.play();
                        a = j;
                        c[a] = 0;
                        ++n;

                        return a + (c[a] +1 - 1) * 16;
                }
            }
            else if (c[j] == 2){
                if (pball->mCircle.getPosition().y <= 32 * 2 + 5)
                {
                        pball->mVelocity.y = -pball->mVelocity.y;
                        ++k[j];
                        if (k[j] == 1){
                            sound1.play();
                            return 16 * 3;
                        }

                        if (j == 3 || j == 12){
                            sound1.play();
                            return 16 * 3;
                        }

                        sound2.play();
                        a = j;
                        c[a] = 1;
                        ++n;
                        return a + (c[a] +1 - 1) * 16;
                }

            }
            else if (c[j] == 3){
                if (pball->mCircle.getPosition().y <= 32 * 3 + 5){
                    sound2.play();
                    pball->mVelocity.y = -pball->mVelocity.y;
                    a = j;
                    c[a] = 2;
                    ++n;
                    return a + (c[a] + 1 - 1) * 16;
                }
            }
        }
        }
    }


    return a + (3 - 1) * 16;
}

void Game::checkForCollisionsWithBalls(Ball *pball, sf::Time dt) const
{
    sf::Vector2f x1 = pball->mCircle.getPosition();
    sf::Vector2f v1 = pball->mVelocity;

    for (int i = 0; i < mBall.size(); ++i){
       sf::Vector2f x2 = mBall[i]->mCircle.getPosition();
       sf::Vector2f v2 = mBall[i]->mVelocity;

       sf::Vector2f a = x1 - x2;
       if (sqrt(a.x * a.x + a.y * a.y) < 2*(pball->getRadius()+5) && pball != mBall[i].get()){

           pball->mVelocity = v1 - (x1-x2)*((v1-v2).x*(x1-x2).x + (v1-v2).y*(x1-x2).y)/((x1-x2).x*(x1-x2).x + (x1-x2).y*(x1-x2).y);
           mBall[i]->mVelocity = v2 - (x2-x1)*((v2-v1).x*(x2-x1).x + (v2-v1).y*(x2-x1).y)/((x1-x2).x*(x1-x2).x + (x1-x2).y*(x1-x2).y);
       }
    }
}

bool Game::checkSpace(Ball *pball)
{
    if (pball->mCircle.getPosition().y > 380){
            --mGameOver;
            return true;
    }
    return false;
}

int Game::isNotGameOver() const
{
    return mGameOver;
}


