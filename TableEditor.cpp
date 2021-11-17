#include "TableEditor.h"
#include <iostream>

TableEditor::TableEditor()
{
	selectedRow = selectedColumn = -1;
}

TableEditor::~TableEditor()
{
	deleteTable();
}

int TableEditor::importTable(string table)
{
	deleteTable();
	int r = 0, p = 0;
	while (p < table.size()) {
		p = readRow(table, p, r, ',');
		if (p == -1) {
			deleteTable();
			return r - 1;
		}
		r++;
	}
	return -2;
}

string TableEditor::exportTable()
{
	string res = "";
	int n, m;
	n = table.getSize();
	m = table[0].getSize();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			res.append(table[i][j]->getValue());
			if (j != m - 1) res += ',';
		}
		res += '\n';
	}
	return res;
}

void TableEditor::deselect()
{
	selectedRow = selectedColumn = -1;
}

void TableEditor::selectRow(int row_position)
{
	if (row_position < 0 || (row_position + 1) >= table.getSize()) return;
	selectedColumn = -1;
	selectedRow = row_position + 1;
}

void TableEditor::selectColumn(string col_name)
{
	int c = findColumn(col_name);
	if (c == -1) return;
	selectedColumn = c;
	selectedRow = -1;
}

void TableEditor::selectCell(int row_position, string col_name)
{
	if (row_position < 0 || (row_position + 1) >= table.getSize()) return;
	int c = findColumn(col_name);
	if (c == -1) return;
	selectedColumn = c;
	selectedRow = row_position + 1;
}

void TableEditor::insertRow()
{
	string row;
	getline(cin, row);
	int r = selectedRow;
	if (r == -1) r = table.getSize();
	Vector<Cell*> v;
	table.insert(r, v);
	readRow(row, 0, r, ',');
}

void TableEditor::insertColumn(string col_name, Type type)
{
	int c = selectedColumn;
	if (c == -1) c = table[0].getSize();
	Cell* cell = new FirstRowCell(col_name, type);
	table[0].insert(c, cell);

	for (int i = 1; i < table.getSize(); i++) {
		switch (type) {
		case INT:
			cell = new IntCell("0");
			break;
		case DECIMAL:
			cell = new DecimalCell("0");
			break;
		case TEXT:
			cell = new TextCell("");
			break;
		}
		table[i].insert(c, cell);
	}
}

void TableEditor::deleteContent()
{
	if (selectedRow != -1 && selectedColumn != -1) {
		table[selectedRow][selectedColumn]->deleteCell();
		selectedRow = -1;
		selectedColumn = -1;
		return;
	}
	if (selectedRow != -1) {
		for (int i = 0; i < table[selectedRow].getSize(); i++) {
			delete table[selectedRow][i];
			table[selectedRow][i] = nullptr;
		}
		table.remove(selectedRow);
		selectedRow = -1;
	}
	if (selectedColumn != -1) {
		for (int i = 0; i < table.getSize(); i++) {
			delete table[i][selectedColumn];
			table[i][selectedColumn] = nullptr;
			table[i].remove(selectedColumn);
		}
		selectedColumn = -1;
	}
}

void TableEditor::editCellValue()
{
	if (selectedRow == -1 || selectedColumn == -1) return;
	string value;
	cin >> value;
	table[selectedRow][selectedColumn]->editCell(value);
}

void TableEditor::add(double value)
{
	if (selectedRow != -1 && selectedColumn != -1) {
		table[selectedRow][selectedColumn]->add(value);
		return;
	}
	if (selectedRow != -1) {
		for (int i = 0; i < table[selectedRow].getSize(); i++) {
			table[selectedRow][i]->add(value);
		}
	}
	if (selectedColumn != -1) {
		for (int i = 0; i < table.getSize(); i++) {
			table[i][selectedColumn]->add(value);
		}
	}
}

void TableEditor::mul(double value)
{
	if (selectedRow != -1 && selectedColumn != -1) {
		table[selectedRow][selectedColumn]->mul(value);
		return;
	}
	if (selectedRow != -1) {
		for (int i = 0; i < table[selectedRow].getSize(); i++) {
			table[selectedRow][i]->mul(value);
		}
	}
	if (selectedColumn != -1) {
		for (int i = 0; i < table.getSize(); i++) {
			table[i][selectedColumn]->mul(value);
		}
	}
}

void TableEditor::sortByValue(string col_name, bool asc)
{
	int col = findColumn(col_name);
	if (col == -1) return;

	for (int i = 1; i < table.getSize(); i++) {
		for (int j = i + 1; j < table.getSize(); j++) {
			if (table[j][col]->cmp(table[i][col]->getValue()) && asc) {
				swap(table[i], table[j]);
			}
			if (table[i][col]->cmp(table[j][col]->getValue()) && !asc) {
				swap(table[i], table[j]);
			}
		}
	}
}

int TableEditor::findFirstOf(string value, string col_name)
{
	int col = findColumn(col_name);
	if (col == -1) return -2;

	int res = -2;
	for (int i = table.getSize() - 1; i >= 0; i--) {
		if (table[i][col]->getValue() == value) {
			res = i;
		}
	}
	return res - 1;
}

int TableEditor::findLastOf(string value, string col_name)
{
	int col = findColumn(col_name);
	if (col == -1) return -2;

	int res = -2;
	for (int i = 0; i < table.getSize(); i++) {
		if (table[i][col]->getValue() == value) {
			res = i;
		}
	}
	return res - 1;
}

int TableEditor::countValues(string value, string col_name)
{
	int col = findColumn(col_name);
	if (col == -1) return -2;

	int res = 0;
	for (int i = 0; i < table.getSize(); i++) {
		if (table[i][col]->getValue() == value) {
			res++;
		}
	}
	return res;
}

int TableEditor::countDistinctValues(string col_name)
{
	int col = findColumn(col_name);
	if (col == -1) return -2;

	int res = 0;
	for (int i = 1; i < table.getSize(); i++) {
		if (findLastOf(table[i][col]->getValue(), col_name) == (i - 1)) res ++;
	}
	return res;
}

void TableEditor::deleteTable() {
	for (int i = 0; i < table.getSize(); i++) {
		for (int j = 0; j < table[i].getSize(); j++) {
			delete table[i][j];
			table[i][j] = nullptr;
		}
	}
}

int TableEditor::readRow(string& rows, int p, int r, char sep)
{
	int c = 0;
	if (r >= table.getSize()) {
		Vector<Cell*> v;
		table.push(v);
	}
	while (rows[p] != '\n' && p < rows.size()) {
		p = readCell(rows, p, r, c, sep);
		if (p == -1) return -1;
		c++;
	}
	if (table[0].getSize() != table[r].getSize()) return -1;
	if (rows[p] == '\n') p++;
	return p;
}

int TableEditor::readCell(string& cells, int p, int r, int c, char sep)
{
	string value = "";
	if (cells[p] == '"') {
		value += cells[p];
		p++;
		while (cells[p] != '"') {
			if (cells[p] == '\n' || p == cells.size()) return -1;
			value += cells[p];
			p++;
		}
		value += cells[p];
		p++;
		if (cells[p] != sep && cells[p] != '\n' && p < cells.size()) return -1;
	}
	else {
		while (cells[p] != sep && cells[p] != '\n' && p < cells.size()) {
			value += cells[p];
			p++;
		}
	}

	if (r == 0) {
		FirstRowCell* cell = new FirstRowCell(value);
		if (!cell->checkValue()) {
			delete cell;
			return -1;
		}
		table[0].push((Cell*)cell);
	}
	else {
		if (c >= table[0].getSize()) return -1;
		Cell* cell;
		switch (table[0][c]->getType()) {
		case 'i':
			cell = new IntCell(value);
			break;
		case 'd':
			cell = new DecimalCell(value);
			break;
		case 't':
			cell = new TextCell(value);
			break;
		default:
			return -1;
		}
		if (!cell->checkValue()) {
			delete cell;
			return -1;
		}
		table[r].push(cell);
	}
	if (cells[p] == sep) p++;
	return p;
}

int TableEditor::findColumn(string col_name)
{
	for (int i = 0; i < table[0].getSize(); i++) {
		if ((table[0][i]->getValue()).compare(2, col_name.size(), col_name) == 0) {
			return i;
		}
	}
	return -1;
}