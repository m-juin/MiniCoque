# **Minishell**
<img alt="Minishell" src="https://img.shields.io/static/v1?label=Minishell&message=101+/+125&color=gree&style=plastic"/>

# Project
   Minishell is one of the two project in the 42 program fourth circle. This is the first group project of the 42     common core program. In this projects the students need to create their own shell basec on sh.
   # Involved Language(s)
*    <img alt="C_Logo" src="https://upload.wikimedia.org/wikipedia/commons/thumb/archive/3/35/20220802133510%21The_C_Programming_Language_logo.svg/120px-The_C_Programming_Language_logo.svg.png" style="height : 50px;"/>

# Constraint
 According to the subject there only one constraint for this project:
*    The whole files of the projects need to follow 42 norm <a href="https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf">[Link]</a>

#  External Functions Allowed
Here are the external functions allowed for this project:



|             |          |                 |           |                  |                |
| ----------- | -------- | --------------- | --------- | ---------------- | -------------- |
| add_history | printf   | malloc          | fork      | wait             | waitpid        |
| free        | write    | access          | wait3     | wait4            | signal         |
| open        | read     | close           | sigaction | sigemptyset      | sigaddset      |
| kill        | exit     | rl_replace_line | readline  | rl_clear_history | rl_on_new_line |
| getcwd      | chdir    | stat            | lstat     | fstat            | unlink         |
| execve      | dup      | dup2            | pipe      | opendir          | readdir        |
| closedir    | strerror | perror          | isatty    | ttyname          | ttyslot        |
| ioctl       | getenv   | tcsetattr       | tcgetattr | tgetent          | tgetflag       |
| tgetnum     | tgetstr  | tgoto           | tputs     |                  |                |

# Project breakdown
Our group splitted the workload in 2 parts:
*    The input parsing handled by <a href="">GreenPG</a>.
*    The remainings features (creation and/or execution of commands, signal management, etc.) was handled by myself.

# Mandatory Features
In the following array a list of the features requested by the subject:

|       Name       |                                                                   Descripion                                                                    |       status       |
|:----------------:|:-----------------------------------------------------------------------------------------------------------------------------------------------:|:------------------:|
|    **Prompt**    |                                                 Display a prompt when waiting for a new command                                                 | :white_check_mark: |
|   **History**    |                                                          Have a working input history                                                           | :white_check_mark: |
|     **PATH**     |                  Search and launch the right executable (based on the PATH variable or using a relative or an absolute path).                   | :white_check_mark: |
|      **'**       |                                                               Handle single quote                                                               | :white_check_mark: |
|      **"**       |                                                               Handle double quote                                                               | :white_check_mark: |
|      **\|**      |                      The output of each command in the pipeline is connected to the input of the next command via a pipe.                       | :white_check_mark: |
| **Env Variable** |                   Handle environment variables ($ followed by a sequence of characters) which should expand to their values.                    | :white_check_mark: |
|      **$?**      |                                                          Have a working input history                                                           | :white_check_mark: |
|                  |                                                                **Redirections**                                                                 |                    |
|      **<**       |                                                             Should redirect input.                                                              | :white_check_mark: |
|      **<<**      |                                                             Should redirect output.                                                             | :white_check_mark: |
|      **>**       | Should be given a delimiter, then read the input until a line containing the delimiter is seen. However, it doesn’t have to update the history! | :white_check_mark: |
|      **>>**      |                                                     Should redirect output in append mode.                                                      | :white_check_mark: |
|                  |                                                                   **Signaux**                                                                   |                    |
|    **ctrl-C**    |                                                      Displays a new prompt on a new line.                                                       | :white_check_mark: |
|    **ctrl-D**    |                                                                Exits the shell.                                                                 | :white_check_mark: |
|   **ctrl-\\**    |                                                                  Does nothing.                                                                  | :white_check_mark: |
|                  |                                                                  **Builtins**                                                                   |                    |
|     **echo**     |                                                               echo with option -n                                                               | :white_check_mark: |
|      **cd**      |                                                    cd with only a relative or absolute path                                                     | :white_check_mark: |
|     **pwd**      |                                                               pwd with no options                                                               | :white_check_mark: |
|    **export**    |                                                             export with no options                                                              | :white_check_mark: |
|    **unset**     |                                                              unset with no options                                                              | :white_check_mark: |
|     **env**      |                                                        env with no options or arguments                                                         | :white_check_mark: |
|     **exit**     |                                                              exit with no options                                                               | :white_check_mark: |

</details>

# Bonus Features
In the following array a list of the bonus features requested by the subject:

|  Name   |                                                  Descripion                                                  |       status       |
|:-------:|:------------------------------------------------------------------------------------------------------------:|:------------------:|
| **&&**  |                              With parenthesis for priorities.                                                | :x: |
| **\|\|** |                                         With parenthesis for priorities                                     | :x: |
| **Wildcards** |                                         Should work for the current working directory.                                     | :x: |

</details>

# Usage

``make`` to compile.

``clean`` to clean all compiled file without the library file.

``fclean`` to clean all compiled file with the library file.

``re`` to fclean then make.
