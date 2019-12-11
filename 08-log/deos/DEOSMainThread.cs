using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class DEOSMainThread : DEOSThread
    {
        public DEOSMainThread(Thread t): base(t)
        { }

        public void Run(int tickResult)
        {
            DEOS.Inc();

            if (tickResult == Clock.NOTIMECHANGE)
            {
                DEOS.println("No interrupts!");
                DEOS.println(thread.ToString() + " waiting until next period");
                DEOSKernel.WaitUntilNextPeriodK(thread); //yieldCPU();
            }
            else
            {
                if (DEOS.RandBool())
                {
                    DEOS.println("---Choice 0 of main---");
                    DEOS.println(thread.ToString() + " waiting until next period");
                    DEOSKernel.WaitUntilNextPeriodK(thread);

                }
                else
                {
                    DEOS.println("---Choice 1 of main---");

                    GetInterrupted(tickResult);
                }
            }
        }
    }
}
