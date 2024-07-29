/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kweihman <kweihman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:00:02 by kweihman          #+#    #+#             */
/*   Updated: 2024/07/29 12:21:14 by kweihman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

//Returns the length of a given string.
// If skip_until is not 0, it will only start counting characters after 
//  skip_until is encountered
// end_char sets a character where the function stops counting
// If incl is non-zero it will include the end character in the count. 
//  If it is 0, it will exclude the end character
int	length(char *str, int skip_until, int end_char, int incl)
{
	int	len;

	len = 0;
	if (skip_until != 0)
		while (*str++ != skip_until)
			;
	while (*str)
	{
		if (*str == end_char)
			break ;
		len++;
		str++;
	}
	if (incl != 0)
		len++;
	return (len);
}

// Checks if given string includes a '\n' character.
// Returns 1 (true) or 0 (false).
int	includes_newline(char *reststring)
{
	while (*reststring != '\0')
	{
		if (*reststring == '\n')
			return (1);
		reststring++;
	}
	return (0);
}

//Copies from one string to another.
// If skip_until is not 0, it will only start copying characters after 
//  skip_until is encountered.
// End_char sets a character where the function stops copying.
// It will always copy the end character as well.
void	copy(char *src, char *dst, int skip_until, int end_char)
{
	if (skip_until != 0)
		while (*src++ != skip_until)
			;
	while (*src != end_char)
		*dst++ = *src++;
	*dst = end_char;
	if (end_char != 0)
		*++dst = '\0';
}
