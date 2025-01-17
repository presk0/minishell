/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   gc.c											   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nidionis <nidionis@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/04 16:20:59 by nidionis		  #+#	#+#			 */
/*   Updated: 2025/01/03 16:59:01 by nidionis		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include <libft.h>

void	gc_free_all(t_list **gc_addr)
{
	t_list	*tmp;
	t_list	*gc;

	if (!gc_addr)
		return ;
	gc = *gc_addr;
	while (gc)
	{
		tmp = gc->next;
		ft_lstdelone(gc, free);
		gc = tmp;
	}
	*gc_addr = NULL;
}

/* use carefully:
 * returns NULL if lstnew crashed
 * (and if ptr == NULL)
 */
void	*gc_append(t_list **gc_addr, void *ptr)
{
	t_list	*new_garbage;

	if (!ptr)
		return (NULL);
	new_garbage = ft_lstnew(ptr);
	if (!new_garbage)
	{
		free(ptr);
		ptr = NULL;
		gc_free_all(gc_addr);
	}
	else
		ft_lstadd_back(gc_addr, new_garbage);
	return (ptr);
}

void	*gc_malloc(t_list **gc_addr, size_t count, size_t size)
{
	void	*ptr;
	void	*node;

	if (size)
		if (size * count / size != count)
			return (NULL);
	ptr = ft_calloc(count, size);
	if (ptr == NULL)
	{
		write(2, "[gc_malloc 1] failed to malloc\n", 32);
		gc_free_all(gc_addr);
		return (NULL);
	}
	node = gc_append(gc_addr, ptr);
	if (!node)
	{
		write(2, "[gc_malloc 1] failed to malloc\n", 32);
		gc_free_all(gc_addr);
		return (NULL);
	}
	return (ptr);
}

char	*gc_strdup(t_list **gc_addr, char *str)
{
	char	*ret;
	size_t	len;

	ret = NULL;
	len = ft_strlen(str);
	if (len)
	{
		ret = gc_malloc(gc_addr, ++len, 1);
		if (!ret)
			gc_free_all(gc_addr);
		else
			ft_strlcpy(ret, str, len);
	}
	return (ret);
}

void gc_free_item(t_list **gc_addr, void *ptr)
{
	t_list *gc;
	t_list *prev;

	if (!gc_addr || !*gc_addr)
		return;

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
			return ;
		}
		prev = gc;
		gc = gc->next;
	}
}


void print_gc(t_list *gc)
{
	printf("Garbage Collector List:\n");
	while (gc)
	{
		printf("  Node: %p, Content: %p\n", gc, gc->content);
		gc = gc->next;
	}
}
