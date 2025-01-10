/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_isascii.c									   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: supersko <ndionis@student.42mulhouse.fr>   +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/02/23 16:48:16 by supersko		  #+#	#+#			 */
/*   Updated: 2024/11/16 15:16:15 by nidionis		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
