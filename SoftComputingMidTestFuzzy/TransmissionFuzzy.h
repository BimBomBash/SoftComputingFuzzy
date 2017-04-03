#pragma once

#define SMALL "SMALL"
#define PRETTY_SMALL "PRETTYSMALL"
#define MEDIUM "MEDIUM"
#define PRETTY_LARGE "PRETTYLARGE"
#define LARGE "LARGE"

#define SHIFT_DOWN "SHIFTDOWN"
#define STAY "STAY"
#define SHIFT_UP "SHIFTUP"

class TransmissionFuzzy
{
	Fuzzy *fuzzy;

	IOType *throttle;
	IOType *load;
	IOType *transmissionShift;
	RuleType *ruleBase;

	void InsertMembershipFunction(MFType *list, MFType *target);
	void SetThrottle(float _throttleValue);
	void SetLoad(float _loadValue);
	void SetTransmissionShift();
	void SetRules();
	void AddRule(std::string, std::string, std::string);
	MFType *SearchMF(IOType *, std::string);
	void Initiate(float, float);
public:
	TransmissionFuzzy();
	~TransmissionFuzzy();
	void Test(float,float);
	void PrintIO(IOType *target);
	void PrintRules(RuleType *base);
	void Input();
};

