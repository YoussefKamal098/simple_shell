#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
/* for perror */
#include <unistd.h>
/* for fork, execve, getpid, access, close, read, write, isatty */
#include <stdlib.h>
/* for malloc ,free */
#include <stdarg.h>
/* for, va_start, var_arg, va_end */
#include <errno.h>
/* for errno */
/* #include <sys/types.h> */
/*
*for type pid_t and size_t,
Keep in mind that including <sys/types.h> may
not always be necessary in modern C programming,
as many standard headers already include the necessary definitions.
However, it can be useful in some situations,
especially when working with low-level system programming or
dealing with specific features provided by POSIX-compliant systems.
*/
#include <sys/wait.h>
/* for wait */
#include <sys/stat.h>
/* for stat function */
#include <signal.h>
/* for signal management, sigaction function  */
#include <fcntl.h>
/* for open files, open function */

#define BUFFER_SIZE 1024
#define PROMPT "$ "

#define PROGRAM_INFO_INITIAL                                              \
	{                                                         \
		NULL, NULL, NULL, 0, 0, NULL, NULL, NULL, \
	}

#define COMMAND_NOT_FOUND 127
#define PERMISSION_DENIED 126
#define NO_SUCH_FILE_OR_DIRECTORY ENOENT
#define ILLEGAL_NUMBER 222

/**
 * struct list - list of strings
 * @str: string
 * @next: next node
 */
typedef struct list
{
	char *str;
	struct list *next;
} list_t;

/**
 * struct program_info - struct for information of the program
 * @name: the name of the program
 * @curr_cmd: current command to by executed
 * @curr_cmd_name: pointer to the first command typed by the user
 * @exec_counter: number of executed command
 * @file_descriptor: file descriptor to input file
 * @curr_cmd_tokens: list of tokenized of current command
 * @env: list of the environment variable
 * @alias: list of the program aliases.
 */
typedef struct program_info
{
	char *name;
	char *curr_cmd;
	char *curr_cmd_name;
	int exec_counter;
	int file_descriptor;
	list_t *curr_cmd_tokens;
	list_t *env;
	list_t *alias;
} program_info_t;

/**
 * struct builtin_command - struct for builtin command
 * @name: command name
 * @execute_func: function that execute command
 */
typedef struct builtin_command
{
	char *name;
	int (*execute_func)(program_info_t *info);
} builtin_command_t;

/* init_program_info.c */
void init_program_info(program_info_t *info, int ac, char **av, char **env);

/* run.c */
void run(program_info_t *info, char *prompt);

/* execute_command.c */
int execute_command(program_info_t *info);

/* _strtok.c */
char *_strtok(char *str, char *delimiters);

/* tokenize.c */
void tokenize_curr_cmd(program_info_t *info);
char **tokenize_env_path(program_info_t *info);
void tokenize_buffer(char *buffer, list_t **next_cmds, list_t **next_ops);

/* validate_buffer.c  */
int check_for_syntax_error(program_info_t *info, char *buffer);
int check_for_unsupported_features(program_info_t *info, char *buffer);

/* environ_management.c */
char *get_env_key(program_info_t *info, char *key);
int set_env_key(program_info_t *info, char *key, char *value);
int unset_env_key(program_info_t *info, char *key);
void print_env(program_info_t *info);

/* find_builtin_command.c */
int (*find_builtin_command(program_info_t *info))(program_info_t *info);

/* builtin_exit_command.c */
int builtin_exit_command(program_info_t *info);

/* builtin_env_command.c */
int builtin_env_command(program_info_t *info);
int builtin_set_env(program_info_t *info);
int builtin_unset_env(program_info_t *info);

/* find_program.c */
int find_program(program_info_t *info);

/* check_file.c */
int check_file(char *path);

/* getline.c */
int _getline(program_info_t *info);
int is_and_operator(char *buffer, int i);
int is_or_operator(char *buffer, int i);
int is_double_semicolon_operator(char *buffer, int i);

/* expansion.c */
void expand_variables(program_info_t *info);

/* free.c */
void free_curr_program_info(program_info_t *info);
void free_all_program_info(program_info_t *info);
void free_array_of_pointers(char **array);
void free_list(list_t **head);
void free_list_node(list_t **node);

/* str_pack_1.c */
size_t _strlen(char *str);
char *_strcpy(char *dest, char *src);
char *str_concat(char *str1, char *str2);
int _strcmp(char *str1, char *str2);
char *_strdup(char *str);

/* str_pack_2.c */
int is_starts_with(char *str, char *prefix);
unsigned int count_digit(unsigned long int num);
int _isdigit(char c);

/* str_pack_3.c */
char *str_n_concat(unsigned int n, ...);
int is_space(char *str);
int is_empty_str(char *str);

/* print.c */
int _puts(char *str);

/* print_error_1.c */
int _puts_error(char *str);

void print_error_msg(program_info_t *info, int code);
void print_msg(program_info_t *info, char *msg);
void print_prefix_err_msg(program_info_t *info);

/* print_error_2.c */
void print_open_file_error_msg(program_info_t *info, char *file_name);
void print_illegal_number_msg(program_info_t *info);
void print_syntax_error_msg(program_info_t *info, char *error);
void print_unsupported_feature_error_msg(program_info_t *info, char *feature);
void print_no_such_file_or_directory_error_msg(program_info_t *info);

/* numbers_pack.c */
char *_itoa(long int num, int is_unsigned);
long int _atoi(char *str);
int is_pos_integer(char *str);

/* list_pack_1.c */
size_t list_len(const list_t *head);
int list_push(list_t **head, char *str);
size_t print_list_str(const list_t *head, char *delimeter);

/* list_pack_2.c */
int remove_node_at_index(list_t **head, unsigned int index);
char *shift_list(list_t **head);
char *get_node_str_at_index(list_t *head, unsigned int index);

/* list_pack_3.c */
char **list_to_strs(list_t *head);
int update_node_str_at_index(list_t *head, char *str, size_t index);
int list_search(list_t *head, char *prefix);

#endif /* SHELL_H */
