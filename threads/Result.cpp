#include "Result.h"


int Result::get_num_of_minor_errors()
{
	return num_of_minor_errors;
}

void Result::add_minor_error() {
	num_of_minor_errors++;
}
void Result::add_major_error() {
	major_error e;
	res = e;
}
void Result::calculate_successful(int val_) {
	success s = success(val_);
	res = s;
}
