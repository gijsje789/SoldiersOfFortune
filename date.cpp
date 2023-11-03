#include "date.h"

Months& operator++(Months& orig, int)
{
    orig = static_cast<Months>(orig + 1);
    if (orig > MO_DECEMBER)
    {
        orig = MO_JANUARY;
    }
    return orig;
}

Date::Date()
{
    m_year = 0;
    m_month = Months::MO_JANUARY;
    m_day = 1;
}

Date::Date(const Date &obj):
    m_year(obj.m_year),
    m_month(obj.m_month),
    m_day(obj.m_day)
{

}

Date::Date(int year, Months month, int day) :
    m_year(year),
    m_month(month),
    m_day(day)
{

}

Date::Date(QString dateString)
{
    this->setDate(dateString);
}

void Date::setDate(int year, Months month, int day)
{
    m_year = year;
    m_month = month;
    m_day = day;
}

void Date::setDate(QString formatted)
{
    formatted = formatted.trimmed();

    qsizetype yearSep = formatted.indexOf("-");
    qsizetype monthSep = formatted.indexOf("-", yearSep+1);

    m_year = formatted.sliced(0, yearSep).toInt();
    m_month = MonthStrings.key(formatted.sliced(yearSep+1, monthSep-(yearSep+1)));
    m_day = formatted.sliced(monthSep+1).toInt();
}

QString Date::getDate()
{
    return QString::number(m_year) + "-" + MonthStrings[m_month] + "-" + QString::number(m_day);
}

void Date::addDays(int days)
{
    int daysThisMonth = 0;
    int daysLeft = 0;

    while(days > 0)
    {
        daysThisMonth = getDaysInMonth(m_month, m_year);
        daysLeft = daysThisMonth - m_day;
        if(days > (daysLeft))
        {
            // new day becomes first of next month
            if(m_month == Months::MO_DECEMBER)
            {
                m_year++;
            }
            m_month++;
            m_day = 1;
            days -= (daysLeft+1);
        }
        else
        {
            // we stay int his month
            m_day += days;
            days = 0;
        }
    }
}

void Date::addWeek(int weeks)
{
    addDays(7);
}

void Date::addMonth(int months)
{
    if(months > 0)
    {
        addDays(getDaysInMonth(m_month, m_year));
    }
}

void Date::addYear(int years)
{
    m_year += years;
}

void Date::addTime(int days, int months, int years)
{
    addYear(years);
    addMonth(months);
    addDays(days);
}

void Date::setMonth(Months newMonth)
{
    m_month = newMonth;
}

Months Date::month() const
{
    return m_month;
}

int Date::day() const
{
    return m_day;
}

void Date::setDay(int newDay)
{
    m_day = newDay;
}

int Date::year() const
{
    return m_year;
}

void Date::setYear(int newYear)
{
    m_year = newYear;
}

Date Date::operator+(int val)
{
    Date newVal = Date(*this);
    newVal.addDays(val);
    return newVal;
}

bool Date::operator>(const Date &rh)
{
    bool rval = false;
    if(this->m_year > rh.m_year)
    {
        rval = true;
    }
    else
    {
        if(this->m_year == rh.m_year)
        {
            // Same year
            if(this->m_month > rh.m_month)
            {
                rval = true;
            }
            else
            {
                if(this->m_month == rh.m_month)
                {
                    // Same month
                    if(this->m_day >= rh.m_day)
                    {
                        rval = true;
                    }
                }
            }
        }
    }
    return rval;
}

bool Date::operator>(const QString& rh)
{
    Date arrivalDate = Date(rh);
    return *this > arrivalDate;
}

int Date::getDaysInMonth(Months month, int year)
{
    int rval;
    switch(month)
    {
    case MO_JANUARY:
    case MO_MARCH:
    case MO_MAY:
    case MO_JULY:
    case MO_AUGUST:
    case MO_OCTOBER:
    case MO_DECEMBER:
        rval = 31;
        break;
    case MO_APRIL:
    case MO_JUNE:
    case MO_SEPTEMBER:
    case MO_NOVEMBER:
        rval = 30;
        break;

    case MO_FEBRUARY:
        if(year % 4 == 0)
        {
            // Leap year when divisible by 4
            // but not if divisible by 100
            // but is if divisible by 400
            if(year % 100 == 0 && year % 400 > 0)
            {
                // No leap year
                rval = 28;
            }
            else
            {
                // Leap year
                rval = 29;
            }
        }
        else
        {
            rval = 28;
        }
    default:
        break;
    }
    return rval;
}
