//
//  Tank.cpp
//  Game-mac
//
//  Created by Gimin Moon on 10/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Tank.h"
#include "Game.h"
#include "Renderer.h"
#include "Bullet.h"
#include "TankMove.h"

Tank::Tank(class Game* game)
:Actor(game)
,mFireKey(SDL_SCANCODE_LSHIFT)
,mShooting(false)
{
    MeshComponent* mesh = new MeshComponent(this);
    TankMove* moveC = new TankMove(this);
    mMesh = mesh;
    mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/TankBase.gpmesh"));
    mComponent = moveC;
    Turret* turret = new Turret(game);
    mTurret = turret;
    CollisionComponent* cc = new CollisionComponent(this);
    cc->SetSize(30.0f, 30.0f, 30.0f);
    mCollision = cc;
}

void Tank::UpdateActor(float deltaTime){
    mTurret->SetPosition(this->GetPosition());
}

void Tank::SetPlayerTwo(){
    TankMove* tm = dynamic_cast<TankMove*>(mComponent);
    tm->SetPlayTwo();
    mTurret->SetPlayerTwo();
    mMesh->SetTextureIndex(1);
    mFireKey = SDL_SCANCODE_RSHIFT;
}
void Tank::Respawn(){
    this->SetPosition(OriginalPosition);
    this->SetRotation(0.0f);
    mTurret->SetRotation(0.0f);
}
void Tank::Fire(){
    Bullet* bullet = new Bullet(this->mGame);
    bullet->SetPosition(this->GetPosition());
    bullet->SetRotation(-mTurret->GetRotation());
    bullet->FiredTank = this;
}

void Tank::ActorInput(const Uint8 *keyState)
{
    if(keyState[mFireKey])
    {
        //finding leading edge
        if(!mFireKeyPressed)
        {
            Fire();
        }
        else{
            mFireKeyPressed = true;
        }
    }
    else{
        mFireKeyPressed = false;
    }
}

