/* ========================================================================
 * PROJECT: windage Library
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

#ifndef _TEMPLATE_MINIMIZATION_H_
#define _TEMPLATE_MINIMIZATION_H_

#include <vector>
#include <cv.h>

#include "wMatrix.h"
 
namespace windage
{
	class TemplateMinimization
	{
	protected:
		static const int DELTA = 1;
		float PARAMETER_AMPLIFICATION;
		int SAMPLING_STEP;
		Matrix3 homography;

		int width;
		int height;

		IplImage* templateImage;
		IplImage* samplingImage;

		bool isInitialize;

	public:
		TemplateMinimization(int width=150, int height=150)
		{
			this->SAMPLING_STEP = 2;

			this->width = width;
			this->height = height;

			homography.m1[0] = 1.0; homography.m1[1] = 0.0; homography.m1[2] = 0.0;
			homography.m1[3] = 0.0; homography.m1[4] = 1.0; homography.m1[5] = 0.0;
			homography.m1[6] = 0.0; homography.m1[7] = 0.0; homography.m1[8] = 1.0;

			// templateImage is gray
			templateImage = cvCreateImage(this->GetTemplateSize(), IPL_DEPTH_8U, 1);
			samplingImage = cvCreateImage(this->GetTemplateSize(), IPL_DEPTH_8U, 1);
			cvZero(samplingImage);

			isInitialize = false;
		}
		virtual ~TemplateMinimization()
		{
			if(templateImage)	cvReleaseImage(&templateImage);
			if(samplingImage)	cvReleaseImage(&samplingImage);
		}

		inline void SetParameterAmplification(float amplification){this->PARAMETER_AMPLIFICATION = amplification;};
//		inline void SetSamplingStep(float step){this->SAMPLING_STEP = step;};
		
		inline CvSize GetTemplateSize(){return cvSize(this->width, this->height);};
		inline IplImage* GetTemplateImage(){return this->templateImage;};
		inline IplImage* GetSamplingImage(){return this->samplingImage;};

		virtual Matrix3 GetHomography() = 0;
		virtual void SetInitialHomography(Matrix3 homography) = 0;
		
		virtual bool AttatchTemplateImage(IplImage* image) = 0;
		virtual bool Initialize() = 0;
		virtual float UpdateHomography(IplImage* image, float* delta = NULL) = 0;
	};
}

#endif