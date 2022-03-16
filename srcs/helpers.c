/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asanthos <asanthos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/12 12:21:22 by asanthos          #+#    #+#             */
/*   Updated: 2022/03/16 10:42:21 by asanthos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_isalnum(int c)
{
	if ((c < 91 && c > 64) || (c < 123 && c > 96) || (c < 58 && c > 47))
		return (1);
	return (0);
}

static void	ft_bzero(void *s, size_t n)
{
	unsigned char	*dest;
	unsigned int	i;

	i = 0;
	dest = (unsigned char *)s;
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	int		*str;

	str = (int *)malloc(nmemb * size);
	if (!str)
		return (NULL);
	ft_bzero(str, nmemb * size);
	return (str);
}

void	ft_putstr(char *str)
{
	while (*str)
		write(1, &*str++, 1);
}

static void	check_int(double r)
{
	if (r > 2147483647 || r < -2147483648)
	{
		ft_putstr("Error\n");
		exit(EXIT_FAILURE);
	}
}

static void	check_num(const char *str, int i)
{
	if (str[i] < 48 || str[i] > 57)
	{
		ft_putstr("Error\n");
		exit(EXIT_FAILURE);
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	int		s;
	double	r;

	i = 0;
	s = 1;
	r = 0;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	while (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	check_num(str, i);
	while (str[i] <= '9' && str[i] >= '0')
	{
		if (i >= 10)
			check_int(r);
		r *= 10;
		r = r + (str[i] - '0');
		i++;
	}
	r *= s;
	return (r);
}
