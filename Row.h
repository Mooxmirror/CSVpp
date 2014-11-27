#pragma once
#include "CSV.h"

namespace csv
{
	using std::string;
	using std::vector;

	class Row
	{
	private:
		vector<string>		m_header;
		vector<string>		m_cells;
		int					find_cell(string& _name);
	public:
		Row(vector<string>&, vector<string>&);
		Row(vector<string>& _header) : Row(_header, vector<string>(_header.size())) {};

		void			set_cell(string&, string&);
		void			set_cell(unsigned, string&);
		void			set_cell(char[], char[]);
		void			set_cell(unsigned, char[]);
		string			get_cell(string&);
		string			get_cell(char[]);
		string			get_cell(unsigned);
		string			to_csv_string();
		unsigned		length();

		static string	to_csv_string(Row&);
	};
}