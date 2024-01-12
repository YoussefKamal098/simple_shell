#include "shell.h"

/**
 * list_to_strs - convert list to pointer of strings
 * @head: head of the list
 * Return: pointer of strings
 */

char **list_to_strs(list_t *head)
{
	size_t len = list_len(head), i;
	list_t *node = head;
	char **list, *str;

	if (!head || !len)
		return (NULL);

	list = malloc(sizeof(char *) * (len + 1));
	if (!list)
	{
		errno = ENOMEM, perror("Error");
		return (NULL);
	}

	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			errno = ENOMEM, perror("Error");
			list[i] = NULL, free_array_of_pointers(list), free(list);
			return (NULL);
		}

		str = _strcpy(str, node->str), list[i] = str;
	}

	list[i] = NULL;
	return (list);
}

/**
 * update_node_str_at_index - update_node_str_at_index
 * @head: head of the list
 * @str: string that will replace node string
 * @index: index of node
 * Return: 0 if success, -1 otherwise
 */

int update_node_str_at_index(list_t *head, char *str, size_t index)
{
	list_t *curr;

	if (!head)
		return (-1);
	curr = head;

	while (curr && index--)
		curr = curr->next;

	if (!curr)
		return (-1);

	free(curr->str), curr->str = _strdup(str);
	return (0);
}

/**
 * list_search - search in list for prefix str
 * @head: head of the list
 * @prefix: prefix of node string
 * Return: index of node or -1 if no node string with prefix
 */

int list_search(list_t *head, char *prefix)
{
	list_t *curr;
	size_t i = 0;

	if (!head)
		return (-1);

	curr = head;
	while (curr)
	{
		if (is_starts_with(curr->str, prefix))
			return (i);

		curr = curr->next;
		i++;
	}

	return (-1);
}
