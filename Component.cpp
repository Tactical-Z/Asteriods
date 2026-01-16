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
	SetObjectBounds(_parent);
}

CollisionComponent::~CollisionComponent()
{
}

void CollisionComponent::SetObjectBounds(Entity* _parent)
{
	float x = 0.f;
	float y = 0.f;

	for (glm::vec2 point : _parent->GetMeshRef()->mPoints) {
		if (x < abs(point.x)) {
			x = abs(point.x);
		}
		if (y < abs(point.y)) {
			y = abs(point.y);
		}
	}
	mObjectAABBBounds = glm::vec2(x, y);

	float r = 0.f;
	for (glm::vec2 point : _parent->GetMeshRef()->mPoints) {
		float dist = SMath::GetDistanceBetweenTwoPoints(_parent->GetMeshRef()->mLocalOrigin, point);
		if (r < dist) {
			r = dist;
		}
	}
	mObjectBoundRadius = r;
}

void CollisionComponent::UpdateComponent(float _dt)
{

}

bool CollisionComponent::IsIntersecting(CollisionComponent* _colliderA, CollisionComponent* _colliderB)
{

	// Bounding Sphere intesect
	if (BoundingSphereVBoundingSphereIntersect(_colliderA, _colliderB)) {
		
		// Check complex intersect
		if(SATCollision(_colliderA, _colliderB))
			return true;
		return false;
	
	}

	return false;
}

bool CollisionComponent::BoundingSphereVBoundingSphereIntersect(CollisionComponent* _colliderA, CollisionComponent* _colliderB)
{

	glm::vec2 ObjAPos = _colliderA->GetParent()->GetPosition();
	glm::vec2 ObjBPos = _colliderB->GetParent()->GetPosition();
	float ObjAMaxScale = _colliderA->GetParent()->GetMaxScale();
	float ObjBMaxScale = _colliderB->GetParent()->GetMaxScale();

	glm::vec2 centreDist = (ObjBPos - ObjAPos);
	float totalDistance = glm::dot(centreDist, centreDist);

	// apply scale transform
	float radiusSum = pow(((_colliderA->mObjectBoundRadius * ObjAMaxScale) + (_colliderB->mObjectBoundRadius * ObjBMaxScale)), 2);

	if (totalDistance <= radiusSum) {
		return true;
	}

	return false;
}

bool CollisionComponent::SATCollision(CollisionComponent* _colliderA, CollisionComponent* _colliderB)
{
	glm::vec2 ObjAPos = _colliderA->GetParent()->GetPosition();
	glm::vec2 ObjBPos = _colliderB->GetParent()->GetPosition();
	float ObjAMaxScale = _colliderA->GetParent()->GetMaxScale();
	float ObjBMaxScale = _colliderB->GetParent()->GetMaxScale();

	// 1. for each object Simplify to convex hulls
	// 2. for each hull calculate side normals 
	// 3. for each normal project onto each axis
	// 4. for each axis check for overlap
	// 5. (compute minimum translation vector)
	// 6. (Handel edge cases)
	// 7. (account for object rotation/movement)


	return false;
}

