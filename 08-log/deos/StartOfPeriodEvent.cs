using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class StartOfPeriodEvent
    {
        static StartOfPeriodEvent[] periodicEvents;
        int itsPeriodId;
        int itsPassCount;
        public int countDown;
        int itsPeriodIndex;
        ThreadList itsWaitingThreads;
        StartOfPeriodEvent itsSuccessor;

        private StartOfPeriodEvent(int thePeriodIndex, int thePassCount)
        {
            itsPassCount = thePassCount;
            itsPeriodIndex = thePeriodIndex;
            itsWaitingThreads = new ThreadList();

            countDown = 1;
            itsPeriodId = 0;
            itsSuccessor = null;
        }

        public int CurrentPeriod()
        {
            return itsPeriodId;
        }

        public static StartOfPeriodEvent EventForPeriodIndex(int i)
        {
            return periodicEvents[i];
        }

        public static void Initialize()
        {
            //System.out.println("StartOfPeriodEvent.Initialize");
            int numPeriods = Registry.numPeriods;


            //SPIN Registry::numberOfPeriodsSupported();
            periodicEvents = new StartOfPeriodEvent[numPeriods];

            int ticksInLastPeriod = 1;

            for (int i = 0; i < numPeriods; i++)
            {
                int ticksInThisPeriod = Registry.PeriodDurationInSystemTicks(i);
                periodicEvents[i] = new StartOfPeriodEvent(i,
                                                           ticksInThisPeriod / ticksInLastPeriod);
                if (i > 0)
                {
                    periodicEvents[i - 1].itsSuccessor = periodicEvents[i];
                }
                ticksInLastPeriod = ticksInThisPeriod;
            }

        }

        public void MakeThreadWait(Thread theThread)
        {
            itsWaitingThreads.AddAtEnd(theThread.startOfPeriodWaitNode);
        }

        public void PulseEvent(int systemTickCount)
        {
            countDown = countDown - 1;

            if (countDown == 0)
            {
                itsPeriodId = (itsPeriodId + 1) % 2; /////!!!!!!!


                //startOfPeriodTickValues[itsPeriodIndex] = systemTickCount;
                countDown = itsPassCount;
                Scheduler.RunnableList().MergeList(itsWaitingThreads);

                if (itsSuccessor != null)
                {
                    itsSuccessor.PulseEvent(systemTickCount);
                }
            }
        }
    }
}
