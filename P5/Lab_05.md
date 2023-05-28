# Lab 5 - Linux Memory Managment
## 1 – Setup & Basic Tasks
#### Check the number of CPUs and the number of online-cpus (using which command?)

- nproc
- lscpu
- cat /proc/cpuinfo

#### Check the compiler installation (using which command?)

- gcc --version

#### Setup three to four terminal connections to your machine, it makes life easier

Tip: use <code>tmux</code>

Look up for a cheat sheet, but here are a few useful commands:

| Combination        | Description                        |
|--------------------|------------------------------------|
| tmux               | Create a tmux session              |
| CTRL+b into c      | Create a terminal                  |
| CTRL+b into %      | Split current pane vertically      |
| CTRL+b into "      | Split current pane horizontally    |
| CTRL+b into \<nr\> | Switch to existing terminal \<nr\> |
| CTRL+d into \<nr\> | Close terminal \<nr\>              |

### 1.1 – Basic memory under Linux
#### Todo 1 - In the first section call up a function to print out the PID of the running process - this will come in useful later (hint - use the getpid system call). Add an endless loop below this, exit, compile and run.

See [MEM_lab.c](MEM_lab.c) - Todo 1

#### In a second terminal run top or htop - what memory parameters are useful to know? (Hint - use the documentation for htop to look for VIRT/RES/SHR)

```
$ htop
```

![1_1_htop.png](img%2F1_1_htop.png)

Tip: Press <code>M</code> to order htop by memory usage.

| Column           | Description                                                                                                              |
|------------------|--------------------------------------------------------------------------------------------------------------------------|
| M_SIZE (VIRT)    | The size of the virtual memory of the process.                                                                           |
| M_RESIDENT (RES) | The resident set size (text + data + stack) of  the  process  (i.e.  the  size  of  the process's used physical memory). |
| M_SHARE (SHR)    | The size of the process's shared pages.                                                                                  |
 
#### In a third terminal using the command free (hint - man free) display the system memory parameters in kilobytes

```
$ free --kilo
```
![1_1_free.png](img%2F1_1_free.png)

Tip: Use e.g. -k to display kibibytes (1024 or 2^10 bytes) instead of --kilo for kilobytes (1000 or 10^3 bytes).

#### Read the file /proc/${pid}/status specifically the memory related portions. What do the fields mean? (hint-man proc)

| Attribute     | Description                                                                                     |
|---------------|-------------------------------------------------------------------------------------------------|
| Mems_allowed  | Mask of memory nodes allowed to this process.                                                   |
| RssAnon       | Size of resident anonymous memory.                                                              |
| RssShmem      | Size of resident shared memory.                                                                 |
| VmLck         | Locked memory size.                                                                             |
| VmPeak        | Peak virtual memory size.                                                                       |
| VmPin         | These are pages that can't be moved because something needs to directly access physical memory. |
| VmSize        | Virtual memory size.                                                                            |
| VmSwap        | Swapped-out virtual memory size.                                                                |

##### VmLck

The amount of memory that has been "pinned" or kept in physical memory and is not allowed to be swapped out to disk. This is often used for critical system processes or processes that require low-latency access to memory.

##### VmPin

The amount of memory that has been locked or "locked-in" physical memory, meaning it cannot be paged out or swapped out to disk. This is typically used for processes that need to guarantee access to a certain amount of memory, such as databases or real-time applications.

#### What is the difference between VmPin and VmLck?

| Attribute | Description                                                                                     |
|-----------|-------------------------------------------------------------------------------------------------|
| VmLck     | Locked memory size.                                                                             |
| VmPin     | These are pages that can't be moved because something needs to directly access physical memory. |

#### Research the command smem, install if necessary. What information does smem give you about your system?

smem is used to report memory usage with shared memory divided proportionally.

![1_1_smem.png](img%2F1_1_smem.png)

| Column | Description                                           |
|--------|-------------------------------------------------------|
| USS    | Unique Set Size for unshared memory                   |
| PSS    | Proportional Set Size = shared + unshared memory      |
| RSS    | Resident Set Size: Held in RAM, will not swap to disk |

#### Todo 2 - Remove the endless loop and insert code to read the page size (store it in a variable) and print it out.

See [MEM_lab.c](MEM_lab.c) - Todo 2 and output at the end of Task 1.1.

#### Verify this with the getconf command

```
$ getconf PAGE_SIZE
4096
```

#### Todo 3  - Include code to reserve memory (hint - man malloc) the size of a number of pages.

See [MEM_lab.c](MEM_lab.c) - Todo 3 and output at the end of Task 1.1.

#### After each execution step of this code run the following command (another terminal)

```
ps -o min_flt,maj_flt {pid}
```

See PS output at the end of Task 1.1.

| Attribute | Description                 |
|-----------|-----------------------------|
| min_flt   | Number of minor page faults |
| max_flt   | Number of major page faults |

#### Todo 4 - use the align_alloc function to reserve a buffer of a number of pages size, aligned on a page boundary. Then use the function mincore to check whether the pages are in memory.

The pages are not resident in the memory before accessing them. 

Here we write random characters into the memory as displayed with the samples. 

See [MEM_lab.c](MEM_lab.c) - Todo 4 and output at the end of Task 1.1.

#### Todo 5 - Linux uses lazy allocation - include an access to the buffer - and run the code again. What do you see when you run the code and check the page faults reported by the ps command?

The count for page faults reset when starting the program anew as a new process starts and different memory is allocated.

See [MEM_lab.c](MEM_lab.c) - Todo 5 (included in Part 4) and output at the end of Task 1.1.


#### OUTPUT: Terminal of complete program  

![1_1_out.png](img%2F1_1_out.png)
  
#### OUTPUT: PS of complete program

![1_1_ps.png](img%2F1_1_ps.png)

### 1.2 – Limiting memory (1)
#### From reading the process status file we know the maximum amount of memory the process uses during startup. We can now attempt to limit this on a high level. 
#### Research the ulimit command and use it to display the resource limitations. What precisely is limited?

The following command `ulimit -a` fetches all limits for a user.

![1_2_ulimits.png](img%2F1_2_ulimits.png)

#### Using the data from reading /proc/${pid}/status let us limit the available memory for the start phase of the test program to under the peak requirement. What happens?

For example. If we limit a process that requires 90 MB (92'160 kB) and we limit it to 50 MB (51'200 kb)
using the command <code>ulimit -m 51200</code>, the program will receive an error when trying to allocate 
more than 50 MB and therefore will crash. 

#### How do you restore the unlimited memory access capability? What is your assessment of this method?

- `ulimit -m unlimited`

- It might be helpful in the first time to assign unlimited memory access. But if a process has flaws, it might be dangerous.

### 1.3 – Limiting memory (2)

#### cgroups allows us to limit the resources used for individual processes. Here we will create a memory controller for our test process
#### We define a cgroup memory controller. Use the man pages to understand the parameters

`sudo cgcreate -a ubuntu:ubuntu -t ubuntu:ubuntu -g memory:myGroup`

| Parameter         | Description                                                                     |
|-------------------|---------------------------------------------------------------------------------|
| sudo              | Run command with admin privileges                                               |
| cgcreate          | Create a cgroup                                                                 |
| -a ubuntu:ubuntu  | Define user & group to access the cgroup as admins. User: Ubuntu, Group: Ubuntu |
| -t ubuntu:ubuntu  | Define user & group that the cgroup will apply to. User: Ubuntu, Group: Ubuntu  |
| -t memory:myGroup | Define subsystem and cgroup name. Subsystem: Memory, Name: myGroup              |

#### What memory controller files have been created? What can be used to set limitations of memory usage?

- The following files have been created
    - memory.limit_in_bytes
    - memory.usage_in_bytes
    - memory.max_usage_in_bytes
    - memory.failcnt

- What can be used to set limitations of memory usage?
- For example we could use:
    -  `sudo cgset -r memory.limit_in_bytes=500000 myGroup
`

#### We check the peak memory usage of the process which should be, in section 5, high - around the 120M mark. 

#### We can now use this value to limit the process memory by writing an appropriate value into the group memory controller file

`echo 2M > /sys/fs/cgroup/memory/myGroup/memory.limit_in_bytes`

#### By running the process as follows ...

`cgexec -g memory:myGroup process_name`

#### ... the process will run under the condition set by the cgroups memory controller.
#### Check the results using the free command. Two things can happen - if it’s your lucky day the process will be killed. Why? The console output of your VM will give you a better hint. Explain it.

- The process will be killed because it has exceeded the memory limit set by myGroup. OOM comes into action and kills the process. 
- Use the command <code>dmesg</code> to display the system log:
![1_3_cgroup_kill.jpg](img%2F1_3_cgroup_kill.jpg)

### 1.4 – Setting up a swap area

#### Why should we bother with a swap area? Because the principle of virtual memory depends on having excess secondary memory to enable a maximum number of processes to run “simultaneously.”
#### If using free it can be seen there is no swap area in secondary memory, then one needs to be setup. We do this in the following sequence

- 1.) Create a file that can be used for swapping
    - a.) sudo fallocate -l 1G /swapfile
- 2.) Give this file root permissions only
    - a.) sudo chmod 600 /swapfile
- 3.) Setup a Linux swap area in the file
    - a.) sudo mkswap /swapfile
- 4.) Activate the swap file
    - a.) sudo swapon /swapfile
- 5.)If this is to be permanent then
    - a.) sudo nano /etc/fstab
    - b.) And add: /swapfile swap swap defaults 0 0
6.) sudo swapon --show or
7.) sudo free -h will now show a swap area

#### Swappiness is a Linux kernel property that defines how often the system will use the swap space.
#### Use the command to read the swappiness.

`cat /proc/sys/vm/swappiness`

#### What value do you get? The higher the value the more likely the kernel is to swap, the lower the value the more the kernel tries to avoid it. 

![1_4_swappiness.png](img%2F1_4_swappiness.png)

#### On production servers, a low swappiness is often preferred to decrease latencies and user available system memory.
#### Swappiness can be adjusted using:

`sudo sysctl vm.swappiness=10`

#### Read the manpage for swapoff

#### If your process was killed in Substep 1.3, setup the swap area and repeat the experiment. What happens now?

The swaps swapped a lot due to swapping the swappiness configuration of the memory for more swappiness. Swap :)

![1_4_free_swappiness.jpg](img%2F1_4_free_swappiness.jpg)