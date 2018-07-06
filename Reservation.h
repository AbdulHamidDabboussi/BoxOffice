#pragma once
#include "Theater.h"

class Reservation {
public:
	Theater *theater;
	char *seatRow;
	int *seatCol;
	int size;

	Reservation();
	Reservation(Theater* theater);
	~Reservation();
	void operator= (const Reservation &other);

};