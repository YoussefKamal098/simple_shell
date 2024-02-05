
<h1 align ="center" style="font-style:italic; font-size: 4em">Simple Shell</h1><br>


## Repository Description

This repository contains the files to simulate a basic `Unix Shell` with its respective commands. It uses the POSIX API to implement many of the same functionalities of the first Ken Thompson's Shell and It is made to carry out the  `0x16. C - Simple Shell` project at [ALX Africa.](https://www.alxafrica.com/ "ALX Africa.")

## General.

- All your files will be compiled on Ubuntu 14.04 LTS
- Your programs and functions will be compiled with `gcc 4.8.4` using the flags `-Wall` `-Werror` `-Wextra` and `-pedantic`
- All your files should end with a new line
- A `README.md` file, at the root of the folder of the project is mandatory
- Your code should use the `Betty` style. It will be checked using [betty-style.pl](https://github.com/holbertonschool/Betty/blob/master/betty-style.pl "betty-style.pl") and [betty-doc.pl](https://github.com/holbertonschool/Betty/blob/master/betty-doc.pl "betty-doc.pl")
- Your shell should not have any memory leaks
- No more than 5 functions per file
- All your header files should be include guarded

## Requirements:

* Operating System: [Ubuntu 14.04 LTS](http://releases.ubuntu.com/14.04/)

* Compiler: [GCC 4.8.4](https://gcc.gnu.org/gcc-4.8/)

## Features:
* This `Shell` displays a prompt and waits that the user types a command. A command line always ends with a new line (when user push `ENTER` key).
* The prompt is displayed again each time a command has been executed.
* When the user enters exit, `Shell` will end and returns the status 0.
* When the user enters exit `[status]`, `Shell` will end and returns the inputted status, where `status` is a value from 0 to 255. 
* The user could stop the program using `Ctrl+D` (end of file).
* The `Shell` handles the command lines with arguments and pathways.
* The `Shell` does not quit when the user inputs `^C` `(Ctrl+C)`.
* The `Shell` prints the current environment when the user types `env`.
* This `Shell` executes the most common shell commands as `ls`, `grep`, `find`, `pwd`, `rm`, `cp`, `mv`, `exit`, `env`, `cd`, `alias`, etc... with arguments.
* If an executable cannot be found, It prints an error message and displays the prompt again.
* This `Shell` supports commentaries using `#`, 
* The `Shell` does NOT support wildcard characters such as ls \*.dat in parameters (or commands) , Math calculations `$((1+5*6))`, parentheses `()` , quotes `'`, double quotes`"`
* This shell does NOT support pipes `|`, background processes `&`.

### Allowed functions: 
-   `access` (man 2 access)
-   `chdir` (man 2 chdir)
-   `close` (man 2 close)
-   `closedir` (man 3 closedir)
-   `execve` (man 2 execve)
-   `exit` (man 3 exit)
-   `_exit` (man 2 _exit)
-   `fflush` (man 3 fflush)
-   `fork` (man 2 fork)
-   `free` (man 3 free)
-   `getcwd` (man 3 getcwd)
-   `getline` (man 3 getline)
-   `getpid` (man 2 getpid)
-   `isatty` (man 3 isatty)
-   `kill` (man 2 kill)
-   `malloc` (man 3 malloc)
-   `open` (man 2 open)
-   `opendir` (man 3 opendir)
-   `perror` (man 3 perror)
-   `read` (man 2 read)
-   `readdir` (man 3 readdir)
-   `signal` (man 2 signal)
-   `stat` (__xstat) (man 2 stat)
-   `lstat` (__lxstat) (man 2 lstat)
-   `fstat` (__fxstat) (man 2 fstat)
-   `strtok` (man 3 strtok)
-   `wait` (man 2 wait)
-   `waitpid` (man 2 waitpid)
-   `wait3` (man 2 wait3)
-   `wait4` (man 2 wait4)
-   `write` (man 2 write)

## Process Description

The next steps are a brief description about how the shell works:

1. First, the parent process is created when the user run the program.
2. Then, the `isatty()` function using `STDIN_FILENO` file descriptor -fd- to tests if there is an open file descriptor referring to a terminal. If `isatty()` returns 1, the prompt is showed using `write()` with `STDOUT_FILENO` as fd and waits for an input user command line.
3. When the user types a command, `getline()` function reads an entire line from the stream and `strtok()` function breaks the inputted command into a sequence of non-empty tokens.
4. Next, it creates a separate child process suing `fork()` that performs the inputted command. Unless otherwise is specified, the parent process waits for the child to exit before continuing.
5. After tokening the command, `execve()` function brings and executes it, the it frees all allocated memory with `free()`.
6. Finally, the program returns to main process: prints the prompt, and waits for another user input.
<p align="center">
  <img  style="width: 100%; height: 900px"  src="https://user-images.githubusercontent.com/47532674/79399623-79bd2300-7f49-11ea-82b6-7d4f7576318d.png">
</p>




## Basic beggining

To run this shell with its respective commands its necessary to clone this reposotory in your terminal. Do it like this:
- HTTPS:

```c
git clone https://github.com/Parsankamusa/simple_shell.git
```

- SSH:

```
git clone git@github.com:Parsankamusa/simple_shell.git
```

## Compiling, Debugging and Runing

- All of your and our programs and functions will be compiled with `gcc 4.8.4` using the flags `-Wall` `-Werror` `-Wextra` and `-pedantic`

- To **compile** your functions use: `

```
gcc -Wall -Wextra -Werror -pedantic -Wno-format -g *.c -o hsh
```
- If you want to **debugging** the shell, use valgrind:
```
valgrind --leak-check=full ./hsh
```
- Or just `Run` and try this shell using:
```
./hsh
```

## Examples

Here are shown some examples of the usage of the Shell:

- ls

```shell
$ ls
AUTHORS              dict_pack_1.c       free_pack_1.c        list_pack_1.c  str_pack_2.c
builtin_alias_cmd.c  dict_pack_2.c       free_pack_2.c        list_pack_2.c  str_pack_3.c
builtin_cd_cmd.c     eprint_1.c          get_curr_cmd.c       num_pack.c     strtok.c
builtin_env_cmd.c    eprint_2.c          getline.c            print.c        tokenize.c
builtin_exit_cmd.c   execute_cmd.c       handle_signals.c     README.md      validate_input_line.c
check_file.c         expansion.c         hsh                  shell.c
commands.txt         find_builtin_cmd.c  hsh.c                shell.h
dict_management.c    find_program.c      init_program_info.c  str_pack_1.c

```

```shell
$ /bin/ls
AUTHORS              dict_pack_1.c       free_pack_1.c        list_pack_1.c  str_pack_2.c
builtin_alias_cmd.c  dict_pack_2.c       free_pack_2.c        list_pack_2.c  str_pack_3.c
builtin_cd_cmd.c     eprint_1.c          get_curr_cmd.c       num_pack.c     strtok.c
builtin_env_cmd.c    eprint_2.c          getline.c            print.c        tokenize.c
builtin_exit_cmd.c   execute_cmd.c       handle_signals.c     README.md      validate_input_line.c
check_file.c         expansion.c         hsh                  shell.c
commands.txt         find_builtin_cmd.c  hsh.c                shell.h
dict_management.c    find_program.c      init_program_info.c  str_pack_1.c
```

```shell
$ ls -lat
total 220
-rw-rw-r--  1 youssef-samuel youssef-samuel  8537 فبر  5 10:33 README.md
drwxr-xr-x 68 youssef-samuel youssef-samuel 12288 فبر  3 20:10 ..
drwxrwxr-x  8 youssef-samuel youssef-samuel  4096 ينا 24 18:41 .git
-rw-rw-r--  1 youssef-samuel youssef-samuel   487 ينا 23 17:11 getline.c
-rwxrwxr-x  1 youssef-samuel youssef-samuel 42752 ينا 21 19:01 hsh
drwxrwxr-x  3 youssef-samuel youssef-samuel  4096 ينا 21 19:01 .
-rw-rw-r--  1 youssef-samuel youssef-samuel  6845 ينا 21 13:41 shell.h
...
```
- pwd

```shell
$ pwd
/home/vagrant/HOLBERTON/simple_shell_project
```
- echo

```shell
$ echo Hello World
Hello World
```
- `Ctrl+D`  and  `Ctrl+C` 

```shell
$ ^C
$ 
vagrant@vagrant-ubuntu-trusty-64:~/HOLBERTON/simple_shell_project$ 
```
Note that in the second line the `Ctrl+D`  is typed
## Contributions

Contributions to the Shell are welcome! Fork the repository, make your changes, and submit a pull request. Please follow the existing code style and conventions.

## Known Bugs
Currently no known bugs. 🤝 Feel free to check the [issues page](../../issues/).

## Show your Support

Give me a ⭐️ if you like this project!

## Authors &copy;
- Youssef Samuel Kamal - [YoussefKamal098](https://github.com/YoussefKamal098)