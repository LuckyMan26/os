#include "FunctionG.h"
#include "globals.h"

void FunctionG::compute() {
	bool flag = false;
	int x_copy = x;
	if (x_copy < 5) {
	
		result.add_major_error();
		major_error_g = true;
		flag = true;
	}
	else if (x_copy % 3 == 0) {

		std::random_device rd;
		std::mt19937 gen(rd()); 
		std::uniform_int_distribution<int> distribution(0, 3);
		int temp = distribution(gen);
		
		
			
			result.add_minor_error();
			temp = distribution(gen);	
			if (result.get_num_of_minor_errors() >= max_number_of_minor_errors) {
				major_error_due_to_minors_g = true;
				result.add_major_error();
				
				flag = true;
			}
		
			x_copy += 5;
		
	}
	
	if (!flag) {
		std::this_thread::sleep_for(15s);
		int result_g = 3 * x_copy;
		result.calculate_successful(result_g);

		
	}
	
	
}
Result FunctionG::getResult() {
	return result;
}

int FunctionG::getX()
{
	return x;
}
void FunctionG::print_all_info()
{
	if (result.get_res().index() == 1) {
		std::cout << "Function g returns value: " << std::get<success>(result.get_res()).value << " with: " << result.get_num_of_minor_errors() << " minor errors" << std::endl;
		return;
	}

	else if (result.get_res().index() == 0) {
		std::cout << "Function g has got major error: " << " with: " << result.get_num_of_minor_errors() << " minor errors" << std::endl;
		return;
	}
	else if (result.get_res().index() == 2) {
		std::cout << "Function g hasn`t returned value(but doesn`t have major error): " << " with: " << result.get_num_of_minor_errors() << " minor errors" << std::endl;
		return;
	}
}