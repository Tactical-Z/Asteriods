#include "Entity.h"
#include "ofApp.h"
#include "GameConstants.h"
#include "SMath.h"


Entity::~Entity()
{
	for (std::pair<const std::string, Component*>& compPair : mComponents) {
		delete compPair.second;
		compPair.second = nullptr;
	}
}

void Entity::DrawDebug()
{
	if (DEBUG) {
		ofSetColor(255, 0, 0);
		// Sphere bounding area
		glm::vec2 position = mMesh.mLocalOrigin + mTransform.mPosition;
		float maxScale = std::max(mTransform.mScale.x, mTransform.mScale.y);
		float radius = mMesh.mObjectBoundRadius * maxScale;
		ofDrawCircle(position, radius);
		ofSetColor(255, 255, 255);
	}
}

void Entity::UpdateEntityComponent(float _dt)
{
	for (std::pair<std::string, Component*> compPair : mComponents) {
		compPair.second->UpdateComponent(_dt);
	}
}

Ship::Ship()
{
	mMesh = Mesh(glm::vec2(-8,8), glm::vec2(16, -1), glm::vec2(-8, -8));
}

Ship::~Ship()
{
}

void Ship::Draw()
{
	std::vector<glm::vec2> tempPoints = SMath::ApplyTransform(&mTransform, &mMesh);
	
	// Calculate curve points
	glm::vec2 edge = tempPoints[2] - tempPoints[0];
	glm::vec2 normal(edge.y, -edge.x);
	normal = glm::normalize(normal);
	glm::vec2 curvePointOne = tempPoints[0] + normal * mCurveStrength;
	glm::vec2 curvePointTwo = tempPoints[2] + normal * mCurveStrength;

	ofDrawLine(tempPoints[0], tempPoints[1]);
	ofDrawLine(tempPoints[1], tempPoints[2]);
	ofDrawCurve(curvePointOne.x, curvePointOne.y, tempPoints[0].x, tempPoints[0].y, tempPoints[2].x, tempPoints[2].y, curvePointTwo.x, curvePointTwo.y);

	if (mAccelerating) {
		ofFill();
		float maxScale = std::max(mTransform.mScale.x, mTransform.mScale.y);
		float radius = mTrailRadius * maxScale;
		glm::vec2 backPosition = ((tempPoints[0] + tempPoints[2]) / 2) - ((mTransform.GetForwardVector() * (5 * mTransform.mScale)));
		ofDrawCircle(backPosition, radius);

		ofNoFill();
	}
		
	DrawDebug();
}

void Ship::Update(float _dt)
{
	
	
}

Asteroid::Asteroid()
{
	mMesh = Mesh(glm::vec2(-5, -5), glm::vec2(-5, 10), glm::vec2(5, -5), glm::vec2(5,5));
}

Asteroid::~Asteroid()
{
}

void Asteroid::Draw()
{
	std::vector<glm::vec2> tempPoints = SMath::ApplyTransform(&mTransform, &mMesh);

	ofDrawLine(tempPoints[0], tempPoints[1]);
	ofDrawLine(tempPoints[0], tempPoints[2]);
	ofDrawLine(tempPoints[3], tempPoints[1]);
	ofDrawLine(tempPoints[3], tempPoints[2]);
	
	
	DrawDebug();
	
	
}

void Asteroid::Update(float _dt)
{

}

Bullet::Bullet()
{
	mMesh = Mesh(glm::vec2(0, 0));
}

Bullet::~Bullet()
{
}

void Bullet::Draw()
{
	std::vector<glm::vec2> tempPoints = SMath::ApplyTransform(&mTransform, &mMesh);
	float maxScale = std::max(mTransform.mScale.x, mTransform.mScale.y);
	float radius = mBulletSize * maxScale;
	ofDrawCircle(tempPoints[0], radius);
}

void Bullet::Update(float _dt)
{
}
