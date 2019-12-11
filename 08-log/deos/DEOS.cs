using System;
using System.Text;
using System.Collections.Generic;
using System.Linq;

namespace DEOS
{

    public class DEOS
    {
        public static NewTimer theTimer;
        public static PeriodicClock thePeriodicClock;
        public static Clock systemClock;
        public static bool abstraction = false;
        public static string indent = "";
        public static string INC = "  ";

		
        public static void Inc()
        {
            //indent = INC + indent;
        }

        public bool Run()
        {
            Console.WriteLine("JAVA - DEOS\n");

            theTimer = new NewTimer();
            thePeriodicClock = new PeriodicClock(Registry.uSecsInFastestPeriod);
            systemClock = new Clock(thePeriodicClock, theTimer);

            DEOSKernel.ColdStartKernel();

            int result = DEOSKernel.CreateThreadK("user1", 0, 21, 1);

            result = DEOSKernel.CreateThreadK("user2", 0, 21, 1);

            int tickResult = Clock.NOINTERRUPTS;

            for (int i = 0; i < 1000; i++)
            {
                DEOS.println("****************************");
                DEOS.println("Current time: " + DEOS.systemClock.GetCurrentTime());

                DEOS.println(Scheduler.CurrentThread().ToString() + " is the current thread");

                tickResult = DEOS.systemClock.Ticks();

                Scheduler.CurrentThread().GetBody().Run(tickResult);
            }

            return true;
        }

        public static void println(string s)
        {
            Console.WriteLine(indent + s);
        }

        public static bool RandBool()
        {
            Random rand = new Random();
            if (rand.NextDouble() < 0.5)
                return true;
            else
                return false;
        }
    }
}
