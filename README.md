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

Note that both parts contribute to your overall Exam 1 grade, so make sure you are comfortable with all of the potential topics that can appear. 

An additional thing to note - you'll be connecting to a remote server for this exam. Namely, you'll be using `ssh` to connect to a machine other than your own. 

This means no local git repo of your work, unless if your instructor allows you to bring it over. The only reference material you get, as far as I'm aware, is a 1-sided 8.5" x 11" piece of paper of hand-written notes. Do with that what you will.

Also, you get access to Linux man pages. They do tell you helpful information!

<a id="content_notes"></a>

## *Content* Notes
The topics you are expected to know for this exam are roughly as follows:
- Using `fork()` to create & effectively use multiple processes
- The `exec(...)` family of functions
- Using `pipe(...)` to effectively communicate info between processes
- Using `signal()` to register signal handlers
- Using `wait()`, `waitpid()` to make sure child processes exit properly

Any of these are equally likely to appear on exams. However, many of these rely on utilizing `fork()` to actually have any useful behavior, so make sure you are especially comfortable with what `fork()` does. 

Now, for some more detail on each of those functions found above:



