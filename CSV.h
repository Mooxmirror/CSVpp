#pragma once
#include <vector>
#include <deque>
#include <map>
#include <string>
#include <fstream>

namespace csv {

	enum class Error : int {
		UNDEFINED_CELL = 0, // cell name not found in header
		OUT_OF_RANGE = 1, // target  index exceeds arraay
		NOT_COMPATIBLE = 2, // row length is different
		FILE_NOT_FOUND = 3,// Failed to load fileS
		FILE_SAVE_FAILED
	};

	class Row;
	class Table;
	class SQLQuery;
	class SQLResult;
}