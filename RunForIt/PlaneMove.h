//
//  PlaneMove.h
//  Game-mac
//
//  Created by Gimin Moon on 10/16/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef PlaneMove_h
#define PlaneMove_h
#include "MoveComponent.h"
#include "Tile.h"


class PlaneMove : public MoveComponent{
public:
    PlaneMove(Actor* actor);
    void Update(float deltaTime) override;
    const Tile* mNextTile;
    void SetNextTile(const Tile* tile);
};


#endif /* PlaneMove_h */
