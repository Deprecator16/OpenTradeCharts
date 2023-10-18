/**
 *@file      ChronoDefinitions.h
 *@brief     File contains the project definitions related to the std::chrono library
 *@details   Definitions for the following types: Date, Time, Duration, Clock, TimePoint
 *@author    Bassil Virk
 *@date      11.10.2023
 *@copyright © Bassil Virk, 2023. All right reserved.
 */
#pragma once
#include <chrono>

using Date = std::chrono::year_month_day;
using Time = std::chrono::hh_mm_ss<std::chrono::seconds>;
using Duration = std::chrono::duration<long long>;
using Clock = std::chrono::system_clock;
using TimePoint = std::chrono::time_point<Clock, Duration>;
