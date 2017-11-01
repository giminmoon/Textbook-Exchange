#include "MoveComponent.h"

#include "Actor.h"
#include <iostream>
MoveComponent::MoveComponent(class Actor* owner)
:Component(owner)
,mAngularSpeed(0.0f)
,mForwardSpeed(0.0f)
{
	
}

void MoveComponent::Update(float deltaTime)
{
    //update actor's rotation
    float rotation = deltaTime * mAngularSpeed;
    this->mOwner->SetRotation(this->mOwner->GetRotation() + rotation);
    
    //velocity = foward vector * speed
    Vector2 velocity = this->mOwner->GetForward() * mForwardSpeed;
    
    //position += velocity * deltaTime
    
    Vector2 originalPosition = (this->mOwner->GetPosition());
    
    //update
    this->mOwner->SetPosition(originalPosition += velocity*deltaTime);
}
