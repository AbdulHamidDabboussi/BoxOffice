#pragma once
#include <string>

class Theater {
	int id, numRows, numSeatsPerRow;
	std::string moviename;

public:
	Theater();
	~Theater();
	void modifyTheater(int id, int numRows, int numSeatsPerRow, std::string moviename);
	void operator=(Theater& other);
	int getId();
	int getRows();
	int getSeatsPerRow();
	int getAvailableSeats();
	std::string getMovieName();
	std::string getSeats(int, int);

	std::string **seats;
	int availableSeats;
	
};