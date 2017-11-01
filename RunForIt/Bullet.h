//
//  Bullet.h
//  Game-mac
//
//  Created by Gimin Moon on 10/17/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef Bullet_h
#define Bullet_h
#include "Actor.h"
#include "Plane.h"

class Bullet : public Actor{
public:
    Bullet(class Game* game);
    void UpdateActor(float deltaTime) override;
    float duration;
    bool Collides(Plane* plane, Bullet* bullet);
};

#endif /* Bullet_h */
