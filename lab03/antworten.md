# Task 1 – Programs and Processes

## Subtask 1.1 – Processes Basics

# Using “top”, explain the elements of the “Summary Display”

[From the Manpage](https://manpages.ubuntu.com/manpages/xenial/man1/top.1.html):
```top``` provides a dynamic, real time overview of a running system. It shows a summary of the system load and the processes as well as the threads currently being managed by the kernel.
It can be used to get a quick overview of the system and to detect processes that consume too many resources.

Comprehensive explanation:
```
top is a command-line utility in Ubuntu and other Unix-based systems that provides a live, dynamic view of the processes running on a system. The Summary Display in top is the first section of its output, which shows the overall system status and resource usage. Here's a brief explanation of the elements you'll typically see in the Summary Display:

top: Shows the current time, uptime (time since the system was last booted), number of users logged in, and the average system load for the last 1, 5, and 15 minutes.
Tasks: Displays the total number of tasks (or processes) on the system, as well as the number of tasks in different states: running, sleeping, stopped, and zombie.
%Cpu(s): Shows the percentage of CPU usage, broken down into different categories:
- us: User CPU time (percentage of time spent executing user-level code)
- sy: System CPU time (percentage of time spent executing kernel-level code)
- ni: Nice CPU time (percentage of time spent executing low-priority user-level code)
- id: Idle time (percentage of time the CPU spends doing nothing)
- wa: I/O wait time (percentage of time the CPU spends waiting for I/O operations to complete)
- hi: Hardware interrupts (percentage of time spent handling hardware interrupts)
- si: Software interrupts (percentage of time spent handling software interrupts)
- st: Steal time (percentage of time spent in involuntary wait by the virtual CPU while the hypervisor services other tasks)
MiB Mem: Displays memory usage information in mebibytes (MiB), including total memory, used memory, free memory, and available memory (an estimate of how much memory is available for starting new applications without swapping).
MiB Swap: Shows the swap space usage information in mebibytes (MiB), including total swap, used swap, and free swap.
Please note that the exact elements and their layout might vary slightly depending on the version of top and the Linux distribution you're using.
```

# Which process has PID 1 and PID 2? Who is the owner of these processes?
    - Systemd is the process with PID 1. It is the process that starts all other processes. It is owned by root.
    - kthreadd is the process with PID 2. It is the process that manages other kernel threads. It is owned by root.
```
ubuntu@shalaar3:~$ top
   PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                                                                                                           
      1 root      20   0  170692  12940   8460 S   0.0   0.3   0:34.89 systemd                                                                                                           
      2 root      20   0       0      0      0 S   0.0   0.0   0:00.04 kthreadd                                                                                                          
      3 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 rcu_gp                                                                                                            
      4 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 rcu_par_gp                     
```
# What is the PID of your terminal? Who is the owner?

```
ubuntu@shalaar3:~$ echo $$
32607

```

This command will print the PID of the shell (terminal) process running in the current terminal window. When you run this command, you will see the PID of your current terminal session displayed as the output. Please note that this command will give you the PID of the shell (e.g., bash, zsh, etc.) running in the terminal, not the PID of the terminal emulator application itself (e.g., gnome-terminal, xterm, etc.).

# Show the Environmental Variables of your terminal....

```
ubuntu@shalaar3:~$ printenv
SHELL=/bin/bash
PWD=/home/ubuntu
LOGNAME=ubuntu
XDG_SESSION_TYPE=tty
MOTD_SHOWN=pam
HOME=/home/ubuntu
LANG=C.UTF-8
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
SSH_CONNECTION=172.27.158.144 50633 10.0.3.42 22
LESSCLOSE=/usr/bin/lesspipe %s %s
XDG_SESSION_CLASS=user
TERM=xterm-256color
LESSOPEN=| /usr/bin/lesspipe %s
USER=ubuntu
SHLVL=1
XDG_SESSION_ID=368
LC_CTYPE=C.UTF-8
XDG_RUNTIME_DIR=/run/user/1000
SSH_CLIENT=172.27.158.144 50633 22
XDG_DATA_DIRS=/usr/local/share:/usr/share:/var/lib/snapd/desktop
PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
SSH_TTY=/dev/pts/0
_=/usr/bin/printenv
```

# ... add a variable named Name and assign your surname to it.

```
ubuntu@shalaar3:~$ export Name=shalaar3
ubuntu@shalaar3:~$ echo $Name
shalaar3
```

# Study the “tail” program and find out how to monitor the evolution of a file in real-time. Use this tool to monitor system information available in the following file: /var/log/syslog

tail is a command-line utility that displays the last part (usually the last 10 lines) of a file. To monitor the evolution of a file in real-time, you can use the ```-f``` (follow) option, which makes tail output new data as the file grows.

To monitor the system information available in the ```/var/log/syslog``` file in real-time, run the following command: 

```
ubuntu@shalaar3:~$ sudo tail -f /var/log/syslog
Mar 23 17:00:26 shalaar3 systemd[32481]: Reached target Main User Target.
Mar 23 17:00:26 shalaar3 systemd[32481]: Startup finished in 114ms.
Mar 23 17:14:03 shalaar3 systemd[1]: Starting Message of the Day...
Mar 23 17:14:08 shalaar3 50-motd-news[32662]:  * Strictly confined Kubernetes makes edge and IoT secure. Learn how MicroK8s
Mar 23 17:14:08 shalaar3 50-motd-news[32662]:    just raised the bar for easy, resilient and secure K8s cluster deployment.
Mar 23 17:14:08 shalaar3 50-motd-news[32662]:    https://ubuntu.com/engage/secure-kubernetes-at-the-edge
Mar 23 17:14:08 shalaar3 systemd[1]: motd-news.service: Succeeded.
Mar 23 17:14:08 shalaar3 systemd[1]: Finished Message of the Day.
Mar 23 17:17:01 shalaar3 CRON[32685]: (root) CMD (   cd / && run-parts --report /etc/cron.hourly)
Mar 23 17:33:01 shalaar3 CRON[32694]: (root) CMD (   test -x /etc/cron.daily/popularity-contest && /etc/cron.daily/popularity-contest --crond)

```
# Start a second terminal and observe the output of your monitoring session. What do you notice?

```
# Second shell
armandoshala@mbp16-von-armando ~ % ssh -i .ssh/BSY_MBP_CLOUDLAB ubuntu@IP
[LOGGED IN]
ubuntu@shalaar3:~$ pwd
/home/ubuntu
```

```
# First shell
ubuntu@shalaar3:~$ sudo tail -f /var/log/syslog
[...]
Mar 23 17:37:12 shalaar3 systemd[1]: Started Session 372 of user ubuntu.
```

# On the second terminal, what is the PID and the state of your monitoring process (tail)?

To show the process hierarchy of the tail process, you can use the pstree command along with the -s (show parent) option and the PID of the tail process. First, make sure you've found the PID of the tail process using the method described in the previous answer.

Assuming the PID of the tail process is 12345 (replace this with the actual PID on your system), run the following command in the terminal:

```
ubuntu@shalaar3:~$ ps aux | grep "tail -f" | grep -v grep
root       32697  0.0  0.1  11164  4804 pts/0    S+   17:36   0:00 sudo tail -f /var/log/syslog
root       32699  0.0  0.0   7264   592 pts/0    S+   17:36   0:00 tail -f /var/log/syslog
```

This command will:

- Run ps aux to display a detailed list of all currently running processes.
- Use grep "tail -f" to filter the processes containing the string "tail -f", which will include the tail command with the -f option.
- Apply grep -v grep to exclude the grep process itself from the output.

# Show the process hierarchy of your observer process (tail)

To show the process hierarchy of the tail process, you can use the pstree command along with the -s (show parent) option and the PID of the tail process. First, make sure you've found the PID of the tail process using the method described in the previous answer.

Assuming the PID of the tail process is 12345 (replace this with the actual PID on your system), run the following command in the terminal:

```
# Second shell
ubuntu@shalaar3:~$ pstree -s 32898
systemd───sshd───sshd───sshd───bash───sudo───tail

```
This command will display the process hierarchy, starting from the init or systemd process (PID 1) and moving down through the process tree to the tail process. The output will show you the chain of parent processes leading to the tail command.

# Terminal (kill) the terminal that runs the tail command and explain what happens.
When you kill the terminal running the tail command, the terminal, along with all the processes running within it, will be terminated, including the tail command.

To kill the terminal running the tail command, you can use the kill command followed by the PID of the shell (e.g., bash, zsh, etc.) running in the terminal that is executing the tail command. Please note that this is different from the PID of the tail process itself.

The PID of the shell running the tail command is 32898, run the following command in the other terminal:

```
# Second shell
ubuntu@shalaar3:~$ kill 32898
-bash: kill: (32898) - Operation not permitted
ubuntu@shalaar3:~$ sudo !!
sudo kill 32898
# First shell (Ready for next command because the tail command was killed)
ubuntu@shalaar3:~$
```

<br>
<br>
<br>
<br>
<br>
<br>

# Subtask 1.2 – Job Control

* Study the “Job Control” section of the bash man page

```
JOB CONTROL
       Job control refers to the ability to selectively stop (suspend) the execution of processes and continue (resume) their execution at a later point.  A user typically employs this  facility  via  an
       interactive interface supplied jointly by the operating system kernel's terminal driver and bash.

       The shell associates a job with each pipeline.  It keeps a table of currently executing jobs, which may be listed with the jobs command.  When bash starts a job asynchronously (in the background),
       it prints a line that looks like:

              [1] 25647

       indicating that this job is job number 1 and that the process ID of the last process in the pipeline associated with this job is 25647.  All of the processes in a single pipeline  are  members  of
       the same job.  Bash uses the job abstraction as the basis for job control.

       To  facilitate  the implementation of the user interface to job control, the operating system maintains the notion of a current terminal process group ID.  Members of this process group (processes
       whose process group ID is equal to the current terminal process group ID) receive keyboard-generated signals such as SIGINT.  These processes are said to be in  the  foreground.   Background  pro‐
       cesses are those whose process group ID differs from the terminal's; such processes are immune to keyboard-generated signals.  Only foreground processes are allowed to read from or, if the user so
       specifies with stty tostop, write to the terminal.  Background processes which attempt to read from (write to when stty tostop is in effect) the terminal are sent a SIGTTIN (SIGTTOU) signal by the
       kernel's terminal driver, which, unless caught, suspends the process.

       If the operating system on which bash is running supports job control, bash contains facilities to use it.  Typing the suspend character (typically ^Z, Control-Z) while a process is running causes
       that process to be stopped and returns control to bash.  Typing the delayed suspend character (typically ^Y, Control-Y) causes the process to be stopped when it attempts to  read  input  from  the
       terminal, and control to be returned to bash.  The user may then manipulate the state of this job, using the bg command to continue it in the background, the fg command to continue it in the fore‐
       ground, or the kill command to kill it.  A ^Z takes effect immediately, and has the additional side effect of causing pending output and typeahead to be discarded.

       There are a number of ways to refer to a job in the shell.  The character % introduces a job specification (jobspec).  Job number n may be referred to as %n.  A job may also be referred to using a
       prefix  of  the  name used to start it, or using a substring that appears in its command line.  For example, %ce refers to a stopped ce job.  If a prefix matches more than one job, bash reports an
       error.  Using %?ce, on the other hand, refers to any job containing the string ce in its command line.  If the substring matches more than one job, bash reports an error.  The symbols  %%  and  %+
       refer  to  the shell's notion of the current job, which is the last job stopped while it was in the foreground or started in the background.  The previous job may be referenced using %-.  If there
       is only a single job, %+ and %- can both be used to refer to that job.  In output pertaining to jobs (e.g., the output of the jobs command), the current job is always flagged with  a  +,  and  the
       previous job with a -.  A single % (with no accompanying job specification) also refers to the current job.

       Simply  naming  a  job can be used to bring it into the foreground: %1 is a synonym for ``fg %1'', bringing job 1 from the background into the foreground.  Similarly, ``%1 &'' resumes job 1 in the
       background, equivalent to ``bg %1''.

       The shell learns immediately whenever a job changes state.  Normally, bash waits until it is about to print a prompt before reporting changes in a job's status so as to  not  interrupt  any  other
       output.  If the -b option to the set builtin command is enabled, bash reports such changes immediately.  Any trap on SIGCHLD is executed for each child that exits.

       If  an  attempt  to  exit bash is made while jobs are stopped (or, if the checkjobs shell option has been enabled using the shopt builtin, running), the shell prints a warning message, and, if the
       checkjobs option is enabled, lists the jobs and their statuses.  The jobs command may then be used to inspect their status.  If a second attempt to exit is made without an intervening command, the
       shell does not print another warning, and any stopped jobs are terminated.

       When  the shell is waiting for a job or process using the wait builtin, and job control is enabled, wait will return when the job changes state. The -f option will force wait to wait until the job
       or process terminates before returning.
```

# Start three observer processes and put all of them into the background

To start three observer processes and put them all into the background, you can use the tail -f command as an example of an observer process. Run the following commands in the terminal:
    
```
tail -f /var/log/syslog &
tail -f /var/log/syslog &
tail -f /var/log/syslog &
```

Each command will start a tail -f process that monitors the /var/log/syslog file in real-time, and the ampersand (&) at the end of each command tells the shell to run the process in the background.


# Display the list of background jobs and explain the output

```
ubuntu@shalaar3:~$ jobs
[1]   Running                 tail -f /var/log/syslog &
[2]-  Running                 tail -f /var/log/syslog &
[3]+  Running                 tail -f /var/log/syslog &
```

This output shows information about each background job in the current session:

The numbers in square brackets [ ] represent the job number. These job numbers are assigned by the shell and can be used to refer to a specific background job when using job control commands like fg, bg, kill, etc.
The Running status indicates that each job is currently running in the background.
The command following the status (e.g., tail -f /var/log/syslog &) shows the actual command being executed in the background.
In this example, the output displays three background jobs, all of which are running the tail -f /var/log/syslog command. The & at the end of each command signifies that the process is running in the background.

# Move job number 2 into foreground and press Ctrl + z. List again the job list. What is the difference now?

```
ubuntu@shalaar3:~$ fg 2
tail -f /var/log/syslog
^Z
[2]+  Stopped                 tail -f /var/log/syslog
ubuntu@shalaar3:~$ jobs
[1]   Running                 tail -f /var/log/syslog &
[2]+  Stopped                 tail -f /var/log/syslog
[3]-  Running                 tail -f /var/log/syslog &
```

* Return each job to foreground and terminate it (Ctrl + c)

```
ubuntu@shalaar3:~$ fg 1
tail -f /var/log/syslog
^C
ubuntu@shalaar3:~$ fg 2
tail -f /var/log/syslog
^C
ubuntu@shalaar3:~$ fg 3
tail -f /var/log/syslog
^C
ubuntu@shalaar3:~$ jobs
ubuntu@shalaar3:~$ 
```
or simply do
```
ubuntu@shalaar3:~$ jobs
[1]   Running                 tail -f /var/log/syslog &
[2]-  Running                 tail -f /var/log/syslog &
[3]+  Running                 tail -f /var/log/syslog &
ubuntu@shalaar3:~$ kill %1
ubuntu@shalaar3:~$ kill %2
[1]   Terminated              tail -f /var/log/syslog
ubuntu@shalaar3:~$ kill %3
[2]-  Terminated              tail -f /var/log/syslog
ubuntu@shalaar3:~$ jobs
ubuntu@shalaar3:~$ 

```

<br>
<br>
<br>
<br>
<br>
<br>

# Subtask 1.3 – Process Creation

# Write a Hello World in c

```
ubuntu@shalaar3:~$ touch helloworld.c
ubuntu@shalaar3:~$ nano helloworld.c
ubuntu@shalaar3:~$ cat helloworld.c 

#include <stdio.h>

int main() {
    printf("Hello World\n");
    return 0;
}
```

# create a process that executes your program

```
ubuntu@shalaar3:~$ gcc helloworld.c -o hello
ubuntu@shalaar3:~$ ./hello 
Hello World
```

# Revisit the layout of a binary and print the sizes of sections “Text”, “Data” and “BSS”.

```
ubuntu@shalaar3:~$ size hello
   text	   data	    bss	    dec	    hex	filename
   1565	    600	      8	   2173	    87d	hello
```

#  What is the difference between the “Berkley” and the “Gnu” format?
The "Berkley" and "GNU" formats mentioned here refer to the output formats of the size utility, which is used to display section sizes of binary files. Both formats display the same information but arrange it differently in the output.

The ```Berkley Format``` is the default format used by the size command on Unix and Unix-like systems, including Linux. It displays the section sizes in a more compact manner and is also known as "System V" format. The output includes the text, data, and bss section sizes, along with the total size (in decimal) and the hex value of the combined sizes.
```
ubuntu@shalaar3:~$ size hello
   text	   data	    bss	    dec	    hex	filename
   1565	    600	      8	   2173	    87d	hello
```

The ```GNU format``` provides a more detailed and human-readable output compared to the Berkley format. The output includes section sizes (text, data, and bss), total size, and some additional information about the binary file, such as the architecture, format, and more.

```
ubuntu@shalaar3:~$ size --format=SysV hello
hello  :
section              size    addr
.interp                28     792
.note.gnu.property     32     824
.note.gnu.build-id     36     856
.note.ABI-tag          32     892
.gnu.hash              36     928
.dynsym               168     968
.dynstr               130    1136
.gnu.version           14    1266
.gnu.version_r         32    1280
.rela.dyn             192    1312
.rela.plt              24    1504
.init                  27    4096
.plt                   32    4128
.plt.got               16    4160
.plt.sec               16    4176
.text                 389    4192
.fini                  13    4584
.rodata                16    8192
.eh_frame_hdr          68    8208
.eh_frame             264    8280
.init_array             8   15800
.fini_array             8   15808
.dynamic              496   15816
.got                   72   16312
.data                  16   16384
.bss                    8   16400
.comment               43       0
Total                2216
```

To sum up, the main difference between the Berkley and GNU formats is the way they present the information about the binary file's section sizes. The Berkley format is more compact and displays the sizes in a single line, while the GNU format provides a more detailed output with additional information.


# Use objdump and display all section headers. Revisit the sections above and study the elements of each section. Disassemble the “Text” section.

This command will output a list of all section headers in the binary file, along with their properties such as size, address, and flags.

```
ubuntu@shalaar3:~$ objdump -h hello

hello:     file format elf64-x86-64

Sections:
Idx Name          Size      VMA               LMA               File off  Algn
  0 .interp       0000001c  0000000000000318  0000000000000318  00000318  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  1 .note.gnu.property 00000020  0000000000000338  0000000000000338  00000338  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .note.gnu.build-id 00000024  0000000000000358  0000000000000358  00000358  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .note.ABI-tag 00000020  000000000000037c  000000000000037c  0000037c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .gnu.hash     00000024  00000000000003a0  00000000000003a0  000003a0  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  5 .dynsym       000000a8  00000000000003c8  00000000000003c8  000003c8  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  6 .dynstr       00000082  0000000000000470  0000000000000470  00000470  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  7 .gnu.version  0000000e  00000000000004f2  00000000000004f2  000004f2  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  8 .gnu.version_r 00000020  0000000000000500  0000000000000500  00000500  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  9 .rela.dyn     000000c0  0000000000000520  0000000000000520  00000520  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 10 .rela.plt     00000018  00000000000005e0  00000000000005e0  000005e0  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 11 .init         0000001b  0000000000001000  0000000000001000  00001000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 12 .plt          00000020  0000000000001020  0000000000001020  00001020  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 13 .plt.got      00000010  0000000000001040  0000000000001040  00001040  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 14 .plt.sec      00000010  0000000000001050  0000000000001050  00001050  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 15 .text         00000185  0000000000001060  0000000000001060  00001060  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 16 .fini         0000000d  00000000000011e8  00000000000011e8  000011e8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 17 .rodata       00000010  0000000000002000  0000000000002000  00002000  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 18 .eh_frame_hdr 00000044  0000000000002010  0000000000002010  00002010  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 19 .eh_frame     00000108  0000000000002058  0000000000002058  00002058  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 20 .init_array   00000008  0000000000003db8  0000000000003db8  00002db8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 21 .fini_array   00000008  0000000000003dc0  0000000000003dc0  00002dc0  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 22 .dynamic      000001f0  0000000000003dc8  0000000000003dc8  00002dc8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 23 .got          00000048  0000000000003fb8  0000000000003fb8  00002fb8  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 24 .data         00000010  0000000000004000  0000000000004000  00003000  2**3
                  CONTENTS, ALLOC, LOAD, DATA
 25 .bss          00000008  0000000000004010  0000000000004010  00003010  2**0
                  ALLOC
 26 .comment      0000002b  0000000000000000  0000000000000000  00003010  2**0
                  CONTENTS, READONLY
```

To study the elements of the ".text", ".data", and ".bss" sections, you can use objdump with the -s flag followed by the section name. This will display the contents of the specified section in both hexadecimal and ASCII formats.

For the ".text" section, the output is as follows:
```
ubuntu@shalaar3:~$ objdump -s -j .text hello

hello:     file format elf64-x86-64

Contents of section .text:
 1060 f30f1efa 31ed4989 d15e4889 e24883e4  ....1.I..^H..H..
 1070 f050544c 8d056601 0000488d 0def0000  .PTL..f...H.....
 1080 00488d3d c1000000 ff15522f 0000f490  .H.=......R/....
 1090 488d3d79 2f000048 8d05722f 00004839  H.=y/..H..r/..H9
 10a0 f8741548 8b052e2f 00004885 c07409ff  .t.H.../..H..t..
 10b0 e00f1f80 00000000 c30f1f80 00000000  ................
 10c0 488d3d49 2f000048 8d35422f 00004829  H.=I/..H.5B/..H)
 10d0 fe4889f0 48c1ee3f 48c1f803 4801c648  .H..H..?H...H..H
 10e0 d1fe7414 488b0505 2f000048 85c07408  ..t.H.../..H..t.
 10f0 ffe0660f 1f440000 c30f1f80 00000000  ..f..D..........
 1100 f30f1efa 803d052f 00000075 2b554883  .....=./...u+UH.
 1110 3de22e00 00004889 e5740c48 8b3de62e  =.....H..t.H.=..
 1120 0000e819 ffffffe8 64ffffff c605dd2e  ........d.......
 1130 0000015d c30f1f00 c30f1f80 00000000  ...]............
 1140 f30f1efa e977ffff fff30f1e fa554889  .....w.......UH.
 1150 e5488d3d ac0e0000 e8f3feff ffb80000  .H.=............
 1160 00005dc3 662e0f1f 84000000 00006690  ..].f.........f.
 1170 f30f1efa 41574c8d 3d3b2c00 00415649  ....AWL.=;,..AVI
 1180 89d64155 4989f541 544189fc 55488d2d  ..AUI..ATA..UH.-
 1190 2c2c0000 534c29fd 4883ec08 e85ffeff  ,,..SL).H...._..
 11a0 ff48c1fd 03741f31 db0f1f80 00000000  .H...t.1........
 11b0 4c89f24c 89ee4489 e741ff14 df4883c3  L..L..D..A...H..
 11c0 014839dd 75ea4883 c4085b5d 415c415d  .H9.u.H...[]A\A]
 11d0 415e415f c366662e 0f1f8400 00000000  A^A_.ff.........
 11e0 f30f1efa c3                          .....   
```

The ".data" section contains the initialized data:
```
ubuntu@shalaar3:~$ objdump -s -j .data hello

hello:     file format elf64-x86-64

Contents of section .data:
 4000 00000000 00000000 08400000 00000000  .........@......
```

For the ".bss" section, keep in mind that it typically doesn't store any data in the binary file itself, so using the -s flag won't provide any meaningful output. The ".bss" section is used for uninitialized global and static variables, and their memory is allocated at runtime. The size of the ".bss" section is determined by the linker, and it is not stored in the binary file. The linker will allocate the required memory for the ".bss" section at runtime, and the memory will be initialized to zero.


To disassemble the ".text" section, which contains the executable code of the binary, you can use objdump with the -d flag:


<details>
  <summary>Open long ass file</summary>

```
ubuntu@shalaar3:~$ objdump -d -j .text hello

hello:     file format elf64-x86-64


Disassembly of section .text:

0000000000001060 <_start>:
    1060:	f3 0f 1e fa          	endbr64 
    1064:	31 ed                	xor    %ebp,%ebp
    1066:	49 89 d1             	mov    %rdx,%r9
    1069:	5e                   	pop    %rsi
    106a:	48 89 e2             	mov    %rsp,%rdx
    106d:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    1071:	50                   	push   %rax
    1072:	54                   	push   %rsp
    1073:	4c 8d 05 66 01 00 00 	lea    0x166(%rip),%r8        # 11e0 <__libc_csu_fini>
    107a:	48 8d 0d ef 00 00 00 	lea    0xef(%rip),%rcx        # 1170 <__libc_csu_init>
    1081:	48 8d 3d c1 00 00 00 	lea    0xc1(%rip),%rdi        # 1149 <main>
    1088:	ff 15 52 2f 00 00    	callq  *0x2f52(%rip)        # 3fe0 <__libc_start_main@GLIBC_2.2.5>
    108e:	f4                   	hlt    
    108f:	90                   	nop

0000000000001090 <deregister_tm_clones>:
    1090:	48 8d 3d 79 2f 00 00 	lea    0x2f79(%rip),%rdi        # 4010 <__TMC_END__>
    1097:	48 8d 05 72 2f 00 00 	lea    0x2f72(%rip),%rax        # 4010 <__TMC_END__>
    109e:	48 39 f8             	cmp    %rdi,%rax
    10a1:	74 15                	je     10b8 <deregister_tm_clones+0x28>
    10a3:	48 8b 05 2e 2f 00 00 	mov    0x2f2e(%rip),%rax        # 3fd8 <_ITM_deregisterTMCloneTable>
    10aa:	48 85 c0             	test   %rax,%rax
    10ad:	74 09                	je     10b8 <deregister_tm_clones+0x28>
    10af:	ff e0                	jmpq   *%rax
    10b1:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    10b8:	c3                   	retq   
    10b9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000010c0 <register_tm_clones>:
    10c0:	48 8d 3d 49 2f 00 00 	lea    0x2f49(%rip),%rdi        # 4010 <__TMC_END__>
    10c7:	48 8d 35 42 2f 00 00 	lea    0x2f42(%rip),%rsi        # 4010 <__TMC_END__>
    10ce:	48 29 fe             	sub    %rdi,%rsi
    10d1:	48 89 f0             	mov    %rsi,%rax
    10d4:	48 c1 ee 3f          	shr    $0x3f,%rsi
    10d8:	48 c1 f8 03          	sar    $0x3,%rax
    10dc:	48 01 c6             	add    %rax,%rsi
    10df:	48 d1 fe             	sar    %rsi
    10e2:	74 14                	je     10f8 <register_tm_clones+0x38>
    10e4:	48 8b 05 05 2f 00 00 	mov    0x2f05(%rip),%rax        # 3ff0 <_ITM_registerTMCloneTable>
    10eb:	48 85 c0             	test   %rax,%rax
    10ee:	74 08                	je     10f8 <register_tm_clones+0x38>
    10f0:	ff e0                	jmpq   *%rax
    10f2:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    10f8:	c3                   	retq   
    10f9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001100 <__do_global_dtors_aux>:
    1100:	f3 0f 1e fa          	endbr64 
    1104:	80 3d 05 2f 00 00 00 	cmpb   $0x0,0x2f05(%rip)        # 4010 <__TMC_END__>
    110b:	75 2b                	jne    1138 <__do_global_dtors_aux+0x38>
    110d:	55                   	push   %rbp
    110e:	48 83 3d e2 2e 00 00 	cmpq   $0x0,0x2ee2(%rip)        # 3ff8 <__cxa_finalize@GLIBC_2.2.5>
    1115:	00 
    1116:	48 89 e5             	mov    %rsp,%rbp
    1119:	74 0c                	je     1127 <__do_global_dtors_aux+0x27>
    111b:	48 8b 3d e6 2e 00 00 	mov    0x2ee6(%rip),%rdi        # 4008 <__dso_handle>
    1122:	e8 19 ff ff ff       	callq  1040 <__cxa_finalize@plt>
    1127:	e8 64 ff ff ff       	callq  1090 <deregister_tm_clones>
    112c:	c6 05 dd 2e 00 00 01 	movb   $0x1,0x2edd(%rip)        # 4010 <__TMC_END__>
    1133:	5d                   	pop    %rbp
    1134:	c3                   	retq   
    1135:	0f 1f 00             	nopl   (%rax)
    1138:	c3                   	retq   
    1139:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001140 <frame_dummy>:
    1140:	f3 0f 1e fa          	endbr64 
    1144:	e9 77 ff ff ff       	jmpq   10c0 <register_tm_clones>

0000000000001149 <main>:
    1149:	f3 0f 1e fa          	endbr64 
    114d:	55                   	push   %rbp
    114e:	48 89 e5             	mov    %rsp,%rbp
    1151:	48 8d 3d ac 0e 00 00 	lea    0xeac(%rip),%rdi        # 2004 <_IO_stdin_used+0x4>
    1158:	e8 f3 fe ff ff       	callq  1050 <puts@plt>
    115d:	b8 00 00 00 00       	mov    $0x0,%eax
    1162:	5d                   	pop    %rbp
    1163:	c3                   	retq   
    1164:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
    116b:	00 00 00 
    116e:	66 90                	xchg   %ax,%ax

0000000000001170 <__libc_csu_init>:
    1170:	f3 0f 1e fa          	endbr64 
    1174:	41 57                	push   %r15
    1176:	4c 8d 3d 3b 2c 00 00 	lea    0x2c3b(%rip),%r15        # 3db8 <__frame_dummy_init_array_entry>
    117d:	41 56                	push   %r14
    117f:	49 89 d6             	mov    %rdx,%r14
    1182:	41 55                	push   %r13
    1184:	49 89 f5             	mov    %rsi,%r13
    1187:	41 54                	push   %r12
    1189:	41 89 fc             	mov    %edi,%r12d
    118c:	55                   	push   %rbp
    118d:	48 8d 2d 2c 2c 00 00 	lea    0x2c2c(%rip),%rbp        # 3dc0 <__do_global_dtors_aux_fini_array_entry>
    1194:	53                   	push   %rbx
    1195:	4c 29 fd             	sub    %r15,%rbp
    1198:	48 83 ec 08          	sub    $0x8,%rsp
    119c:	e8 5f fe ff ff       	callq  1000 <_init>
    11a1:	48 c1 fd 03          	sar    $0x3,%rbp
    11a5:	74 1f                	je     11c6 <__libc_csu_init+0x56>
    11a7:	31 db                	xor    %ebx,%ebx
    11a9:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    11b0:	4c 89 f2             	mov    %r14,%rdx
    11b3:	4c 89 ee             	mov    %r13,%rsi
    11b6:	44 89 e7             	mov    %r12d,%edi
    11b9:	41 ff 14 df          	callq  *(%r15,%rbx,8)
    11bd:	48 83 c3 01          	add    $0x1,%rbx
    11c1:	48 39 dd             	cmp    %rbx,%rbp
    11c4:	75 ea                	jne    11b0 <__libc_csu_init+0x40>
    11c6:	48 83 c4 08          	add    $0x8,%rsp
    11ca:	5b                   	pop    %rbx
    11cb:	5d                   	pop    %rbp
    11cc:	41 5c                	pop    %r12
    11ce:	41 5d                	pop    %r13
    11d0:	41 5e                	pop    %r14
    11d2:	41 5f                	pop    %r15
    11d4:	c3                   	retq   
    11d5:	66 66 2e 0f 1f 84 00 	data16 nopw %cs:0x0(%rax,%rax,1)
    11dc:	00 00 00 00 

00000000000011e0 <__libc_csu_fini>:
    11e0:	f3 0f 1e fa          	endbr64 
    11e4:	c3                   	retq   
```

</details>

<br>
<br>

# Write a program that when running as a process, creates another process by “forking” (man fork) itself.

```C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("I'm the child process with PID %d, and my parent has PID %d\n", getpid(), getppid());
    } else {
        // Parent process
        printf("I'm the parent process with PID %d, and I created a child with PID %d\n", getpid(), pid);

        // Wait for the child process to finish
        wait(NULL);
    }

    return EXIT_SUCCESS;
}
```

The output will display the PIDs (process IDs) of both the parent and child processes. The parent process will wait for the child process to finish before terminating.

```
ubuntu@shalaar3:~$ touch fork.c
ubuntu@shalaar3:~$ nano fork.c 
# Past program in file
ubuntu@shalaar3:~$ gcc -o fork fork.c
ubuntu@shalaar3:~$ ./fork 
I'm the parent process with PID 38867, and I created a child with PID 38868
I'm the child process with PID 38868, and my parent has PID 38867
```

<br>
<br>
<br>
<br>
<br>

## Subtask 1.4 – Zombie and Subtask 1.5 – Zombie or no Zombie

# Develop a program that creates a “Zombie Process”. Technically, when a child process terminates,
A zombie process is a process that has terminated but hasn't been reaped by its parent. This occurs when the parent doesn't collect the child's exit status using wait() or waitpid(). Here's a simple C program that demonstrates how to create a zombie process:


```
ubuntu@shalaar3:~$ touch zombie_process.c
ubuntu@shalaar3:~$ nano zombie_process.c
ubuntu@shalaar3:~$ cat zombie_process.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("I'm the child process with PID %d, and my parent has PID %d\n", getpid(), getppid());
        printf("Child process is terminating...\n");
    } else {
        // Parent process
        printf("I'm the parent process with PID %d, and I created a child with PID %d\n", getpid(), pid);
        printf("Parent process is sleeping...\n");

        // Sleep for 60 seconds while the child process terminates and becomes a zombie
        sleep(60);

        printf("Parent process is waking up and terminating...\n");
    }

    return EXIT_SUCCESS;
}
```

While the program is running, you can check the process status using the ps command in another terminal:
    
```
# First terminal
ubuntu@shalaar3:~$ ./zombie_process
I'm the parent process with PID 39025, and I created a child with PID 39026
Parent process is sleeping...
I'm the child process with PID 39026, and my parent has PID 39025
Child process is terminating...
```
    
```
# Second terminal
ubuntu@shalaar3:~$ ps aux | grep zombie_process
ubuntu     39025  0.0  0.0   2488   516 pts/1    S+   10:00   0:00 ./zombie_process
ubuntu     39026  0.0  0.0      0     0 pts/1    Z+   10:00   0:00 [zombie_process] <defunct>
ubuntu     39028  0.0  0.0   8164   656 pts/2    S+   10:00   0:00 grep --color=auto zombie_process
```
You'll notice that the child process is marked as a "Z" (zombie) in the process status column. The parent process will sleep for 60 seconds, during which the child process becomes a zombie, and then the parent process will terminate.


# Task 2 – Multi-Threading

# Study the following code and explain what happens, step-by-step. How can you (developer) define what should be shared between parent and child?

```
#define STACK_SIZE (1024 * 1024) /* Stack size for cloned child */

// Some function that should be run by the child
static int childFunc(void *arg) {
    //do something
    return 0;
}

Int main(int argc, char *argv[]) {

    char *stack;
    char *stackTop;
    pid_t pid;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <child-hostname>\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    # Define a new virtual address space
    stack = mmap(NULL, STACK_SIZE, PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);

    stackTop = stack + STACK_SIZE;

    # Pass new virtual address space to clone function
    pid = clone(childFunc, stackTop, CLONE_NEWUTS | SIGCHLD, argv[1]);

    if (waitpid(pid, NULL, 0) == -1)
        exit();

    printf("child has terminated\n");
    exit(EXIT_SUCCESS);
}
```
This code demonstrates a simple example of using the clone() system call to create a new child process that runs the childFunc() function. The code creates a new process with a new UTS (Unix Time-sharing System) namespace, which allows the child process to have a different hostname than the parent process. Here's a step-by-step explanation of what happens in the code:

1. The #define STACK_SIZE (1024 * 1024) macro defines the stack size for the cloned child process.
2. The childFunc() function is a simple function that will be executed by the child process.
3. In the main() function, the code checks if the user has provided a command-line argument for the child's hostname. If not, it prints a usage message and exits.
4. The mmap() function is called to allocate a new virtual address space for the child process's stack. The size of the stack is defined by the STACK_SIZE macro, and the address space is marked as private, anonymous, and stack memory. The PROT_READ and PROT_WRITE flags indicate that the memory should be readable and writable.
5. The stackTop pointer is set to the top of the stack (end of the memory region).
6. The clone() function is called to create the new child process. The childFunc() function is passed as the entry point for the child process, and stackTop is passed as the child's stack. The CLONE_NEWUTS flag indicates that the child process should have a new UTS namespace, which allows it to have a different hostname than the parent process. The SIGCHLD flag is passed to indicate that the child should send a SIGCHLD signal to the parent when it terminates.
7. The waitpid() function is called to wait for the child process to terminate. If the call fails, the program exits.
8. After the child process terminates, the parent process prints a message indicating that the child has terminated, and then the program exits successfully.

To define what should be shared between the parent and child, you can use different flags in the clone() function. For example, to share the file descriptor table, you can pass the CLONE_FILES flag. To share the same virtual memory space, you can pass the CLONE_VM flag. Check the clone() man page (man 2 clone) for a full list of flags and their descriptions.


# Task 3 - Kernel Threads

* Which process has PID #2?

```
ubuntu@shalaar3:~$ top
PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                                                                                                                                                   
      1 root      20   0  102260  11776   8380 S   0.0   0.3   0:37.31 systemd                                                                                                                                                   
      2 root      20   0       0      0      0 S   0.0   0.0   0:00.04 kthreadd                                                                                                                                                  
      3 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 rcu_gp              
```

* Identify any Kernel Thread and find out on which CPU it is running.
To identify kernel threads and find out on which CPU they are running, you can use the ps command along with some additional options and grep. Kernel threads are usually shown with square brackets around their names in the output of the ps command.
The following command will display a list of all kernel threads along with their PID, CPU number (processor ID), and command name:

```
ubuntu@shalaar3:~$ ps -eLo pid,psr,comm | grep "\]"

```

To find out more details about a specific kernel thread, for example, the kthreadd kernel thread with PID 2, run the following command:
```
ubuntu@shalaar3:~$ ps -p 2 -o pid,psr,comm
    PID PSR COMMAND
      2   1 kthreadd
```
This command will display the PID, CPU number, and command name for the specified kernel thread. Note that the CPU number might change if the kernel thread is migrated to another CPU by the scheduler.

Remember that kernel threads can be migrated between CPUs by the Linux scheduler, so the CPU number may not be constant.

# Select any thread called “Kworker” and explain the state by querying it with the ps command.

"Kworker" threads are kernel worker threads that handle various tasks within the kernel. They are created by the kernel to perform work on behalf of the workqueue mechanism. Workqueues are a generic mechanism used to queue work to be processed by kernel worker threads, which handle various tasks such as handling I/O completions, deferred tasks, and other kernel-level functions. This command will display a list of all "kworker" threads along with their PID and command name. Pick one of the PIDs from the list for further analysis:

```
ubuntu@shalaar3:~$ ps -eLo pid,comm | grep "kworker"
      6 kworker/0:0H-kblockd
     20 kworker/1:0H-kblockd
    112 kworker/u5:0
    335 kworker/1:1H-kblockd
    346 kworker/0:1H-kblockd
  37804 kworker/0:0-events
  37912 kworker/0:2-events
  38176 kworker/u4:0-events_power_efficient
  38622 kworker/u4:1-events_unbound
  38623 kworker/1:2-events
  38882 kworker/1:0-events
```

Run the following command to display the state of the selected "kworker" thread (replace PID 6 with the actual PID of the "kworker" thread you selected):
```
ubuntu@shalaar3:~$ ps -p 6 -o pid,comm,state
    PID COMMAND         S
      6 kworker/0:0H-kb I
 ```

This command will display the PID, command name, and state of the specified "kworker" thread. The state field shows the current state of the process. The possible states are:

- R (running): The process is running or runnable (on the run queue).
- S (sleeping): The process is in an interruptible sleep state, waiting for an event to complete.
- D (disk sleep): The process is in an uninterruptible sleep state, usually waiting for disk I/O.
- T (stopped): The process has been stopped, typically by a job control signal.
- t (tracing stop): The process is being traced (debugged) and has been stopped by a debugger.
- X (dead): The process is dead (a "zombie" state).
- Z (zombie): The process is terminated but hasn't been reaped by its parent.
Based on the state returned by the ps command, you can determine the current state of the "kworker" thread you selected.