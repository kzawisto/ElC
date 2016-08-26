#include "TestScene2.h"
#include "GridNode.h"
#include "logic/SingularGrid.h"
#include "logic/LogicalGrid.h"
#include <sys/time.h>
USING_NS_CC;
using namespace std;
Scene* TestScene2::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = TestScene2::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TestScene2::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(TestScene2::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label


  ;
  	  int switcher = true;
    if(switcher){
    	double size = 45, sideSize = 2 * size * tan(M_PI/12);
    //auto grid = GridNode::createSqrGrid(size,45);
    	PD spacing ={2*size,size * 2* sqrt(3)};
    	PI howMany = {8,4};
    auto grid2 = GridNode::createTwGrid({0,0},size,spacing,howMany);
    auto grid =GridNode::createTwGrid({size,size*sqrt(3)},size,spacing,howMany);
    auto gridTri1 = GridNode::createTriGrid({size,sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany);
    auto gridTri2 = GridNode::createTriGrid({size,-sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany,0);
    auto gridTri11 = GridNode::createTriGrid({0,size*sqrt(3)+sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany);
    auto gridTri21 = GridNode::createTriGrid({0,size*sqrt(3)-sideSize*(0.5 + sqrt(3)/3)},sideSize,spacing,howMany,0);

    vector<shared_ptr<logic::SingularGrid>> vec;//{grid->singularGrid, grid2->singularGrid};
    vector<GridNode *> vec1 {grid,grid2,gridTri1,gridTri2,gridTri11,gridTri21};
    for(auto g: vec1) vec.push_back(g->singularGrid);
    logic::GridConnectionResolver resolver(vec);
    resolver.propagateConnections();

    DrawNode *dnode = DrawNode::create();
    this->addChild(dnode);
    dnode->setPosition({100,100});
//    for(int i =0; i < grid->size.X();++i)
//    	for(int j =0; j < grid->size.Y();++j){
//    		grid2->drawConnections(i,j,dnode);
//    		grid->drawConnections(i,j,dnode);
//    	}
    for(auto g : vec1) {
    	g->setPosition(100,100);
    	addChild(g);
    }
    }
    else{
	double size1 =70;
	double op = (1.0 + sqrt(2.0))*size1, sq32 = sqrt(3)/2*size1;
    //auto lt = shared_ptr<logic::LogicalTile>{ new logic::LogicalTile(8, {50,50}, {op/2,size1*0.5})};
	auto lt = shared_ptr<logic::LogicalTile>{ new logic::LogicalTile(4, {50,50}, {size1,size1})};
    auto tile = TileNode::create(lt);

    	shared_ptr<SinGrid>singularGrid{new logic::SingularGrid (8, {6,5},{op,op},{op/2,size1*0.5},{op/2,op/2})};
    tile->setPosition(300,300);
    auto ltOct = shared_ptr<logic::LogicalTile>{new logic::LogicalTile(8,{op/2,op/2},{op/2,size1*0.5})};
    auto tileOct = TileNode::create(ltOct);
    auto ltHex= shared_ptr<logic::LogicalTile>{new logic::LogicalTile(6,{op/2,op/2},{sq32,0.5*size1})};
    auto tileHex = TileNode::create(ltHex);
    auto ltTri= shared_ptr<logic::LogicalTile>{new logic::LogicalTile(3,{op/2,op/2},{0,size1})}; //{sqrt(3)/3*size1,size1})};
    auto tileTri = TileNode::create(ltTri, -30);
    auto ltTri1= shared_ptr<logic::LogicalTile>{new logic::LogicalTile(3,{op/2,op/2},{size1/2,sqrt(3)/6* size1})}; //{sqrt(3)/3*size1,size1})};
    auto tileTri1 = TileNode::create(ltTri1, 30);
    auto ltTri2= shared_ptr<logic::LogicalTile>{new logic::LogicalTile(3,{op/2,op/2},{sqrt(3)/6* size1,size1/2})}; //{sqrt(3)/3*size1,size1})};
     auto tileTri2 = TileNode::create(ltTri2, 0);
     auto ltTri3= shared_ptr<logic::LogicalTile>{new logic::LogicalTile(3,{op/2,op/2},{sqrt(3)/3* size1,0})}; //{sqrt(3)/3*size1,size1})};
        auto tileTri3 = TileNode::create(ltTri3, 60);
    auto ltTw= shared_ptr<logic::LogicalTile>{new logic::LogicalTile(12,{op/2,op/2},{size1,tan(M_PI/12)*size1})};
        auto tileTw = TileNode::create(ltTw);
    tileOct->setPosition(600,200);
    tileHex->setPosition(800,200);
    tileTri->setPosition(200,500);
    tileTri1->setPosition(800,500);

    tileTri2->setPosition(900,500);
    tileTri3->setPosition(700,500);
    tileTw->setPosition(400,500);

    this->addChild(tile);
    this->addChild(tileOct);
    this->addChild(tileTri);
    this->addChild(tileTri1);
    this->addChild(tileTri2);
    this->addChild(tileTri3);
    this->addChild(tileHex);
    this->addChild(tileTw);
    }
    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);

    return true;
}


void TestScene2::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
