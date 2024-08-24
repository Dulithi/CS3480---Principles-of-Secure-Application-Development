# README

## CS3480 Principles of Secure Application Development - Programming Lab 1

### Part 1

#### Description : 

lab1p1 executes a series of commands separated by `+` symbols as specified in the command-line arguments. 
Each command runs in its own process.

#### Build Instructions:

To compile the program, use the following command in the terminal:
```bash
$ gcc lab1p1.c -o lab1p1 
```

#### Usage Instructions:

To execute the program, use the following command format:
`./lab1p1 <command1> + <command2> + ... + <commandN>`

e.g.
```bash 
$ ./lab1p1 /bin/echo Linux is cool + /bin/echo But I am sleepy + /bin/echo Going to sleep now + /bin/sleep 5 + /bin/echo Now I am awake
```

__Note:__
    Ensure the specified command paths are correct for your system. You can verify the paths using the "which" command, 
    e.g. which echo


### Part 2

#### Description:

lab1p2 is a shell-like tool that executes repetitive commands, replacing placeholders % with subsequent inputs provided by the user.

#### Build Instructions:

To compile the program, use the following command in the terminal:
gcc lab1p2.c -o lab1p2 

#### Usage Instructions:

To execute the program, use the following command format:
`./lab1p2 <command> % % ... %
<command1>
<command2>
...
<command2>`

`%` is a placeholder for the words that will be entered in the subsequent lines. 


press `CTRL + D` to indicate end of inputs

e.g. 
```bash
$ ./lab1p2 gcc -c %
a.c
b.c
c.c
```

e.g.
```bash
$ ./lab1p2 gcc % % % % % %
-c a.c
-c b.c
-c c.c
-o a.o b.o c.o
```
    


