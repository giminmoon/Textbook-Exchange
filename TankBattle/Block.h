//
//  Block.h
//  Game-mac
//
//  Created by Gimin Moon on 10/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef Block_h
#define Block_h
#include "Actor.h"
#include "MeshComponent.h"
class Block : public Actor{
public:
    Block(class Game* game);
    ~Block();
};

#endif /* Block_h */
