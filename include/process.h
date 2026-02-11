/**
 * @file process.h
 * @brief Process representation for the system monitor.
 */

#ifndef PROCESS_H
#define PROCESS_H

#include <string>

/**
 * @brief Represents a single running process with CPU, memory, and metadata.
 */
class Process {
 public:
  /**
   * @brief Constructs a Process for the given PID.
   * @param pid Process ID.
   */
  Process(int pid);
  /** @brief Returns the process ID. */
  int Pid() const;
  /** @brief Returns the username owning the process. */
  std::string User();
  /** @brief Returns the command line of the process. */
  std::string Command();
  /** @brief Returns CPU utilization (0.0 to 1.0 or higher). */
  float CpuUtilization() const;
  /** @brief Returns RAM usage in MB. */
  std::string Ram();
  /** @brief Returns process uptime in seconds. */
  long int UpTime() const;
  /**
   * @brief Less-than comparison for sorting by CPU utilization.
   * @param a Another Process to compare.
   * @return true if this process has higher CPU utilization.
   */
  bool operator<(Process const& a) const;

 private:
  int pid_;  /**< Process ID. */
};

#endif