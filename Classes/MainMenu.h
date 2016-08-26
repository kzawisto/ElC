/*
 * MainMenu.h
 *
 *  Created on: Oct 18, 2015
 *      Author: krystian892
 */
#ifndef MAINMENU_H
#define MAINMENU_H
#include"cocos2d.h"
#include<functional>
#include<string>
#include "ui/UIScale9Sprite.h"

USING_NS_CC;

class MainMenu: public cocos2d::Layer
{
public:
   static cocos2d::Scene* createScene();
   // EventObserver eventObserver = new EventObserver();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    void menuCloseCallback(Ref* pSender);

    void menuNewGame(Ref* pSender);
    void menuSettings(Ref* pSender);
    void menuScoreboards(Ref* pSender);
    void menuInfo(Ref* pSender);
    CREATE_FUNC(MainMenu);
};


#endif // MAINMENU_H
