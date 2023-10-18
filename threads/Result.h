#pragma once
#include <iostream>
struct major_error{};
struct minor_error{
	int number_of_alerts;
};
struct success{
	int value;
};
struct unfinished{};
#include <variant>

class Result
{
	std::variant <major_error, success,unfinished> res;
	int num_of_minor_errors;
public:
	Result() {
		num_of_minor_errors = 0;
		unfinished u;
		res = u;
	}
	void add_minor_error();
	void add_major_error();
	void calculate_successful(int val_);
	std::variant <major_error, success, unfinished> get_res() {
		return res;
	}
	void print();
	int get_num_of_minor_errors();
};

