#include <dirent.h>
#include <unistd.h>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() {
string line;
string key;
string value;
float memory_utilization = 0.0;
float memory_free;
float total_memory;

 std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value){
         if (key == "MemTotal:") {
          total_memory = std::stof(value);
        }
        else if (key == "MemFree:") {
          memory_free = std::stof(value);
        }
      }
    }
  }
  return memory_utilization = (total_memory - memory_free)/total_memory;
}
      




// TODO: Read and return the system uptime
long LinuxParser::UpTime() {
  long uptime{0}, idle_time{0};
  string line;
  std::ifstream filestream(kProcDirectory + kUptimeFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      linestream >> uptime >> idle_time;
    }
    return uptime;
  }
  return 0;  // Return default if file can't be opened
}
    

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() {
  vector<string> jiffies{CpuUtilization()};
  long total(0);

  if (jiffies.size() > 0) {
    // loop runs till 7 because the rest of the values after that are zero
    for (int i = 0; i <= 7; i++) {
      total += stol(jiffies[i]);
    }
  }
  return total;
}


// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {           // Line 131 - Function opens {
  string line;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatFilename);

  if (filestream.is_open()) {                        
    std::getline(filestream, line);
    std::istringstream linestream(line);

    
    vector<string> pid_vector;
    string temp;
    while (linestream >> temp) {
        pid_vector.push_back(temp);
    }

    long total_active_pid_jiffies{0};

    vector<int> active_jiffies_indexes{13, 14, 15, 16};

    for (int jiffie_index : active_jiffies_indexes) {
      total_active_pid_jiffies += stol(pid_vector[jiffie_index]);
    }
    return total_active_pid_jiffies;
  }                                                    
  return 0;                                           
} 

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return Jiffies() - IdleJiffies(); }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() {
  vector<string> jiffies{CpuUtilization()};
  if (jiffies.size() > 0) {
    long idle{stol(jiffies[3])};
    long i_owait{stol(jiffies[4])};
    return idle + i_owait;
  }
  return 0;
}

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
 string line;
  string key;
  string value;

 vector<string> cpu_utilization;
 std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key) {
        if (key == "cpu") {
          while (linestream >> value) {
            cpu_utilization.push_back(value);
          }
          return cpu_utilization;
        }
      }
    }
  }  return cpu_utilization;
}
  

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() {
  string line;
  string key;
  string value;
  int total_process;
  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          total_process = std::stoi(value);
          return total_process;
        }
      }
    }
  }
  return total_process;
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  string line;
  string key;
  string value;
  int running_processes;
  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          running_processes = std::stoi(value);
          return running_processes;
        }
      }
    }
  }
  return running_processes;
}

// TODO: Read and return the command associated with a process

string LinuxParser::Command(int pid) { 
  string line;
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line, '\0'); // Delimiter is null character
  }

  return line; 
}
// TODO: Read and return the memory used by a process

string LinuxParser::Ram(int pid) { 
  string line, key, value;
  
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatusFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") {
          return value;    
        }
      }
    }
  }
  return value;
}


// TODO: Read and return the user ID associated with a process

string LinuxParser::Uid(int pid) { 
  string line, key, value;
  
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatusFilename);
  if (filestream.is_open()) {
    while(std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;    
        }
      }
    }
  }
  return value;
}


// TODO: Read and return the user associated with a process

string LinuxParser::User(int pid) { 
  string line, user, uid, key, value;
  
  uid = Uid(pid);
  std::ifstream filestream(kPasswordPath);
  
  if (filestream.is_open()) {
    while (getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> key >> value;
      if (value == uid) {
        return user;
      }
    }
  }
  return user;
 }

// TODO: Read and return the uptime of a process
long LinuxParser::UpTime(int pid) { 
  string line;
  string key;
  long uptime{0};
  
  int i = 0;
  
  std::ifstream filestream(LinuxParser::kProcDirectory + to_string(pid) + LinuxParser::kStatFilename);
  if(filestream.is_open()) {
    while(filestream >> key)
    {
        if(i == 21)
      {
        uptime = UpTime() - stof(key)/sysconf(_SC_CLK_TCK);
        return uptime;
      }
    i += 1;
    }
  }
  return uptime;

}


