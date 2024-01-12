#include "shell.h"

/**
 * remove_node_at_index - remove_node_at_index
 * @head: head of the list
 * @index: index of the node
 * Return: 1 if success
 * -1 if head is NULL or index greater or equal to list len
 */

int remove_node_at_index(list_t **head, unsigned int index)
{
	list_t *curr, *pre;
	unsigned int i = 0;

	if (!head || !*head)
		return (-1);

	curr = *head;
	if (!index)
	{
		*head = curr->next, free(curr->str), free(curr);
		return (1);
	}

	while (curr)
	{
		if (i == index)
		{
			pre->next = curr->next, free(curr->str), free(curr);
			return (1);
		}
		i++, pre = curr, curr = curr->next;
	}

	return (-1);
}

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
 * get_node_str_at_index - get_node_str_at_index
 * @head: head of the list
 * @index: index of the node
 * Return: node str at index
 */

char *get_node_str_at_index(list_t *head, unsigned int index)
{
	while (index-- && head)
		head = head->next;

	return (head ? head->str : NULL);
}
