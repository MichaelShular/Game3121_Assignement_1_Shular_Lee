#include "UI.h"

/// The defualt conconstructor used for creation of all widgets in scene.
///  
/// @param TrayMgr: Tray manager for labels in the scene.
/// @param ButtonTrayMgr: Tray manager for buttons in the scene.
/// @note: Two tray managers need to be used because if widgets are hidden the transparent tray
/// is still visable. Instead the entire tray is hidden.  
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

/// Used to change time label text.
/// 
/// @param a: Takes in a string to change text.
void UI::setTime(String a)
{
    mTime->setCaption(a);
}

/// Used to change Lives label text.
/// 
/// @param a: Takes in a string to change text.
void UI::setLives(String a)
{
    mLives->setCaption(a);
}

/// Used to change score label text.
/// 
/// @param a: Takes in a string to change text.
void UI::setScore(String a)
{
    mScore->setCaption(a);
}

/// Used to hide tray holding reset button.
void UI::showResetButton() {
   
    mButtonTrayMgr->showAll();
}

/// Used to show tray holding reset button.
void UI::hideResetButton() {

    mButtonTrayMgr->hideAll();
}
/// Used to check if reset button is pressed or not.
///
/// checks the state of the reset button to see if button is pressed
/// @returns bool if button is pressed down
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
