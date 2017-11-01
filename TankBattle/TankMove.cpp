//
//  TankMove.cpp
//  Game-mac
//
//  Created by Gimin Moon on 10/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "TankMove.h"
#include "Game.h"

TankMove::TankMove(Actor* owner)
:MoveComponent(owner)
{
    mForwardKey = SDL_SCANCODE_W;
    mBackKey = SDL_SCANCODE_S;
    mRotateClockKey = SDL_SCANCODE_A;
    mRotateCounterKey = SDL_SCANCODE_D;
}
void TankMove::Update(float deltaTime)
{
    MoveComponent::Update(deltaTime);
    //coliision
    
    float tankBot, tankTop, tankLeft, tankRight;
    tankBot = mOwner->GetCollision()->GetMax().y;
    tankTop = mOwner->GetCollision()->GetMin().y;
    tankLeft = mOwner->GetCollision()->GetMin().x;
    tankRight = mOwner->GetCollision()->GetMax().x;
    
    //loop thru all the blocks
    for(int i = 0; i < mOwner->GetGame()->Blocks.size(); i++)
    {
        //collides with the block
        if(mOwner->GetCollision()->Intersect(mOwner->GetGame()->Blocks[i]->GetCollision()))
        {
            
            //case 1 : block's bottom to player's top
            //block's top - player bot
            float case1 = mOwner->GetGame()->Blocks[i]->GetCollision()->GetMin().y - tankBot;
            //case 2: collides with player's bottom and block's top
            float case2 = mOwner->GetGame()->Blocks[i]->GetCollision()->GetMax().y - tankTop;
            //case 3 : collides block left and player right
            float case3 = mOwner->GetGame()->Blocks[i]->GetCollision()->GetMin().x - tankRight;
            //case4 : collides block right with player left
            float case4 = mOwner->GetGame()->Blocks[i]->GetCollision()->GetMax().x - tankLeft;
            
            //find minimum
            float minimum = std::min(std::abs(case1), std::min(std::abs(case2), std::min(std::abs(case3), std::abs(case4))));
            
            //fix dy to players y
            if(minimum == std::abs(case1))
            {
                Vector3 updatePosition(mOwner->GetPosition().x, mOwner->GetPosition().y + case1,0);
                mOwner->SetPosition(updatePosition);
            }
            else if(minimum == std::abs(case2))
            {
                Vector3 updatePosition(mOwner->GetPosition().x, mOwner->GetPosition().y + case2,0);
                mOwner->SetPosition(updatePosition);
                
            }
            else if(minimum == std::abs(case3))
            {
                Vector3 updatePosition(mOwner->GetPosition().x + case3, mOwner->GetPosition().y,0);
                mOwner->SetPosition(updatePosition);
            }
            else{
                Vector3 updatePosition(mOwner->GetPosition().x + case4, mOwner->GetPosition().y,0);
                mOwner->SetPosition(updatePosition);
                
            }
        }
    }
}

void TankMove::ProcessInput(const Uint8 *keyState)
{
    //forward
    if(keyState[mForwardKey]){
        SetForwardSpeed(250);
    }
    else if(keyState[mBackKey])
    {
        SetForwardSpeed(-250);
    }
    else if(keyState[mRotateClockKey])
    {
        SetAngularSpeed(-Math::TwoPi);
    }
    else if(keyState[mRotateCounterKey])
    {
        SetAngularSpeed(Math::TwoPi);
    }
    else
    {
        SetAngularSpeed(0);
        SetForwardSpeed(0);
    }
}

void TankMove::SetPlayTwo(){
    mForwardKey = SDL_SCANCODE_O;
    mBackKey = SDL_SCANCODE_L;
    mRotateCounterKey = SDL_SCANCODE_K;
    mRotateClockKey = SDL_SCANCODE_SEMICOLON;
}
