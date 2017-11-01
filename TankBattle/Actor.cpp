#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>


Actor::Actor(Game* game)
	:mGame(game)
	,mState(EActive)
	,mPosition(Vector3::Zero)
	,mScale(1.0f)
	,mRotation(0.0f)
    ,mMesh(nullptr)
    ,mComponent(nullptr)
{
    mGame->AddActor(this);
}

Actor::~Actor()
{
    mGame->RemoveActor(this);
    delete mComponent;
    delete mCollision;
    delete mMesh;
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
        if(mMesh)
        {
            mMesh->Update(deltaTime);
        }
        UpdateActor(deltaTime);
        mWorldTransform = (Matrix4::CreateScale(mScale)) * (Matrix4::CreateRotationZ(mRotation)) * (Matrix4::CreateTranslation(mPosition));
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
        //mSprite->ProcessInput(keyState);
        if(mMesh)
        {
            mMesh->ProcessInput(keyState);
        }
        ActorInput(keyState);
    }
}

void Actor::ActorInput(const Uint8* keyState)
{
    
}

Vector3 Actor::GetForward()
{
    Vector3 forward = Vector3(Math::Cos(mRotation), -(Math::Sin(mRotation)),0.0f);
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





