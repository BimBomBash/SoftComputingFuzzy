#pragma once

#define UPPER_LIMIT 255

struct MFType {
	std::string name;
	float value;
	float point1;
	float point2;
	float slope1;
	float slope2;
	MFType(std::string _name, float _pointA, float _pointB, float _pointC, float _pointD) {
		name = _name;
		point1 = _pointA;
		point2 = _pointB;
		slope1 = UPPER_LIMIT / (_pointB - _pointA);
		slope2 = UPPER_LIMIT / (_pointD - _pointC);
	}
};

struct IOType {
	std::string name;
	float value;
	std::list<MFType*> membershipFunctions;
	IOType(std::string _name, float _value, std::list<MFType*> &_membershipFunctions) {
		name = _name;
		value = _value;
		membershipFunctions = _membershipFunctions;
	}
};

struct RuleElementType {
	float *value;
};

struct RuleType {
	std::list<RuleElementType*> ifSide;
	std::list<RuleElementType*> thenSide;
};

class Fuzzy
{
	std::list<IOType*> systemInputs;
	std::list<IOType*> systemOutputs;

	void GetSystemInputs();
	void Fuzzification();
	void RuleEvaluation();
	void Defuzzification();
	void ComputeDegreeOfMembership(MFType *_mf, float _input);
	float ComputeAreaOfTrapezoid(MFType *_mf);
	void PutSystemOutputs();
public:
	std::list<RuleType*> ruleBase;
	void Update();
	Fuzzy();
	~Fuzzy();
};

