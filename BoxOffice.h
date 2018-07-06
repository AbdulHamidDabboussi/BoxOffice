#pragma once
#include <string>
#include "Theater.h"
#include "Reservation.h"

class BoxOffice {
public:
	BoxOffice();
	~BoxOffice();
	void addTheater(int theaterId, std::string moviename,
		int numRows, int numSeatsPerRow);
	void removeTheater(int theaterId);
	void showAllTheaters();
	void showTheater(int theaterId);
	int makeReservation(int theaterId, int numAudiances,
		char *seatRow, int *seatcol);
	void cancelReservation(int resCode);
	void showReservation(int resCode);

private:
	
	int size;
	int reservationCount;
	Theater *theaters;
	Reservation *reservations;
	
};