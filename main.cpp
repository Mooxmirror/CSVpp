#include <iostream>
#include "CSVpp.h"

using namespace std;
int main() {
	csv::Table myTable(string("schoolarships.csv"));
	myTable.save_file(string("schools1.csv"));
}