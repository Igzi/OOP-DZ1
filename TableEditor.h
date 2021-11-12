#ifndef TABLEEDITOR_H
#define TABLEEDITOR_H

#include "Cell.h"
#include "Vector.h"

class TableEditor {
public:
	TableEditor();
	~TableEditor();

	int importTable(string table);
	string exportTable();

	void deselect();
	void selectRow(int row_position);
	void selectColumn(string col_name);
	void selectCell(int row_position, string col_name);

	void insertRow();
	void insertColumn(string col_name, Type type);

	void deleteContent();
	void editCellValue();

	void add(double value);
	void mul(double value);
	void sortByValue(string col_name, bool asc);

	int findFirstOf(string value, string col_name);
	int findLastOf(string value, string col_name);

	int countValues(string value, string col_name);
	int countDistinctValues(string col_name);

private:
	Vector<Vector<Cell*>> table;
	int selectedRow, selectedColumn;

	int readRow(string &rows, int p, int r, char sep);
	int readCell(string &cells, int p, int r, int c, char sep);
	int findColumn(string col_name);
};
#endif
