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

	info->curr_cmd = NULL, info->curr_cmd_name = NULL;
}

/**
 * free_all_program_info - free all information of program
 * @info: program information
 */
void free_all_program_info(program_info_t *info)
{
	if (info->file_descriptor != STDIN_FILENO)
		if (close(info->file_descriptor))
			perror(info->name);

	free_curr_program_info(info), free_list(&info->env);
}

/**
 * free_array_of_pointers - free array of pointer
 * @array: array of pointers
 */
void free_array_of_pointers(char **array)
{
	size_t i;

	if (!array || !*array)
		return;

	for (i = 0; array[i]; i++)
		free(array[i]);

	free(array);
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

	temp = *head, free_list(&temp->next);
	free(temp->str), free(temp), *head = NULL;
}

/**
 * free_list_node - free node
 * @node: node of list
 */

void free_list_node(list_t **node)
{
	list_t *temp;

	if (!node || !*node)
		return;

	temp = *node, free(temp->str), free(temp), *node = NULL;
}
