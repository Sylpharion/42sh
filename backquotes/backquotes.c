/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backquotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggobin <ggobin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 08:46:16 by ggobin            #+#    #+#             */
/*   Updated: 2017/01/23 11:41:53 by afougere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../sh.h"
#include "backquotes.h"

static void		child(char *old_inner_command, char const *launched_path,
					int *fd)
{
	char		*argv[4];
	extern char **environ;

	argv[0] = ft_strdup("42sh");
	argv[1] = ft_strdup("-c");
	argv[2] = ft_remove_back_quotes(old_inner_command);
	argv[3] = NULL;
	dup2(fd[1], 1);
	close(fd[1]);
	close(fd[0]);
	execve(launched_path, argv, environ);
	exit(0);
}

static char		*father(int *fd, char *old_inner_command, char *cmd)
{
	char	tmp[32];
	char	*new_inner_command;
	char	*res;
	int		ret;

	new_inner_command = ft_strnew(1);
	wait(NULL);
	close(fd[1]);
	while ((ret = read(fd[0], tmp, 31)) != 0)
	{
		if (ret == -1)
			break ;
		tmp[ret] = '\0';
		new_inner_command = ft_strjoin_free(new_inner_command, tmp, 1);
	}
	old_inner_command = ft_strjoin_free("`", old_inner_command, 2);
	if (ft_strcmp(old_inner_command, ft_strchr(cmd, '`') + 1) != 0)
		old_inner_command = ft_strjoin_free(old_inner_command, "`", 1);
	res = ft_replace_str_by_str(cmd, old_inner_command, new_inner_command);
	free(old_inner_command);
	free(new_inner_command);
	close(fd[0]);
	free(fd);
	return (res);
}

char			*ft_exec_back_quotes(char *cmd, char const *launched_path)
{
	int		*fd;
	char	*old_inner_command;
	pid_t	pid;

	fd = (int *)malloc(sizeof(int) * 2);
	pipe(fd);
	old_inner_command = ft_quotes_search(cmd);
	pid = fork();
	if (pid == 0)
		child(old_inner_command, launched_path, fd);
	else if (pid > 0)
		return (father(fd, old_inner_command, cmd));
	return (NULL);
}
