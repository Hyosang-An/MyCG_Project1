#pragma once

#include "Triangle.h"

class Square : public Object
{
public:
    Triangle triangle1, triangle2;

    Square(vec3 LT, vec3 RT, vec3 RB, vec3 LB, vec2 uv_LT = vec2(0.0f), vec2 uv_RT = vec2(1, 0), vec2 uv_RB = vec2(1, 1), vec2 uv_LB = vec2(0, 1))
        : triangle1(LT, RT, RB), triangle2(LT, RB, LB)
    {
        triangle1.uv0 = uv_LT;
        triangle1.uv1 = uv_RT;
        triangle1.uv2 = uv_RB;

        triangle2.uv0 = uv_LT;
        triangle2.uv1 = uv_RB;
        triangle2.uv2 = uv_LB;
    }

	virtual Hit CheckRayCollision(Ray& ray) override
    {
        auto hit1 = triangle1.CheckRayCollision(ray);
        auto hit2 = triangle2.CheckRayCollision(ray);

        if (hit1.d >= 0.0f && hit2.d >= 0.0f)
        {
            return hit1.d < hit2.d ? hit1 : hit2;
        }
        else if (hit1.d >= 0.0f)
        {
            return hit1;
        }
        else
        {
            return hit2;
        }
    }
};