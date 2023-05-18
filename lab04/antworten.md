# Lab BSY SCHED Antworten

## Introduction & Prerequisites

This laboratory is to learn how to:
- Create some basic schedules
- Find and understand the command line setting of task scheduler
- Find and understand the command line setting of task priority
- (Find and understand the command line setting of task affinity)
- Understand the programming settings of task scheduler
- Understand the programming task scheduler inheritance
- Find and understand the command line setting of I/O scheduler
- (Find and understand the programming setting of I/O scheduler)

The following resources and tools are required for this laboratory session:
- A ZHAW VPN session
- Any modern web browser
- Any modern SSH client application
- OpenStack Horizon dashboard: https://ned.cloudlab.zhaw.ch
- OpenStack account details 
  - See Moodle
- Username to login with SSH into VMs in ned.cloudlab.zhaw.ch OpenStack cloud from your laptops 
  - Ubuntu
- Ubuntu VM with 4 cores
- Installed C compiler, and tools (gcc/make)

## Time
The entire session will require 90 minutes.

## Assessment

No assessment foreseen

# Task 1 - Basic Theory

## Subtask 1.1 – Schedules

Burst Time is an expression for the runtime of a task representing the computing time and not including any wait times for I/O which may increase the actual completion time of the task.

Given the following task list, determine the FIFO and RR schedules. Assume a quantum (q) of 2.
Task | Arrival Time | Burst Time
--- | --- | ---
T1 | 0 | 10
T2 | 3 | 6
T3 | 7 | 1
T4 | 8 | 3

 WCET stands for Worst Case Execution Time. It represents the maximum possible runtime of a piece of code or a process/thread independently of the runtime environment and any scheduling factors. WCET generally includes wait times for I/O. It is used in real-time systems and embedded systems where I/O access times tend to be deterministic - i.e completed in constant-time. I/O may include disk access times but rarely depends on I/O from a (non-deterministic) user.


Task | WCET | Period 
--- | --- | --- 
| | (C) | (T)
T1 | 10 | 20 
T2 | 10 | 50 
T3 | 5 | 30 

a.) Which task has the highest priority?

b.) Is there a guaranteed schedule?


# Task 2 – Setup & Basic Tasks

- Setup your virtual machine with at least 4 cores.
  - Done
- Check the number of CPUs and the number of online-cpus (using which command?)
```
ubuntu@shalaar3:~$ lscpu
Architecture:                    x86_64
CPU op-mode(s):                  32-bit, 64-bit
Byte Order:                      Little Endian
Address sizes:                   46 bits physical, 48 bits virtual
CPU(s):                          4
On-line CPU(s) list:             0-3
Thread(s) per core:              1
Core(s) per socket:              1
Socket(s):                       4
NUMA node(s):                    1
Vendor ID:                       GenuineIntel
CPU family:                      6
Model:                           79
Model name:                      Intel(R) Xeon(R) CPU E5-2680 v4 @ 2.40GHz
Stepping:                        1
CPU MHz:                         2400.000
BogoMIPS:                        4800.00
Virtualization:                  VT-x
Hypervisor vendor:               KVM
Virtualization type:             full
L1d cache:                       128 KiB
L1i cache:                       128 KiB
L2 cache:                        16 MiB
L3 cache:                        64 MiB
NUMA node0 CPU(s):               0-3
Vulnerability Itlb multihit:     Not affected
Vulnerability L1tf:              Mitigation; PTE Inversion; VMX flush not necessary, SMT disabled
Vulnerability Mds:               Mitigation; Clear CPU buffers; SMT Host state unknown
Vulnerability Meltdown:          Mitigation; PTI
Vulnerability Spec store bypass: Mitigation; Speculative Store Bypass disabled via prctl and seccomp
Vulnerability Spectre v1:        Mitigation; usercopy/swapgs barriers and __user pointer sanitization
Vulnerability Spectre v2:        Mitigation; Full generic retpoline, IBPB conditional, IBRS_FW, STIBP disabled, RSB filling
Vulnerability Srbds:             Not affected
Vulnerability Tsx async abort:   Mitigation; Clear CPU buffers; SMT Host state unknown
Flags:                           fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ss syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon rep_good nopl xtopology cpuid tsc_known_freq pni pclmulqdq vmx ssse3 fma cx16 pdcm pcid sse4_
                                 1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand hypervisor lahf_lm abm 3dnowprefetch cpuid_fault invpcid_single pti ssbd ibrs ibpb stibp tpr_shadow vnmi flexpriority ept vpid ept_ad fsgsbase tsc_adjust bmi1 hle avx2 smep bm
                                 i2 erms invpcid rtm rdseed adx smap xsaveopt arat umip md_clear arch_capabilities

```
- Check the compiler installation (using which command?)
```
ubuntu@shalaar3:~$ gcc --version
gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
Copyright (C) 2019 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
```
## Subtask 2.1 – Process scheduling and manipulation on keyboard using nice and chrt

Inspect the code in the file processes_SCHED.c and answer the following questions:
### 1. Predict what it does.
The code creates a child process using the `fork()` system call. The parent (mother) and child processes then run a loop with `ITERATIONS` number of iterations, performing some work (`justWork(WORK_HARD)`) and printing their respective identifiers ("Mother" or "Child") alongside the iteration number. After completing the iterations, both processes print "Au revoir ...". The parent process waits for the child process to terminate before exiting.

### 2. Open a second shell and run top or htop.
This is an instruction for you to open a second terminal and run the `top` or `htop` command to monitor the processes running on your system.

### 3. Let the code run (./process_SCHED.e).
This is an instruction for you to compile and run the code using the provided executable `./process_SCHED.e`.

### 4. Does the code do what you predicted?
This question asks you to observe and confirm whether the code behaves as predicted in question 1.

### 5. How many threads/units of execution are being run?
The code runs two units of execution, one for the parent (mother) process and one for the child process.

### 6. You see the print of “Mother” and “Child” in seemingly random fashion. What do you learn from this behaviour?
This behavior suggests that the scheduling of the parent and child processes is non-deterministic, and they are being interleaved by the operating system's scheduler.

### 7. Open a third terminal and get the PIDs of the two processes. Using the command `chrt -p <PID>` display the current priority and scheduler.
This is an instruction for you to open a third terminal, get the process IDs (PIDs) of the parent and child processes, and then use the `chrt -p <PID>` command to display their current priority and scheduler.

### 8. What is the nice value of the shell process? Look at the manpages for nice and renice.
The nice value of the shell process is typically 0 by default. The nice value is a measure of a process's priority, with lower values indicating higher priority. You can find more information about nice values in the `nice` and `renice` man pages.

### 9. Change the nice of one process to -20 and that of the other to 20. What do you see now?
By setting the nice value of one process to -20 (highest priority) and the other to 20 (lowest priority), you will likely observe that the higher priority process gets significantly more CPU time and finishes its iterations much faster than the lower priority process.

### 10. Change the priority for the scheduler to 1 using `sudo chrt -o -p 1 <PID>` what do you get and why?
By setting the priority for the scheduler to 1 using `sudo chrt -o -p 1 <PID>`, you change the priority of the process to 1 under the SCHED_OTHER scheduling policy. However, since the SCHED_OTHER policy does not use priorities, this change will not have any noticeable effect on the process's behavior.

### 11. Read the manpage for chrt and set one of the processes to priority 1 scheduler `SCHED_RR` and check that this has been done.
To set one of the processes to priority 1 and the `SCHED_RR` scheduler, use the command `sudo chrt -r -p 1 <PID>`. You can verify that the change has been made by running `chrt -p <PID>` again.

### 12. What do you notice on the output?
After setting one process to priority 1 and the `SCHED_RR` scheduler, you might notice that the process with the `SCHED_RR` policy runs more frequently compared to the other process still using the default scheduler (`SCHED_OTHER`). This is because the `SCHED_RR` policy is a real-time round-robin scheduling policy, and the process with this policy will have a higher priority than a process with the default scheduling policy.

### 13. Read the RR quantum using `cat /proc/sys/kernel/sched_rr_timeslice_ms`. What does this tell you and what does it mean?
The `cat /proc/sys/kernel/sched_rr_timeslice_ms` command displays the time slice (quantum) value for the round-robin (RR) scheduler in milliseconds. This value represents the maximum time that a process with the `SCHED_RR` policy will be allowed to run before being preempted by another process with the same priority. If a process with the `SCHED_RR` policy exhausts its time slice, it will be moved to the end of the queue and the next process in the queue will be given a chance to run.

### 14. Change the priority and scheduler of the other process to 80 and `RR`. What do you see now?
To change the priority and scheduler of the other process to 80 and `RR`, use the command `sudo chrt -r -p 80 <PID>`. After making this change, you will see that both processes now have the `SCHED_RR` policy, and they will alternate their execution in a more predictable manner. The process with the higher priority (80) will run more frequently than the one with the lower priority (1).

### 15. Change the priority and scheduler of one process to 80 and `FIFO`. Both processes still run, why? Read the man page for `sched(7)`.
To change the priority and scheduler of one process to 80 and `FIFO`, use the command `sudo chrt -f -p 80 <PID>`. Both processes continue to run because the `SCHED_FIFO` policy, like the `SCHED_RR` policy, is a real-time scheduling policy. However, unlike `SCHED_RR`, `SCHED_FIFO` does not use time slices for preemption. Instead, a higher-priority process will run until it is finished, blocked, or voluntarily yields the CPU to a process with the same priority. In this case, since both processes have different priorities, they can still be scheduled and run by the operating system.


<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>
<br>

Given the following task table, answer the following questions and complete the exercise for a Rate

Monotonic Schedule

```
Task, Arrival Time, Burst time (Time it needs to complete task)

T1 0 10
T2 3 6
T3 7 1
T4 8 3

Quantum number (we use two quantums per task --> q = 2), Task
1 T1
2 T1

3 T1
4 T1

5 T2
6 T2

7 T1
8 T1

9 T3 (Finished)
10 T4

11 T4
12 T2

13 T2
14 T1

15 T1
16 T4

17 T2
18 T2

19 T1
20 T1
```

Second table (Real-time scheduling)

## Which task has the highest priority?
T1

## Is there a guaranteed schedule?
Cannot determine due to insufficient information (task deadlines or periods are missing).

## Determine the schedule (Real time deadline)
Cannot determine due to insufficient information (task deadlines or periods are missing)

# Task 2 – Setup & Basic Tasks

## Check the number of CPUs and the number of online-cpus (using which command?)

Total number of CPUs:
```
ubuntu@shalaar3:~$ grep -c ^processor /proc/cpuinfo
4
```

Number of online CPUs:
```
ubuntu@shalaar3:~$ grep -c ^processor /sys/devices/system/cpu/online
0
```

## Check the compiler installation (using which command?)

```
gcc --version
```

## Subtask 2.1 – Process scheduling and manipulation on keyboard using nice and chrt

Inspect the code in the file processes_SCHED.c and answer the following questions

## Predict what it does.
1. The program forks the current process to create a child process.
2. Both the parent and the child process execute a loop for ITERATIONS (20) times, where each iteration calls justWork(WORK_HARD) to simulate workload and then prints the iteration number followed by either "Mother" (for the parent process) or "Child" (for the child process).
3. Both processes use fflush(stdout) to force output to be displayed immediately.


* Edit the makefile if necessary, build the code and let it run (make , ./out.e) open a second shell and you may find htop more useful than top.

* Does it do what you predicted?

```
Yes, prints stuff
```

* How many threads/units of execution are being run?

```
2, parent and child
```

* You see the print of “Mother” and “Child” in seemingly random fashion. What do you learn from this behaviour?

```
Depends on the scheduler that we are running, maybe virtualization also affects this
```

* Open a third terminal and get the PIDs of the two processes. Using the command chrt -p <PID> display the current priority and scheduler

```
ubuntu@sched:~/src$ chrt -p 1870
pid 1870's current scheduling policy: SCHED_OTHER
pid 1870's current scheduling priority: 0
```

* What is the nice value of the shell process? Look at the manpages for nice and renice

```
ubuntu@exam:~$ nice
0
```

* Change the nice of one process to -20 and that of the other to 20. What do you see now?

```
renice -n -20 -p 1870
```

* Change the priority for the scheduler to 1 using sudo chrt -o -p 1 <PID> what do you get and why?

```
sudo chrt -o -p 1 1870

SCHED_OTHER only has priority 0
```

* Read the manpage for chrt and set one of the processes to priority 1 scheduler SCHED_RR and check that this has been done

```
chrt -r -p 1 6491
```

* What do you notice on the output?

```
```

* Read the RR quantum using cat /proc/sys/kernel/sched_rr_timeslice_ms what does this tell you and what does it mean?

```
```

* Change the priority and scheduler of the other process to 80 and RR what do you see now?

```
```

* Change the priority and scheduler of one process to 80 and FIFO. both processes still run, why? Read the man page for sched(7).

```
```

## Subtask 2.2 – Thread scheduling and manipulating on keyboard, including overriding inheritance rules

* Inspect, edit the makefile if necessary, build and run the code threads_SCHED.c. What are the thread priorities?

```
```

* Read the man pages for sched() - why do the child processes/threads have the same scheduler priority

```
```

* Using htop look at the comparative CPU/core usage what do you see?

```
```

* Change the nice value of one of the threads with a core to itself - does anything change?

```
```

* What ways have we seen to change the scheduler/priorities of a thread? What would be more elegant?

```
```

* Modify the code so that the threads (thread 5 has been prepared) start in their required priority and scheduler. Hint - use the following calls, in that order - and the man pages

```
```
