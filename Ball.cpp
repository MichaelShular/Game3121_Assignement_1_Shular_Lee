#include "Ball.h"
#include <iostream>
Ball::Ball(Ogre::SceneManager* scMgr, SceneNode* SceneNode, Paddle* _pad)
{
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
    mBallSpeed = 30.f;    
    mBallDirection = Vector3(-1, 0, -1);
    mStay = true;    
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
}

void Ball::RemoveLife()
{
}

void Ball::SetBallDir()
{
}

void Ball::getNumberOfLife()
{
}

void Ball::Update(Ogre::Real real)
{    
    if (!mStay)
    {
        mSceneNode->translate(mBallDirection * mBallSpeed * real);
        //Top
        if (mSceneNode->getPosition().z < -65)
            mBallDirection.z *= -1;
        //Right
        if (mSceneNode->getPosition().x > 65)
            mBallDirection.x *= -1;
        //Left
        if (mSceneNode->getPosition().x < -65)
            mBallDirection.x *= -1;
        //Bottom
        if (mSceneNode->getPosition().z > 65)
            mBallDirection.z *= -1;
    }
    else
    {
        mSceneNode->setPosition(pad->GetPosition().x, pad->GetPosition().y, 34.0f);
    }
}

void Ball::Moving()
{
}

void Ball::CollisionDetection()
{

}
