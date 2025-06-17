#include "minishell.h"

int	is_special_or_space(char c)
{
	return (is_special_char(c) || ft_isspace(c));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

t_token	*tokenize_line(char *line)
{
	t_token	*tokens = NULL;
	int		i = 0;
	char	*word;

	while (line[i])
	{
		// Saltar espacios
		while (line[i] && ft_isspace(line[i]))
			i++;

		if (!line[i])
			break;

		// Manejo de comillas
		if (line[i] == '\'' || line[i] == '"')
			handle_quotes(line, &i, &word);
		else if (is_special_char(line[i]))
			word = ft_strdup_special(line, &i); // función que maneje símbolos como >, >>, |, etc.
		else
			word = ft_strdup_word(line, &i); // palabra normal

		add_token(&tokens, detect_token_type(word), word);
		free(word);
	}
	printf("%u\n", tokens->type);
	return (tokens);
}

void	add_token(t_token **tokens, t_token_type type, char *value)
{
	t_token	*new = create_token(type, value);
	t_token	*tmp;

	if (!new)
		return;
	if (!*tokens)
	{
		*tokens = new;
		return;
	}
	tmp = *tokens;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = ft_strdup(value);
	token->next = NULL;
	return (token);
}

int	is_special_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	handle_quotes(char *line, int *i, char **word)
{
	char	quote;
	int		start;

	quote = line[*i];
	start = ++(*i);
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] != quote)
	{
		*word = NULL;
		return ;
	}
	*word = ft_substr(line, start, *i - start);
	(*i)++;
}

char	*ft_strdup_special(char *line, int *i)
{
	char	*str;

	if ((line[*i] == '>' && line[*i + 1] == '>') ||
		(line[*i] == '<' && line[*i + 1] == '<'))
	{
		str = ft_substr(line, *i, 2);
		*i += 2;
	}
	else
	{
		str = ft_substr(line, *i, 1);
		*i += 1;
	}
	return (str);
}

char	*ft_strdup_word(char *line, int *i)
{
	int		start;
	int		len;

	start = *i;
	while (line[*i] && !is_special_or_space(line[*i]))
		(*i)++;
	len = *i - start;
	return (ft_substr(line, start, len));
}

t_token_type	detect_token_type(char *word)
{
	if (!ft_strcmp(word, "|"))
		return (T_PIPE);
	else if (!ft_strcmp(word, "<"))
		return (T_REDIRECT_IN);
	else if (!ft_strcmp(word, "<<"))
		return (T_HEREDOC);
	else if (!ft_strcmp(word, ">"))
		return (T_REDIRECT_OUT);
	else if (!ft_strcmp(word, ">>"))
		return (T_APPEND);
	else
		return (T_WORD);
}
