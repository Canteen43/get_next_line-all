/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   legacy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kweihman <kweihman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 15:08:45 by kweihman          #+#    #+#             */
/*   Updated: 2024/07/20 16:32:33 by kweihman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*read_into_buffer(int fd)
{
	char	*buf;

	buf = malloc(BUFFER_SIZE);
	if (buf == NULL)
		return (NULL);
	if (read(fd, buf, BUFFER_SIZE) == -1)
		return (NULL);
	return (buf);
}

char	*append(char *reststring, int fd, int *p_ret)
{
	int		i;
	char	*new_reststring;

	i = 0;
	while (*(reststring + i) != '\0')
		i++;
	new_reststring = malloc(i + BUFFER_SIZE + 1);
	if (new_reststring == NULL)
		return (NULL);
	*p_ret = read(fd, (new_reststring + i), BUFFER_SIZE);
	if (*p_ret == -1)
		return (NULL);
	*(new_reststring + i + *p_ret) = '\0';
	while (i-- != 0)
		*(new_reststring + i) = *(reststring + i);
	return (new_reststring);
}
