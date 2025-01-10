#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>

class Ray
{
public:
	glm::vec3 start;
	glm::vec3 dir;
};