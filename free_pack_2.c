#include "shell.h"

/**
 * free_dict - free dictionary
 * @head: head of the dictionary
 */

void free_dict(dict_t **head)
{
	dict_t *temp;

	if (!head || !*head)
		return;

	temp = *head;
	free_dict(&temp->next);
	free_dict_node(&temp);
	*head = NULL;
}

/**
 * free_dict_node - free dictionary node
 * @node: node of dictionary
 */

void free_dict_node(dict_t **node)
{
	dict_t *temp;

	if (!node || !*node)
		return;

	temp = *node;
	free(temp->key);
	free(temp->value);
	free(temp);
	*node = NULL;
}
