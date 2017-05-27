/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stack.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvillasa <hvillasa@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/27 01:23:58 by hvillasa          #+#    #+#             */
/*   Updated: 2017/05/27 01:24:02 by hvillasa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int check_dups(t_list *stack, int *value)
{
	while (stack)
	{
		if (*(int*)stack->content == *value)
			return (1);
		stack = stack->next;
	}
	return (0);
}

int list_len(t_list *ls)
{
	int len;

	len = 0;
	while (ls)
	{
		len++;
		ls = ls->next;
	}
	return (len);
}

static int av_to_int(char *av, int *value)
{
	int		num;
	int		neg;

	num = 0;
	neg = 1;
	if (!av)
		return (1);
	if (*av == '-')
	{
		neg = -1;
		av++;
	}
	if (*av == '\0')
		return (1);
	while ('0' <= *av && *av <= '9')
	{
		num = (10 * num) + neg * (*av - '0');
		av++;
		if ((neg == 1 && num < 0) || (neg == -1 && num > 0))
			return (1);
	}
	if (*av != '\0')
		return (1);
	*value = num;
	return (0);
}


static int addstackarray(t_list **stack, char *av)
{
	char	**split;
	int		value;
	int		i;

	i = 0;
	split = ft_strsplit(av, ' ');

	while (split[i])
		i++;
	while (i)
	{
		i--;
		if (av_to_int(split[i], &value) || check_dups(*stack, &value))
		{
			free_split(&split);
			return (1);
		}
		ft_lstadd(stack, ft_lstnew(&value, sizeof(int)));
	}
	free_split(&split);
	return (0);
}

int *moveto_array(t_list *stack, int stack_len)
{
	int *a;
	int i;

	i = 0;
	a = init_array(stack_len);
	while (stack)
	{
		a[i] = *(int*)stack->content;
		i++;
		stack = stack->next;
	}
	return (a);
}

int create_stack(int ac, char **av, t_stack **st)
{
	t_list *a;

	a = NULL;
	while (--ac)
	{
		if (addstackarray(&a, av[ac]))
			return (1);
	}
	(*st)->size_a = list_len(a);
	(*st)->a = moveto_array(a, (*st)->size_a);
	ft_lstfree(a);
	return (0);
}
