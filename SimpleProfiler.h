#ifndef SIMPLEPROFILER_H
#define SIMPLEPROFILER_H

#include <string>
#include <chrono>
#include <vector>
#include <map>
#include <tuple>

#define profile() Timer timer(__FUNCTION__)
#define profile_summary Timer::get_profile_summary()
#define profile_details Timer::get_profile_details()

class Timer
{
private:
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point stop;
    std::chrono::duration<double> duration;
    std::string function_name;
    
    static std::map<std::string, std::pair<double, std::vector<double>>> summary_map;

public:

    Timer() = delete;
    Timer(const std::string& func)
    {
        start = std::chrono::high_resolution_clock::now();
        function_name = func;
    }
    ~Timer()
    {
        stop = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::duration<double>>(stop - start);

        double time_span = duration.count()*1e3;
        summary_map[function_name].first += time_span;
        summary_map[function_name].second.push_back(time_span);
    }

    static void reset() { summary_map.clear(); }

    static std::string get_profile_summary()
    {
        std::string str;
        for(auto& [key, value]: summary_map)
        {
            str.append(key).append(": called ")
                .append(std::to_string(value.second.size()) + " times with overall duration of ")
                .append(std::to_string(value.first) + " us\n");
        }

        return str;
    }

    static std::string get_profile_details()
    {
        std::string str;
        for(auto& [key, value]: summary_map)
        {
            str.append(key).append(": called ")
                .append(std::to_string(value.second.size()) + " times with overall duration of ")
                .append(std::to_string(value.first) + " us\n");

            for(size_t i = 0; i<value.second.size(); i++)
                str.append(" " + std::to_string(i+1))
                    .append(":\t" + std::to_string(value.second[i]))
                    .append(" us\n");
            str.append("\n");
        }

        return str;
    }

    static std::map<std::string, std::pair<double, std::vector<double>>>& get_summary_map()
    {
        return summary_map;
    }
};

std::map<std::string, std::pair<double, std::vector<double>>> Timer::summary_map = {};

#endif
