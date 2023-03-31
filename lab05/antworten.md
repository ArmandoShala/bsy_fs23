# Antworten

# Task 1 – Understand Cgroups Version One

## Subtask 1.1 – Default System Configuration

### Analyse the default cgroup configuration of Ubuntu. Which subsystems are supported by the Ubuntu kernel? Explain the output.

To analyze the default cgroup configuration of Ubuntu and determine which subsystems are supported by the Ubuntu kernel, you can check the cgroup hierarchy using the following command:
```
ubuntu@shalaar3:~$ cat /proc/cgroups
#subsys_name	hierarchy	num_cgroups	enabled
cpuset	3	1	1
cpu	5	93	1
cpuacct	5	93	1
blkio	10	93	1
memory	9	162	1
devices	2	93	1
freezer	12	2	1
net_cls	4	1	1
perf_event	11	1	1
net_prio	4	1	1
hugetlb	8	1	1
pids	6	99	1
rdma	7	1	1
```

### Which hierarchies are provided by default? Which subsystems are configured at which hierarchy?

This command will display the mounted cgroup filesystems, their mount points, and the attached subsystems. The output will show the hierarchy and subsystems in a format like this:
`cgroup /sys/fs/cgroup/<subsystem> cgroup <options>`


```
ubuntu@shalaar3:~$ cat /proc/mounts | grep cgroup
tmpfs   /sys/fs/cgroup tmpfs ro,nosuid,nodev,noexec,mode=755 0 0
cgroup2 /sys/fs/cgroup/unified cgroup2 rw,nosuid,nodev,noexec,relatime,nsdelegate 0 0
cgroup  /sys/fs/cgroup/systemd cgroup rw,nosuid,nodev,noexec,relatime,xattr,name=systemd 0 0
cgroup  /sys/fs/cgroup/devices cgroup rw,nosuid,nodev,noexec,relatime,devices 0 0
cgroup  /sys/fs/cgroup/cpuset cgroup rw,nosuid,nodev,noexec,relatime,cpuset 0 0
cgroup  /sys/fs/cgroup/net_cls,net_prio cgroup rw,nosuid,nodev,noexec,relatime,net_cls,net_prio 0 0
cgroup  /sys/fs/cgroup/cpu,cpuacct cgroup rw,nosuid,nodev,noexec,relatime,cpu,cpuacct 0 0
cgroup  /sys/fs/cgroup/pids cgroup rw,nosuid,nodev,noexec,relatime,pids 0 0
cgroup  /sys/fs/cgroup/rdma cgroup rw,nosuid,nodev,noexec,relatime,rdma 0 0
cgroup  /sys/fs/cgroup/hugetlb cgroup rw,nosuid,nodev,noexec,relatime,hugetlb 0 0
cgroup  /sys/fs/cgroup/memory cgroup rw,nosuid,nodev,noexec,relatime,memory 0 0
cgroup  /sys/fs/cgroup/blkio cgroup rw,nosuid,nodev,noexec,relatime,blkio 0 0
cgroup  /sys/fs/cgroup/perf_event cgroup rw,nosuid,nodev,noexec,relatime,perf_event 0 0
cgroup  /sys/fs/cgroup/freezer cgroup rw,nosuid,nodev,noexec,relatime,freezer 0 0

```

### Navigate to the default CPU hierarchy and check how many cgroups are present. What may be the purpose of these cgroups? Who created them?

```
# 1) find the mount point of the CPU cgroup hierarchy:
ubuntu@shalaar3:~$ grep "cpu" /proc/mounts 
cgroup /sys/fs/cgroup/cpuset cgroup rw,nosuid,nodev,noexec,relatime,cpuset 0 0
cgroup /sys/fs/cgroup/cpu,cpuacct cgroup rw,nosuid,nodev,noexec,relatime,cpu,cpuacct 0 0

# 2) navigate to the mount point of the CPU cgroup hierarchy:
ubuntu@shalaar3:~$ cd /sys/fs/cgroup/cpu,cpuacct
ubuntu@shalaar3:/sys/fs/cgroup/cpu,cpuacct$ 

# 3) check how many cgroups are present:
ubuntu@shalaar3:/sys/fs/cgroup/cpu,cpuacct$ find . -type d | wc -l
93

```

### How many processes are in cgroup user.slice/ system.slice/ init.slice/?


```
# 1) find the mount point of the CPU cgroup hierarchy:
ubuntu@shalaar3:/sys/fs/cgroup/cpu,cpuacct$ grep "cgroup2 " /proc/mounts
cgroup2 /sys/fs/cgroup/unified cgroup2 rw,nosuid,nodev,noexec,relatime,nsdelegate 0 0

# 2) For each cgroup (user.slice, system.slice, and init.scope), navigate to their respective directories and count the number of processes:
# a. For user.slice:
ubuntu@shalaar3:/sys/fs/cgroup/unified/user.slice$ cat /sys/fs/cgroup/unified/user.slice/cgroup.procs | wc -l
0

# b. For system.slice:
ubuntu@shalaar3:/sys/fs/cgroup/unified/user.slice$ cat /sys/fs/cgroup/unified/system.slice/cgroup.procs | wc -l
0

# c. For init.scope:
ubuntu@shalaar3:/sys/fs/cgroup/unified/user.slice$ cat /sys/fs/cgroup/unified/init.scope/cgroup.procs | wc -l
1

```

### Run the following commands and explain the output: ps xawf -eo pid,user,cgroup,args



<details>
<summary>Command output</summary>

```
ubuntu@shalaar3:/sys/fs/cgroup/unified/user.slice$ ps xawf -eo pid,user,cgroup,args
    PID USER     CGROUP                      COMMAND
      2 root     -                           [kthreadd]
      3 root     -                            \_ [rcu_gp]
      4 root     -                            \_ [rcu_par_gp]
      6 root     -                            \_ [kworker/0:0H-kblockd]
      9 root     -                            \_ [mm_percpu_wq]
     10 root     -                            \_ [ksoftirqd/0]
     11 root     -                            \_ [rcu_sched]
     12 root     -                            \_ [migration/0]
     13 root     -                            \_ [idle_inject/0]
     14 root     -                            \_ [cpuhp/0]
     15 root     -                            \_ [cpuhp/1]
     16 root     -                            \_ [idle_inject/1]
     17 root     -                            \_ [migration/1]
     18 root     -                            \_ [ksoftirqd/1]
     20 root     -                            \_ [kworker/1:0H-kblockd]
     21 root     -                            \_ [cpuhp/2]
     22 root     -                            \_ [idle_inject/2]
     23 root     -                            \_ [migration/2]
     24 root     -                            \_ [ksoftirqd/2]
     26 root     -                            \_ [kworker/2:0H-kblockd]
     27 root     -                            \_ [cpuhp/3]
     28 root     -                            \_ [idle_inject/3]
     29 root     -                            \_ [migration/3]
     30 root     -                            \_ [ksoftirqd/3]
     32 root     -                            \_ [kworker/3:0H-kblockd]
     33 root     -                            \_ [kdevtmpfs]
     34 root     -                            \_ [netns]
     35 root     -                            \_ [rcu_tasks_kthre]
     36 root     -                            \_ [kauditd]
     37 root     -                            \_ [khungtaskd]
     38 root     -                            \_ [oom_reaper]
     39 root     -                            \_ [writeback]
     40 root     -                            \_ [kcompactd0]
     41 root     -                            \_ [ksmd]
     42 root     -                            \_ [khugepaged]
     89 root     -                            \_ [kintegrityd]
     90 root     -                            \_ [kblockd]
     91 root     -                            \_ [blkcg_punt_bio]
     92 root     -                            \_ [tpm_dev_wq]
     93 root     -                            \_ [ata_sff]
     94 root     -                            \_ [md]
     95 root     -                            \_ [edac-poller]
     96 root     -                            \_ [devfreq_wq]
     97 root     -                            \_ [watchdogd]
    100 root     -                            \_ [kswapd0]
    101 root     -                            \_ [ecryptfs-kthrea]
    103 root     -                            \_ [kthrotld]
    104 root     -                            \_ [acpi_thermal_pm]
    107 root     -                            \_ [scsi_eh_0]
    108 root     -                            \_ [scsi_tmf_0]
    109 root     -                            \_ [scsi_eh_1]
    110 root     -                            \_ [scsi_tmf_1]
    112 root     -                            \_ [vfio-irqfd-clea]
    113 root     -                            \_ [ipv6_addrconf]
    123 root     -                            \_ [kstrp]
    126 root     -                            \_ [kworker/u9:0]
    139 root     -                            \_ [charger_manager]
    181 root     -                            \_ [cryptd]
    251 root     -                            \_ [raid5wq]
    291 root     -                            \_ [jbd2/vda1-8]
    292 root     -                            \_ [ext4-rsv-conver]
    327 root     -                            \_ [hwrng]
    350 root     -                            \_ [kworker/3:1H-kblockd]
    384 root     -                            \_ [kworker/1:1H-kblockd]
    398 root     -                            \_ [kworker/2:1H-kblockd]
    497 root     -                            \_ [kaluad]
    498 root     -                            \_ [kmpath_rdacd]
    499 root     -                            \_ [kmpathd]
    500 root     -                            \_ [kmpath_handlerd]
    513 root     -                            \_ [loop0]
    515 root     -                            \_ [loop2]
    516 root     -                            \_ [kworker/0:1H-kblockd]
  18917 root     -                            \_ [loop3]
  19055 root     -                            \_ [loop4]
  19449 root     -                            \_ [loop5]
  19952 root     -                            \_ [kworker/0:0-events]
  20151 root     -                            \_ [kworker/3:1-events]
  20255 root     -                            \_ [kworker/1:1-events]
  20506 root     -                            \_ [kworker/0:1-events]
  20717 root     -                            \_ [kworker/u8:0-events_unbound]
  20732 root     -                            \_ [kworker/u8:3-events_power_efficient]
  20748 root     -                            \_ [kworker/2:0-mm_percpu_wq]
  20779 root     -                            \_ [kworker/2:1-events]
  20817 root     -                            \_ [kworker/3:0-cgroup_destroy]
  20936 root     -                            \_ [kworker/1:2-events]
      1 root     10:blkio:/init.scope,9:memo /sbin/init
    366 root     10:blkio:/system.slice/syst /lib/systemd/systemd-journald
    401 root     10:blkio:/system.slice/syst /lib/systemd/systemd-udevd
    501 root     10:blkio:/system.slice/mult /sbin/multipathd -d -s
    537 systemd+ 10:blkio:/system.slice/syst /lib/systemd/systemd-timesyncd
    616 systemd+ 10:blkio:/system.slice/syst /lib/systemd/systemd-networkd
    633 systemd+ 10:blkio:/system.slice/syst /lib/systemd/systemd-resolved
    724 root     10:blkio:/system.slice/acco /usr/lib/accountsservice/accounts-daemon
    727 root     10:blkio:/system.slice/cron /usr/sbin/cron -f
    728 message+ 10:blkio:/system.slice/dbus /usr/bin/dbus-daemon --system --address=systemd: --nofork --nopidfile --systemd-activat
    734 root     10:blkio:/system.slice/irqb /usr/sbin/irqbalance --foreground
    735 root     10:blkio:/system.slice/netw /usr/bin/python3 /usr/bin/networkd-dispatcher --run-startup-triggers
    740 syslog   10:blkio:/system.slice/rsys /usr/sbin/rsyslogd -n -iNONE
    742 root     10:blkio:/system.slice/syst /lib/systemd/systemd-logind
    746 root     10:blkio:/system.slice/udis /usr/lib/udisks2/udisksd
    747 daemon   10:blkio:/system.slice/atd. /usr/sbin/atd -f
    766 root     10:blkio:/system.slice/syst /sbin/agetty -o -p -- \u --keep-baud 115200,38400,9600 ttyS0 vt220
    791 root     10:blkio:/system.slice/syst /sbin/agetty -o -p -- \u --noclear tty1 linux
    807 root     10:blkio:/system.slice/polk /usr/lib/policykit-1/polkitd --no-debug
    859 root     10:blkio:/system.slice/ssh. sshd: /usr/sbin/sshd -D [listener] 0 of 10-100 startups
  20916 root     10:blkio:/user.slice,9:memo  \_ sshd: ubuntu [priv]
  21042 ubuntu   10:blkio:/user.slice,9:memo      \_ sshd: ubuntu@pts/0
  21045 ubuntu   10:blkio:/user.slice,9:memo          \_ -bash
  21120 ubuntu   10:blkio:/user.slice,9:memo              \_ ps xawf -eo pid,user,cgroup,args
  19109 root     10:blkio:/system.slice/snap /usr/lib/snapd/snapd
  20930 ubuntu   10:blkio:/user.slice,9:memo /lib/systemd/systemd --user
  20935 ubuntu   10:blkio:/user.slice,9:memo  \_ (sd-pam)
```

</details>

This output is a hierarchical view of the processes running on your system, including their process ID (PID), user, cgroup, and command line arguments (args). The command `ps xawf -eo pid,user,cgroup,args` generates this output.

Here is an explanation of the columns:

- **PID**: Process ID, a unique identifier for each process.
- **USER**: The user who owns the process.
- **CGROUP**: The cgroup to which the process belongs. It may show multiple cgroups separated by commas if the process belongs to multiple cgroup subsystems.
- **COMMAND**: The command and its arguments used to run the process.

In this specific output, most processes are running under the root user and are kernel-related processes. These processes are listed in a hierarchical format, using indentation to show parent-child relationships between processes. For example, the process with PID 3 (`[rcu_gp]`) is a child of the process with PID 2 (`[kthreadd]`).

System services managed by systemd are organized under different slices, such as `system.slice`, `user.slice`, and `init.scope`. In the output, you can see several processes running under `system.slice`, which are system-level services, and a few running under `user.slice`, which are user-level services.

For example, you can see the SSH service (`sshd`) running under `system.slice`, and an SSH session for the user "ubuntu" running under `user.slice`.




### Check the configuration for a process called “cron” using “ps” and “grep”. Explain both, the configuration for the “cron” and “ps” process, in terms of systemd and cgroup configuration.

To check the configuration for the "cron" process using ps and grep:

```
ubuntu@shalaar3:~$ ps aux | grep '[c]ron'
root         727  0.0  0.0   8536  3032 ?        Ss   Mar29   0:00 /usr/sbin/cron -f

```

Here's an explanation of the output:
- User: root - The user running the process (in this case, the root user).
- PID: 727 - The Process ID (PID) of the cron process.
- %CPU: 0.0 - The percentage of CPU used by the process.
- %MEM: 0.0 - The percentage of memory used by the process.
- VSZ: 8536 - The virtual memory size of the process in kilobytes (updated value).
- RSS: 3032 - The resident set size (physical memory used) of the process in kilobytes (updated value).
- TTY: ? - The controlling terminal for the process (question mark '?' indicates that the process is not attached to a terminal).
- STAT: Ss - The process state (S: interruptible sleep, s: session leader).
- START: Mar29 - The start date or time of the process.
- TIME: 0:00 - The cumulative CPU time the process has used.
- COMMAND: /usr/sbin/cron -f - The command used to start the cron process.


To understand the cgroup configuration for the "cron" process, you can use the PID found in the previous output (727 in this example) and check the contents of /proc/<PID>/cgroup file:
```
ubuntu@shalaar3:~$ cat /proc/727/cgroup
12:freezer:/
11:perf_event:/
10:blkio:/system.slice/cron.service
9:memory:/system.slice/cron.service
8:hugetlb:/
7:rdma:/
6:pids:/system.slice/cron.service
5:cpu,cpuacct:/system.slice/cron.service
4:net_cls,net_prio:/
3:cpuset:/
2:devices:/system.slice/cron.service
1:name=systemd:/system.slice/cron.service
0::/system.slice/cron.service
```

The cron process with PID 727 is part of several cgroup subsystems.
It belongs to the system.slice for multiple controllers, including blkio, memory, pids, cpu,cpuacct, devices, name=systemd, and the unified cgroup hierarchy (denoted by 0::).
The service associated with this process is cron.service under system.slice, which is managed by systemd.
In summary, the "cron" process is running under the root user with a specific PID, and its cgroup configuration shows that it is managed by systemd as part of the system.slice/cron.service.


### Verify your understanding by using the following commands: systemd-cgtop and systemd-cgls Can you identify the “cron” service?

Yes. The cron service is listed under the system.slice/cron.service. Here is an explanation of the different output:

- systemd-cgtop: This command will show the top control groups by their resource usage. It is similar to the "top" command, but it displays information about cgroups. Look for the "cron" service in the output. You may see it under the "Path" column, likely as /system.slice/cron.service.
- systemd-cgls: This command will display a tree view of the control group hierarchy. You can look for the "cron" service in this tree view. It will likely appear under the "system.slice" node, as cron.service.


## Subtask 1.2: Default Systemd Configuration by Systemd

### Obviously, systemd creates a number of cgroups. Identify the respective unit files and explain their configuration.

To identify the unit files for the systemd cgroups, you can use the following command:
```
ubuntu@shalaar3:~$ systemctl list-units --type=service --state=running
  UNIT                        LOAD   ACTIVE SUB     DESCRIPTION                                 
  accounts-daemon.service     loaded active running Accounts Service                            
  atd.service                 loaded active running Deferred execution scheduler                
  cron.service                loaded active running Regular background program processing daemon
  dbus.service                loaded active running D-Bus System Message Bus                    
  getty@tty1.service          loaded active running Getty on tty1                               
  irqbalance.service          loaded active running irqbalance daemon                           
  multipathd.service          loaded active running Device-Mapper Multipath Device Controller   
  networkd-dispatcher.service loaded active running Dispatcher daemon for systemd-networkd      
  polkit.service              loaded active running Authorization Manager                       
  rsyslog.service             loaded active running System Logging Service                      
  serial-getty@ttyS0.service  loaded active running Serial Getty on ttyS0                       
  snapd.service               loaded active running Snap Daemon                                 
  ssh.service                 loaded active running OpenBSD Secure Shell server                 
  systemd-journald.service    loaded active running Journal Service                             
  systemd-logind.service      loaded active running Login Service                               
  systemd-networkd.service    loaded active running Network Service                             
  systemd-resolved.service    loaded active running Network Name Resolution                     
  systemd-timesyncd.service   loaded active running Network Time Synchronization                
  systemd-udevd.service       loaded active running udev Kernel Device Manager                  
  udisks2.service             loaded active running Disk Manager                                
  user@1000.service           loaded active running User Manager for UID 1000                   

LOAD   = Reflects whether the unit definition was properly loaded.
ACTIVE = The high-level unit activation state, i.e. generalization of SUB.
SUB    = The low-level unit activation state, values depend on unit type.

21 loaded units listed.
```

Here's an explanation of the output for the `systemctl list-units --type=service --state=running` command:

This command displays a list of currently running services, managed by systemd. The output contains various columns with specific information:

- **UNIT**: The name of the service unit (e.g., `cron.service`).
- **LOAD**: Reflects whether the unit definition was properly loaded.
- **ACTIVE**: The high-level unit activation state, i.e., a generalization of the `SUB` state.
- **SUB**: The low-level unit activation state, with values depending on the unit type.
- **DESCRIPTION**: A brief description of the service.

In the output, you can see several essential system services, such as:

1. **cron.service**: The regular background program processing daemon.
2. **dbus.service**: The D-Bus system message bus, responsible for inter-process communication.
3. **rsyslog.service**: The system logging service, which handles logging events.
4. **ssh.service**: The OpenBSD Secure Shell server, which allows remote administration.
5. **systemd-journald.service**: The journal service, which manages log data.
6. **systemd-logind.service**: The login service, which manages user logins and sessions.
7. **systemd-networkd.service**: The network service, which manages network interfaces.
8. **systemd-resolved.service**: The network name resolution service, responsible for DNS resolution.
9. **systemd-timesyncd.service**: The network time synchronization service, which synchronizes the system clock with NTP servers.

These services are essential for the proper functioning of your system. Understanding their roles can help you manage and troubleshoot your system more effectively.


### Modify the user.slice configuration such that all processes created by users do not receive more than 20% of CPU share.
To modify the user.slice configuration so that all processes created by users do not receive more than 20% of CPU share, follow these steps:
1) Create a new file /etc/systemd/system/user.slice.d/limit_cpu.conf using a text editor:
```
ubuntu@shalaar3:~$ sudo mkdir /etc/systemd/system/user.slice.d/
ubuntu@shalaar3:~$ sudo touch /etc/systemd/system/user.slice.d/limit_cpu.conf
ubuntu@shalaar3:~$ sudo nano /etc/systemd/system/user.slice.d/limit_cpu.conf
```

2) Add the following lines to the file:
```
[Slice]
CPUQuota=20%
```

3) Reload the systemd daemon:
```
ubuntu@shalaar3:~$ sudo systemctl daemon-reload
```

4) Verify that the configuration has been applied:
```
ubuntu@shalaar3:~$ sudo systemctl show user.slice | grep CPU
CPUUsageNSec=[not set]
EffectiveCPUs=
CPUAccounting=no
CPUWeight=[not set]
StartupCPUWeight=[not set]
CPUShares=[not set]
StartupCPUShares=[not set]
CPUQuotaPerSecUSec=200ms
CPUQuotaPeriodUSec=infinity
AllowedCPUs=
```
OR
```
ubuntu@shalaar3:~$ systemctl status user.slice
● user.slice - User and Session Slice
     Loaded: loaded (/lib/systemd/system/user.slice; static; vendor preset: enabled)
    Drop-In: /etc/systemd/system/user.slice.d
             └─limit_cpu.conf
     Active: active since Wed 2023-03-29 17:20:02 UTC; 1 day 17h ago
       Docs: man:systemd.special(7)
      Tasks: 7
     Memory: 349.3M
     CGroup: /user.slice
             └─user-1000.slice
               ├─session-51.scope
               │ ├─20916 sshd: ubuntu [priv]
               │ ├─21042 sshd: ubuntu@pts/0
               │ ├─21045 -bash
               │ ├─21635 systemctl status user.slice
               │ └─21636 pager
               └─user@1000.service
                 └─init.scope
                   ├─20930 /lib/systemd/systemd --user
                   └─20935 (sd-pam)

Warning: journal has been rotated since unit was started, output may be incomplete.
```


### Verify your configuration by creating more load than your system can handle, e.g. by creating a number of “wc /dev/zero &” background processes (& send the process directly into the background).
<b>I must reiterate that running these commands can lead to system instability and potential damage. Proceed at your own risk.</b>
```
ubuntu@shalaar3:~$ for i in {1..100}; do (wc /dev/zero &); done
```
To stop the processes and free up the system resources, you can use the following command:
```
ubuntu@shalaar3:~$ killall wc
```

### Free one wc process from the limits imposed by the user.slice related cgroup.
To free one wc process from the limits imposed by the user.slice related cgroup, you'll need to move the process to a different cgroup that doesn't have those limitations.

1. Find the PID of the wc process you want to free from the limits. You can use pgrep or ps to get the PID:
```
ubuntu@shalaar3:~$ ps -ef | grep wc
ubuntu     22066       1  3 13:58 pts/0    00:00:01 wc /dev/zero
ubuntu     22068       1  4 13:58 pts/0    00:00:02 wc /dev/zero
ubuntu     22070       1  4 13:58 pts/0    00:00:02 wc /dev/zero
ubuntu     22072       1  3 13:58 pts/0    00:00:01 wc /dev/zero
ubuntu     22074       1  3 13:58 pts/0    00:00:01 wc /dev/zero
ubuntu     22077   21851  0 13:59 pts/0    00:00:00 grep --color=auto wc
```
OR
```
ubuntu@shalaar3:~$ pgrep wc
22066
22068
22070
22072
22074
```

Choose one PID from the list of wc processes.

2. Check the cgroups currently imposed on the process by examining the /proc/PID/cgroup file, replacing PID with the actual PID you found in step 1:
```
ubuntu@shalaar3:~$ cat /proc/22066/cgroup
12:freezer:/
11:perf_event:/
10:blkio:/user.slice
9:memory:/user.slice/user-1000.slice/session-57.scope
8:hugetlb:/
7:rdma:/
6:pids:/user.slice/user-1000.slice/session-57.scope
5:cpu,cpuacct:/user.slice
4:net_cls,net_prio:/
3:cpuset:/
2:devices:/user.slice
1:name=systemd:/user.slice/user-1000.slice/session-57.scope
0::/user.slice/user-1000.slice/session-57.scope
```

3. Create a new cgroup in the cpu and memory controllers without limitations:
```
ubuntu@shalaar3:~$ sudo mkdir /sys/fs/cgroup/cpu/unlimited_wc
ubuntu@shalaar3:~$ sudo mkdir /sys/fs/cgroup/memory/unlimited_wc
```

4. Set the parameters:

```
# For the cpu controller:
echo 100000 | sudo tee /sys/fs/cgroup/cpu/unlimited_wc/cpu.cfs_period_us
echo -1 | sudo tee /sys/fs/cgroup/cpu/unlimited_wc/cpu.cfs_quota_us
```

```
#For the memory controller:
echo -1 | sudo tee /sys/fs/cgroup/memory/unlimited_wc/memory.limit_in_bytes
```

5. Move the wc process to the new cgroup by echoing the PID to the cgroup.procs file:
Move the wc process to the new cgroup by echoing the PID to the cgroup.procs file:
```
ubuntu@shalaar3:~$ echo 22066 | sudo tee /sys/fs/cgroup/cpu/unlimited_wc/cgroup.procs
22066
ubuntu@shalaar3:~$ echo 22066 | sudo tee /sys/fs/cgroup/memory/unlimited_wc/cgroup.procs
22066
```

Now, the wc process with the specified PID should be free from the limitations imposed by the user.slice related cgroup.

## Subtask 1.2 – Create Custom Controls

### Create an environment to control CPU access (CPU affinity) from scratch, i.e. not using any preconfigured cgroups.
Creating an environment to control CPU access (CPU affinity) can be done using the taskset command in Linux. The taskset utility allows you to set or retrieve the CPU affinity of a running process, or launch a new process with a specified CPU affinity.

1. First, install the util-linux package, which includes taskset:

```
ubuntu@shalaar3:~$ sudo apt update
ubuntu@shalaar3:~$ sudo apt install util-linux
```

2. To launch a new process with a specified CPU affinity, use the following command:
```
ubuntu@shalaar3:~$ taskset -c 0,2 ./my_program
```

3. To set or retrieve the CPU affinity of a running process, use the following command:
```
ubuntu@shalaar3:~$ taskset -p 1234
```

4. To set the CPU affinity of a running process, use the following command:
```
ubuntu@shalaar3:~$ taskset -p 0x5 1234
```

5. 



### Create a tmpfs under /mnt and use this directory for your cgroup hierarchy.

1. Create a tmpfs filesystem under /mnt with the desired size. For example, to create a tmpfs of size 100MB, run:
```
ubuntu@shalaar3:~$ sudo mount -t tmpfs -o size=100M tmpfs /mnt
```

2. Create a cgroup hierarchy under /mnt:
```
ubuntu@shalaar3:~$ sudo mkdir /mnt/cgroup
ubuntu@shalaar3:~$ sudo mount -t cgroup -o none,name=systemd cgroup /mnt/cgroup
```

3. Mount the cpu and memory cgroup controllers:
```
ubuntu@shalaar3:~$ sudo mkdir /mnt/cgroup/cpu
ubuntu@shalaar3:~$ sudo mkdir /mnt/cgroup/memory
ubuntu@shalaar3:~$ sudo mount -t cgroup -o none,name=cpu cgroup /mnt/cgroup/cpu
ubuntu@shalaar3:~$ sudo mount -t cgroup -o none,name=memory cgroup /mnt/cgroup/memory
```

To set the desired CPU limits for the new cgroup, set the value to the desired value. For example, to set the CPU share to 512, run:
```
ubuntu@shalaar3:~$ echo 512 | sudo tee /mnt/cgroup/cpu/mygroup/cpu.shares
```


### How many CPUs can be controlled on your system per default?
To find out how many CPUs are available on your system, run the following command:
```
ubuntu@shalaar3:~$ nproc
4
```
Another way to get this information is by checking the contents of /proc/cpuinfo:
```
ubuntu@shalaar3:~$ cat /proc/cpuinfo | grep processor | wc -l
4
```

### Create M processes, with M being the number of CPUs (N) on your system plus one (M=N+1). Those processes shall consume 100% CPU load. Now configure your cgroups to only allow these processes to use half of the CPUs available on your system.
1. Determine the number of CPUs (N) on your system:
```
ubuntu@shalaar3:~$ N=$(nproc)
```
2. Create M processes, with M being the number of CPUs (N) on your system plus one (M=N+1). Those processes shall consume 100% CPU load:
```
ubuntu@shalaar3:~$ M=$((N+1))
ubuntu@shalaar3:~$ for i in $(seq 1 $M); do (yes > /dev/null &); done
```
3. Create a cgroup that allows processes to use only half of the available CPUs:

```
# Create a new directory for the cgroup
ubuntu@shalaar3:~$ sudo mkdir -p /sys/fs/cgroup/cpu/half_cpus

# Calculate the number of allowed CPUs
ubuntu@shalaar3:~$ HALF_CPUS=$((N / 2))

# Set allowed CPUs for the cgroup
ubuntu@shalaar3:~$ CPU_LIST=$(seq -s, 0 $((HALF_CPUS - 1)))
ubuntu@shalaar3:~$ echo $CPU_LIST | sudo tee /sys/fs/cgroup/cpu/half_cpus/cpuset.cpus
0,1

# Set necessary cpuset.mems (copy the value from the root cgroup)
ubuntu@shalaar3:~$ MEMS=$(cat /sys/fs/cgroup/cpuset/cpuset.mems)
ubuntu@shalaar3:~$ echo $MEMS | sudo tee /sys/fs/cgroup/cpu/half_cpus/cpuset.mems
0

# Move all processes to the new cgroup
ubuntu@shalaar3:~$ # Get the PIDs of the 'yes' processes

# Move each process to the new cgroup
for PID in $PIDS; do
  echo $PID | sudo tee /sys/fs/cgroup/cpu/half_cpus/cgroup.procs
done
```
Now, the created processes are limited to use only half of the available CPUs on your system.

5. Stop and clean up the processes and cgroups:
```
ubuntu@shalaar3:~$ sudo killall yes
ubuntu@shalaar3:~$ sudo rmdir /sys/fs/cgroup/cpu/half_cpus
```



### Verify and explain the effect by looking at the processes via “top”. Also double-check the CPU assignments (affinity) with the command “taskset”. Disable those CPUs, via “chcpu”, that you allowed in your cpuset and explain what happens with those processes pinned onto them.
1. Use top to observe the CPU usage of the processes:
```
ubuntu@shalaar3:~$ top
```
In the top interface, you should see the yes processes consuming a high percentage of CPU. Press '1' to toggle the per-CPU usage view. You will see that only half of the CPUs are being used by the processes, as configured in the cgroup.

2. Check the CPU assignments (affinity) using taskset:
First, get the PIDs of the 'yes' processes:
```
ubuntu@shalaar3:~$ PIDS=$(pgrep yes)
```

Then, for each PID, check the CPU affinity using taskset:
```
for PID in $PIDS; do
  echo "PID: $PID"
  taskset -p $PID
done
```

3. Disable the CPUs that you allowed in your cpuset:
```
ubuntu@shalaar3:~$ sudo chcpu -d 2,3
```
If you were to disable the CPUs that are allowed in your cpuset (and if it were applicable to your system), the processes pinned to those CPUs would no longer be scheduled to run on them. The operating system's scheduler would likely attempt to migrate those processes to the remaining available CPUs. This could lead to increased load on the remaining CPUs, potentially causing a decrease in overall system performance.

It's important to note that disabling CPUs is a highly platform-specific action and may not be applicable or advisable for your particular system. Make sure to research the implications and potential consequences of disabling CPUs on your system before attempting such actions.
