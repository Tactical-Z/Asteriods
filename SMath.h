#pragma once
#include <glm/glm.hpp>

class SMath
{
public:
	// Applies the transform of the object onto the mesh and returns a vector
	// of points which is the mesh updated with scale, rotation and position.
	static std::vector<glm::vec2> ApplyTransform(struct Transform* _transform, struct Mesh* _mesh);

	// Applies the rotation to the input point by angle, then returns the new point position. 
	static glm::vec2 ApplyRotation(float _rotationAngle, glm::vec2 _point, glm::vec2 _localOriginPos);
};

