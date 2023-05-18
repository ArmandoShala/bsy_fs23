## Task 1

### Subtask 1.1 – See unit status and grouping
* Use the command to see the status of all units in the system

```bash
```

* Why are units organized in slices?

```bash
```

* What do they represent?

```bash
```

* Compare the output of the previous command with the output of ‘pstree’. Can you find the “bash” process in both? What is the difference?

```bash
```

### Subtask 1.2 – Targets

* Use the command to list all available target units

```bash
```

* Find out which command to use to find the default target for the local operating system

```bash
```

* What is the default target in the VM?

```
```

* Which command can you use to see the unit file of the default target and its location?

```bash
```

* What service unit should be started with that target?

```bash
```

* Is it required?

```bash
```

* What’s the difference between ‘requires’ and ‘wants’?

```bash
```

* There is a command that lets you see the “dependencies” of each unit.

```bash
```
> why is multi-user.target not dependent on basic.target? Or how can you read the graph?

```bash
```

<br>

* What is the command to list the dependencies of the default target?

```bash
```

* What is the command to see the dependencies of the ‘sysinit.target’?

```bash
```

* What do the listed dependencies mean?

```bash
```

* Use the man command to see which systemctl command allows you to see which units depend on a specific unit.

```bash
```

* Which target(s) depends on the ssh.service ?

```bash
```

## Task 2 - Services

### Subtask 2.1 – Inspect a service

* Can you tell from the status command the PID of the ssh process?

```bash
```

* Can you tell on which port it is running from the logs?

```bash
```

* In order to see the full logs of the service we can use a specific command. How do you see the logs of the ssh.service unit?

```bash
```

* What command can you use to see the unit-file of the ssh.service? Can you also see its location on the file system?

```bash
```

### Subtask 2.2 – Killing a service: Restart

* Use the “kill -SIGKILL <PID>“ command (e.g., “sudo kill -9 676”) to kill the “cron.service”. If you check the status of the cron service before and after killing the cron process, what do you see?

```bash
```

```bash
```

* Let’s now try to use a different signal (TERM) to kill cron (without ‘-9’): sudo kill <PID> What happens in this case?

```bash
```

```bash
```

* Look at the cron.service unit file with the systemctl cat command. What are the restarting conditions?

```bash
```

### Subtask 2.3 – Making the service restart always

* Let’s make a copy of the original cron.service file in /etc/systemd/system (configuration in /etc overrides the one in /lib) Use a text editor to change the “Restart” condition to “always” Force systemd to reload the units with the daemon-reload subcommand Verify that also when using the TERM signal to kill the cron process.

```bash
```

```bash
```

### Subtask 2.4 – KillMode

* What would happen if you were to stop the ssh.service with systemctl stop? Would your ssh session (and bash terminal) be killed?

```bash
```

## Task 3 - Create a Service Unit

### Subtask 3.1 – Unit File

* Create a service that writes the file /home/ubuntu/service_started each time it gets started

> 1. methood

```bash
```

```bash
```

```bash
```

```bash
```

```bash
```

```bash
```

<br>

> 2. method

```bash
```

### Subtask 3.2 – Set dependencies with Install section

* How would you extend your service unit file to make it automatically start with the multi-user.target?

```bash
```

* In order to make your service autostart you will also need to enable it with the appropriate command.

```bash
```

* Does this start the service? What command enables and immediately starts the service?

```bash
```

## Task 4 - Systemd User

### Subtask 4.1 – Unit File Installation

```bash
```

### Subtask 4.2 – Follow up service

```bash
```

```bash
```

```bash
```


### Subtask 4.3 – Start Without User Login

```bash
```

