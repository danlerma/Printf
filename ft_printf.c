/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlerma-c <dlerma-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 20:30:24 by dlerma-c          #+#    #+#             */
/*   Updated: 2021/09/19 20:57:19 by dlerma-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_percent(const char *str, va_list ap, int i)
{
	int			count;
	int			y;
	t_percent	per;

	count = 0;
	y = 0;
	if (str[i + 1] == 'c')
	{
		per.c_character = va_arg(ap, int);
		count = ft_putchar_fd(per.c_character, 1);
	}
	//string (s)
	else if (str[i + 1] == 's')
	{
		per.s_string = va_arg(ap, char *);
		if (per.s_string == '\0')
			count += ft_putstr("(null)");
		else
			count += ft_putstr(per.s_string);
	}
	//int (d) int (i)
	else if (str[i + 1] == 'd' || str[i + 1] == 'i')
	{
		per.d_integer = va_arg(ap, int);
		per.s_string = ft_itoa(per.d_integer);
		count += ft_putstr(per.s_string);
		free(per.s_string);
	}
	//int (u)
	else if (str[i + 1] == 'u')
	{
		per.d_integer = va_arg(ap, int);
		per.s_string = ft_itoa(per.d_integer);
		per.u_integer = ft_atoi(per.s_string);
		count += ft_putstr(per.u_integer);
		free(per.s_string);
	}
	return (count);
}

static int	check_normal_characters(char str)
{
	int count;

	count = 0;
	count = ft_putchar_fd(str, 1);
	return (count);
}

int	ft_printf(const char *str, ...)
{
    va_list	ap;
	int		result;
	int		i;

	i = 0;
	result = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			result += check_percent(str, ap, i);
			i++;
		}
		else
			result += check_normal_characters(str[i]);
		i++;
	}
	va_end(ap);
	return (result);
}
