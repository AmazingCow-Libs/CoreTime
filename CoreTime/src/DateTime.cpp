// Header
#include "../include/DateTime.h"
// CoreTime
#include "../include/TimeSpan.h"
#include <sys/time.h>
// Usings
USING_NS_CORETIME;


//----------------------------------------------------------------------------//
// Helper Functions                                                           //
//----------------------------------------------------------------------------//
DateTime::tm_t convert_to_tm(time_t ticks, DateTime::DateTimeKind kind)
{
    auto seconds = (ticks / TimeSpan::TicksPerSecond);

    DateTime::tm_t _tm = {0};
    (kind == DateTime::DateTimeKind::UTC)
        ? gmtime_r   (&seconds, &_tm)
        : localtime_r(&seconds, &_tm);

    return _tm;
}


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
DateTime::DateTime(
    time_t       year,
    time_t       month,
    time_t       day,
    time_t       hour,
    time_t       minute,
    time_t       second,
    time_t       millisecond,
    DateTimeKind kind /* = DateTimeKind::UTC */) :
    m_kind               (kind),
    m_tmIsDirty          (true)
{
    auto tm = tm_t{
        .tm_sec   = second,      /* Seconds. [0-60] (1 leap second) */
        .tm_min   = minute,      /* Minutes. [0-59]                 */
        .tm_hour  = hour,        /* Hours.   [0-23]                 */
        .tm_mday  = day,         /* Day.     [1-31]                 */
        .tm_mon   = month - 1,   /* Month.   [0-11]                 */
        .tm_year  = year - 1900, /* Year - 1900.                    */
        .tm_wday  = 0,           /* Day of week. [0-6]              */
        .tm_yday  = 0,           /* Days in year.[0-365]            */
        .tm_isdst =  -1          /* DST.     [-1/0/1]               */
    };

    auto seconds          = mktime(&tm);
    m_ticksSinceUnixEpoch = (seconds * TimeSpan::TicksPerSecond);
}

//------------------------------------------------------------------------------
DateTime::DateTime(
    time_t       ticks,
    DateTimeKind kind /* = DateTimeKind::UTC */) :
    m_ticksSinceUnixEpoch(ticks),
    m_kind               ( kind),
    m_tmIsDirty          ( true)
{
    // Empty...
}


//----------------------------------------------------------------------------//
// Getters                                                                    //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
time_t DateTime::Day() const
{
    return Update_tm().tm_mday;
}

//------------------------------------------------------------------------------
time_t DateTime::DayOfWeek() const
{
    return Update_tm().tm_wday;
}

//------------------------------------------------------------------------------
time_t DateTime::DayOfYear() const
{
    return Update_tm().tm_yday + 1;
}

//------------------------------------------------------------------------------
time_t DateTime::Hour() const
{
    return Update_tm().tm_hour;
}

//------------------------------------------------------------------------------
DateTime::DateTimeKind DateTime::Kind() const
{
    return m_kind;
}

//------------------------------------------------------------------------------
time_t DateTime::Millisecond() const
{
    return 0;
}

//------------------------------------------------------------------------------
time_t DateTime::Minute() const
{
    return Update_tm().tm_min;
}

//------------------------------------------------------------------------------
time_t DateTime::Month() const
{
    return Update_tm().tm_mon + 1;
}

//------------------------------------------------------------------------------
DateTime DateTime::Now()
{
    //--------------------------------------------------------------------------
    // Get the "time" since the epoch.
    struct timeval _timeval = {0};
    gettimeofday(&_timeval, nullptr);

    //--------------------------------------------------------------------------
    // Now we have the "time" in the localtime, just calculate
    // how many ticks this represents.
    return DateTime(
        _timeval.tv_sec         * TimeSpan::TicksPerSecond +
        _timeval.tv_usec / 1000 * TimeSpan::TicksPerMillisecond,
        DateTimeKind::Local
    );
}

//------------------------------------------------------------------------------
time_t DateTime::Second() const
{
    return Update_tm().tm_sec;
}

//------------------------------------------------------------------------------
time_t DateTime::Ticks() const
{
    return m_ticksSinceUnixEpoch;
}

//------------------------------------------------------------------------------
TimeSpan DateTime::TimeOfDay() const
{
    return TimeSpan(m_ticksSinceUnixEpoch);
}

//------------------------------------------------------------------------------
DateTime DateTime::Today()
{
    //COWTODO(n2omatt): Implement...
}

//------------------------------------------------------------------------------
DateTime DateTime::UtcNow()
{
    // Get the "time" since the epoch.
    struct timeval _timeval = {0};
    gettimeofday(&_timeval, nullptr);

    //--------------------------------------------------------------------------
    // Now we have the "time" in the localtime, just calculate
    // how many ticks this represents.
    return DateTime(
        _timeval.tv_sec         * TimeSpan::TicksPerSecond +
        _timeval.tv_usec / 1000 * TimeSpan::TicksPerMillisecond,
        DateTimeKind::UTC
    );
}


//------------------------------------------------------------------------------
time_t DateTime::Year() const
{
    return Update_tm().tm_year + 1900;
}


//----------------------------------------------------------------------------//
// Methods                                                                    //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
DateTime DateTime::Add(const TimeSpan &timeSpan)
{

}

//------------------------------------------------------------------------------
DateTime DateTime::AddDays(double days)
{
    return DateTime(
        m_ticksSinceUnixEpoch + (days * TimeSpan::TicksPerDay),
        m_kind
    );
}

//------------------------------------------------------------------------------
DateTime DateTime::AddHours(double hours)
{
    return DateTime(
        m_ticksSinceUnixEpoch + (hours * TimeSpan::TicksPerHour),
        m_kind
    );
}

//------------------------------------------------------------------------------
DateTime DateTime::AddMilliseconds(double ms)
{
    return DateTime(
        m_ticksSinceUnixEpoch + (ms * TimeSpan::TicksPerMillisecond),
        m_kind
    );
}

//------------------------------------------------------------------------------
DateTime DateTime::AddMinutes(double minutes)
{
    return DateTime(
        m_ticksSinceUnixEpoch + (minutes * TimeSpan::TicksPerMinute),
        m_kind
    );
}

//------------------------------------------------------------------------------
DateTime DateTime::AddMonths(time_t months)
{
    //--------------------------------------------------------------------------
    // Get the current date.
    auto curr_day   = Day  ();
    auto curr_month = Month();
    auto curr_year  = Year ();

    //--------------------------------------------------------------------------
    // Calculate which month/year we gonna be.
    auto target_month = (curr_month + months) % 12;
    auto span_years   = (curr_month + months) / 12;

    if(target_month == 0)
    {
        target_month = curr_month;
        --span_years;
    }

    auto target_year = curr_year + span_years;

    //--------------------------------------------------------------------------
    // Clamp the day, so it'll be valid on that month.
    auto days_in_target_month = DaysInMonth(target_month, target_year);
    auto target_day           = curr_day;
    if(curr_day > days_in_target_month)
        target_day = days_in_target_month;


    return DateTime(
        target_year,
        target_month,
        target_day,
        Hour       (),
        Minute     (),
        Second     (),
        Millisecond(),
        m_kind
    );
}

//------------------------------------------------------------------------------
DateTime DateTime::AddSeconds(double seconds)
{
    return DateTime(
        m_ticksSinceUnixEpoch + (seconds * TimeSpan::TicksPerSecond),
        m_kind
    );
}

//------------------------------------------------------------------------------
DateTime DateTime::AddTicks(time_t ticks)
{

}

//------------------------------------------------------------------------------
DateTime DateTime::AddYears(time_t years)
{
    return AddMonths(years * 12);
}

//------------------------------------------------------------------------------
time_t DateTime::Compare(const DateTime &lhs, const DateTime &rhs)
{

}

//------------------------------------------------------------------------------
time_t DateTime::CompareTo(const DateTime &rhs) const
{

}

//------------------------------------------------------------------------------
time_t DateTime::DaysInMonth(time_t month, time_t year)
{
    //COWTODO(n2omatt): Sanity checks...
    --month;

    //--------------------------------------------------------------------------
    // Reference:
    //   http://memorize.com/days-in-each-month
    static int k_month_days[] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };

    //--------------------------------------------------------------------------
    // Only February can change its month days.
    if(month != 2)
        return k_month_days[month];

    //--------------------------------------------------------------------------
    // Add a leap day if year is leap year.
    return k_month_days[2] + ((IsLeapYear(year)) ? 1 : 0);
}

//------------------------------------------------------------------------------
bool DateTime::IsDaylightSavingTime() const
{
    if(m_kind == DateTimeKind::UTC)
        return false;

    return (Update_tm().tm_isdst > 0);
}

//------------------------------------------------------------------------------
bool DateTime::IsLeapYear(time_t year)
{
    //--------------------------------------------------------------------------
    // Reference:
    //   https://en.wikipedia.org/wiki/Leap_year
    return (year % 4 == 0) && (year % 100 == 0 && year % 400 != 0);
}

//------------------------------------------------------------------------------
DateTime DateTime::Parse(const std::string &format)
{
}

//------------------------------------------------------------------------------
DateTime DateTime::SpecifyKind(const DateTime &dateTime, DateTimeKind kind)
{

}

//------------------------------------------------------------------------------
DateTime DateTime::Subtract(const DateTime &dateTime) const
{

}

//------------------------------------------------------------------------------
DateTime DateTime::Subtract(const TimeSpan &timeSpan) const
{

}

//------------------------------------------------------------------------------
void DateTime::ToLocalTime()
{

}

//------------------------------------------------------------------------------
void DateTime::ToUniversalTime()
{
    // Nothing to convert...
    if(m_kind == DateTimeKind::UTC)
        return;



}

//----------------------------------------------------------------------------//
// Helper Methods                                                             //
//----------------------------------------------------------------------------//
const DateTime::tm_t& DateTime::Update_tm() const
{
    if(!m_tmIsDirty)
        return m_tm;

    m_tm        = convert_to_tm(m_ticksSinceUnixEpoch, m_kind);
    m_tmIsDirty = false;

    return m_tm;
}
