//
//  CharacterHuman.h
//  ZombieEscapeTest1
//
//  Created by ImranR on 10/10/13.
//
//

#ifndef __ZombieEscapeTest1__CharacterHuman__
#define __ZombieEscapeTest1__CharacterHuman__

#include "cocos2d.h"
#include "CharacterHuman.h"
#include "CharacterHumanDelegateClass.h"

using namespace cocos2d;

class CharacterHumanDelegateClas;
class CharacterHuman : public cocos2d::CCLayerColor
{
    
    CCSprite* character;
    
    
    
    bool shouldMove;
    float goAtAngle;
    
public:
    
    CCTMXTiledMap *_map;
    bool isHurdle;
    CCArray *patharray ;
    CharacterHumanDelegateClas *delegate;
    CCArray *boundaryTilesArray;
    
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();

    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(CharacterHuman);
    
    
    virtual void draw();
    
    virtual void registerWithTouchDispatcher(void);
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void placeHumanToMapAt(CCPoint position);
    void moveCharacter();
    void moveCharacterToAngle();
    void moveToAngleFinished();
    
    void allienInRadius(bool inBoundary);
    
    
    float characterCurrentAngleInDeg(CCPoint startingPoint, CCPoint endingPoint);
    CCPoint getPointsWithDistanceAtAngle(int angle, int distance, float x, float y);
};


#endif /* defined(__ZombieEscapeTest1__CharacterHuman__) */
