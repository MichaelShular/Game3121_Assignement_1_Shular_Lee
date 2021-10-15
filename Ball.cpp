#include "Ball.h"
#include <iostream>

/// The defualt conconstructor used for setting defualt settings of the ball object
/// 
/// 
/// @param: a SceneManager
/// @param: a SceneNode
/// @param: a paddle class object 
Ball::Ball(Ogre::SceneManager* scMgr, SceneNode* SceneNode, Paddle* _pad)
{
    mScore = 0;
	this->mSceneManager = scMgr;
    mSceneNode = SceneNode;
    this->mEntity = mSceneManager->createEntity("sphere.mesh");
    mEntity->setCastShadows(false);
    mSceneNode = mSceneManager->createSceneNode("ball");
    mSceneNode->attachObject(mEntity);
    mSceneManager->getRootSceneNode()->addChild(mSceneNode);
    mSceneNode->setPosition(Ogre::Vector3(0.0f, 4.0f, 34.0f ));
    mSceneNode->setScale(0.03f, 0.03f, 0.03f);
    pad = _pad;
    mNumLife = 3;
    mBallSpeed = 30.f;    
    mBallDirection = Vector3(-1, 0, -1);
    mStay = true;
    mSceneNode->getShowBoundingBox();    
    mSceneNode->_getWorldAABB();
}

/// Used to get the position of the ball.
/// 
/// @returns a vector3.
Ogre::Vector3 Ball::GetPosition()
{
	return Ogre::Vector3();
}

/// Used to reset aspects of the game. 
/// 
/// Resets the score, number of lives, set balls position above paddle and the direction of ball.
void Ball::Reset()
{
    mScore = 0;
    mNumLife = 3;
    mStay = true;
    mBallDirection = Vector3(-1, 0, -1);
}

/// Used to get the game's current score. 
/// 
/// @returns a int which is the current score of the game.  
int Ball::GetScore()
{
    return mScore;
}

/// Used to set state of ball to false.
/// 
/// This bool is used to allow the if statement in update to allow movment. 
void Ball::SetStart()
{
    mStay = false;
}

/// Used to decrease the amount of lives left.
void Ball::RemoveLife()
{
    --mNumLife;
}

/// Used to get the player's current amount of lives. 
/// 
/// @returns a int which is the current amount of lives that the player has. 
int Ball::getNumberOfLife()
{
    return mNumLife;
}

/// Controls how the ball updates each frame.
/// 
/// 
/// @param:
void Ball::Update(Ogre::Real real)
{
    if (mNumLife <= 0)
    {

    }
    else {
        if (!mStay)
        {
            //Paddle Collision
            // Paddle size Vector3(20, 10, 5)
            // ball Size Vector3(6, 6, 6)
            AxisAlignedBox aab = mSceneNode->_getWorldAABB().intersection(pad->GetWorldAABB());
            if (!aab.isNull())
            {
                if (mSceneNode->getPosition().x > pad->GetPosition().x + 10
                    || mSceneNode->getPosition().x < pad->GetPosition().x - 10)
                    mBallDirection.x *= -1;
                mBallDirection.z *= -1;
                ++mScore;
            }
            //Wall Collision

            //Moving
            mSceneNode->translate(mBallDirection * mBallSpeed * real);
            //Top
            if (mSceneNode->getPosition().z < -45)
            {
                mBallDirection.z *= -1;
                mSceneNode->setPosition(
                    Vector3(mSceneNode->getPosition().x, mSceneNode->getPosition().y, mSceneNode->getPosition().z + mBallSpeed * real));
                
            }
            //Right
            if (mSceneNode->getPosition().x > 65)
            {
                mBallDirection.x *= -1;
                mSceneNode->setPosition(
                    Vector3(mSceneNode->getPosition().x - (mBallSpeed * real), mSceneNode->getPosition().y, mSceneNode->getPosition().z));
            }
                
            //Left
            if (mSceneNode->getPosition().x < -65)
            {
                mSceneNode->setPosition(
                    Vector3(mSceneNode->getPosition().x + (mBallSpeed * real), mSceneNode->getPosition().y, mSceneNode->getPosition().z));
                mBallDirection.x *= -1;
            }
            //Bottom
            if (mSceneNode->getPosition().z > 50)
            {
                RemoveLife();
                mBallDirection = Vector3(-1, 0, -1);
                mStay = true;
            }
        }
        else
        {
            mSceneNode->setPosition(pad->GetPosition().x, pad->GetPosition().y, 34.0f);
        }
    }
}
