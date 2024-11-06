/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_scidu.c                                 :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:03:35 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/06 19:21:01 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_printf.h"
#include <stdlib.h>

// The following functions manage conversions for %c, %%, %s %i to string;
// After conversion, functions to apply bonus flags and manage width are called;
// The resulting strings are passed to add_str_to_list for writing later;
// Return is either NULL or the ptr to converted string for error-checking.

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

char	*c_perc(t_strlst **out_lst)
{
	char	*conv_str;

	conv_str = (char *) malloc (sizeof(char) * 2);
	if (!conv_str)
		return (NULL);
	conv_str[0] = '%';
	conv_str[1] = '\0';
	if (!add_str_to_list(conv_str, out_lst, 1))
		return (NULL);
	return (conv_str);
}

char	*c_char(int next_var, t_strlst **out_lst, char *flags, ssize_t *wid_prec)
{
	char	*conv_str;
	ssize_t	str_len;

	conv_str = (char *)malloc (sizeof(char) * 2);
	if (!conv_str)
		return (NULL);
	conv_str[0] = (char)next_var;
	conv_str[1] = '\0';
	str_len = 1;
	conv_str = app_flags_cs(conv_str, flags, wid_prec, &str_len);
	if (!add_str_to_list(conv_str, out_lst, str_len))
		return (NULL);
	return (conv_str);
}

char	*c_int(int next_var, t_strlst **out_lst, char *flags, ssize_t *wid_prec)
{
	char	*conv_str;
	ssize_t	str_len;

	conv_str = ft_itoa(next_var);
	if (!conv_str)
		return (NULL);
	str_len = ft_strlen(conv_str);
	conv_str = app_flags_di(conv_str, flags, wid_prec, &str_len);
	if (!add_str_to_list(conv_str, out_lst, str_len))
		return (NULL);
	return (conv_str);
}

char	*c_uint(unsigned long long next_var, t_strlst **out_lst) // VAR for +/' ' (sign), VAR for 0/- (just), VAR for width
{
	char	*conv_str;
	int		str_len;

	conv_str = ft_utoa(next_var);
	if (!conv_str)
		return (NULL);
	str_len = ft_strlen(conv_str);
	if (!add_str_to_list(conv_str, out_lst, str_len))
		return (NULL);
	return (conv_str);
}
