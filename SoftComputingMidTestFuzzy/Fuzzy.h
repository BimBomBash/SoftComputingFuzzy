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
};

struct IOType {
	std::string name;
	float value;
	MFType *membershipFunctions;
	IOType *next;
};

struct RuleElementType {
	float *value;
	RuleElementType *next;
};

struct RuleType {
	RuleElementType *ifSide;
	RuleElementType *thenSide;
	RuleType *next;
};

class Fuzzy
{
	IOType *systemInputs;
	IOType *systemOutputs;

	void GetSystemInputs();
	void Fuzzification();
	void RuleEvaluation();
	void Defuzzification();
	void ComputeDegreeOfMembership(MFType *_mf, float _input);
	float ComputeAreaOfTrapezoid(MFType *_mf);
	void PutSystemOutputs();
public:
	RuleType *ruleBase;
	void Update();
	Fuzzy();
	~Fuzzy();
};

