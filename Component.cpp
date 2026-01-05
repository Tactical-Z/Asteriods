#include "Component.h"
#include "Entity.h"

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

	mAcceleration = glm::vec2(0);
}

void PhysicsComponent::ApplyAcceleration(float _dt)
{
	mVelocity += mAcceleration * _dt;
}

void PhysicsComponent::ApplyVelocity(Transform& _transform, float _dt)
{
	_transform.mPosition += mVelocity * _dt;
	_transform.mRotation += mConstAngularVelocity * _dt;
}