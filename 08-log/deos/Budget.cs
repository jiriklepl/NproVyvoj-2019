using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class Budget
    {
        private int itsTotalBudget;
        private int itsRemainingBudget;

        public void SetRemainingBudgetInUsec(int b)
        {
            itsRemainingBudget = b;
        }

        public void SetTotalBudgetInUsec(int b)
        {
            itsTotalBudget = b;
        }

        public void AdjustRemainingTime(int b)
        {
            itsRemainingBudget += b;
        }

        public int RemainingBudgetInUsec()
        {
            return itsRemainingBudget;
        }

        public void Replenish()
        {
            itsRemainingBudget = itsTotalBudget;
        }

        public void ReplenishAndStartTimer()
        {
            itsRemainingBudget = itsTotalBudget;
            StartTimer();
        }

        public void StartTimer()
        {
            DEOS.systemClock.SetTimer(itsRemainingBudget);
        }

        public int TotalBudgetInUsec()
        {
            return itsTotalBudget;
        }

        int StopTimer()
        {
            // Modified by ckong - June 25, 2001
            //itsRemainingBudget = DEOS.theTimer.timeRemaining();
            itsRemainingBudget = DEOS.theTimer.GetRemainingTime(
                                       DEOS.systemClock.GetCurrentTime());

            return itsRemainingBudget;
        }
    }
}
