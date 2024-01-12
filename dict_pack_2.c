#include "shell.h"

/**
 * dict_to_strs - convert dictionary to pointer of strings
 * @head: head of the dictionary
 * @delimeter: concatenate key with value with it
 * Return: pointer of strings
 */
char **dict_to_strs(dict_t *head, char *delimeter)
{
	size_t len = dict_len(head), i;
	dict_t *node = head;
	char **list, *str, *temp;

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
		str = str_concat(node->key, delimeter);
		temp = str;
		str = str_concat(str, node->value);
		free(temp);

		if (!str)
		{
			errno = ENOMEM, perror("Error");
			list[i] = NULL;
			free_array_of_pointers(list);
			free(list);
			return (NULL);
		}

		list[i] = str;
	}

	list[i] = NULL;
	return (list);
}

/**
 * remove_dict_node_at_index - remove dictionary node at index
 * @head: head of the dictionary
 * @index: index of the node
 * Return: 1 if success
 * -1 if head is NULL or index greater or equal to list len
 */
int remove_dict_node_at_index(dict_t **head, size_t index)
{
	dict_t *curr, *pre;
	size_t i = 0;

	if (!head || !*head)
		return (-1);

	curr = *head;
	if (!index)
	{
		*head = curr->next;
		free_dict_node(&curr);
		return (1);
	}

	while (curr)
	{
		if (i == index)
		{
			pre->next = curr->next;
			free_dict_node(&curr);
			return (1);
		}
		i++, pre = curr, curr = curr->next;
	}

	return (-1);
}

/**
 * dict_search - search in dictionary for prefix str
 * @head: head of the list
 * @key: key of node
 * Return: index of node or -1 if no node string with prefix
 */
int dict_search(dict_t *head, char *key)
{
	dict_t *curr;
	size_t i = 0;

	if (!head)
		return (-1);

	curr = head;
	while (curr)
	{
		if (!_strcmp(curr->key, key))
			return (i);

		curr = curr->next;
		i++;
	}

	return (-1);
}

/**
 *  update_dict_node_value_at_index - update dictionary node value at index
 * @head: head of the dictionary
 * @value: value to to be replaced with node value
 * @index: index of node
 * Return: 0 if success, -1 otherwise
 */
int update_dict_node_value_at_index(dict_t *head, char *value, size_t index)
{
	dict_t *curr;

	if (!head)
		return (-1);
	curr = head;

	while (curr && index--)
		curr = curr->next;

	if (!curr)
		return (-1);

	free(curr->value);
	curr->value = _strdup(value);
	return (0);
}

/**
 * get_dict_node_value_at_index - get dictionary node value at index
 * @head: head of the dictionary
 * @index: index of the node
 * Return: node value at index
 */
char *get_dict_node_value_at_index(dict_t *head, size_t index)
{
	while (index-- && head)
		head = head->next;

	return (head ? head->value : NULL);
}
