/**
 * @file processor.h
 * @brief CPU utilization for the system monitor.
 */

#ifndef PROCESSOR_H
#define PROCESSOR_H

/**
 * @brief Represents the aggregate CPU utilization of the system.
 */
class Processor {
 public:
  /**
   * @brief Returns current CPU utilization as a fraction (0.0 to 1.0).
   * @return CPU utilization from /proc/stat.
   */
  float Utilization();

 private:
  int pid_;  /**< Unused; kept for potential per-CPU support. */
};

#endif