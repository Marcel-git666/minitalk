/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 17:26:55 by mmravec           #+#    #+#             */
/*   Updated: 2024/09/17 10:26:10 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *str, char c)
{
	int		words;
	int		is_inside_word;

	words = 0;
	is_inside_word = 0;
	while (*str)
	{
		if (*str == c)
		{
			is_inside_word = 0;
		}
		else
		{
			if (!is_inside_word)
			{
				words++;
				is_inside_word = 1;
			}
		}
		str++;
	}
	return (words);
}

static char	*alloc_copy_word(char *current_word, int word_length)
{
	char	*word;

	word = (char *)malloc((word_length + 1) * sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, current_word, word_length + 1);
	return (word);
}

static void	extract_words(char **result, char const **s, char c, int *words)
{
	char	*current_word;
	int		word_length;

	word_length = 0;
	while (**s)
	{
		if (**s == c)
		{
			if (word_length > 0)
			{
				result[*words] = alloc_copy_word(current_word, word_length);
				(*words)++;
				word_length = 0;
			}
		}
		else
		{
			if (word_length++ == 0)
				current_word = (char *)*s;
		}
		(*s)++;
	}
	if (word_length > 0)
		result[(*words)++] = alloc_copy_word(current_word, word_length);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		words;

	words = 0;
	if (!s)
		return (NULL);
	result = (char **) malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	extract_words(result, &s, c, &words);
	result[words] = NULL;
	return (result);
}
