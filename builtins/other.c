/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smassand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 13:31:04 by smassand          #+#    #+#             */
/*   Updated: 2016/12/13 13:31:20 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void		ft_env_usage(void)
{
	ft_putstr_fd("usage: env [-i] [--ignore-environement] \
[-u name] [--unset name]\n", 2);
	ft_putstr_fd("\t   [name=value ...] [utility [args...]]\n", 2);
}
