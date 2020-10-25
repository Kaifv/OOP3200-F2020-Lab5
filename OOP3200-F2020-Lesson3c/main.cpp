#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <cstdlib>


#include "Vector2D.h"



int main()
{
	try
	{
		/************************
		 *	DECLARATIONS
		 ************************/
		std::map < std::string, Vector2D<float>*> pointDistance;


		
		/******************************************************************************
		 *	Reading Labels/Points into the Map:
		 *	Attempt to open the data file.  If the data file opens, read a label,
		 *	followed by a point and insert them into the map using the label as the key.
		 *	Repeat until all the data is read and close the file. If the data file did
		 *	not open, tell the user and remind them to check that the file exists. If
		 *	the file opened but the map is empty after the input loop, report that to
		 *	the user and remind them to check that the file contains valid data in
		 *	the correct format. Only continue processing if the file was opened and the
		 *	map is not empty.
		 ******************************************************************************/
		std::ifstream inFile;
		std::string fileName = "PointData.dat";

		inFile.open(fileName.c_str());

		if (inFile.is_open())
		{
			std::string name;
			int x, y = 0;

			while (!inFile.fail())
			{
				inFile >> name;
				inFile.ignore(1, ' ');
				inFile.ignore(1, '(');
				inFile >> x;
				inFile.ignore(1, ',');
				inFile >> y;
				inFile.ignore(1, ' ');
				inFile.ignore(1, ')');

				auto* temp_object = new Vector2D<float>(x, y);

				pointDistance[name] = temp_object;

			}

			inFile.close();

			for (const auto& map_position : pointDistance)
			{
				std::cout << "Label and Key " << map_position.first << std::endl;
				std::cout << "Value: " << map_position.second->ToString() << std::endl;

			}




			/******************************************************************************
			 *	Determine the Total Distance Between All Points in Order:
			 *	Use an iterator and a loop to traverse each label/point in the map. For
			 *	each label/point, determine the distance from that point to the previous
			 *	point (or next point depending on how you implement this) and add that
			 *	distance to a total.  Note that the Vector2D class includes a static
			 *	distance function to determine the distance between two Vector2D
			 *	objects, so you should not need to use any complicated math here.  Report
			 *	to the user how many points the map contains and what the total distance is.
			 ******************************************************************************/

			if (pointDistance.size() > 0)
			{


				//Creating an iterator
				auto iter = pointDistance.begin();
				auto* tempVector = iter->second;

				double total = 0;
				for (auto& vector : pointDistance)
				{

					auto distance1 = Vector2D<float>::Distance(*tempVector, *vector.second);

					tempVector = vector.second;

					total += distance1;
				}

				std::cout << "Map has " << std::to_string(pointDistance.size()) <<
					" key - value pair. And total distance between all the points is " << std::to_string(total);


				/******************************************************************************
				 *	Determine the Distance Between the Start Point and a User Selected Point:
				 *	Prompt the user to enter a label or to enter "quit" to end.  If the user
				 *	entered anything other than "quit", attempt to find the label they entered
				 *	in the map. If it was found, report the distance between the point for the
				 *	label they entered and the start point (i.e. the point labeled "AA").
				 *	Otherwise, tell the user that the label they entered is not in the map.
				 *	Repeat these steps until the user enters "quit".
				 ******************************************************************************/
				std::string userInput;
				std::string  exit = "quit";
				do
				{
					std::cout << "\n Enter the label of the point you wish to go to (quit to exit): ";
					std::cin >> userInput;

					if (pointDistance.find(userInput) != pointDistance.end())
					{
						auto tempVector = pointDistance.begin()->second;
						auto userPoint = pointDistance[userInput];
						auto distance = Vector2D<float>::Distance(*tempVector, *userPoint);
						std::cout << "\nThe distance between " << pointDistance.begin()->first <<
							" " << pointDistance.begin()->second->ToString() << " and " << userInput
							<< " " << *pointDistance[userInput] << " is " << std::to_string(distance) << std::endl;
					}
					else 
					{
						std::cout << "\n There is not point labeled " << userInput << " in the map\n";
					}
				} while (userInput != "quit");
			}
			else
			{
				std::cout << "The map is empty. Check that the file contains valid data in the correct format.";
			}
		}
		else
		{
			std::cout << "PointsData.dat could not be opened for input. Check that the file exists.";
		}
	}
	/******************************************************************************
	 *	Exception Handling:
	 *	Catch any std::exception thrown. Report to the user that a run-time error
	 *	occurred and show what exception was thrown.
	 ******************************************************************************/
	catch(const std::exception& ex)  // an exception was thrown
	{
		std::cerr << "\An Error occurred at run time" << ex.what() << std::endl;
	}

	// END-OF-PROGRAM
	
	return 0;
}

