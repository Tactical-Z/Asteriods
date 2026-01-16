#pragma once
#include <glm/glm.hpp>

class Component
{
private:
protected:
	class Entity* mParent;
public:

	Component(Entity* _parent);
	~Component();

	virtual void UpdateComponent(float _dt) = 0; 

	Entity* GetParent() { return mParent; }

};

class PhysicsComponent : public Component
{
private:

	glm::vec2 mVelocity = glm::vec2(0.f);
	float mAngularVelocity = 0.f;
	glm::vec2 mAcceleration = glm::vec2(0.f);

protected:
public:

	PhysicsComponent(Entity* _parent);
	~PhysicsComponent();

	void UpdateComponent(float _dt) override;

	void ApplyAcceleration(float _dt);
	void ApplyVelocity(struct Transform* _transform, float _dt);
	void ForceCorrection();

	void SetVelocity(glm::vec2 _newVelocity) { mVelocity = _newVelocity; };
	void SetAngularVelocity(float _newVelocity) { mAngularVelocity = _newVelocity; };
	void SetAcceleration(glm::vec2 _newAcceleration) { mAcceleration = _newAcceleration; };
	void AddVelocity(glm::vec2 _addVelocity) { mVelocity += _addVelocity; };
	void AddAngularVelocity(float _newVelocity) { mAngularVelocity += _newVelocity; };
	void AddAcceleration(glm::vec2 _addAcceleration) { mAcceleration += _addAcceleration; };
};

class CollisionComponent : public Component
{
private:

	bool mCollisionEnabled = true;
	std::vector<Entity*> mIgnoreEntities;

public:
	float mObjectBoundRadius = 0.f;
	glm::vec2 mObjectAABBBounds = glm::vec2(0);

protected:
public:

	CollisionComponent(Entity* _parent);
	~CollisionComponent();

	void SetObjectBounds(Entity* _parent);

	void UpdateComponent(float _dt) override;

	static bool IsIntersecting(CollisionComponent* _colliderA, CollisionComponent* _colliderB);
	static bool BoundingSphereVBoundingSphereIntersect(CollisionComponent* _colliderA, CollisionComponent* _colliderB);
	static bool SATCollision(CollisionComponent* _colliderA, CollisionComponent* _colliderB);

	//bool IsColliding(Entity* _otherObject);
	//bool IsOverlappingBoundingSphere(Entity* _otherObject);
	void AddIgnoreEntity(Entity* _ignoreEntity) { mIgnoreEntities.push_back(_ignoreEntity); };
	std::vector<Entity*>* GetIgnoreEntitiesRef() { return &mIgnoreEntities; };
	bool IsCollisionEnabled() { return mCollisionEnabled; };
	void SetCollisionEnabled(bool _b) { mCollisionEnabled = _b; };
	bool ContainsIgnoreEntity(Entity* _entityToIgnore) { return std::find(mIgnoreEntities.begin(), mIgnoreEntities.end(), _entityToIgnore) != mIgnoreEntities.end(); };
};