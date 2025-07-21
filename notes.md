
# TODO:

[ ] Expansor
[ ] Comillas
[ ] builtins
    [ ]

# DONE
[x] env compiler to arr, str
[x] env -i

## Expansor y comillas
[ ] Expansor de variable

[ ] Parse the command line: Separate between operators and words
[ ] Handle quote rules to define

Handle quotes (preserve tokens).

Expand variables.

Remove quotes.

### Quote parsing
    Quotes devuelven una nueva linea de tipo word, operadores seran considerados
    words

ex: "ls | ls": command not found

## BUILTINS -- UNSET
    Coge todas las args validas y las borra.

### CASOS

    - export ABC=123 | unset ABC | env
    bash output: env print sin ABC
    - export ABC=123 | env
    bash output: env print sin ABC
    - export ABC=123 | env | unset ABC
    bash output: NO PRINT
    - export ABC=123 | echo $ABC
    bash output: \n

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

;
p;Great question — and your comment in the code hints at the right idea. The best point to expand environment variables depends on **what stage of processing** you're at and **what type of structure** you’re working with. Let’s walk through this step by step:

---

### 🔁 What each function likely does:

```c
shell->tokens = tokenize_line(*line);
```

* This breaks the raw line into tokens — possibly separating commands, arguments, operators (`|`, `&&`, etc).

```c
syntax_check(shell->tokens)
```

* Ensures the tokens form a valid shell syntax.

```c
parse_tokens(shell, shell->tokens, &shell->cmd)
```

* Converts the tokens into a structured command list (`t_cmd` tree or array).

```c
expand_variables(shell, shell->cmd)
```

* Replaces `$VAR`, `$?`, etc., with their actual values **inside the parsed command structure**.

---

### ✅ Correct stage for env variable expansion:

Environment variable expansion (e.g., turning `$HOME` into `/home/user`) **should** happen **after** tokenizing **and** parsing — **exactly where you have it now**.

That’s because:

* Tokenizing and parsing need to understand **quoted strings** (`"$HOME"` vs `$HOME`) and **operators** — so doing expansion too early might mess up parsing.
* After parsing, you have a structured representation (`shell->cmd`) where arguments and strings are clearly identified, and variable expansion can be done precisely.

---

### 🧠 Why not earlier?

* If you expand variables **before parsing**, you risk:

  * Breaking quotes incorrectly.
  * Interpreting special characters wrongly (e.g., `$HOME*` could turn into `"/home/user/*"` and confuse the tokenizer).
  * Losing the structure needed to decide whether expansion should even occur (e.g., variables in single quotes shouldn’t be expanded).

---

### ✅ Conclusion

You're already doing the expansion in the correct spot:

```c
if (parse_tokens(shell, shell->tokens, &shell->cmd))
    return (0);
if (expand_variables(shell, shell->cmd)) // Correct place
    return (0);
```

This is ideal, since:

* You only expand once you're sure parsing succeeded.
* Tokens aren’t needed anymore.
* Your command structure is clean and safe to modify.

If you want to be even cleaner, you could consider **freeing the tokens** right after expansion starts, if you don’t need them anymore.

Let me know if you want help optimizing or cleaning up this pipeline!










==============================================================================
tester:

Test   1: ❌ echo hello world 
mini output = ()
bash output = (hello world)
mini exit code =
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test   2: ❌ echo "hello world" 
mini output = ()
bash output = (hello world)
mini exit code =
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test   3: ❌ echo 'hello world' 
mini output = ()
bash output = (hello world)
mini exit code =
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test   4: ❌ echo hello'world' 
mini output = ()
bash output = (helloworld)
mini exit code =
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test   5: ❌ echo hello""world 
mini output = ()
bash output = (helloworld)
mini exit code =
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test   6: ❌ echo '' 
mini exit code =
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test   7: ❌ echo "$PWD" 
mini output = ()
bash output = (/home/aybelhaj/minishell/minishell_tester)
mini exit code =
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()
Test   8: ❌ echo '$PWD' 
mini output = ()
bash output = ($PWD)
mini exit code =
bash exit code = 0
mini error = ( No such file or directory)
bash error = ()


