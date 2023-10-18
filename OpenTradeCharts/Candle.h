/**
 *@file      Candle.h
 *@brief     File contains the Candle class definition and implementation
 *@details   A candle represents the open, high, low, close, and volume of a financial instrument at a given time
 *@author    Bassil Virk
 *@date      11.10.2023
 *@copyright © Bassil Virk, 2023. All right reserved.
 */
#pragma once
#include <chrono>

#include "ChronoDefinitions.h"

/**
 *@class   Candle
 *@brief   Data structure representing a "Candle", in financial terms
 *@details A candle represents the open, high, low, close, and volume of a financial instrument at a given time
 *@author  Bassil Virk
 */
class Candle
{
public:
    /**
     *@brief Candle constructor with all parameters specified
     *@param open      - Open price
     *@param high      - High price
     *@param low       - Low price
     *@param close     - Close price
     *@param volume    - Volume traded
     *@param date      - Date of candle
     *@param time      - Time at which this candle began
     *@param duration  - Time duration of candle in seconds
     */
    Candle(float open, float high, float low, float close, int volume, Date date, Time time, Duration duration)
        : open(open), high(high), low(low), close(close), volume(volume),
          date(date), time(time), duration(duration)
    {
    }

    /**
     *@brief Candle constructor with no specified date, time, or duration
     *@param open      - Open price
     *@param high      - High price
     *@param low       - Low price
     *@param close     - Close price
     *@param volume    - Volume traded
     */
    Candle(float open, float high, float low, float close, int volume)
        : open(open), high(high), low(low), close(close), volume(volume),
          date(Date()), time(Time()), duration(Duration::zero())
    {
    }

    /**
     *@brief Candle constructor with no specified volume, date, time, or duration
     *@param open      - Open price
     *@param high      - High price
     *@param low       - Low price
     *@param close     - Close price
     */
    Candle(float open, float high, float low, float close)
        : open(open), high(high), low(low), close(close), volume(0),
		  date(Date()), time(Time()), duration(Duration::zero())
    {
    }

    float open;  //!< Open price
    float high;  //!< High price
    float low;   //!< Low price
    float close; //!< Close price
    int volume;  //!< Volume traded

    Date date;         //!< Date of candle
    Time time;         //!< Time that candle began at
    Duration duration; //!< Time duration of candle in seconds
};