// SoftComputingMidTestFuzzy.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <string>
#include <iostream>
#include "Fuzzy.h"
#include "TransmissionFuzzy.h"

int main()
{
	TransmissionFuzzy *tr = new TransmissionFuzzy();
	tr->Input();
	int s;
	std::cin >> s;
    return 0;
}

