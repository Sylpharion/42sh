/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 14:54:30 by afougere          #+#    #+#             */
/*   Updated: 2016/01/27 17:28:17 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*s_bis;
	int		start;
	int		ma_taille;
	int		i;

	i = 0;
	start = 0;
	if (s == NULL)
		return (NULL);
	while (s[start] && (s[start] == ' ' || s[start] == '\t' || s[start] ==
	'\n'))
		start++;
	while (s[i])
		i++;
	i -= 1;
	while (i > 0 && (s[i] == ' ' || s[i] == '\t' || s[i] == '\n'))
		i--;
	ma_taille = i - start + 1;
	if (ma_taille <= 0)
		return (s_bis = ft_strsub(s, 0, 0));
	return (s_bis = ft_strsub(s, start, ma_taille));
}
