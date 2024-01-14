#include "shell.h"

/**
 * dict_len - get size of the dictionary
 * @head: head of the dictionary
 * Return: size of dictionary
 */

size_t dict_len(const dict_t *head)
{
	size_t size = 0;

	while (head)
		head = head->next, size++;

	return (size);
}

/**
 * dict_push - add node to the dictionary
 * @head: head of the dictionary
 * @key: key of the node
 * @val: value of the node
 * Return: 0 if success or -1 if head is NULL or malloc failed
 */

int dict_push(dict_t **head, char *key, char *val)
{
	dict_t *node, *curr;

	if (!head)
		return (-1);

	node = (dict_t *)malloc(sizeof(dict_t));
	if (!node)
	{
		errno = ENOMEM, perror("Error");
		return (-1);
	}

	node->key = _strdup(key);
	if (!node->key)
	{
		errno = ENOMEM, perror("Error"), free(node);
		return (-1);
	}

	node->val = _strdup(val);
	if (!node->val)
	{
		errno = ENOMEM, perror("Error");
		free(node->key), free(node);
		return (-1);
	}

	node->next = NULL;
	if (!*head)
	{
		*head = node;
		return (0);
	}

	curr = *head;
	while (curr->next)
		curr = curr->next;

	curr->next = node;
	return (0);
}

/**
 * print_dict - print key value of the dictionary
 * @head: head of the dictionary
 * @delims: delimiters
 * @val_surround: surrounding variable value with specific string
 * Return: size of dictionary
 */

size_t print_dict(const dict_t *head, char *delims, char *val_surround)
{
	size_t size = 0;

	while (head)
	{
		_puts(head->key);
		_puts(delims);
		_puts(val_surround);
		_puts(head->val);
		_puts(val_surround);
		_puts("\n");
		head = head->next, size++;
	}

	return (size);
}
