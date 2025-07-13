
# TODO:

[ ] Expansor
[ ] Comillas
[ ] builtins
    [ ]

# DONE
[x] env compiler to arr, str
[x] env -i

## Expansor y comillas
[ ] Estudiar lexer, estructura de parseo, algoritmo de agrupacion y 
    logica de rollback - Binary tree?
[ ] Expansor de variable

## BUILTINS -- UNSET
    Coge todas las args validas y las borra.
### CASOS

    - export ABC=123 | unset ABC | env
    bash output: env print sin ABC
    - export ABC=123 | env
    bash output: env print sin ABC
    - export ABC=123 | env | unset ABC
    bash output: NO PRINT

## ENV -i
no lo pide el subject, se considera nulo

# LINKS

-   https://aosabook.org/en/v1/bash.html
    Chet Ramey very goated explanation of bash parsing
[ ]     very cool, very good

-   https://mywiki.wooledge.org/bashparser
[ ]     To understand the way Bash processes the input

-   https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218
    Dev diary of his approach when doing minishell, guide and steps of study and dev
[ ]     REFERENCE: [SHUNTING YARD ALGORITHM]

-   https://explainshell.com/
    Tool to understand the semantic of bash, after introducing a line, does not 
    go into detail for precedence

-   https://en.wikipedia.org/wiki/Bourne_shell
[ ]     Understanding of the bourne shell def and scope

-   https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J
    Minishell study case that exemplifies the programs routine

-   https://www.youtube.com/watch?v=ubt-UjcQUYg&list=PLbtzT1TYeoMhF4hcpEiCsOeN13zqrzBJq&index=1
    Similar exercise of recreating a shell, explained. Exemple of 430 lines of code

-   https://medium.com/@oduwoledare/42-minitalk-explained-5b236adc2c24
    Minitalk brief to understand logic of signals

-   https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005fon_005fnew_005fline
    readline function documentation

-   https://matklad.github.io/2020/04/13/simple-but-powerful-pratt-parsing.html
    Pratt parsing, because sounds fun
