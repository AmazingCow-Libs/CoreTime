#pragma once

// std
#include <ctime>
#include <string>
// CoreTime
#include "CoreTime_Utils.h"


NS_CORETIME_BEGIN

class TimeSpan
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Represents the maximum TimeSpan value. This field is read-only.
    static const TimeSpan& MaxValue();

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Represents the minimum TimeSpan value. This field is read-only.
    static const TimeSpan& MinValue();

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Represents the number of ticks in 1 millisecond. This field is constant.
    static constexpr time_t TicksPerMillisecond = 10000;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Represents the number of ticks in 1 second.
    static constexpr time_t TicksPerSecond = TicksPerMillisecond * 1000;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Represents the number of ticks in 1 minute. This field is constant.
    static constexpr time_t TicksPerMinute = TicksPerSecond * 60;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Represents the number of ticks in 1 hour. This field is constant.
    static constexpr time_t TicksPerHour = TicksPerMinute * 60;


    ///-------------------------------------------------------------------------
    /// @brief
    ///   Represents the number of ticks in 1 day. This field is constant.
    static constexpr time_t TicksPerDay = TicksPerHour * 24;

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Represents the zero TimeSpan value. This field is read-only.
    static const TimeSpan& Zero();


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Initializes a new instance of the TimeSpan structure to a
    ///   specified number of hours, minutes, and seconds.
    TimeSpan(time_t hours, time_t minutes, time_t seconds);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Initializes a new instance of the TimeSpan structure to
    ///   a specified number of days, hours, minutes, and seconds.
    TimeSpan(time_t days, time_t hours, time_t minutes, time_t seconds);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Initializes a new instance of the TimeSpan structure to a specified
    ///   number of days, hours, minutes, seconds, and milliseconds.
    TimeSpan(
        time_t days,
        time_t hours,
        time_t minutes,
        time_t seconds,
        time_t milliseconds);

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Initializes a new instance of the TimeSpan structure to the
    ///   specified number of ticks.
    TimeSpan(time_t ticks);


    //------------------------------------------------------------------------//
    // Getters Methods                                                        //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the days component of the time interval represented by
    ///   the current TimeSpan structure.
    inline time_t Days() const { return m_days; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the hours component of the time interval represented by the
    ///   current TimeSpan structure.
    inline time_t Hours() const { return m_hours; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the milliseconds component of the time interval represented by
    ///   the current TimeSpan structure.
    inline time_t Milliseconds() const { return m_milliseconds; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the minutes component of the time interval represented by the
    ///   current TimeSpan structure.
    inline time_t Minutes() const { return m_minutes; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the seconds component of the time interval represented by the
    ///   current TimeSpan structure.
    inline time_t Seconds() const { return m_seconds; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the number of ticks that represent the value of the current
    ///   TimeSpan structure.
    inline time_t Ticks() const
    {
        return m_days         * TicksPerDay
             + m_hours        * TicksPerHour
             + m_minutes      * TicksPerMinute
             + m_seconds      * TicksPerSecond
             + m_milliseconds * TicksPerMillisecond;
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the value of the current TimeSpan structure expressed in
    ///   whole and fractional days.
    inline double TotalDays() const { return Ticks() / TicksPerDay; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the value of the current TimeSpan structure expressed in
    ///   whole and fractional hours.
    inline double TotalHours() const { return Ticks() / TicksPerHour; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the value of the current TimeSpan structure expressed in
    ///   whole and fractional milliseconds.
    inline double TotalMilliseconds() const { return Ticks() / TicksPerMillisecond; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the value of the current TimeSpan structure expressed in
    ///   whole and fractional minutes.
    inline double TotalMinutes() const { return Ticks() / TicksPerMinute; }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Gets the value of the current TimeSpan structure expressed in
    ///   whole and fractional seconds.
    inline double TotalSeconds() const { return Ticks() / TicksPerSecond; }


    //------------------------------------------------------------------------//
    // Methods                                                                //
    //------------------------------------------------------------------------//
public:
    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new TimeSpan object whose value is the sum of the specified
    ///   TimeSpan object and this instance.
    inline TimeSpan Add(const TimeSpan &timeSpan) const
    {
        return TimeSpan(*this + timeSpan);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Compares two TimeSpan values and returns an integer that indicates
    ///   whether the first value is shorter than, equal to, or longer than
    ///   the second value.
    inline static time_t Compare(const TimeSpan &lhs, const TimeSpan &rhs)
    {
        return (lhs.Ticks() - rhs.Ticks());
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Compares this instance to a specified TimeSpan object and returns an
    ///   integer that indicates whether this instance is shorter than, equal to,
    ///   or longer than the TimeSpan object.
    inline time_t CompareTo(const TimeSpan &rhs) const
    {
        return Compare(*this, rhs);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new TimeSpan object whose value is the absolute value of the
    ///   current TimeSpan object.
    TimeSpan Duration() const
    {
        auto ticks = Ticks();
        return TimeSpan((ticks < 0) ? -ticks : ticks);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a value that indicates whether two specified instances of
    ///   TimeSpan are equal.
    static bool Equals(const TimeSpan &lhs, const TimeSpan &rhs)
    {
        return lhs.Ticks() == rhs.Ticks();
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a TimeSpan that represents a specified number of days, where
    ///   the specification is accurate to the nearest millisecond.
    inline static TimeSpan FromDays(double days)
    {
        return TimeSpan(days * TicksPerDay);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a TimeSpan that represents a specified number of hours,
    ///   where the specification is accurate to the nearest millisecond.
    inline static TimeSpan FromHours(double hours)
    {
        return TimeSpan(hours * TicksPerHour);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a TimeSpan that represents a specified number of milliseconds.
    inline static TimeSpan FromMilliseconds(double ms)
    {
        return TimeSpan(ms * TicksPerMillisecond);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a TimeSpan that represents a specified number of minutes,
    ///   where the specification is accurate to the nearest millisecond.
    inline static TimeSpan FromMinutes(double minutes)
{
        return TimeSpan(minutes * TicksPerMinute);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a TimeSpan that represents a specified number of seconds,
    ///   where the specification is accurate to the nearest millisecond.
    inline static TimeSpan FromSeconds(double seconds)
    {
        return TimeSpan(seconds * TicksPerSecond);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a TimeSpan that represents a specified time, where the
    ///   specification is in units of ticks.
    inline static TimeSpan FromTicks(time_t ticks)
    {
        return TimeSpan(ticks);
    }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new TimeSpan object whose value is the negated value
    ///   of this instance.
    inline TimeSpan Negate() const { return TimeSpan(-Ticks()); }

    ///-------------------------------------------------------------------------
    /// @brief
    ///   Returns a new TimeSpan object whose value is the difference between
    ///   the specified TimeSpan object and this instance.
    TimeSpan Subtract(const TimeSpan &rhs) const
    {
        return TimeSpan(*this - rhs);
    }


    //------------------------------------------------------------------------//
    // Operators                                                              //
    //------------------------------------------------------------------------//
public:
    friend bool operator < (const TimeSpan &lhs, const TimeSpan &rhs);
    friend bool operator > (const TimeSpan &lhs, const TimeSpan &rhs);

    friend bool operator <=(const TimeSpan &lhs, const TimeSpan &rhs);
    friend bool operator >=(const TimeSpan &lhs, const TimeSpan &rhs);

    friend bool operator ==(const TimeSpan &lhs, const TimeSpan &rhs);
    friend bool operator !=(const TimeSpan &lhs, const TimeSpan &rhs);

    friend TimeSpan operator + (const TimeSpan &lhs, const TimeSpan &rhs);
    friend TimeSpan operator - (const TimeSpan &lhs, const TimeSpan &rhs);

    friend TimeSpan& operator +=(TimeSpan &lhs, const TimeSpan &rhs);
    friend TimeSpan& operator -=(TimeSpan &lhs, const TimeSpan &rhs);


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    time_t m_days;
    time_t m_hours;
    time_t m_minutes;
    time_t m_seconds;
    time_t m_milliseconds;
};

//----------------------------------------------------------------------------//
// Operators                                                                  //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
inline bool operator <(const TimeSpan &lhs, const TimeSpan &rhs)
{
    return lhs.Ticks() < rhs.Ticks();
}

//------------------------------------------------------------------------------
inline bool operator >(const TimeSpan &lhs, const TimeSpan &rhs)
{
    return lhs.Ticks() > rhs.Ticks();
}

//------------------------------------------------------------------------------
inline bool operator <=(const TimeSpan &lhs, const TimeSpan &rhs)
{
    return lhs.Ticks() <= rhs.Ticks();
}

//------------------------------------------------------------------------------
inline bool operator >=(const TimeSpan &lhs, const TimeSpan &rhs)
{
    return lhs.Ticks() >= rhs.Ticks();
}

//------------------------------------------------------------------------------
inline bool operator ==(const TimeSpan &lhs, const TimeSpan &rhs)
{
    return lhs.Ticks() == rhs.Ticks();
}

//------------------------------------------------------------------------------
inline bool operator !=(const TimeSpan &lhs, const TimeSpan &rhs)
{
    return lhs.Ticks() != rhs.Ticks();
}

inline TimeSpan operator +(const TimeSpan &lhs, const TimeSpan &rhs)
{
    return TimeSpan(lhs.Ticks() + rhs.Ticks());
}

inline TimeSpan operator -(const TimeSpan &lhs, const TimeSpan &rhs)
{
    return TimeSpan(lhs.Ticks() - rhs.Ticks());
}


inline TimeSpan& operator +=(TimeSpan &lhs, const TimeSpan &rhs)
{
    lhs.m_days         += rhs.m_days;
    lhs.m_hours        += rhs.m_hours;
    lhs.m_minutes      += rhs.m_minutes;
    lhs.m_seconds      += rhs.m_seconds;
    lhs.m_milliseconds += rhs.m_milliseconds;

    return lhs;
}

inline TimeSpan& operator -=(TimeSpan &lhs, const TimeSpan &rhs)
{
    lhs.m_days         -= rhs.m_days;
    lhs.m_hours        -= rhs.m_hours;
    lhs.m_minutes      -= rhs.m_minutes;
    lhs.m_seconds      -= rhs.m_seconds;
    lhs.m_milliseconds -= rhs.m_milliseconds;

    return lhs;
}

NS_CORETIME_END
