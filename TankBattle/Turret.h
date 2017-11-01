//
//  Turret.h
//  Game-mac
//
//  Created by Gimin Moon on 10/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef Turret_h
#define Turret_h
#include "Actor.h"
#include "SDL/SDL_image.h"

class Turret : public Actor{
public:
    Turret(class Game* game);
    void ActorInput(const Uint8* keyState) override;
    SDL_Scancode mRotateClockKey, mRotateCounterKey;
    void SetPlayerTwo();
};

#endif /* Turret_h */
