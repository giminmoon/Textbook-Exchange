//
//  AnimatedSprite.hpp
//  Game-mac
//
//  Created by Gimin Moon on 10/6/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef AnimatedSprite_hpp
#define AnimatedSprite_hpp
#include "SpriteComponent.h"
#include "Actor.h"
#include <stdio.h>

class AnimatedSprite:public SpriteComponent{
public:
    AnimatedSprite(class Actor* owner, int drawOrder);
    std::vector<SDL_Texture*> mImages;
    float mAnimTimer;
    float mAnimSpeed;
    void AddImage(SDL_Texture* image);
    void Update(float deltaTime) override;
};

#endif /* AnimatedSprite_hpp */
