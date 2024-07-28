/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kweihman <kweihman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 13:52:24 by kweihman          #+#    #+#             */
/*   Updated: 2024/07/26 14:02:20 by kweihman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// This is an attempt to save some lines by mallocing and checking for NULL
//  in the same line.
char	*my_malloc(char **string, int len)
{
	*string = malloc(len);
	if (*string == NULL)
		return (NULL);
	return (*string);
}

// Writing a variadic function that can free given pointers and 
//  return NULL could also save some lines.