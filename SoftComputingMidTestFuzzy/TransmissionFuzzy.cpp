#include "stdafx.h"
#include <string>
#include <iostream>
#include "Fuzzy.h"
#include "TransmissionFuzzy.h"


void TransmissionFuzzy::InsertMembershipFunction(MFType * list, MFType * target)
{
	MFType *temp;
	if (list == nullptr) list = target;
	else {
		temp = list;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = target;
	}
}

void TransmissionFuzzy::SetThrottle(float _throttleValue)
{
	MFType *throttleMF= new MFType(SMALL, 0.0f, 0.0f, 42.0f, 85.0f);
	InsertMembershipFunction(throttleMF, new MFType(PRETTY_SMALL, 42.0f, 85.0f, 85.0f, 127.0f));
	InsertMembershipFunction(throttleMF, new MFType(MEDIUM, 85.0f, 127.0f, 127.0f, 170.0f));
	InsertMembershipFunction(throttleMF, new MFType(PRETTY_LARGE, 127.0f, 170.0f, 170.0f, 217.0f));
	InsertMembershipFunction(throttleMF, new MFType(LARGE, 170.0f, 217.0f, 255.0f, 255.0f));
	throttle = new IOType("THROTTLE", _throttleValue, throttleMF);
	throttle->next = load;
}

void TransmissionFuzzy::SetLoad(float _loadValue)
{
	MFType *loadMF = new MFType(SMALL, 0.0f, 0.0f, 42.0f, 85.0f);
	InsertMembershipFunction(loadMF, new MFType(PRETTY_SMALL, 42.0f, 85.0f, 85.0f, 127.0f));
	InsertMembershipFunction(loadMF, new MFType(MEDIUM, 85.0f, 127.0f, 127.0f, 170.0f));
	InsertMembershipFunction(loadMF, new MFType(PRETTY_LARGE, 127.0f, 170.0f, 170.0f, 217.0f));
	InsertMembershipFunction(loadMF, new MFType(LARGE, 170.0f, 217.0f, 255.0f, 255.0f));
	load = new IOType("LOAD", _loadValue, loadMF);
}

void TransmissionFuzzy::SetTransmissionShift()
{
	MFType *shiftMF= new MFType(SHIFT_DOWN, 0.0f, 0.0f, 63.0f, 127.0f);
	InsertMembershipFunction(shiftMF, new MFType(STAY, 63.0f, 127.0f, 127.0f, 191.0f));
	InsertMembershipFunction(shiftMF, new MFType(SHIFT_UP, 127.0f, 191.0f, 191.0f, 255.0f));
	transmissionShift = new IOType("SHIFT", 0.0f, shiftMF);
	transmissionShift->next = nullptr;
	MFType *iter = transmissionShift->membershipFunctions;
	while (iter != NULL) {
		iter->value = 0;
		iter = iter->next;
	}
}

void TransmissionFuzzy::SetRules()
{
	AddRule(SMALL, SMALL, SHIFT_DOWN);
	AddRule(PRETTY_SMALL, SMALL, STAY);
	AddRule(MEDIUM, SMALL, STAY);
	AddRule(PRETTY_LARGE, SMALL, SHIFT_UP);
	AddRule(LARGE, SMALL, SHIFT_UP);
	AddRule(SMALL, PRETTY_SMALL, SHIFT_DOWN);
	AddRule(PRETTY_SMALL, PRETTY_SMALL, SHIFT_DOWN);
	AddRule(MEDIUM, PRETTY_SMALL, STAY);
	AddRule(PRETTY_LARGE, PRETTY_SMALL, STAY);
	AddRule(LARGE, PRETTY_SMALL, SHIFT_UP);
	AddRule(SMALL, MEDIUM, SHIFT_DOWN);
	AddRule(PRETTY_SMALL, MEDIUM, SHIFT_DOWN);
	AddRule(MEDIUM, MEDIUM, STAY);
	AddRule(PRETTY_LARGE, MEDIUM, STAY);
	AddRule(LARGE, MEDIUM, STAY);
	AddRule(SMALL, PRETTY_LARGE, SHIFT_DOWN);
	AddRule(PRETTY_SMALL, PRETTY_LARGE, SHIFT_DOWN);
	AddRule(MEDIUM, PRETTY_LARGE, SHIFT_DOWN);
	AddRule(PRETTY_LARGE, PRETTY_LARGE, STAY);
	AddRule(LARGE, PRETTY_LARGE, STAY);
	AddRule(SMALL, LARGE, SHIFT_DOWN);
	AddRule(PRETTY_SMALL, LARGE, SHIFT_DOWN);
	AddRule(MEDIUM, LARGE, SHIFT_DOWN);
	AddRule(PRETTY_LARGE, LARGE, SHIFT_DOWN);
	AddRule(LARGE, LARGE, STAY);
}

void TransmissionFuzzy::AddRule(std::string _if1, std::string _if2, std::string _then)
{
	RuleType *temp;
	if (ruleBase == nullptr) ruleBase = new RuleType (SearchMF(throttle,_if1), SearchMF(load, _if2), SearchMF(transmissionShift, _then));
	else {
		temp = ruleBase;
		while (temp->next != nullptr) {
			temp = temp->next;
		}
		temp->next = new RuleType(SearchMF(throttle, _if1), SearchMF(load, _if2), SearchMF(transmissionShift, _then));
	}
}

MFType * TransmissionFuzzy::SearchMF(IOType * _source, std::string _keyword)
{
	MFType *temp = nullptr;
	for (MFType* iter = _source->membershipFunctions; iter != nullptr; iter = iter->next) {
		if (iter->name == _keyword) { 
			temp = iter;
			break;
		}
	}
	return temp;
}

void TransmissionFuzzy::Initiate(float _throttleValue, float _loadValue)
{
	SetThrottle(_throttleValue);
	SetLoad(_loadValue);
	SetTransmissionShift();
}

TransmissionFuzzy::TransmissionFuzzy()
{
}

TransmissionFuzzy::~TransmissionFuzzy()
{
}

void TransmissionFuzzy::Test(float a, float b)
{
	Initiate(a, b);
	PrintIO(throttle);
	PrintIO(load);
	PrintIO(transmissionShift);
	SetRules();
	PrintRules(ruleBase);
}

void TransmissionFuzzy::PrintIO(IOType * target)
{
	std::cout << target->name << std::endl;
	MFType *iter = target->membershipFunctions;
	while (iter != NULL) {
		std::cout <<iter->name<<": "<<iter->point1<<", "<<iter->point2<<" SLOPE: "<<iter->slope1<<", "<<iter->slope2<<std::endl;
		iter = iter->next;
	}
	std::cout << std::endl;
}

void TransmissionFuzzy::PrintRules(RuleType * base)
{
	std::cout << "RULES" << std::endl;
	RuleType *iter = base;
	while (iter != NULL) {
		std::cout <<"IF Throttle: " <<*iter->ifSide->name << " AND Load: " << *iter->ifSide->next->name << ", THEN Transmission Shift: " << *iter->thenSide->name << std::endl;
		iter = iter->next;
	}
	std::cout << std::endl;
}

void TransmissionFuzzy::Input()
{
	Initiate(0.0f, 0.0f);
	PrintIO(throttle);
	PrintIO(load);
	PrintIO(transmissionShift);
	SetRules();
	PrintRules(ruleBase);

	std::cout << "Enter THROTTLE value:";
	std::cin >> throttle->value;
	std::cout << "Enter LOAD value:";
	std::cin >> load->value;

	fuzzy = new Fuzzy(throttle, load, transmissionShift, ruleBase);
	fuzzy->Count();
}
