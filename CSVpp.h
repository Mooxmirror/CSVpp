#pragma once
#include "CSV.h"
#include "Row.h"
#include "Table.h"

/**\mainpage CSV++ project documentation

\section welcome Welcome to CSV++!

CSV++ provides a simple interface to access CSV files in C++!
Using a object-oriented approach it can parse files at a pretty good speed but it's still in development, there are a lot of features on the way for this projects.
Just look us up on the <a href="https://github.com/Mooxmirror/CSVpp">GitHub repository page</a>!

\section example Example code to get started

\code{.cpp}
#include <iostream>
#include "CSVpp.h" // Include this file to get started

int main() {
	csv::Table my_table("example.csv"); // Creates a new table and loads the file "example.csv"
	std::cout << my_table.to_csv_string() << std::endl; // Prints the table data to the console

	return 0;
}
\endcode
*/