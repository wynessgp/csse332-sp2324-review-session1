# csse332-sp2324-review-session1

## How to download and edit the files here:
First, create a new directory on your WSL. You can do this by running the following command:
``` 
mkdir <directory name>
```
Once you've done that, go ahead and cd into the directory. Then, you'll want to go ahead and run the following command:
```
git clone git@github.com:wynessgp/csse332-sp2324-review-session1.git
```
And that should go ahead and move all of the files over to your WSL. My suggestion is you keep all the review sessions material in this directory, as they'll be nicely organized. Note that you could also just directly clone this repo from your home directory, and the file that comes out of that will just be the repo's name. 

If you are having errors with GitHub saying it cannot authenticate you due to a publickey issue, you'll need to create a SSH key. You can either follow the instructions on [GitHub's website](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/generating-a-new-ssh-key-and-adding-it-to-the-ssh-agent) to generate one, or you can follow Comp Arch 1's tutorial [here](comp-arch-ssh-tutorial.md). Note that the Comp Arch 1 tutorial talks about using `Git Bash` -- you'll need to do all of those steps in WSL instead, so do it on your Ubuntu machine! 

If that is not the error, I'd suggest following whatever the console spits out - those hints usually tell you everything you need.

I'd recommend leaving this README page up on [GitHub](https://github.com/wynessgp/csse332-sp2324-review-session1) and tabbing back and forth for instructions. If you are viewing this in VSCode, note that to render markdowns, you can do `Ctrl + k, v` (in that order), although you shouldn't ever open VSCode for this class (you certainly won't be allowed to on the Exams). I have tried to leave you some nice links that you can click on for some navigability. 

## A quick request
If you are going to ask me questions related to this practice exam after the review session, please see me for my regularly scheduled hours within the next 2 weeks:
- (Percopo 2 Study Room) Thursday night, 3/21, from 7-10pm.
- (Percopo 0 Classroom) Monday night, 3/25, from 7-10pm.
- (Percopo 0 Classroom) Wednesday night, 3/27, from 7-10pm.
- (Percopo 2 Study Room) Thursday night, 3/28, from 7-10pm. 

I am not too keen on hopping on Teams calls or responding to messages outside of my regularly scheduled hours, as I too have assignments that I need to do. Study room hours and classroom hours are specific times the SRTs set aside for you to come and ask us questions or get help!

<a id="toc"></a>

## Table of Contents
Reminder that these links will only work if you're viewing this in a markdown renderer, or if you're on GitHub. I'd highly suggest using one of those.

[Administrative Notes](#admin_notes) <br>
[Content Notes](#content_notes) <br>
[Problem 1](#problem_one) <br>
[Problem 2](#problem_two) <br>

<a id="admin_notes"></a>

## *Administrative* Notes
This GitHub repository will only contain the **questions** for a practice exam. I will **NOT** be posting solutions here, as that would make my solutions public. You may ask me for hints on how to implement things.

Please note that these questions are typically going to be harder than what you'll see on the actual exams. 

I do this on purpose, thought process being that if you can solve these, you should be able to solve 99% of the questions they'll ask on the exams.

That being said, let's talk about your exam structure. Exam 1 is split as follows:
- Part 1 will be on Friday, 3/22, during your normally scheduled class time.
- Part 2 will be on Friday, 3/29, during your normally scheduled class time.

This means you have 50 minutes (if you do not have accomodations) on both parts of the exam. Be careful studying for this exam, as any of the sample exams posted as part of the `CSSE332` repo that are older than this year ('23-'24) used to be night exams that were 3 hours long. 

In general, for the two parts you'll experience, you should anticipate getting one "overall" question on both days, split into two parts, as follows:
- Part 1: Basics of the concepts. Enough to earn you a C if you get this correct.
- Part 2: A little more advanced. You'll need to get this correct to earn an A.
- Part 3: This only sometimes appears, but it will be for extra credit if it does.

Note that both parts contribute to your overall Exam 1 grade, so make sure you are comfortable with all of the potential topics that can appear. If you get an A on one day of the exam, but completely fail the other part, the most you would be elgible for is a 100/200. Do your best!

An additional thing to note - you'll be connecting to a remote server for this exam. Namely, you'll be using `ssh` to connect to a machine other than your own. 

This means no local git repo of your work, unless if your instructor allows you to bring it over. The only reference material you get, as far as I'm aware, is a 1-sided 8.5" x 11" piece of paper of hand-written notes. Do with that what you will.

Also, you get access to Linux man pages. They do tell you helpful information!

<a id="content_notes"></a>

## *Content* Notes
This is the section where I yap on and on about certain function calls you've seen. If you don't feel like seeing what I have to yap about, please skip ahead to the practice problems. 

If you do feel like looking at my notes on these things, maybe you'll learn something new. 

The topics you are expected to know for this exam are roughly as follows:
- [Using `fork()` to create & effectively use multiple processes](#fork_notes)
- [The `exec(...)` family of functions](#exec_notes)
- [Using `pipe(...)` to effectively communicate info between processes](#pipe_notes)
- [Using `signal()` to register signal handlers](#signal_notes)
- [Using `wait()`, `waitpid()`, `exit()` to make sure child processes exit properly](#wait_notes)

Any of these are equally likely to appear on exams. However, many of these rely on utilizing `fork()` to actually have any useful behavior, so make sure you are especially comfortable with what `fork()` does. 

Now, for some more detail on each of those functions found above:

<a id="fork_notes"></a>

## On `fork()`:
Remember that the `fork()` function creates an entirely new process, but with a context **identical** to the current one, with the exception of whatever PID variable you're using. 

This new child process it spawns will be **ISOLATED** from the current process at its creation, unless you've used `pipe()` just beforehand. 

The child process will then begin running the same program as the parent from the exact line you called fork on; so `fork()` essentially returns twice.

Note that in Linux, it just so happens that the child process will always have `fork()` return `0`. This is how we can actually tell the parent and child processes apart; that's what we're checking for whenever we do the `if (fork() == 0)` (or some equivalent statement) line in code.

As you might've noticed, this tends to lead to a distinct `if () {...} else if () {...}` pattern when we write code around `fork()`. One important thing I'd like to point out regarding this pattern - most times when you see it in class, we include something like this:
```
int pid = fork();
if (pid < 0) {
    perror("fork error");
    exit(1);
}
```
But what does this really even mean? Shouldn't `fork()` always return 0 or a positive number? The answer is 99% of the time, it will. But if `fork()` causes an error, I think you'd like to know sooner than later. `fork()` will return a negative value if an error occurs, and you should exit if that is the case, otherwise you may end up with some very bad process behavior. 

Continuing on that example, you'll want to make sure that the child process exits:
```
} else if (pid == 0) {
    // do something...
    exit(<some exit code>);
} else {
    // parent code
}
// also parent code, if child exits.
```
If you don't ensure the child process exits, it may end up running whatever code is located after your `if () {...} else if () {...}` block, which is not good. That's why we always suggest the parent calls `wait()`, because it'll be more obvious if the child process doesn't exit properly. (It also helps ensure you don't end up with zombies!)

[Link back to TOC](#toc)

<a id="exec_notes"></a>

## On the `exec(...)` family of functions:
It is **VERY** important to note that exec will replace the **CURRENT** process with whatever else you are attempting to `exec`. This is why you usually see any `exec()` calls paired with a `fork()` call just before it - otherwise we just throw out the code we're attempting to run, which defeats the point. That's not to say that couldn't be the point of a program, but we typically don't have you throw away the code you're writing in this class. 

Much like with `fork()`, we suggest you error-check any `exec()` calls you make by simply throwing a `perror("<msg>")` and `exit(<some exit code>)` call **AFTER** the `exec()` call - something like this:
```
// some code here...
exec(...);
perror("exec failed, something bad is happening!");
exit(EXIT_FAILURE);
// ...
```
Since `exec` generally relies on the other process exiting normally, if you manage to reach the `perror` afterwards, you know something went wrong, and can make that process exit on your accord instead of creating a zombie process. 

Also, let's take a brief look at the function signatures specified in the Linux man page:
```
int execl(const char *pathname, const char *arg, ..., (char *) NULL);
int execlp(const char *file, const char *arg, ..., (char *) NULL);
int execv(const char *pathname, char *const argv[]);
int execvp(const char *file, char *const argv[]);
```
Note that `execl` and `execlp` have this weird syntax that says `const char *arg, ...,`, that just means you can have 1 or more args. You also have the NULL padding on the end; note that `execv` and `execvp` also expect that NULL, it just has to be the last thing in the array.

It is VERY important that you cast all of your values to `char*`'s before you call `exec` in any form; as it tries to execute the commands just like you do on the command line, and most programs treat those as strings. If you're unsure on how to cast anything to a char*, you can usually do the following:
```
char mybuf[128];
sprintf(mybuf, "my number: %d", 12);
```
`sprintf` will copy the formatted string provided (in my case, `"my number: %d"`), fill it in using the standard C string formatting rules (so the thing becomes `"my number: 12"`) and then puts it into the char buffer provided as the first argument. So if I were to print out what's in the buffer later:
```
printf("%s\n", mybuf)
my number: 12
```
I'd just get whatever I put in the buffer. Make sure you're using the appropriate string formatting tools to put your data types in, though. 

Some constraints: make sure your buffer is actually long enough to hold onto the message you're trying to put in there. Things will probably break otherwise. 

[Link back to TOC](#toc)

<a id="pipe_notes"></a>

## On using `pipe()`:
Pipes are meant to be the primary means through which processes communicate with each other. Think about it - with completely isolated processes after calling `fork()`, how are you actually meant to get a message from one process to another? The only feasible way is through a shared file; and that's precisely what pipes are. 

Remember that a `pipe` is a **unidirectional** channel of communication between two or more processes that share a common ancestor; that being the process who set up the pipe. So one end is strictly the **read** end (index 0) and one end is strictly the **write** end (index 1). 

To preserve the **unidirectional** nature of pipes, you should always close the end you are NOT going to use at the start of a particular process's code. If two processes are to communicate back and forth, you should utilize more than one pipe. In this class, we encourage you to explicitly close both ends in both the child and parent process. Ex:
```
if (pid == 0) {
    // child
    close(fd[0]);
    ...
    close(fd[1]);
} else {
    // parent
    close(fd[1]);
    ...
    close(fd[0]);
}
```
Additionally, it is vital that you call `pipe(...)` before you call `fork()`, otherwise the pipes will not get initialized correctly. 

Something else to remember - when you are using `read` and `write` to interact with pipes, you have to remember some of the edge cases that come with using those functions.

For `read`, remember that this is a blocking call - `read` will only return once either of the below things have happened:
- Read has successfully gotten at least 1 byte of data out of the pipe 
- All of the other writing ends of the pipe have been closed 
    - If no data was in the pipe, read will not put anything in the buffer specified in the call.

The second reason is why it is especially important to close your pipes! You don't want a `read` call to pause execution of everything else in your code.

For `write`, there's really only one case in which it blocks:
- The pipe is full

Additionally, note that you need to be careful about how many bytes you write/read at any given time. These move the respective read and write pointers along the file, so if your read pointer is WAY ahead of your write pointer, you'll never get the chance to see that data, and will likely have your program stall.

This is why we usually recommend reading and writing the same amount of bytes in your calls. 

[Link back to TOC](#toc)

<a id="signal_notes"></a>

## On using `signal()`:
Signal does not have as many complexities to it as some of the other functions that you'll use here. Remember that in order to properly use it, you'll need to provide it with:
```
signal(<signal type>, signal_handler);
```
Where `signal_handler` is some void function you define earlier in the file. 

When you are using `signal`, make sure you are 100% aware of WHEN Linux generates the signal that you choose to put in the function call. To briefly go back to the process lab for an example, we had you look at the man page for `alarm(...)`. Alarm would take in an integer argument, and after that many seconds, it would deliver a `SIGALRM` signal. You would need to use signal to appropriately catch that, and allow for test cases to effectively timeout.

You might also know about the `SIGSEGV` signal, which is a signal that is generated when a segmentation violation (more commonly, a segfault) occurs. Note that a segfault occurs when you try to access an invalid memory location; so it isn't technically 100% sufficient for handling crashes. A crash occurs whenever a program fails to exit altogether - this means things like memory leaks, stack smashing, etc. 

[Link back to TOC](#toc)

<a id="wait_notes"></a>

## On using `wait()`, `waitpid()`, `exit()`:
Remember that a good parent process should **ALWAYS** make sure that its child process exited. This is how you prevent zombie processes from going around and wreaking havoc. This is where the `wait()` family of functions come in, as they do exactly what their name entails.

Here's something to consider on when exactly you should use `wait()` vs. `waitpid()`:
- Is parallelism a big thing with this program you are going to be writing?
    - If so, you'll want to consider using `waitpid()`.
        - `waitpid()` allows you to wait on a process without being a direct parent of it; so you can go through, generate a whole bunch of processes, then not have to worry about which process generated another at what point. Just save the PIDs!
    - If not, you'll want to consider using `wait()`.
        - `wait()` only really works well if you are directly related to the process you just created via `fork()`, otherwise it may grab the wrong process to wait on. Note that this is equivalent to calling `waitpid(-1, &status, 0);` so it will work, but it doesn't allow you to target specific processes. 

In either case, the parent process will stop execution of the program **UNTIL** the child process calls `exit()`, or runs out of lines to run in a function (if it doesn't return to somewhere else). 

This is also why it is important to make sure your child process always exits. If it doesn't the parent process may get locked out of running its code for a while, not to mention the fact that you'll have a process running rogue through your code. 

Also, remember your macros to get the exit status from a process - things like `WIFEXITED(status)`, or `WEXITSTATUS(status)`. These may come in handy on the exam!

[Link back to TOC](#toc)

### Problems
Ok, enough rambling. Let's get to the actual content you're likely here for.

<a id="problem_one"></a>

## Problem 1: [Scouting Parties](scout.c)
Length: Medium <br>
Objective: Use `fork()` in conjunction with `exec(...)`, and exit codes. <br>
Files to modify: `scout.c` <br>  

### Description:
Suppose that you are the manager of a Medieval era war camp. Your country is currently fighting a brutal campaign against your enemy and you need all of the information you can get on them. For whatever reason, you find yourself in your tent late at night, and an idea strikes you - why not send out some scouting parties and have them report back to you?

"What a great idea!" you think to yourself. But who do you pick to send out on this scouting party? You look over the list of soldiers you have in your camp. You decide on sending out every 7th soldier you have on your list, because that should bring your scouts good luck out in the field. You go to bed with a smile on your face, and mentally prepare yourself to start sending them out tomorrow.

That's enough storytelling for now. Let's return to the land of ~~pain~~ C coding and attempt to model this problem. 

### Implementation Details:
There are two files that go with this problem: `scout.c` and `report.c`. You will not need to modify `report.c` at all, but you will want to take a look at what it is doing to figure out the various exit codes it gives out. 

Your code for `scout.c` is to try and generate a lucky scout N times (where N is the input to the program) to send out on a scouting mission. A lucky scout will be any child process you generate that has a pid divisible by `7`. 

This lucky scout is then to make a report that it will **HOPEFULLY** bring back to you at some point in the future. This means that the lucky scout is to execute `./report.bin <scout's pid>`, and you are to eventually determine what that report (exit code) means for you. (Look at the comments in `report.c`, those are what you will want to print). You should be able to do this without creating **ANY** zombie processes.

Additionally, all of your lucky scouts should be able to go out on missions at the same time (needs to be parallelized). Once one of them exits (or crashes!), your parent process should reveal what the associated report information was. 

In order to get the scout's PID, you'll likely need to use `getpid()`.

Note that in order to appropriately call `./report.bin <pid>` from the lucky scout's process, you'll need to convert the pid into a string - you can do so with `sprintf`:
```
char scout_pid[32];
sprintf(scout_pid, "%d", <pid>);
```
And this will store their PID in `scout_pid`. You'll want to use that as an argument to `exec`. 

Additionally, the correct way to execute `scout.bin` is:
```
$ ./scout.bin N
```
Where N is some integer of your choosing - try to make it somewhat high, but no more than 300 reasonably speaking. 

Also, it is OK to hold onto all of the pids you generate - just make sure that if the process is not a lucky one, that you make it `exit()` with a code that doesn't overlap with what `report.c` has.

You can generate both `./report.bin` and `./scout.bin` by typing `make` in your practice exam's directory. If you would like to try to match my output, here's an example of running the program:
```
$ ./scout.bin 77
Scout 2282 is leaving the camp!
Scout 2289 is leaving the camp!
Scout 2296 is leaving the camp!
Scout 2303 is leaving the camp!
Scout 2310 is leaving the camp!
Scout 2317 is leaving the camp!
Scout 2324 is leaving the camp!
Scout 2331 is leaving the camp!
Scout 2338 is leaving the camp!
Scout 2345 is leaving the camp!
Scout 2352 is leaving the camp!
Ambush! Someone followed the scout!
Ambush! Someone followed the scout!
We're rich! The scout found treasure!
Oh tragic day! The scout never returned!
Ambush! Someone followed the scout!
Useless! The scout came back empty handed...
Ambush! Someone followed the scout!
Ambush! Someone followed the scout!
Oh tragic day! The scout never returned!
Useless! The scout came back empty handed...
We're rich! The scout found treasure!
```
Note that the line with `$ ./scout.bin 77` is me entering the command to start the program.

<a id="problem_two"></a>

## Problem Two: [Chaos in the Armory](armory.c)
Length: Medium <br>
Objective: Use `fork()` in conjunction with `pipe()` to communicate with *multiple* child processes at once. <br>
Files to modify: `armory.c` <br>

## Description:
Everything was going fine one day in your camp until the armory suddenly caught on fire. You hear people outside your tent yelling:

"Fire! Fire! Save the armory!" 

If you lose those weapons, you're going to be in a lot of trouble. Without much of a thought, you rush into the burning building, past the crowd of soldiers gathering around it. 

Luckily for you, the section of the armory you're in isn't burning yet, though you guess that you probably don't have much time. You turn around and see some of your personal guards have followed you in. 

"Okay, here's the plan. You lot are to split into groups of 4 and save some of the weapons in this section of the armory." You say, and they all nod. "I want you, you, and you to be the ones grabbing weapons out of the piles, and the rest of you are to drag them away after the leader of each group hands you one." 

They all nod in agreement and split up to go to the various corners of the room, working diligently to save what they can, under your diligent oversight.

## Implementation:
This one will be a bit trickier to model. For simplicity's sake, imagine that you are the process that calls `./armory.bin`, AKA the **MAIN** process. The leader of each small group will be another process; and the people working to transport the weapons out of the armory are yet another process. To give you a rough idea of what I'm aiming for here, let me give you a little diagram:
```
                                            Main Process
                                    /            |          \
                                /                |                \
                            Leader 1          Leader 2          Leader 3
                           /    |    \       /   |    \        /   |    \
                          /     |     \     /    |     \      /    |     \
                         S1    S2     S3   S1    S2    S3    S1    S2    S3
```
I intend for you to read this diagram from the top down. The main process has 3 child processes:
- Leader 1
- Leader 2
- Leader 3

Each Leader process, subsequently, has child processes:
- S1
- S2
- S3

The leader must be able to communicate, via pipe, with all three (per example) of its child processes.

Additionally, the main process should wait for each Leader to finish; printing out when they do. 

Here are some `#define` statements I've thrown at the top of the file that you'll need to use to determine how long each process must stay alive for:
```
#define NUM_LEADERS 3
#define NUM_SOLDIERS 3
#define NUM_WEAPONS_PER_SOLIDER 2
...
```
(Note that by the hierarchy above, Leaders stay in their respective place; Soldiers will be the S~ layer you see below them). 

Each Leader must direct their respective soliders to pick up `NUM_WEAPONS_PER_SOLIDER` weapons; by putting the respective weapon's number in the pipe. (Think about how many times they must do this). 

So if I was a leader telling a soldier to pick up the first weapon, I'd just write the number `1` into the pipe. 

In order to represent writing a message into the pipe, you should print out:
```
Leader <leader PID> says to retrieve weapon <weapon number>!
```
Note that it doesn't matter which solider gets to retrieve the weapon first (namely, who reads first), it just matters that some soldier gets it. Once a soldier retrieves the weapon, they should print out:
```
Soldier <soldier PID> retrieved weapon <weapon number>!
```
And then they should sleep for `2` seconds to model them taking it out of the army. 

Once any soldier retrieves `NUM_WEAPONS_PER_SOLIDER`, they should print out:
```
Soldier <soldier PID> has retrieved the alotted amount of weapons!
```
And then prompty exit.

Once a leader has supervised handed out all of their orders on weapons to retrieve, they should promptly exit, printing the message:
```
Leader <leader PID>'s job is done here!
```
Just before they exit.

Finally, come back up to our main process, once we've confirmed that a Leader has left, we should print out:
```
Main Process <main process PID> has confirmed that Leader <leader PID> left the armory!
```
While there are a couple of different ways to achieve these print outs, I am going to strictly enforce this hierarchy for the sake of this problem. None of your processes should exit before they finish their job, and you should have **NO** zombies after the program is done running. 

Like the other problems, you can use `make` to generate `./armory.bin`, which is what you'll need to use in order to run the program. Here's some sample output from me running it:
```
$ ./armory.bin

```



