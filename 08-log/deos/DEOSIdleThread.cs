using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class DEOSIdleThread : DEOSThread
    {
        public DEOSIdleThread(Thread t): base(t)
        {
        }

        public void Run(int tickResult)
        {
            GetInterrupted(tickResult);
        }
    }
}
