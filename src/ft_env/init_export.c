/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   init_export.c                                      :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nkieffer <nkieffer@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/07/11 12:10:39 by nkieffer		  #+#	#+#			 */
/*   Updated: 2025/01/16 12:11:17 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "minishell.h"

t_export	*init_export(t_list *gc, char *env[])
{
	t_export	*my_export;
	t_export	*node;
	int			i;

	my_export = export_new_node(gc, env[0]);
	node = export_new_node(gc, env[1]);
	my_export->next = node;
	i = 2;
	while (env[i] != NULL)
	{
		if (env[i][0] != '_')
		{
			node->next = export_new_node(gc, env[i]);
			node = node->next;
		}
		i++;
	}
	if (i == 3)
		node->next = export_new_deminode(gc, "OLDPWD");
	sort_export(gc, &my_export);
	return (my_export);
}

t_export	*export_new_node(t_list *gc, char *content)
{
	t_export	*node;
	int			size;
	int			i;

	if (ft_strchr(content, '=') == NULL)
		return (export_new_deminode(gc, content));
	node = malloc(sizeof(t_export));
	if (!node)
		return (NULL);
	size = ft_strlen(content) + 2;
	i = -1;
	node->line = malloc((size + 1) * sizeof(char));
	node->line[size] = '\0';
	node->line[size - 1] = '"';
	while (content[++i] != '=')
		node->line[i] = content[i];
	node->line[i] = '=';
	node->line[i + 1] = '"';
	while (content[++i] != '\0')
		node->line[i + 1] = content[i];
	node->line = ft_strjoin_free2("declare -x ", node->line);
	node->next = NULL;
	return (node);
}

t_export	*export_new_deminode(t_list *gc, char *content)
{
	t_export	*node;
	int			size;
	int			i;

	(void)gc;
	node = malloc(sizeof(t_export));
	if (!node)
		return (NULL);
	size = ft_strlen(content);
	i = -1;
	node->line = malloc((size + 1) * sizeof(char));
	node->line[size] = '\0';
	while (content[++i] != '\0')
		node->line[i] = content[i];
	node->line = ft_strjoin_free2("declare -x ", node->line);
	node->next = NULL;
	return (node);
}
