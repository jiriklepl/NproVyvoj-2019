using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class ProcessConstraint
    {
        int remainingNormalizedUtilization;
        int initialNormalizedUtilization;

        public ProcessConstraint(int theUtilization)
        {
            initialNormalizedUtilization = theUtilization;
            remainingNormalizedUtilization = theUtilization;
        }

        public static int CPUTimeToNormalizedUtilization(int CPUTime,
                                                          int periodIndex)
        {
            int ticksPerPeriod = (Registry.PeriodDurationInMicroSecs(periodIndex) / Registry.PeriodDurationInMicroSecs(0));
            return CPUTime / ticksPerPeriod;
        }

        public bool AllocateCPUForThread(int CPUTime, int periodIndex,
                                             bool isISR)
        {
            int normalizedThreadUtilization = CPUTimeToNormalizedUtilization(CPUTime,
                                                                             periodIndex);
            if (normalizedThreadUtilization > remainingNormalizedUtilization)
            {
                return false; // InsufficientCPU
            }

            remainingNormalizedUtilization -= normalizedThreadUtilization;
            return true;
        }

        public void DeallocateCPUForThread(int CPUTime, int periodIndex)
        {
            remainingNormalizedUtilization += CPUTimeToNormalizedUtilization(CPUTime,
                                                                             periodIndex);
        }

        public int OneHundredPercentUtilization()
        {
            return Registry.PeriodDurationInMicroSecs(0);
        }
    }
}
