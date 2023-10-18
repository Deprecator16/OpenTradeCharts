/**
 *@file      CandleChart.h
 *@brief     File contains the CandleChart class definition
 *@details   Responsible for drawing a container of candles. Will draw all visible 
 *           candles in the window view. CandleChart objects should be created and 
 *           managed by a CandleChartManager object. CandleChart objects should not 
 *           be created directly by the user.
 *@author    Bassil Virk
 *@date      11.10.2023
 *@copyright © Bassil Virk, 2023. All right reserved.
 */
#pragma once
#include <vector>
#include <chrono>

#include <SFML/Graphics.hpp>

#include "ChronoDefinitions.h"
#include "CandleContainer.h"

/**
 *@class   CandleChart
 *@brief   Responsible for drawing a container of candles
 *@details Will draw all visible candles in the window view
 *@author  Bassil Virk
 */
class CandleChart
{
public:
    /**
     *@brief CandleChart object constructor
     *@param candleContainer - CandleContainer to be moved into this chart
     *@param width           - Width of the chart in pixels
     *@param height          - Height of the chart in pixels
     */
    CandleChart(CandleContainer&& candleContainer, float width, float height);

    /**
     *@brief Draws candles to the window view
     *@param window - RenderWindow object to draw to
     */
    void draw(sf::RenderWindow& window);

    CandleContainer candleContainer; //!< Candles to draw are taken from this container

    float width;  //!< Width of this chart in pixels
    float height; //!< Height of this chart in pixels

    float pixelsPerCurrencyYScale; //!< Amount to scale candles by along y axis.
    float candleSpacing;           //!< Pixels of space between candles
    float bodyWidth;               //!< Width of candle bodies
    float wickWidth;               //!< Width of candle wicks
};