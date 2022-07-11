#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <ColourRGB.h>
#include <Camera.h>
#include <Ellipsoid.h>


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

	Camera mainCamera;
	mainCamera.SetPerspective(60.f, (float)imageWidth / (float)imageHeight, 0.1f, 1000.f);
	mainCamera.setPosition(Vector3(0.f, 0.f, 5.f));
	mainCamera.LookAt(Vector3(0.f, 0.f, 0.f), Vector3(0.f, 1.f, 0.f));


	//output the Image Header data
	std::cout << "P3" << std::endl;
	std::cout << imageWidth << ' ' << imageHeight << std::endl;
	std::cout << channelColours << std::endl;

	//Define a sphere origin and radius
	Ellipsoid s1(Vector3(-1.f, -1.f, -15.f), 3.f);

	//get reciprocal of image dimensions
	float invWidth = 1.f / (float)imageWidth;
	float invHeight = 1.f / (float)imageHeight;

	//for each row of the image
	for (int i = 0; i < imageHeight; i++) 
	{
		std::clog << "\rCurrently rendering scanline " << i << " of " << imageHeight << std::flush;
		//for each pixel in a row
		//Calculate Screen Space Y
		float screenSpaceY = 1.f - 2.f * ((float)i + 0.5f) * invHeight;
		
		for (int j = 0; j < imageWidth; j++)
		{
			//Get the current pixel in screen space cooridnates( in range -1 to 1 )
			float screenSpaceX = 2.f * ((float)j + 0.5f) * invWidth - 1.f;
			Vector2 screenSpacePos = Vector2(screenSpaceX, screenSpaceY);

			//Create a Ray with origin at the camera and direction into the near plane offset
			Ray viewRay = mainCamera.CastRay(screenSpacePos);

			//convert ray direction into colour space 0->1
			ColourRGB rayColour;
			Vector3 hitPos = Vector3(0.f, 0.f, 0.f);
			Vector3 surfNormal = Vector3(0.f, 0.f, 0.f);

			if (s1.IntersectTest(viewRay,hitPos, surfNormal))
			{
				rayColour = (surfNormal + 1.f) * 0.5f;
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

	
	

	//set output steam buffer back to what it was previously
	std::cout.rdbuf(backup);
	return EXIT_SUCCESS;
}

