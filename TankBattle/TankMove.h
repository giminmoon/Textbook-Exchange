//
//  TankMove.h
//  Game-mac
//
//  Created by Gimin Moon on 10/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef TankMove_h
#define TankMove_h
#include "MoveComponent.h"
#include "Actor.h"
#include "SDL/SDL_image.h"

class TankMove : public MoveComponent{
public:
    TankMove(Actor* owner);
    void Update(float deltaTime) override;
    void ProcessInput(const Uint8* keyState) override;
    void SetPlayTwo();
    SDL_Scancode mForwardKey, mBackKey,mRotateClockKey, mRotateCounterKey;
};
#endif /* TankMove_h */
