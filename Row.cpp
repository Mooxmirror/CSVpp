#include "Row.h"

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
	for (unsigned i = 0; i < row.size(); i++) {
		result += row.getCell(i) + ";";
	}
	return result;
}
unsigned csv::Row::size() {
	return cells.size();
}