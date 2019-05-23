/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maparmar <maparmar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 11:13:38 by maparmar          #+#    #+#             */
/*   Updated: 2019/05/23 12:45:59 by maparmar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ssl.h"

static	char	*itoa_store(intmax_t *num, int base, int *i, int *count)
{
	char	*new;
	long	tmp;
	int		len;

	len = 0;
	if (*num < 0)
	{
		if (base == 10)
			(*i)++;
		(*num) *= -1;
	}
	tmp = *num;
	while (tmp >= base)
	{
		tmp /= base;
		len++;
	}
	len++;
	*count = (len + (*i));
	new = (char*)malloc(sizeof(char) * (*count) + 1);
	return (new);
}

char			*ft_itoa_base(intmax_t n, int base)
{
	char		*base_d;
	char		*new;
	intmax_t	num;
	int			i;
	int			count;

	i = 0;
	count = 0;
	num = n;
	base_d = ft_strdup("0123456789abcdef");
	new = itoa_store(&num, base, &i, &count);
	if (!new)
		return (NULL);
	if (i > 0)
		new[0] = '-';
	new[count] = '\0';
	while (num >= base)
	{
		new[--count] = base_d[num % base];
		num /= base;
	}
	new[i] = base_d[num % base];
	ft_strdel(&base_d);
	return (new);
}

t_mem	*ft_memjoin(t_mem *dest, t_mem *src)
{
	t_mem *ret;

	ret = (t_mem *)malloc(sizeof(t_mem));
	if (!dest)
	{
		ret->data = (unsigned char *)ft_strnew(src->len);
		ft_memcpy(ret->data, src->data, src->len);
		ret->len = src->len;
		return (ret);
	}
	ret->len = dest->len + src->len;
	ret->data = (unsigned char *)ft_strnew(ret->len);
	ft_memcpy((void*)ret->data, dest->data, dest->len);
	ft_memcpy((void*)&ret->data[dest->len], src->data, src->len);
	ft_free_mem(dest);
	return (ret);
}

void	ft_free_mem(t_mem *mem)
{
	free(mem->data);
	free(mem);
}