# TableEditor
 
 This code implements a TableEditor class which represents a csv table where you can select, delete, insert or edit rows, columns or cells. 

| Syntax      | Description |
| ----------- | ----------- |
TableEditor(); | class constructor 
TableEditor(); | class destructor 
importTable(string table); | import table as a csv string or return row position of an error
string exportTable(); | generates a cvs string from table
void deselect(); | deselect content
void selectRow(int row_position); | selects row at row_position
void selectColumn(string col_name); | selects column with name col_name
void selectCell(int row_position, string col_name); | selects cell with position (row_position,col_name)
void insertRow(); | insert row in front of the selected row or at the end if row isn't selected
void insertColumn(string col_name, Type type); | insert column in front of the selected column or at the end if row isn't selected
void deleteContent(); | delete selected content
void editCellValue(); | set cell value using std::cin
void add(double value); | add value to selected content
void mul(double value); | multiply selected content with value
void sortByValue(string col_name, bool asc); | sort column col_ name ascending or descending
int findFirstOf(string value, string col_name); | find first element with value inside a column
int findLastOf(string value, string col_name); | find last element with value inside a column
int countValues(string value, string col_name); | count number of elements with value inside a column
int countDistinctValues(string col_name); | count number of distinct elements inside a coulmn
