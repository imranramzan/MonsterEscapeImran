//
//  CharacterHuman.cpp
//  ZombieEscapeTest1
//
//  Created by ImranR on 10/10/13.
//
//

#include "CharacterHuman.h"


#define ktouchLocationX "touchLocationX"
#define ktouchLocationY "touchLocationY"
#define kCharacterVelocity 100.0f
#define kCharacterVelocityRandom 300.0f

CCScene* CharacterHuman::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    CharacterHuman *layer = CharacterHuman::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool CharacterHuman::init()
{
    //////////////////////////////
    // 1. super init first
    if (!CCLayerColor::initWithColor( ccc4(0,0,255,255)) )
    {
        return false;
    }
    
    isHurdle = false;
    shouldMove = false;
        
        
    patharray = CCArray::create();
    patharray->retain();
    
    boundaryTilesArray = CCArray::create();
    boundaryTilesArray->retain();
    
    this->setTouchEnabled(true);
    this->setColor(ccc3(255, 0, 0));
    
   // CCLayerColor *bgLayer = CCLayerColor::create(ccc4(0,0,255,255), 300, 300);
   // this->addChild(bgLayer);
    
    return true;
}


void CharacterHuman::placeHumanToMapAt(cocos2d::CCPoint position)
{
    character  = CCSprite::create("grossinis_sister1.png");
    character->retain();
    character->setPosition(position);
    
    this->addChild(character, 0);

}

CCPoint CharacterHuman::getPointsWithDistanceAtAngle(int angle, int distance, float x, float y)
{
    CCPoint endPoint;
    endPoint.x = cosf(CC_DEGREES_TO_RADIANS(angle)) * distance;
    endPoint.y = sinf(CC_DEGREES_TO_RADIANS(angle)) * distance;
    endPoint = ccpAdd(CCPoint(x,y), endPoint);
    return endPoint;
}

void CharacterHuman::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -1, true);
}

bool CharacterHuman::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint point = pTouch->getLocationInView();
   
    point = CCDirector::sharedDirector()->convertToGL(point);
     point  = this->convertToNodeSpace(point);
    
    if (character->boundingBox().containsPoint(point))
    {
        character->stopAllActions();
        patharray->removeAllObjects();
        shouldMove = true;
        return true;
    }
    
    else return false;
}

void CharacterHuman::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
   // CCLOG("Array Count %d", patharray->count());
    if (shouldMove )
    {
        
        
        CCPoint point = pTouch->getLocationInView();
        point = CCDirector::sharedDirector()->convertToGL(point);
        point = this->convertToNodeSpace(point);
        
        this->delegate->characterTouchMove(point, this);
        if (!isHurdle)
        {
            CCDictionary *position = CCDictionary::create();
            position->setObject(CCString::createWithFormat("%f", point.x), ktouchLocationX);
            position->setObject(CCString::createWithFormat("%f", point.y), ktouchLocationY);
            patharray->addObject(position);
        }
        
        
     //   CCLOG("TouchX %f", point.x);
     //   CCLOG("TouchY %f", point.y);
        
        
    }
}

void CharacterHuman::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if(shouldMove)
    {
        this->moveCharacter();
        shouldMove = false;
        isHurdle = false;
    }
}

void CharacterHuman::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    
}

void CharacterHuman::moveCharacter()
{
    if (patharray->count())
    {
        //CCLOG("Array Count %d", patharray->count());
        
        CCDictionary *posDic = (CCDictionary *)patharray->objectAtIndex(0);
        CCPoint pos = ccp(((CCString *) posDic->objectForKey(ktouchLocationX))->floatValue(), ((CCString *) posDic->objectForKey(ktouchLocationY))->floatValue());
        float distance = ccpDistance(pos, character->getPosition());
        float duration = distance / kCharacterVelocity;
        
        CCDictionary *anglePosDic;
        CCPoint anglePos;
        
        if (patharray->count() > 4)
        {
        anglePosDic = (CCDictionary *)patharray->objectAtIndex(4);
        anglePos = ccp(((CCString *) anglePosDic->objectForKey(ktouchLocationX))->floatValue(), ((CCString *) anglePosDic->objectForKey(ktouchLocationY))->floatValue());
            float angle = this->characterCurrentAngleInDeg(character->getPosition(), anglePos);
            goAtAngle = angle;
            CCLOG("Character Angle %f", angle);
            int Tag = angle / 45;
            CCLOG("Character Image Tag %d", Tag);
        }
       
    //    CCLOG("Character Duration %f", duration);
        character->runAction(
                             CCSequence::create(
                                                CCMoveTo::create(duration, pos),
                                                CCCallFunc::create(this, callfunc_selector(CharacterHuman::moveCharacter)),
                                                NULL));
        patharray->removeObjectAtIndex(0);
    }
    
    else
    {
        this->moveCharacterToAngle();
    }
}

void CharacterHuman::moveCharacterToAngle()
{
    CCPoint destinationPoint = this->getPointsWithDistanceAtAngle(goAtAngle, 1, character->getPosition().x, character->getPosition().y);
    delegate->humanCurrentPosition(destinationPoint, this);
    
    if (!isHurdle)
    {
        
        float distance = ccpDistance(destinationPoint, character->getPosition());
        float duration = distance / kCharacterVelocityRandom;
        character->runAction(CCSequence::create(
                                                CCMoveTo::create(duration, destinationPoint),
                                                CCCallFunc::create(this, callfunc_selector(CharacterHuman::moveCharacterToAngle)),
                                                NULL));
    }
    
    
}

void CharacterHuman::moveToAngleFinished()
{
    
}
void CharacterHuman::draw()
{
    if (patharray->count())
    {
        for (int i = 0; i < patharray->count() - 1; i++)
        {
            CCDictionary *posDic = (CCDictionary *)patharray->objectAtIndex(i);
            CCPoint pos = ccp(((CCString *) posDic->objectForKey(ktouchLocationX))->floatValue(), ((CCString *) posDic->objectForKey(ktouchLocationY))->floatValue());
            
            posDic = (CCDictionary *)patharray->objectAtIndex(i+1);
            CCPoint pos2 = ccp(((CCString *) posDic->objectForKey(ktouchLocationX))->floatValue(), ((CCString *) posDic->objectForKey(ktouchLocationY))->floatValue());
            ccDrawColor4F(1.0f, 0.0f, 0.0f, 1.0f);
            ccDrawLine(pos , pos2);
        }
    }    
}

float CharacterHuman::characterCurrentAngleInDeg(CCPoint startingPoint, CCPoint endingPoint)
{
    CCPoint originPoint = CCPointMake(endingPoint.x - startingPoint.x, endingPoint.y - startingPoint.y); // get origin point to origin by subtracting end from start
    float bearingRadians = atan2f(originPoint.y, originPoint.x); // get bearing in radians
    float bearingDegrees = bearingRadians * (180.0 / M_PI); // convert to degrees
    
    bearingDegrees = (bearingDegrees > 0.0 ? bearingDegrees : (360.0 + bearingDegrees)); // correct discontinuity
    return bearingDegrees;
}

void CharacterHuman::allienInRadius(bool inBoundary)
{
     if (inBoundary)
     {
         character->runAction(CCRepeatForever::create(
                                                      CCSequence::create(
                                                                         CCScaleTo::create(1, .7),
                                                                         CCScaleTo::create(1, 1),
                                                                         NULL)));
     }
    
    else
    {
        character->setScale(1);
        character->stopAllActions();
    }
}

