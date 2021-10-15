#pragma once
#ifndef UI_H
#define UI_H

#include "Ogre.h"
#include "OgreTrays.h"

using namespace Ogre;
using namespace OgreBites;

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
    virtual ~UI() {};
    void setTime(String a);
    void setLives(String a);
    void setScore(String a);
    void showResetButton();
    void hideResetButton();
    bool getReset();
};

#endif 
