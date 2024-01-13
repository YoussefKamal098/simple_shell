#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
/* for perror */
#include <unistd.h>
/* for fork, execve, getpid, access, close, read, write, isatty */
#include <stdlib.h>
/* for malloc ,free */
/* #include <stdarg.h> */
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

#define PROGRAM_INFO_INIT                                                 \
	{                                                         \
		NULL, NULL, NULL, 0, 0, NULL, NULL, NULL, \
	}

#define CMD_NOT_FOUND 127
#define PERMISSION_DENIED 126
#define NO_SUCH_FILE_OR_DIR ENOENT
#define ILLEGAL_NUMBER 222
#define CANNOT_CD_TO 333

/**
 * struct list - list of strings
 * @value: string of the node
 * @next: next node
 */
typedef struct list
{
	char *value;
	struct list *next;
} list_t;

/**
 * struct dict - list of key values variables
 * @key: key of node
 * @value: value of node
 * @next: next node
 */
typedef struct dict
{
	char *key;
	char *value;
	struct dict *next;
} dict_t;

/**
 * struct program_info - struct for information of the program
 * @name: the name of the program
 * @curr_cmd: current command to by executed
 * @curr_cmd_name: pointer to the first command typed by the user
 * @exec_counter: number of executed command
 * @fd: file descriptor to input file
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
	int fd;
	list_t *curr_cmd_tokens;
	dict_t *env;
	dict_t *alias;
} program_info_t;

/**
 * struct builtin_cmd - struct for builtin command
 * @name: command name
 * @execute_func: function that execute command
 */
typedef struct builtin_cmd
{
	char *name;
	int (*execute_func)(program_info_t *info);
} builtin_cmd_t;

/* init_program_info.c */
void init_program_info(program_info_t *info, int ac, char **av, char **env);

/* hsh.c */
void hsh(program_info_t *info, char *prompt);

/* execute_cmd.c */
int execute_cmd(program_info_t *info);

/* _strtok.c */
char *_strtok(char *value, char *delimiters);

/* tokenize.c */
void tokenize_curr_cmd(program_info_t *info);
char **tokenize_env_path(program_info_t *info);
void tokenize_buffer(char *buffer, list_t **next_cmds, list_t **next_ops);

/* validate_buffer.c  */
int check_for_syntax_err(program_info_t *info, char *buffer);
int check_for_unsupported_features(program_info_t *info, char *buffer);

/* dict_management.c */
char *get_dict_key(dict_t *head, char *key);
int set_dict_key(dict_t **head, char *key, char *value);
int unset_dict_key(dict_t **head, char *key);

/* find_builtin_cmd.c */
int (*find_builtin_cmd(program_info_t *info))(program_info_t *info);

/* builtin_exit_cmd.c */
int builtin_exit_cmd(program_info_t *info);

/* builtin_env_cmd.c */
int builtin_env_cmd(program_info_t *info);
int builtin_setenv_cmd(program_info_t *info);
int builtin_unsetenv_cmd(program_info_t *info);

/* builtin_cmd_command.c  */
int builtin_cd_cmd(program_info_t *info);

/* find_program.c */
int find_program(program_info_t *info);

/* check_file.c */
int check_file(char *path);

/* getline.c */
int _getline(program_info_t *info);
int is_and_operator(char *buffer, int i);
int is_or_operator(char *buffer, int i);
int is_double_semicolon(char *buffer, int i);

/* expansion.c */
void expand_vars(program_info_t *info);

/* free_pack_1.c */
void free_curr_program_info(program_info_t *info);
void free_all_program_info(program_info_t *info);
void free_array_of_pointers(char **array);
void free_list(list_t **head);
void free_list_node(list_t **node);

/* free_pack_2 */
void free_dict(dict_t **head);
void free_dict_node(dict_t **node);

/* str_pack_1.c */
size_t _strlen(char *value);
char *_strcpy(char *dest, char *src);
char *strconcat(char *str1, char *str2);
int _strcmp(char *str1, char *str2);
char *_strdup(char *value);

/* str_pack_2.c */
size_t count_digit(size_t num);
int _isdigit(char c);

/* str_pack_3.c */
/* char *str_n_concat(size_t n, ...) */
int is_space(char *value);
int is_empty_str(char *value);

/* print.c */
int _puts(char *value);

/* print_error_1.c */
int _eputs(char *value);
void print_stderr_msg(program_info_t *info, int code);
void print_err_msg(program_info_t *info, char *msg);
void print_prefix_err_msg(program_info_t *info);
void print_cannot_cd_to_err_msg(program_info_t *info);

/* print_error_2.c */
void print_open_file_err_msg(program_info_t *info, char *file_name);
void print_illegal_number_err_msg(program_info_t *info);
void print_syntax_err_msg(program_info_t *info, char *error);
void print_unsupported_feature_err_msg(program_info_t *info, char *feature);
void print_no_such_file_or_dir_err_msg(program_info_t *info);

/* numbers_pack.c */
char *_itoa(long int num, int is_unsigned);
long int _atoi(char *value);
int is_pos_int(char *value);

/* list_pack_1.c */
size_t list_len(const list_t *head);
size_t print_list(const list_t *head, char *delimeter);
int list_push(list_t **head, char *value);

/* list_pack_2.c */
char *shift_list(list_t **head);
char *get_list_node_value_at_index(list_t *head, size_t index);
char **list_to_strs(list_t *head);
int update_list_node_value_at_index(list_t *head, char *value, size_t index);

/* dict_pack_1.c */
size_t dict_len(const dict_t *head);
size_t print_dict(const dict_t *head, char *delimeter);
int dict_push(dict_t **head, char *key, char *value);

/* dict_pack_2.c */
int remove_dict_node_at_index(dict_t **head, size_t index);
int dict_search(dict_t *head, char *key);
int update_dict_node_value_at_index(dict_t *head, char *value, size_t index);
char *get_dict_node_value_at_index(dict_t *head, size_t index);
char **dict_to_strs(dict_t *head, char *delimeter);

#endif /* SHELL_H */
