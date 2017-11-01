//
//  Turret.cpp
//  Game-mac
//
//  Created by Gimin Moon on 10/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Turret.h"
#include "Game.h"
#include "Renderer.h"

Turret::Turret(class Game* game)
:Actor(game)
{
    MeshComponent* mesh = new MeshComponent(this);
    MoveComponent* moveC = new MoveComponent(this);
    mMesh = mesh;
    mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/TankTurret.gpmesh"));
    mComponent = moveC;
    mScale = 1.8f;
    mRotateClockKey = SDL_SCANCODE_E;
    mRotateCounterKey = SDL_SCANCODE_Q;
}
void Turret::ActorInput(const Uint8 *keyState)
{
    if(keyState[mRotateCounterKey]){
        mComponent->SetAngularSpeed(Math::TwoPi);
        SetRotation(GetRotation()+Math::TwoPi);
    }
    else if(keyState[mRotateClockKey]){
        mComponent->SetAngularSpeed(-Math::TwoPi);
        SetRotation(GetRotation()-Math::TwoPi);
    }
    else{
        mComponent->SetAngularSpeed(0);
    }
}

void Turret::SetPlayerTwo(){
    mRotateClockKey = SDL_SCANCODE_P;
    mRotateCounterKey = SDL_SCANCODE_I;
    mMesh->SetTextureIndex(1);
}
