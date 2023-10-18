/**
 *@file      CandleContainer.cpp
 *@brief     File contains the CandleContainer class definition
 *@details   Container class wrapping a vector of Candles, and other stock/asset metadata. 
 *			 All stock/asset data should be wrapped up into this class for use by other classes.
 *@author    Bassil Virk
 *@date      14.10.2023
 *@copyright © Bassil Virk, 2023. All right reserved.
 */
#include <chrono>

#include "CandleContainer.h" // CandleContainer class definition
#include "ChronoDefinitions.h"
#include "Candle.h"

CandleContainer::CandleContainer()
	: candleDuration(Duration::zero())
{
}

// Set candleDuration to either the first candle's duration, or zero if the vector is empty
CandleContainer::CandleContainer(std::vector<Candle>&& candles)
	: candles(std::move(candles)), candleDuration(this->candles.empty() ? Duration::zero() : this->candles[0].duration)
{
}

CandleContainer::CandleContainer(std::vector<Candle>&& candles, Duration candleDuration)
	: candles(std::move(candles)), candleDuration(candleDuration)
{
}

void CandleContainer::appendCandle(Candle&& candle)
{
	candles.push_back(std::move(candle));
}

void CandleContainer::appendCandle(float open, float high, float low, float close, int volume, Date date, Time time)
{
	candles.emplace_back(open, high, low, close, volume, date, time, candleDuration);
}

bool CandleContainer::updateLastCandle(float currentPrice)
{
	// If there are no candles, return false
	if (candles.empty())
		return false;

	// Set the close price of the last candle to currentPrice, and update the high and low if necessary
	Candle& candle = candles.back();
	candle.close = currentPrice;
	candle.high = candle.close > candle.high ? candle.close : candle.high;
	candle.low = candle.close < candle.low ? candle.close : candle.low;
}
