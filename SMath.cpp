#include "SMath.h"
#include "Entity.h"
#include <math.h>

std::vector<glm::vec2> SMath::ApplyTransform(Transform* _transform, Mesh* _mesh) {
	std::vector<glm::vec2> tempPoints;

	// for each point apply transform
	for (glm::vec2& point : _mesh->mPoints) {

		glm::vec2 newPoint = point;

		//  move to origin
		newPoint -= _mesh->mLocalOrigin;

		// ----- Scale -----
		newPoint *= _transform->mScale;

		// ----- Rotate -----
		newPoint = SMath::ApplyRotation(_transform->mRotation, newPoint);

		// ----- Move -----
		newPoint += _transform->mPosition;

		// move back
		newPoint += _mesh->mLocalOrigin;

		tempPoints.push_back(newPoint);
	}
	return tempPoints;
}

glm::vec2 SMath::ApplyRotation(float _rotationAngle, glm::vec2 _point) {

	glm::vec2 point = _point;

	float rad = glm::radians(_rotationAngle);

	// rotation matrix
	glm::mat2 rotationMatrix = glm::mat2({ {cos(rad), -sin(rad)},
											{sin(rad), cos(rad)} });

	// rotate points
	point = rotationMatrix * point;

	return point;
}

float SMath::GetDistanceBetweenTwoPoints(glm::vec2 _pointOne, glm::vec2 _pointTwo)
{
	return (float)std::sqrt(std::pow(_pointTwo.x - _pointOne.x,2) + std::pow(_pointTwo.y - _pointOne.y,2));
}
