#include <vector>
#include <deque>
#include <map>
#include <string>
#ifndef CSVTABLE_H
#define CSVTABLE_H

namespace csv {
	using std::string;
	using std::vector;
	using std::deque;

	enum class Error : int {
		UNDEFINED_CELL = 0, // cell name not found in header
		OUT_OF_RANGE = 1, // target  index exceeds arraay
		NOT_COMPATIBLE = 2 // row length is different
	};

	class Row {
		vector<string> header;
		vector<string> cells;
		int findCell(string& name);
	public:
		Row(vector<string>& header, vector<string>& cells);
		Row(vector<string>& header) : Row(header, vector<string>(header.size())) {};
		void setCell(string& name, string& value);
		void setCell(unsigned i, string& value);
		void setCell(char name[], char value[]);
		void setCell(unsigned i, char value[]);
		string getCell(string& name);
		string getCell(unsigned i);
		string toCSV();
		static string toCSV(Row& row);
		int size();
	};

	class Table {
		vector<string> header;
		deque<Row> rows;
	public:
		Table();
		Table(vector<string>& header);
		Table(string& fileName);
		~Table();
		Row getRow(int i);
		void setRow(int i, Row& row);
		int addRow(Row& row);
		void removeRow(int i);
		int width();
		int height();
		bool loadFromFile(string& fileName);
		bool saveToFile(string& fileName);
		static vector<string> splitLine(string& line, char seperator = ';');
		Row toRow(string& line);
		string toCSV();
	};
}

#endif