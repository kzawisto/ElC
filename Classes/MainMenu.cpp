
#include "MainMenu.h"
#include "GridNode.h"
#include "EventObserver.h"
#include <fstream>
#include <logic/Challenges.h>
#include <logic/Utils.h>
#include <Colors.h>
#include <VcDirector.h>
using namespace std;
bool MainMenu::init()
{
     if ( !Layer::init() )
    {
        return false;
    }

//    string s1,s =FileUtils::getInstance()->sharedFileUtils()->fullPathForFilename("txt11");
//    auto mymap=myUtils::Utils::loadColumnMap<string,Challenge>(s,":");
//    for(auto it = mymap.begin();it != mymap.end();++it){
//    	 Challenge c= it->second;
//    	 cout<<c.pk<<" "<<c.args<<" "<<c.grid<<" "<<c.type<<" "<<c.level<<"\n";
//    }
//    string s2 = FileUtils::getInstance()->getWritablePath()+"txt2";
//    myUtils::Utils::serializeMap(s2,":",mymap);
    // AchievementsObserver::getInstance();

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

     // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenu::menuCloseCallback, this));
    double menuSize=40;
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto buttonNewGame = ButtonFactory::createButton(CC_CALLBACK_1(MainMenu::menuNewGame,this),"NEW GAME",
      Vec2(visibleSize.width*1/2, visibleSize.height*6/7),menuSize);
    auto buttonSettings = ButtonFactory::createButton(CC_CALLBACK_1(MainMenu::menuSettings,this),"SETTINGS",
      Vec2(visibleSize.width*1/2, visibleSize.height*5/7),menuSize);
    auto buttonInfo = ButtonFactory::createButton(CC_CALLBACK_1(MainMenu::menuInfo,this),"INFO",
      Vec2(visibleSize.width*1/2, visibleSize.height*4/7),menuSize);
    auto buttonScores = ButtonFactory::createButton(CC_CALLBACK_1(MainMenu::menuScoreboards,this),"SCOREBOARDS",
      Vec2(visibleSize.width*1/2, visibleSize.height*3/7),menuSize);
     auto menu = Menu::create(closeItem,buttonNewGame,buttonSettings,buttonInfo,buttonScores, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    ParticleSystem *ps = ParticleSystemQuad::create("colored_rain.plist");
   // ps->initWithFile("cloud.plist");
  ps->setSourcePosition(Vec2(0,0));
    // ps->initWithFile("cloud.plist");
  // Scoreboards boo;
   this->addChild(ps,0);
   return true;
}
void MainMenu::menuNewGame(Ref* pSender)
{
	MyEvent event("GAME_SELECT", 0);
   EventObserver::get().sendEvent(event);
}
void MainMenu::menuSettings(Ref* pSender)
{
//  MyEvent event("START_SETTINGS", 0);
//    EventObserver::get().sendEvent(event);
}
void MainMenu::menuScoreboards(Ref* pSender)
{
  MyEvent event("START_SCOREBOARDS", 0);
  EventObserver::get().sendEvent(event);
}

void MainMenu::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
  //  Layer::menuCloseCallback(pSender);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
void MainMenu::menuInfo(Ref* pSender)
{

}
Scene* MainMenu::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainMenu::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
