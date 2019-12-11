using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class DEOSThread
    {
        public Thread thread; // which "Thread" object is this Thread one related to
        bool running = false;

        // run at a time
        bool isMain = false;
        bool isIdle = false;
        bool firstTime = true;
        bool setDelete = false;
        bool setWaitUntilNextPeriod = false;

        public DEOSThread(Thread th) 
        {
            thread = th;
            isIdle = thread.IsIdle();
            isMain = thread.IsMain();

            DEOS.println(thread.ToString() + " created");
        }

        public void Run(int tickResult)
        {
            //Verify.assertTrue(Timer.timer || Timer.tick);
            DEOS.Inc();

            if (tickResult == Clock.NOTIMECHANGE)
            {
                if (DEOS.RandBool())
                {
                    //System.out.println("Thread: " + thread + " - Depth: " + depth);
                    DEOS.println("No interrupt - Choice 0:");
                    DEOS.println(thread.ToString() + " waiting until next period");
                    DEOSKernel.WaitUntilNextPeriodK(thread);

                    //yieldCPU();
                }
                else
                {
                    //System.out.println("Thread: " + thread + " - Depth: " + depth);
                    DEOS.println("No interrupt - Choice 1:");
                    DEOS.println(thread.ToString() + " deleting");
                    DEOSKernel.DeleteThreadK(thread); //deleteThread();
                }
            }
            else
            {
                Random rand = new Random();
                switch (rand.Next(2))
                {
                    case 0:

                        //System.out.println("Thread: " + thread + " - Depth: " + depth);
                        DEOS.println("Choice 0:");
                        DEOS.println(thread.ToString() + " waiting until next period");
                        DEOSKernel.WaitUntilNextPeriodK(thread);

                        //yieldCPU();	   
                        break;

                    case 2:

                        //System.out.println("Thread: " + thread + " - Depth: " + depth);
                        DEOS.println("Choice 2:");
                        DEOS.println(thread.ToString() + " deleting");
                        DEOSKernel.DeleteThreadK(thread);

                        //deleteThread();
                        break;

                    case 1:

                        //System.out.println("Thread: " + thread + " - Depth: " + depth);
                        DEOS.println("Choice 1: ");
                        GetInterrupted(tickResult);

                        break;
                }
            }
        }

        public void GetInterrupted(int tickResult)
        {
            if (tickResult == Clock.SYSTEMINTERRUPT)
            {
                DEOS.println(thread.ToString() + " interrupted by system tick");
                DEOS.thePeriodicClock.ResetUsedTime();
                Scheduler.HandleSystemTickInterrupt();
            }
            else if (tickResult == Clock.TIMEOUT)
            {
                DEOS.println(thread.ToString() + " interrupted by timer");
                Scheduler.HandleTimerInterrupt();
            }
            else
            {
                DEOS.println(thread.ToString() + " waiting for time to pass");
            }
        }
    }
}
