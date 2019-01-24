//Theodoros Psarra
//Airport Handling System
#include "List.cpp"

errorCode StringEqualCheck(const char s1[], const char s2[]);

void ModifyTime(const int size, char ID[], List<FlightRec>&flights, FlightRec &Plane);

void DeleteFlight(char ID[], int &size, List<FlightRec> &flights, FlightRec &Plane);

void EnterFlight(char ID[], char delay, char FType, int &size, List<FlightRec> &flights, FlightRec &Plane, const TimeRec currentTime);

void ModifyDelay(const int size, char ID[], List<FlightRec>&flights, FlightRec &Plane);

void PrintDeparture(const int size, List<FlightRec>&flights, FlightRec &Plane, const TimeRec currentTime);

void PrintArrivals(const int size, List<FlightRec>&flights, FlightRec &Plane, const TimeRec currentTime);

void SortByID(const int size, List<FlightRec> &flights, FlightRec &plane);

void SortByTime(const int size, List<FlightRec> &flights, FlightRec &Plane);

void WriteToFile(const int size, const List<FlightRec> flights, const FlightRec Plane);

void ReadFromFile(int &size, List < FlightRec> &flights, FlightRec &Plane);

void ExtractInteger(string str, int &hour, int &min, int &sec);

int main() {
	List<FlightRec> flights;
	FlightRec Plane;
	TimeRec currentTime;
	char FType = '0';
	int choice = 0;
	char delay = '0';
	int size = 0;
	char ID[10];

	do {
		cout << "Enter the current time(h/m/s):";
		cin >> currentTime.hour >> currentTime.min >> currentTime.sec;
	} while ((currentTime.hour > 24 || currentTime.hour < 0) || (currentTime.min > 60 || currentTime.min < 0) || (currentTime.sec > 60 || currentTime.sec < 0));

	while (choice != -1) {
		cout << "Enter you choice,-1 to quit";
		cout << "\n               1:Enter Current Time";
		cout << "\n               2:Read From a File";
		cout << "\n               3:Write to a File";
		cout << "\n               4:Enter a new Flight";
		cout << "\n               5:Get Size";
		cout << "\n               6:Get Planes Information";
		cout << "\n               7:Delete A Flight";
		cout << "\n               8:Modify the time of a flight";
		cout << "\n               9:Modify the Delay in a flight";
		cout << "\n              10:Dsiplay flights who have not departured yet";
		cout << "\n              11:Display flight who have arrived yet";
		cout << "\n              12:Sort by Flight ID";
		cout << "\n              13:Sort by Time";
		cout << "\n";
		cin >> choice;

		switch (choice) {
		case 1:
			do {
			cout << "Enter the current time(h/m/s):";
			cin >> currentTime.hour >> currentTime.min >> currentTime.sec;
			} while ((currentTime.hour > 24 || currentTime.hour < 0) || (currentTime.min > 60 || currentTime.min < 0) || (currentTime.sec > 60 || currentTime.sec < 0));
			break;

		case 2:
			ReadFromFile(size, flights, Plane);
			break;

		case 3:
			WriteToFile(size,flights,Plane);
			break;

		case 4:
			EnterFlight(ID, delay, FType, size, flights, Plane, currentTime);
			break;

		case 5:
			cout << "The Size is:";
			cout << flights.size();
			cout << endl;
			break;

		case 6:
			flights.print();
			break;

		case 7:
			DeleteFlight(ID, size, flights, Plane);
			break;

		case 8:
			ModifyTime(size, ID, flights, Plane);
			break;

		case 9:
			ModifyDelay(size, ID, flights, Plane);
			break;

		case 10:
			PrintDeparture(size, flights, Plane, currentTime);
			break;

		case 11:
			PrintArrivals(size, flights, Plane, currentTime);
			break;

		case 12:
			SortByID(size, flights, Plane);
			break;

		case 13:
			SortByTime(size, flights, Plane);
			break;
		}
	}
}

ostream& operator <<(ostream &stream, FlightRec &data) {
	string value;

	stream << data.FlightNO << ";"
		<< data.Destination << ";";
	if (data.Ftype == Departure)
		stream << "Departure" << ';';
	if (data.Ftype == Arrival)
		stream << "Arrival" << ';';
	if (data.Delay == 1)
		stream << "Delayed" << ";" << data.ExpectedTime.hour << ":" << data.ExpectedTime.min << ":" << data.ExpectedTime.sec << "\n";
	else
		stream << "On Time" << ";" << data.Time.hour << ":" << data.Time.min << ":" << data.Time.sec << "\n";
	return stream;
}

void CopyValues(FlightRec &a, const FlightRec b) {

	for (int k = 0; k < 10; k++) {
		a.FlightNO[k] = b.FlightNO[k];
		a.Destination[k] = b.Destination[k];
	}
	a.Time.hour = b.Time.hour;
	a.Time.min = b.Time.min;
	a.Time.sec = b.Time.sec;
	a.Ftype = b.Ftype;
	a.Delay = b.Delay;
	if (a.Delay == true) {
		a.ExpectedTime.hour = b.ExpectedTime.hour;
		a.ExpectedTime.min = b.ExpectedTime.min;
		a.ExpectedTime.sec = b.ExpectedTime.sec;
	}
}

errorCode StringEqualCheck(const char s1[], const char s2[]) {
	int counter = 0;
	int i = 0;
	int j = 0;

	for (i = 0; i < 10; i++) {};
	for (j = 0; j < 10; j++) {};

	if (i > j) {
		for (j = 0; j < i; j++) {
			if (s1[j] == s2[j])
				counter++;
		}
		if (counter == i)
			return success;
	}
	else {
		for (int i = 0; i < j; i++) {
			if (s1[i] == s2[i])
				counter++;
		}
		if (counter == j)
			return success;
	}


	return fail;
}

void DeleteFlight(char ID[], int &size, List<FlightRec> &flights, FlightRec &Plane) {
	cout << "Enter Flight Number:";
	cin >> ID;

	for (int i = 0; i < size; i++) {
		if (flights.retrieve(i, Plane) == success)
			if (StringEqualCheck(ID, Plane.FlightNO) == success)
				flights.remove(i, Plane);
	}

}

void EnterFlight(char ID[], char delay, char FType, int &size, List<FlightRec> &flights, FlightRec &Plane, const TimeRec currentTime) {
	bool AlreadyExists;

	do {
		AlreadyExists = false;
		cout << "\nEnter Flight Number:";
		cin >> ID;

		for (int i = 0; i < size; i++) {//Checks if the ID is already registered
			if (flights.retrieve(i, Plane) == success) {
				if (StringEqualCheck(ID, Plane.FlightNO) == success) {
					cout << "ID already exists";
					AlreadyExists = true;
					break;
				}
			}
		}
	} while (AlreadyExists == true);

	for (int j = 0; j < 10; j++)
		Plane.FlightNO[j] = ID[j];

	cout << "\nEnter the Destination:";
	cin >> Plane.Destination;

	do {
		cout << "\nEnter the time it's going to Arrive/Depart(h/m/s):";
		cin >> Plane.Time.hour >> Plane.Time.min >> Plane.Time.sec;
	} while ((Plane.Time.hour > 24 || Plane.Time.hour < 0) || (Plane.Time.min > 60 || Plane.Time.min < 0) || (Plane.Time.sec > 60 || Plane.Time.sec < 0));

do {
	cout << "\nEnter Flight Type(A/D):";
	cin >> FType;
} while ((FType != 'A' && FType != 'a') && (FType != 'D' && FType != 'd'));

if (FType == 'A' || FType == 'a') {
	Plane.Ftype = Arrival;
}
else if (FType == 'D' || FType == 'd') {
	Plane.Ftype = Departure;
}

do {
	cout << "\nIs the flight gonna be delayed?(Y/N)";
	cin >> delay;
} while ((delay != 'Y' && delay != 'y') && (delay != 'N' && delay != 'n'));

if (delay == 'Y' || delay == 'y') {
	Plane.Delay = true;
	cout << "\nWhen the flight is expected to Arrive(h/m/s)?";
	cin >> Plane.ExpectedTime.hour >> Plane.ExpectedTime.min >> Plane.ExpectedTime.sec;
}
else if (delay == 'N' || delay == 'n')
Plane.Delay = false;

flights.add(size, Plane);
size++;
}

void ModifyTime(const int size, char ID[], List<FlightRec>&flights, FlightRec &Plane) {
	cout << "Enter Flight ID:";
	cin >> ID;

	for (int i = 0; i < size; i++) {
		if (flights.retrieve(i, Plane) == success)
			if (StringEqualCheck(ID, Plane.FlightNO) == success) {
				do {
					cout << "\nEnter the time you want(h/m/s):";
					cin >> Plane.Time.hour >> Plane.Time.min >> Plane.Time.sec;
				} while ((Plane.Time.hour > 24 || Plane.Time.hour < 0) || (Plane.Time.min > 60 || Plane.Time.min < 0) || (Plane.Time.sec > 60 || Plane.Time.sec < 0));
				flights.replace(i, Plane);
			}
	}
}

void ModifyDelay(const int size, char ID[], List<FlightRec>&flights, FlightRec &Plane) {
	cout << "Enter Flight ID:";
	cin >> ID;

	for (int i = 0; i < size; i++) {
		if (flights.retrieve(i, Plane) == success)
			if (StringEqualCheck(ID, Plane.FlightNO) == success) {
				Plane.Delay = 1;
				do {
					cout << "\nEnter expected Time:";
					cin >> Plane.ExpectedTime.hour >> Plane.ExpectedTime.min >> Plane.ExpectedTime.sec;
				} while ((Plane.ExpectedTime.hour > 24 || Plane.ExpectedTime.hour < 0) || (Plane.ExpectedTime.min > 60 || Plane.ExpectedTime.min < 0) || (Plane.ExpectedTime.sec > 60 || Plane.ExpectedTime.sec < 0));
				flights.replace(i, Plane);
			}
	}

}

void PrintDeparture(const int size, List<FlightRec>&flights, FlightRec &Plane, const TimeRec currentTime) {
	for (int i = 0; i < size; i++) {
		if (flights.retrieve(i, Plane) == success && Plane.Ftype == Departure) {
			if (Plane.Delay == false) {
				if (Plane.Time.hour > currentTime.hour) {
					cout << "FLIGHT NO     DESTINATION    TIME\n";
					cout << Plane.FlightNO << setw(20) << setfill(' ') << Plane.Destination << setw(7) << setfill(' ') << Plane.Time.hour << ":" << Plane.Time.min;
				}
				else if (Plane.Time.hour == currentTime.hour && Plane.Time.min > currentTime.min) {
					cout << "FLIGHT NO     DESTINATION    TIME\n";
					cout << Plane.FlightNO << setw(20) << setfill(' ') << Plane.Destination << setw(7) << setfill(' ') << Plane.Time.hour << ":" << Plane.Time.min;
				}
				else if (Plane.Time.hour == currentTime.hour && Plane.Time.min == currentTime.min && Plane.Time.sec > currentTime.sec) {
					cout << "FLIGHT NO     DESTINATION    TIME\n";
					cout << Plane.FlightNO << setw(20) << setfill(' ') << Plane.Destination << setw(7) << setfill(' ') << Plane.Time.hour << ":" << Plane.Time.min;
				}
			}
			else if (Plane.Delay == true) {
				if (Plane.ExpectedTime.hour > currentTime.hour) {
					cout << "FLIGHT NO     DESTINATION    TIME\n";
					cout << Plane.FlightNO << setw(20) << setfill(' ') << Plane.Destination << setw(7) << setfill(' ') << Plane.ExpectedTime.hour << ":" << Plane.ExpectedTime.min;
				}
				else if (Plane.ExpectedTime.hour == currentTime.hour && Plane.ExpectedTime.min > currentTime.min) {
					cout << "FLIGHT NO     DESTINATION    TIME\n";
					cout << Plane.FlightNO << setw(20) << setfill(' ') << Plane.Destination << setw(7) << setfill(' ') << Plane.ExpectedTime.hour << ":" << Plane.ExpectedTime.min;
				}
				else if (Plane.ExpectedTime.hour == currentTime.hour && Plane.ExpectedTime.min == currentTime.min && Plane.ExpectedTime.sec > currentTime.sec) {
					cout << "FLIGHT NO     DESTINATION    TIME\n";
					cout << Plane.FlightNO << setw(20) << setfill(' ') << Plane.Destination << setw(7) << setfill(' ') << Plane.ExpectedTime.hour << ":" << Plane.ExpectedTime.min;
				}
			}
		}
	}
	cout << "\n";
}

void PrintArrivals(const int size, List<FlightRec>&flights, FlightRec &Plane, const TimeRec currentTime) {

	for (int i = 0; i < size; i++) {
		if (flights.retrieve(i, Plane) == success && Plane.Ftype == Arrival) {
			if (Plane.Delay == false) {
				if (Plane.Time.hour > currentTime.hour) {
					cout << "FLIGHT NO     DESTINATION    TIME\n";
					cout << Plane.FlightNO << setw(20) << setfill(' ') << Plane.Destination << setw(10) << setfill(' ') << Plane.Time.hour << ":" << Plane.Time.min;
				}
				else if (Plane.Time.hour == currentTime.hour && Plane.Time.min > currentTime.min) {
					cout << "FLIGHT NO     DESTINATION    TIME\n";
					cout << Plane.FlightNO << setw(20) << setfill(' ') << Plane.Destination << setw(10) << setfill(' ') << Plane.Time.hour << ":" << Plane.Time.min;
				}
				else if (Plane.Time.hour == currentTime.hour && Plane.Time.min == currentTime.min && Plane.Time.sec > currentTime.sec) {
					cout << "FLIGHT NO     DESTINATION    TIME\n";
					cout << Plane.FlightNO << setw(20) << setfill(' ') << Plane.Destination << setw(10) << setfill(' ') << Plane.Time.hour << ":" << Plane.Time.min;
				}
			}
			else if (Plane.Delay == true) {
				if (Plane.ExpectedTime.hour > currentTime.hour) {
					cout << "FLIGHT NO     DESTINATION    TIME\n";
					cout << Plane.FlightNO << setw(20) << setfill(' ') << Plane.Destination << setw(10) << setfill(' ') << Plane.ExpectedTime.hour << ":" << Plane.ExpectedTime.min;
				}
				else if (Plane.ExpectedTime.hour == currentTime.hour && Plane.ExpectedTime.min > currentTime.min) {
					cout << "FLIGHT NO     DESTINATION    TIME\n";
					cout << Plane.FlightNO << setw(20) << setfill(' ') << Plane.Destination << setw(10) << setfill(' ') << Plane.ExpectedTime.hour << ":" << Plane.ExpectedTime.min;
				}
				else if (Plane.ExpectedTime.hour == currentTime.hour && Plane.ExpectedTime.min == currentTime.min && Plane.ExpectedTime.sec > currentTime.sec) {
					cout << "FLIGHT NO     DESTINATION    TIME\n";
					cout << Plane.FlightNO << setw(20) << setfill(' ') << Plane.Destination << setw(10) << setfill(' ') << Plane.ExpectedTime.hour << ":" << Plane.ExpectedTime.min;
				}
			}
		}
	}
	cout << "\n";
}

void SortByID(const int size, List<FlightRec> &flights, FlightRec &Plane) {
	int tempsize = size - 1;
	bool exchangeMade;
	FlightRec temp;
	int i;
	int k;
	do {
		exchangeMade = false;
		for (i = 0; i < size; i++) {
			if (flights.retrieve(i, Plane) == success) {
				CopyValues(temp, Plane);
				if (flights.retrieve(i + 1, Plane) == success) {
					k = 0;

					while (temp.FlightNO[k] == Plane.FlightNO[k])
						k++;
					if (temp.FlightNO[k] > Plane.FlightNO[k]) {
						flights.replace(i, Plane);
						flights.replace(i + 1, temp);
						exchangeMade = true;
					}
				}
			}
		}
		tempsize -= 1;
	} while (exchangeMade && (size > 0));
}

void SortByTime(const int size, List<FlightRec> &flights, FlightRec &Plane) {
	int tempsize = size - 1;
	bool exchangeMade;
	FlightRec temp;
	int i;

	do {
		exchangeMade = false;
		for (i = 0; i < size; i++) {
			if (flights.retrieve(i, Plane) == success) {
				CopyValues(temp, Plane);
				if (flights.retrieve(i + 1, Plane) == success) {
					if (temp.Time.hour > Plane.Time.hour) {
						flights.replace(i, Plane);
						flights.replace(i + 1, temp);
						exchangeMade = true;
					}
					if ((temp.Time.hour == Plane.Time.hour) && (temp.Time.min > Plane.Time.min)) {
						flights.replace(i, Plane);
						flights.replace(i + 1, temp);
						exchangeMade = true;
					}
					if ((temp.Time.hour == Plane.Time.hour) && (temp.Time.min == Plane.Time.min) && (temp.Time.sec > Plane.Time.sec)) {
						flights.replace(i, Plane);
						flights.replace(i + 1, temp);
						exchangeMade = true;
					}
				}
			}
		}
		tempsize -= 1;
	} while (exchangeMade && (size > 0));
}

void ExtractInteger(string str, int &hour, int &min, int &sec) {
	char c;
	stringstream(str) >> hour >> c >> min >> c >> sec;
}

void WriteToFile(const int size, List<FlightRec> flights, FlightRec Plane) {
	fstream file;
	file.open("Airport.txt", ios::out);
	for (int i = 0; i < size; i++) {
		flights.retrieve(i, Plane);
		file << Plane;
	}
	file.close();
}

void ReadFromFile(int &size, List < FlightRec> &flights, FlightRec &Plane) {
	ifstream file;
	string FlightNO;
	string Destination;
	string Ftype;
	string Delay;
	string Time;
	string ExpectedTime;
	string temp;
	int hour;
	int min;
	int sec;
	int i;

	file.open("Airport.txt");

	while (file.good()) {
		getline(file, FlightNO, ';');
		for (i = 0; FlightNO[i] != '\0'; i++)
			Plane.FlightNO[i] = FlightNO[i];
		Plane.FlightNO[i] = '\0';

		getline(file, Destination, ';');
		for (i = 0; Destination[i] != '\0'; i++)
			Plane.Destination[i] = Destination[i];
		Plane.Destination[i] = '\0';

		getline(file, Ftype, ';');
		if (Ftype == "Arrival") Plane.Ftype = Arrival;
		if (Ftype == "Departure") Plane.Ftype = Departure;

		getline(file, Delay, ';');
		if (Delay == "On Time") {
			Plane.Delay = false;
			getline(file, Time, ';');
			ExtractInteger(Time, hour, min, sec);
			Plane.Time.hour = hour;
			Plane.Time.min = min;
			Plane.Time.sec = sec;
		}
		else if (Delay == "Delayed") {
			Plane.Delay = true;
			getline(file, ExpectedTime, ';');
			ExtractInteger(ExpectedTime, hour, min, sec);
			Plane.ExpectedTime.hour = hour;
			Plane.ExpectedTime.min = min;
			Plane.ExpectedTime.sec = sec;
		}
		flights.add(size, Plane);
		size++;
	}
	file.close();
}






