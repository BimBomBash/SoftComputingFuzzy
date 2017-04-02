// SoftComputingMidTestFuzzy.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <list>
#include "Fuzzy.h"

IOType *throttle;
IOType *load;
IOType *transmissionShift;

std::list<RuleType*> ruleBase;

void Initiate(float _throttleValue, float _loadValue) {
	std::list<MFType*> throttleMF;
	std::list<MFType*> loadMF;
	std::list<MFType*> transmissionShiftMF;

	throttleMF.insert(new MFType("SMALL", 0.0f, 0.0f, 42.0f, 85.0f));
}

int main()
{
    return 0;
}

