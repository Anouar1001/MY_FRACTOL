/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aboukhmi <aboukhmi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 12:30:36 by aboukhmi          #+#    #+#             */
/*   Updated: 2025/01/26 13:30:36 by aboukhmi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_isvalide(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (str[i] == '+' || str[i] == '-'
		|| ft_isdigit(str[i]) == 1 || str[i] == '.')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == 1)
			i++;
		else if (str[i] == '.')
		{
			i++;
			count++;
		}
		else
			return (0);
	}
	if (count > 1)
		return (0);
	return (1);
}

double	ft_pow(int a, int b)
{
	int			i;
	long long	res;

	i = 0;
	res = 1;
	while (i < b)
	{
		res = res * a;
		i++;
	}
	return (res);
}

int	check_signe(char c)
{
	int	signe;

	signe = 1;
	if (c == '-')
		signe = -1;
	return (signe);
}

double	ft_atodd(char *str)
{
	int		i;
	double	result;
	int		signe;
	int		count;

	count = 0;
	i = 0;
	result = 0.0;
	signe = 1;
	signe = check_signe(str[i]);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]) == 1)
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] == '.' && str[i + 1] == '\0')
		show_error();
	while (ft_isdigit(str[++i]) == 1)
	{
		result = result * 10 + (str[i] - '0');
		count++;
	}
	return (signe *(result / ft_pow(10, count)));
}
