#pragma once
#include <chrono>

extern bool major_error_f;
extern bool major_error_g;
extern bool major_error_due_to_minors_f;
extern bool major_error_due_to_minors_g;
extern int max_number_of_minor_errors;
extern std::chrono::seconds timeout_error;
extern bool is_timeout_error;