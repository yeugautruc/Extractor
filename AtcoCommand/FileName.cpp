#include <string>
#include "FileName.h"

DateTime::DateTime()
{
	year = 0;
	month = 0;
	day = 0;
	hour = 0;
	min = 0;
	sec = 0;
	milisec = 0;
}

DateTime::DateTime(std::string date, std::string time)
{
	readData(date, time);
}

DateTime::DateTime(const DateTime &input)
{
	this->year = input.year;
	this->month = input.month;
	this->day = input.day;
	this->hour = input.hour;
	this->min = input.min;
	this->sec = input.sec;
	this->milisec = input.milisec;
}

DateTime &DateTime::operator=(const DateTime &input)
{
	if (this != &input)
	{
		this->year = input.year;
		this->month = input.month;
		this->day = input.day;
		this->hour = input.hour;
		this->min = input.min;
		this->sec = input.sec;
		this->milisec = input.milisec;
	};
	return *this;
};

void DateTime::readData(std::string date, std::string time)
{
	year = stoi(readData(date, '-'));
	month = stoi(readData(date, '-'));
	day = stoi(date);
	hour = stoi(readData(time, '-'));
	min = stoi(readData(time, '-'));
	sec = stoi(readData(time, '-'));
	milisec = stoi(time);
}

std::string DateTime::readData(std::string &input, char delimiter)
{
	std::string output = input.substr(0, input.find(delimiter));
	input.erase(0, input.find(output) + output.length() + 1);
	return output;
}

std::string DateTime::toString()
{
	return " (" + std::to_string(day) + "-" + std::to_string(month) + "-" + std::to_string(year) + "-" + std::to_string(hour) + ":" + std::to_string(min) + ":" + std::to_string(sec) + "):";
}

void DateTime::setYear(int y)
{
	this->year = y;
};
void DateTime::setMonth(int m)
{
	this->month = m;
};
void DateTime::setDay(int d)
{
	this->day = d;
};
void DateTime::setHour(int h)
{
	this->hour = h;
};
void DateTime::setMin(int m)
{
	this->min = m;
};
void DateTime::setSec(int s)
{
	this->sec = s;
};
void DateTime::setMilisec(int ms)
{
	this->milisec = ms;
};

const int DateTime::getYear()
{
	return year;
};
const int DateTime::getMonth()
{
	return month;
};
const int DateTime::getDay()
{
	return day;
};
const int DateTime::getHour()
{
	return hour;
};
const int DateTime::getMin()
{
	return min;
};
const int DateTime::getSec()
{
	return sec;
};
const int DateTime::getMilisec()
{
	return milisec;
};

DateTime::~DateTime()
{
}
