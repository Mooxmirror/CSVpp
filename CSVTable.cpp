#include "CSVTable.h"

#pragma region Row declaration
csv::Row::Row(vector<string>& header, vector<string>& cells) {
	this->header = header;
	if (cells.size() != header.size())
		throw Error::NOT_COMPATIBLE;
	this->cells = cells;
}
int csv::Row::findCell(string& name) {
	for (unsigned int i = 0; i < header.size(); i++) {
		if (header[i] == name)
			return i;
	}
	return -1;
}
void csv::Row::setCell(string& name, string& value) {
	int cellIndex = findCell(name);
	if (cellIndex != -1)
		cells[cellIndex] = value;
	else
		throw Error::UNDEFINED_CELL;
}
void csv::Row::setCell(unsigned i, string& value) {
	if (i < size())
		cells[i] = value;
	else
		throw Error::OUT_OF_RANGE;
}
void csv::Row::setCell(char name[], char value[]) {
	setCell(string(name), string(value));
}
void csv::Row::setCell(unsigned i, char value[]) {
	setCell(i, string(value));
}
std::string csv::Row::getCell(string& name) {
	int cellIndex = findCell(name);
	if (cellIndex != -1)
		return cells[cellIndex];

	throw Error::UNDEFINED_CELL;
}
std::string csv::Row::getCell(unsigned i) {
	if (i < cells.size())
		return cells[i];
	throw Error::OUT_OF_RANGE;
}
std::string csv::Row::toCSV() {
	return toCSV(*this);
}
std::string csv::Row::toCSV(Row& row) {
	string result;

	for (int i = 0; i < row.size(); i++) {
		result += row.getCell(i) + ";";
	}

	return result;
}
int csv::Row::size() {
	return cells.size();
}
#pragma endregion
#pragma region Table declaration
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
	//TODO Implement file loading
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
#pragma endregion