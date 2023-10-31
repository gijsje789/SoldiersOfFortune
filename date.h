#ifndef DATE_H
#define DATE_H

#include <QString>
#include <QMap>

enum Months
{
    MO_JANUARY = 0,
    MO_FEBRUARY,
    MO_MARCH,
    MO_APRIL,
    MO_MAY,
    MO_JUNE,
    MO_JULY,
    MO_AUGUST,
    MO_SEPTEMBER,
    MO_OCTOBER,
    MO_NOVEMBER,
    MO_DECEMBER
};
Months& operator++(Months& orig, int);

class Date {
public:
    Date();
    Date(Date const &obj);
    Date(int year, Months month, int day);
    Date(QString dateString);
    void setDate(int year, Months month, int day);
    void setDate(QString formatted);
    QString getDate();
    void addDays(int days);
    void addWeek(int weeks);
    void addMonth(int months);
    void addYear(int years);
    void addTime(int days, int months = 0, int years = 0);

    void setMonth(Months newMonth);
    Months month() const;

    int day() const;
    void setDay(int newDay);

    int year() const;
    void setYear(int newYear);

    Date operator+(int val);
    bool operator>(const Date& rh);
    bool operator>(const QString& rh);

private:
    Months m_month = Months::MO_JANUARY;
    int m_day = 1;
    int m_year = 2023;

    int getDaysInMonth(Months month, int year);

    QMap<Months, QString> MonthStrings
    {
        {MO_JANUARY, "January"},
        {MO_FEBRUARY, "Feburary"},
        {MO_MARCH, "March"},
        {MO_APRIL, "April"},
        {MO_MAY, "May"},
        {MO_JUNE, "June"},
        {MO_JULY, "July"},
        {MO_AUGUST, "August"},
        {MO_SEPTEMBER, "September"},
        {MO_OCTOBER, "October"},
        {MO_NOVEMBER, "November"},
        {MO_DECEMBER, "December"}
    };
};

#endif // DATE_H
