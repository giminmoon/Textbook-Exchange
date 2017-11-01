//
//  Tower.h
//  Game-mac
//
//  Created by Gimin Moon on 10/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef Tower_h
#define Tower_h
#include "Actor.h"
#include "Bullet.h"
#include "Plane.h"

class Tower : public Actor{
public:
    Tower(class Game* game);
    void UpdateActor(float deltaTime) override;
    std::pair<Plane*,float> closestTower();
    float getDistance(Plane* plane, Tower* tower);
    
    float attackTimer;
};

#endif /* Tower_h */
