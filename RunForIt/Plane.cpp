//
//  Plane.cpp
//  Game-mac
//
//  Created by Gimin Moon on 10/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Plane.h"
#include "Game.h"

Plane::Plane(Game* game)
:Actor(game)
{
    mSprite = new SpriteComponent(this);
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(64, 64);
    PlaneMove* pm = new PlaneMove(this);
    mComponent = pm;
    mGame->planes.push_back(this);
    
}
Plane::~Plane()
{
    mGame->planes.erase(std::remove(mGame->planes.begin(), mGame->planes.end(), this), mGame->planes.end());
}
