/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aihya <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 05:50:19 by aihya             #+#    #+#             */
/*   Updated: 2018/10/28 15:19:34 by aihya            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_words(char const *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c)
			n++;
		i++;
	}
	return (n);
}
