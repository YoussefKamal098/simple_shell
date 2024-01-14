#include "shell.h"

/**
 * free_curr_program_info - free the information needed each loop
 * @info: program information
 */
void free_curr_program_info(program_info_t *info)
{
	free_list(&info->curr_cmd_tokens);

	if (info->curr_cmd)
		free(info->curr_cmd);
	if (info->curr_cmd_name)
		free(info->curr_cmd_name);

	info->curr_cmd = NULL;
	info->curr_cmd_name = NULL;
}

/**
 * free_all_program_info - free all information of program
 * @info: program information
 */
void free_all_program_info(program_info_t *info)
{
	if (info->fd != STDIN_FILENO)
		if (close(info->fd))
			perror(info->name);

	free_curr_program_info(info);
	free_list(&info->next_cmds);
	free_list(&info->next_operators);
	free_dict(&info->env);
	free_dict(&info->alias);
}

/**
 * free_pointers_arr - free array of strings
 * @arr: array of strings
 */
void free_pointers_arr(char **arr)
{
	size_t i;

	if (!arr || !*arr)
		return;

	for (i = 0; arr[i]; i++)
		free(arr[i]);

	free(arr);
}

/**
 * free_list - free list
 * @head: head of the list
 */

void free_list(list_t **head)
{
	list_t *temp;

	if (!head || !*head)
		return;

	temp = *head;
	free_list(&temp->next);
	free_list_node(&temp);
	*head = NULL;
}

/**
 * free_list_node - free list node
 * @node: node of the list
 */

void free_list_node(list_t **node)
{
	list_t *temp;

	if (!node || !*node)
		return;

	temp = *node;
	free(temp->val);
	free(temp);
	*node = NULL;
}
