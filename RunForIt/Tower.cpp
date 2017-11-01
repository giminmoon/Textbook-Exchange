//
//  Tower.cpp
//  Game-mac
//
//  Created by Gimin Moon on 10/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Tower.h"
#include "Game.h"

Tower::Tower(class Game* game)
:Actor(game)
{
    mSprite = new SpriteComponent(this);
    attackTimer = 2.0f;
}

void Tower::UpdateActor(float deltaTime)
{
    attackTimer -= deltaTime;
    if(attackTimer <= 0.0f)
    {
        std::pair<Plane*, float> closest = closestTower();
        if(closest.second < 100.0f)
        {
            float angle = -Math::Atan2(closest.first->GetPosition().y - this->GetPosition().y, closest.first->GetPosition().x - this->GetPosition().x);
            this->SetRotation(angle);
            Bullet* bullet = new Bullet(mGame);
            Vector2 position = this->GetPosition();
            bullet->SetPosition(position);
            SpriteComponent* sc = new SpriteComponent(bullet, 200);
            sc->SetTexture(mGame->GetTexture("Assets/Bullet.png"));
            bullet->SetSprite(sc);
            bullet->SetRotation(this->GetRotation());
        }
        attackTimer = 2.0f;
    }
}

std::pair<Plane*,float> Tower::closestTower()
{
    Plane* closetPlane = nullptr;
    float minDistance = std::numeric_limits<float>::max();
    for(unsigned int i = 0; i < mGame->planes.size(); i++)
    {
        if(minDistance > getDistance(mGame->planes[i], this))
        {
            minDistance = getDistance(mGame->planes[i], this);
            closetPlane = mGame->planes[i];
        }
    }
    return std::make_pair(closetPlane, minDistance);
}

float Tower::getDistance(Plane* plane, Tower* tower)
{
    return sqrtf(pow(plane->GetPosition().x - tower->GetPosition().x,2) + pow(plane->GetPosition().y - tower->GetPosition().y,2));
}
