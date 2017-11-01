//
//  Plane.h
//  Game-mac
//
//  Created by Gimin Moon on 10/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef Plane_h
#define Plane_h
#include "Actor.h"
#include "PlaneMove.h"

class Plane : public Actor{
public:
    Plane(Game* game);
    ~Plane();
};

#endif /* Plane_h */
