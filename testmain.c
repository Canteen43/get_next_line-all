/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testmain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kweihman <kweihman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:27:32 by kweihman          #+#    #+#             */
/*   Updated: 2024/07/29 12:22:37 by kweihman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

void	write_string(int fd, char *str)
{
	size_t	i;

	i = 0;
	while (*(str + i) != '\0')
		i++;
	write(fd, str, i);
}

void	put_linenumber(int linenumber)
{
	char	a;

	a = '0' + linenumber;
	write_string(1, "Line ");
	write(1, &a, 1);
	write_string(1, ": ");
}

int	ft_error_codes(int error_code)
{
	if (error_code == 0)
		write_string(2, "\nFile name missing.");
	if (error_code == 1)
		write_string(2, "\nNo or too many file names.");
	if (error_code == 2)
		write_string(2, "\nCannot open file.");
	if (error_code == 3)
		write_string(2, "\nFunction returned NULL.");
	return (1);
}

int	main(int argc, char *argv[])
{
	int		fd;
	int		line_number;
	char	*next_line;

	if (argc != 2)
		return (ft_error_codes(1));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (ft_error_codes(2));
	line_number = 0;
	while (0 == 0)
	{
		next_line = get_next_line(fd);
		if (next_line == NULL)
		{
			close(fd);
			return (ft_error_codes(3));
		}
		line_number++;
		put_linenumber(line_number);
		write_string(1, next_line);
		free(next_line);
	}
	close(fd);
}
