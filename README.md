# miniShell
## Shell Implementation (IN THEORY)
### The Parser
The *parser* will read the command line and transpose it into a data structure *Command Table*.
### The executor 
The *executor* will read from the *Command Table* and create a new *process* for each one of them.
The executor also takes care of the redirections -> *Standard Input/Standard Output/Standard Error*.
![signal flow of typical command](https://i.ibb.co/Rb8nhC9/Screen-Shot-2020-11-24-at-17-22-05.png)
**It is to be noted that '>& errfile' should redirect **ERROR LOG** of each command to errfile**
Related operators are:
-*>*
-*>>*
-*<*
- *|* (what is the extent of pipe usage? not simple redirect).
### Shell Subsystems
#### Environment Variables
Setting up an environment with its variables.
Related commands are: 
- *env*
- *export*
- *unset*
- *$VAR*
#### Wildcards
Simple \* REGEX handling for pattern matching. (mandatory?)
### Subshells
Parsing through *``* *''* *""* to retrieve correct shell input.
### Separator:
Separator should work as end signals for the parser.
One separator signals the ending of the *command table* configuration.
If more data is yet to be parsed through, a new *struct* is created and a new *command table* is then being used.
Related separators are: 
- *;*
- *\n* (others of the same kind ?)
- *Signals*
### SIGNALS:

## Shell Implementation (IN PRACTICE)
