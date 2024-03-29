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

#ifndef _STEREO_SURF_SENSOR_DETECTOR_H_
#define _STEREO_SURF_SENSOR_DETECTOR_H_

#include <vector>
#include <cv.h>

#include "base.h"
#include "SpatialInteraction/SpatialSensor.h"
#include "SpatialInteraction/SensorDetector.h"
#include "Tracker/Calibration.h"
#include "Tracker/ModifiedSURFTracker.h"

namespace windage
{
	/**
	 * @brief
	 *		Class for Spatial Sensor Detector using stereo SURF Descriptor
	 * @author
	 *		windage
	 */
	class DLLEXPORT StereoSURFDetector : public SensorDetector
	{
	private:
		int cameraNumber;							///< number of camera
		double activationThreshold;					///< compaired image kernel size
		std::vector<Calibration*> cameraParameters;	///< activation threshold

		void Release();

		inline int GetCameraNumber(){return this->cameraNumber;};
		inline void SetCameraNumber(int cameraNumber){this->cameraNumber = cameraNumber;};

	public:
		StereoSURFDetector();
		~StereoSURFDetector();

		/**
		 * @brief
		 *		Initialize stereo-based SURF Descriptor spatial sensor detector
		 * @remark
		 *		Initialize stereo-based SURF Descriptor spatial sensor detector, set activation threshold and camera number
		 */
		void Initialize(double activationThreshold = 0.2, int cameraNumber = 2);

		inline double GetActivationThreshold(){return this->activationThreshold;};
		inline void SetActivationThreshold(double activationThreshold){this->activationThreshold = activationThreshold;};

		/**
		 * @brief
		 *		Attatch Camera Parameter
		 * @remark
		 *		attatch camera paramter only read and update from outside
		 */
		void AttatchCameraParameter(int cameraNumber, Calibration* cameraParameters);
		
		/**
		 * @brief
		 *		Get Disparity
		 * @remark
		 *		compaire SURF Descriptor from spatial sensor position
		 */
		double GetDisparity(std::vector<IplImage*>* images, SpatialSensor* sensor);

		/**
		 * @brief
		 *		Calculate Activation
		 * @remark
		 *		calculate activation from attatched all spatial sensors
		 */
		void CalculateActivation(std::vector<IplImage*>* images);

//		void operator=(const StereoSpatialSensor rhs);
	};
}

#endif