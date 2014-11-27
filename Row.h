#pragma once
#include "CSV.h"
namespace csv {
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
		unsigned size();
	};
}