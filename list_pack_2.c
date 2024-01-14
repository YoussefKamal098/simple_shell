#include "shell.h"

/**
 * shift_list - remove first node in the list
 * @head: head of the list
 * Return: removed node value or NULL if head is NULL
 */

char *shift_list(list_t **head)
{
	list_t *temp;
	char *val;

	if (!head || !*head)
		return (NULL);

	temp = *head;
	*head = temp->next;
	temp->next = NULL;

	val = _strdup(temp->val);
	free_list_node(&temp);
	return (val);
}

/**
 * get_list_node_value_at_index - get node value at index
 * @head: head of the list
 * @idx: index of the node
 * Return: node value at index
 */
char *get_list_node_value_at_index(list_t *head, size_t idx)
{
	while (idx-- && head)
		head = head->next;

	return (head ? head->val : NULL);
}

/**
 * list_to_strs - convert list to array of strings
 * @head: head of the list
 * Return: array of strings
 */

char **list_to_strs(list_t *head)
{
	size_t len, i;
	list_t *node = head;
	char **list, *val;

	len = list_len(head);
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
		val = malloc(_strlen(node->val) + 1);
		if (!val)
		{
			errno = ENOMEM, perror("Error");
			list[i] = NULL;
			free_pointers_arr(list);
			free(list);
			return (NULL);
		}

		val = _strcpy(val, node->val), list[i] = val;
	}

	list[i] = NULL;
	return (list);
}

/**
 * update_list_node_value_at_index - update_list_node_value_at_index
 * @head: head of the list
 * @val: value that will be replaced node value
 * @idx: index of node
 * Return: 0 if success or -1 otherwise
 */

int update_list_node_value_at_index(list_t *head, char *val, size_t idx)
{
	list_t *curr;

	if (!head)
		return (-1);
	curr = head;

	while (curr && idx--)
		curr = curr->next;

	if (!curr)
		return (-1);

	free(curr->val);
	curr->val = _strdup(val);
	return (0);
}
