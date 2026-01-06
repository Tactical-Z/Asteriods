#include "Component.h"
#include "Entity.h"
#include "GameConstants.h"

Component::Component(Entity* _parent)
	: mParent(_parent) 
{
}

Component::~Component()
{
	mParent = nullptr;
}

PhysicsComponent::PhysicsComponent(Entity* _parent)
	: Component(_parent)
{
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::UpdateComponent(float _dt)
{
	if (!mParent) return;

	ApplyAcceleration(_dt); // adds acceleration to velocity
	ApplyVelocity(mParent->GetTransformRef(), _dt); // adds velocity to transform

	ForceCorrection();
}

void PhysicsComponent::ApplyAcceleration(float _dt)
{
	mVelocity += mAcceleration * _dt;
}

void PhysicsComponent::ApplyVelocity(Transform& _transform, float _dt)
{
	_transform.mPosition += mVelocity * _dt;
	_transform.mRotation += mAngularVelocity * _dt;
}

void PhysicsComponent::ForceCorrection()
{
	mVelocity.x = (mVelocity.x > sPlayerShipMaxVelocity) ? sPlayerShipMaxVelocity : mVelocity.x;
	mVelocity.y = (mVelocity.y > sPlayerShipMaxVelocity) ? sPlayerShipMaxVelocity : mVelocity.y;
	mAngularVelocity = (mAngularVelocity > sPlayerShipMaxAngularVelocity) ? sPlayerShipMaxAngularVelocity : mAngularVelocity;
	mAcceleration = glm::vec2(0);
}
