/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <aihya@student.1337.ma>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 21:04:06 by aihya             #+#    #+#             */
/*   Updated: 2022/04/20 01:05:08 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int	invalid_option(char op)
{
	ft_putstr("nm: invalid option -- ");
	ft_putchar('\'');
	ft_putchar(op);
	ft_putendl("'");
	return (ERROR);
}

static int	adjust_options(int ops)
{
	if (ops & OP_U)
		ops &= ~(OP_G | OP_A | DFLT);
	else if (ops & OP_G)
		ops &= ~(OP_A | DFLT);
	else if (ops & OP_A)
		ops &= ~(DFLT);
	if (ops & OP_P)
		ops &= ~(OP_R);
	return (ops);
}

static int	parse_arg(char *arg, int old_ops)
{
	int		ops;
	size_t	i;

	ops = old_ops;
	i = 0;
	while (++i < ft_strlen(arg) && ft_strchr("agurp", arg[i]))
	{
		if (arg[i] == 'a')
			ops |= OP_A;
		else if (arg[i] == 'g')
			ops |= OP_G;
		else if (arg[i] == 'u')
			ops |= OP_U;
		else if (arg[i] == 'r')
			ops |= OP_R;
		else
			ops |= OP_P;
	}
	if (i == ft_strlen(arg))
		return (adjust_options(ops));
	return (invalid_option(arg[i]));
}

int	parse_args(int argc, char **argv, int *ops)
{
	int	names;
	int	i;
	int o;

	i = 0;
	names = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-' || (argv[i][0] == '-' && ft_strlen(argv[i]) == 1))
			names++;
		else if (argv[i][0] == '-')
		{
			o = parse_arg(argv[i], *ops);
			if (o == ERROR)
				return (ERROR);
			*ops = o;
		}
	}
	return (names);
}
