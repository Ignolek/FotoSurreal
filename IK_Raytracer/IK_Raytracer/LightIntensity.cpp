#include "LightIntensity.h"
#include "Ray.h"

void LightIntensity::add(double R, double G, double B)
{
	this->r += R;
	this->g += G;
	this->b += B;
}

LightIntensity LightIntensity::operator+(LightIntensity& li)
{
	LightIntensity Result;
	Result.r = (this->r + li.r);
	Result.g = (this->g + li.g);
	Result.b = (this->b + li.b);
	return Result;
}

LightIntensity LightIntensity::operator+(LightIntensity li)
{
	LightIntensity Result;
	Result.r = (this->r + li.r);
	Result.g = (this->g + li.g);
	Result.b = (this->b + li.b);
	return Result;
}

LightIntensity LightIntensity::operator-(LightIntensity& li)
{
	LightIntensity Result;
	Result.r = (this->r - li.r);
	Result.g = (this->g - li.g);
	Result.b = (this->b - li.b);
	return Result;
}

LightIntensity LightIntensity::operator*(float num)
{
	LightIntensity Result;
	Result.r = (this->r * num);
	Result.g = (this->g * num);
	Result.b = (this->b * num);
	return Result;
}

LightIntensity LightIntensity::operator/(float num)
{
	LightIntensity Result;
	Result.r = (this->r / num);
	Result.g = (this->g / num);
	Result.b = (this->b / num);
	return Result;
}

//LightIntensity LightIntensity::operator+=(LightIntensity& li)
//{
//	LightIntensity Result;
//	Result.r = this->r + li.r;
//	Result.g = this->g + li.g;
//	Result.b = this->b + li.b;
//	return Result;
//}

void LightIntensity::operator+=(LightIntensity li)
{
	this->r = this->r + li.r;
	this->g = this->g + li.g;
	this->b = this->b + li.b;
}

void LightIntensity::operator-=(LightIntensity& li)
{
	this->r = this->r - li.r;
	this->g = this->g - li.g;
	this->b = this->b - li.b;
}

void LightIntensity::operator*=(float num)
{
	this->r = this->r * num;
	this->g = this->g * num;
	this->b = this->b * num;
}

void LightIntensity::operator/=(float num)
{
	this->r = this->r / num;
	this->g = this->g / num;
	this->b = this->b / num;
}

bool LightIntensity::operator==(const LightIntensity& li)
{
	if (this->r == li.r && this->g == li.g && this->b == li.b)
		return true;
	else return false;
}



LightIntensity LightIntensity::Antialiasing(Hitable* world, Camera* camera, float fov, float m, bool ortho, float xMin, float xMax, float yMin, float yMax, int x, int y, float w, std::vector<LightIntensity*> diffuseColors, std::vector<PointLight> pointLights, std::vector<DirectionalLight> directionalLights)
{
	maxSteps = 0.125f;
	LightIntensity result(0.0f, 0.0f, 0.0f);
	Ray ray(vec3(0,0,0), vec3(0,0,1));

	if (diffuseColors[LEFT_UPPER] == nullptr)
	{
		ray = camera->getRay(xMin, yMin, fov, m, ortho);
		diffuseColors[LEFT_UPPER] = new LightIntensity(this->GetColorFromRay(ray, world, camera->origin, pointLights, directionalLights, 0));
	}
	if (diffuseColors[RIGHT_UPPER] == nullptr)
	{
		ray = camera->getRay(xMax, yMin, fov, m, ortho);
		diffuseColors[RIGHT_UPPER] = new LightIntensity(this->GetColorFromRay(ray, world, camera->origin, pointLights, directionalLights, 0));
	}
	if (diffuseColors[RIGHT_LOWER] == nullptr)
	{
		ray = camera->getRay(xMax, yMax, fov, m, ortho);
		diffuseColors[RIGHT_LOWER] = new LightIntensity(this->GetColorFromRay(ray, world, camera->origin, pointLights, directionalLights, 0));
	}
	if (diffuseColors[LEFT_LOWER] == nullptr)
	{
		ray = camera->getRay(xMin, yMax, fov, m, ortho);
		diffuseColors[LEFT_LOWER] = new LightIntensity(this->GetColorFromRay(ray, world, camera->origin, pointLights, directionalLights, 0));
	}
	if (diffuseColors[CENTER] == nullptr)
	{
		ray = camera->getRay((xMin + xMax) * 0.5f, (yMin + yMax) * 0.5f, fov, m, ortho);
		diffuseColors[CENTER] = new LightIntensity(this->GetColorFromRay(ray, world, camera->origin, pointLights, directionalLights, 0));
	}

	if (w < maxSteps || *diffuseColors[LEFT_UPPER] == *diffuseColors[CENTER])
	{
		result += *diffuseColors[LEFT_UPPER];
	}
	else 
	{
		result += this->Antialiasing(world, camera, fov, m, ortho, xMin, (xMin + xMax) * 0.5f, yMin, (yMin + yMax) * 0.5f, x, y, w * 0.5f, std::vector<LightIntensity*>{new LightIntensity(*diffuseColors[LEFT_UPPER]), nullptr, new LightIntensity(*diffuseColors[CENTER]), nullptr, nullptr}, pointLights, directionalLights);
		//std::cout << result.getRed() << "  " << result.getGreen() << "  " << result.getBlue() << std::endl;
	}

	if (w < maxSteps || *diffuseColors[RIGHT_UPPER] == *diffuseColors[CENTER])
	{
		result += *diffuseColors[RIGHT_UPPER];
	}
	else
	{
		result += this->Antialiasing(world, camera, fov, m, ortho, (xMin + xMax) * 0.5f, xMax , yMin, (yMin + yMax) * 0.5f, x, y, w * 0.5f, std::vector<LightIntensity*>{new LightIntensity(*diffuseColors[RIGHT_UPPER]), nullptr, new LightIntensity(*diffuseColors[CENTER]), nullptr, nullptr}, pointLights, directionalLights);
		//std::cout << result.getRed() << "  " << result.getGreen() << "  " << result.getBlue() << std::endl;
	}

	if (w < maxSteps || *diffuseColors[RIGHT_LOWER] == *diffuseColors[CENTER])
	{
		result += *diffuseColors[RIGHT_LOWER];
	}
	else
	{
		result += this->Antialiasing(world, camera, fov, m, ortho, (xMin + xMax) * 0.5f, xMax, (yMin + yMax) * 0.5f, yMax, x, y, w * 0.5f, std::vector<LightIntensity*>{new LightIntensity(*diffuseColors[CENTER]), nullptr, new LightIntensity(*diffuseColors[RIGHT_LOWER]), nullptr, nullptr}, pointLights, directionalLights);
		//std::cout << result.getRed() << "  " << result.getGreen() << "  " << result.getBlue() << std::endl;
	}

	if (w < maxSteps || *diffuseColors[LEFT_LOWER] == *diffuseColors[CENTER])
	{
		result += *diffuseColors[LEFT_LOWER];
	}
	else
	{
		result += this->Antialiasing(world, camera, fov, m, ortho, xMin, (xMin + xMax) * 0.5f, (yMin + yMax) * 0.5f, yMax, x, y, w * 0.5f, std::vector<LightIntensity*>{new LightIntensity(*diffuseColors[CENTER]), nullptr, new LightIntensity(*diffuseColors[LEFT_LOWER]), nullptr, nullptr}, pointLights, directionalLights);
		//std::cout << result.getRed() << "  " << result.getGreen() << "  " << result.getBlue() << std::endl;
	}

	for (int i = 0; i < 5; i++)
	{
		delete diffuseColors[i];
	}
	diffuseColors.clear();

	return 0.25f*result;
}

LightIntensity operator*(float num, LightIntensity& li)
{
	LightIntensity Result;
	Result.r = num * li.r;
	Result.g = num * li.g;
	Result.b = num * li.b;
	return Result;
}

LightIntensity LightIntensity::operator*(vec3 v)
{
	LightIntensity Result;
	Result.r *= v.r();
	Result.g *= v.g();
	Result.b *= v.b();
	return Result;
}

//LightIntensity operator*(LightIntensity& li, float num)
//{
//	LightIntensity Result;
//	Result.r = li.r * num;
//	Result.g = li.g * num;
//	Result.b = li.b * num;
//	return Result;
//}

LightIntensity LightIntensity::GetColorFromRay(const Ray& r, Hitable* world, vec3 cameraPosition, std::vector<PointLight> pointLights, std::vector<DirectionalLight> directionalLights, int bounce)
{
	hitRecord rec;
	float shadowIntensity = 0.20f; // 0 - black , 1 - no shadow
	vec3 attenuation;

	if (world->hit(r, 0.001, 10000, rec))
	{
		vec3 ambientColor (0, 0, 0);
		vec3 diffuseColor (0, 0, 0);
		vec3 specularColor(0, 0, 0);

		if (rec.materialPtr->isMirror && bounce < 5)
		{
			vec3 newNormal = -rec.normal;
			vec3 scatterDir = (unit_vector(r.direction()) - 2 * dot(unit_vector(r.direction()), newNormal) * newNormal);
			Ray scatterRay(rec.p, (scatterDir));

			return GetColorFromRay(scatterRay, world, cameraPosition, pointLights, directionalLights, bounce++);
		}

		else if (rec.materialPtr->isRefractor && bounce < 5)
		{
			rec.materialPtr->refraction = 2.0f - rec.materialPtr->refraction;
			vec3 refractedDir;
			vec3 uv = unit_vector(r.direction());
			//float dt = dot(uv, -rec.normal);
			//float discriminant = 1.0 - rec.materialPtr->refraction * rec.materialPtr->refraction * (1 - dt * dt);
			float cosi = dot(rec.normal, uv);

			if (cosi > 0)
			{
				//refractedDir = rec.materialPtr->refraction * (uv - rec.normal * dt) - rec.normal * sqrt(discriminant);
				refractedDir = (uv * rec.materialPtr->refraction - rec.normal * (-cosi + rec.materialPtr->refraction * cosi));
			}
			else
			{
				refractedDir = r.direction();
			}

			Ray refractedRay(rec.p, refractedDir);

			if (bounce == 0)
			{
				attenuation = rec.materialPtr->mDiffuse;
			}
			return GetColorFromRay(refractedRay, world, cameraPosition, pointLights, directionalLights, bounce++);// * rec.materialPtr->mDiffuse;
		}

		else
		{
			for (int i = 0; i < pointLights.size(); i++)
			{
				hitRecord shadowRec;
				Ray shadowRay(rec.p, unit_vector(pointLights.at(i).location -rec.p));

				// shadow
				if (world->hit(shadowRay, 0.001, 100000, shadowRec) && shadowRec.materialPtr->isTransparent == false)
				{
					if (shadowRec.materialPtr->isRefractor == true)
					{
						ambientColor += pointLights.at(i).ambientColor;
						specularColor += pointLights.at(i).getSpecular(rec, -cameraPosition, rec.materialPtr->shininess) * shadowIntensity * 4;
						diffuseColor += pointLights.at(i).getDiffuse(rec) * shadowIntensity * 4;
					}
					else
					{
						ambientColor +=  pointLights.at(i).ambientColor;
						//specularColor += pointLights.at(i).getSpecular(rec, -cameraPosition, rec.materialPtr->shininess) * shadowIntensity;
						diffuseColor += pointLights.at(i).getDiffuse(rec) * shadowIntensity;
					}
			
				}
				// no shadow
				else
				{
					ambientColor += pointLights.at(i).ambientColor;
					specularColor += pointLights.at(i).getSpecular(rec, -cameraPosition, rec.materialPtr->shininess);
					diffuseColor +=  pointLights.at(i).getDiffuse(rec);
				}
			}

			for (int i = 0; i < directionalLights.size(); i++)
			{
				hitRecord shadowRec;
				Ray shadowRay(rec.p, -directionalLights.at(i).direction);


				// shadow
				if (world->hit(shadowRay, 0.001, 100000, shadowRec) && shadowRec.materialPtr->isTransparent == false && rec.materialPtr->isRefractor == false)
				{
					ambientColor += directionalLights.at(i).ambientColor;
					//specularColor += directionalLights.at(i).getSpecular(rec, -cameraPosition, rec.materialPtr->shininess) * shadowIntensity;
					diffuseColor += directionalLights.at(i).getDiffuse(rec) * shadowIntensity;
				}
				// no shadow
				else
				{
					ambientColor += directionalLights.at(i).ambientColor;
					specularColor += directionalLights.at(i).getSpecular(rec, -cameraPosition, rec.materialPtr->shininess);
					diffuseColor += directionalLights.at(i).getDiffuse(rec);
				}
			}
		
			// Final color
			if (rec.materialPtr->texture != nullptr)
			{
				//std::cout << "TEXTURE" << std::endl;
				//std::cout << rec.u << rec.v << std::endl;
				float redTexAmbientValue =  rec.materialPtr->texture->value(rec.u, rec.v, rec.p).r() * 0.1 * ambientColor.r();
				float greenTexAmbientValue =rec.materialPtr->texture->value(rec.u, rec.v, rec.p).g() * 0.1 * ambientColor.g();
				float blueTexAmbientValue = rec.materialPtr->texture->value(rec.u, rec.v, rec.p).b() * 0.1 * ambientColor.b();
			
				float redTexDiffuseValue =   rec.materialPtr->texture->value(rec.u, rec.v, rec.p).r() * 3 * diffuseColor.r();
				float greenTexDiffuseValue = rec.materialPtr->texture->value(rec.u, rec.v, rec.p).g() * 3 * diffuseColor.g();
				float blueTexDiffuseValue =  rec.materialPtr->texture->value(rec.u, rec.v, rec.p).b() * 3 * diffuseColor.b();
			
				float redTexSpecularValue =  rec.materialPtr->texture->value(rec.u, rec.v, rec.p).r() * specularColor.r();
				float greenTexSpecularValue =rec.materialPtr->texture->value(rec.u, rec.v, rec.p).g() * specularColor.g();
				float blueTexSpecularValue = rec.materialPtr->texture->value(rec.u, rec.v, rec.p).b() * specularColor.b();

				return LightIntensity(red(redTexAmbientValue + redTexDiffuseValue + redTexSpecularValue),
									  green(greenTexAmbientValue + greenTexDiffuseValue + greenTexSpecularValue),
									  blue(blueTexAmbientValue + blueTexDiffuseValue + blueTexSpecularValue));
			}
			else
			{
				//std::cout << "TEXTURE" << std::endl;
				return LightIntensity(red(rec.materialPtr->mAmbient.r()  * ambientColor.r() + rec.materialPtr->mDiffuse.r() * diffuseColor.r() + rec.materialPtr->mSpecular.r() * specularColor.r()),
									  green(rec.materialPtr->mAmbient.g()* ambientColor.g() + rec.materialPtr->mDiffuse.g() * diffuseColor.g() + rec.materialPtr->mSpecular.g() * specularColor.g()),
									  blue(rec.materialPtr->mAmbient.b() * ambientColor.b() + rec.materialPtr->mDiffuse.b() * diffuseColor.b() + rec.materialPtr->mSpecular.b() * specularColor.b()));
			}
		}
	}
	else
	{
		//return LightIntensity(0, 50, 200);
		return LightIntensity(0, 0, 0);
	}
}

float LightIntensity::red(float redValue)
{
	if (redValue >= 255.0f) { return 255.0f; }
	else if (redValue <= 0.0f) { return 0.0f; }
	else { return redValue; }
}
float LightIntensity::green(float greenValue)
{
	if (greenValue >= 255.0f) { return 255.0f; }
	else if (greenValue <= 0.0f) { return 0.0f; }
	else { return greenValue; }
}
float LightIntensity::blue(float blueValue)
{
	if (blueValue >= 255.0f) { return 255.0f; }
	else if (blueValue <= 0.0f) { return 0.0f; }
	else { return blueValue; }
}
