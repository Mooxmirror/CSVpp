#include <iostream>
#include "CSVTable.h"

using namespace std;
int main() {
	vector<string> header(3);
	header[0] = "First name";
	header[1] = "Last name";
	header[2] = "Age";

	string myLine = "Peter;Parker;21";
	csv::Table myTable(header);
	csv::Row myRow = myTable.toRow(myLine);
	myTable.addRow(myRow);
	cout << myTable.toCSV();
}