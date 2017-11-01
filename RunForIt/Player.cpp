//
//  Player.cpp
//  Game-mac
//
//  Created by Gimin Moon on 9/21/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Player.h"

Player::Player(Game* game)
:Actor(game)
{
    mCollision = new CollisionComponent(this);
    mCollision->SetSize(20, 64);

}
