# InLine - Console based game engine
Ever wanted to make a small game to just tell a story? InLine is your solution, with it's comprehensible [scripting language](#inscript---a-scripting-language)

# Inscript - A scripting language
### Index
- [**VSCode** extension](#vscode-compatibility)
- [**#SECTION** directives](#section-directives)
    - [**Sign**](#sign)
    - [**Options**](#options)
    - [**Data**](#data)
    - [**Nouns**](#nouns)
    - [**Adjectives**](#adjectives)
    - [**Script**](#script)
- [**#TYPE** directives](#type-directives)
    - [**Written**](#written-planned)
    - [**Sequence based**](#sequence-based)
- [**Wrapped directives**](#wrapped-directives)

### VSCode Compatibility
The extension isn't ready yet so it's not in the marketplace but it's under active development.

### Section directives

#### Sign
#### Options
#### Data
#### Nouns
#### Verbs
#### Adjectives
#### Script

### Type directives
**#TYPE** directives are the most important ones, they define how the engine will read, compile and run your code so please write it correctly or there will be problems.

The syntax is pretty simple, just write #TYPE followed by the game type you'll code. for example, for sequence based games you'll write
```inscript
    #TYPE SEQUENCE_BASE
```
Or
```inscript
    #TYPE SEQUENCE
```
Both will be recognized without any complication. Now, let's move on to the different game types supported or planned.
#### Written (Planned)
Written games are planned to be literally written by the user, in the following format
```
    Situation the developer wrote
    User answer
    Situation
```
The engine will parse and manage everything using three main structs, `Verb`s, `Noun`s and `Adjective`s that point to different actions and functions. It's still being worked on and the development is currently focusing on sequence based games so I'm not sure if it's gonna be ready soon.
#### Sequence Based
Sequence based games are the main and simplest game type where the developer uses a system similar to the one in CUI to create different options for the user to choose from. The engine does everything else. The game looks something like this:
```
    GAME: Developer text (option 1, 2, 3)
    USER: 1
    GAME: Developer text ;D
```
Even though it seems easy, the developer has full control over the variables, characters and history with a few clicks.

Code Example:
```inscript
#TYPE SEQUENCE_BASED
#SECTION sign
TITLE: Your_Game_Title
DEV: Your_Name
GENRE: Your_Game’s_genre

#SECTION options

#SECTION data

#SECTION nouns
Character_1
Character_2

#SECTION script
START_SEQUENCE : Character_1 “text” (OPTIONS) “Option 1” Sequence_1(END_OPTIONS)
Sequence_1: "Hello!"
## If you leave the character slot empty, the game will just put GAME: instead of the character's name, also, you can modify that in the options section and put whatever default name you want, the variable is called DEFAULT_NARRATOR
END_SEQUENCE: Character_1 “Bye!” #CLOSE
```
### Wrapped directives
Wrapped directives are one of the most important ones in the whole language, they allow you to add logic in between sequences and dialogs, calculate things, change colors, etc...

The syntax is also pretty simple, you just write **(Directive)** arguments **(END_DIRECTIVE)**
```inscript
    #SECTION script
    START_SEQUENCE: "Hello there!" (OPTIONS) "Option 1" Sequence_1(END_OPTIONS)
    Sequence_1: "You pressed 1!"
    END_SEQUENCE: "Bye!" #CLOSE
```
Now, I'll procede to list all aviable directives
#### (OPTIONS)
The most common one after #GOTO, (OPTIONS) allows you to specify all possible options the user has in a decision 
#### (COLOR)
#### (ATTRIBUTE)
#### (EMBED)
Embed is allows you to literally embed, insert (or whatever you wanna call it) inscript logic into a string.  
Example usage:
```
    #SECTION script
    START_SEQUENCE: "Hello! the result of 1 + 1 is: (EMBED)(CALC) 1+1 (END_CALC)(END_EMBED)"
```
#### (CALC)
Calc is as simple as it looks, write your expression and that's it, it's considered logic so it goes inside an embed block if you wanna put it inside of a string.  
Example usage:
```inscript
    #SECTION script
    START_SEQUENCE: "Hello! the result of 1 + 1 is: (EMBED)(CALC) 1+1 (END_CALC)(END_EMBED)"
```
In this case, it'll be printed because it's inside the embed tag directive but if you put it inside another one, for example, attribute, it'll just return the value. Also, you can modify variables with that, check this out.  
Example usage #2:
```
    #SECTION data
    INT variable: 1

    #SECTION nouns
    MAIN_CHARACTER: Name, #ffffff, Attribute INT 1
    #SECTION script
    START_SEQUENCE: Name "Look! my attirbute is at: (EMBED) (ATTRIBUTE) Name, Attribute, MODIFY (CALC) 
```
### # Directives

### Autor
- Developed by Nahum Naranjo as part of the C learning project