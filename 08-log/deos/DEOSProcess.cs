using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class DEOSProcess
    {
        static ProcessConstraint itsProcessConstraint;
        static Thread itsMainThread;
        int cpuUtilization = Registry.uSecsInFastestPeriod;

        public DEOSProcess()
        {
            itsMainThread = new Thread("main");
            itsMainThread.SetCPUBudget(Registry.uSecsInFastestPeriod);
            itsMainThread.ConceptualObjectConstructor(0);
            itsProcessConstraint = new ProcessConstraint(cpuUtilization);
        }

        public static int AllocateCPUBudgetForThread(Thread theThread,
                                                int requestedBudget,
                                                int periodIndex)
        {
            int grantedCPU;

            if (theThread == itsMainThread)
            {
                return itsMainThread.CpuBudget();
            }

            bool result = itsProcessConstraint.AllocateCPUForThread(requestedBudget,
                                                                       periodIndex,
                                                                       false/*SPIN isAssociatedWithInterrupt*/
                                                                      );

            if (result)
            {
                itsMainThread.SetCPUBudget(itsMainThread.CpuBudget() -
                                           ProcessConstraint.CPUTimeToNormalizedUtilization(
                                                 requestedBudget, periodIndex));
                grantedCPU = requestedBudget;
            }
            else
            {
                grantedCPU = -1;
            }

            return grantedCPU;
        }

        public static void DeallocateCPUBudgetForThread(Thread theThread)
        {
            int budget = theThread.CpuBudget();
            int periodIndex = theThread.PeriodIndex();
            itsProcessConstraint.DeallocateCPUForThread(budget, periodIndex);
            itsMainThread.SetCPUBudget(itsMainThread.CpuBudget() +
                                       ProcessConstraint.CPUTimeToNormalizedUtilization(
                                             budget, periodIndex));
        }

        public static Thread MainThread()
        {
            return itsMainThread;
        }
    }
}
