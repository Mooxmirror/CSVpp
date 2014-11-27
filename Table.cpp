#include "Table.h"

csv::Table::Table() {
	// TODO Add useful constructor
}
csv::Table::Table(vector<string>& header) {
	this->header = header;
}
csv::Table::~Table() {
	rows.clear();
	header.clear();
}
csv::Table::Table(string& fileName) {
	loadFromFile(fileName);
}
csv::Row csv::Table::toRow(string& line) {
	vector<string> cellValues = splitLine(line);
	return Row(header, cellValues);
}
std::vector<std::string> csv::Table::splitLine(string& line, char seperator) {
	if (line.at(line.size() - 1) != seperator)
		line += seperator;
	vector<string> parts;
	string activePart;
	for (unsigned i = 0; i < line.length(); i++) {
		if (line[i] == seperator) {
			if (i > 0) {
				if (!(line[i - 1] == '\\')) {
					parts.push_back(activePart);
					activePart.clear();
				}
			}
		}
		else
			activePart += line[i];
	}
	return parts;
}
csv::Row csv::Table::getRow(int i) {
	if (i > -1 && i < height())
		return rows[i];
	else
		throw Error::OUT_OF_RANGE;
}
void csv::Table::setRow(int i, Row& row) {
	if (i > -1 && i < height()) {
		if (row.size() == width())
			rows[i] = row;
		else
			throw Error::NOT_COMPATIBLE;
	}
	else
		throw Error::OUT_OF_RANGE;
}
int csv::Table::addRow(Row& row) {
	int size = rows.size();
	if (row.size() == width())
		rows.push_back(row);
	else
		throw Error::NOT_COMPATIBLE;
	return size;
}
void csv::Table::removeRow(int i) {
	if (i > -1 && i < height())
		rows.erase(rows.begin() + i);
	else
		throw Error::OUT_OF_RANGE;
}
int csv::Table::width() {
	return header.size();
}
int csv::Table::height() {
	return rows.size();
}
bool csv::Table::loadFromFile(string& fileName) {
	ifstream fileStream(fileName);

	if (fileStream.is_open()) {
		// Do file handling here
		string line;
		bool firstLine = true;
		
		while (std::getline(fileStream, line)) {
			if (line != "") {
				if (firstLine) {
					header = splitLine(line);
					firstLine = false;
				}
				else {
					Row row = toRow(line);
					addRow(row);
				}
			}
		}

		fileStream.close();
	}
	else
		throw Error::FILE_NOT_FOUND;

	return false;
}
bool csv::Table::saveToFile(string& fileName) {
	//TODO Implement file saving
	return false;
}
std::string csv::Table::toCSV() {
	string result;
	for (string& heading : header) {
		result += heading + ";";
	}
	result += "\n";
	for (Row& row : rows) {
		result += row.toCSV() + "\n";
	}
	return result;
}