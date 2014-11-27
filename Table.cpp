#include "Table.h"

/**
Initializes a new table containing nothing.
*/
csv::Table::Table()
{
	// TODO Add useful constructor
}
/**
Initializes a new table with a new header.
@param[in]	_header Header to be assigned to the table
*/
csv::Table::Table(vector<string>& _header)
{
	this->m_header = _header;
}
/**
Clears up all table values. Not really necessary.
*/
csv::Table::~Table()
{
	m_rows.clear();
	m_header.clear();
}
/**
Initializes a new table and loads the data from the file.
@param[in]	_file Target file
*/
csv::Table::Table(string& _file)
{
	load_file(_file);
}
/**
Parses a string to a new row fitting to the table.
@param[in]	_line Line to parse
@return The parsed row
*/
csv::Row csv::Table::parse_to_row(string& _line)
{
	vector<string> cell_values = split_line(_line);
	return Row(m_header, cell_values);
}
/**
Splits a line by using a seperator character. By using \<seperator> you can use the seperator in fields.
@param[in]	_line String data to split
@param[in]	_seperator Seperator character. Standard is ';'
@return Returns the splitted strings as a vector
*/
std::vector<std::string> csv::Table::split_line(string& _line, char _seperator)
{
	if (_line.at(_line.size() - 1) != _seperator)
		_line += _seperator;
	vector<string> line_parts;
	string active_part;
	for (unsigned i = 0; i < _line.length(); i++)
	{
		if (_line[i] == _seperator)
		{
			if (i > 0)
			{
				if (!(_line[i - 1] == '\\'))
				{
					line_parts.push_back(active_part);
					active_part.clear();
				}
				else
				{
					active_part += _line[i];
				}
			}
		}
		else
		{
			active_part += _line[i];
		}
	}
	return line_parts;
}
/**
Finds the row at the specified index.
@param[in]	_index Index of the row
@return The row at the index
*/
csv::Row csv::Table::get_row(unsigned _index)
{
	if (_index < row_count())
	{
		return m_rows[_index];
	}
	else
	{
		throw Error::OUT_OF_RANGE;
	}
}
/**
Assigns the row at the specified index to the argument row.
@param[in]	_index Index of the target row
@param[in]	_row Data that will be assigned to the specified row
*/
void csv::Table::set_row(unsigned _index, Row& _row)
{
	if (_index < row_count())
	{
		if (_row.length() == col_count())
		{
			m_rows[_index] = _row;
		}
		else
		{
			throw Error::NOT_COMPATIBLE;
		}
	}
	else
	{
		throw Error::OUT_OF_RANGE;
	}
}
/**
Appends a new row to the table.
@param[in]	_row The row that will be appended
@return Index of the appended row
*/
unsigned csv::Table::add_row(Row& _row)
{
	unsigned table_size = row_count();
	if (_row.length() == col_count())
	{
		m_rows.push_back(_row);
	}
	else
	{
		throw Error::NOT_COMPATIBLE;
	}
	return table_size;
}
/**
Erases the row at the index from the table.
@param[in]	_index Index of the row
*/
void csv::Table::rem_row(unsigned _index)
{
	if (_index > -1 && _index < row_count())
		m_rows.erase(m_rows.begin() + _index);
	else
		throw Error::OUT_OF_RANGE;
}
/**
Amount of cols in the table.
@return Count of cols
*/
unsigned csv::Table::col_count()
{
	return m_header.size();
}
/**
Amount of rows in the table.
@return Count of rows
*/
unsigned csv::Table::row_count()
{
	return m_rows.size();
}
/**
Loads the table data from the specified file.
@param[in]	_file Path string
@return Success state
*/
bool csv::Table::load_file(string& _file)
{
	using std::ifstream;

	ifstream input_file(_file);
	if (input_file.is_open())
	{
		string current_line;
		bool is_first = true;
		while (std::getline(input_file, current_line))
		{
			if (current_line != "")
			{
				if (is_first)
				{
					m_header = split_line(current_line);
					is_first = false;
				}
				else
				{
					Row row = parse_to_row(current_line);
					add_row(row);
				}
			}
		}
		input_file.close();
	}
	else
	{
		return false;
	}
	return true;
}
/**
Saves the table data in a CSV file that will be overwritten or created.
@param[in]	_file Path string
@return Success state
*/
bool csv::Table::save_file(string& _file)
{
	using std::ofstream;

	ofstream output_file;
	output_file.open(_file);
	if (output_file.is_open())
	{
		output_file << to_csv_string();
		output_file.close();
	}
	else
	{
		return false;
	}
	return true;
}
/**
Loads the table data from the specified file.
@param[in]	_file Path string
@return Success state
*/
bool csv::Table::load_file(char _file[])
{
	return load_file(string(_file));
}
/**
Saves the table data in a CSV file that will be overwritten or created.
@param[in]	_file Path string
@return Success state
*/
bool csv::Table::save_file(char _file[])
{
	return save_file(string(_file));
}
/**
Parses the complete table to a valid CSV string including header.
@return CSV string (with line feeds '\n')
*/
std::string csv::Table::to_csv_string()
{
	string csv_string;
	for (string& col_heading : m_header)
	{
		csv_string += col_heading + ";";
	}
	csv_string += "\n";
	for (Row& row_data : m_rows)
	{
		csv_string += row_data.to_csv_string() + "\n";
	}
	return csv_string;
}