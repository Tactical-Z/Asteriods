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

};

class PhysicsComponent : public Component
{
private:

	glm::vec2 mVelocity = glm::vec2(0.f);
	float mConstAngularVelocity = 0.f;
	glm::vec2 mAcceleration = glm::vec2(0.f);

protected:
public:

	PhysicsComponent(Entity* _parent);
	~PhysicsComponent();

	void UpdateComponent(float _dt) override;

	void ApplyAcceleration(float _dt);
	void ApplyVelocity(struct Transform& _transform, float _dt);

	void SetVelocity(glm::vec2 _newVelocity) { mVelocity = _newVelocity; };
	void SetAngularVelocity(float _newVelocity) { mConstAngularVelocity = _newVelocity; };
	void SetAcceleration(glm::vec2 _newAcceleration) { mAcceleration = _newAcceleration; };
	void AddVelocity(glm::vec2 _addVelocity) { mVelocity += _addVelocity; };
	void AddAngularVelocity(float _newVelocity) { mConstAngularVelocity += _newVelocity; };
	void AddAcceleration(glm::vec2 _addAcceleration) { mAcceleration += _addAcceleration; };
};