# csse332-sp2324-review-session1

## How to download and edit the files here:
First, create a new directory on your WSL. You can do this by running the following command:
``` 
mkdir <directory name>
```
Once you've done that, go ahead and cd into the directory. Then, you'll want to go ahead and run the following command:
```
git clone git@github.com:wynessgp/git@github.com:wynessgp/csse332-sp2324-review-session1.git
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
[Problem 3](#problem_three) <br>

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
- Using `fork()` to create & effectively use multiple processes
- The `exec(...)` family of functions
- Using `pipe(...)` to effectively communicate info between processes
- Using `signal()` to register signal handlers
- Using `wait()`, `waitpid()` to make sure child processes exit properly

Any of these are equally likely to appear on exams. However, many of these rely on utilizing `fork()` to actually have any useful behavior, so make sure you are especially comfortable with what `fork()` does. 

Now, for some more detail on each of those functions found above:

### On `fork()`:
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

### On the `exec(...)` family of functions
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

### On using `pipe()`
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






