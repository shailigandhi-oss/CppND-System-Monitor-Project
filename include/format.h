/**
 * @file format.h
 * @brief String formatting utilities for the system monitor.
 */

#ifndef FORMAT_H
#define FORMAT_H

#include <string>

/**
 * @brief Formatting utilities for display strings.
 */
namespace Format {
/**
 * @brief Converts elapsed time in seconds to HH:MM:SS format.
 * @param times Elapsed time in seconds.
 * @return Formatted string in HH:MM:SS format.
 */
std::string ElapsedTime(long times);
}  // namespace Format

#endif