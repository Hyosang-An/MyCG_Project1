#pragma once

#include <vector>

#include "Ray.h"
#include "Light.h"
#include "Hit.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Square.h"


using namespace std;
using namespace glm;

class Raytracer
{
public:
	int width, height;
	Light light;

	shared_ptr<Sphere> reflecting_sphere1;
	shared_ptr<Sphere> reflecting_sphere2;
	shared_ptr<Sphere> transparent_sphere1;
	shared_ptr<Sphere> transparent_sphere2;

	vector<shared_ptr<Object>> objects;

	Raytracer(const int& width, const int& height)
		: width(width), height(height)
	{

		light = Light{ {0.0f, 2.5f, 0.5f} }; // 화면 뒷쪽

		// ================================================
		// 물체들
		// ================================================

		// Reflecting Sphere1
		reflecting_sphere1 = make_shared<Sphere>(vec3(0.f, -1.f, 3.5f), 1.0f);

		reflecting_sphere1->amb = vec3(0.0f);
		reflecting_sphere1->dif = vec3(0.0f, 0.0f, 1.0f);
		reflecting_sphere1->spec = vec3(0.0f);
		reflecting_sphere1->alpha = 50.0f;
		reflecting_sphere1->reflection = 0.5f;
		reflecting_sphere1->transparency = 0.0f;

		objects.push_back(reflecting_sphere1);

		// Reflecting Sphere2
		reflecting_sphere2 = make_shared<Sphere>(vec3(-2.f, -1.f, 3.5f), 1.0f);

		reflecting_sphere2->amb = vec3(0.0f);
		reflecting_sphere2->dif = vec3(0.6f, 0.0f, 0.0f);
		reflecting_sphere2->spec = vec3(0.0f);
		reflecting_sphere2->alpha = 50.0f;
		reflecting_sphere2->reflection = 0.5f;
		reflecting_sphere2->transparency = 0.0f;

		objects.push_back(reflecting_sphere2);

		// Transparent Sphere1
		transparent_sphere1 = make_shared<Sphere>(vec3(2.f, 0.f, 3.5f), 1.0f);

		transparent_sphere1->amb = vec3(0.0f);
		transparent_sphere1->dif = vec3(0.0f, 0.0f, 0.6f);
		transparent_sphere1->spec = vec3(0.0f);
		transparent_sphere1->alpha = 50.0f;
		transparent_sphere1->reflection = 0.0f;
		transparent_sphere1->transparency = 0.8f;

		objects.push_back(transparent_sphere1);

		// Transparent Sphere2
		transparent_sphere2 = make_shared<Sphere>(vec3(0.f, 1.5f, 3.5f), 1.0f);

		transparent_sphere2->amb = vec3(0.0f);
		transparent_sphere2->dif = vec3(0.0f, 0.0f, 0.0f);
		transparent_sphere2->spec = vec3(0.0f);
		transparent_sphere2->alpha = 50.0f;
		transparent_sphere2->reflection = 0.0f;
		transparent_sphere2->transparency = 1.f;

		objects.push_back(transparent_sphere2);



		// ground
		auto table_texture = std::make_shared<Texture>("marble_table.jpg");

		auto ground = make_shared<Square>(vec3(-5.f, -2.f, 8.f), vec3(5.f, -2.f, 8.f), vec3(5.f, -2.f, 0.f), vec3(-5.f, -2.f, 0.0f));

		ground->amb = vec3(0.2f);
		ground->dif = vec3(0.8f);
		ground->spec = vec3(1.0f);
		ground->alpha = 10.0f;
		ground->reflection = 0.2f;
		ground->ambTexture = table_texture;
		ground->difTexture = table_texture;

		objects.push_back(ground);

		// ================================================
		// Saint Peter's Basilica (주변	환경)
		// ================================================
		const float d = 20;

		// front
		auto squareTexture = std::make_shared<Texture>("SaintPetersBasilica\\posz.jpg");
		auto square = make_shared<Square>(vec3(-d, d, d), vec3(d, d, d), vec3(d, -d, d), vec3(-d, -d, d));

		square->amb = vec3(1.0f);
		square->dif = vec3(0.0f);
		square->spec = vec3(0.0f);
		square->alpha = 10.0f;
		square->reflection = 0.0f;
		square->ambTexture = squareTexture;
		square->difTexture = squareTexture;

		objects.push_back(square);

		// back
		squareTexture = std::make_shared<Texture>("SaintPetersBasilica\\negz.jpg");
		square = make_shared<Square>(vec3(d, d, -d), vec3(-d, d, -d), vec3(-d, -d, -d), vec3(d, -d, -d));

		square->amb = vec3(1.0f);
		square->dif = vec3(0.0f);
		square->spec = vec3(0.0f);
		square->alpha = 10.0f;
		square->reflection = 0.0f;
		square->ambTexture = squareTexture;
		square->difTexture = squareTexture;

		objects.push_back(square);

		// left
		squareTexture = std::make_shared<Texture>("SaintPetersBasilica\\negx.jpg");
		square = make_shared<Square>(vec3(-d, d, -d), vec3(-d, d, d), vec3(-d, -d, d), vec3(-d, -d, -d));

		square->amb = vec3(1.0f);
		square->dif = vec3(0.0f);
		square->spec = vec3(0.0f);
		square->alpha = 10.0f;
		square->reflection = 0.0f;
		square->ambTexture = squareTexture;
		square->difTexture = squareTexture;

		objects.push_back(square);

		// right
		squareTexture = std::make_shared<Texture>("SaintPetersBasilica\\posx.jpg");
		square = make_shared<Square>(vec3(d, d, d), vec3(d, d, -d), vec3(d, -d, -d), vec3(d, -d, d));

		square->amb = vec3(1.0f);
		square->dif = vec3(0.0f);
		square->spec = vec3(0.0f);
		square->alpha = 10.0f;
		square->reflection = 0.0f;
		square->ambTexture = squareTexture;
		square->difTexture = squareTexture;

		objects.push_back(square);

		// top
		squareTexture = std::make_shared<Texture>("SaintPetersBasilica\\posy.jpg");
		square = make_shared<Square>(vec3(-d, d, -d), vec3(d, d, -d), vec3(d, d, d), vec3(-d, d, d));

		square->amb = vec3(1.0f);
		square->dif = vec3(0.0f);
		square->spec = vec3(0.0f);
		square->alpha = 10.0f;
		square->reflection = 0.0f;
		square->ambTexture = squareTexture;
		square->difTexture = squareTexture;

		objects.push_back(square);

		// bottom
		squareTexture = std::make_shared<Texture>("SaintPetersBasilica\\negy.jpg");
		square = make_shared<Square>(vec3(-d, -d, d), vec3(d, -d, d), vec3(d, -d, -d), vec3(-d, -d, -d));

		square->amb = vec3(1.0f);
		square->dif = vec3(0.0f);
		square->spec = vec3(0.0f);
		square->alpha = 10.0f;
		square->reflection = 0.0f;
		square->ambTexture = squareTexture;
		square->difTexture = squareTexture;

		objects.push_back(square);

	}

	Hit FindClosestCollision(Ray& ray)
	{
		float closestD = 1000.0; // inf
		Hit closestHit = Hit{ -1.0, dvec3(0.0), dvec3(0.0) };

		for (int l = 0; l < objects.size(); l++)
		{
			auto hit = objects[l]->CheckRayCollision(ray);

			if (hit.d >= 0.0f)
			{
				if (hit.d < closestD)
				{
					closestD = hit.d;
					closestHit = hit;
					closestHit.obj = objects[l];

					// 텍스춰 좌표
					closestHit.uv = hit.uv;
				}
			}
		}

		return closestHit;
	}

	// 물체를 통과하면서 오는 빛의 세기 계산 (투명하거나 반투명한 물체는 투과하면서 강도를 계산)
	float CalculateTransmittance(Ray& ray, const float& distance)
	{
		float transmittance = 1.0f;
		for (int l = 0; l < objects.size(); l++)
		{
			auto hit = objects[l]->CheckRayCollision(ray);
			if (hit.d >= 0.0f && hit.d < distance)
			{
				transmittance *= objects[l]->transparency;
				if (transmittance < 0.001f)
					return 0.0f;
			}
		}

		return transmittance;
	}

	// 광선이 물체에 닿으면 그 물체의 색 반환
	vec3 traceRay(Ray& ray, const int recurseLevel)
	{
		if (recurseLevel < 0)
			return vec3(0.0f);

		// Render first hit
		const auto hit = FindClosestCollision(ray);

		if (hit.d >= 0.0f)
		{
			glm::vec3 color(0.0f);

			const vec3 dirToLight = glm::normalize(light.pos - hit.point);
			Ray shadowRay = { hit.point + dirToLight * 1e-4f, dirToLight };
			glm::vec3 phongColor(0.0f);

			// 해당 지점에 들어오는 빛의 세기 계산
			float transmittance = CalculateTransmittance(shadowRay, glm::length(light.pos - hit.point));

			if (transmittance > 0.0f)
			{
				// Diffuse
				const float diff = transmittance * glm::max(glm::dot(hit.normal, dirToLight), 0.0f);

				// Specular
				const vec3 reflectDir = hit.normal * 2.0f * dot(dirToLight, hit.normal) - dirToLight;
				const float specular = transmittance * glm::pow(glm::max(glm::dot(reflectDir, -ray.dir), 0.0f), hit.obj->alpha);

				if (hit.obj->difTexture)
				{
					phongColor += diff * hit.obj->dif * hit.obj->difTexture->SampleLinear(hit.uv);
				}
				else
				{
					phongColor += diff * hit.obj->dif;
				}

				phongColor += hit.obj->spec * specular;
			}			

			if (hit.obj->ambTexture)
			{
				phongColor += hit.obj->amb * hit.obj->ambTexture->SampleLinear(hit.uv);
			}
			else
			{
				phongColor += hit.obj->amb;
			}			

			color += phongColor * (1.0f - hit.obj->reflection - hit.obj->transparency);


			// Reflection
			if (hit.obj->reflection)
			{
				const auto reflectedDirection = glm::normalize(2.0f * hit.normal * dot(-ray.dir, hit.normal) + ray.dir);
				Ray reflection_ray{ hit.point + reflectedDirection * 1e-4f, reflectedDirection }; // add a small vector to avoid numerical issue

				color += traceRay(reflection_ray, recurseLevel - 1) * hit.obj->reflection;
			}


			// Refraction
			if (hit.obj->transparency)
			{
				const float ior = 1.5f; // Index of refraction (유리: 1.5, 물: 1.3)

				float eta; // sinTheta1 / sinTheta2
				vec3 normal;

				if (glm::dot(ray.dir, hit.normal) < 0.0f) // 밖에서 안에서 들어가는 경우 (예: 공기->유리)
				{
					eta = ior;
					normal = hit.normal;
				}
				else // 안에서 밖으로 나가는 경우 (예: 유리->공기)
				{
					eta = 1.0f / ior;
					normal = -hit.normal;
				}

				const float cosTheta1 = glm::dot(-ray.dir, normal);
				const float sinTheta1 = sqrt(1.0f - cosTheta1 * cosTheta1);
				const float sinTheta2 = sinTheta1 / eta;
				const float cosTheta2 = sqrt(1.0f - sinTheta2 * sinTheta2);

				const vec3 m = glm::normalize(cosTheta1 * normal + ray.dir);
				const vec3 a = sinTheta2 * m;
				const vec3 b = -cosTheta2 * normal;
				const vec3 refractedDirection = glm::normalize(a + b); // transmission

				Ray refractedRay{ hit.point + refractedDirection * 1e-4f, refractedDirection }; // add a small vector to avoid numerical issue
				color += traceRay(refractedRay, recurseLevel - 1) * hit.obj->transparency;
			}

			return color;
		}

		return vec3(0.0f);
	}

	void Render(std::vector<glm::vec4>& pixels)
	{
		std::fill(pixels.begin(), pixels.end(), vec4(0.0f, 0.0f, 0.0f, 1.0f));

		const vec3 eyePos(0.0f, 0.0f, -1.5f);

#pragma omp parallel for
		for (int j = 0; j < height; j++)
			for (int i = 0; i < width; i++)
			{
				const vec3 pixelPosWorld = TransformScreenToWorld(vec2(i, j));
				Ray pixelRay{ pixelPosWorld, glm::normalize(pixelPosWorld - eyePos) };
				pixels[i + width * j] = vec4(glm::clamp(traceRay(pixelRay, 5), 0.0f, 1.0f), 1.0f);
			}
	}

	vec3 TransformScreenToWorld(vec2 posScreen)
	{
		const float xScale = 2.0f / this->width;
		const float yScale = 2.0f / this->height;
		const float aspect = float(this->width) / this->height;

		// 3차원 공간으로 확장 (z좌표는 0.0)
		return vec3((posScreen.x * xScale - 1.0f) * aspect, -posScreen.y * yScale + 1.0f, 0.0f);
	}
};