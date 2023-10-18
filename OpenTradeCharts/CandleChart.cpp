/**
 *@file      CandleChart.cpp
 *@brief     File contains the CandleChart class implementation
 *@author    Bassil Virk
 *@date      11.10.2023
 *@copyright © Bassil Virk, 2023. All right reserved.
 */
#include <algorithm>
#include <cmath>
#include <ranges>

#include "CandleChart.h" // CandleChart class definition
#include "Candle.h"

CandleChart::CandleChart(CandleContainer&& candleContainer, float width, float height)
    : candleContainer(candleContainer), width(width), height(height), pixelsPerCurrencyYScale(10.f),
      candleSpacing(5.f), bodyWidth(9.f), wickWidth(3.f)
{
}

void CandleChart::draw(sf::RenderWindow& window)
{
    const sf::View& view = window.getView(); // Get the view of the window
    float viewLeft = view.getCenter().x - view.getSize().x / 2;  // Left edge of view
    float viewRight = view.getCenter().x + view.getSize().x / 2; // Right edge of view

    int leftIndex = viewLeft < 0.f ? 0 : static_cast<int>(viewLeft / (bodyWidth + candleSpacing)); // Index of leftmost candle
    int rightIndex = static_cast<int>(viewRight / (bodyWidth + candleSpacing)) + 1; // Index of rightmost candle

    // Drop candles that are out of view to the left, and take candles that are in view. Enumerate them so we can get the index
    auto visibleCandles = candleContainer.candles
                          | std::views::drop(leftIndex)
                          | std::views::take(rightIndex - leftIndex + 1)
                          | std::views::enumerate;

    float xPosBase = leftIndex * (bodyWidth + candleSpacing); // X position of leftmost candle that is in view

    // Draw the candles
    for (const auto& [index, candle] : visibleCandles)
    {
        float midPrice = (candle.open + candle.close) / 2; // Midpoint of candle body
        float xPos = (index + leftIndex) * (bodyWidth + candleSpacing); // X position of candle
        float yPos = -midPrice * pixelsPerCurrencyYScale; // Y position of candle

        float bodyHeight = std::abs(candle.open - candle.close) * pixelsPerCurrencyYScale; // Height of candle body
        sf::RectangleShape body({ bodyWidth, bodyHeight }); // Candle body shape
        body.setOrigin(bodyWidth / 2, bodyHeight / 2); // Set origin to center of body
        body.setPosition(xPos, yPos); // Set position of body
        body.setFillColor(candle.open < candle.close ? sf::Color::Green : sf::Color::Red); // Set color of body

        float wickHeight = candle.high - candle.low; // Height of candle wick
        sf::RectangleShape wick({ wickWidth, wickHeight * pixelsPerCurrencyYScale }); // Candle wick shape. Mult by pixelsPerCurrencyYScale to scale to price
        wick.setOrigin(wickWidth / 2, (candle.high - midPrice) * pixelsPerCurrencyYScale); // Set origin to center of wick
        wick.setPosition(xPos, yPos); // Set position of wick
        wick.setFillColor(candle.open < candle.close ? sf::Color::Green : sf::Color::Red); // Set color of wick

        window.draw(wick); // Draw wick
        window.draw(body); // Draw body
    }
}