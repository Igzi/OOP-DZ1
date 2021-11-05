#ifndef CELL_H
#define CELL_H

#include <string>

using namespace std;

enum Type {
	INT,
	DECIMAL,
	TEXT,
	NOTDEFINED,
};

class Cell {
public:
	Cell();
	Cell(string data);

	string getValue();
	void deleteCell();

	virtual char getType();
	virtual bool checkValue();
	virtual void editCell(string data);
	virtual void add(double val);
	virtual void mul(double val);
	virtual bool cmp(string value);
protected:
	string value;
};

class FirstRowCell : public Cell {
public:
	FirstRowCell(string data);
	FirstRowCell(string col_name, Type type);

	virtual char getType() override;
	virtual bool checkValue() override;
};

class IntCell : public Cell {
public:
	IntCell(string data);

	virtual char getType() override;
	virtual bool checkValue() override;
	virtual void editCell(string data) override;
	virtual void add(double val) override;
	virtual void mul(double val) override;
	virtual bool cmp(string value) override;
private:
	int intValue;
};

class DecimalCell : public Cell {
public:
	DecimalCell(string data);

	virtual char getType() override;
	virtual bool checkValue() override;
	virtual void editCell(string data) override;
	virtual void add(double val) override;
	virtual void mul(double val) override;
	virtual bool cmp(string value) override;
private:
	double decimalValue;
	void roundValue(double &value);
};

class TextCell : public Cell {
public:
	TextCell(string data);

	virtual char getType() override;
	virtual bool cmp(string value) override;
};
#endif
