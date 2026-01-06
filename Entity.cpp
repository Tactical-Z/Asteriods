#include "Entity.h"
#include "ofApp.h"
#include "SMath.h"


Entity::~Entity()
{
	for (std::pair<const std::string, Component*>& compPair : mComponents) {
		delete compPair.second;
		compPair.second = nullptr;
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
	mMesh = Mesh(glm::vec2(12,25), glm::vec2(36, 16), glm::vec2(12, 9));
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
		float radius = mTrailRadius * mTransform.mScale.y;
		glm::vec2 backPosition = ((tempPoints[0] + tempPoints[2]) / 2) - ((mTransform.GetForwardVector() * (5 * mTransform.mScale)));
		ofDrawCircle(backPosition, radius);

		ofNoFill();
	}
		
	
}

void Ship::Update(float _dt)
{
	
	
}
