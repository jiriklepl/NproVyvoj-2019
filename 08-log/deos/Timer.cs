using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class Timer
    {
        const int uSecsPeriod = Registry.uSecsInFastestPeriod;
        static int       Start_time = 0; // time 'requested' by thread and 'written to timer'
        static int       Remaining_time = 0;
        static int       Used_time = 0;

        static bool tick = false;
        static bool timer = false;

        public Timer () 
        { }

        public static void ClearInterrupts () 
        {
            timer = false;
            tick = false;
        }

        public int TimeRemaining()
        {
            int used_in_period = 0; // how much time did thread use
            int time_to_eop = uSecsPeriod - Used_time; // time left in period

            // if tick and timer are still set, then you know they happended -
            // they are (should be) cleared by the threads otherwise
            if (tick)
            { // used all the time to eop OR no time
                used_in_period = time_to_eop;
            }
            else if (timer)
            { // used all the time OR no time
                used_in_period = Start_time;
            }
            else if (time_to_eop <= Start_time)
            {
                DEOS.Inc();
                if (!DEOS.RandBool())
                { // used all the time to eop OR no time
                    used_in_period = time_to_eop;
                }
                else
                {
                    used_in_period = 0;
                }
            }
            else
            { // time_to_eop > Start_time, i.e. use Start_time for calculations
                DEOS.Inc();

                if (DEOS.RandBool())
                {
                    used_in_period = Start_time;
                }
                else
                {
                    used_in_period = 0;
                }
            }

            Used_time += used_in_period;

            if (tick)
            {
                Used_time = 0; // this is to help the invariant...
            }
            ClearInterrupts();
            Remaining_time = Start_time - used_in_period;
            return Remaining_time;
        }

        public void Write (int delayInMicroseconds) 
        {
            Start_time = delayInMicroseconds;

            if ((Start_time + Used_time) >= uSecsPeriod) 
            {
                tick = true; // tick may happen
            } 
            else if ((Start_time + Used_time) < uSecsPeriod) 
            {
                timer = true;
            } 
            else 
            {
                DEOS.println("Timer ERROR - this case should not happen");
            }
        }
    }
}
