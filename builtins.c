#include "minishell.h"

int is_valid_exit_arg(char *arg)
{
    if (!arg)
        return (1);
    while (*arg) {
        if (!ft_isdigit(*arg))
            return (0);
        arg++;
    }
    return (1);
}

int builtin_exit(t_shell *shell, char **argv)
{
    int exit_code = 0;
    
    (void)shell;  // Marcar parámetro no usado explícitamente
    
    if (argv[1] && argv[2]) {
        ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
        return (1);
    }
    if (argv[1] && !is_valid_exit_arg(argv[1])) {
        ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
        ft_putstr_fd(argv[1], STDERR_FILENO);
        ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
        exit_code = 255;
    }
    else if (argv[1]) {
        exit_code = ft_atoi(argv[1]);
    }
    // Limpiar recursos antes de salir
    exit(exit_code);
}

int builtin_cd(t_shell *shell, char **argv)
{
    char *path = argv[1];
    char cwd[PATH_MAX];
    char *oldpwd = getcwd(NULL, 0);
    
    if (!path || (path[0] == '~' && path[1] == '\0'))
        path = get_env_value(shell, "HOME");
    else if (path[0] == '-' && path[1] == '\0')
        path = get_env_value(shell, "OLDPWD");
    
    if (!path) {
        ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
        free(oldpwd);
        return (1);
    }
    if (chdir(path) != 0) {
        perror("minishell: cd");
        free(oldpwd);
        return (1);
    }
    set_env_var(shell, "OLDPWD", oldpwd);
    getcwd(cwd, sizeof(cwd));
    set_env_var(shell, "PWD", cwd);
    free(oldpwd);
    return (0);
}
int builtin_echo(t_shell *shell, char **argv)
{
    int i = 1;
    int newline = 1;
    
    (void)shell;
    if (argv[1] && ft_strcmp(argv[1], "-n") == 0) {
        newline = 0;
        i++;
    }
    
    while (argv[i]) {
        ft_putstr_fd(argv[i], STDOUT_FILENO);
        if (argv[i + 1])
            ft_putchar_fd(' ', STDOUT_FILENO);
        i++;
    }
    
    if (newline)
        ft_putchar_fd('\n', STDOUT_FILENO);
    return 0;
}
int builtin_pwd(t_shell *shell, char **argv)
{
    (void)argv;
    (void)shell;
    char *cwd = getcwd(NULL, 0);
    if (cwd) {
        printf("%s\n", cwd);
        free(cwd);
        return 0;
    }
    perror("minishell: pwd");
    return 1;
}

int builtin_export(t_shell *shell, char **argv)
{
    if (!argv[1]) {
        for (int i = 0; shell->env[i]; i++)
            printf("declare -x %s\n", shell->env[i]);
        return 0;
    }
    
    int status = 0;
    for (int i = 1; argv[i]; i++) {
        char *name = argv[i];
        char *value = strchr(argv[i], '=');
        
        if (value) *value++ = '\0';
        
        if (!is_valid_identifier(name)) {
            ft_putstr_fd("minishell: export: `", STDERR_FILENO);
            ft_putstr_fd(name, STDERR_FILENO);
            ft_putstr_fd("': not a valid identifier\n", STDERR_FILENO);
            status = 1;
            continue;
        }
        
        if (value) {
            set_env_var(shell, name, value);
        } else {
            // Solo exportar sin asignar valor
            char *current = get_env_value(shell, name);
            if (!current) set_env_var(shell, name, "");
        }
    }
    return status;
}

int builtin_unset(t_shell *shell, char **argv)
{
    if (!argv[1]) {
        fprintf(stderr, "minishell: unset: missing argument\n");
        return 1;
    }
    (void) shell;
    // Implementar lógica para eliminar variables
    return 0;
}

int builtin_env(t_shell *shell, char **argv)
{
    (void)argv;
    for (int i = 0; shell->env[i]; i++) {
        printf("%s\n", shell->env[i]);
    }
    return 0;
}