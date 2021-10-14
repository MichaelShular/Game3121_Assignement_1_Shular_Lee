#include "Ball.h"
#include <iostream>
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
    mNumLife = 5;
    mBallSpeed = 30.f;    
    mBallDirection = Vector3(-1, 0, -1);
    mStay = true;
    mSceneNode->getShowBoundingBox();    
    mSceneNode->_getWorldAABB();
}

Ball::~Ball()
{
}

Ogre::Vector3 Ball::GetPosition()
{
	return Ogre::Vector3();
}

void Ball::Reset()
{
    mScore = 0;
    mNumLife = 5;
    mStay = true;
    mBallDirection = Vector3(-1, 0, -1);
}

int Ball::GetScore()
{
    return mScore;
}

void Ball::SetStart()
{
    mStay = false;
}

void Ball::RemoveLife()
{
    --mNumLife;
}

int Ball::getNumberOfLife()
{
    return mNumLife;
}

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
                mBallDirection.z *= -1;
            //Right
            if (mSceneNode->getPosition().x > 65)
                mBallDirection.x *= -1;
            //Left
            if (mSceneNode->getPosition().x < -65)
                mBallDirection.x *= -1;
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
