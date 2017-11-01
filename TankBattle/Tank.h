//
//  Tank.h
//  Game-mac
//
//  Created by Gimin Moon on 10/19/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef Tank_h
#define Tank_h
#include "Actor.h"
#include "MeshComponent.h"
#include "Turret.h"


class Tank : public Actor{
public:
    Tank(class Game* game);
    Turret* mTurret;
    void UpdateActor(float deltaTime) override;
    void SetPlayerTwo();
    void Respawn();
    void Fire();
    Vector3 OriginalPosition;
    SDL_Scancode mFireKey;
    void ActorInput(const Uint8* keyState) override;
    bool mFireKeyPressed;
    bool mShooting;
};



#endif /* Tank_h */
