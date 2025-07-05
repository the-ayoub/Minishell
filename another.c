#include "minishell.h"

int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == ';');
}

static char *collect_word(char *s, int *i)
{
    int start = *i;
    int in_quote = 0;
    char quote_char = 0;

    while (s[*i]) {
        // Manejo de comillas
        if (!in_quote && (s[*i] == '\'' || s[*i] == '\"')) {
            in_quote = 1;
            quote_char = s[*i];
            (*i)++;
            continue;
        } 
        else if (in_quote && s[*i] == quote_char) {
            in_quote = 0;
            (*i)++;
            // Si después de cerrar comillas viene espacio o token especial, termina la palabra
            if (s[*i] == ' ' || s[*i] == '\t' || s[*i] == '\0' || is_special_char(s[*i]))
                break;
            else
                continue;
        }
        
        // Si no está entre comillas y encuentra un caracter especial, termina
        if (!in_quote && is_special_char(s[*i])) {
            break;
        }
        
        // Si no está entre comillas y encuentra espacio, termina
        if (!in_quote && (s[*i] == ' ' || s[*i] == '\t')) {
            break;
        }
        
        (*i)++;
    }
    return ft_substr(s, start, *i - start);
}


static t_token_type detect_operator(char *s, int *i)
{
    if (s[*i] == '|') {
        (*i)++;
        return TOKEN_PIPE;
    }
    if (s[*i] == '<' && s[*i + 1] == '<') {
        (*i) += 2;
        return TOKEN_HEREDOC;
    }
    if (s[*i] == '>' && s[*i + 1] == '>') {
        (*i) += 2;
        return TOKEN_REDIR_APPEND;
    }
    if (s[*i] == '<') {
        (*i)++;
        return TOKEN_REDIR_IN;
    }
    if (s[*i] == '>') {
        (*i)++;
        return TOKEN_REDIR_OUT;
    }
    return TOKEN_WORD;
}


t_token *create_token(t_token_type type, char *value)
{
    t_token *new = malloc(sizeof(t_token));
    if (!new)
        return (NULL);
    new->type = type;
    new->value = value;
    new->next = NULL;
    return (new);
}

void add_token(t_token **tokens, t_token_type type, char *value)
{
    t_token *new = create_token(type, value);
    t_token *last;
    
    if (!new)
        return;
    if (!*tokens)
        *tokens = new;
    else
    {
        last = *tokens;
        while (last->next)
            last = last->next;
        last->next = new;
    }
}

t_token *tokenize_line(char *line)
{
    t_token *tokens = NULL;
    int i = 0;
    
    while (line[i]) {
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if (!line[i])
            break;
        
        if (is_special_char(line[i])) {
            t_token_type type = detect_operator(line, &i);
            add_token(&tokens, type, NULL);
        }
        else {
            char *word = collect_word(line, &i);
            if (!word) {
                // Liberar tokens si hay error
                free_tokens(tokens);
                return NULL;
            }
            add_token(&tokens, TOKEN_WORD, word);
        }
    }
    return tokens;
}
