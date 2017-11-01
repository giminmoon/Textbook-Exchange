//
//  Block.cpp
//  Game-mac
//
//  Created by Gimin Moon on 10/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include <stdio.h>
#include "Block.h"
#include "Game.h"
#include "Renderer.h"

Block::Block(class Game* game)
:Actor(game)
{
    MeshComponent* mesh = new MeshComponent(this);
    mMesh = mesh;
    mMesh->SetMesh(game->GetRenderer()->GetMesh("Assets/Cube.gpmesh"));
    mScale = 64.0f;
    CollisionComponent* cc = new CollisionComponent(this);
    cc->SetSize(1.0f, 1.0f, 1.0f);
    mCollision = cc;
    mGame->Blocks.push_back(this);
    
}
Block::~Block(){
    
    int i = 0;
    for(auto& block : mGame->Blocks)
    {
        if(block == this)
        {
            mGame->Blocks.erase(mGame->Blocks.begin()+i);
            ////
        }
        i++;
    }
            
}
