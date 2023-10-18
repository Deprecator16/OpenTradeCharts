/**
 *@file      CandleContainer.h
 *@brief     File contains the CandleContainer class definition
 *@details   Container class wrapping a vector of Candles, and other stock/asset metadata. All stock/asset data should be wrapped up into this class for use by other classes.
 *@author    Bassil Virk
 *@date      14.10.2023
 *@copyright © Bassil Virk, 2023. All right reserved.
 */
#pragma once
#include <vector>

#include "ChronoDefinitions.h"

class Candle;

/**
 *@class   CandleContainer
 *@brief   Container class wrapping a vector of Candles, and other stock/asset metadata.
 *@details All stock/asset data should be wrapped up into this class for use by other classes.
 *@author  Bassil Virk
 */
class CandleContainer
{
public:
	/**
	*@brief Empty CandleContainer constructor. The candleDuration must be set before using an object created by this constructor
	*/
	CandleContainer();

	/**
	*@brief CandleContainer constructed with existing vector. Vector will be moved in. candleDuration is automatically set to 
	* either the first candle's duration, or zero if the vector is empty
	*@param candles - std::vector of Candles to be moved into this CandleContainer
	*/
	CandleContainer(std::vector<Candle>&& candles);

	/**
	*@brief CandleContainer constructed with existing vector, which will be moved in, and a duration
	*@param candles        - std::vector of Candles to be moved into this CandleContainer
	*@param candleDuration - Duration of candles in seconds
	*/
	CandleContainer(std::vector<Candle>&& candles, Duration candleDuration);

	/**
	*@brief Moves a candle into end of vector
	*@param candle - Candle object to move in
	*/
	void appendCandle(Candle&& candle);

	/**
	*@brief Emplaces candle into end of vector
	*@param open   - Candle open
	*@param high   - Candle high
	*@param low    - Candle low
	*@param close  - Candle close
	*@param volume - Candle volume
	*@param date   - Candle start date
	*@param time   - Candle start time
	*/
	void appendCandle(float open, float high, float low, float close, int volume, Date date, Time time);

	/**
	*@brief  Updates the close price of the last candle in the vector. Used to update the last candle live
	*@param  currentPrice    - Price to update candle close value to
	*@retval                 - True if candle was successfully updated
	*/
	bool updateLastCandle(float currentPrice);

	std::vector<Candle> candles; //!< Vector of candles
	Duration candleDuration;	 //!< Duration of candles in this container
};

