#include <iostream>
#include "CSVpp.h"

using namespace std;
int main() {
	csv::Table myTable(string("schoolarships.csv"));
	myTable.saveToFile(string("schools1.csv"));
}