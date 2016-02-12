/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tet.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchaleil <hello@baptistechaleil.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/18 15:04:36 by bchaleil          #+#    #+#             */
/*   Updated: 2016/02/12 16:10:13 by bchaleil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

static int		get_colone_y(char *matrix)
{
	int		i;
	int		r;
	int		ret;

	i = -1;
	r = 0;
	ret = 1337;
	while (++i < 20)
	{
		if (matrix[i] == '#')
		{
			if (r == 0)
				return (0);
			if (r < ret)
				ret = r;
			while (matrix[i] != '\n')
				i++;
		}
		r++;
		if (matrix[i] == '\n')
			r = 0;
	}
	return (ret);
}

static int		get_code(char *matrix)
{
	int	pos;
	int i;
	int j;
	int code;

	pos = get_colone_y(matrix);
	i = pos - 1;
	j = 1;
	code = 0;
	while (++i < 20)
	{
		if (matrix[i] == '#' && EDGE(matrix, i))
		{
			code *= 10;
			code += j;
		}
		j++;
		if (matrix[i] == '\n')
		{
			j = 1;
			i += pos;
		}
	}
	return (code);
}

static int		valid_tet(int code)
{
	int	*codes;
	int i;

	codes = get_codes();
	i = 0;
	while (codes[i] != -1337)
	{
		if (codes[i++] == code)
		{
			free(codes);
			return (1);
		}
	}
	free(codes);
	return (0);
}

int				get_tet(char *file_name, t_tet **tetri_list)
{
	char		*matrix;
	int			tet_count;
	int			i;
	int			code;

	matrix = get_matrix(file_name);
	tet_count = ((ft_strlen(matrix) + 1) / 21);
	i = 0;
	while (i < tet_count)
	{
		code = get_code(matrix + (21 * i));
		if (valid_tet(code))
			push_list(tetri_list, i, code);
		else
			return (0);
		i++;
	}
	return (1);
}
