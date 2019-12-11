using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class Scheduler
    {
        static Thread itsRunningThread;
        static Thread itsIdleThread;
        static PriorityListOfThreads itsRunnableList;
        static DEOSProcess theProcess;
        static SynchObject synch;

        public static DEOSProcess CurrentProcess()
        {
            return theProcess;
        }

        public static Thread CurrentThread()
        {
            return itsRunningThread;
        }

        public static Thread IdleThread()
        {
            return itsIdleThread;
        }

        public static void Initialize()
        {
            synch = new SynchObject();
            itsRunnableList = new PriorityListOfThreads();
            InitializeIdleProcess();

            int interruptState = CPU.EnterCritical();
            itsRunningThread = itsIdleThread;
            itsRunningThread.StartChargingCPUTime();
            CPU.ExitCritical(interruptState);
            theProcess = new DEOSProcess();
            DEOSKernel.LocalStartThread(DEOSProcess.MainThread(),
                                        Registry.uSecsInFastestPeriod, 0);
        }

        public static int PriorityForPeriodIndex(int thePeriodIndex)
        {
            return Registry.numPeriods - thePeriodIndex;
        }

        public static PriorityListOfThreads RunnableList()
        {
            return itsRunnableList;
        }

        public static void ScheduleAnyThread()
        {
            if (!itsRunnableList.IsEmpty()) 
            {
                if (itsRunningThread.CurrentPriority() < itsRunnableList.Head().Parent().CurrentPriority()) 
                {
                    itsRunnableList.AddAtBeginning(itsRunningThread.preemptionNode);
                    Scheduler.ScheduleOtherThread();
                } 
                else 
                {
                    itsRunningThread.StopChargingCPUTime(0);
                    itsRunningThread.StartChargingCPUTime();
                }
            } 
            else
            {
                DEOS.println("How can this be!!!");
            }
        }

        public static void ScheduleOtherThread()
        {
            Thread newThread;
            Thread fromThread = itsRunningThread;

            ThreadListNode runnableThreadListNode = itsRunnableList.Head();
            Thread runnableThread = runnableThreadListNode.Parent();
            newThread = runnableThread;
            runnableThreadListNode.RemoveFromList();

            fromThread.StopChargingCPUTime(0);

            newThread.StartChargingCPUTime(); // cannot add this to atomic, since

            itsRunningThread = newThread;
        }

        public static void HandleSystemTickInterrupt()
        {
            StartOfPeriodEvent.EventForPeriodIndex(0).PulseEvent(0);
            Scheduler.ScheduleAnyThread();
        }

        //private
        public static void HandleTimerInterrupt()
        {
            itsRunningThread.CpuAllowanceExceeded();
        }

        private static void IdleThreadMain()
        {
            while (true)
            {
            }
        }

        private static void InitializeIdleProcess()
        {
            itsIdleThread = new Thread("idle");

            itsIdleThread.ConceptualObjectConstructor(0);
            itsIdleThread.SetCurrentPriority(0);
            itsIdleThread.WaitForNextTriggeringEvent();

            itsIdleThread.startOfPeriodWaitNode.RemoveFromList();

            itsIdleThread.SetCPUBudget(Registry.PeriodDurationInMicroSecs(
                                             itsIdleThread.PeriodIndex()));
            itsIdleThread.Budget().Replenish();
        }
    }
}
