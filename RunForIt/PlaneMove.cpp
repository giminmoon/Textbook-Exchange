//
//  PlaneMove.cpp
//  Game-mac
//
//  Created by Gimin Moon on 10/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "PlaneMove.h"
#include "Actor.h"
#include "Game.h"
#include "Tile.h"

PlaneMove::PlaneMove(Actor* actor)
:MoveComponent(actor)
{
    Vector2 position = actor->GetGame()->mGrid->GetStartTile()->GetPosition();
    actor->SetPosition(position);
    SetForwardSpeed(200.0f);
    SetNextTile(mOwner->GetGame()->mGrid->GetStartTile()->GetParent());
}

void PlaneMove::Update(float deltaTime)
{
    MoveComponent::Update(deltaTime);
    if(mNextTile)
    {
         double distance = std::sqrt(pow(mOwner->GetPosition().x - mNextTile->GetPosition().x,2) + pow(mOwner->GetPosition().y - mNextTile->GetPosition().y,2));
        if(distance < 2.0f){
            SetNextTile(mNextTile->GetParent());
        }
        
        if(mOwner->GetPosition().x > 1000)
        {
            mOwner->SetState(Plane::EDead);
        }
    }
}

void PlaneMove::SetNextTile(const Tile* tile)
{
    mNextTile = tile;
    if(!mNextTile)
    {
        mOwner->SetRotation(0);
    }
    else
    {
        float angle = -Math::Atan2(mNextTile->GetPosition().y - mOwner->GetPosition().y, mNextTile->GetPosition().x - mOwner->GetPosition().x);
        mOwner->SetRotation(angle);
    }
}
