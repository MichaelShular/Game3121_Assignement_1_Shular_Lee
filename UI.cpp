#include "UI.h"

UI::UI(TrayManager* TrayMgr, TrayManager* ButtonTrayMgr)
{
    mTrayMgr = TrayMgr;
    mButtonTrayMgr = ButtonTrayMgr;
    mLives = mTrayMgr->createLabel(TL_TOPLEFT, "lives", "Lives: 3", 150);
    mScore = mTrayMgr->createLabel(TL_TOPLEFT, "score", "Score: 0", 150);
    mTrayMgr->showFrameStats(TL_TOPRIGHT);
    mTrayMgr->toggleAdvancedFrameStats();
    mTime = mTrayMgr->createLabel(TL_TOPRIGHT, "time", "Time: 0", 150);
    mReset = mButtonTrayMgr->createButton(TL_CENTER, "reset", "Reset", 100);
    hideResetButton();
}

void UI::setTime(String a)
{
    mTime->setCaption(a);
}

void UI::setLives(String a)
{
    mLives->setCaption(a);
}

void UI::setScore(String a)
{
    mScore->setCaption(a);
}

void UI::showResetButton() {
   
    mButtonTrayMgr->showAll();
}

void UI::hideResetButton() {

    mButtonTrayMgr->hideAll();
}

bool UI::getReset()
{
    if (mReset->getState() == BS_DOWN) {
        return true;
    }
    else
    {
        return false;
    } 
}
