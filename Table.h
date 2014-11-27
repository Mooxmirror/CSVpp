#pragma once
#include "CSV.h"
#include "Row.h"
namespace csv {
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