#include <iostream>
#include "Manager.hpp"
#include "globals.h"
#include <ctime>
#include <random>
bool major_error_f = false;
bool major_error_g = false;
bool major_error_due_to_minors_f = false;
bool major_error_due_to_minors_g = false;
int max_number_of_minor_errors = 3;
bool is_timeout_error = false;
std::chrono::seconds timeout_error = 50s;
int main()
{
	int x;
	std::cout << "Enter x: \n";
	std::cin >> x;
	Manager m(x);
	
	m.compute();
	m.print();
}
