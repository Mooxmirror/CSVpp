#include "Row.h"

/**
Creates a new row with a specified header and specified cell content.
@param[in]	_header The header section defining cell names
@param[in]	_cells The cell data of this row
*/
csv::Row::Row(vector<string>& _header, vector<string>& _cells)
{
	this->m_header = _header;
	if (_cells.size() != _header.size())
	{
		throw Error::NOT_COMPATIBLE;
	}
	this->m_cells = _cells;
}
/**
Searches for the cell index in the header array.
@param[in]	_name Name of the header cell
@return Index of the header name
*/
int csv::Row::find_cell(string& _name)
{
	for (unsigned int i = 0; i < m_header.size(); i++)
	{
		if (m_header[i] == _name)
		{
			return i;
		}
	}
	return -1;
}
/**
Sets the identified cell to the value.
@param[in]	_name Name of the header for indexing
@param[in]	_value Value to be assigned
*/
void csv::Row::set_cell(string& _name, string& _value)
{
	int cell_index = find_cell(_name);
	if (cell_index != -1)
	{
		m_cells[cell_index] = _value;
	}
	else
	{
		throw Error::UNDEFINED_CELL;
	}
}
/**
Sets the cell at index to the value.
@param[in]	_index Index of the cell
@param[in]	_value Value to be assigned
*/
void csv::Row::set_cell(unsigned _index, string& _value)
{
	if (_index < length())
	{
		m_cells[_index] = _value;
	}
	else
	{
		throw Error::OUT_OF_RANGE;
	}
}
/**
Sets the identified cell to the value.
@param[in]	_name Name of the header for indexing
@param[in]	_value Value to be assigned
*/
void csv::Row::set_cell(char _name[], char _value[])
{
	set_cell(string(_name), string(_value));
}
/**
Sets the cell at index to the value.
@param[in]	_index Index of the cell
@param[in]	_value Value to be assigned
*/
void csv::Row::set_cell(unsigned _index, char _value[])
{
	set_cell(_index, string(_value));
}
/**
Looks up the cell value.
@param[in]	_name Name of the header for indexing
@return Value of the cell
*/
std::string csv::Row::get_cell(string& _name)
{
	int cell_index = find_cell(_name);
	if (cell_index != -1)
	{
		return m_cells[cell_index];
	}
	throw Error::UNDEFINED_CELL;
}
/**
Looks up the cell value.
@param[in]	_name Name of the header for indexing
@return Value of the cell
*/
std::string csv::Row::get_cell(char _name[])
{
	return get_cell(string(_name));
}
/**
Looks up the cell value.
@param[in]	_index Index of the cell in the row
@return Value of the cell
*/
std::string csv::Row::get_cell(unsigned _index)
{
	if (_index < m_cells.size())
	{
		return m_cells[_index];
	}
	throw Error::OUT_OF_RANGE;
}
/**
Parses this row to a valid CSV line.
@return CSV string containing row data
*/
std::string csv::Row::to_csv_string()
{
	return to_csv_string(*this);
}
/**
Parses the specified row to a valid CSV line.
@return CSV string containing row data
*/
std::string csv::Row::to_csv_string(Row& _row)
{
	string csv_string;
	for (unsigned i = 0; i < _row.length(); i++)
	{
		csv_string += _row.get_cell(i) + ";";
	}
	return csv_string;
}
/**
Calculates the count of cells.
@return Row size
*/
unsigned csv::Row::length()
{
	return m_cells.size();
}