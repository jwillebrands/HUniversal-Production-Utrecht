/**
 * @file QRCodeDetector.cpp
 * @brief Detects barcodes and extract values
 * @date Created: 2012-10-02
 *
 * @author Glenn Meerstra
 * @author Zep Mouris
 * @author Koen Braham
 * @author Daan Veltman
 *
 * @section LICENSE
 * License: newBSD
 * 
 * Copyright © 2012, HU University of Applied Sciences Utrecht.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * - Neither the name of the HU University of Applied Sciences Utrecht nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE HU UNIVERSITY OF APPLIED SCIENCES UTRECHT
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 **/

#include <sstream>
#include <vector>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include "Vision/QRCodeDetector.h"
#include "DataTypes/Crate.h"

<<<<<<< HEAD
/**
 * Constructor which sets the values for the scanner.
 **/
QRCodeDetector::QRCodeDetector() {
    scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);
}

/**
 * Detects multiple crate QR codes and returns their location data.
 *
 * @param image The image to detect the QR codes on.
 * @param crates Vector where crates can be stored on.
 * @param criteria Criteria (with a default value) for the refinement of corner pixels on the detected QR codes. OpenCV termcriteria: "Criteria for termination of the iterative process of corner refinement. That is, the process of corner position refinement stops either after a certain number of iterations or when a required accuracy is achieved. The criteria may specify either of or both the maximum number of iteration and the required accuracy."
 */
void QRCodeDetector::detectQRCodes(cv::Mat& image, std::vector<DataTypes::Crate> &crates, cv::TermCriteria criteria) {
	try {
		// create an image in zbar with:
		// width
		// height
		// fourcc format "Y800" (simple, single Y plane for monchrome images)
		// pointer to image.data
		// area of the image
		zbar::Image zbarImage(image.cols, image.rows, "Y800", (void*)image.data, image.cols * image.rows);

		int amountOfScannedResults = scanner.scan(zbarImage);

		if (amountOfScannedResults > 0) {

			zbar::Image::SymbolIterator it = zbarImage.symbol_begin();
			for(; it!=zbarImage.symbol_end(); ++it) {
				// if the current QR code is a crate (starts with GC)
				if(boost::starts_with(it->get_data(), "GC")) {
					// add all "position" corners of a qr code to a vector
					std::vector<cv::Point2f> corners;
					corners.push_back(cv::Point2f(it->get_location_x(1), it->get_location_y(1)));
					corners.push_back(cv::Point2f(it->get_location_x(0), it->get_location_y(0)));
					corners.push_back(cv::Point2f(it->get_location_x(3), it->get_location_y(3)));

					// windowsSize is half of the sidelength of the window around every coordinate to check by cornerSubPix.
					// No idea why the distance between two corners is divided by 65.0 (effectively), but the result is:
					//  65 px distance = (1 x 1) windowsSize > ( 3 x  3) window
					// 130 px distance = (2 x 2) windowsSize > ( 5 x  5) window
					// 195 px distance = (3 x 3) windowsSize > ( 7 x  7) window
					// 260 px distance = (4 x 4) windowsSize > ( 9 x  9) window
					// 325 px distance = (5 x 5) windowsSize > (11 x 11) window
					// 390 px distance = (6 x 6) windowsSize > (13 x 13) window
					// 455 px distance = (7 x 7) windowsSize > (15 x 15) window
					// 520 px distance = (8 x 8) windowsSize > (17 x 17) window
					// etc...
					float windowsSize = 2.0 * (Crate::distance(corners[0], corners[2]) / 130.0);

					// The cornerSubPix function iterates to find the sub-pixel accurate location of corners or radial saddle points
					// corners is now updated!
					cv::cornerSubPix(image, corners, cv::Size(windowsSize,windowsSize), cv::Size(-1,-1), criteria);

					crates.push_back(Crate(it->get_data(), corners));
				}
			}
		}
	} catch (std::exception &e) {
		return;
	}
}

/**
 * Detects multiple reconfigure QR codes and returns their string data.
 *
 * @param image The image to detect the QR codes on.
 * @param reconfigureCommands Vector where the QR code data can be stored on.
 */
void QRCodeDetector::detectQRCodes(cv::Mat& image, std::vector<string> &reconfigureCommands) {
	try {
		// create an image in zbar with:
		// width
		// height
		// fourcc format "Y800" (simple, single Y plane for monchrome images)
		// pointer to image.data
		// area of the image
		zbar::Image zbarImage(image.cols, image.rows, "Y800", (void*)image.data, image.cols * image.rows);
=======
namespace Vision{
	QRCodeDetector::QRCodeDetector() {
		scanner.set_config(zbar::ZBAR_QRCODE, zbar::ZBAR_CFG_ENABLE, 1);
	}

	QRCodeDetector::~QRCodeDetector() {}

	bool QRCodeDetector::detect(cv::Mat& image, std::string &result) {
		try {
		/**
		 * create an image in zbar with:
		 * width
		 * height
		 * fourcc format "Y800" (simple, single Y plane for monchrome images)
		 * pointer to image.data
		 * area of the image
		**/
		 zbar::Image zbarImage(image.cols, image.rows, "Y800", (void*)image.data, image.cols * image.rows);

		// scan for symbols
		 int amountOfScannedResults = scanner.scan(zbarImage);

		 if (amountOfScannedResults) {
		 	zbar::Image::SymbolIterator symbol = zbarImage.symbol_begin();

		 	result = symbol->get_data();

		 } else {
		 	return false;
		 }
		} catch (std::exception &e) {
			return false;
		}
		return true;
	}

	void QRCodeDetector::detectCrates(cv::Mat& image, std::vector<DataTypes::Crate> &crates, cv::TermCriteria criteria) {
		try {
		/**
		 * create an image in zbar with:
		 * width
		 * height
		 * fourcc format "Y800" (simple, single Y plane for monchrome images)
		 * pointer to image.data
		 * area of the image
		**/
		 zbar::Image zbarImage(image.cols, image.rows, "Y800", (void*)image.data, image.cols * image.rows);
>>>>>>> b610a9128f0b1a774cbc856246e7edf0901d801f

		 int amountOfScannedResults = scanner.scan(zbarImage);

<<<<<<< HEAD
		if (amountOfScannedResults > 0) {
			zbar::Image::SymbolIterator it = zbarImage.symbol_begin();

			for(; it!=zbarImage.symbol_end(); ++it) {
				// if the current QR code is not a crate (start with RC)
				if(boost::starts_with(it->get_data(), "RC")) {
					reconfigureCommands.push_back(it->get_data());
=======
		 if (amountOfScannedResults > 0) {

		 	zbar::Image::SymbolIterator it = zbarImage.symbol_begin();
		 	for(; it!=zbarImage.symbol_end(); ++it) {
				// add all "position" corners of a qr code to a vector
		 		std::vector<cv::Point2f> corners;
		 		corners.push_back(cv::Point2f(it->get_location_x(1), it->get_location_y(1)));
		 		corners.push_back(cv::Point2f(it->get_location_x(0), it->get_location_y(0)));
		 		corners.push_back(cv::Point2f(it->get_location_x(3), it->get_location_y(3)));

				/**
				 * windowsSize is half of the sidelength of the window around every coordinate to check by cornerSubPix.
				 * No idea why the distance between two corners is divided by 65.0 (effectively), but the result is:
				 *  65 px distance = (1 x 1) windowsSize > ( 3 x  3) window
				 * 130 px distance = (2 x 2) windowsSize > ( 5 x  5) window
				 * 195 px distance = (3 x 3) windowsSize > ( 7 x  7) window
				 * 260 px distance = (4 x 4) windowsSize > ( 9 x  9) window
				 * 325 px distance = (5 x 5) windowsSize > (11 x 11) window
				 * 390 px distance = (6 x 6) windowsSize > (13 x 13) window
				 * 455 px distance = (7 x 7) windowsSize > (15 x 15) window
				 * 520 px distance = (8 x 8) windowsSize > (17 x 17) window
				 * etc...
				 **/
				 float windowsSize = 2.0 * (DataTypes::Crate::distance(corners[0], corners[2]) / 130.0);

				/**
				 * The cornerSubPix function iterates to find the sub-pixel accurate location of corners or radial saddle points
				 * corners is now updated!
				 **/
				 cv::cornerSubPix(image, corners, cv::Size(windowsSize,windowsSize), cv::Size(-1,-1), criteria);

				 crates.push_back(DataTypes::Crate(it->get_data(), corners));
>>>>>>> b610a9128f0b1a774cbc856246e7edf0901d801f
				}
			}
		} catch (std::exception &e) {
			return;
		}
	}
}
