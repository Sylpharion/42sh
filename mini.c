/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afougere <afougere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/12 12:10:43 by afougere          #+#    #+#             */
/*   Updated: 2017/02/05 08:22:57 by ggobin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh.h"
#include "operators.h"
#include "builtins/env.h"

static int		affect_chars(char *src, char *op, int *t)
{
	char	tocmp[5];
	int		i;
	char	*sp;

	i = 1;
	while (++i < 5)
	{
		tocmp[0] = op[t[0]];
		tocmp[1] = op[t[1]];
		tocmp[2] = op[t[2]];
		tocmp[3] = op[t[3]];
		tocmp[i] = '\0';
		if ((tocmp[0] == ' ' && tocmp[3] == ' ' && tocmp[1] == tocmp[2]) ||
			(tocmp[0] == ' ' && tocmp[1] == ' ' && tocmp[2] == tocmp[3]) ||
			(tocmp[2] == ' ' && tocmp[3] == ' ' && tocmp[0] == tocmp[1]))
			continue;
		sp = ft_strchr(tocmp, ' ');
		if (ft_strstr(src, tocmp) != NULL && ((ft_strlen(tocmp) >= 3 && !sp) ||
					(ft_strlen(tocmp) > 3 && sp)))
		{
			ft_putendl_fd("\nparse error", 2);
			return (-1);
		}
	}
	return (0);
}

static int		check_chars(char *src, char *op)
{
	int		t[4];

	t[0] = -1;
	while (op[++t[0]])
	{
		t[1] = -1;
		while (op[++t[1]])
		{
			t[2] = -1;
			while (op[++t[2]])
			{
				t[3] = -1;
				while (op[++t[3]])
					if (affect_chars(src, op, t) == -1)
						return (-1);
			}
		}
	}
	return (0);
}

int				run_once(t_save *save, char **argv)
{
	save->stdout_dup = 1;
	save->termio->uppped = 0;
	save->fail_quotes = 0;
	save->utils->lst = NULL;
	save->termio->heredoc = 0;
	save->termio->quote = 0;
	ft_init_state(save);
	ft_jj(0);
	save->fd = 1;
	save->line = ft_strdup(argv[2]);
	if (save->line && check_chars(save->line, "|&<> ") == 0)
		ft_parse_quotes_and_exec(save, save->termio);
	if (save->line)
		ft_useless_function(save);
	free(save->line);
	return (0);
}

void			run_all(t_save *save)
{
	static int			flg = 1;

	save->use_env_tmp = NO;
	save->stdout_dup = 1;
	save->termio->uppped = 0;
	save->fail_quotes = 0;
	save->utils->lst = NULL;
	save->termio->heredoc = 0;
	save->termio->quote = 0;
	ft_init_state(save);
	ft_jj(0);
	save->fd = 1;
	ft_term(save, save->termio);
	if (save->line && (flg = check_chars(save->line, "|&<> ")) == 0)
		ft_parse_quotes_and_exec(save, save->termio);
	if (save->line)
		ft_useless_function(save);
	if (!flg)
		free(save->termio->save);
	if (save->line == NULL)
	{
		ft_putendl_fd("\nparse error", 2);
		exit(42);
	}
}

int				main(int argc, char **argv, char **envp)
{
	t_save *save;

	signal(SIGINT, sign);
	ft_init_save(&save, argv);
	if (argc && argv)
	{
		if (argc == 3 && !ft_strcmp("-c", argv[1]))
		{
			free(save->termio->prompt);
			save->termio->prompt = ft_strdup("");
		}
		ft_change_env_save(save, envp);
		ft_get_info_env(save->builts);
		if (argc == 3 && !ft_strcmp("-c", argv[1]))
			return (run_once(save, argv));
		while (42)
			run_all(save);
	}
	return (0);
}
