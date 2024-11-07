/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   printf_appf_str_bonus.c                             :+:    :+:           */
/*                                                      +:+                   */
/*   By: avaliull <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/07 13:02:28 by avaliull       #+#    #+#                */
/*   Updated: 2024/11/07 13:07:09 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static char	*str_not_next_var(char *flags, ssize_t *wid_prec, ssize_t *l)
{
	char *conv_str;
	
	if ((flags[2] == '.' && wid_prec[1] < 6))
	{
		conv_str = ft_strdup("");
		*l = 0;
	}
	else
	{
		conv_str = ft_strdup("(null)");
		*l = 6;
	}
	if (!conv_str)
		return (NULL);
	return (conv_str);
}

static char	*str_new(char *var, char *flags, ssize_t *wid_prec, ssize_t *l)
{
	char	*conv_str;

	*l = ft_strlen(var);
	if (flags[2] == '.' && wid_prec[1] < *l)
		*l = wid_prec[1];
	conv_str = (char *) malloc(sizeof(char) * (*l + 1));
	if (!conv_str)
		return (NULL);
	ft_memcpy(conv_str, var, *l);
	conv_str[*l] = '\0';
	return (conv_str);
}

char	*c_str(char *next_var, t_strlst **out_lst, char *flags, ssize_t *wid_prec)
{
	char	*conv_str;
	ssize_t	str_len;
	
	if (wid_prec[1] == -1)
		wid_prec[1] = 0;
	if (!next_var)
		conv_str = str_not_next_var(flags, wid_prec, &str_len);
	else if (*next_var == '\0')
	{
		conv_str = ft_strdup("");
		str_len = 0;
	}
	else
		conv_str = str_new(next_var, flags, wid_prec, &str_len);		
	if (!conv_str)
		return (NULL);
	conv_str = app_flags_cs(conv_str, flags, wid_prec, &str_len);
	if (!add_str_to_list(conv_str, out_lst, str_len))
		return (NULL);
	return (conv_str);
}

