#include "Manager.hpp"

std::variant<int, major_error> Manager::binaryOperation()
{
	Result resultF = f.getResult();
	Result resultG = g.getResult();

		if (resultF.get_res().index() == 1 && resultG.get_res().index() == 1) {
			return (std::get<success>(resultF.get_res()).value) & (std::get<success>(resultG.get_res()).value);
		}
		else {
			major_error m;
			return m;
		}
	
}
