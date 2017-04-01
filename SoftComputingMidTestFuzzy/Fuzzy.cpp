#include "stdafx.h"
#include <iostream>
#include <string>
#include <algorithm>
#include "Fuzzy.h"


void Fuzzy::Fuzzification()
{
	IOType *si;
	MFType *mf;

	for (si = systemInputs; si != NULL; si = si->next) {
		for (mf = si->membershipFunctions; mf != NULL; mf = mf->next) {
			//ComputeDegreeOfMembership(mf,si->value);
		}
	}
}

void Fuzzy::RuleEvaluation()
{
	RuleType *rule;
	RuleElementType *ip;
	RuleElementType *tp;
	float strength;

	for (rule = ruleBase; rule != NULL; rule = rule->next) {
		strength = UPPER_LIMIT;
		for (ip = rule->ifSide; ip != NULL; ip=ip->next) {
			strength = std::min(strength, *ip->value);
		}
		for (tp = rule->thenSide; tp != NULL; tp = tp->next) {
			*(tp->value) = std::max(strength, *(tp->value));
		}
	}
}

void Fuzzy::Defuzzification()
{
	IOType *so;
	MFType *mf;
	float sumOfProducts;
	float sumOfAreas;
	float area;
	float centroid;

	for (so = systemOutputs; so != NULL; so == so->next) {
		sumOfProducts = 0;
		sumOfAreas = 0;

		for (mf = so->membershipFunctions; mf != NULL; mf = mf->next) {
			area = ComputeAreaOfTrapezoid(mf);
			centroid = mf->point1 + (mf->point2 - mf->point1) / 2;
			sumOfProducts += area*centroid;
			sumOfAreas += area;
		}
		so->value = sumOfProducts / sumOfAreas;
	}
}

void Fuzzy::ComputeDegreeOfMembership(MFType * _mf, float _input)
{
	float delta1;
	float delta2;
	delta1 = _input - _mf->point1;
	delta2 = _mf->point2 - _input;

	if ((delta1 <= 0) || (delta2 <= 0)) {
		_mf->value = 0;
	}
	else {
		_mf->value = std::min((_mf->slope1*delta1), (_mf->slope1*delta2);
		_mf->value = std::min(_mf->value,(float) UPPER_LIMIT);
	}
}

float Fuzzy::ComputeAreaOfTrapezoid(MFType * _mf)
{
	float run1;
	float run2;
	float base;
	float top;
	float area;
	base = _mf->point2 - _mf-> point1;
	run1 = _mf->value/_mf->slope1;
	run2 = _mf->value / _mf->slope2;
	top = base - run1 - run2;
	area = _mf->value * (base + top) / 2;
	return area;
}

void Fuzzy::Update()
{
	GetSystemInputs();
	Fuzzification();
	RuleEvaluation();
	Defuzzification();
	PutSystemOutputs();
}

Fuzzy::Fuzzy()
{
}


Fuzzy::~Fuzzy()
{
}
