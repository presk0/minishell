/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkieffer <nkieffer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 16:20:59 by nidionis          #+#    #+#             */
/*   Updated: 2024/12/17 17:02:12 by nkieffer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	clean_exit(t_list **gc_addr)
{
	t_list  *tmp;
	t_list  *gc;

	gc = *gc_addr;
	while (gc)
	{
		tmp = gc->next;
		ft_lstdelone(gc, free);
		gc = tmp;
	}
}

void	*gc_append(t_list **gc_addr, void *ptr)
{
	t_list	*new_garbage;

	new_garbage = ft_lstnew(ptr);
	if (!new_garbage)
		clean_exit(gc_addr);
	ft_lstadd_back(gc_addr, new_garbage);
	return (ptr);
}

void	*gc_malloc(t_list **gc_addr, size_t count, size_t size)
{
	void	*ptr;

	if (size)
		if (size * count / size != count)
			return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
	 return (NULL);
	gc_append(gc_addr, ptr);
	return (ptr);
}

void gc_free_item(t_list **gc_addr, void *ptr)
{
	t_list *gc;
	t_list *prev;

	gc = *gc_addr;
	prev = NULL;
	while (gc)
	{
		if (gc->content == ptr)
		{
			if (prev)
				prev->next = gc->next;
			else
				*gc_addr = gc->next;
			ft_lstdelone(gc, free);
			break;
		}
		prev = gc;
		gc = gc->next;
	}
}

/*
#include <stdio.h>
#include <stdlib.h>
#include "libgc.h" // Include your header file with function declarations
#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Include this for SIZE_MAX

int main() {

	t_list *gc = NULL; // Initialize garbage collector list


	// Test clean_exit with an empty list

	ntf("Testing clean_exit with an empty list...\n");

	clean_exit(&gc); // Should not crash


	// Test gc_calloc with zero size

	printf("Testing gc_calloc with zero size...\n");

	void *ptr1 = gc_calloc(&gc, 0, 10);

	if (ptr1 == NULL) {

		printf("Passed: gc_calloc returned NULL for zero size.\n");

	}


	// Test gc_calloc with zero count

	printf("Testing gc_calloc with zero count...\n");

	void *ptr2 = gc_calloc(&gc, 10, 0);

	if (ptr2 == NULL) {

		printf("Passed: gc_calloc returned NULL for zero count.\n");

	}


	// Test gc_calloc with large values to check for overflow

	printf("Testing gc_calloc with large values...\n");

	void *ptr3 = gc_calloc(&gc, INT_MAX, INT_MAX);

	if (ptr3 == NULL) {

		printf("Passed: gc_calloc returned NULL for overflow.\n");

	}


	// Test successful allocation

	printf("Testing successful gc_calloc...\n");

	void *ptr4 = gc_calloc(&gc, 5, sizeof(int));

	if (ptr4 != NULL) {

		printf("Passed: gc_calloc allocated memory successfully.\n");

	


	// Check if memory is initialized to zero

	int *arr = (int *)ptr4;

	for (int i = 0; i < 5; i++) {

		if (arr[i] != 0) {

			printf("Failed: Memory not initialized to zero.\n");

			break;

		}

	}


	c_free_item with a non-existent pointer

	("Testing gc_free_item with a non-existent pointer...\n");

	int non_existent = 42;

	gc_free_item(&gc, &non_existent); // Should not crash


	// Test gc_free_item with the allocated pointer

	printf("Testing gc_free_item with the allocated pointer...\n");

	gc_free_item(&gc, ptr4); // Should free the allocated memory


	// Test clean_exit with a populated list

	printf("Testing clean_exit with a populated list...\n");

	clean_exit(&gc); // Should free all remaining items


	return 0;

}
*/
