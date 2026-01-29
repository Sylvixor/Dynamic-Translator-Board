#pragma once
#include <chrono>
#include <stdio.h>
#include <iostream>

namespace sw
{

    struct DurationCaster
    {
        template<typename ToDuration, typename FromDuration>
        constexpr ToDuration operator()(ToDuration, FromDuration fromDuration) const
        {
            return std::chrono::duration_cast<ToDuration>(fromDuration);
        }
    };



    template <typename ClockType>

    class stopwatch_base
    {
    public:
        using clock_type = ClockType;
        using duration = typename clock_type::duration;
        using time_point = typename clock_type::time_point;

        stopwatch_base()
             : start_(clock_type::now())
        {}

        void reset()
        {
            start_ = clock_type::now();
        }

        int elapsed() const{    //returns elapsed time in seconds

            std::chrono::nanoseconds nanosec = clock_type::now() - start_;
            // typedef std::chrono::seconds sec;
            std::chrono::seconds sec = std::chrono::duration_cast<std::chrono::seconds>(nanosec);

            return sec.count();
        }

        duration result() const
        {
            std::cout << "flag1" << std::endl;
            return clock_type::now() - start_;
        }

        template<typename Duration>
        Duration result() const
        {
            std::cout << "flag2" << std::endl;
            return DurationCaster()(Duration(), result());
        }

        

        template<typename Duration>
        operator Duration() const
        {
            std::cout << "flag3" << std::endl;
            return result<Duration>();
        }

    private:
        time_point start_;
    };

}