
// Header
#include "../include/TimeSpan.h"
// std
#include <limits>

// Usings
USING_NS_CORETIME;


//----------------------------------------------------------------------------//
// Enums / Constants / Typedefs                                               //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
const TimeSpan& TimeSpan::MaxValue()
{
    static TimeSpan s_time_span(std::numeric_limits<time_t>::max());
    return s_time_span;
}

//------------------------------------------------------------------------------
const TimeSpan& TimeSpan::MinValue()
{
    static TimeSpan s_time_span(std::numeric_limits<time_t>::min());
    return s_time_span;
}

//------------------------------------------------------------------------------
const TimeSpan& TimeSpan::Zero()
{
    static TimeSpan s_time_span(0);
    return s_time_span;
}


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
//------------------------------------------------------------------------------
TimeSpan::TimeSpan(time_t hours, time_t minutes, time_t seconds) :
    TimeSpan(0, hours, minutes, seconds)
{
    // Empty...
}

//------------------------------------------------------------------------------
TimeSpan::TimeSpan(time_t days, time_t hours, time_t minutes, time_t seconds) :
    TimeSpan(days, hours, minutes, seconds, 0)
{
    // Empty...
}

//------------------------------------------------------------------------------
TimeSpan::TimeSpan(
    time_t days,
    time_t hours,
    time_t minutes,
    time_t seconds,
    time_t milliseconds) :
    m_days        (        days),
    m_hours       (       hours),
    m_minutes     (     minutes),
    m_seconds     (     seconds),
    m_milliseconds(milliseconds)
{
    // Empty...
}

//------------------------------------------------------------------------------
TimeSpan::TimeSpan(time_t ticks) :
    TimeSpan(
        ticks / TicksPerDay,
        ticks / TicksPerHour,
        ticks / TicksPerMinute,
        ticks / TicksPerSecond,
        ticks / TicksPerMillisecond
    )
{
    // Empty....
}
