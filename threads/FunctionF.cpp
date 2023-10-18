#include "FunctionF.h"
#include "globals.h"

void FunctionF::compute() {
	bool flag = false;
	int x_copy = x;
	if (x_copy < 0) {
		result.add_major_error();
		major_error_f = true;
		flag = true;
		
	}
	if (x_copy % 2 == 0) {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<int> distribution(0, 2);
		int temp = distribution(gen);
		while (temp != 1) {
			
			result.add_minor_error();
			temp = distribution(gen);
			if (result.get_num_of_minor_errors() >= max_number_of_minor_errors) {
				major_error_due_to_minors_f = true;
				flag = true;
				result.add_major_error();
			}
		}
		x_copy += 1;
		
	}
	if (!flag) {
		std::this_thread::sleep_for(10s);
		int result_f = 2 * x_copy;

		result.calculate_successful(result_f);
	}
	
	

}
Result FunctionF::getResult() {
	
	Result temp_result = result;
	return temp_result;
}

int FunctionF::getX()
{
	return x;
}

void FunctionF::print_all_info()
{
	if (result.get_res().index() == 1) {
		std::cout << "Function f returns value: " << std::get<success>(result.get_res()).value << " with: "<< result.get_num_of_minor_errors()<<" minor errors" << std::endl;
		return;
	}

	else if (result.get_res().index() == 0) {
		std::cout << "Function f has got major error " << " with: " << result.get_num_of_minor_errors() << " minor errors" << std::endl;
		return;
	}
	else if (result.get_res().index() == 2) {
		std::cout << "Function f hasn`t returned value(but doesn`t have major error): " << " with: " << result.get_num_of_minor_errors() << " minor errors" << std::endl;
		return;
	}
}
