using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    public class PeriodicClock
    {
        int microSecsPeriod = 0;
        int usedTime = 0;
        int startingPeriodTime = 0;
        bool systemInterrupt = false;
        int special_case_usedTime = 0; // used to get correct value when systemtick can happen, but doesn't 

        public PeriodicClock(int periodIn)
        {
            microSecsPeriod = periodIn;
        }

        public bool IsInterrupted()
        {
            return systemInterrupt;
        }

        public int GetPeriod()
        {
            return microSecsPeriod;
        }

        public int GetTimeToEOP()
        {
            return microSecsPeriod - usedTime;
        }

        public void SetUsedTime(int usedTimeIn)
        {
            usedTime = usedTimeIn;
        }

        public int GetUsedTime()
        {
            if (systemInterrupt)
            {
                return special_case_usedTime;
            }

            return usedTime;
        }

        public void ClearInterrupt()
        {
            systemInterrupt = false;
            ResetUsedTime();
        }

        public void ClockTicks(int currentTime)
        {
            usedTime = currentTime % microSecsPeriod;

            if (usedTime == 0)
            {
                special_case_usedTime = microSecsPeriod;
                systemInterrupt = true;
                startingPeriodTime = currentTime;
            }
        }

        public void ResetUsedTime()
        {
            special_case_usedTime = usedTime;
        }
    }
}
