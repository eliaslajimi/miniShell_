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
- *>*
- *>>*
- *<*
- | (what is the extent of pipe usage? not simple redirect).
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
Signals can be interpreted as *separators* although they tend to implicate more drastic changes to current runnign processes.
- Ctrl + C *interrupts the current foreground process running. process's command table is therefore deleted and not interpreted*
### More on Parser:
#### Lexer:
takes input characters and put them into word called tokens.
#### Parser:
Processes the tokens according to inner semmantic to be able to build command tables.
![flow chart of miniShell project](https://i.ibb.co/PNwWScf/shell.jpg)
#### Introduction to the pipe() system call
Similarly to pipe(), fork() is used to create processes. It takes *no arguments* and return a process ID.
fork() will then start a child process *identical* to the original parent process, and both process will execute the instruction following the
fork.
```
int main()
{
	pid_t pid;
	
	pid = fork();
	if (pid == 0)
		write(1, "pid is 0\n", strlen("pid is 0\n"));
	else 
	{
		write(1, "pid is ", strlen("pid is "));
		write(1, itoa((int)pid), strlen(itoa((int)pid)));
		write(1, "\n", 1);
	}
	return (0);
}

```
To successfully identify which of the two process is running, the program should refer to the variable pid_t pid directly.
**It is to be noted the system will make a copy of the parent's adresses. Therefore both parent and child have different adresses**

## My approach to pipe:
![pipe](https://i.ibb.co/wz9mmQw/pipe.png)
## My approach to Minishell:
![minishell](https://i.ibb.co/wQb8yDH/overall-shell.png)
## Shell Implementation (IN PRACTICE)
#### Summary
The Minishell REPL is divided into a couple of funtions. The first one is the lexer. This one will use several simple utils and iterate through the string identifying 
key tokens. It'll then return a double pointer char to a parsing function. The parser has the same semantic, but this time identify the role of each token and assign it 
to a structure. once a separator is identify it passes on to a new structure and keep assigning each token to its specific role within its command table until a NULL flag 
is crossed. Once that is done, it will pass on to the executor which will iterate through each command table and apply its builtin with the correct in/out/args/flags.
#### Pipe
forking in this project is used mainly to handle realtime
multiprocessing with

#### Troubleshoot:
- 'exitr' exits regardless 
