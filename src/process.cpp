#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"


using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
Process::Process(int pid) : pid_{pid} {}
int Process::Pid() const {
  if (!pid_) {
    throw "Process pid is missing";
  }
  return pid_;
}
// TODO: Return this process's CPU utilization

float Process::CpuUtilization() const {
  long HERTZ{sysconf(_SC_CLK_TCK)};
  return static_cast<float>(LinuxParser::ActiveJiffies(Pid())) / HERTZ /
         UpTime();
}

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(Pid()); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(Pid()); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() const {
  long HERTZ{sysconf(_SC_CLK_TCK)};
  return LinuxParser::UpTime() - LinuxParser::UpTime(Pid()) / HERTZ;
}


// TODO: Overload the "less than" comparison operator for Process objects
bool Process::operator<(Process const& a) const {
  return CpuUtilization() > a.CpuUtilization();
}