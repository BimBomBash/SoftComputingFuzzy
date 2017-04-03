#pragma once

#define UPPER_LIMIT 255

struct MFType {
	std::string name;
	float value;
	float point1;
	float point2;
	float slope1;
	float slope2;
	MFType *next;
	MFType(std::string _name, float _pointA, float _pointB, float _pointC, float _pointD) {
		name = _name;
		point1 = _pointA;
		point2 = _pointD;
		slope1 = UPPER_LIMIT / (_pointB - _pointA);
		slope2 = UPPER_LIMIT / (_pointD - _pointC);
		next = nullptr;
	}
};

struct IOType {
	std::string name;
	float value;
	MFType *membershipFunctions;
	IOType *next;
	IOType(std::string _name, float _value, MFType* _membershipFunctions) {
		name = _name;
		value = _value;
		membershipFunctions = _membershipFunctions;
		next = nullptr;
	}
};

struct RuleElementType {
	std::string  *name;
	float *value;
	RuleElementType *next;
	RuleElementType(std::string &_name,float &_value) {
		value = &_value;
		name = &_name;
		next = nullptr;
	}
};

struct RuleType {
	RuleElementType *ifSide;
	RuleElementType *thenSide;
	RuleType *next;
	RuleType(MFType *_ifSide1, MFType *_ifSide2, MFType *_thenSide) {
		ifSide = new RuleElementType(_ifSide1->name, _ifSide1->value);
		ifSide->next = new RuleElementType(_ifSide2->name, _ifSide2->value);
		thenSide = new RuleElementType(_thenSide->name, _thenSide->value);
		next = nullptr;
	}
};

class Fuzzy
{
	IOType *systemInputs;
	IOType *systemOutputs;

	RuleType *ruleBase;

	void Fuzzification();
	void RuleEvaluation();
	void Defuzzification();
	void ComputeDegreeOfMembership(MFType *_mf, float _input);
	float ComputeAreaOfTrapezoid(MFType *_mf);
	void PutSystemOutputs();
public:
	void Count();
	Fuzzy();
	Fuzzy(IOType*, IOType*, IOType*, RuleType*);
	~Fuzzy();
};

