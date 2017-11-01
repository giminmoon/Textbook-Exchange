//
//  Bullet.h
//  Game-mac
//
//  Created by Gimin Moon on 10/23/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef Bullet_h
#define Bullet_h

#include "Actor.h"
#include "Game.h"
#include "Tank.h"

class Bullet : public Actor{
public:
    Bullet(class Game* game);
    void UpdateActor(float deltaTime) override;
    Tank* FiredTank;
};

#endif /* Bullet_h */
