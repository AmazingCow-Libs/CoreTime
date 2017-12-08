#pragma once

// std
#include <ctime>
#include <string>
// CoreTime
#include "CoreTime_Utils.h"
#include "TimeSpan.h"

NS_CORETIME_BEGIN

class DateTime
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    enum class DateTimeKind { Local, UTC, None };

    typedef struct tm tm_t;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Initializes a new instance of the DateTime structure to the
    ///   specified year, month, day, hour, minute, second, millisecond,
    ///   and Coordinated Universal Time (UTC) or local time.
    DateTime(
        time_t       year,
        time_t       month,
        time_t       day,
        time_t       hour,
        time_t       minute,
        time_t       second,
        time_t       millisecond,
        DateTimeKind kind = DateTimeKind::UTC);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Initializes a new instance of the DateTime structure to a specified
    ///   number of ticks and to Coordinated Universal Time (UTC) or local time.
    explicit DateTime(
        time_t       ticks,
        DateTimeKind kind = DateTimeKind::UTC);


    //------------------------------------------------------------------------//
    // Getters                                                                //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the day of the month represented by this instance.
    time_t Day() const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the day of the week represented by this instance.
    time_t DayOfWeek() const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///  Gets the day of the year represented by this instance.
    time_t DayOfYear() const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the hour component of the date represented by this instance.
    time_t Hour() const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets a value that indicates whether the time represented by
    ///   this instance is based on local time,
    ///   Coordinated Universal Time (UTC), or neither.
    DateTimeKind Kind() const;

    ///-------------------------------------------------------------------------
    /// @brief
    /// Gets the milliseconds component of the date represented
    /// by this instance.
    time_t Millisecond() const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the minute component of the date represented by this instance.
    time_t Minute() const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the month component of the date represented by this instance.
    time_t Month() const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///  Gets a DateTime object that is set to the current date and time on
    ///  this computer, expressed as the local time.
    static DateTime Now();

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the seconds component of the date represented by this instance.
    time_t Second() const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the number of ticks that represent the date and
    ///   time of this instance.
    time_t Ticks() const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the time of day for this instance.
    TimeSpan TimeOfDay() const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///  Gets the current date.
    static DateTime Today();

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets a DateTime object that is set to the current date and time
    ///   on this computer, expressed as the Coordinated Universal Time (UTC).
    static DateTime UtcNow();


    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the year component of the date represented by this instance.
    time_t Year() const;


    //------------------------------------------------------------------------//
    // Methods                                                                //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new DateTime that adds the value of the specified
    ///   TimeSpan to the value of this instance.
    DateTime Add(const TimeSpan &timeSpan);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new DateTime that adds the specified number of days to
    ///   the value of this instance.
    DateTime AddDays(double days);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new DateTime that adds the specified number of hours to
    ///   the value of this instance.
    DateTime AddHours(double hours);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new DateTime that adds the specified number of milliseconds
    ///   to the value of this instance.
    DateTime AddMilliseconds(double ms);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new DateTime that adds the specified number of minutes
    ///   to the value of this instance.
    DateTime AddMinutes(double minutes);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new DateTime that adds the specified number of months to
    ///   the value of this instance.
    DateTime AddMonths(time_t months);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new DateTime that adds the specified number of seconds to
    ///   the value of this instance.
    DateTime AddSeconds(double seconds);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new DateTime that adds the specified number of ticks to
    ///   the value of this instance.
    DateTime AddTicks(time_t ticks);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new DateTime that adds the specified number of years to
    ///   the value of this instance.
    DateTime AddYears(time_t years);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Compares two instances of DateTime and returns an time_teger that
    ///   indicates whether the first instance is earlier than, the same as,
    ///   or later than the second instance.
    static time_t Compare(const DateTime &lhs, const DateTime &rhs);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Compares the value of this instance to a specified DateTime value
    ///   and returns an time_teger that indicates whether this instance is
    ///   earlier than, the same as, or later than the specified DateTime value.
    time_t CompareTo(const DateTime &rhs) const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns the number of days in the specified month and year.
    static time_t DaysInMonth(time_t month, time_t year);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Indicates whether this instance of DateTime is within the daylight
    ///   saving time range for the current time zone.
    bool IsDaylightSavingTime() const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns an indication whether the specified year is a leap year.
    static bool IsLeapYear(time_t year);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Converts the string representation of a date and time to
    ///   its DateTime equivalent.
    static DateTime Parse(const std::string &format);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Creates a new DateTime object that has the same number of
    ///   ticks as the specified DateTime, but is designated as either
    ///   local time, Coordinated Universal Time (UTC), or neither,
    ///   as indicated by the specified DateTimeKind value.
    static DateTime SpecifyKind(const DateTime &dateTime, DateTimeKind kind);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Subtracts the specified date and time from this instance.
    DateTime Subtract(const DateTime &dateTime) const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Subtracts the specified duration from this instance.
    DateTime Subtract(const TimeSpan &timeSpan) const;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Converts the value of the current DateTime object to local time.
    void ToLocalTime();

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Converts the value of the current DateTime object to
    ///   Coordinated Universal Time (UTC).
    void ToUniversalTime();


    //------------------------------------------------------------------------//
    // Helper Methods                                                         //
    //------------------------------------------------------------------------//
private:
    const tm_t& Update_tm()const;



    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    time_t       m_ticksSinceUnixEpoch;
    DateTimeKind m_kind;

    mutable tm_t m_tm;
    mutable bool m_tmIsDirty;
};

NS_CORETIME_END
