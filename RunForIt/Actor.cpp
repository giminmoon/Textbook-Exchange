#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game* game)
	:mGame(game)
	,mState(EActive)
	,mPosition(Vector2::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
    ,mSprite(nullptr)
    ,mComponent(nullptr)
{
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);
    delete mSprite;
    delete mComponent;
    delete mCollision;
}

void Actor::Update(float deltaTime)
{
	if(mState == EActive)
    {
        //update components??
        
        if(mComponent != nullptr)
        {
            mComponent->Update(deltaTime);

        }
        if(mSprite != nullptr)
        {
            mSprite->Update(deltaTime);
            
        }
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{
}

void Actor::ProcessInput(const Uint8* keyState)
{
    if(mState == EActive){
        if(mComponent != nullptr)
        {
            mComponent->ProcessInput(keyState);
        }
        if(mSprite != nullptr)
        {
            mSprite->ProcessInput(keyState);
        }
        
        //mSprite->ProcessInput(keyState);
        
        ActorInput(keyState);
    }
}

void Actor::ActorInput(const Uint8* keyState)
{
    
}

SpriteComponent* Actor::GetSprite()
{
    return mSprite;
}

void Actor::SetSprite(SpriteComponent* sprite)
{
    mSprite = sprite;
}

Vector2 Actor::GetForward()
{
    Vector2 forward = Vector2(Math::Cos(mRotation), -(Math::Sin(mRotation)));
    return forward;
}

MoveComponent* Actor::GetComponent()
{
    return mComponent;
}

CollisionComponent* Actor::GetCollision()
{
    return mCollision;
}





