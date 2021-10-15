//Assignment_1_ShularLee
//You should see the same scene as seen earlier,
//but this time, the instance of Sinbad moves right and you can't move the camera or
//close the application with the Escape key.To close the application, click the X button
//on the console windows, or if you started the application from a console, you can
//use CTRL + C.

#include <iostream>
#include "Ogre.h"
#include "OgreApplicationContext.h"
#include "OgreInput.h"
#include "OgreRTShaderSystem.h"
#include "OgreFrustum.h"
#include "OgreTrays.h"
#include "OgreTimer.h"
#include "Ball.h"
#include "Paddle.h"
#include "UI.h"



using namespace Ogre;
using namespace OgreBites;

class Updater : public Ogre::FrameListener
{
private:
    Ogre::SceneNode* _sceneNode;
    UI* _UIElements;
    Ball* _ball;
    Ogre::SceneNode* _camNode;
    Ogre::Timer timer; 
    float _movementspeed;
    float _mousespeed;
    float mPausedTime;
public:

    Updater(Ball* ball, Ogre::SceneNode* camNode, UI* UIElements)
    {
        _ball = ball;
        _UIElements = UIElements;
        _camNode = camNode;
        _movementspeed = 200.0f;
        _mousespeed = 0.002f;
        
    }

    bool frameStarted(const Ogre::FrameEvent& evt)
    {      
        _ball->Update(evt.timeSinceLastFrame);
        _UIElements->setLives(Ogre::StringConverter::toString(_ball->getNumberOfLife()));
        _UIElements->setScore(Ogre::StringConverter::toString(_ball->GetScore()));
        
        
        if (_ball->getNumberOfLife() <= 0 )
        {
            _UIElements->showResetButton();
            _UIElements->setTime(Ogre::StringConverter::toString(mPausedTime));

            if (_UIElements->getReset() == true) {
                _ball->Reset();
                timer.reset();
                _UIElements->hideResetButton();
            }
        }
        else {
            _UIElements->setTime(Ogre::StringConverter::toString(timer.getMilliseconds() / 1000));
            mPausedTime = timer.getMilliseconds() / 1000;
        }

        return true;
    }
};

class Game
    : public ApplicationContext
    , public InputListener
{
private:
    Ogre::FrameListener* FrameListener;
    OgreBites::TrayListener myTrayListener;
    OgreBites::TrayManager* mTrayMgr;
    OgreBites::TrayManager* mButtonTrayMgr;
    SceneNode* SinbadNode;    
    SceneManager* scnMgr;
    Root* root;
    Paddle* paddle;
    Ball* ball;
    UI* UIElements;
    
    
public:
    Game();
    virtual ~Game() {}
    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    void createScene();
    void createCamera();
    void createFrameListener();
    void createTrayListener();
};

Game::Game()
    : ApplicationContext("week3-5-FrameListenerDemo")
{
}

Ogre::Real x = 0.0, y = 0.0, z = 0.0;

void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    root = getRoot();    
    scnMgr = root->createSceneManager();
    
    /*framelistener = new FrameListener();
    root->addFrameListener(framelistener);*/
    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
    createScene();    
    createCamera();
    createTrayListener();
    createFrameListener();
}

void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new Updater(ball, SinbadNode, UIElements);
    mRoot->addFrameListener(FrameListener);
}

void Game::createTrayListener()
{
    //Adding UI for
    mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());
    scnMgr->addRenderQueueListener(getOverlaySystem());
    addInputListener(mTrayMgr); 

    mButtonTrayMgr = new OgreBites::TrayManager("ButtonInterface", getRenderWindow());
    scnMgr->addRenderQueueListener(getOverlaySystem());
    addInputListener(mButtonTrayMgr);

    UIElements = new UI(mTrayMgr, mButtonTrayMgr);
}

bool Game::keyPressed(const KeyboardEvent& evt)
{
    switch (evt.keysym.sym)

    {
    case SDLK_ESCAPE:
        getRoot()->queueEndRendering();
        break;    
    case 97: //ASCII code for "a"
    {
        paddle->MoveLeft();
    }
    break;
    case 100: //ASCII code for "d"
    {
        paddle->MoveRight();
    }
    case 32:
        ball->SetStart();
    default:
        break;
    }
    //SinbadNode->setPosition(x, y, z);
    return true;
}

void Game::createScene()
{
    // -- tutorial section start --

    Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
    scnMgr->getRootSceneNode()->addChild(node);

    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
       //! [turnlights]

    //! [newlight]
    //

    Ogre::Light* light = scnMgr->createLight("Light1");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(Ogre::Vector3(1, -1, 0));

    // Set Light Color
    light->setDiffuseColour(1.0f, 1.0f, 1.0f);
    // Set Light Reflective Color
    light->setSpecularColour(1.0f, 1.0f, 0.0f);
    // Set Light (Range, Brightness, Fade Speed, Rapid Fade Speed)
    //light1->setAttenuation(10, 0.5, 0.045, 0.0);

    //
    Entity* lightEnt = scnMgr->createEntity("LightEntity", "sphere.mesh");
    SceneNode* lightNode = node->createChildSceneNode("LightNode");
    lightNode->attachObject(lightEnt);
    lightNode->attachObject(light);
    lightNode->setScale(0.01f, 0.01f, 0.01f);
    lightNode->setPosition(0.0f, 100.0f, 0);
    //! [newlight]
    //The first thing we'll do is create an abstract Plane object. This is not the mesh, it is more of a blueprint.
    Plane plane(Vector3::UNIT_Y, -10);
    //Now we'll ask the MeshManager to create us a mesh using our Plane blueprint. The MeshManager is already keeping track of the resources we loaded when initializing our application. On top of this, it can create new meshes for us.
    MeshManager::getSingleton().createPlane(
        "ground", RGN_DEFAULT,
        plane,
        1500, 1500, 20, 20,
        true,
        1, 5, 5,
        Vector3::UNIT_Z);

    //Now we will create a new Entity using this mesh.
    //We want to tell our SceneManager not to cast shadows from our ground Entity. It would just be a waste. Don't get confused, this means the ground won't cast a shadow, it doesn't mean we can't cast shadows on to the ground.
    Entity* groundEntity = scnMgr->createEntity("ground");
    scnMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
    groundEntity->setCastShadows(false);
    //And finally we need to give our ground a material.
    groundEntity->setMaterialName("Examples/BeachStones");

    paddle = new Paddle(scnMgr, SinbadNode);
    ball = new Ball(scnMgr, SinbadNode, paddle);
}

void Game::createCamera()
{
    //! [camera]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");    
    cam->setProjectionType(PT_ORTHOGRAPHIC);
    cam->setOrthoWindowHeight(100);
    //cam->setOrthoWindow(100, 100);
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(false);
    camNode->attachObject(cam);
    camNode->setPosition(0, 100, 0);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
    
    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);

    //! [camera]


}

int main(int argc, char** argv)
{
    try
    {
        Game app;
        app.initApp();
        app.getRoot()->startRendering();
        app.closeApp();
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error occurred during execution: " << e.what() << '\n';
        return 1;
    }

    return 0;
}

