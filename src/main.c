/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ycheroua <ycheroua@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 11:57:40 by ashirzad          #+#    #+#             */
/*   Updated: 2024/06/23 21:20:26 by ycheroua         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <readline/history.h>

void	init_obj(t_obj *obj)
{
	obj->exit_code = 0;
	obj->token = NULL;
	obj->cmd = NULL;
	obj->env = NULL;
}

void	init_env(t_obj *obj, char **env)
{
	while (*env)
	{
		append_env(&obj->env, *env);
		env++;
	}
}

void	init_tool(t_obj *obj)
{
	char	pwd[200];

	getcwd(pwd, 200);
	obj->tool.pwd = ft_strdup(pwd);
	obj->tool.oldpwd = ft_strdup(pwd);
}

void	print_argv(t_cmd *cmd)
{
	t_cmd	*cmd_t;
	t_lexer	*lexer;

	cmd_t = cmd;
	while (cmd_t)
	{
		lexer = cmd_t->lexer;
		int i = 0;
		while (cmd->argv[i])
		{
			printf("%s ", cmd->argv[i]);
			fflush(0);
			i++;
		}
		printf("\n");
		while (lexer)
		{
			printf("fd = %d str = %s\n", lexer->i, lexer->str);
			lexer = lexer->next;		
		}
		cmd_t = cmd_t->next;
	}
}

int	main(int args, char **argv, char **env)
{
	(void)args;
	(void)argv;
	char	*str;
	t_obj	obj;
	// int		pid;

	init_obj(&obj);
	init_env(&obj, env);
	init_tool(&obj);
	// pid = fork();
	// if (pid == 0)
	// {
		while (1)
		{
			str = readline("minishell -> ");
			parsing(&obj, str);
			// print_argv(obj.cmd);
			add_history(str);
			executor(&obj, env);
			free(str);
			free_cmd(&obj.cmd);
		}
	// }
	free_env(&obj.env);
	free(obj.tool.oldpwd);
	free(obj.tool.pwd);
	wait(0);
	return (0);
}
