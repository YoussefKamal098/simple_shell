#include "shell.h"

/**
 * list_len - length of  the list
 * @head: head of the list
 * Return: length of list
 */

size_t list_len(const list_t *head)
{
	size_t size = 0;

	while (head)
		head = head->next, size++;

	return (size);
}

/**
 * list_push - add node to end of the list
 * @head: head of the list
 * @value: string of the node
 * Return: 0  or -1 if head is NULL or malloc failed
 */

int list_push(list_t **head, char *value)
{
	list_t *node, *curr;

	if (!head)
		return (-1);

	node = (list_t *)malloc(sizeof(list_t));
	if (!node)
	{
		errno = ENOMEM, perror("Error");
		return (-1);
	}

	node->value = _strdup(value);
	if (!node->value)
	{
		errno = ENOMEM, perror("Error");
		free(node);
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
 * print_list - print strings of the list with delimiter
 * @head: head of the list
 * @delimeter: delimeter
 * Return: length of list
 */

size_t print_list(const list_t *head, char *delimeter)
{
	size_t size = 0;

	while (head)
	{
		_puts(head->value);
		_puts(delimeter);
		head = head->next, size++;
	}

	return (size);
}
