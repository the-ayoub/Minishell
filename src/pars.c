#include "../include/minishell.h"

int expand_dollar(t_shell *shell, char **result, char *ptr)
{
    int len = 1;
    char *var_name = NULL;
    char *var_value = NULL;
    char *start_ptr = ptr;  // Usar puntero para posición

    if (ptr[1] == '?') // Manejo de $?
    {
        var_value = ft_itoa(shell->last_status);
        len = 2;
    }
    else if (ft_isalnum(ptr[1]) || ptr[1] == '_') // Variables normales
    {
        start_ptr = ptr + 1;
        ptr = start_ptr;
        while (ft_isalnum(*ptr) || *ptr == '_')
            ptr++;
        len = ptr - start_ptr;
        var_name = ft_substr(start_ptr, 0, len);
        var_value = get_env_value(shell, var_name);
        len++; // Sumamos el '$'
    }
    else // $ seguido de carácter no válido
    {
        append_char(result, '$');
        return 1;
    }
    
    if (var_value)
    {
        char *new = ft_strjoin(*result, var_value);
        free(*result);
        *result = new;
        free(var_value);
    }
    if (var_name)
        free(var_name);
    return len;
}

void append_char(char **str, char c)
{
    char *new_str;
    int len = *str ? ft_strlen(*str) : 0;
    
    new_str = malloc(len + 2);
    if (!new_str)
        return;
    if (*str)
        ft_memcpy(new_str, *str, len);
    new_str[len] = c;
    new_str[len + 1] = '\0';
    if (*str)
        free(*str);
    *str = new_str;
}


int syntax_check(t_token *tokens)
{
    if (!tokens)
        return (1); // Error: línea vacía
    
    // Verificar pipe al inicio
    if (tokens->type == TOKEN_PIPE)
        return (1);
    
    t_token *current = tokens;
    while (current)
    {
        // Verificar redirecciones sin archivo
        if (current->type >= TOKEN_REDIR_IN && current->type <= TOKEN_HEREDOC)
        {
            if (!current->next || current->next->type != TOKEN_WORD)
                return (1);
            current = current->next; // Saltar el archivo
        }
        // Verificar pipes consecutivos
        else if (current->type == TOKEN_PIPE)
        {
            if (!current->next || current->next->type == TOKEN_PIPE)
                return (1);
        }
        current = current->next;
    }
    return (0); // Sintaxis válida
}
#include "../include/minishell.h"

static void add_argument(t_cmd *cmd, char *arg)
{
    int count = 0;
    char **new_argv;

    // Contar argumentos existentes
    if (cmd->argv) {
        while (cmd->argv[count]) count++;
    }

    // Asignar nuevo array (count + 1 argumentos + NULL)
    new_argv = malloc((count + 2) * sizeof(char *));
    if (!new_argv) return;

    // Copiar argumentos existentes
    for (int i = 0; i < count; i++) {
        new_argv[i] = cmd->argv[i];
    }

    // Agregar nuevo argumento
    new_argv[count] = arg;
    new_argv[count + 1] = NULL;

    // Liberar el array anterior y actualizar
    if (cmd->argv) free(cmd->argv);
    cmd->argv = new_argv;
}

static t_redir *create_redirection(t_redir_type type, char *file)
{
    t_redir *new = malloc(sizeof(t_redir));
    if (!new) return NULL;
    
    new->type = type;
    new->file = file;
    new->next = NULL;
    return new;
}
void add_redirection(t_cmd *cmd, t_token *token)
{
    t_redir_type type;
    char *file = NULL;

    // Determinar tipo de redirección
    if (token->type == TOKEN_REDIR_IN)
        type = REDIR_IN;
    else if (token->type == TOKEN_REDIR_OUT)
        type = REDIR_OUT;
    else if (token->type == TOKEN_REDIR_APPEND)
        type = REDIR_APPEND;
    else if (token->type == TOKEN_HEREDOC)
        type = REDIR_HEREDOC;
    else
        return;

    // Obtener el archivo (siguiente token debe ser palabra)
    if (token->next && token->next->type == TOKEN_WORD) {
        file = ft_strdup(token->next->value);
    }

    if (!file) return;  // Error: falta archivo para redirección

    t_redir *new_redir = create_redirection(type, file);
    if (!new_redir) {
        free(file);
        return;
    }

    // Agregar a la lista de redirecciones
    if (!cmd->redirs) {
        cmd->redirs = new_redir;
    } else {
        t_redir *last = cmd->redirs;
        while (last->next) last = last->next;
        last->next = new_redir;
    }
}

static t_cmd *create_new_command(void)
{
    t_cmd *new = malloc(sizeof(t_cmd));
    if (!new) return NULL;
    
    new->argv = NULL;
    new->redirs = NULL;
    new->next = NULL;
    return new;
}

t_cmd *parse_tokens(t_shell *shell, t_token *tokens)
{
    (void)shell;  // Marcar parámetro como usado para evitar warning
    
    t_cmd *head = NULL;
    t_cmd *current_cmd = NULL;
    t_token *current = tokens;

    while (current) {
        if (current->type == TOKEN_PIPE) {
            if (!current_cmd) {
                ft_putstr_fd("minishell: syntax error near `|'\n", STDERR_FILENO);
                free_cmd_list(head);
                return NULL;
            }
            current_cmd->next = create_new_command();
            current_cmd = current_cmd->next;
            current = current->next;
            continue;
        }

        if (!current_cmd) {
            current_cmd = create_new_command();
            head = current_cmd;
        }

        switch (current->type) {
            case TOKEN_WORD:
                add_argument(current_cmd, ft_strdup(current->value));
                break;
                
            case TOKEN_REDIR_IN:
            case TOKEN_REDIR_OUT:
            case TOKEN_REDIR_APPEND:
            case TOKEN_HEREDOC:
                // Validar que el siguiente token es palabra
                if (!current->next || current->next->type != TOKEN_WORD) {
                    ft_putstr_fd("minishell: syntax error near redirection\n", STDERR_FILENO);
                    free_cmd_list(head);
                    return NULL;
                }
                add_redirection(current_cmd, current);
                current = current->next; // Saltar token de archivo
                break;
                
            case TOKEN_PIPE:  // Añadido explícitamente aunque ya se maneja arriba
                // No debería llegar aquí por el continue previo
                break;
                
            default:
                // Manejar cualquier token inesperado
                ft_putstr_fd("minishell: unknown token type\n", STDERR_FILENO);
                free_cmd_list(head);
                return NULL;
        }
        current = current->next;
    }
    return head;
}
