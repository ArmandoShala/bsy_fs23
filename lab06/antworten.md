# Lab BSY MEM
## Introduction & Prerequisites
# Laboratory Objectives
The objective of this laboratory is to learn how to:
- Understand how Linux reports memory statistics and usage
- Understand the relationship between program memory requirements and Linux
- Understand practical ramifications of pages
- Limit memory on a user basis
- Limit memory by the use of a cgroup
- Understand the relationship between virtual memory and a swap area
- Initialise a swap area

## Required Resources and Tools
The following resources and tools are required for this laboratory session:
- A ZHAW VPN session
- Any modern web browser
- Any modern SSH client application
- OpenStack Horizon dashboard: https://ned.cloudlab.zhaw.ch
- OpenStack account details (See Moodle)
- Username to login with SSH into VMs in ned.cloudlab.zhaw.ch OpenStack cloud from your laptops
- Ubuntu
- Ubuntu VM with at least 2 cores, preferably 4
- Installed C compiler, and tools (gcc/make)
- `sudo apt update`
- `sudo apt install build-essential`
## Time
The entire session will require 90 minutes.

## Assessment
No assessment foreseen

# Task 1 – Setup & Basic Tasks
Setup your virtual machine with one or more cores 
## Check the number of CPUs and the number of online-cpus (using which command?)

## Check the compiler installation (using which command?)
To check the number of CPUs and the number of online CPUs on a Linux-based system, you can use the following commands:

To check the total number of CPUs:
```
parallels@parallels-Parallels-Virtual-Platform:~$ lscpu
Architecture:                    x86_64
CPU op-mode(s):                  32-bit, 64-bit
Byte Order:                      Little Endian
Address sizes:                   36 bits physical, 48 bits virtual
CPU(s):                          6
On-line CPU(s) list:             0-5
Thread(s) per core:              1
Core(s) per socket:              6
Socket(s):                       1
NUMA node(s):                    1
Vendor ID:                       GenuineIntel
CPU family:                      6
Model:                           158
Model name:                      Intel(R) Core(TM) i9-9980HK CPU @ 2.40GHz
Stepping:                        13
CPU MHz:                         2400.000
BogoMIPS:                        4800.00
Hypervisor vendor:               KVM
Virtualization type:             full
L1d cache:                       192 KiB
L1i cache:                       192 KiB
L2 cache:                        1.5 MiB
L3 cache:                        16 MiB
NUMA node0 CPU(s):               0-5
Vulnerability Itlb multihit:     KVM: Mitigation: VMX unsupported
Vulnerability L1tf:              Mitigation; PTE Inversion
Vulnerability Mds:               Vulnerable: Clear CPU buffers attempted, no microcode; SMT Host state unknown
Vulnerability Meltdown:          Mitigation; PTI
Vulnerability Spec store bypass: Vulnerable
Vulnerability Spectre v1:        Mitigation; usercopy/swapgs barriers and __user pointer sanitization
Vulnerability Spectre v2:        Mitigation; Full generic retpoline, STIBP disabled, RSB filling
Vulnerability Srbds:             Unknown: Dependent on hypervisor status
Vulnerability Tsx async abort:   Not affected
Flags:                           fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ss ht syscall nx rdtscp lm constant_tsc nopl xtopology nonstop_tsc cpuid tsc_known_freq pni pcl
                                 mulqdq ssse3 fma cx16 pcid sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand hypervisor lahf_lm abm 3dnowprefetch invpcid_single pti fsgsbase tsc_adjust bmi1 avx2 s
                                 mep bmi2 invpcid rdseed adx smap clflushopt xsaveopt xsavec dtherm arat pln pts
```
This command will provide you with detailed information about your CPU, including the number of CPU cores. Look for the "CPU(s)" field in the output.

To check the number of online CPUs
```
parallels@parallels-Parallels-Virtual-Platform:~$ nproc
6
```

## Install the cgroup-bin package 
When this is installed edit /etc/default/grub and edit the relevant line to `GRUB_CMDLINE_LINUX_DEFAULT="cgroup_enable=memory swapaccount=1"`
## Run
`sudo update-grub`
## Reboot
This should install `cgexec`. Note: Rebooting could take some time - you can check the VM console (https://ned.cloudlab.zhaw.ch) for the VM status.

Setup three to four terminal connections to your machine, it makes life easier


# Subtask 1.1 – Basic memory under Linux
## Download and unzip the file package MEM_students_code.zip.

Open the MEM_lab.c file and inspect the code. In the first section (ToDo 1,) call up a function to print out the PID of the running process - this will come in useful later (hint - use the getpid system call)

## Add an endless loop below this, exit, compile and run.
```
(void) printf("----- the PID of the running process is %i\n", getpid());
```
To add an endless loop below this line, you can simply use a while loop with a condition that is always true. Here's an example

```
(void) printf("----- the PID of the running process is %i\n", getpid());
while (1) {}
```
This will create an endless loop that will keep running until the program is terminated. To compile and run the program, you can use the following commands
```
gcc MEM_lab.c -o MEM_lab
./MEM_lab
```
## In a second terminal run top or htop - what memory parameters are useful to know? (Hint - use the documentation for htop to look for VIRT/RES/SHR)
When running top or htop, the following memory parameters are useful to know:
- VIRT: the total amount of virtual memory used by the process
- RES: the total amount of physical memory (RAM) used by the process
- SHR: the total amount of shared memory used by the process
These memory parameters can give an indication of the memory usage of a process and how it is distributed between virtual and physical memory, as well as the amount of shared memory that is being used

Here are some memory parameters that you may find useful:
- %MEM: The percentage of the total physical memory that is being used by the process.
- RSS (Resident Set Size): The amount of physical memory that is currently being used by the process, in kilobytes (KB).
- SZ (Size): The total virtual memory used by the process, in kilobytes (KB).
- SWAP: The amount of swap space currently being used by the process, in kilobytes (KB).


## In a third terminal using the command free (hint - man free) display the system memory parameters in kilobytes
To display system memory parameters in kilobytes using the free command, open a terminal and type the following command
```
parallels@parallels-Parallels-Virtual-Platform:~$ free -k
              total        used        free      shared  buff/cache   available
Mem:       22254628      500352    21047904       26564      706372    21408928
Swap:       2097148           0     2097148
```
The output will show the following memory parameters in kilobytes:
- total: Total amount of physical memory.
- used: Amount of physical memory used.
- free: Amount of physical memory free.
- shared: Amount of shared memory.
- buff/cache: Amount of memory used for buffering/cache.
- available: Amount of memory available for new processes.
Note that the values shown in free output are in kilobytes by default.

## Explain the parameters
### Read the file /proc/${pid}/status specifically the memory related portions. What do the fields mean? (hint-man proc) Note down the values or make a screenshot, we shall need this later What is the difference between VmPin and VmLck?
The free command displays the total amount of free and used physical and swap memory in the system, as well as the buffers and cache used by the kernel.
Memory Parameters:
- total: Total amount of physical RAM on the system.
- used: Amount of RAM used by the system.
- free: Amount of RAM free for new processes.
- shared: Amount of shared memory.
- buffers: Amount of RAM used for buffering disk blocks.
- cached: Amount of RAM used as cache memory.
/proc/${pid}/status Fields:
- VmPeak: Peak virtual memory size.
- VmSize: Current virtual memory size.
- VmLck: Locked memory size.
- VmPin: Pinned memory size.
- VmHWM: Peak resident set size.
- VmRSS: Current resident set size.
- VmData: Data size.
- VmStk: Stack size.
- VmExe: Text size.

VmPin and VmLck are both fields in the /proc/${pid}/status file that relate to memory locking. VmPin refers to the total amount of memory that has been pinned in RAM, while VmLck refers to the amount of memory that has been locked into RAM using the mlock() system call. When memory is pinned in RAM, it cannot be swapped out to disk, but it can still be paged out. When memory is locked, it cannot be swapped out or paged out, and must remain in physical RAM.

## Research the command smem, install if necessary. What information does smem give you about your system?
### Note: smem is a useful tool for helping set up resource management in server systems

The smem command provides a more detailed summary of memory usage on a system than other commands like free. It reports the memory usage by processes and by memory pools. Specifically, smem provides information on:

- Physical memory usage (RSS, Resident Set Size)
- Shared memory usage (PSS, Proportional Set Size)
- Unshared memory usage (USS, Unique Set Size)
- Virtual memory usage (VMS, Virtual Memory Size)
- Swapped-out memory usage (Swap)
Additionally, smem can display memory usage per user or per process, and can sort output based on various criteria such as memory usage or process name. Overall, smem is a useful tool for analyzing memory usage on a system and identifying which processes are consuming the most memory

## Go back to the code program
Remove the endless loop and insert code to read the page size (store it in a variable) and print it out. (ToDo 2) Build and run (hint - man getpagesize)

Here's the modified code to read the page size and print it out:
```
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main(void) {
    int result;
    int section = 1;

    (void) printf("Hello MEM Lab\n");

    // ---------- section 

    (void) printf("------------ Part %i:  Simple program check memory of process\n", section++);

    (void) printf("\nPress enter to continue\n");
    (void) getchar();

    // ---------- section  

    (void) printf("------------ Part %i:  whats the page size\n", section++);

    // ToDo 2: insert function to get and read the page size  
    long page_size = sysconf(_SC_PAGESIZE);
    if (page_size == -1) {
        perror("Failed to read page size\n");
        exit(EXIT_FAILURE);
    }
    (void) printf("Page size: %ld bytes\n", page_size);

    (void) printf("Press return to continue\n");
    (void) getchar();

    // ---------- section 

    (void) printf("------------ Part %i:  generate some memory area\n", section++);

    // ToDo 3: insert code to reserve memory  

    (void) printf("\nPress return to continue\n");
    (void) getchar();

    // ---------- section 

    (void) printf("------------ Part %i: Are these pages in memory?\n", section++);

    // ToDO 4: reserve memory with aligned_alloc this is necessary for the mincore function to function properly

    // ToDo 5: write something into the reserved buffer      

    (void) printf("Press return to continue\n");
    (void) getchar();

    // ---------- section 

    (void) printf("------------ Part %i: Lets limit the available memory\n", section++);

    // prepare variables and load a large file
    int width=0, height=0, bpp=0;
    uint8_t *rgb_image = stbi_load("Hopper.png", &width, &height, &bpp, 3);

    // in case of issues
    if (rgb_image == NULL) {
        perror("File read failed\n"); 
        exit(EXIT_FAILURE);
    }

    // reserve memory for the greyscale image
    // the rgb png comes in 8-bit format
    uint8_t *gry_image = malloc (width * height * sizeof(uint8_t));    

    // lets exercise
    rgb2grayscale (width, height, rgb_image, gry_image);    

    (void) printf("Check the number of page faults\n");
    (void) printf("Press return to continue\n");
    (void) getchar();

    (void) printf("Carry out the instructions in the lab guide to limit the available memory and repeat \n");

    (void) printf("Bye MEM Lab\n");

    exit(0);
}
```

## Verify this with the getconf command (hint - man getconf) Now include code to reserve memory (hint - man malloc) the size of a number of pages (ToDo 3) After each execution step of this code run the command (another terminal)
```
ps -o min_flt,maj_flt {pid}
```
To get the page size and verify it using the getconf command, the following code can be added after the first printf statement in the code
```
// get page size
int pagesize = getpagesize();
printf("Page size: %d\n", pagesize);

// verify with getconf command
long page_size = sysconf(_SC_PAGESIZE);
printf("Verified page size with getconf command: %ld\n", page_size);
```
To reserve memory, the following code can be added after the second printf statement in the code
```
// reserve memory for 2 pages
int num_pages = 2;
int mem_size = pagesize * num_pages;
void* mem_ptr = malloc(mem_size);
if (mem_ptr == NULL) {
    printf("Error: Failed to allocate memory.\n");
    exit(1);
}

// print address of allocated memory
printf("Allocated memory address: %p\n", mem_ptr);
```

After each execution step of this code, the ps command can be run in another terminal with the specified pid to display the number of minor and major page faults. For example, to display this information for pid 3042, the command would be:
```
ps -o min_flt,maj_flt 3042
```
The output of this command shows the number of minor and major page faults for the specified process. Minor page faults occur when a requested page is not in memory and must be brought in from disk, while major page faults occur when a page is requested that does not exist and must be allocated

## Use the man page to understand the parameters. What do you notice?
The ps command with the -o option is used to specify the output format. In the case of ps -o min_flt,maj_flt {pid}, the output format is set to display the number of minor and major page faults for the process with the specified PID.

A minor page fault occurs when a process attempts to access a page that is currently not in memory, but is in the swap space. The operating system loads the page from the swap space into memory, which results in a minor page fault.

A major page fault occurs when a process attempts to access a page that is not currently in memory and is also not in the swap space. The operating system has to allocate a new page and load it into memory, which results in a major page fault.

By monitoring the number of page faults, we can get an idea of how often the process is accessing memory and how well it is utilizing the available memory
## Return to the code - for ToDo 4
use the align_alloc function to reserve a buffer of a number of pages size, aligned on a page boundary. Then use the function mincore to check whether the pages are in memory.

## What do you see?

## Linux uses lazy allocation
include an access to the buffer - ToDo 5 - and run the code again. What do you see when you run the code and check the page faults reported by the ps command?

# Subtask 1.2 – Limiting memory (1)

## From reading the process status file we know the maximum amount of memory the process uses during startup. We can now attempt to limit this on a high level.

## Research the ulimit command and use it to display the resource limitations. What precisely is limited?

## Using the data from reading /proc/${pid}/status let us limit the available memory for the start phase of the test program to under the peak requirement. What happens?

## How do you restore the unlimited memory access capability? What is your assessment of this method?

# Subtask 1.3 – Limiting memory (2)

## cgroups allows us to limit the resources used for individual processes. Here we will create a memory controller for our test process.

## We define a cgroup memory controller. Use the man pages to understand the parameters

```
sudo cgcreate -a ubuntu:ubuntu -t ubuntu:ubuntu -g memory:myGroup
```


## What memory controller files have been created? What can be used to set limitations of memory usage?

## We check the peak memory usage of the process which should be, in section 5, high - around the 120M mark. We can now use this value to limit the process memory by writing an appropriate value into the group memory controller file

```
echo xxM > /sys/fs/cgroup/memory/myGroup/memory.limit_in_bytes
```

## By running the process as follows

```
cgexec -g memory:myGroup process_name
```

The process will run under the condition set by the cgroups memory controller.

## Check the results using the free command. Two things can happen - if it’s your lucky day the process will be killed. Why? The console output of your VM will give you a better hint. Explain it.

# Subtask 1.4 – Setting up a swap area

## Why should we bother with a swap area?

Because the principle of virtual memory depends on having excess secondary memory to enable a maximum number of processes to run “simultaneously.”

If using free it can be seen there is no swap area in secondary memory, then one needs to be setup. We do this in the following sequence
1. Create a file that can be used for swapping 
   a. Run `sudo fallocate -l 1G /swapfile`

2. Give this file root permissions only 
   a. Run `sudo chmod 600 /swapfile`

3. Setup a Linux swap area in the file 
   a. Run `sudo mkswap /swapfile`

4. Activate the swap file 
   a. Run `sudo swapon /swapfile`

5. If this is to be permanent, then 
   a. Run `sudo nano /etc/fstab`
   b. Add the following line to the end of the file: `/swapfile swap swap defaults 0 0`

6. Run `sudo swapon --show` or `sudo free -h` to verify that the swap area is now active.

##  Swappiness is a Linux kernel property that defines how often the system will use the swap space. Use the command to read the swappiness. What value do you get? The higher the value the more likely the kernel is to swap, the lower the value the more the kernel tries to avoid it. On production servers, a low swappiness is often preferred to decrease latencies and user available system memory.

```
cat /proc/sys/vm/swappiness
```

## Read the manpage for swapoff. Swappiness can be adjusted using:
```
sudo sysctl vm.swappiness=10
```

## If your process was killed in Substep 1.3, setup the swap area and repeat the experiment. What happens now?

# Cleanup

IMPORTANT: At the end of the lab session, please do the following:

- Delete all unused OpenStack VMs, volumes, and security group rules that were created by your team.

# Additional Documentation

OpenStack Horizon documentation can be found on the following page:
- User Guide: https://docs.openstack.org/horizon/latest/
