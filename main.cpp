#include <iostream>
#include "CSVpp.h"

using namespace std;
int main() {
	csv::Table myTable(string("schoolarships.csv"));
	cout << myTable.toCSV();
}