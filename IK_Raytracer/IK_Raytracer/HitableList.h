#ifndef HITABLELISTH
#define HITABLELISTH

#include "Hitable.h"
#include <vector>

class HitableList : public Hitable
{
public:
	HitableList(){}
	//HitableList(Hitable** l, int n) { list = l; listSize = n; }
	HitableList(std::vector<Hitable*> vHitable) { vecHitable = vHitable; }
	virtual bool hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const;
	std::vector<Hitable*> vecHitable;
	//Hitable** list;
	//int listSize;
};

bool HitableList::hit(const Ray& r, float tMin, float tMax, hitRecord& rec) const
{
	hitRecord tempRec;
	bool hitAnything = false;
	double closestSoFar = tMax;
	//for (int i = 0; i < listSize; i++)
	//{
	//	if (list[i]->hit(r, tMin, closestSoFar, tempRec))
	//	{
	//		hitAnything = true;
	//		closestSoFar = tempRec.t;
	//		rec = tempRec;
	//	}
	//}

	for (int i = 0; i < vecHitable.size(); i++)
	{
		if (vecHitable.at(i)->hit(r, tMin, closestSoFar, tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			rec = tempRec;
		}
	}
	return hitAnything;
}
#endif // !HITABLELISTH

