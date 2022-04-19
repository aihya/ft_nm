/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:04:06 by aihya             #+#    #+#             */
/*   Updated: 2022/04/18 22:04:11 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	invalid_option(char op)
{
	ft_putstr("nm: invalid option -- ");
	ft_putchar('\'');
	ft_putchar(arg);
	ft_putendl("'");
}

static int	set_options(char *arg, int *ops)
{
	int	i;

	i = 0;
	while (++i && ft_strchr("agurp", arg[i]))
	{
		if (arg[i] == 'a')
			*ops |= OP_A;
		else if (arg[i] == 'g')
			*ops |= OP_G;
		else if (arg[i] == 'u')
			*ops |= OP_U;
		else if (arg[i] == 'r')
			*ops |= OP_R;
		else
			*ops |= OP_P;
	}
	return (i);
}

static int	parse_arg(char *arg)
{
	int	i;
	int	ops;

	ops = 0;
	i = set_options(arg, &ops);
	if (i != ft_strlen(arg + 1))
		return (invalid_option(arg[i]));
	return (ops);
}

int	parse_args(int argc, char **argv)
{
	int	i;
	int	j;
	int	ops;
	int o;

	if (argc == 1)
		return (pr_error("ft_nm need a file name.\n"));
	ops = 0;
	i = 0;
	while (++i < argc)
	{
		o = parse_arg(argv[i]);
		if (argv[i][0] == '-' && o == ERROR)
			return (ERROR);
		ops |= o;
	}
	return (ops);
}