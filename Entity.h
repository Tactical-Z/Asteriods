#pragma once

#include <glm/glm.hpp>

struct Transform {
	glm::vec2 mPosition = glm::vec2(0.f);
	float mRotation = 0.f;
	glm::vec2 mScale = glm::vec2(1.f);
};

struct Mesh {
	std::vector<glm::vec2> mPoints;
	glm::vec2 mLocalOriginPos = glm::vec2();

	Mesh() {
	};

	Mesh(glm::vec2 _p1) {
		mPoints.push_back(_p1);
	};
	Mesh(glm::vec2 _p1, glm::vec2 _p2) {
		mPoints.push_back(_p1);
		mPoints.push_back(_p2);
	};
	Mesh(glm::vec2 _p1, glm::vec2 _p2, glm::vec2 _p3) {
		mPoints.push_back(_p1);
		mPoints.push_back(_p2);
		mPoints.push_back(_p3);
		mLocalOriginPos = glm::vec2(((_p1.x + _p2.x + _p3.x) / 3), ((_p1.y + _p2.y + _p3.y) / 3));
	};
	Mesh(glm::vec2 _p1, glm::vec2 _p2, glm::vec2 _p3, glm::vec2 _p4) {
		mPoints.push_back(_p1);
		mPoints.push_back(_p2);
		mPoints.push_back(_p3);
		mPoints.push_back(_p4);
	};
};

class Entity {
private:
	
protected:
	Transform mTransform;
	Mesh mMesh;

public:

	
	Entity();
	~Entity();

	virtual void Draw() = 0;
	virtual void Update(float _dt) = 0;
};

class Ship : public Entity {
private: 

	float mCurveStrength = 20.f;

public:
	
	Ship();
	~Ship();

	void Draw() override;
	void Update(float _dt) override;

};