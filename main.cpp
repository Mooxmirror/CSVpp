#include <iostream>
#include "CSVTable.h"

using namespace std;
int main() {
	vector<string> header(3);
	header[0] = "First name";
	header[1] = "Last name";
	header[2] = "Age";

	csv::Table myTable(header);
	csv::Row myRow(header);
	myRow.setCell("First name", "Peter");
	myRow.setCell(1, "Parker");
	myRow.setCell(2, "21");
	myTable.addRow(myRow);
	cout << myTable.toCSV();
}