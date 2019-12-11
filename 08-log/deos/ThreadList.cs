using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class ThreadList : DoubleLinkListNode
    {
        public ThreadList () 
        {
            previous = this;
            next = this;
        }

        public bool IsEmpty() 
        {
            return next == (ThreadList) this;
        }

        public void AddAtBeginning (ThreadListNode newNode) 
        {
            AddAfter(newNode);
        }

        public void AddAtEnd (ThreadListNode newNode) 
        {
            previous.AddAfter(newNode);
        }

        public ThreadListNode Head () 
        {
            if (IsEmpty()) 
            {
                DEOS.println("Attempt to acquire head of empty list!");
                System.Environment.Exit(0);
            }
            return (ThreadListNode) next;
        }

        public void MergeList (ThreadList otherList) 
        {
            if (!otherList.IsEmpty()) 
            {
                previous.next = otherList.next;
                otherList.next.previous = previous;
                previous = otherList.previous;
                otherList.previous.next = this;
                otherList.next = otherList;
                otherList.previous = otherList;
            }
        }

        public ThreadListNode Tail () 
        {
            if (IsEmpty()) 
            {
                DEOS.println("Attempt to acquire tail of empty list!");
                System.Environment.Exit(0);
            }
            return (ThreadListNode) previous;
        }
    }
}
