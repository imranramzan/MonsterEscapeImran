//
//  CharacterHumanDelegateClass.h
//  ZombieEscapeTest1
//
//  Created by ImranR on 10/23/13.
//
//

#ifndef __ZombieEscapeTest1__CharacterHumanDelegateClass__
#define __ZombieEscapeTest1__CharacterHumanDelegateClass__

#include <iostream>
#include "cocos2d.h"
#include "CharacterHuman.h"

using namespace cocos2d;

class CharacterHuman;
class CharacterHumanDelegateClas {
    
    
public:
    
    virtual void characterTouchMove (CCPoint touchPoint, CharacterHuman *human) = 0;
    virtual void humanCurrentPosition (CCPoint pos, CharacterHuman *human) = 0;
};

#endif /* defined(__ZombieEscapeTest1__CharacterHumanDelegateClass__) */
