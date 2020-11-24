# miniShell
## Shell Implementation
### The Parser
The *parser* will read the command line and transpose it into a data structure *Command Table*.
### The executor 
The *executor* will read from the *Command Table* and create a new *process* for each one of them.
The executor also takes care of the redirections -> *Standard Input/Standard Output/Standard Error*.

![signal flow of typical command](https://ibb.co/W5C9Dc6)

### Shell Subsystems

