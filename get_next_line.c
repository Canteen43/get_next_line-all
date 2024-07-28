/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kweihman <kweihman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:56:02 by kweihman          #+#    #+#             */
/*   Updated: 2024/07/26 14:05:33 by kweihman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*reststring;
	int			bytes_read;

	if (BUFFER_SIZE < 1)
		return (NULL);
	if (reststring == NULL)
		reststring = set_null_character(reststring);
	if (reststring == NULL)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	while (includes_newline(reststring) == 0 && bytes_read == BUFFER_SIZE)
	{
		reststring = keep_reading(reststring, fd, &bytes_read);
		if (reststring == NULL)
			return (NULL);
	}
	if (includes_newline(reststring) == 1)
		return (return_next_line(&reststring));
	if (*reststring != '\0')
		return (return_last_line(&reststring));
	free(reststring);
	reststring = NULL;
	return (NULL);
}

char	*set_null_character(char *p)
{
	p = malloc(1);
	if (p == NULL)
		return (NULL);
	*p = '\0';
	return (p);
}

char	*return_last_line(char **p_reststring)
{
	char	*name;

	name = *p_reststring;
	*p_reststring = NULL;
	return (name);
}

//This function takes a string and adds a newly read buffer to its end.
char	*keep_reading(char *reststring, int fd, int *p_bytes_read)
{
	int		len;
	char	*new_reststring;

	len = length(reststring, 0, 0, 0);
	new_reststring = malloc(len + BUFFER_SIZE + 1);
	if (new_reststring == NULL)
	{
		free(reststring);
		return (NULL);
	}
	copy(reststring, new_reststring, 0, 0);
	free(reststring);
	*p_bytes_read = read(fd, (new_reststring + len), BUFFER_SIZE);
	if (*p_bytes_read == -1)
	{
		free(new_reststring);
		return (NULL);
	}
	*(new_reststring + len + *p_bytes_read) = '\0';
	return (new_reststring);
}

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

char	*return_next_line(char **p_reststring)
{
	char	*next_line;
	char	*new_reststring;

	next_line = malloc(length(*p_reststring, 0, '\n', 1) + 1);
	if (next_line == NULL)
	{
		free(*p_reststring);
		return (NULL);
	}
	copy(*p_reststring, next_line, 0, '\n');
	new_reststring = malloc(length(*p_reststring, '\n', 0, 0) + 1);
	if (new_reststring == NULL)
	{
		free(*p_reststring);
		free(next_line);
		return (NULL);
	}
	copy(*p_reststring, new_reststring, '\n', 0);
	free(*p_reststring);
	*p_reststring = new_reststring;
	return (next_line);
}
