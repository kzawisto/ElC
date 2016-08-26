#include "HelloWorldScene.h"
#include "GridNode.h"
#include "logic/SingularGrid.h"
#include "logic/LogicalGrid.h"
#include <sys/time.h>
USING_NS_CC;
using namespace std;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
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
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //shared_ptr<LogTile> tile1 { new logic::LogicalTile(4,50,{0,0},{50,0})};
   // TileNo//de * tile = TileNode::create(tile1);
    timeval  t1,t2;
    gettimeofday(&t1,nullptr);
    if( true){
    auto grid = GridNode::createSqrGridOld(60,45);
    auto grid2 = GridNode::createOctGridOld(60);
    vector<shared_ptr<logic::SingularGrid>> vec{grid->singularGrid, grid2->singularGrid};
    logic::GridConnectionResolver resolver(vec);
    resolver.propagateConnections();
    grid->setPosition({100,100});
    grid2->setPosition({100,100});
    DrawNode *dnode = DrawNode::create();
    this->addChild(dnode);
    dnode->setPosition({100,100});
    for(int i =0; i < grid->size.X();++i)
    	for(int j =0; j < grid->size.Y();++j)
    		grid2->drawConnections(i,j,dnode);
    this->addChild(grid);
    this->addChild(grid2);
    double b=1.0000001;
    for(int a =0;a<1000000;++a) b*=1.0000001;
    gettimeofday(&t2,nullptr);
    cout<<" "<<t2.tv_sec -t1.tv_sec<<" "<<t2.tv_usec - t1.tv_usec<<"\n";
    }
    if(false){
	double size1 =100;
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
    auto ltTri= shared_ptr<logic::LogicalTile>{new logic::LogicalTile(3,{op/2,op/2},{sqrt(3)/3*size1,size1})};
    auto tileTri = TileNode::create(ltTri);
    auto ltTw= shared_ptr<logic::LogicalTile>{new logic::LogicalTile(3,{op/2,op/2},{sqrt(3)/3*size1,size1})};
        auto tileTw = TileNode::create(ltTri);
    tileOct->setPosition(600,300);
    tileHex->setPosition(800,300);
    tileTri->setPosition(300,500);
    tileTw->setPosition(600,500);
    this->addChild(tile);
    this->addChild(tileOct);

    this->addChild(tileTri);

    this->addChild(tileHex);
    }
    // add the sprite as a child to this layer
    //this->addChild(sprite, 0);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
