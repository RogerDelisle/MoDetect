#include "signalatom.h"
#include <cmath>

SignalAtom::SignalAtom(double freq, TimedPointDuration duration, double tolerance = 0.0005) :
    freq(freq), duration(duration), tolerance(tolerance)
{

}

bool SignalAtom::operator ==(SignalAtom& other)
{
    double fr_tol_value = (double)(abs(other.freq) > abs(freq) ? other.freq : freq) * tolerance;
    TimedPointDuration bigger_dur = other.duration > duration ?
                                         other.duration : duration;
    TimeUnit&& dur_tol_value = (TimeUnit)((double)bigger_dur.count() * tolerance);
    TimeUnit&& thistimecnt = duration.count();
    TimeUnit&& othertimecnt = other.duration.count();

    return (other.freq > (freq - fr_tol_value) && (other.freq < (freq + fr_tol_value))
            && (othertimecnt > (thistimecnt - dur_tol_value)) &&
            (othertimecnt < (thistimecnt + dur_tol_value)));
}

bool SignalAtom::operator < (const SignalAtom& other) const
{
    double&& rrfreq = abs(freq);
    double&& rrofreq = abs(other.freq);
    TimedPointDuration&& rrdur = abs(duration);
    TimedPointDuration&& rrodur = abs(other.duration);
    double fr_tol_value = (double)(rrofreq > rrfreq ? rrofreq : rrfreq) * tolerance;
    TimedPointDuration bigger_dur = rrodur > rrdur ?
                                         rrodur : rrdur;
    TimeUnit&& dur_tol_value = (TimeUnit)((double)bigger_dur.count() * tolerance);
    TimeUnit&& thistimecnt = duration.count();
    TimeUnit&& othertimecnt = other.duration.count();

    if (freq < (other.freq - fr_tol_value))
        return true;
    if (freq > (other.freq + fr_tol_value))
        return false;
    if (thistimecnt < (othertimecnt - dur_tol_value))
        return true;
    if (thistimecnt > (othertimecnt + dur_tol_value))
        return false;

    return false;
}

char* SignalAtom::GetValueString(char *strout)
{
    sprintf(strout, "%1.3f Hz\n%lld us", freq, duration.count());
    return strout;
}


/*
SignalAtom& SignalAtom::operator = (const SignalAtom& other) :
    freq(other.freq), duration(other.duration), tolerance(other.tolerance)
{
    return *this;
}
*/
