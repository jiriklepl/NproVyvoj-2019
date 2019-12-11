using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class PriorityListOfThreads
    {
        public const int numberOfThreadPriorities = 4; // from spin code 
        int              itsHighestPriorityMember;
        ThreadList[]     itsList;

        public PriorityListOfThreads () 
        {
            itsHighestPriorityMember = 0;
            itsList = new ThreadList[numberOfThreadPriorities];

            for (int i = 0; i < numberOfThreadPriorities; i++) {
                itsList[i] = new ThreadList();
            }
        }

        public bool IsEmpty() 
        {
            return HighestPriorityMember().IsEmpty();
        }

        public void AddAtBeginning (ThreadListNode theNode) 
        {
            int threadPriority = theNode.Parent().CurrentPriority();
            itsList[threadPriority].AddAtBeginning(theNode);

            if (itsHighestPriorityMember < threadPriority) 
            {
                itsHighestPriorityMember = threadPriority;
            }
        }

        public void AddAtEnd (ThreadListNode theNode) 
        {
            int threadPriority = theNode.Parent().CurrentPriority();
            itsList[threadPriority].AddAtEnd(theNode);

            if (itsHighestPriorityMember < threadPriority) 
            {
                itsHighestPriorityMember = threadPriority;
            }
        }

        public ThreadListNode Head()
        {
            return HighestPriorityMember().Head();
        }

        public void MergeList(PriorityListOfThreads otherList)
        {
            //Verify.beginAtomic();
            ThreadList mine = itsList[0];
            ThreadList his = otherList.itsList[0];
            int end = otherList.itsHighestPriorityMember + 1;
            int i = 0;

            do
            {
                mine.MergeList(his);
                i++;
                mine = itsList[i];
                his = otherList.itsList[i];
            } while (i != end);

            if (itsHighestPriorityMember < otherList.itsHighestPriorityMember)
            {
                itsHighestPriorityMember = otherList.itsHighestPriorityMember;
            }

            otherList.itsHighestPriorityMember = 0;
        }

        public void MergeList(ThreadList otherList)
        {
            if (!otherList.IsEmpty())
            {
                int otherListPriority = otherList.Head().Parent().CurrentPriority();

                itsList[otherListPriority].MergeList(otherList);

                if (itsHighestPriorityMember < otherListPriority)
                {
                    itsHighestPriorityMember = otherListPriority;
                }
            }

        }

        private ThreadList HighestPriorityMember()
        {
            int hipri = itsHighestPriorityMember;

            for (; hipri > 0; hipri--)
            {
                if (!itsList[hipri].IsEmpty())
                {
                    break;
                }
            }

            itsHighestPriorityMember = hipri;

            return itsList[hipri];
        }
    }
}
