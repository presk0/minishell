/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nkieffer <nkieffer@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/02/24 15:51:11 by supersko		  #+#	#+#			 */
/*   Updated: 2025/01/23 16:36:03 by nidionis         ###   ########.fr       */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (!s1 || !s2)
		return (INT_MIN);
	if (n)
	{
		while (--n && *s1 && *s1 == *s2)
		{
			s1++;
			s2++;
		}
		return ((unsigned char) *s1 - (unsigned char) *s2);
	}
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	i = 0;
	while (s1[i] == s2[i] && s1[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strcmp_until(const char *s1, const char *s2, char c)
{
	size_t	i;

	if (!s1)
		return (-1);
	if (!s2)
		return (1);
	i = 0;
	while (s1[i] != '\0' && s1[i] != c && s2[i] != c && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i] || (s1[i] == c && s2[i] == '\0')
		|| (s2[i] == c && s1[i] == '\0'))
		return (0);
	if (s1[i] == c)
		return (-77777);
	if (s2[i] == c)
		return (77777);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
#include <stdio.h>
#include <string.h>
int main(int argc, char **argv)
{
	printf("my_func: %i\n", ft_strncmp(argv[1], argv[2], atoi(argv[3])));
	printf("original: %i\n", strncmp(argv[1], argv[2], atoi(argv[3])));
}
*/
