#ifndef TIMER_H
#define TIMER_H

#include <chrono>

using namespace std::chrono;

/** This class facilitates timing */
class Timer
{
    std::chrono::high_resolution_clock::time_point create;
    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;
    double last_sec;
    double cum_sec;
    int ntimes;

    public:
        Timer(): create(high_resolution_clock::now()),
            begin(create), last_sec(0), cum_sec(0), ntimes(0) {}

        void add_time(double x) { cum_sec+=last_sec=x; ntimes++; }
        void start()  { begin=high_resolution_clock::now(); }
        void stop()  { end=high_resolution_clock::now(); add_time(sec()); }
        void reset() { last_sec=cum_sec=0; ntimes=0; }
        void reset_last() { last_sec=0; }

        double sec() const {
            duration<double> span=
                duration_cast<duration<double> > (end-begin);
            return span.count();
        }

        double get_last() const { return last_sec; }
        double get_total() const { return cum_sec; }
};

#endif
