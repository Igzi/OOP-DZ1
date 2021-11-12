#include "Cell.h"

const double eps = 0.0001;

Cell::Cell()
{
	value = "";
}

Cell::Cell(string data)
{
	value = data;
}

string Cell::getValue()
{
	return value;
}

void Cell::deleteCell()
{
	value = "";
}

char Cell::getType()
{
	return 0;
}

bool Cell::checkValue()
{
	return true;
}

void Cell::editCell(string data)
{
	value = data;
}

void Cell::add(double val) {}

void Cell::mul(double val) {}

bool Cell::cmp(string value)
{
	return false;
}

FirstRowCell::FirstRowCell(string data):Cell(data) {}

FirstRowCell::FirstRowCell(string col_name, Type type)
{
	switch (type){
	case INT:
		value = "i:";
		break;
	case DECIMAL:
		value = "d:";
		break;
	case TEXT:
		value = "t:";
		break;
	}
	value += col_name;
}

char FirstRowCell::getType()
{
	return value[0];
}

bool FirstRowCell::checkValue()
{
	if (value.size() < 2 || value[1] != ':') return false;
	if (value[0] != 'i' && value[0] != 'd' && value[0] != 't') return false;
	return true;
}

IntCell::IntCell(string data):Cell(data)
{
	if (value != "") intValue = stoi(data);
	else intValue = -1;
}

char IntCell::getType()
{
	return 'i';
}

bool IntCell::checkValue()
{
	for (int i = 0; i < value.size(); i++) {
		if (i == 0 && value[i] == '-') continue;
		if (value[i] < '0' && value[i]>'9') return false;
	}
	return true;
}

void IntCell::editCell(string data)
{
	value = data;
	if (value != "") intValue = stoi(data);
	else intValue = -1;
}

void IntCell::add(double val)
{
	if (value != "") {
		//Zaokruzivanje na najblizi ceo broj
		intValue += (int)round(val);
		value = to_string(intValue);
	}
}

void IntCell::mul(double val)
{
	if (value != "") {
		//Zaokruzivanje na najblizi ceo broj
		intValue *= (int)round(val);
		value = to_string(intValue);
	}
}

bool IntCell::cmp(string value)
{
	return (intValue < stoi(value));
}

DecimalCell::DecimalCell(string data):Cell(data)
{
	if (data != "") decimalValue = stof(data);
	else decimalValue = -1;
}

char DecimalCell::getType()
{
	return 'd';
}

bool DecimalCell::checkValue()
{
	for (int i = 0; i < value.size(); i++) {
		if (i == 0 && value[i] == '-') continue;
		if (i == value.size() - 2 && value[i] == '.') continue;
		if (value[i] < '0' && value[i]>'9') return false;
	}
	return true;
}

void DecimalCell::editCell(string data)
{
	value = data;
	if (data != "") decimalValue = stof(data);
	else decimalValue = -1;
}

void DecimalCell::add(double val)
{
	if (value != "") {
		decimalValue += val;
		value = roundValue(decimalValue);
	}
}

void DecimalCell::mul(double val)
{
	if (value != "") {
		decimalValue *= val;
		value = roundValue(decimalValue);
	}
}

bool DecimalCell::cmp(string value)
{
	double cmpValue = stof(value);
	roundValue(cmpValue);
	return (round(10*decimalValue) + eps  < round(10 * cmpValue));
}

string DecimalCell::roundValue(double &value)
{
	value *= 10;
	if (abs(value - (int)value - 0.5) < eps) {
		if ((int)value % 2) value += 0.5;
		else value -= 0.5;
	}
	int intValue = round(value);
	value = (double)intValue / 10;

	string res = "";
	res += '0' + intValue % 10;
	intValue /= 10;
	res += '.';
	while (intValue > 0 && res.size() < 3) {
		res += '0' + intValue % 10;
		intValue /= 10;
	}
	reverse(res.begin(), res.end());
	return res;
}

TextCell::TextCell(string data):Cell(data){}

char TextCell::getType()
{
	return 't';
}

bool TextCell::cmp(string value)
{
	return (this->value < value);
}
