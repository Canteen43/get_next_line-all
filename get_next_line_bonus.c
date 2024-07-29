/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kweihman <kweihman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 13:56:02 by kweihman          #+#    #+#             */
/*   Updated: 2024/07/29 12:26:14 by kweihman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*reststring[1024];
	int			bytes_read;

	if (BUFFER_SIZE < 1 || fd < 0 || fd > 1023)
		return (NULL);
	if (reststring[fd] == NULL)
		reststring[fd] = set_null_character(reststring[fd]);
	if (reststring[fd] == NULL)
		return (NULL);
	bytes_read = BUFFER_SIZE;
	while (includes_newline(reststring[fd]) == 0 && bytes_read == BUFFER_SIZE)
	{
		reststring[fd] = keep_reading(reststring[fd], fd, &bytes_read);
		if (reststring[fd] == NULL)
			return (NULL);
	}
	if (includes_newline(reststring[fd]) == 1)
		return (return_next_line(&reststring[fd]));
	if (*reststring[fd] != '\0')
		return (return_last_line(&reststring[fd]));
	free(reststring[fd]);
	reststring[fd] = NULL;
	return (NULL);
}

// This function is needed because my function rely on
//  the reststring being a valid pointer. It sets the reststring
//  from NULL to pointer to \0.
char	*set_null_character(char *p)
{
	p = malloc(1);
	if (p == NULL)
		return (NULL);
	*p = '\0';
	return (p);
}

// This function returns the pointer to the last line read while
//  setting the reststring to NULL.
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

// This function returns the next line while also handling the
//  creation of the new_reststring that does not include that next line.
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
