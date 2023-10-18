﻿#pragma once
#include "Result.h"
#include <random>
#include <chrono>
#include <thread>
#include "globals.h"
using namespace std::chrono_literals;


class FunctionF
{

	Result result;
	int x;
public:
	FunctionF(int x_)  {
		x = x_;
	}
	void compute();
	Result getResult();
	int getX();
	void print_all_info();
};

