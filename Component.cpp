#include "Component.h"
#include "Entity.h"
#include "GameConstants.h"
#include "ofApp.h"

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

void PhysicsComponent::ApplyVelocity(Transform* _transform, float _dt)
{
	_transform->mPosition += mVelocity * _dt;
	_transform->mRotation += mAngularVelocity * _dt;
}

void PhysicsComponent::ForceCorrection()
{
	mVelocity.x = (mVelocity.x > sPlayerShipMaxVelocity) ? sPlayerShipMaxVelocity : mVelocity.x;
	mVelocity.x = (mVelocity.x < -sPlayerShipMaxVelocity) ? -sPlayerShipMaxVelocity : mVelocity.x;
	mVelocity.y = (mVelocity.y > sPlayerShipMaxVelocity) ? sPlayerShipMaxVelocity : mVelocity.y;
	mVelocity.y = (mVelocity.y < -sPlayerShipMaxVelocity) ? -sPlayerShipMaxVelocity : mVelocity.y;
	mAngularVelocity = (mAngularVelocity > sPlayerShipMaxAngularVelocity) ? sPlayerShipMaxAngularVelocity : mAngularVelocity;
	mAngularVelocity = (mAngularVelocity < -sPlayerShipMaxAngularVelocity) ? -sPlayerShipMaxAngularVelocity : mAngularVelocity;
	mAcceleration = glm::vec2(0);
}

CollisionComponent::CollisionComponent(Entity* _parent)
	: Component(_parent)
{
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::UpdateComponent(float _dt)
{

}

bool CollisionComponent::IsIntersecting(CollisionComponent* _colliderA, CollisionComponent* _colliderB)
{

	// Bounding Sphere intesect
	if (BoundingSphereVBoundingSphereIntersect(_colliderA, _colliderB)) {
		return true;

		// Complex intersect
	}



	return false;
}

bool CollisionComponent::BoundingSphereVBoundingSphereIntersect(CollisionComponent* _colliderA, CollisionComponent* _colliderB)
{
	Transform* transformA = _colliderA->GetParent()->GetTransformRef();
	Transform* transformB = _colliderB->GetParent()->GetTransformRef();
	Mesh* meshA = _colliderA->GetParent()->GetMeshRef();
	Mesh* meshB = _colliderB->GetParent()->GetMeshRef();
	
	glm::vec2 centreDist = (transformB->mPosition - transformA->mPosition);
	float totalDistance = glm::dot(centreDist, centreDist);

	// apply scale transform:
	float maxScale = std::max(transformB->mScale.x, transformB->mScale.y);
	float radiusSum = pow((meshA->mObjectBoundRadius + (meshB->mObjectBoundRadius * maxScale)), 2);

	if (totalDistance <= radiusSum) {
		return true;
	}

	return false;
}

