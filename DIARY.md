# Dev Diary :D  
## Introduction
Here, I'll narrate every single problem/curious thing that happened during the development of this project, just so I can read it and laugh at myself in the future (I hope near future D:).  

## 1.0.0 realease  
I actually never really worked with all these new tools before (Inno setup, C itself, cmake, etc...) but i really enjoyed the experience, it was very challenging to learn a new coding language (And specially if it is C) with a project instead of a class but it was rewarding. One of the biggest challenges I had during the development of this project (specially cxt) was learning about pointers and strings with c, it might be one of the hardest things to dominate out there, if it wasn't because of google this project might be dead, I can't imagine how people used to code without the beauty of learning through a search engine.  

## 1.1.0 realease
Hello there! it's the first time I write it from the beginning of the period of time I'm supposed to be doing it, so, let's start with the first few things I would like to present you the only thing I wanna add in this realease.  
- **Build Assistant**: I know its hard to do but I would like to code an automatic cmake file generator to just code and code without worrying for the cmake :D. I guess I'll just have a basic template for its first version and then add a bunch more of them. I'm thinking of some commands like:  
```bash
    # This one would make the cbaFile.cl so the user can just do build or cl -ba build to update
    [buildSystem] -[assembler] # This would go in cba.c
    cl -ba cmake -ninja # This one would use CL PATH command as a short cut
    # ↑ uses cmake and ninja as examples

    build # On cba.c would update the CMake files and  build the .exe
    reset # Deletes all cbaFiles.cl so you can change configurations
    config # configuration menu
```
Anyways, I'll put them in the documentation once I finish it. For the moment, those are the only ones I have planned so far.  

---
### 1.0.1 update :D
For this update (which I have about half an hour to code) I'll try to set the base for this new tool in the stack, wish me luck!

For the first files I made, I must say, I really should work on ui.c, it reapeats in every new project that needs it, I know it's hard to make an universal one. Was thinking about C#'s override feature but discarded it after noticing it'd be the same, I'd override it literally ALL the times I wanna make a personalized UI so I'll keep doing it the way I'm doing so until I come up with a better plan.

As I kept working I found out the past bash commands were not good enough, they were pretty repetitive and complicated for things I could automate and make easier for the user so this is the idea now:  
```bash
    build # Will look for cba.build, with all the info it needs to run
    prepare # If it doesn't find said file, you should run this one
    config # Pretty much self-explanatory
```
If build is run without a cba.build file it'll ask the user for permission to make another one, assuming its the root directory of the project and writing with the options saved in cba directory in C:/InCGames/CL/configs

---

Another minor patch for the installer. For now, it's just a minor adjustment on what files and where does it make it. Before, the config files weren't generated at all (wasn't necessary), now they're located at "C:\InCGames\cl\configs" on the user's pc. 

Also, I found out I left cba.c incomplete last time I touched it, started to work in that

I honestly thought it'd be harder, ofc it's way simpler than i want it to be and i haven't tested a thing but i'm pretty sure it'll work just fine, for now, CBA is half way to it's first usable release (which will be 1.1.0 of the main program). For now, when you first run the build command, it starts doing magic, looking for a cba.build file (if it doesn't, it'll look for cba.config in the same folder as the last time i said it). then, it'll write this code to the main CMakelists.txt

```cmake
    cmake_minimum_required(VERSION %s) // %s is the variable that
    project(%s VERSION %s)
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
    set(CMAKE_MAKE_PROGRAM ninja)
    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.c")
    file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "*.h")
    add_executable(%s ${SOURCES} ${HEADERS})
    set_target_libraries(%s PRIVATE common)
```

then, it'll look for subdirectories, making a basic CMakelists.txt for each one, being:
```cmake
    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.c")
    file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.h")
    target_sources(%s PRIVATE ${SOURCES} ${HEADERS})
    set_target_libraries(%s PRIVATE common)
```

if the subdirectory name is:
- ".cbaignore"
- "tests"
- "docs"
- "configs"
- ".idea"
- ".github"
- ".vscode"
- ".git"
- "build"

it'll automatically ignore it  
if the directory name is "common", then cba will make this CMakelists.txt:
```cmake
    file(GLOB COMMON_SOURCES "common/*.c")
    add_library(common STATIC ${COMMON_SOURCES})
    target_include_directories(common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
    set_target_properties(common PROPERTIES C_STANDARD 11)
```

And that's it, now the user should be able to run either "ninja", "cmake .." or "cba build" (prefirably cba build because it rechecks everything) to get the .exe's

For now and due to my lack of experience with cmake, it'll be based completely on my files so it won't have that much of compatibility but it'll improve with time. This was an easy tool to develop tbh, I was hoping to find problems.

## 1.2.0
(yeah, i forgot last realease was 1.1 and put a 1.2 the whole time)  
For this version i want to:
- **Refactor CBA** due to some issues i saw during the weekend on folder checking and adding it's documentation and changelog
- Finally work with **CL and do a major overhaul** of it's functionalities
- Take **CBA out of beta** and add it to the hub so it has an easier access
- Finally use **.config files** added in last update.

Also, i'm gonna change the format of this markdown file, now it'll have different sections for the different plans for the minor realease and other sections for patches or updates.  
Last format was way too chaotic.  
**(After afinating)**
I came to this new versioning protocol. I upload a daily patch and a weekly drop of a new tool (this one being cba) so the new versioning will be:  
major.weeklyDrop.dailyPatch (so don't be surprised if we're in 1.39.4 in a near future)

Another anouncement, i'm trying to add a new tool/minor update each week so stay tuned!

### CBA refactorization  //Postponed to 1.3
I'm tired today so let's work with this, it's way simpler and easier so i hope i finish quick. After a quick check on the code, i noticed i could let the user build their own structure and have some defaults instead of directly doing it all by myself.  

For now, I've been working more on the interpreter than actual refactoring the code, all it's flaws are perfectly corregible by just doing a good work with the interpreter and cl. For now, im pretty sure it's gonna be easy.  

I've been learning a lot these few weeks i've had this project, fr i think c is the greatest language to ever exist, i can do whatever i want however i want and the computer will do exactly that, almost no rules, almost nothing to do but code and learn a lot, specially when it comes to string functions, coming from high level languages it's way different but way funnier this way (and more efficient, i guess). Also, memory managment is not that bad as people say, it's like dude, just keep track of what you're doing and that's it. I wanna be a C programmer (embedded engineering calling) someday.  


### CL Overhaul //done as of 13-02-26
It's already late today so i'm gonna try to rush it, even though it's wednesday, i might be a bit short on time already. Curious thing of the day, my family calls me alex beacause it's my middle name but every other person calls me nahum, a bit useless today but it's better than nothing.

For the first thing to do is to unify all CL's commands into cl.c so the user can write something like:  
```bash
    cl exec cxt "C:\Absolute\Path" write && cl -e cxt "C:\Report\File" info -a 
    ## OR
    cl exec cba prepare

    ## I wanna make clear, cba is also added to path so you can just
    cba prepare || cba build
```

Also, i wanna work on the exec command so you can skip hub.c and do:
```bash
    cl exec 1 ## And execute cxt
    cl exec 2 ## And execute cba ui
```

this'll gonna be a bit harder but it's ok, i have plenty of time (i have about 2 hours before having to upload this week's drop)

Im done, its so hardddddddd i've been testing and fixing for the whole night now, ill realease the version as it is just warning the users and adding an exclaimer as a BETA so people is aware it's not complete, ill work tomorrow all day to make it work. I hope i take it out of beta soon. CL is so hard, i didn't know i had such a problem here. My commands don't work even though they're LITERALLY coded and made to do so, i have no compiler issues and my installer is pretty happy too, it's just that cl.c doesn't wanna do what i tell it to do. im done for today.

The problem was the stcmp, i've always hated that function. strcmp(var, "value") == 0???? c'mon, why don't it return a bool? it'd be much more intuitive and easier.

Also, the file path was somehow causing problems when cl exec cxt path info -a and used \ instead of /... now that i think about it, it'll break if you have spaces in the path too, i'll work on that...

forgetaboutit, the user can just enter "path" and it'll automatically return a single argument instead of different ones.

Also, you should check the bottom of this file, there'll be the first official curious nerd thing of the day 

### Doc works //Done as of 09-02-26
For today (09/02/26), I'll be working on this, changelog, roadmap and all project md's must be outdated and kinda weird because i wrote them in a rush. Also, curious thing of the day, linux had over 10 thousand lines of code, 5.9k of ANSI C, 2.5k of C headers and 1.4k lines of i386 assembler (goated cpu btw).

To start the day, I read a [github article](https://github.com/resources/articles/tools-and-techniques-for-effective-code-documentation), it wasn't that useful tbh.

As i worked in the documentation (not much of a deal, it's the boring part) i noticed i haven't been updating the installer in a while, i just runned "iscc [filepath]" and didn't notice i still had to run "ninja" on my project so all versions before 1.1.0 are the exact same 1.0.0. Also, i had a few problems with lookForRootFiles.c and cba.c so i fixed them, nothing much, just design problems. I assumed i'd always need to normally read the file but now i know i didn't, prepare uses "rb" and build uses "r" so I just added a new param to lookForRootFiles() so i can just stick it into the fopen().   

I honestly didn't what to write to the ROADMAP.md so i just started to imagine the whole project and write it down, maybe that's how it words. It might be it, i think im done for today, its 6 o'clock and im hungry, see ya later! (it's been 3 hours of work now D:)

## 1.1 minor updates/patches
### 1.1.1
I just updated and improved all documentation and fixed some logic problems i noticed in lookForFiles.c and cba.c

### 1.1.2
Didn't do much tbh

### 1.2.0 BETA
i should stop with this changelogs but it helps to keep track of my thoughts outside all that "formal" language i gotta use in the normal one
- **Started refactorizing cba**  
- **CL Overhaul**  
- **Doc updated to the beta**

## 1.3.0
Hi, it's me again, for this release I'll try to:
### Refacorize CBA (i postponed it to this release)

### Add the C File Manager (CFM) cause i need it more than i thought
Hi! it's me again, today i'll try to set the base for CFM and might even postpone CBA refactorization again, i wanna make a lot of things in cl, im inspired.

First of all, let's start with definitions to save us some problems in the future (i learnt from my mistakes):

**What is a file manager?**  
For me (a.k.a, for what i need), it's a bunch of tools designed to make the coder's life easier when it comes to manage files in c, why? it's basically a lot of templates so you can just adapt them for what you need. Also, i'll add all it's headers to `/common` so i can use it as i library by just adding all .c's i need in the `CMakeLists.txt`.

**What will CFM have?**  
- **A file parser**, to return a string with the line by line of a .txt, .config, etc...
- **A file pointer**, so i can just access specific root folders whenever i want without having to write the whole path (more or less like lookForRootFiles.c).
- **A file finder/lister**, i can just put a file name into it and it'll look for it in all the folders it has access to (obviusly limited to the folder it is being executed on).

that's pretty much it, i'll get to work.

I've been thinking about hub.c, my poor guy is almost abandoned, even though it's only a launcher i feel kinda bad for him. For now, i'll leave it that way while i think of some games i could add to it :D

Damn, i locked in for about 2 hours. Anyways, look at what i did.  
```c
    void* findFile(char* name, char* root, char* type){
    if(!type) return NULL;
    // ...
    }

    void cleanBackSlash(char* source){
        // ...
    }
```
At the begining i had problems with fopen modes but found out the function didn't need that much of a detail so i removed EVERY append and write mode, if it can't read it, it'll simply return null...

im literally falling asleep rn, see ya later (didn't even test btw)!

Tuesday was pretty productive but thursday cant be any less. CAN'T FOCUS AT ALL, i guess i burnt out even though i had one day to rest. anyways, this stuff happens sometimes. I made some simple parsing and calc funcions in calc.c to continue with the cl overhaul and i think i might be done with cfm, i'll just test and pray for it to be fine.

## 1.2 minor updates
### 1.2.1
it's getting late for bed so ill rush to explain what i did for this update:
- added cfm.c and cfm.h with same functions as lookForRootFile.c (depracted now)
- made a findFile() function in cfm.c
- made a cleanBackSlash() function in cfm.c

# Nerd things to read :D

## Nerd thing 1 
### (2026-02-16, Monday)

The first computer bug was literally a moth found trapped inside a Harvard Mark II computer in 1947. Grace Hopper and her team taped it into the logbook with the note "First actual case of bug being found." That's why we call them bugs today!
(i should make something to link these .md's to my web site so i don't do the same thing twice)

## Nerd thing 2
### (2026-02-17, Tuesday)
The entire Apollo 11 guidance computer had less processing power than a modern calculator. It ran at 1.024 MHz and had 72 KB of memory, yet it landed humans on the Moon. Meanwhile, my C code struggles to parse a few strings properly. Priorities, I guess.

## Nerd thing 3
### (2026-02-19, Thursday)
The first 1GB hard drive (1980) weighed over 500 pounds and cost $40,000. Today, you can get a 1TB microSD card smaller than a fingernail for like $20. We're basically living in the future, and I'm using it to complain about string functions in C or make useless tools no one will ever use :D.