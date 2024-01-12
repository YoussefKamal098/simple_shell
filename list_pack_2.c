#include "shell.h"

/**
 * shift_list - remove first node in list
 * @head: head of the list
 * Return: removed node str or NULL if head is NULL
 */

char *shift_list(list_t **head)
{
	list_t *temp;
	char *str;

	if (!head || !*head)
		return (NULL);

	temp = *head;
	*head = temp->next;
	temp->next = NULL;

	str = _strdup(temp->str);
	free_list_node(&temp);
	return (str);
}

/**
 * get_list_node_str_at_index - get_node_str_at_index
 * @head: head of the list
 * @index: index of the node
 * Return: node str at index
 */
char *get_list_node_str_at_index(list_t *head, size_t index)
{
	while (index-- && head)
		head = head->next;

	return (head ? head->str : NULL);
}

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
			list[i] = NULL;
			free_array_of_pointers(list);
			free(list);
			return (NULL);
		}

		str = _strcpy(str, node->str), list[i] = str;
	}

	list[i] = NULL;
	return (list);
}

/**
 * update_list_node_str_at_index - update_list_node_str_at_index
 * @head: head of the list
 * @str: string that will replace node string
 * @index: index of node
 * Return: 0 if success, -1 otherwise
 */

int update_list_node_str_at_index(list_t *head, char *str, size_t index)
{
	list_t *curr;

	if (!head)
		return (-1);
	curr = head;

	while (curr && index--)
		curr = curr->next;

	if (!curr)
		return (-1);

	free(curr->str);
	curr->str = _strdup(str);
	return (0);
}
