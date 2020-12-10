#pragma once
#include <string>

class DateTime
{
private:
    /* data */
    int year;
    int month;
    int day;
    int hour;
    int min;
    int sec;
    int milisec;

public:
    DateTime();

    DateTime(std::string date, std::string time);

    DateTime(const DateTime& input);

    DateTime &operator=(const DateTime &input);

    void readData(std::string date, std::string time);

    std::string readData(std::string &input, char delimiter);

    std::string toString();

    ~DateTime();

    void setYear(int year);
    void setMonth(int month);
    void setDay(int day);
    void setHour(int hour);
    void setMin(int min);
    void setSec(int sec);
    void setMilisec(int milisec);

    const int getYear();
    const int getMonth();
    const int getDay();
    const int getHour();
    const int getMin();
    const int getSec();
    const int getMilisec();
};