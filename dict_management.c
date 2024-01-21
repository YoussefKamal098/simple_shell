#include "shell.h"

/**
 * get_dict_key - get the value of the variable
 * @head: head of dictionary
 * @key: the key of variable
 * Return: a pointer to the variable
 * or NULL if it doesn't exist
 */
char *get_dict_key(dict_t *head, char *key)
{
	int i;

	if (!key)
		return (NULL);

	i = dict_search(head, key);
	if (i != -1)
		return (get_dict_node_value_at_index(head, i));

	return (NULL);
}

/**
 * set_dict_key - overwrite the value of the variable
 * or create it if it doesn't exist.
 * @head: head of dictionary
 * @key: the key of variable
 * @value: value to assigned to variable key
 * Return: 0 if success or  -1 if any of the parameters are NULL
 */
int set_dict_key(dict_t **head, char *key, char *value)
{
	int i;

	if (!key || !value)
		return (-1);

	i = dict_search(*head, key);
	if (i != -1)
	{
		update_dict_node_value_at_index(*head, value, i);
		return (0);
	}

	dict_push(head, key, value);
	return (0);
}

/**
 * unset_dict_key - remove a variable
 * @head: head of dictionary
 * @key: the key of variable
 * Return: 0 if the key was removed or -1 if the key doesn't  exist
 */
int unset_dict_key(dict_t **head, char *key)
{
	int i = 0;

	if (!key)
		return (-1);

	i = dict_search(*head, key);
	if (i != -1)
	{
		remove_dict_node_at_index(head, i);
		return (0);
	}

	return (-1);
}
