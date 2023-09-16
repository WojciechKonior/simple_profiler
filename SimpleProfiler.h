#ifndef SIMPLEPROFILER_H
#define SIMPLEPROFILER_H

#include <chrono>
#include <vector>
#include <map>

#define profile() Timer timer(__FUNCTION__)
#define profile_info Timer::get_profile_info()

struct Timer
{
    static std::map<std::string, std::vector<double>> mp;

    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point stop;
    std::chrono::duration<double> duration;
    std::string function_name;

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
        mp[function_name].push_back(time_span);
    }

    static std::string get_profile_info()
    {
        std::string str;
        for(auto& [key, value]: mp)
            str.append(key).append(": ").append(std::to_string(value[0]));

        return str;
    }
};

std::map<std::string, std::vector<double>> Timer::mp = {};

#endif
