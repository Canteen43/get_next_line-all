/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kweihman <kweihman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 14:00:09 by kweihman          #+#    #+#             */
/*   Updated: 2024/07/28 10:29:23 by kweihman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H

# include <unistd.h> //read()
# include <stdlib.h> //malloc() and free()

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 43
# endif

# define GET_NEXT_LINE_H

char	*get_next_line(int fd);
char	*keep_reading(char *reststring, int fd, int *p_read_rt);
int		length(char *str, int skip_until, int end_char, int incl);
void	copy(char *src, char *dst, int skip_until, int end_char);
int		includes_newline(char *reststring);
char	*return_next_line(char **p_reststring);
char	*set_null_character(char *p);
char	*return_last_line(char **p_reststring);

#endif