/* ========================================================================
 * PROJECT: Numerical Optimization for windage Library
 * ========================================================================
 * This work is based on the original windage Library developed by
 *   Woonhyuk Baek
 *   Woontack Woo
 *   U-VR Lab, GIST of Gwangju in Korea.
 *   http://windage.googlecode.com/
 *   http://uvr.gist.ac.kr/
 *
 * Copyright of the derived and new portions of this work
 *     (C) 2009 GIST U-VR Lab.
 *
 * This framework is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this framework; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * For further information please contact 
 *   Woonhyuk Baek
 *   <windage@live.com>
 *   GIST U-VR Lab.
 *   Department of Information and Communication
 *   Gwangju Institute of Science and Technology
 *   1, Oryong-dong, Buk-gu, Gwangju
 *   South Korea
 * ========================================================================
 ** @author   Woonhyuk Baek
 * ======================================================================== */

#include <iostream>
#include <string.h>

#include "UnimodalOptimization/FibonacciSearch.h"
#include "UnimodalOptimization/GoldenSectionSearch.h"

#include "Utils/Logger.h"

#define FUNCTION function_example1
double INITIAL_VALUE_1 = +0.0;
double INITIAL_VALUE_2 = +1.0;

const int FIBONACCI_COUNT = 30;

// problem set
long double function_example1(long double x)
{
	return abs(x - 0.6);
}

std::string PrintErrorMessage(double value)
{
	switch((int)value)
	{
	case 0: return std::string("unknown error");break;
//	case -1:return std::string("time-out (maybe cannot found solution)");break;
	case -2:return std::string("not initialized function");break;
	case -3:return std::string("wrong initial value");break;
	case -9:return std::string("method specific error");break;
	default:
		{
			char message[100];
			sprintf(message, "time-out ( %lf : %e )", value, FUNCTION(value));
			return std::string(message);break;
		}
	}
}


void main()
{
	windage::Logger* logger = new windage::Logger(&std::cout);

	std::cout << "unimodal optimization algorithm examples\n" << std::endl;
	long double solution1 = 0.0;
	long double solution2 = 0.0;
	int iteration = 0;

	std::cout << "[[ Fibonacci Search ]]" << std::endl;
	windage::FibonacciSearch* fibonacciSearch = new windage::FibonacciSearch();
	fibonacciSearch->AttatchFunction(FUNCTION);
	fibonacciSearch->SetFibonacciCount(FIBONACCI_COUNT);
	iteration = fibonacciSearch->SeekBound(&INITIAL_VALUE_1, &INITIAL_VALUE_2);
	fibonacciSearch->SetInitialValue(INITIAL_VALUE_1, INITIAL_VALUE_2);

	logger->updateTickCount();
	std::cout << "\tinitial values : " << INITIAL_VALUE_1 << ", " << INITIAL_VALUE_2 << " (" << iteration << ")" << std::endl;
	if(fibonacciSearch->Calculate(&solution1, &solution2))
		std::cout << "\tcalculate optimization poin : [" << solution1 << ", " << solution2 << "] (repeat : " << fibonacciSearch->GetRepatCount() << ")" << std::endl;
	else
	{
		std::cout << "\tfault : can not found optimization point" << " (repeat : " << fibonacciSearch->GetRepatCount() << ")" << std::endl;
		std::cout << "\t\t( " << PrintErrorMessage(solution1).c_str() << ")" << std::endl;
	}
	logger->log("\tprocessing time", logger->calculateProcessTime());
	logger->logNewLine();

	std::cout << "[[ GoldenSection Search ]]" << std::endl;
	windage::GoldenSectionSearch* goldenSectionSearch = new windage::GoldenSectionSearch();
	goldenSectionSearch->AttatchFunction(FUNCTION);
	goldenSectionSearch->SetInitialValue(solution1, solution2);

	logger->updateTickCount();
	std::cout << "\tinitial values : " << solution1 << ", " << solution2 << std::endl;
	if(goldenSectionSearch->Calculate(&solution1, &solution2))
		std::cout << "\tcalculate optimization poin : [" << solution1 << ", " << solution2 << "] (repeat : " << goldenSectionSearch->GetRepatCount() << ")" << std::endl;
	else
	{
		std::cout << "\tfault : can not found optimization point" << " (repeat : " << goldenSectionSearch->GetRepatCount() << ")" << std::endl;
		std::cout << "\t\t( " << PrintErrorMessage(solution1).c_str() << ")" << std::endl;
	}
	logger->log("\tprocessing time", logger->calculateProcessTime());
	logger->logNewLine();

}