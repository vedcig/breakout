#include "score.h"
#include <cstdlib>
#include <iostream>

Score::Score()
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
   // Vaš kod dolazi ovdje
    mScoreText.setFont(mFont);
    mScoreText.setPosition(400, 300);
    mScoreText.setFillColor(sf::Color::Red);
    mGameOverText.setFont(mFont);
    mGameOverText.setPosition(200, 200);
    mGameOverText.setFillColor(sf::Color::Red);

    mLevelText.setFont(mFont);
    mLevelText.setPosition(50, 350);
    mLevelText.setFillColor(sf::Color::Red);

    mLifeText.setFont(mFont);
    mLifeText.setPosition(50, 300);
    mLifeText.setFillColor(sf::Color::Red);
}

int Score::getScore()
{
    return mScore;
}

void Score::getLevel(int n)
{
    if (n == 1)
        mLevelText.setString("1. nivo");
    else if (n == 2)
        mLevelText.setString("2. nivo");
    else
        mLevelText.setString("3. nivo");
}

void Score::getLife(int n)
{
    if (n == 3)
        mLifeText.setString("3");
    else if (n == 2)
        mLifeText.setString("2");
    else if (n == 1)
        mLifeText.setString("1");
    else
        mLifeText.setString("0");
}

void Score::addNoCompleted(int n)
{
  // Vaš kod.
  mScore = 10 * n;
}

void Score::setGameOver()
{
  // Vaš kod.
  mGameOverText.setString(("Game over"));
}

void Score::update()
{
  // Vaš kod.
  sf::String string = "";
  if ((mScore/10)/10)
    string += (char)('0' + (mScore/10)/10);
  if (mScore != 0)
    string += (char)('0' + (mScore/10)%10);
  string += "0";
  mScoreText.setString(sf::String (string));
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  // Vaš kod.
  target.draw(mScoreText, states);
  target.draw(mGameOverText, states);
  target.draw(mLevelText, states);
  target.draw(mLifeText, states);
}
