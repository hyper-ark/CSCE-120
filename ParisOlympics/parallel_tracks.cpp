#include <iostream>
#include <iomanip>
#include <cstring>
#include "parallel_tracks.h"

using std::cin, std::cout, std::endl;

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  an array of doubles is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
  for (unsigned int i = 0; i < SIZE; i++) {
	ary[i] = 0.0;
  }
}

//-------------------------------------------------------
// Name: prep_unsigned_int_array
// PreCondition:  an array of unsigned ints is passed in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	for (unsigned int i = 0; i < SIZE; i++) {
		ary[i] = 0;
	}
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  an array of strings is passed in
// PostCondition: each element in the array is set to "N/A"
//---------------------------------------------------------
void prep_string_array(char ary[][STRING_SIZE])
// making sure all values within the array are set to "N/A";
{
	for (unsigned int i = 0; i < SIZE; i++) {
		strcpy(ary[i], "N/A");
	}
}

//-------------------------------------------------------
// Name: trim
// PreCondition:  the cstring
// PostCondition: whitespace has been removed from beginning and end of string
//---------------------------------------------------------
void trim(char str[STRING_SIZE]) {

	while (isspace(str[0])) {
		for (int i = 0; str[i] != '\0'; i++) {
		str[i] = str[i+1];
		}
	}
	for (int i = strlen(str)-1; isalpha(str[i]) == 0; i--) {
		str[i] = '\0';
	}
		
}

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays
// PostCondition: all arrays contain data from standard in
//---------------------------------------------------------
bool get_runner_data(double timeArray[], char countryArray[][STRING_SIZE], 
		unsigned int numberArray[], char lastnameArray[][STRING_SIZE]) 
{
	double time;
	char country[STRING_SIZE];
	int number;
	char name[STRING_SIZE];
  
  	for (unsigned int i = 0; i < SIZE; i++) {
		cin >> time;
		cin >> country;
		cin >> number;
		cin.getline(name, STRING_SIZE);

		if (time <= 0) {
			return false;
		}

		if (strlen(country) != 3) {
			return false;
		}
		else {
			for (int i = 0; i < 3; i++) {
				if (islower(country[i])) {
					return false;
				}
			}
		}

		if ((number / 10) >= 10 || number < 0) {
			return false;
		}

		trim(name);
		if (name[1] == '\0' || name[0] == '\0') {
			return false;
		}
		else {
			for (unsigned int i = 0; name[i] != '\0'; i++) {
				if (!isalpha(name[i]) && !isspace(name[i])) {
					return false;
				}
			}
		}

		timeArray[i] = time;
		strcpy(countryArray[i], country);
		numberArray[i] = number;
		strcpy(lastnameArray[i], name);
  	}

  return true; // set so it will compile
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
	//TODO

	int rank;
	double temptime;

	for (unsigned int i = 0; i < SIZE; i++) {
		rank = 1;
		temptime = timeArray[i];

		for (unsigned int j = 0; j < SIZE; j++) {
			if (timeArray[j] < temptime) {
				rank++;
			}
		}
		rankArray[i] = rank;
	}
}


//-------------------------------------------------------
// Name: print_results
// PreCondition:  all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays them along with a delta in time from the start
//---------------------------------------------------------
void print_results(const double timeArray[], const char countryArray[][STRING_SIZE],
		const char lastnameArray[][STRING_SIZE], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}