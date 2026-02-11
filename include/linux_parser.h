/**
 * @file linux_parser.h
 * @brief Linux system information parser using /proc filesystem.
 */

#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>
#include <vector>

/**
 * @brief Parser for Linux system and process information from /proc.
 */
namespace LinuxParser {
/** @brief Path to the /proc filesystem. */
const std::string kProcDirectory{"/proc/"};
/** @brief Filename for command line in process directory. */
const std::string kCmdlineFilename{"/cmdline"};
/** @brief Filename for CPU info. */
const std::string kCpuinfoFilename{"/cpuinfo"};
/** @brief Filename for process status. */
const std::string kStatusFilename{"/status"};
/** @brief Filename for process/CPU statistics. */
const std::string kStatFilename{"/stat"};
/** @brief Filename for system uptime. */
const std::string kUptimeFilename{"/uptime"};
/** @brief Filename for memory info. */
const std::string kMeminfoFilename{"/meminfo"};
/** @brief Filename for kernel version. */
const std::string kVersionFilename{"/version"};
/** @brief Path to OS release file. */
const std::string kOSPath{"/etc/os-release"};
/** @brief Path to passwd file for user lookup. */
const std::string kPasswordPath{"/etc/passwd"};

/** @brief Memory utilization as a fraction (0.0 to 1.0). */
float MemoryUtilization();
/** @brief System uptime in seconds. */
long UpTime();
/** @brief List of all process IDs. */
std::vector<int> Pids();
/** @brief Total number of processes. */
int TotalProcesses();
/** @brief Number of running processes. */
int RunningProcesses();
/** @brief Operating system name from os-release. */
std::string OperatingSystem();
/** @brief Kernel version string. */
std::string Kernel();

/**
 * @brief CPU state indices in /proc/stat.
 */
enum CPUStates {
  kUser_ = 0,   /**< User time. */
  kNice_,       /**< Nice time. */
  kSystem_,     /**< System time. */
  kIdle_,       /**< Idle time. */
  kIOwait_,     /**< I/O wait time. */
  kIRQ_,        /**< IRQ time. */
  kSoftIRQ_,    /**< Soft IRQ time. */
  kSteal_,      /**< Steal time. */
  kGuest_,      /**< Guest time. */
  kGuestNice_   /**< Guest nice time. */
};
/** @brief CPU utilization values for each state. */
std::vector<std::string> CpuUtilization();
/** @brief Total jiffies (clock ticks). */
long Jiffies();
/** @brief Active jiffies (non-idle). */
long ActiveJiffies();
/** @brief Active jiffies for a specific process. */
long ActiveJiffies(int pid);
/** @brief Idle jiffies. */
long IdleJiffies();

/** @brief Command line for process pid. */
std::string Command(int pid);
/** @brief RAM usage in MB for process pid. */
std::string Ram(int pid);
/** @brief User ID for process pid. */
std::string Uid(int pid);
/** @brief Username for process pid. */
std::string User(int pid);
/** @brief Uptime in seconds for process pid. */
long int UpTime(int pid);
}  // namespace LinuxParser

#endif