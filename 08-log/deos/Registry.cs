using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class Registry
    {
        public const int uSecsInFastestPeriod = 20;
        public const int uTicksInFastestPeriod = 1;
        public const int numPeriods = 3;

        public static int PeriodDurationInMicroSecs (int periodIndex) 
        {
            if (periodIndex == 0) {
                return uSecsInFastestPeriod;
            } else {
                return 3 * uSecsInFastestPeriod * periodIndex;
            }
        }

        public static int PeriodDurationInSystemTicks(int periodIndex)
        {
            if (periodIndex == 0)
            {
                return uTicksInFastestPeriod;
            }
            else
            {
                return 3 * uTicksInFastestPeriod * periodIndex;
            }
        }
    }
}
