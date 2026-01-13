#pragma once
#include "Component.h"
#include "SMath.h"
#include <glm/glm.hpp>
#include <unordered_map>
#include <string>

struct Transform {
	glm::vec2 mPosition = glm::vec2(0.f);
	float mRotation = 0.f;
	glm::vec2 mScale = glm::vec2(1.f);

	void SetRotation(float _rotation) { mRotation = _rotation; };
	glm::vec2 GetForwardVector() {
		float rad = glm::radians(mRotation);
		return glm::vec2(cos(rad), -sin(rad));
	};
};

struct Mesh {
	std::vector<glm::vec2> mPoints;
	glm::vec2 mLocalOrigin = glm::vec2();
	glm::vec2 mObjectBounds = glm::vec2();
	float mObjectBoundRadius = 0.f;

	Mesh() {
	};

	Mesh(glm::vec2 _p1) {
		mPoints.push_back(_p1);
		UpdateOrigin();
		UpdateBounds();
	};
	Mesh(glm::vec2 _p1, glm::vec2 _p2) {
		mPoints.push_back(_p1);
		mPoints.push_back(_p2);
		UpdateOrigin();
		UpdateBounds();
	};
	Mesh(glm::vec2 _p1, glm::vec2 _p2, glm::vec2 _p3) {
		mPoints.push_back(_p1);
		mPoints.push_back(_p2);
		mPoints.push_back(_p3);
		UpdateOrigin();
		UpdateBounds();
	};
	Mesh(glm::vec2 _p1, glm::vec2 _p2, glm::vec2 _p3, glm::vec2 _p4) {
		mPoints.push_back(_p1);
		mPoints.push_back(_p2);
		mPoints.push_back(_p3);
		mPoints.push_back(_p4);
		UpdateOrigin();
		UpdateBounds();
	};

	void UpdateOrigin() {
	
		for (glm::vec2 point : mPoints) {
			mLocalOrigin += point;
		}
		mLocalOrigin /= mPoints.size();
	}
	void UpdateBounds() {
		
		//float minx = mLocalOrigin.x - ()
		
		float x = 0.f;
		float y = 0.f;
	
		for (glm::vec2 point : mPoints) {
			if (x < abs(point.x)) {
				x = abs(point.x);
			}
			if (y < abs(point.y)) {
				y = abs(point.y);
			}
		}
		mObjectBounds = glm::vec2(x, y);
		
		float r = 0.f;
		for (glm::vec2 point : mPoints) {
			float dist = SMath::GetDistanceBetweenTwoPoints(mLocalOrigin, point);
			if (r < dist) {
				r = dist;
			}
		}
		mObjectBoundRadius = r;
	}
};

class Entity {
private:
	
protected:
	Transform mTransform;
	Mesh mMesh;
	std::unordered_map<std::string, Component*> mComponents;
public:

	Entity() = default;
	~Entity();

	virtual void Draw() = 0;
	void DrawDebug();
	virtual void UpdateEntityComponent(float _dt);
	virtual void Update(float _dt) = 0;
	template <typename T>
	void AddComponent(std::string _componentName) {
		if (!mComponents.contains(_componentName)) {
			mComponents.insert(std::pair<std::string, Component*>(_componentName, new T(this)));
		}
	}

	template <typename T>
	T* GetComponent() {
		for (std::pair<const std::string, Component*>& compPair : mComponents) {
			T* correctComp = dynamic_cast<T*>(compPair.second);
			if (correctComp)
				return correctComp;
		}
		return nullptr;
	}

	Transform* GetTransformRef() { return &mTransform; };
	glm::vec2 GetForwardVector() { return mTransform.GetForwardVector();}
	glm::vec2 GetPosition() { return mTransform.mPosition; }
	void SetPosition(glm::vec2 _newPos) { mTransform.mPosition = _newPos; }
	glm::vec2 GetScale() { return mTransform.mScale; }
	void SetScale(glm::vec2 _newScale) { mTransform.mScale = _newScale; }
	float GetRotation() { return mTransform.mRotation; }
	void SetRotation(float _newRotation) { mTransform.mRotation = _newRotation; }
};

class Ship : public Entity {
private: 

	float mTrailRadius = 4.f;
	float mCurveStrength = 20.f;
	bool mAccelerating = false;

public:
	
	Ship();
	~Ship();

	void Draw() override;
	void Update(float _dt) override;

	void SetIsAccelerating(bool _t) { mAccelerating = _t; };
};

class Asteroid : public Entity {
private:

public:

	Asteroid();
	~Asteroid();

	void Draw() override;
	void Update(float _dt) override;
};

class Bullet : public Entity {
private:

	float mBulletSize = 2.5f;

public:

	Bullet();
	~Bullet();

	void Draw() override;
	void Update(float _dt) override;
};