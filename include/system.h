/**
 * @file system.h
 * @brief System aggregate view for the monitor.
 */

#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

/**
 * @brief Aggregates CPU, memory, kernel, and process data for display.
 */
class System {
 public:
  /** @brief Reference to the CPU processor. */
  Processor& Cpu();
  /** @brief Reference to the list of processes. */
  std::vector<Process>& Processes();
  /** @brief Memory utilization as a fraction (0.0 to 1.0). */
  float MemoryUtilization();
  /** @brief System uptime in seconds. */
  long UpTime();
  /** @brief Total number of processes. */
  int TotalProcesses();
  /** @brief Number of running processes. */
  int RunningProcesses();
  /** @brief Kernel version string. */
  std::string Kernel();
  /** @brief Operating system name. */
  std::string OperatingSystem();

 private:
  Processor cpu_ = {};           /**< CPU utilization data. */
  std::vector<Process> processes_ = {};  /**< Process list. */
};

#endif