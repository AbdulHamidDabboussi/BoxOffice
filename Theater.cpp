#include "Theater.h"

Theater::Theater() {
	id = 0;
	numRows = 0;
	numSeatsPerRow = 0;
	moviename = "";
	availableSeats = numRows * numSeatsPerRow;

	seats = new std::string*[numRows + 1];
	//initializes the available seats
	for (int i = 0; i <= numRows; i++) { //to includes the letters and numbers 
		seats[i] = new std::string[numSeatsPerRow + 1];
		for (int j = 1; j <= numSeatsPerRow; j++) //sets the seats of each row to be available
			seats[i][j] = "o";
	}
	//initializes the letters
	std::string letters[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
							  "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V",
							  "W", "Y", "X", "Z" };
	for (int i = 1; i <= numRows; i++)
		seats[i][0] = letters[i - 1];
	for (int i = 1; i <= numSeatsPerRow; i++)
		seats[0][i] = i;
	seats[0][0] = " ";
}


void Theater::modifyTheater(int id, int numRows, int numSeatsPerRow, std::string moviename) {
	this->~Theater();
	this->id = id;
	this->numRows = numRows;
	this->numSeatsPerRow = numSeatsPerRow;
	this->moviename = moviename;
	availableSeats = numRows * numSeatsPerRow;

	seats = new std::string*[numRows + 1];
	//initializes the available seats
	for (int i = 0; i <= numRows; i++) { //to includes the letters and numbers 
		seats[i] = new std::string[numSeatsPerRow + 1];
		for (int j = 1; j <= numSeatsPerRow; j++) //sets the seats of each row to be available
			seats[i][j] = "o";
	}
	//initializes the letters
	std::string letters[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
							  "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V",
							  "W", "Y", "X", "Z" };
	for (int i = 1; i <= numRows; i++)
		seats[i][0] = letters[i - 1];
	for (int i = 1; i <= numSeatsPerRow; i++)
		seats[0][i] = std::to_string(i);
	seats[0][0] = " ";
}

void Theater::operator=(Theater& other) {
	this->~Theater();
	id = other.id;
	numRows = other.numRows;
	numSeatsPerRow = other.numSeatsPerRow;
	moviename = other.moviename;
	availableSeats = other.availableSeats;


	seats = new std::string*[numRows + 1];
	for (int i = 0; i < numRows + 1; i++) {
		seats[i] = new std::string[numSeatsPerRow + 1];
		for (int j = 0; j < numSeatsPerRow + 1; j++) //sets the seats of each row to be available
			seats[i][j] = other.getSeats(i, j);
	}
	
}

int Theater::getId() {
	return id;
}

int Theater::getRows() {
	return numRows;
}

int Theater::getSeatsPerRow() {
	return numSeatsPerRow;
}

int Theater::getAvailableSeats() {
	return availableSeats;
}

std::string Theater::getMovieName() {
	return moviename;
}

std::string Theater::getSeats(int i, int j) {
	return seats[i][j];
}

Theater::~Theater() {
	for (int i = 0; i < numRows + 1; i++) {
		delete[] seats[i];
	}
	delete[] seats;
}