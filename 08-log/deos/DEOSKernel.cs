using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DEOS
{
    class DEOSKernel
    {
        public const int threadSuccess = 0;
        public const int threadInvalidHandle = 1;
        public const int threadInvalidInterrupt = 2;
        public const int threadNotDormant = 3;
        public const int threadNotSchedulable = 4;
        public const int threadInsufficientPrivilege = 5;
        public const int threadNotDynamic = 6;
        public const int threadNot = 7;
        public const int threadMaximumThreadsExceeded = 8;
        public const int threadInsufficientRAMForStack = 9;
        public const int threadNoSuchThread = 10;
        public const int threadInvalidTemplate = 11;
        public const int threadNotActive = 12;
        public const int threadInScheduleBefore = 13;
        public const int threadInsufficientBudget = 14;
        public const int threadDuplicateISR = 15;
        public const int threadInvalidFromDynamicProcess = 16;
        public const int threadPrimaryCannotBeISR = 17;

        public static void ColdStartKernel()
        {
            StartOfPeriodEvent.Initialize();
            Scheduler.Initialize();
        }

        public static int CreateThreadK (String name, int threadTemplateId, int threadBudget, int periodIndex) 
        {
            int         returnStatus;
            DEOSProcess currentProcess = Scheduler.CurrentProcess();

            // Allocate a thread, then initialize it
            Thread threadCreated = new Thread(name);

            if (threadCreated == null) 
            {
                Console.WriteLine("Thread could not be created");
                returnStatus = threadMaximumThreadsExceeded;
            } 
            else 
            {
                // Allocate stack and initialize the thread...
                if (!threadCreated.ConceptualObjectConstructor(periodIndex)) 
                {
                    threadCreated = null;
                    returnStatus = threadInsufficientRAMForStack;
                } 
                else 
                {
                    int interruptState = CPU.EnterCritical();
                    returnStatus = LocalStartThread(threadCreated, threadBudget, periodIndex);
                    CPU.ExitCritical(interruptState);

                    if (threadSuccess == returnStatus) 
                    {
                    } 
                    else 
                    {
                        threadCreated.ConceptualObjectDestructor();
                        threadCreated = null;
                    }
                }
            }

            return returnStatus;
        }

        public static int DeleteThreadK(Thread theThread) 
        {
            if (theThread != Scheduler.CurrentThread()) 
            {
              Console.WriteLine("Thread " + theThread + " no longer running delete");

              return 0;
            }

            int result;
            int interruptState = CPU.EnterCritical();

            CPU.ExitCritical(interruptState);
            theThread.InitiateStopAndDelete();
            result = threadSuccess;
            interruptState = CPU.EnterCritical();
            CPU.ExitCritical(interruptState);

            return result;
        }
        public static int LocalStartThread(Thread theThread, int requestedThreadBudget, int periodIndex)
        {
            // changed the following code because can't pass int (budget) by reference.
            //  cpuTimeInMicroseconds budget; 
            int budget; // budget set by following call.

            budget = DEOSProcess.AllocateCPUBudgetForThread(theThread, requestedThreadBudget, periodIndex);

            if (budget > -1)
            {
                theThread.StartThread(budget);

                return threadSuccess;
            }
            else
            {
                return threadNotSchedulable;
            }
        }

        public static int WaitUntilNextPeriodK(Thread th) 
        {
            if (th != Scheduler.CurrentThread()) 
            {
                Console.WriteLine("Thread " + th + " no longer running");
                return 0;
            }
            Scheduler.CurrentThread().WaitForNextPeriod();
            return 0; // void really
        }
    }
}
