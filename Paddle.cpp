#include "Paddle.h"
#include <iostream>


/// The defualt conconstructor used for setting default settings for paddle object
/// 
/// @param: a SceneManager
/// @param: a SceneNode
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
/// Used to get the position of the paddle.
/// 
/// @returns a vector3.

Ogre::Vector3 Paddle::GetPosition()
{
    return mSceneNode->getPosition();
}

/// Moves the paddle to the right.
/// 
/// First checks if the player is less then certian X postion and if it's true allow
/// to translate right. 
void Paddle::MoveRight()
{ 
    // Paddle size Vector3(20, 10, 5)
    if(mSceneNode->getPosition().x < 65 - 10)
        mSceneNode->translate(Vector3(0.9, 0.0, 0));    
}

/// Moves the paddle to the left.
/// 
/// First checks if the player is greater then certian X postion and if it's true allow
/// to translate left. 
void Paddle::MoveLeft()
{
    if (mSceneNode->getPosition().x > -65 + 10)
        mSceneNode->translate(Vector3(-0.9, 0.0, 0));
}

/// Get Paddle's world AABB box. 
/// 
/// The Paddle's AABB box will be used to check if it collides with the Ball's AABB box.
/// @returns Paddles's world AABB box.
AxisAlignedBox Paddle::GetWorldAABB()
{
    return mSceneNode->_getWorldAABB();
}
