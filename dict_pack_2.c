#include "shell.h"

/**
 * dict_to_strs - convert dictionary to array of strings
 * @head: head of the dictionary
 * @delims: concatenate key with value with it
 * Return: array of strings
 */
char **dict_to_strs(dict_t *head, char *delims)
{
	size_t len, i;
	dict_t *curr;
	char **list, *str;

	len = dict_len(head);
	if (!head || !len)
		return (NULL);

	list = (char **)malloc(sizeof(char *) * (len + 1));
	if (!list)
	{
		errno = ENOMEM, perror("Error");
		return (NULL);
	}

	for (i = 0, curr = head; curr; curr = curr->next, i++)
	{
		str = str_n_concat(3, curr->key, delims, curr->value);
		if (!str)
		{
			errno = ENOMEM, perror("Error");
			list[i] = NULL;
			free_pointers_arr(list);
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
 * @idx: index of the node
 * Return: 1 if success
 * -1 if head is NULL or index greater or equal to list length of dictionary
 */
int remove_dict_node_at_index(dict_t **head, size_t idx)
{
	dict_t *curr, *pre;
	size_t i = 0;

	if (!head || !*head)
		return (-1);

	curr = *head;
	if (!idx)
	{
		*head = curr->next;
		free_dict_node(&curr);
		return (1);
	}

	while (curr)
	{
		if (i == idx)
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
 * dict_search - search in dictionary for key
 * @head: head of the dictionary
 * @key: key of node
 * Return: index of node or -1 if no node with key
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

		curr = curr->next, i++;
	}

	return (-1);
}

/**
 *  update_dict_node_value_at_index - update dictionary node value at index
 * @head: head of the dictionary
 * @value: value to to be replaced with node value
 * @idx: index of node
 * Return: 0 if success or -1 otherwise
 */
int update_dict_node_value_at_index(dict_t *head, char *value, size_t idx)
{
	dict_t *curr;

	if (!head)
		return (-1);
	curr = head;

	while (curr && idx--)
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
 * @idx: index of the node
 * Return: node value at index or NULL if idex greater than dictionary length
 */
char *get_dict_node_value_at_index(dict_t *head, size_t idx)
{
	while (idx-- && head)
		head = head->next;

	return (head ? head->value : NULL);
}
