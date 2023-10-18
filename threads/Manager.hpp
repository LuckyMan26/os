#pragma once
#include <thread>
#include "FunctionF.h"
#include "FunctionG.h"
#include <ostream>
#include <numeric>
#include <future>
class Manager {
	
	FunctionF f;
	FunctionG g;
	std::variant<int, major_error> result;
public:
	Manager(int x_) : f(FunctionF(x_)), g(FunctionG(x_)) {
		result = 0;
	}
	void compute() {
	
		
		std::mutex mtxf;
		std::mutex mtxg;
		std::mutex mtxt;
		std::mutex mtxt2;
	
		

		
		auto functor = [](FunctionF& f,std::mutex& m ) ->void { 
			{
				std::unique_lock<std::mutex> l(m);
				f.compute();
			}
			
			};
		auto functor2 =
			[](FunctionG& g,  std::mutex& m) ->void {
				{
					std::unique_lock<std::mutex> l(m);
					g.compute();
				}
				
				
			};
		std::unique_lock<std::mutex> l(mtxt);
		std::thread tf(functor, std::ref(f),std::ref(mtxf));
		
		std::thread tg(functor2, std::ref(g), std::ref(mtxg));

		auto future1 = std::async(std::launch::async, &std::thread::join, &tf);
		auto future2 = std::async(std::launch::async, &std::thread::join, &tg);
		
		if (future1.wait_for(std::chrono::seconds(timeout_error))
			== std::future_status::timeout || future2.wait_for(std::chrono::seconds(timeout_error))
			== std::future_status::timeout) {
			
			is_timeout_error = true;
		}

	
	}
	void print() {
		Result resultF = f.getResult();
		Result resultG = g.getResult();
		
		result = binaryOperation();
		if (is_timeout_error) {
			std::cout << "Timeout error\n" << "Information about functions and their statuses: \n";
			f.print_all_info();
			g.print_all_info();
		}
		else {
			if (result.index() == 0) {
				std::cout << "f(" << f.getX() << ")&" << "g(" << g.getX() << "):"  << std::endl;
				std::cout << "Result: " << std::get<success>(resultF.get_res()).value <<"&"<< std::get<success>(resultG.get_res()).value << "=" << std::get<int>(result) << std::endl;
			}
			else {
				if (major_error_f)
					std::cout << "Major error during computation of: " << "f(" << f.getX() << ")" << std::endl;
				if (major_error_g)
					std::cout << "Major error during computation of: " << "g(" << g.getX() << ")" << std::endl;
				if (major_error_due_to_minors_f)
					std::cout << "Major error(a lot of minor errors) during computation of: " << "f(" << f.getX() << ")" << " Number of minor errors: " << f.getResult().get_num_of_minor_errors() << std::endl;
				if (major_error_due_to_minors_g)
					std::cout << "Major error(a lot of minor errors) during computation of: " << "g(" << g.getX() << ")"<<" Number of minor errors: "<<g.getResult().get_num_of_minor_errors() << std::endl;
				if (!major_error_f && !major_error_due_to_minors_f)
					std::cout << "Result of f: " << "f(" << f.getX() << ")=" << std::get<success>(resultF.get_res()).value << std::endl;
				if (!major_error_g && !major_error_due_to_minors_g)
					std::cout << "Result of g: " << "g(" << g.getX() << ")=" << std::get<success>(resultG.get_res()).value << std::endl;
				
			}
		}
	}
	std::variant<int, major_error>  binaryOperation();
};