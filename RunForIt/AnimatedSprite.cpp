//
//  AnimatedSprite.cpp
//  Game-mac
//
//  Created by Gimin Moon on 10/6/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "AnimatedSprite.h"
#include <iostream>

AnimatedSprite::AnimatedSprite(class Actor* owner, int drawOrder)
:SpriteComponent(owner, drawOrder)
,mAnimSpeed(15.0)
,mAnimTimer(0.0)
{
    
}

void AnimatedSprite::AddImage(SDL_Texture* image){
    mImages.push_back(image);
}

void AnimatedSprite::Update(float deltaTime){
    
    mAnimTimer += (mAnimSpeed * deltaTime);
    int currentFrame = (int) mAnimTimer;

    if(currentFrame >= mImages.size())
    {
        currentFrame = 0;
        mAnimTimer = 0.0;
    }
    std::cout << currentFrame << std::endl;
    SetTexture(mImages[currentFrame]);
}
