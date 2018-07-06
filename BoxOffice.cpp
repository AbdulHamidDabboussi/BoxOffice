#include <string>
#include <sstream>
#include <iostream>
#include "BoxOffice.h"
using namespace std;


BoxOffice::BoxOffice() {
	size = 0;
	reservationCount = 0;
	theaters = NULL;
	reservations = NULL;
}
BoxOffice::~BoxOffice() {
	if (reservations != NULL)
		delete[] reservations;
	if (theaters != NULL)
		delete[] theaters;
}

void BoxOffice::addTheater(int theaterId, std::string moviename,
	int numRows, int numSeatsPerRow) {
	if (size == 0) {
		if (theaters != NULL)
			delete[] theaters;
		theaters = new Theater[1];
		theaters[0].modifyTheater(theaterId, numRows, numSeatsPerRow, moviename);
	}
	else {
		Theater *temp = new Theater[size + 1];
		for (int i = 0; i < size; i++) {
			temp[i] = theaters[i];
		}
		temp[size].modifyTheater(theaterId, numRows, numSeatsPerRow, moviename);
		if (theaters != NULL)
			delete[] theaters;
		theaters = temp;
	}
	size++;
	cout << "Theater " << theaterId << " (" +
		moviename + ") has been added" << endl;
	return;
}

void BoxOffice::removeTheater(int theaterId) {
	Theater *temp = new Theater[size - 1];
	int count = 0;
	for (int i = 0; i < size; i++) {
		if (theaters[i].getId() == theaterId) {
			for (int i = 0; i < size; i++) {
				if (theaters[i].getId() != theaterId) {
					temp[count] = theaters[i];
					count++;
				}
			}
			if (theaters != NULL)
				delete[] theaters;
			theaters = temp;
			size--;
			cout << "Theater " << theaterId << " has been removed" << endl;
			break;
		}
	}
	cout << "Theater " << theaterId << " does not exist" << endl;
	return;
}

void BoxOffice::showAllTheaters() {
	if (size == 0) {
		cout << "No movie theaters in the system!" << endl << endl;
	}
	else {
		cout << endl << "Theaters currently in the system:" << endl;
		for (int i = 0; i < size; i++) {
			cout << "Theater " << theaters[i].getId() << " (" +
				theaters[i].getMovieName() + "): " << theaters[i].getAvailableSeats() <<
				" available seats" << endl;
		}
	}
	return;

}

void BoxOffice::showTheater(int theaterId) {

	int count = 0;
	while (theaters[count].getId() != theaterId) {
		count++;
		if (count == size) {
			cout << "Theater " << theaterId << " does not exist" << endl;
			return;
		}
	}
	Theater *temp = &theaters[count];

	cout << endl << "Theater " << temp->getId() << " (" +
		temp->getMovieName() + ") has " << temp->getAvailableSeats() <<
		" available seats" << endl;

	for (int i = 0; i < temp->getRows() + 1; i++) {
		for (int j = 0; j < temp->getSeatsPerRow() + 1; j++)
			cout << temp->seats[i][j] << " ";
		cout << endl;
	}
	return;
}


int BoxOffice::makeReservation(int theaterId, int numAudiences,
	char *seatRow, int *seatCol) {

	int count = 0;
	while (theaters[count].getId() != theaterId) { //checks is theater exists
		count++;
		if (count == size) {
			cout << "Theater " << theaterId << " does not exist" << endl;
			return -1;
		}
	}
	Theater *temp = &theaters[count];
	if (temp->getAvailableSeats() < numAudiences) { //checks num of available seats
		cout << endl << "Theater " << temp->getId() << " (" +
			temp->getMovieName() + ") does not have enough space for " <<
			numAudiences << "audiences" << endl;
		return -1;
	} 
	for (int i = 0; i < numAudiences; i++) { //find if seat is available
		if (temp->getSeats((seatRow[i] - 64), seatCol[i]) == "x") {
			cout << "Seat " << seatRow[i] << seatCol[i] <<
				" has already been taken" << endl;
			return -1;
		}
	}

	if (reservationCount == 0) {
		if (reservations != NULL)
			delete[] reservations;
		reservations = new Reservation[1];
		reservations[0].size = numAudiences;
		reservations[0].seatRow = new char[numAudiences];
		reservations[0].seatCol = new int[numAudiences];
		for (int i = 0; i < numAudiences; i++) {
			reservations[0].seatRow[i] = seatRow[i];
			reservations[0].seatCol[i] = seatCol[i];
		}
		reservations[0].theater = &theaters[count];
		reservations[0].theater->availableSeats -= numAudiences;
		for (int i = 0; i < numAudiences; i++) //reserves the seats with an x
			reservations[0].theater->seats[seatRow[i] - 64][seatCol[i]] = "x";
		reservationCount++;
		cout << "Your reservation code is " << reservationCount << endl;
		
	}
	else {
		Reservation *resTemp = new Reservation[reservationCount + 1];
		for (int i = 0; i < reservationCount; i++)
			resTemp[i] = reservations[i];
		resTemp[reservationCount].seatRow = new char[numAudiences];
		resTemp[reservationCount].seatCol = new int[numAudiences];
		for (int i = 0; i < numAudiences; i++) {
			resTemp[reservationCount].seatRow[i] = seatRow[i];
			resTemp[reservationCount].seatCol[i] = seatCol[i];
		}
		resTemp[reservationCount].size = numAudiences;
		resTemp[reservationCount].theater = &theaters[count];
		for (int i = 0; i < numAudiences; i++) //reserves the seats with an x
			resTemp[reservationCount].theater->seats[seatRow[i] - 64][seatCol[i]] = "x";
		resTemp[reservationCount].theater->availableSeats -= numAudiences;
		reservationCount++;
		cout << "Your reservation code is " << reservationCount << endl;
		
		if ( reservations != NULL)
			delete[] reservations;
		reservations = resTemp;
	}
	return reservationCount;
}

void BoxOffice::cancelReservation(int resCode) {
	if (resCode > reservationCount || reservations[resCode - 1].size < 0)
		cout << "No reservation under code " << resCode << endl;
	else {
		for (int i = 0; i < reservations[resCode].size; i++) {
			//frees the reserved seats
			reservations[resCode - 1].theater->seats[reservations[resCode - 1].seatRow[i] - 64][reservations[resCode - 1].seatCol[i]] = 'o';
			reservations[resCode - 1].theater->availableSeats++;
		}
		cout << "Reservation for seats ";
		for (int i = 0; i < reservations[resCode - 1].size; i++) {
			cout << reservations[resCode - 1].seatRow[i] << reservations[resCode - 1].seatCol[i] << " ";
		}
		cout << "is canceled in Theater " << reservations[resCode - 1].theater->getId() <<
			" (" << reservations[resCode - 1].theater->getMovieName() << ")" << endl;
		reservations[resCode - 1].size = -1;
	}
	return;
}

void BoxOffice::showReservation(int resCode) {
	if (resCode > reservationCount || reservations[resCode - 1].size < 0)
		cout << "No reservation under code " << resCode << endl;
	else {
		cout << "Reservation under code " << resCode << " in Theater " << reservations[resCode - 1].theater->getId() <<
			" (" << reservations[resCode - 1].theater->getMovieName() << "): ";
		for (int i = 0; i < reservations[resCode - 1].size; i++) {
			cout << reservations[resCode - 1].seatRow[i] << reservations[resCode - 1].seatCol[i] << " ";
		}
	}
	cout << endl;
}

int main() {
	BoxOffice R;
	R.showAllTheaters();
	R.addTheater(10425, "Ted", 4, 3);
	R.addTheater(8237, "Cloud Atlas", 8, 3);
	R.showAllTheaters();
	R.showTheater(8237);
	char row[4] = {'A','B','B','C'};
	int col[4] = {3,3,1,1};
	int code1 = R.makeReservation(10425, 4, row, col);
	int code2 = R.makeReservation(8237, 4, row, col);
	R.showTheater(10425);
	R.showTheater(8237);
	R.showReservation(10425);
	R.showAllTheaters();
	R.showReservation(1);
	R.showReservation(2);
	R.cancelReservation(1);
	R.showReservation(1);
	R.showReservation(2);
	return 0;
}