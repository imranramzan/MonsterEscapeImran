/*
 Touch Gestures Functionality
 AllienEscape (c) BrainLogix
 Written by: Zeeshan Ali
 */


#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

#define ktouchLocationX "touchLocationX"
#define ktouchLocationY "touchLocationY"


CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    if ( !CCLayerPanZoom::init() )
    {
        return false;
    }

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback) );
    pCloseItem->setPosition( ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    /////////////////////////////
    // 3. add your codes below...

    flag = false;
    

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

//    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
//    pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
//    this->addChild(pLabel, 1);

    // add "HelloWorld" splash screen"
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("zombi_run.plist");
    
    animFrames = CCArray::createWithCapacity(21);
    char str[100] = {0};
    
    for(int i = 1; i < 20; i++)
    {
        if(i<10)
            sprintf(str, "run000%d.png", i);
        else
            sprintf(str, "run00%d.png", i);
        
        CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName( str );
        animFrames->addObject(frame);
    }
    
    CCAnimation *runAnimation=CCAnimation::createWithSpriteFrames(animFrames, 0.05f);
    
    
    pSprite = CCSprite::createWithSpriteFrameName("run0001.png");

    // position the sprite on the center of the screen
    pSprite->setPosition( ccp(size.width/2, size.height/2) );
    pSprite->runAction( CCRepeatForever::create( CCAnimate::create(runAnimation) ));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);
    pSprite->setScaleX(0.5);
    pSprite->setScaleY(0.5);

    int actualDuration = ( arc4random() % 7 );
    if(actualDuration == 1 || actualDuration == 2 || actualDuration == 3){
        pSprite->setScaleX(0.5);
        
    }else if (actualDuration == 5 || actualDuration == 6 || actualDuration == 7){
        pSprite->setScaleX(-0.5);
    }

    CCPoint endPoint = this->getPointsWithDistanceAtAngle(actualDuration*45, 200, pSprite->getPositionX(),pSprite->getPositionY());
    float x = endPoint.x;
    float y = endPoint.y;
    
//    CCLOG("hello %f %f",x ,y);
    
    
    CCFiniteTimeAction* actionMove =CCMoveTo::create( 2.0,ccp((int)x,(int)y) );
    CCCallFunc *functions = CCCallFunc::create(this, callfunc_selector(HelloWorld::executings));
    
    
    CCSequence *seq = CCSequence::create(actionMove,functions,NULL);
    seq->setTag(1);
    pSprite->runAction(seq);

    CCCallFuncND *getUpdPos = CCCallFuncND::create(this, callfuncND_selector(HelloWorld::getUpdatedPoints), pSprite);
    pSprite->runAction(CCRepeatForever::create(CCSpawn::create(getUpdPos, NULL)));
    
    _map = CCTMXTiledMap::create("iso-test-zorder.tmx");
    addChild(_map,-1);
    _hurdle = _map->layerNamed("colied");
   // _hurdle->setVisible(false);

    
    this->setTouchEnabled(true);
    
    human1 = CharacterHuman::create();
    this->addChild(human1);
    human1->delegate = this;
    human1->_map = _map;
    human1->setPosition(ccp(400, 400));
    
    human2 = CharacterHuman::create();
    this->addChild(human2);
    human2->delegate = this;
    human2->_map = _map;
    human2->setPosition(ccp(400, 300));
                        
    human3 = CharacterHuman::create();
    this->addChild(human3);
    human3->delegate = this;
    human3->_map = _map;
    human3->setPosition(ccp(400, 200));
    
    return true;
}
void HelloWorld::executings(){
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    int actualDuration = ( arc4random() % 7 );

    if(pSprite->getPositionX() < 0){
        actualDuration = 2;
        
    }else if(pSprite->getPositionY() < 0){
        actualDuration = 0;
    }else if(pSprite->getPositionX() > size.width){
        actualDuration = 6;
    }else if(pSprite->getPositionY() > size.height){
        actualDuration = 4;
    }
    if(actualDuration == 1 || actualDuration == 2 || actualDuration == 3){
        pSprite->setScaleX(0.5);
        
    }else if (actualDuration == 5 || actualDuration == 6 || actualDuration == 7){
        pSprite->setScaleX(-0.5);
    }
 //   CCLOG("%i",actualDuration);
    CCPoint endPoint = this->getPointsWithDistanceAtAngle(actualDuration*45, 200, pSprite->getPositionX(),pSprite->getPositionY());
    float x = endPoint.x;
    float y = endPoint.y;
    
    
    CCFiniteTimeAction* actionMove =CCMoveTo::create( 2.0,ccp((int)x,(int)y) );
    CCCallFunc *functions = CCCallFunc::create(this, callfunc_selector(HelloWorld::executings));
    CCSequence *seq = CCSequence::create(actionMove,functions,NULL);
    seq->setTag(1);
    pSprite->runAction(seq);
    
    
    
}
void HelloWorld::getUpdatedPoints(CCSprite *sprite){
    CCPoint points = sprite->getPosition();
    if(points.x<0){
        sprite->setPosition(ccp(0,points.y));
        sprite->stopActionByTag(1);
        sprite->setScaleX(0.5);

        CCPoint endPoint = this->getPointsWithDistanceAtAngle(45*2, 200, pSprite->getPositionX(),pSprite->getPositionY());
        float x = endPoint.x;
        float y = endPoint.y;
        CCFiniteTimeAction* actionMove =CCMoveTo::create( 2.0,ccp((int)x,(int)y) );
        CCCallFunc *functions = CCCallFunc::create(this, callfunc_selector(HelloWorld::executings));
        CCSequence *seq = CCSequence::create(actionMove,functions,NULL);
        seq->setTag(1);
        pSprite->runAction(seq);

    }else if(points.y<0){
        sprite->setPosition(ccp(points.x,0));
        sprite->stopActionByTag(1);

        CCPoint endPoint = this->getPointsWithDistanceAtAngle(45*0, 200, pSprite->getPositionX(),pSprite->getPositionY());
        float x = endPoint.x;
        float y = endPoint.y;
        CCFiniteTimeAction* actionMove =CCMoveTo::create( 2.0,ccp((int)x,(int)y) );
        CCCallFunc *functions = CCCallFunc::create(this, callfunc_selector(HelloWorld::executings));
        CCSequence *seq = CCSequence::create(actionMove,functions,NULL);
        seq->setTag(1);
        pSprite->runAction(seq);

    }else if(points.x>CCDirector::sharedDirector()->getWinSize().width){
        sprite->setPosition(ccp(points.x-1,points.y));
        sprite->stopActionByTag(1);
        sprite->setScaleX(-0.5);
        CCPoint endPoint = this->getPointsWithDistanceAtAngle(45*6, 200, pSprite->getPositionX(),pSprite->getPositionY());
        float x = endPoint.x;
        float y = endPoint.y;
        CCFiniteTimeAction* actionMove =CCMoveTo::create( 2.0,ccp((int)x,(int)y) );
        CCCallFunc *functions = CCCallFunc::create(this, callfunc_selector(HelloWorld::executings));
        CCSequence *seq = CCSequence::create(actionMove,functions,NULL);
        seq->setTag(1);
        pSprite->runAction(seq);

    }else if(points.y>CCDirector::sharedDirector()->getWinSize().height){
        sprite->setPosition(ccp(points.x,points.y-1));
        sprite->stopActionByTag(1);
        CCPoint endPoint = this->getPointsWithDistanceAtAngle(45*4, 200, pSprite->getPositionX(),pSprite->getPositionY());
        float x = endPoint.x;
        float y = endPoint.y;
        CCFiniteTimeAction* actionMove =CCMoveTo::create( 2.0,ccp((int)x,(int)y) );
        CCCallFunc *functions = CCCallFunc::create(this, callfunc_selector(HelloWorld::executings));
        CCSequence *seq = CCSequence::create(actionMove,functions,NULL);
        seq->setTag(1);
        pSprite->runAction(seq);

    }
    
}
           
cocos2d::CCPoint HelloWorld::getPointsWithDistanceAtAngle(int angle, int distance, float x, float y){
    CCPoint endPoint;
    endPoint.x = sinf(CC_DEGREES_TO_RADIANS(angle)) * distance;
    endPoint.y = cosf(CC_DEGREES_TO_RADIANS(angle)) * distance;
    endPoint = ccpAdd(CCPoint(x,y), endPoint);
    return endPoint;
    
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::characterTouchMove(cocos2d::CCPoint touchPoint, CharacterHuman *human)
{
    if (this->isColiedable(this->getISOCoord(touchPoint)) || this->isExit(this->getISOCoord(touchPoint)))
    {
        human->isHurdle = true;
       
    }
    
    else
    {
        
    }
}

void HelloWorld::humanCurrentPosition(cocos2d::CCPoint pos, CharacterHuman *human)
{

    if (this->isColiedable(this->getISOCoord(pos)))
    {
        human->isHurdle = true;
         this->allienInHumanBoundary(human, true);
    }

    else
    {
        this->allienInHumanBoundary(human, false);
    }
    
    if (this->isExit(this->getISOCoord(pos)))
    {
        human->removeFromParentAndCleanup(true);
        
    }
    
}

cocos2d::CCPoint HelloWorld::getISOCoord(CCPoint point)
{
    int posY = _map->getMapSize().height - point.x/_map->getTileSize().width + _map->getMapSize().width/2 - point.y/_map->getTileSize().height;
    
    int posX = _map->getMapSize().height + point.x/_map->getTileSize().width - _map->getMapSize().width/2 - point.y/_map->getTileSize().height;
    
    if(posX<0)
        posX=0;
    if(posY<1)
        posY=1;
    if(posX>_map->getMapSize().width-1)
        posX=_map->getMapSize().width-1;
    if(posY>_map->getMapSize().height - 1)
        posY=_map->getMapSize().height - 1;
    
    return ccp(posX, posY);
}

bool HelloWorld::isColiedable(CCPoint tileCoord){
    bool flag = false;
    CCTMXLayer *_meta = _map->layerNamed("colied");
    int tileGid = _meta->tileGIDAt(tileCoord);
    if(tileGid)
    {
        flag = true;
    }
    return flag;
}

bool HelloWorld::isExit(CCPoint tileCoord){
    bool flag = false;
 /*   CCTMXLayer *_meta = _map->layerNamed("Exit");
    int tileGid = _meta->tileGIDAt(tileCoord);
    if(tileGid){
        flag = true;
    }*/
    return flag;
}

void HelloWorld::allienInHumanBoundary(CharacterHuman *human, bool inBoundary)
{
        human->allienInRadius(inBoundary);
}
