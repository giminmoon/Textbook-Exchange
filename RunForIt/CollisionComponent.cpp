#include "CollisionComponent.h"
#include "Actor.h"
#include <iostream>
CollisionComponent::CollisionComponent(class Actor* owner)
:Component(owner)
,mWidth(0.0f)
,mHeight(0.0f)
{
	
}

CollisionComponent::~CollisionComponent()
{
	
}

bool CollisionComponent::Intersect(const CollisionComponent* other)
{
    
	if(this->GetMax().x < other->GetMin().x)
    {
        return false;
    }
    if(other->GetMax().x < this->GetMin().x)
    {
        return false;
    }
    if(this->GetMax().y < other->GetMin().y)
    {
        return false;
    }
    if(other->GetMax().y < this->GetMin().y)
    {
        return false;
    }
    return true;
}


Vector2 CollisionComponent::GetMin() const
{
	// TODO: Implement
    float scale = this->mOwner->GetScale();
   
    Vector2 min(this->mOwner->GetPosition().x - mWidth*scale / 2.0f,
                this->mOwner->GetPosition().y - mHeight*scale / 2.0f);
    return min;
}

Vector2 CollisionComponent::GetMax() const
{
    float scale = this->mOwner->GetScale();

    Vector2 max(this->mOwner->GetPosition().x + mWidth*scale / 2.0f,
                this->mOwner->GetPosition().y + mHeight*scale / 2.0f);
    return max;
}

const Vector2& CollisionComponent::GetCenter() const
{
	return mOwner->GetPosition();
}

