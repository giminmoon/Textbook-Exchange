//
//  Bullet.cpp
//  Game-mac
//
//  Created by Gimin Moon on 10/17/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Bullet.h"
#include "Game.h"

Bullet::Bullet(class Game* game)
:Actor(game)
{
    mSprite = new SpriteComponent(this);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(10, 10);
    MoveComponent* bm = new MoveComponent(this);
    mComponent = bm;
    bm->SetForwardSpeed(500.0f);
    duration = 0.0f;
}

void Bullet::UpdateActor(float deltaTime)
{
    duration+=deltaTime;
    if(duration >= 2.0f)
    {
        this->SetState(Bullet::EDead);
    }
    
    for(unsigned int i = 0; i < mGame->planes.size(); i++)
    {
        if(Collides(mGame->planes[i], this))
        {
            mGame->planes[i]->SetState(Plane::EDead);
            this->SetState(Bullet::EDead);
        }
    }
    
}

bool Bullet::Collides(Plane* plane, Bullet* bullet)
{
    return plane->GetCollision()->Intersect(bullet->GetCollision());
}
