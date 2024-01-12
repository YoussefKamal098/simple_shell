#include "shell.h"

/**
 * dict_len - length of the dictionary
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
 * dict_push - add node to end of the dictionary
 * @head: head of the dictionary
 * @key: key of the node
 * @value: value of the node
 * Return: 0  or -1 if head is NULL or malloc failed
 */

int dict_push(dict_t **head, char *key, char *value)
{
	dict_t *node, *temp;

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
		free(node);
		return (-1);
	}

	node->value = _strdup(value);
	if (!node->value)
	{
		free(node->key), free(node);
		return (-1);
	}

	node->next = NULL;
	if (!*head)
	{
		*head = node;
		return (0);
	}

	temp = *head;
	while (temp->next)
		temp = temp->next;

	temp->next = node;
	return (0);
}

/**
 * print_dict - print strings of the dictionary with delimiter
 * @head: head of the dictionary
 * @delimeter: delimeter
 * Return: size of dictionary
 */

size_t print_dict(const dict_t *head, char *delimeter)
{
	size_t size = 0;

	while (head)
	{
		_puts(head->key);
		_puts(delimeter);
		_puts(head->value);
		_puts("\n");
		head = head->next, size++;
	}

	return (size);
}
