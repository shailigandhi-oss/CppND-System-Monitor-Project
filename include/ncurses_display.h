/**
 * @file ncurses_display.h
 * @brief NCurses-based display for the system monitor.
 */

#ifndef NCURSES_DISPLAY_H
#define NCURSES_DISPLAY_H

#include <curses.h>

#include "process.h"
#include "system.h"

/**
 * @brief NCurses display utilities for rendering the system monitor UI.
 */
namespace NCursesDisplay {
/**
 * @brief Displays the full system monitor (system info and top processes).
 * @param system System object with data to display.
 * @param n Number of processes to show (default: 10).
 */
void Display(System& system, int n = 10);
/**
 * @brief Displays system information in the given window.
 * @param system System object with data to display.
 * @param window NCurses window to draw into.
 */
void DisplaySystem(System& system, WINDOW* window);
/**
 * @brief Displays the process list in the given window.
 * @param processes Vector of processes to display.
 * @param window NCurses window to draw into.
 * @param n Maximum number of processes to show.
 */
void DisplayProcesses(std::vector<Process>& processes, WINDOW* window, int n);
/**
 * @brief Creates a text-based progress bar.
 * @param percent Value from 0.0 to 1.0.
 * @return String representation of the progress bar.
 */
std::string ProgressBar(float percent);
}  // namespace NCursesDisplay

#endif