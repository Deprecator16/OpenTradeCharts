/**
 *@file      main.cpp
 *@brief     Main entry point for the OpenTradeCharts application.
 *@details   Creates SFML window, handles user input, draws the chart and candlesticks, 
 *           updates the window.
 *@author    Bassil Virk
 *@date      11.10.2023
 *@copyright © Bassil Virk, 2023. All right reserved.
 */
#include <chrono>
#include <vector>
#include <iostream>
#include <ranges>

#include <SFML/Graphics.hpp>
#include "ChronoDefinitions.h"
#include "Candle.h"
#include "CandleContainer.h"
#include "CandleChart.h"

// Main entry point for the OpenTradeCharts application
int main() {
    using namespace std::chrono;
    using namespace std::literals;

    sf::Vector2i baseWindowSize = { 1200, 900 }; // Default window size

    sf::RenderWindow window(sf::VideoMode(baseWindowSize.x, baseWindowSize.y), "OpenTradeCharts"); // Create window
    
    // Example candles, for testing purposes only
    std::vector<Candle> candles = {
        {42.5f, 55.2f, 37.8f, 49.6f},
        {51.2f, 63.4f, 48.7f, 56.8f},
        {59.8f, 74.5f, 56.2f, 62.3f},
        {58.3f, 69.7f, 55.1f, 63.5f},
        {65.1f, 78.2f, 61.4f, 70.9f},
        {71.0f, 85.6f, 68.2f, 76.4f},
        {76.8f, 90.3f, 72.9f, 81.2f},
        {80.2f, 94.7f, 76.1f, 85.9f},
        {85.5f, 99.2f, 80.4f, 90.6f},
        {88.7f, 98.3f, 84.1f, 87.9f},
        {85.9f, 92.6f, 82.0f, 88.5f},
        {90.1f, 99.5f, 88.3f, 94.7f},
        {94.4f, 100.0f, 90.5f, 91.7f},
        {91.6f, 98.2f, 89.4f, 92.3f},
        {92.4f, 97.5f, 90.6f, 94.1f},
        {94.2f, 99.8f, 92.1f, 95.6f},
        {95.7f, 99.6f, 93.5f, 97.2f},
        {97.3f, 100.0f, 95.2f, 98.5f},
        {98.6f, 100.0f, 96.8f, 99.7f},
        {99.8f, 100.0f, 98.2f, 100.0f},
        {99.9f, 100.0f, 98.9f, 99.6f},
        {99.7f, 100.0f, 98.2f, 99.8f},
        {99.8f, 100.0f, 98.7f, 99.9f},
        {99.9f, 100.0f, 99.1f, 99.7f},
        {99.7f, 100.0f, 99.3f, 99.5f},
        {99.5f, 100.0f, 99.0f, 99.2f},
        {99.2f, 100.0f, 98.5f, 99.6f},
        {99.6f, 100.0f, 99.2f, 99.4f},
        {99.4f, 100.0f, 98.9f, 99.8f},
        {99.8f, 100.0f, 99.5f, 99.7f},
        {99.7f, 100.0f, 99.2f, 99.9f},
        {99.9f, 100.0f, 99.7f, 99.8f},
        {99.8f, 100.0f, 99.4f, 99.6f},
        {99.6f, 100.0f, 99.3f, 99.7f},
        {99.7f, 100.0f, 99.5f, 99.9f},
        {99.9f, 100.0f, 99.6f, 99.7f},
        {99.7f, 100.0f, 99.5f, 99.8f},
        {99.8f, 100.0f, 99.6f, 99.9f},
        {99.9f, 100.0f, 99.7f, 99.8f},
        {99.8f, 100.0f, 99.6f, 99.7f},
        {99.7f, 100.0f, 99.5f, 99.9f},
        {99.9f, 100.0f, 99.7f, 99.8f},
        {99.8f, 100.0f, 99.6f, 99.7f},
        {99.7f, 100.0f, 99.5f, 99.9f},
        {99.9f, 100.0f, 99.7f, 99.8f},
        {99.8f, 100.0f, 99.6f, 99.7f},
        {99.7f, 100.0f, 99.5f, 99.9f},
        {99.9f, 100.0f, 99.7f, 99.8f},
        {99.8f, 100.0f, 99.6f, 99.7f},
        {99.7f, 100.0f, 99.5f, 99.9f}
    };

    CandleChart chart(std::move(candles), 1200, 900);

    sf::View view(sf::FloatRect(0, -900, 1200, 900));
    window.setView(view);

    sf::Vector2i lastMousePos; // Last mouse position, used for panning
    sf::Vector2f zoomLevel = { 1.0f, 1.0f }; // Zoom level, used for keeping track of zoom and adjusting panning speed accordingly

    // Main loop. Handles user input, draws the chart and candlesticks, updates the window
    while (window.isOpen())
    {
        // Handle user input
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Handle window close
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle zooming with mouse scroll
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                // Zoom in or out depending on scroll direction
                if (event.mouseWheelScroll.delta > 0) // Zoom in
                    view.zoom(0.9f);
                else // Zoom out
                    view.zoom(1.1f);

                // Update zoom level by dividing the current view size by the base window size
                auto& [viewX, viewY] = view.getSize();
                zoomLevel = { viewX / baseWindowSize.x, viewY / baseWindowSize.y };
                window.setView(view); // Update the window view
            }
        }

        // Handle panning with mouse drag
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            // If last mouse position is not 0, then pan the view
            sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);// Get current mouse position
            if (lastMousePos.x != 0 || lastMousePos.y != 0)
            {
                // Calculate the delta position and move the view
                sf::Vector2i deltaPos = lastMousePos - currentMousePos;
                sf::Vector2f deltaPosZoomed = { deltaPos.x * zoomLevel.x, deltaPos.y * zoomLevel.y }; // Adjust delta position by zoom level
                view.move(deltaPosZoomed); // Move the view
                window.setView(view); // Update the window view
            }
            lastMousePos = currentMousePos;
        }
        else // Reset last mouse position
        {
            lastMousePos.x = 0;
            lastMousePos.y = 0;
        }

        // Draw the chart and candlesticks
        window.clear();
        chart.draw(window);
        window.display();
    }

    return 0;
}
