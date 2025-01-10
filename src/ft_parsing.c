/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_parsing.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nidionis <nidionis@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/04 16:20:59 by nidionis		  #+#	#+#			 */
/*   Updated: 2025/01/03 19:59:21 by nidionis		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

int	is_blank(char *str)
{
	while (*str)
	{
		if (!ft_strchr(WHITE_SPACE, *str))
			return (0);
		str++;
	}
	return (1);
}

char	*substr_left(t_list *gc, char *node_content, char *found)
{
	char	*ret;

	ret = ft_substr(node_content, 0, found - node_content);
	if (ret && is_blank(ret))
	{
		free(ret);
		ret = NULL;
	}
	if (ret)
	{
		if (!gc_append(&gc, ret))
		{
			write(2, "[substr_left]\n", 14);
			minishell_exit(gc);
		}
	}
	return (ret);
}

char	*substr_right(t_list *gc, char *node_content, char *found)
{
	char	*ret;

	(void)node_content;
	//while (found[0] == found[1])
	//	found++;
	found++;
	ret = ft_substr(found, 0, ft_strlen(found));
	if (ret && is_blank(ret))
	{
		free(ret);
		ret = NULL;
	}
	if (ret)
	{
		if (!gc_append(&gc, ret))
		{
			write(2, "[substr_right]\n", 14);
			minishell_exit(gc);
		}
	}
	return (ret);
}

void   split_node(t_list *gc, t_btree *root, char *sep)
{
	   char					*str;
	   char					*sep_found;
	   t_btree_content *content;

	   if (root->left || root->right)
			   return ;
	   content = root->content;
	   str = content->cmd;
	   sep_found = ft_strnstr_quotes(str, sep, ft_strlen(str));
	   if (sep_found)
	   {
			   content = gc_malloc_btree_content(gc);
			   content->cmd = substr_left(gc, str, sep_found);
			   if (content->cmd)
					   root->left = new_node(gc, content);
			   content = gc_malloc_btree_content(gc);
			   content->cmd = substr_right(gc, str, sep_found);
			   if (content->cmd)
					   root->right = new_node(gc, content);
			   content = root->content;
			   content->cmd = sep_found;
			   root->content = content;
	   }
}


void   btree_split(t_list *gc, t_btree *root, char *sep)
{
	   if (!root)
			   return ;
	   split_node(gc, root, sep);
	   if (root->left)
			   btree_split(gc, root->left, sep);
	   if (root->right)
			   btree_split(gc, root->right, sep);
}