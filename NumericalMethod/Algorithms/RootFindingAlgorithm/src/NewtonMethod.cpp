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

#include "NewtonMethod.h"

using namespace windage;
NewtonMethod::NewtonMethod()
{
	xValue = 0.0;
	derivativeFunction = 0;
}

bool NewtonMethod::Calculate(long double* solution)
{
	this->repeat = 1;

	// fault initialization
	if(!function || !derivativeFunction)
	{
		(*solution) = -2;
		return false;
	}

	long double localXValue = this->xValue;

	bool processing = true;
	while(processing)
	{
		long double result = function(localXValue);
		long double derivativeResult = derivativeFunction(localXValue);
		
		if(abs(result) < LEAST_ERROR_RANGE)
		{
			(*solution) = localXValue;
			return true;
		}
		if(abs(derivativeResult) < LEAST_ERROR_RANGE) // do not following next step
		{
			(*solution) = -10;
			return false;
		}
		
		localXValue = localXValue - (result / derivativeResult);

		this->repeat++;
		if(this->repeat > MAX_INTERATE_TIME)
		{
			(*solution) = localXValue;
			return false;
		}
	}

	(*solution) = 0;
	return false;
}