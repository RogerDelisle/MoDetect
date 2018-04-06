#ifndef SIGNALATOM_H
#define SIGNALATOM_H

#include <ctime>
#include <ratio>
#include <chrono>
#include <string>

using namespace std::chrono;
using namespace std;

typedef duration<long long, std::micro>  TimedPointDuration;
typedef long long TimeUnit;

// using namespace std;

class SignalAtom
{
    double                  freq;
    TimedPointDuration      duration;
    double                  tolerance;

public:
                    SignalAtom(double, TimedPointDuration, double);
                    SignalAtom() : freq(0.0),
                        duration(0), tolerance(0.0005) {}
                    SignalAtom(const SignalAtom& other) : freq(other.freq),
                        duration(other.duration), tolerance(other.tolerance) {}
    SignalAtom&     operator=(const SignalAtom& other) = default;
    bool            operator ==(SignalAtom&);
    bool            operator < (const SignalAtom &) const;
    char*           GetValueString(char* strout);
    double          GetFreq() { return freq; }

};

#endif // SIGNALATOM_H
