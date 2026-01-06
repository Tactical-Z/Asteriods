#include "SMath.h"
#include "Entity.h"
#include <math.h>

std::vector<glm::vec2> SMath::ApplyTransform(Transform* _transform, Mesh* _mesh) {

	std::vector<glm::vec2> tempPoints;

	// for each point apply transform
	for (glm::vec2 point : _mesh->mPoints) {
		glm::vec2 newPoint = point;

		// ----- Scale -----
		newPoint *= _transform->mScale;

		// ----- Rotate -----
		newPoint = SMath::ApplyRotation(_transform->mRotation, newPoint, _mesh->mLocalOriginPos);

		// ----- Move -----
		newPoint += _transform->mPosition;

		tempPoints.push_back(newPoint);
	}

	return tempPoints;
}

glm::vec2 SMath::ApplyRotation(float _rotationAngle, glm::vec2 _point, glm::vec2 _localOriginPos) {

	glm::vec2 point = _point;

	float rad = glm::radians(_rotationAngle);

	// 1. move to origin
	point -= _localOriginPos;

	// rotation matrix
	glm::mat2 rotationMatrix = glm::mat2({ {cos(rad), -sin(rad)},
											{sin(rad), cos(rad)} });

	// 2. rotate points
	point = rotationMatrix * point;

	// 3. move back
	point += _localOriginPos;

	return point;
}