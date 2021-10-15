//Assignment_1_ShularLee
//Michael Shular 101273089
//Daekoen Lee 101076401


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
/// This class is used to control what changes each frame.
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

    /// Default Updator constructor.
    /// 
    /// Used to pass objects that will need to update.
    /// @param: ball class object
    /// @param: defualt camera object
    /// @param: UI class object
    Updater(Ball* ball, Ogre::SceneNode* camNode, UI* UIElements)
    {
        _ball = ball;
        _UIElements = UIElements;
        _camNode = camNode;
        _movementspeed = 200.0f;
        _mousespeed = 0.002f;   
    }

    /// The function which controls what happens each frame. 
    /// 
    /// Updates the ball, UI elements and check to see of game has ended
    /// @param: a FrameEvent, which is passed onto ball
    /// @returns: a bool.
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
/// This class is used to create control main aspects of the game.
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
    /// Game destructor.
    virtual ~Game() {}
    void setup();
    bool keyPressed(const KeyboardEvent& evt);
    void createScene();
    void createCamera();
    void createFrameListener();
    void createTrayListener();
};

/// Defualt Game constructor 
Game::Game()
    : ApplicationContext("week3-5-FrameListenerDemo")
{
}

/// Initialize everything required to start game before updating
/// 
/// Currently sets up 
/// -makes for for application
/// -creates one scene for game
/// -adds camra to scene
/// -adds shader generation to scene
/// -adds trays to scene
/// -adds updator to scene 
void Game::setup()
{
    // do not forget to call the base first
    ApplicationContext::setup();
    addInputListener(this);

    // get a pointer to the already created root
    root = getRoot();    
    scnMgr = root->createSceneManager();
    
    // register our scene with the RTSS
    RTShader::ShaderGenerator* shadergen = RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
    createScene();    
    createCamera();
    createTrayListener();
    createFrameListener();
}

/// Used to initialize the Updater class.
void Game::createFrameListener()
{
    Ogre::FrameListener* FrameListener = new Updater(ball, SinbadNode, UIElements);
    mRoot->addFrameListener(FrameListener);
}

/// Used to initialize the UI class and create all trays in the scene.
void Game::createTrayListener()
{
    //Adding tray for lables
    mTrayMgr = new OgreBites::TrayManager("InterfaceName", getRenderWindow());
    scnMgr->addRenderQueueListener(getOverlaySystem());
    addInputListener(mTrayMgr); 
    //Adding tray for buttons
    mButtonTrayMgr = new OgreBites::TrayManager("ButtonInterface", getRenderWindow());
    scnMgr->addRenderQueueListener(getOverlaySystem());
    addInputListener(mButtonTrayMgr);
    //creating UI class
    UIElements = new UI(mTrayMgr, mButtonTrayMgr);
}

/// Used to control keyboard events.
/// 
/// Currently listens for 
/// Esc: Quit application 
/// A: player moves to left 
/// D: player moves to right 
/// Spacebar: starts the ball movement  
/// @param: takes in OgreBites::KeyboardEvent Struct.  
/// @returns: a bool.
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
    break;
    case 32: //ASCII code for "spacebar"
        ball->SetStart();
        break;
    default:
        break;
    }
    return true;
}

///Used to add all object to scene
///
/// Currently added
/// -light
/// -background
/// -ball
/// -paddle 
void Game::createScene()
{
    Ogre::SceneNode* node = scnMgr->createSceneNode("Node1");
    scnMgr->getRootSceneNode()->addChild(node);

    scnMgr->setShadowTechnique(ShadowTechnique::SHADOWTYPE_STENCIL_ADDITIVE);

    //! [turnlights]
    scnMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
       //! [turnlights]

    //! [newlight]
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

/// Adding camera to scene
///
/// Sets the settings for the camera in the scene postion, direction projection type and etc. 
void Game::createCamera()
{
    //! [camera]
    SceneNode* camNode = scnMgr->getRootSceneNode()->createChildSceneNode();

    // create the camera
    Camera* cam = scnMgr->createCamera("myCam");    
    cam->setProjectionType(PT_ORTHOGRAPHIC);
    cam->setOrthoWindowHeight(100);
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(false);
    camNode->attachObject(cam);
    camNode->setPosition(0, 100, 0);
    camNode->lookAt(Ogre::Vector3(0, 0, 0), Node::TS_WORLD);
    
    // and tell it to render into the main window
    getRenderWindow()->addViewport(cam);
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

