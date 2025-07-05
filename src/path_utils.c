#include "../include/minishell.h"

#include "../include/minishell.h"

#include "../include/minishell.h"

char *get_cmd_path(const char *cmd, char **envp)
{
    char *path_env = NULL;
    char *path_copy = NULL;
    char *full_path = NULL;
    char *token = NULL;
    char **paths = NULL;
    int i = 0;

    // 1. Verificar si el comando es una ruta absoluta o relativa
    if (ft_strchr(cmd, '/')) {
        if (access(cmd, X_OK) == 0)
            return ft_strdup(cmd);
        return NULL;
    }

    // 2. Buscar la variable PATH en el entorno
    while (envp[i] && !path_env) {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            path_env = envp[i] + 5; // Saltar "PATH="
        i++;
    }
    
    if (!path_env) return NULL;

    // 3. Crear copia del PATH para tokenización segura
    path_copy = ft_strdup(path_env);
    if (!path_copy) return NULL;

    // 4. Tokenizar el PATH usando tu función existente
    paths = ft_split(path_copy, ':');
    free(path_copy); // Liberar la copia temporal
    
    if (!paths) return NULL;

    // 5. Buscar en cada directorio del PATH
    for (i = 0; paths[i]; i++) {
        // Construir ruta completa: directorio + "/" + comando
        full_path = ft_strjoin(paths[i], "/");
        if (!full_path) {
            free_array(paths);
            return NULL;
        }
        
        token = full_path;
        full_path = ft_strjoin(full_path, cmd);
        free(token);
        
        if (!full_path) {
            free_array(paths);
            return NULL;
        }
        
        // Verificar si el ejecutable existe
        if (access(full_path, X_OK) == 0) {
            free_array(paths);
            return full_path;
        }
        
        free(full_path);
    }
    
    // 6. Limpieza final
    free_array(paths);
    return NULL;
}
