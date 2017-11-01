//
//  Bullet.cpp
//  Game-mac
//
//  Created by Gimin Moon on 10/23/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
//#include "Game.h"
#include "Bullet.h"
#include "Renderer.h"

Bullet::Bullet(class Game* game)
:Actor(game)
{
    MeshComponent* mesh = new MeshComponent(this);
    MoveComponent* moveC = new MoveComponent(this);
    mMesh = mesh;
    mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/Sphere.gpmesh"));
    mComponent = moveC;
    CollisionComponent* cc = new CollisionComponent(this);
    mCollision = cc;
    cc->SetSize(10.0f, 10.0f, 10.0f);
    SetScale(0.5f);
    mComponent->SetForwardSpeed(400.0f);
}

void Bullet::UpdateActor(float deltaTime){
    
    //if bullet and block intersect
    for(auto& i : this->mGame->Blocks)
    {
        if(this->GetCollision()->Intersect(i->GetCollision()))
        {
            this->SetState(Bullet::EDead);
        }
    }
    
    //intersects with either of the tanks
    if(this->GetCollision()->Intersect(this->mGame->Player1->GetCollision()))
    {
        // not the firing tank
        if(!(this->mGame->Player1 == FiredTank))
        {
            this->mGame->Player1->Respawn();
            this->SetState(Bullet::EDead);
        }
    }    
    if(this->GetCollision()->Intersect(this->mGame->Player2->GetCollision()))
    {
        // not the firing tank
        if(!(this->mGame->Player2 == FiredTank))
        {
            this->mGame->Player2->Respawn();
            this->SetState(Bullet::EDead);
        }
    }
}
