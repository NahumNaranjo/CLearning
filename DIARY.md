# Dev Diary :D  
## Introduction
Here, I'll narrate every single problem/curious thing that happened during the development of this project, just so I can read it and laugh at myself in the future (I hope near future D:).  

## Release numbering first amendment
Hi, this week of vacation (forced) was pretty mind clearing and i found something out, a tool a week isn't that cool (nor sustainable) so im moving the versioning system a bit.  
No more weekly drops but instead meaningfull minor updates, What do I mean by meaningful?
- a new tool  
- a big change (tool refactor, deletion, etc...)  
- a new feature for the ecosystem

Those would be the x.X.x versions  
For the x.x.X versions will be patches and hotfixes and for x.x.xA will just be a little amendment  

Now, for X.x.x versions, i think they deserve something special, like, maybe a new era? for when i finally add InCEngine and start making some games for bored devs or something

Also, for x.x.xPX versions, it's just a part of a small update (new daily drops)

That's all for now, see ya later!
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

### Add the C File Manager (CFM) cause i need it more than i thought (Forgot to record when i finished, didn't notice at the moment)
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

#### Calculator shenanigans (CL overhaul sequel, CFM crossover) (Done as of 2026-03-06)

The calculator didn't work so i had to rewrite it a bit (literally from scratch). Lightwork tbh, see ya tomorrow?

Hi! today's been a very productive day, did loads of things, first of all, i rewrote (again) the calculator, now, it firstly identifies any whitespace to use two different parsers, once its parsed it goes through a for loop (which was a hell to make) to calculate all tokens. For now it's just linear calculation, not operation order implemented just yet, maybe it'll come next update or so.

Anyways, calc.c was such a pain today because of the parsers and everything. I learned that For loops ain't as good as i thought for such complex calculations but it's too late to change it to a while. Also, i didn't know that if you had an if statment without braces it only read the first line immediately after it and will always execute everything under them, I hadn't needed more than two lines but in the end-of-loop if i had 
```c
    if(condition == true) result = result; break;
```
And it always broke everything, had to change it to
```c
    if(condition == true){
        result = result;
        break;
    }
```

it was beneficial after all because it didn't calculate for multiplications, substractions or divisions, just added ;D, once i fixed the one line if problem, i found out and fixed the last one.

today, i used CFM for the first time to parse some config files for calc.c, was pretty impressive to not have any problems after not testing it at all, im a god coder or something i guess

also, i broke calc, messed up the computing and it doesn't work at all, that's why today's update is "1.2.5p1" cause is a pre-pre-release ;D

DIDN'T KNOW THERE WERE PREMADE ALGORITHMS FOR READING MATHEMATICAL EXPRESSIONS THIS WHOLE TIMEEEEEEE, im usin shunting-yard now, i have an hour to learn it, make it and test it, wish me luck. also learnt postnix notation btw, great one.

It was a pain but it's done, i ended up stealing a lot of code from the web but i swear i tried and didn't go as good as i wanted so i refactored almost every single line of  calc.c

## 1.2 minor updates
### 1.3
- calc.c and cfm.c are pretty much complete now
### 1.2.5p1
- calc.c's computing is being remade
### 1.2.4
- calc.c beta 2.0 is out
### 1.2.3
- calc.c entered beta
### 1.2.2
- calc.c added
- cfm worked and almost ready
### 1.2.1
it's getting late for bed so ill rush to explain what i did for this update:
- added cfm.c and cfm.h with same functions as lookForRootFile.c (depracted now)
- made a findFile() function in cfm.c
- made a cleanBackSlash() function in cfm.c

## 1.4.0  
i must admit that 1.3 development was kinda chaotic i'll try to be more organized for this one   
### HUB Overhaul
First of all, i wanna settle this one soon so i'll try to be quick, concise and effective:
**What's wrong with it?**
it's useless, tbh, wasn't thinking that cl exec would completely destroy cl hub so now it HAS to have something else cl command line doesn't, what is it? one word, VIDEOGAMES, so, what will cl hub actually do now?
- No more tools as the main exe's, it will now be purely videogames in different sections, one for each genre
- Tools will have its own section to explore
- hub will be the only way to access these games
- CBA and InCEngine (First thing InCGames developed and im stealing it (from myself)) will interfere and help devs build quick and funny games to add to their library if they're bored

To start, why don't i remake the UI? actually, let's do another section for that.

I'm finally ready to work with this, also, i took some days off because of my birthday, forgive me ;D.

I guess today's the day i launch 1.4.0 so i better get to work, firstly, i'll start with the most obvious thing, the UI remake using the newly developed CUI ;D

it's pretty much done tbh, i thought it'd be harder but nah, cui made it too easy.

### CUI (Like how peruvians call guinea pigs) (Done) <- - - This one is a Hub overhaul extension
First of all, im gonna make a centralized buildUI() and, long story short, centralize all ui.c's in one library i can even add to this release.

Again, i entered flow state, i made an engine to manage ui's from scratch in like four hours, incluiding refactorizing cxt and most of the time, testing and hating on microsoft and their weird ass functions for c. Anyways, it was fantastic and i barely remember it but i just coded like a machine. updated all readmes and even made a new function for cfm and thought about adding a cl install because all the tools are actually useless. ill try to investigate about this. Also, i entered a dilema, should i name this version 1.4.0 or 1.3.1? i mean, it's a new tool but 1.3.0 is just out.

To finish, ill try to summarize what i remember:
- Firstly i started planning the tool, what i needed to centralize and what would be imposible to do, so, i just thought about a bunch of new datatypes to store every option and return a parsed result, like, make a list or something ant cui should ask the user and get everything the programmer needs.
- secondly, i started coding, obviusly, i made the datatypes first and then made a simple title and menuDisplay, then, again, i tried to centralize data collection so i made readinput which i think it's the most useful function here.
- thirdly, i made practically everything else, it's just boring checks and parsings

there you are, i think you have enough of today (long story short, i dont wanna embarass myself with the stupid errors i found while refactorizing cxt, i literally looked at my code and thought someone really really stupid made it (It was me but a month before and the closest thing i had touched was cpp)).

After making cui from scratch and refactorizing cxt (in fact, it's in between), i needed a function to list files and couldn't belive i didnt make one for cfm so i started investigating, confirmed microsoft isn't really the company of the smart people and then made the function with what microsoft had to offer (just confusing datatypes and functions).

### CL update (done)
Made cl install!! why? why not? i had very little time today so i decided to do something small, it's simple, it just installs the packages to a root folder and copies and paste them in /common/packages, that's it, run cl install [tool] and it'll look for the current working dir's common folder and make its magic there.

Also, had to update CFM so it now handles getCurrentDir and dirExists. pretty simple, stolen code from the internet, ngl, i just adjusted a bit.

Today (thursday), i wanted to test and fix the bugs i find but didn't really show any, i haven't made a new project to test it for real but it's working without many problems for the moment, just some design issues i solved instantly with one more system call mkdir'ing a new folder for the tools installed, i should make a `cba copy common` so it copies a new CMakeLists.txt for the common dir and have no problem, anyways, that's for cba refactor.

### CBA Refactor (Now it's fr, i need this) (done)
I started working on it, it's not that bad, i guess, i'll just try to.

God, i dont know what i did but it had like thousands of errors once i built, i didnt understand anything and had to duplicate lots of files, very bad of me but it works now, i guess....

Also, this refactorizing was pretty easy, just literally restructured and changed some stuff, not so much to tell. Thought it would be harder tbh

## 1.3 minor updates
### 1.3.2p1
it was pretty small and i didn't even test, thats why it's p1 instead of full pre-release. check [changelog.md](/CHANGELOG.md) for more
### 1.3.1
Im too lazy to list so many things two times so, check [changelog.md](/CHANGELOG.md) please (sarcasm)

## 1.5.0  
### InCEngine port (InLine)
Ufff, it's gonna be a hard one but let's dive into it  
**What do i want for this port?**
- To have a fully specialized game engine for cmd and work completely by itself.
- Renderer with double buffer (to avoid flicker)
- frame rate control
- profiling tools
- A fully optimized result
- debugging features
- scene managment
- audio system (later)
- resource managment
- collision detection
- game object managment
- input system
- console managment

**Desired game loop structure**
- Initialize
- Process Input
- Update
- Render
- Cleanup

it's quite a bit but let's hope i can make it ;D

For the first version, aka, this week's version, i'll make the text based engine.

Im about halfway to make the textParser so i think its a good point to check on what i did  
First of all, i made a new typedef, verb, it has a full name and a short so the user can either write "take sword" or "t sword" and still be   
I'm having a bit of a conceptual crisis here so i'll just center in text based story centered games and then build the rest of features  

I think i'm almost finished with the file manager so i guess its enough for today. Honestly i was quite disapointed i couldn't use cfm for this (portability issues). Anyways, i did a lot of things today.

first of all, i did the innit() function, which is the largest for now, it's not finished just yet but i guess it's like a 90%. It uses the same techniques i used to make cfm but adapted to the specific syntax i needed for this project, also, i forgot to mention that the text based games will be saved into a file and compiled in real time while the user plays.

Also started to code the dialog system which will act more like an internal thing than something the user will need to use, it'll be automatically handled (obviusly, if we're speaking of text based games).

Lastly, i deleted all screenManagment.c/.h and stringManupulation.c/.h references, they have finally been replaced with the more modern hermes and ariadne versions respectively.

You won't believe it but my brother's office litterally ran out of water so he stole my studio for the first week, anyways, i discovered [FXTap](https://github.com/SpeedyOrc-C/fxTap) and i think i could port it to arduino, how? idk but it'll be funny. Anyways, let's get to work.

I'm honestly a bit burnt out, it's time to eat and now i have another side quest, clist. Anyways, didn't really do anything today, cheers!

Dialog was kinda easy to make but i learnt environment variables are incredibly useful, anyways, see you later!

After a LOOOOOOOOONG week of not being able to work, im able to sneak a little today, let's see what i can do.

Didn't do much, i'm honestly rusty but it's ok, ill get used to it again in no time. Didn't have much trouble but one little thing i didn't know, C has operator precedance too! so i had to call `((inlineError*)errList.content[0])->code` instead of just `(inlineError*)errList.content[0]->code` cause `->` is more important. Weird, isn't it?

### Adding games to CL ;D

### CList (Done as of 04-07-26)
I'm basically just gonna copy python's list cause it's way easier than fighting against an array every time i wanna store data.

Today was a very productive day, i think clist is ready, i'll summarize everything i did function by function.

- First of all, i made createList() cause i didn't really know how to start (fyi, i made this based on python's lists), it was simple, i just did a bit of reaserch on how did cpython allocate its lists and recreated it, pretty simple tbh.
- Secondly i made add() and insert(), which were also easy cause they just move all the data one position to the right (and more importantly, reallocate if needed) and then insert what they need. I struggled at first cause i was obsessed with finding an O(1) solution to this but it seems to be imposible.
- lastly, cherryPick(), pop(), append() and len() which were pretty much easy.
- Then (once i finished) i started optimizing, moved all the capchecks to capCheck() and the movelists to moveList().

### C Configuration Manager (Done as of 2026-03-30)
I started it as a side project for InLine engine so i could manage it's config files in an easier way. For now, it's just basic parsing and file managment.
i've been super tired lately, anyways, tuesday i didnt update this project but i made and ported all tools' repositories so i guess that's enough.  
for today, i just fixed some bugs 1.4.1p1 had.  

Today i locked in for ccmanager, it is now complete for the user part, you can append or read your config files easily now. It was pretty much the same as usual, strtok to manage input and using cui and hermes to literally everything, i love 'em. Anyways, see ya tmrw.

I didn't realize how buggy 1.4.1 was, i literally spent the first 30 minutes just bugfixing and patching some little things (hundreds of them). Anyways, it's 13:30 and i have a lunch break by 16 so i still have time.

Yeah, i forgot to tell you guys but i did finish everything that day

### unrelated content
Today i didn't work on anything related to the update, instead, i literally spent all day bugfixing to make this baby compile, it was surprisingly easier than coding new functions, i guess my brain rested today.  

Also, i decided to make this "unrelated" section for days like this, for example, this friday will be only testing every change since the las stable version (1.4.0) which is kinda a lot.

Also, i learnt a lot today and yesterday working on clist, i think i should make more things like that, before this, i know so little about arrays (and i thought i knew everything about them), i saw them as simple little guys. Now they're my worst enemy and i love it; I also learnt about these (void**) things and so, don't really know when they're necessary but i'll keep trying to put them everywhere.

Aaaaaaaalso, this version is the first built pre-release since a while ago.

Today's testing day, i think it'll be a loooooooong day

I found the bug in lookInRoot() and ParseFile():

lookInRoot() was only trying the hardcoded CL path, so on my repo it failed to open calc.config.
ParseFile() was also broken in cfm.c: it had a duplicate old implementation and bad buffer growth logic.
calc.c was reading config lines with sizeof(config) / sizeof(char*), which is wrong for dynamically returned arrays.
So i fixed it:

made lookInRoot() try both the hardcoded InCGames path and local repo/cwd fallback paths
cleaned up ParseFile() to allocate lines properly, return the real line count, and avoid the duplicate broken block
updated calc.c to use ParseFile(fp, &configLines) and loop over the actual number of lines
changed the config lookup to configs/calc.config
After that, the calculator finally worked again:
build\cl.exe calc 1+1 => Result: 2

Im honestly too tired to work today

My head hurts today, anyways, look at thisI wired the root CMakeLists.txt so a single configure builds common, CFM, CCManager, InLine, CL, hub, CBA, the CUI static lib, and CXT instead of only CXT, then hit build until it went green.

CXT was the messy one: there were two different map.h ideas fighting each other (common's void-pointer Map vs the half-written cxt-local header), AnalyzeText didn't exist in the cxt tree at all so the linker was doomed, and txtFunctions.c wasn't even valid C anymore. The sane fix was to stop pretending cxt is a separate implementation and typedef AnalyzeTextData to the same structs as common/cxtGeneralData.h, delegate AnalyzeText() to commonAnalyzeText(), and delete the duplicate projects/cxt/map.h. After that, cxt_app finally links again.

Hub was sneakier: a clean build failed with undefined gamesInterpreter / toolsInterpreter because I typo'd gameInterpreter in hub.c and never defined the tools one. Also main.c used if (res = 'e') twice (assignment, not compare), and ui.c passed an uninitialized count into createMenu(), which is the kind of bug that only shows up when you're unlucky with stack garbage. CUI's project CMakeLists.txt was building a .exe from a library with no main, hence the WinMain linker whine; turning it into cui_lib fixed that. Patched projects/cui/cui.c too because menu->title, title wasn't assigning anything (strncpy now).

Today was research day for CList, i have to find a way to identify strings without the user having to manually type it, how? i dont know, it's easier to just divide the functions in `stringFunction` and `function` but i guess it's more boring that way. I've tried everything, even assembly, but nothing seems to work exactly as i want it to and with 100% efectiveness so i guess i'll implement a vote system where different systems work together and vote to have the highest chance of a correct guess. Anyways, that's a lot of work and it already took me a lot to find out what to do, i'll see how i do with such complex thing tomorrow. No news this update.

Today's coding day!! I was finally able to code what i reasearched for yesterday, and it was easier than i thought but taught me so much about c!!!! first of all, **C DOES HAVE A WAY TO HANDLE EXCEPTIONSSSSS** its called setjmp and longjmp, they work kinda weird but are like try/catch and i used them together with signals so i could modify its flow to exactly what i needed ;D. 

I'm sorry guys but i hurt my fingers and i can't really code today, sorry D:

## 1.4 minor updates
### 1.4.7
- Test and fix (again)

### 1.4.6
- test and fix
### 1.4.5
- Small update to dialog.c
### 1.4.4
- General bugfixing, testing's this friday
### 1.4.3
- CList officially added to CLearning
### 1.4.2
- InFile has been added to InLine
### 1.4.1
- CCManager first half
### 1.4.1p2
- minor patches
### 1.4.1p1
- Setup only

## 1.6.0

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

## Nerd thing 4
### (2026-02-20, Friday)
The `strcmp` function in C returns `0` when strings match because it was designed to return the difference between the first mismatching characters. So if they're equal, the difference is... zero. Makes sense historically, but yeah, still annoying when you just want a boolean (i really hate `strcmp`).

## Nerd thing 5
### (2026-03-02, Monday)
You won't believe it, they killed a mexican cartel capo and everything exploded so my brother's boss let him do home office all week so i wasn't able to use my studio (I could've coded in my laptop but 1, im too lazy and 2, i can't focus if isn't in my studio so meh). I also made a good beat this week, check my spotify ;D.

## Nerd thing 6
### (2026-03-03, Tuesday)
The name "C" exists because it's the successor to a language called "B" (which was itself a simplified version of BCPL). So technically, if they ever make a language after C, it should be called "D" — and they did, but it never really took off. C++ was originally called "C with Classes." Imagine explaining that to recruiters today.

## Nerd thing 7
### (2026-03-05, Thursday)
Ninja is named like that because it's supposed to be fast and stealthy — it only rebuilds what's necessary and gets out of the way. It was created by Evan Martin at Google to replace Make for Chromium builds. True story: Chromium's build was so slow that switching to Ninja literally saved hours of developer time per week.

## Nerd thing 8
### (2026-03-06, Friday)
The first-ever computer programmer was Ada Lovelace, way back in the 1840s. She wrote algorithms for Charles Babbage's Analytical Engine (a mechanical computer that was never built). She also predicted computers could do more than just math — like composing music. So basically, she was doing high-level thinking before C was even a twinkle in Dennis Ritchie's eye. Happy women's day btw, y'all are beautiful tbh.

## Nerd thing 9
### (2026-03-09, Monday)
The `gets()` function in C was so dangerous (no bounds checking = buffer overflow heaven) that it was literally removed from the C11 standard. It had one job: get a string. And it failed so hard they just... deleted it. RIP gets(), you won't be missed. Use fgets() like a responsible adult like me.

## Nerd thing 10
### (2026-03-10, Tuesday)
CMake isn't a build system — it's a build system generator. It creates files for other build systems (like Ninja or Make) so you don't have to write them yourself. Meta enough for you? It's like writing a program that writes programs that build programs. CBA is better btw, it generates the CMake files so the build file generator can generate the files for the builders, confusing, isn't it?

## Nerd thing 11
### (2026-03-12, Thursday)
The first "C" compiler was written by Dennis Ritchie at Bell Labs in the early 1970s. Fun fact: the entire first version of Unix was rewritten in C by Ken Thompson and Dennis Ritchie so they could move it to different machines more easily. Before that, Unix was written in assembly. Imagine rewriting your entire OS in C just for portability. Absolute madlads.

## Nerd thing 12
### (2026-03-19, Thursday (huge vacation here))
The "segmentation fault" (segfault) you keep running into while coding in C? That error message was originally implemented in Unix to protect different programs from accidentally overwriting each other's memory. When you get one, you're literally experiencing a safety feature designed in the 1970s trying to save your computer from yourself. The OS is out here playing guardian angel while you forget to allocate memory properly.

## Nerd thing 13
### (2026-03-23, Monday)
The `#include` directive in C doesn't actually "import" anything like modern languages. It's literally just a copy-paste. The preprocessor takes `#include <stdio.h>` and pastes the entire content of that file into your code before compilation. That's why you get massive compilation times if you're not careful — you're copy-pasting thousands of lines of code without even knowing it. Brutal, but effective. (im honestly bad at it)

## Nerd thing 14
### (2026-03-24, Tuesday)
The `NULL` pointer in C isn't actually required to be `0` in memory — the standard says it's an implementation-defined null pointer constant that *compares equal* to 0. On most systems it's just `0`, but some ancient architectures used weird values like `0xFFFFFFFF`. So when you write `if (ptr == NULL)`, you're trusting your compiler to handle the magic behind the scenes. Pointer dereferencing a null is still guaranteed to crash though, no magic there.

## Nerd thing 15
### (2026-03-30, Monday)
(I forgot to  write Thursday's nerd thing of the day)  
The `clock()` function in C doesn't measure real time — it measures CPU time consumed by your program. Big difference! If your program sleeps or waits for user input, clock() stops ticking. If you want actual wall-clock time, you need `time()` or `gettimeofday()`.

## Nerd thing 16
### (2026-03-31, Tuesday)
The `static` keyword in C does three completely different things depending on where you put it:
- Inside a function: variable keeps its value between calls (persistent memory)
- Outside a function: variable is only visible within that file (file scope)
- On a function: function is only visible within that file (encapsulation)

Three meanings, one keyword. C is beautiful and terrifying at the same time. Whoever designed this either loved minimalism or hated developers. Maybe both.

## Nerd thing 17
### (2026-04-06)
The `volatile` keyword in C tells the compiler: "Don't optimize this variable away, it might change at any moment." Why? Because external things like hardware devices, signal handlers, or other threads can modify it without the compiler knowing. Use it wrong and your code becomes slower. Forget to use it when you need it and your code breaks in ways that only happen when optimizations are on. Debugging that is a nightmare. Just ask anyone who's ever written embedded C.

## Nerd thing 18
### (2026-04-07)
The `goto` statement in C isn't actually evil — it's just misunderstood. In fact, the Linux kernel uses `goto` extensively for error handling. One function, one label for cleanup, and you jump to it when something fails. No nested `if` hell, no memory leaks. The real sin isn't using `goto` — it's using it to create spaghetti code. Use it wisely and it's beautiful. Abolish it completely and you're just making life harder for yourself.

## Nerd thing 19
### (2026-04-08)
The `++` and `--` operators in C are a blessing and a curse. You can do `x++` (use then increment) or `++x` (increment then use). Looks simple, right? WRONG. Combine that with pointers and you get nightmares like `*p++` vs `(*p)++` vs `*++p`. One increments the pointer, one increments the value, one does god knows what. I've spent 20 minutes tracing through code just to realize I used the wrong one. And for what? Saving one line of code? We've all been there. Don't lie.

## Nerd thing 20
### (2026-04-09)
The `switch` statement in C falls through by default. Yep, if you don't write `break`, it just keeps executing the next case like nothing happened. Sometimes that's useful (multiple cases sharing the same code), but most of the time it's a bug waiting to happen. I can't count how many times I've forgotten a `break` and spent an hour wondering why my program was acting possessed. The designers thought "let's make fall-through the default" was a good idea. It was not. But here we are, decades later, still suffering.

## Nerd thing 21
### (2026-04-10)
The `enum` in C isn't really a type — it's just glorified integers. You can literally do `enum Color { RED, GREEN, BLUE }; int x = RED;` and the compiler won't even blink. No type safety, no "this variable can only be one of these three values." Just ints with fancy names. Python programmers would have a heart attack. But honestly? Sometimes I love it. Other times I want to scream. Depends on how many bugs it's caused me that week.

## Nerd thing 22
### (2026-04-13)
The `sizeof` operator in C is evaluated at compile time, not runtime. Which means `sizeof(array)` only works if the compiler knows the size at compile time. Pass that array to a function and suddenly `sizeof` just gives you the pointer size (usually 8 bytes on 64-bit systems), not the actual array size. So many beginners fall for this. I fell for this. We all fell for this. That's why you always pass the size as a separate parameter. Every. Single. Time. No shortcuts. The language won't save you.

## Nerd thing 23
### (2026-04-20)
The `const` keyword in C is more of a promise than a rule. You can declare something as `const`, but nothing stops you from casting away the constness with a pointer and changing it anyway. The compiler will warn you, sure, but it won't stop you. It's more like "hey, I really don't think you should change this" instead of "you absolutely cannot change this." Meanwhile, C++ actually enforces it properly. Yet another reason people say C is just "high-level assembly" — the language trusts you to know what you're doing, even when you clearly don't.

## Nerd thing 24
### (2026-04-30)
I've been offline for most of the last two weeks due to my brother stealing my studio because his boss told him to do home office for those two weeks, we both don't know why. Anyways, he had to actually go the weekdays i did push something to github.

## Nerd Thing 25 
### (2026-05-04)
The `setjmp()` and `longjmp()` functions in C are basically a DIY exception system before exceptions were cool. `setjmp()` saves the current execution context (registers, stack pointer, all that jazz), and `longjmp()` jumps right back to that saved point like nothing happened. It's like goto on steroids — you can jump across functions, not just within one. Sounds useful, right? WRONG. It completely skips normal function cleanup. No stack unwinding, no resource deallocation, just poof you're somewhere else. Use it wrong and your memory leaks could fill an ocean. That's why nobody uses it. Except database guys. They're built different.

## Nerd thing 26
### (2026-05-05)
The `#pragma` directive in C is the compiler's way of saying "here, have some vendor-specific magic, I don't want to standardize this." Every compiler does its own thing. ``#pragma once`` works on GCC, Clang, and MSVC but isn't officially in the C standard. ``#pragma pack`` for struct alignment? Different syntax everywhere. Warnings? Good luck. It's the wild west. You write ``#pragma`` and pray your code still compiles when someone uses a different compiler. The standard committee basically gave up and said "yeah, compilers, do whatever, we don't care." Chaos incarnated into a preprocessor directive.