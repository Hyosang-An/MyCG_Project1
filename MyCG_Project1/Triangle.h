#pragma once

#include "Object.h"

using namespace glm;

class Triangle : public Object
{
public:
	vec3 v0, v1, v2; // �ﰢ���� �� ������
    vec2 uv0, uv1, uv2; // �ڿ��� �ؽ��� ��ǥ��� ���

public:
    Triangle()
        : v0(vec3(0.0f)), v1(vec3(0.0f)), v2(vec3(0.0f)), uv0(vec2(0.0f)), uv1(vec2(0.0f)), uv2(vec2(0.0f))
    {
    }

    Triangle(vec3 v0, vec3 v1, vec3 v2, vec2 uv0 = vec2(0.0f), vec2 uv1 = vec2(0.0f), vec2 uv2 = vec2(0.0f))
        : v0(v0), v1(v1), v2(v2), uv0(uv0), uv1(uv1), uv2(uv2)
    {
    }

	virtual Hit CheckRayCollision(Ray& ray) override
    {
        Hit hit = Hit{ -1.0, vec3(0.0), vec3(0.0) };

        vec3 point, faceNormal;
        float t, w0, w1;
        if (IntersectRayTriangle(ray.start, ray.dir, this->v0, this->v1,
            this->v2, point, faceNormal, t, w0, w1))
        {
            hit.d = t;
            hit.point = point; // ray.start + ray.dir * t;
            hit.normal = faceNormal;
            hit.uv = uv0 * w0 + uv1 * w1 + uv2 * (1.0f - w0 - w1); // �ؽ��� ��ǥ
        }

        return hit;
    }

    // ����: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
    bool IntersectRayTriangle(const vec3& orig, const vec3& dir,
        const vec3& v0, const vec3& v1,
        const vec3& v2, vec3& point, vec3& faceNormal,
        float& t, float& w0, float& w1)
    {
        /*
         * �⺻ ����
         * - �ﰢ���� �����ִ� ���� ������ ������ ã��,
         * - �� ������ �ﰢ�� �ȿ� �ִ��� �ۿ� �ִ����� �Ǵ��Ѵ�.
         */

         /* 1. �ﰢ���� ���� �ִ� ����� ���� ���� ��� */
        faceNormal = glm::normalize(glm::cross(v1 - v0, v2 - v0));
        //����: �ﰢ���� ���̰� 0�� ��쿡�� ����� �� ����

        // �ﰢ�� �޸��� �׸��� ���� ���� ��� (Backface culling)
        if (dot(-dir, faceNormal) < 0.0f)
            return false;

        // ���� ������ ���� �ſ� �����ٸ� �浹���� ���ϴ� ������ �Ǵ�
        if (glm::abs(dot(dir, faceNormal)) < 1e-2f)
            return false; // t ���� 0���� ������ ����

        /* 2. ������ ����� �浹 ��ġ ��� */
        t = (dot(v0, faceNormal) - dot(orig, faceNormal)) /
            (dot(dir, faceNormal));

        // ������ ������ ������ �浹�Ѵٸ� �������� �ʿ� ����
        if (t < 0.0f)
            return false;

        point = orig + t * dir; // �浹��

        /* 3. �� �浹 ��ġ�� �ﰢ�� �ȿ� ��� �ִ� �� Ȯ�� */

        // ���� �ﰢ���� 3���� normal ���
        // ���⸸ Ȯ���ϸ� �Ǳ� ������ normalize() ���� ����
        const vec3 cross0 = glm::cross(point - v2, v1 - v2);
        const vec3 cross1 = glm::cross(point - v0, v2 - v0);
        const vec3 cross2 = glm::cross(v1 - v0, point - v0);

        if (dot(cross0, faceNormal) < 0.0f)
            return false;
        if (dot(cross1, faceNormal) < 0.0f)
            return false;
        if (dot(cross2, faceNormal) < 0.0f)
            return false;

        // Barycentric coordinates ���
        // �ؽ��縵(texturing)���� ���
        // �Ʒ����� cross product�� ���밪���� ���� �ﰢ������ ���� ���

        const float area0 = glm::length(cross0) * 0.5f;
        const float area1 = glm::length(cross1) * 0.5f;
        const float area2 = glm::length(cross2) * 0.5f;

        // const float areaSum = glm::length(glm::cross(v1 - v0, v2 - v0)) * 0.5f;
        const float areaSum = area0 + area1 + area2;

        w0 = area0 / areaSum; // ��ȣ�� alpha, beta, gamma �Ǵ� u, v, w ���� ����ϱ⵵ ��
        w1 = area1 / areaSum;
        // w2 = area2 / areaSum �Ǵ� w2 = 1.0f - w0 - w1

        return true;
    }
};