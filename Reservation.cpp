#include "Reservation.h"

Reservation::Reservation() {
	size = 0;
	seatRow = NULL;
	seatCol = NULL;
	theater = NULL;
}

Reservation::Reservation( Theater *theater) {
	this->theater = theater;
}

Reservation::~Reservation() {
	theater = NULL;
	if (seatCol != NULL)
		delete[] seatCol;
	if (seatRow != NULL)
		delete[] seatRow;
}

void Reservation::operator=(const Reservation& other) {
	size = other.size;

	seatRow = new char[size];
	seatCol = new int[size];
	theater = other.theater;
	for (int i = 0; i < size; i++) {
		seatRow[i] = other.seatRow[i];
		seatCol[i] = other.seatCol[i];
	}
}
