#include "Paddle.h"
#include <iostream>
Paddle::Paddle(Ogre::SceneManager* scMgr, SceneNode* SceneNode)
{
    this->mSceneManager = scMgr;
    mSceneNode = SceneNode;
    this->mEntity = mSceneManager->createEntity("cube.mesh");
    mEntity->setCastShadows(false);
    mSceneNode = mSceneManager->createSceneNode("paddle");
    mSceneNode->attachObject(mEntity);
    mSceneManager->getRootSceneNode()->addChild(mSceneNode);
    mSceneNode->setPosition(Ogre::Vector3(0.0f, 4.0f, 40.0f));
    mSceneNode->setScale(0.2f, 0.1f, 0.05f);    
    mSceneNode->getShowBoundingBox();    
    mSceneNode->_getWorldAABB();
}

Ogre::Vector3 Paddle::GetPosition()
{    
    mSceneNode->getPosition();
    return mSceneNode->getPosition();
}

void Paddle::MoveRight()
{
    mSceneNode->translate(Vector3(0.9, 0.0, 0));    
}

void Paddle::MoveLeft()
{
    mSceneNode->translate(Vector3(-0.9, 0.0, 0));
}

AxisAlignedBox Paddle::GetWorldAABB()
{    
    return mSceneNode->_getWorldAABB();
}
