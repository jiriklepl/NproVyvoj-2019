using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    public class Clock
    {
        public static int TIME_CONSTRAINT = Registry.numPeriods * 20 * 2; // numPeriods is usually 3
        public static int NOINTERRUPTS = 0;
        public static int TIMEOUT = 1;
        public static int SYSTEMINTERRUPT = 2;
        public static int NOTIMECHANGE = 3;
        int currentTime = -20;
        PeriodicClock clockToNotify; // may use a list in another version
        NewTimer timerToNotify; // if there are more than two clocking devices
        bool eventDriven = false;

        public Clock(PeriodicClock periodicIn, NewTimer timerIn)
        {
            if (DEOS.abstraction)
            {
                currentTime = -20;
            }
            else
            {
                currentTime = -1;
            }

            clockToNotify = periodicIn;
            timerToNotify = timerIn;
        }

        public int GetCurrentTime()
        {
            return currentTime;
        }

        public void SetTimer(int timeIn)
        {
            timerToNotify.SetTimer(timeIn, currentTime);
        }

        public void ClearInterrupts()
        {
            clockToNotify.ClearInterrupt();
            timerToNotify.ClearTimeOut();
        }

        public int Ticks()
        {
            ClearInterrupts();

            int delta;

            if (!DEOS.abstraction)
            {
                delta = 1;
            }
            else
            {
                int timeToEOP = (clockToNotify.GetTimeToEOP());
                int timeOutTime = (timerToNotify.GetStoppingTime());
                int timeToTimeOut = (timeOutTime - currentTime);

                if (DEOS.RandBool())
                {
                    delta = 0;
                }
                else
                {
                    if (timeToEOP <= timeToTimeOut)
                    {
                        delta = timeToEOP;
                    }
                    else
                    {
                        delta = timeToTimeOut;
                    }
                }
            }

            if (delta == 0)
            {
                return NOTIMECHANGE;
            }
            else
            {
                if ((currentTime + delta) > TIME_CONSTRAINT)
                {
                    return NOTIMECHANGE;
                }

                currentTime = (currentTime + delta);
                clockToNotify.ClockTicks(currentTime);
                timerToNotify.ClockTicks(currentTime);

                if (clockToNotify.IsInterrupted())
                {
                    timerToNotify.InterruptTimer();

                    return SYSTEMINTERRUPT;
                }
                else if (timerToNotify.IsTimeOut())
                {
                    return TIMEOUT;
                }
                else
                {
                    return NOINTERRUPTS;
                }
            }
        }
    }
}
