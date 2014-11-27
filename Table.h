#pragma once
#include "CSV.h"
#include "Row.h"
namespace csv {
	using std::string;
	using std::vector;
	using std::deque;

	class Table {
	private:
		vector<string>	m_header;
		deque<Row>		m_rows;
	public:
		Table();
		Table(vector<string>&);
		Table(string&);
		Table(char _file[]) : Table(string(_file)) {};
		~Table();
		Row			get_row(unsigned);
		void		set_row(unsigned, Row&);
		unsigned	add_row(Row&);
		void		rem_row(unsigned);
		unsigned	col_count();
		unsigned	row_count();
		bool		load_file(string&);
		bool		load_file(char[]);
		bool		save_file(string&);
		bool		save_file(char[]);
		Row			parse_to_row(string&);
		string		to_csv_string();

		static vector<string> split_line(string&, char = ';');
	};
}