using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    abstract class AbstractClockingDevice
    {
        public abstract void ClockTicks(int currentTime);
    }
}
