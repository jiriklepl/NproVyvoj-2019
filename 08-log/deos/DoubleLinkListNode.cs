using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    public class DoubleLinkListNode
    {
        public DoubleLinkListNode previous;
        public DoubleLinkListNode next;

        protected DoubleLinkListNode()
        {
            previous = null;
            next = null;
        }

        public bool IsOnAList()
        {
            return next != null;
        }

        public void AddAfter(DoubleLinkListNode newNode)
        {
            DoubleLinkListNode t = this;
            DoubleLinkListNode n = t.next;
            DoubleLinkListNode nn = newNode;
            nn.next = n;
            nn.previous = t;
            t.next = nn;
            n.previous = nn;
        }

        public void EnsureNotOnList()
        {
            if (IsOnAList())
            {
                RemoveFromList();
            }
        }

        public DoubleLinkListNode NextNode()
        {
            return next;
        }

        public DoubleLinkListNode PreviousNode()
        {
            return previous;
        }

        public void RemoveFromList()
        {
            DoubleLinkListNode t = this;
            DoubleLinkListNode p = t.previous;
            DoubleLinkListNode n = t.next;
            n.previous = p;
            p.next = n;

            DoubleLinkListNode zero = null;
            t.previous = zero;
            t.next = zero;
        }
    }
}
