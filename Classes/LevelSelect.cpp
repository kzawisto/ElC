
#include <Colors.h>
#include <logic/Challenges.h>
#include <VcDirector.h>
#include "LevelSelect.h"
#include "GridNode.h"
#include "EventObserver.h"
#include "FullGrid.h"
#include "logic/Utils.h"
bool LevelSelect::init()
{
     if ( !Layer::init() )
    {
        return false;
    }
     levelNames = {"Sq", "Hex", "OctSq", "TwTri", "TwSqTri"};
     ColorLoader & cl =ColorLoader::getInstance();
     starColors = {cl.getColor("bronze"), cl.getColor("silver"),
     	    cl.getColor("gold"),  cl.getColor("white"),  cl.getColor("diamond"),
     		cl.getColor("red"), cl.getColor("green"), cl.getColor("blue") };
     sizes = {35,30,30,30,30};
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
     // add a "close" icon to exit the progress. it's an autorelease object
   // Label *label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    for(int a =0; a< 4;++a){
	Label * l =Label::createWithTTF("", "fonts/Marker Felt.ttf", 24);
	l->setPosition(origin.x + visibleSize.width/3, origin.y + 100 - a*25);
	addChild(l);
	l->setAlignment(TextHAlignment::LEFT);
	challengeLabels.push_back(l);
    }
    for(int a =0; a<3;++a){
    	Sprite * star = Sprite::create("star.png");
    	star->setPosition(origin.x +(1+a)*30+200, origin.y+200);
    	star->setScale(0.5,0.5);
    	stars.push_back(star);
    	addChild(star);
    }
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(LevelSelect::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    auto buttonLeft = ButtonFactory::createButton(CC_CALLBACK_1(LevelSelect::menuRight,this),"Next",
      Vec2(origin.x +visibleSize.width*7/8, origin.y + visibleSize.height*3.5f/7),40);
    auto buttonRight = ButtonFactory::createButton(CC_CALLBACK_1(LevelSelect::menuLeft,this),"Previous",
      Vec2(origin.x +visibleSize.width*5/8, origin.y + visibleSize.height*3.5f/7),40);
    auto buttonStart = ButtonFactory::createButton(CC_CALLBACK_1(LevelSelect::menuStart,this),"START",
          Vec2(origin.x +visibleSize.width*3/4, origin.y + visibleSize.height*4/7),40);
    auto buttonBack = ButtonFactory::createButton(CC_CALLBACK_1(LevelSelect::menuBack,this),"BACK",
          Vec2(origin.x +visibleSize.width*3/4, origin.y + visibleSize.height*3/7),40);
     auto menu = Menu::create(closeItem,buttonLeft, buttonRight,buttonStart,buttonBack, NULL);
    menu->setPosition(Vec2::ZERO);

    this->addChild(menu, 1);

    // ps->initWithFile("cloud.plist");
  // Scoreboards boo;
    refreshGrid();
    updateChallenges();
    return true;
}
void LevelSelect::menuLeft(Ref* pSender)
{
	vec_iter --;
	if(vec_iter< 0 ) vec_iter = levelNames.size()-1;
	 refreshGrid();
	 updateChallenges();
//  MyEvent event("START_NEWGAME", 0);
//    EventObserver::get().sendEvent(event);
}
void LevelSelect::menuRight(Ref* pSender)
{
	vec_iter ++;
	if((unsigned)vec_iter>= levelNames.size()) vec_iter =0;
	 refreshGrid();
	 updateChallenges();
//  MyEvent event("START_SETTINGS", 0);
//    EventObserver::get().sendEvent(event);
}
void LevelSelect::menuStart(Ref* pSender)
{

	MyEvent event("START_NEW_GAME:"+levelNames[vec_iter], 0);
   EventObserver::get().sendEvent(event);
}

void LevelSelect::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
  //  Layer::menuCloseCallback(pSender);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void LevelSelect::refreshGrid() {
	if(grid){
		removeChild(grid,true);
	}
	grid = MyGridFactory::get().generate(levelNames[vec_iter],sizes[vec_iter],true);
	addChild(grid);
	grid->setPosition(origin.x+50, origin.y+250);

}

void LevelSelect::menuBack(Ref* pSender)
{
	MyEvent event("MAIN_MENU", 0);
   EventObserver::get().sendEvent(event);
}
Scene* LevelSelect::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = LevelSelect::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void LevelSelect::updateChallenges() {
//	map<string, Challenge> map =
//			AchievementsObserver::getInstance().retrieveChallengesForRange(levelNames[vec_iter],levelNames[vec_iter]+char(127));
	auto & ao =AchievementsObserver::getInstance();

	auto vec=ao.getChallengeTypes(levelNames[vec_iter]);
	int i =0, j=0;
	for(auto label: challengeLabels) label->setString("");
	for(auto star:stars) star->setVisible(false);
	for(string s : vec){
		int lvl = ao.retrieveRecordLevel(s)+1;
		if(lvl >1){
			stars[j]->setVisible(true);
			stars[j]->setColor(starColors[lvl-2]);
			j++;
		}
		string query = s+"_"+myUtils::Utils::itos<int>(lvl);
		auto mymap=ao.retrieveChallengesForRange(query,query+char(127));
		if(not mymap.empty()){

			ChallengeLogic * cl = ChallengeLogic::get(mymap.begin()->second);
			//log("%s", cl->getMessage().c_str());
			challengeLabels[i]->setString(cl->getMessage());

			delete cl;
			i++;
		}
	}
}
