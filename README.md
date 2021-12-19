# Einkaufsliste

[![workflow](https://github.com/Assertores/Einkaufsliste/actions/workflows/linux.yml/badge.svg)](https://github.com/Assertores/Einkaufsliste/actions/workflows/linux.yml)
[![workflow](https://github.com/Assertores/Einkaufsliste/actions/workflows/windows.yml/badge.svg)](https://github.com/Assertores/Einkaufsliste/actions/workflows/windows.yml)

this project is ment to help you figure out what you have to buy to be able to cook your recipece.

## download

[here](https://github.com/Assertores/Einkaufsliste/releases)

## vision statement

- finish a project up.
  
  - being able to distrebute updates.
  
  - make it build, execute and accept user input to achive ...

- have everything be tested

- have everything expandable

## features

### execution arguments

| argument              | description                                                                                                          | remark                                                                                                                   |
| --------------------- | -------------------------------------------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------ |
| `--no-patch`          | will not try to patch files to the new version                                                                       |                                                                                                                          |
| `--no-update`         | will not try to download an update                                                                                   |                                                                                                                          |
| `--set-update-url`    | changes the url it trys to get the download from                                                                     | not implimented                                                                                                          |
| `--shut-down`         | will automaticly shut down the executable after updating and patching.                                               |                                                                                                                          |
| `--log-level [LEVEL]` | sets the granolarity of logs being loged. the following is possible: `silent`, `fatal`, `error`, `debug`, `verbose`. | the lower levels also contains all more higher levels of logging. e.g. `--log-level error` logs all fatal and error logs |
| `--help`              | shows these arguments                                                                                                |                                                                                                                          |

example:

`einkaufsliste.exe --no-update --log-level silent`
this will run the executable without updating and with no logs.

### comandline interface

comands are only inputed one by one. writing `open recipe C:\my\path.md` will not be understood. type the command first (e.g. `open recipe`), press `enter` now you'll get asked to input a file path, input the path (e.g. `C:\my\path.md`) and press `enter`. now your recipe is opend.

#### high level commands

| command                     | description                                                                        | remark                                                                                                                                           |
| --------------------------- | ---------------------------------------------------------------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------ |
| `exit`, `quit`              | stops the executable                                                               | this only works if you are not within another command                                                                                            |
| `undo`                      | undoes the last run command                                                        | only undoable commands get undone. redo is not undone                                                                                            |
| `redo`                      | reaplyes the last undone command                                                   |                                                                                                                                                  |
| `open recipe`               | opens a file and consideres it to reprecent a recipe                               | creates file if not already existing                                                                                                             |
| `change recipe name`        | sets (or overwrites) the name of the current active recipe                         | this command is only guaranteed to work if the current opened file is a **recipe**                                                               |
| `change recipe description` | sets (or overwrites) the description of the current active recipe                  | the input currently only alows for a single line of text.<br/>this command is only guaranteed to work if the current opened file is a **recipe** |
| `add recipe ingredient`     | add a ingredient to the current active recipe                                      | this command is only guaranteed to work if the current opened file is a **recipe**                                                               |
| `remove recipe ingredient`  | removes a specific ingredient of the current active recipe                         | this command is only guaranteed to work if the current opened file is a **recipe**                                                               |
| `print`                     | prints the current active file                                                     |                                                                                                                                                  |
| `open convertion`           | opens a folder containing convertion files                                         | the folder may only contain convertion files                                                                                                     |
| `open week`                 | opens a file and considers it to reprecent a week                                  | creates file if not already exisiting                                                                                                            |
| `start list`                | creates a new file as a list                                                       | if the file already exists, then it will automaticly pick up the contant                                                                         |
| `add week to list`          | adds the content of a week to the staged files of the current active list          | this command is only guaranteed to work if the current opened file is a **list**                                                                 |
| `add recipe to list`        | adds a recipe to the staged files of the current active list                       | this command is only guaranteed to work if the current opened file is a **list**                                                                 |
| `compile`                   | generates a list of ingredients out of the staged files of the current active list | this command is only guaranteed to work if the current opened file is a **list**                                                                 |
| `add recipe to week`        | adds a recipe to the current active week                                           | this command is only guaranteed to work if the current opened file is a **week**                                                                 |
| `remove recipe from week`   | removes a recipe from the current active week                                      | this command is only guaranteed to work if the current opened file is a **week**                                                                 |
| `help`                      | shows all possible inputs                                                          |                                                                                                                                                  |

#### input required

| request | description                                                                                    | remark                                             |
| ------- | ---------------------------------------------------------------------------------------------- | -------------------------------------------------- |
| file    | the programm needs you to input a path to a file                                               | path is assumed to be absolute                     |
| folder  | the programm needs you to input a path to a folder                                             | path is assumed to be absolute                     |
| unit    | the programm asks you to input an ingredient, the amout and it's unit seperatly in three steps |                                                    |
| text    | asks for any texts                                                                             | can contain white space characters but no new line |

### files

#### convertion

a file containing describing how to convert between different units of the same type. e.g.:

```md
g

- 1000

kg

- 1

mg

- 1000000

t

- 0.001
```

all entrys in the file should be the same amount e.g. `1000g` = `1kg` = `0.001t`

there is currently no way to create these files from within the programm therefore these files currently have to be created by hand.

this system is subject to change.

#### recipe

it contains a name, a description (used to describe how to cook it) and a list of ingredience needed to cook this recipe.  
this list is used to compile the shopping list.

subject to expansion. following features might be added in future:

- split description into instructions and descriptions

- adding a picture

- time required

- inharant form other recipes

- rating

#### week

can hold a reference to a recipe for every weekday and every timepoint (with a minute resolution).

#### list

contains a list of "staged" files which are used for compiling the list and a list of unique ingredience with there units added together as far as possible. for this the convertion files are used. if it can not combine two units they are listed seperatly. e.g. `onion: 150g, 2 piece`.

## licence

[GNU General Public License v3.0](./LICENSE)