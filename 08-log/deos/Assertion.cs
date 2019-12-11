using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class Assertion
    {
        static Thread[] allThreads = new Thread[4];
        static int[] total_time = new int[2];
        static int num_entries = 0;

        public static void AddThread(Thread t)
        {
            //allThreads.add(t);
            allThreads[num_entries] = t;
            num_entries++;
        }

        public static bool Check()
        {
            total_time[0] = 0;
            total_time[1] = 0;

            Thread current;

            for (int i = 0; i < num_entries; i++)
            {
                current = allThreads[i];

                if (current != Scheduler.IdleThread())
                {
                    int cp = current.itsPeriodicEvent.CurrentPeriod();

                    if ((current.itsLastExecution == cp) &&
                            (current.itsLastCompletion != cp))
                    {
                        total_time[1] += current.itsCurrentBudget.RemainingBudgetInUsec();

                        if (current.itsPeriodIndex == 0)
                        {
                            total_time[0] += current.itsCurrentBudget.RemainingBudgetInUsec();
                        }
                    }
                    else if (current.itsLastExecution != cp)
                    {
                        total_time[1] += current.itsCurrentBudget.TotalBudgetInUsec();

                        if (current.itsPeriodIndex == 0)
                        {
                            total_time[0] += current.itsCurrentBudget.TotalBudgetInUsec();
                        }
                    }

                    if (current.itsPeriodIndex == 0)
                    {
                        int tmp = (current.itsCurrentBudget.TotalBudgetInUsec()) * (StartOfPeriodEvent.EventForPeriodIndex(1).countDown - 1);
                        total_time[1] += tmp;
                    }
                }
            }

            int period_count = StartOfPeriodEvent.EventForPeriodIndex(1).countDown - 1;

            int current_period = StartOfPeriodEvent.EventForPeriodIndex(1).CurrentPeriod();

            if (Scheduler.CurrentThread() != Scheduler.IdleThread())
            {
                int remaining = ((Registry.uSecsInFastestPeriod * period_count) +
                                Registry.uSecsInFastestPeriod) -
                                DEOS.thePeriodicClock.GetUsedTime();

                if (total_time[1] > remaining)
                {
                    DEOS.println("Ooops: Time wanted " + total_time[1] + " > " + remaining);
                    throw new Exception("error found");
                }
                else
                {
                }
            }

            total_time[0] = 0;
            total_time[1] = 0;

            return true;
        }

        public static void RemoveThread(Thread t)
        {
            for (int i = 0; i < num_entries; i++)
            {
                if (allThreads[i] == t)
                {
                    for (int j = i + 1; j < num_entries; j++)
                    {
                        allThreads[j - 1] = allThreads[j];
                    }

                    num_entries--;
                    return;
                }
            }
        }
    }
}
