using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    public class NewTimer
    {
        int startingTime = 0; // Time on the clock when timer was started
        int setTime = 0; // Timer is set to this time
        int stoppingTime = 0; // Time on clock when timer should stop
        bool isStarted = false;
        bool timeOut = false;
        bool isInterrupted = false;

        public NewTimer()
        {
        }

        public int GetRemainingTime(int currentTime)
        {
            int remainingTime = stoppingTime - currentTime;

            return remainingTime;
        }

        public int GetSetTime()
        {
            return setTime;
        }

        public int GetStoppingTime()
        {
            return stoppingTime;
        }

        public bool IsTimeOut()
        {
            if (timeOut)
            {
                isStarted = false;
            }
            return timeOut;
        }

        public void SetTimer(int setTimeIn, int startingTimeIn)
        {
            startingTime = startingTimeIn;
            setTime = setTimeIn;
            stoppingTime = startingTime + setTime;
            isStarted = true;
            isInterrupted = false;
            timeOut = false;
        }

        public void ClearTimeOut()
        {
            timeOut = false;
        }

        public void ClockTicks(int currentTime)
        {
            if (stoppingTime == currentTime)
            {
                timeOut = true;
            }
        }

        public void InterruptTimer()
        {
            isStarted = false;
            isInterrupted = true;
        }
    }
}
