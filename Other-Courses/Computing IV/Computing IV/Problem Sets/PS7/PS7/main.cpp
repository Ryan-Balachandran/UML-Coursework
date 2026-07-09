#include <boost/regex.hpp>
#include <boost/date_time.hpp>
#include <exception>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/posix_time/posix_time.hpp"

using namespace std;  // NOLINT
using namespace boost;  // NOLINT

using boost::gregorian::date;
using boost::gregorian::from_simple_string;
using boost::gregorian::date_period;
using boost::gregorian::date_duration;

using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::posix_time::duration_from_string;

void append(string &name)
{
    name += ".rpt";
}

void parse(string fn)
{
    int line_number = 0;
    bool failed_boot = false;
    
    string log, filename, line, boot_start, boot_complete, temp, boottime;
    string time1, time2;
    
    log = fn;
    append(fn);
    
    boottime = "Boot Time: ";
    
    boot_start = ".*log.c.166.*";  // boot up start
    boot_complete = ".*oejs.AbstractConnector:Started SelectChannelConnector.*";  // boot up complete
    
    std::fstream outfile;
    outfile.open(fn.c_str(), fstream::out);
    
    string match_time = "(\\d{2}):(\\d{2}):(\\d{2})";
    string match_date = "(\\d{4})-(\\d{2})-(\\d{2})";
    
    std::ifstream infile(log.c_str());
    
    smatch start_time, end_time, start_date, end_date;
    
    regex e = regex(boot_start);
    regex ea = regex(boot_complete);
    
    regex elapsed_time(match_time);
    regex getdate(match_date);
    regex getdatea(match_date);
    
    std::ostringstream ss;
    
    // search through log file
    while(getline(infile, line))
    {
        line_number++;
        
        if(regex_match(line, e))  // boot start match found
        {
            if(failed_boot == true)  // boot start match found again - failed
            {
                outfile << "**** Incomplete boot ****\n\n";
                failed_boot = false;
                outfile << "\n";
            }
            
            outfile << "=== Device boot ===\n";
            
            regex_search(line, start_time, elapsed_time);  // search for the time with boot start
            regex_search(line, start_date, getdate);  // search for the date with boot start
            
            time1 = start_time[0];
            
            ss.str("");
            ss << line_number;
            
            temp = ss.str();
            temp += "(" + log + "): ";
            temp += start_date[0] + " " + start_time[0] + " Boot Start \n";
            
            outfile << temp;
            failed_boot = true;
            temp.clear();
        }
        
        if(regex_match(line, ea))  // boot complete match found - success
        {
            regex_search(line, end_time, elapsed_time);  // search for the time with boot complete
            regex_search(line, end_date, getdatea);  // search for the date with boot start
            
            time2 = end_time[0];
            
            ss.str("");
            ss << line_number;
            
            temp = ss.str();
            temp += "(" + log + "): ";
            temp += end_date[0] + " " + end_time[0] + " Boot Complete \n";
            
            outfile << temp;
            
            time_duration t1(duration_from_string(time1));
            time_duration t2(duration_from_string(time2));
            
            time_duration td = t2 - t1;
            
            ss.str("");
            ss << td.total_milliseconds();
            
            outfile << "\t" + boottime + ss.str() + "ms\n\n";
            
            failed_boot = false;
            temp.clear();
        }
    }
    
    outfile.close();
}

int main(int argc, char *argv[])
{
    string filename;
    
    filename = argv[1];  // get log file from command line
    
    if(filename.size() < 1)
        throw std::runtime_error("Null string for file name");
    
    parse(filename);
    
    return 0;
}
