#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

class Object;

class Hit
{
public:
	float d; // distance
	glm::vec3 point; // hit point
	glm::vec3 normal; // normal vector
	glm::vec2 uv; // texture coordinate

	std::shared_ptr<Object> obj; // hit object
};