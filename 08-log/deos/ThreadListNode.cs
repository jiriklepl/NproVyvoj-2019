using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class ThreadListNode : DoubleLinkListNode
    {
        private Thread itsParent;

        public ThreadListNode(Thread p)
        {
            itsParent = p;
        }

        public Thread Parent()
        {
            return itsParent;
        }
    }
}
