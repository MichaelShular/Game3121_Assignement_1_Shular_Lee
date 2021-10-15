#pragma once
#ifndef UI_H
#define UI_H

#include "Ogre.h"
#include "OgreTrays.h"

using namespace Ogre;
using namespace OgreBites;
/// Is a class that for the creation and management of UI. 
/// 
/// This class creates all UI for in the scene with in the scene in the default constructor and
/// uses its frunctions to control aspect text or visibility. 
class UI
{
private:
    TrayManager* mTrayMgr;
    TrayManager* mButtonTrayMgr;
    OgreBites::Label* mLives;
    OgreBites::Label* mScore;
    OgreBites::Label* mTime;
    OgreBites::Button* mReset;
public:
    UI(TrayManager* TrayMgr, TrayManager* ButtonTrayMgr);
    /// UI destructor.
    virtual ~UI() {};
    void setTime(String a);
    void setLives(String a);
    void setScore(String a);
    void showResetButton();
    void hideResetButton();
    bool getReset();
};

#endif 
