#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <ColourRGB.h>


typedef enum input_args
{
	OUTPUT_FILE = 1,
	OUTPUT_WIDTH,
	OUTPUT_HEIGHT,
}input_args;

void displayUsage(char* a_path) {
	std::string fullpath = a_path;//get the full path as a string
		//strip off the path part of the string to only keep the executable name
	std::string exeName = fullpath.substr(fullpath.find_last_of('\\') + 1, fullpath.length());
	//display a message to the user indicating usage of the executable
	std::cout << "usage: " << exeName << " [output image name] [image width] [image height]" << std::endl;
}



int main(int argv, char* argc[]) {

	//Setting up the dimensions of the image
	int imageWidth = 1920;
	int imageHeight = 1080;
	int channelColours = 255;

	//output file name
	std::string outputFilename;

	if (argv < 2) { //less than 2 as the path and executable name are always present
		displayUsage(argc[0]);
		return EXIT_SUCCESS;
	}
	else {
		for (int i = 1; i < argv; i++) {
			std::string arg = argc[i];
			if (arg == "-h" || arg == "--help") {
				displayUsage(argc[0]);
				return EXIT_SUCCESS;
			}
			switch (i) 
			{
			case OUTPUT_FILE: {
				outputFilename = argc[OUTPUT_FILE];
				//check to see if the extension was included
				if (outputFilename.find_last_of(".") == std::string::npos) {
					//no extension better add one
					outputFilename.append(".ppm");
				}
				break;
			}
			case OUTPUT_WIDTH: {
				imageWidth = atoi(argc[OUTPUT_WIDTH]);
				break;
			}
			case OUTPUT_HEIGHT: {
				imageHeight = atoi(argc[OUTPUT_HEIGHT]);
				break;
			}
			default:{
				continue;
			}
			}
		}
	}

	//Need to change std::cout to outputFilename

	std::streambuf* backup = std::cout.rdbuf(); //backup std::cout's stream buffer
	std::ofstream outbuff(outputFilename.c_str()); //create an out file stream and set it to our output file name
	std::cout.rdbuf(outbuff.rdbuf()); //set the stream buffer for cout to the file out stream buffer

	//set up aspect ratio
	float aspectRatio = (float)imageWidth / (float)imageHeight;
	//set up camera
	float nearPlaneHeight	= 2.f;
	float nearPlaneWidth	= aspectRatio * nearPlaneHeight;
	float nearPlaneDistance = 1.f;
	//camera position
	Vector3 cameraPosition = Vector3(0.f, 0.f, 0.f);
	//Camera Axis
	Vector3 cameraRight = Vector3(1.f, 0.f, 0.f);
	Vector3 cameraUp	= Vector3(0.f, 1.f, 0.f);
	Vector3 cameraFwd	= Vector3(0.f, 0.f, -1.f);
	//work out the ratio of the near plane to the output image
	//this will be the increment horizontally and vertically for each pixel in the image
	float imageWidthToPlaneRatio = nearPlaneWidth / (float)imageWidth;
	float imageHeightToPlaneRatio = nearPlaneHeight / (float)imageHeight;

	Vector3 upperLeftCorner = cameraPosition + Vector3(-nearPlaneWidth * 0.5f, nearPlaneHeight * 0.5f, -nearPlaneDistance);



	//output the Image Header data
	std::cout << "P3" << std::endl;
	std::cout << imageWidth << ' ' << imageHeight << std::endl;
	std::cout << channelColours << std::endl;

	//Define a sphere origin and radius
	Vector3 spherePos = Vector3(0.f, 0.f, -1.f);
	float sphereRadius = 0.5f;

	int i = 0;
	//for each row of the image
	for (float vPos = imageHeightToPlaneRatio; vPos < nearPlaneHeight; vPos += imageHeightToPlaneRatio, i++) 
	{
		std::clog << "\rCurrently rendering scanline " << i << " of " << imageHeight << std::flush;
		//for each pixel in a row
		for (float hPos = imageWidthToPlaneRatio; hPos < nearPlaneWidth; hPos += imageWidthToPlaneRatio)
		{
			//calculate colour value as a float in range 0->1
			Vector3 offset = cameraRight * hPos + cameraUp * -vPos + cameraFwd * 0.5f;
			Ray viewRay(cameraPosition, (upperLeftCorner + offset) - cameraPosition);

			//convert ray direction into colour space 0->1
			ColourRGB rayColour;
			float intersectDistance = viewRay.IntersectSphere(spherePos, sphereRadius);
			if (intersectDistance > 0.f)
			{
				Vector3 surfaceNormal = viewRay.PointAt(intersectDistance) - spherePos;
				surfaceNormal.Normalize();
				rayColour = (surfaceNormal + 1.f) * 0.5f;
			}
			else
			{
				rayColour = RaytoColour(viewRay);
				//Use Lerp to get colour between white and blue based on the vertical value of the rayColour
				rayColour = Lerp(Vector3(1.f, 1.f, 1.f), Vector3(0.4f, 0.7f, 1.f), rayColour.y);
			}
			//write to output
			WriteColourRGB(std::cout, rayColour);
		}
		std::cout << std::endl;
	}

	
	


	return EXIT_SUCCESS;
}

