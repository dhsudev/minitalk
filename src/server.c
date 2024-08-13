/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:32:07 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/08/13 18:41:52 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	handle_char(t_info *data)
{
	if (data->ch == '\0')
	{
		ft_printf("%sNew message!%s %s\n", BLUE, RESET, data->message);
		free(data->message);
		data->msg_pos = 0;
		data->bytes = 0;
		data->bits = 0;
		kill(data->cli_pid, SIGUSR1);
	}
	else
	{
		data->message[data->msg_pos] = data->ch;
		data->bits = 0;
		data->msg_pos++;
	}
}

void	save_length(t_info *data, int sig)
{
	data->len |= (sig == SIGUSR1);
	if (data->bits == 8)
	{
		data->bytes++;
		data->bits = 0;
	}
	if (data->bytes == sizeof(int))
	{
		data->message = malloc(sizeof(char) * (data->len + 1));
		if (!data->message)
		{
			ft_printf("%sError:%s problem allocating memory", RED, RESET);
			exit(1);
		}
		data->message[data->len] = '\0';
	}
	data->len <<= 1;
}

void	reset_info_struct(t_info *data, int pid)
{
	data->cli_pid = pid;
	data->bytes = 0;
	data->bits = 0;
	data->len = 0;
}

void	handle_signals(int sig, siginfo_t *info, void *context)
{
	static t_info	data;

	if (!data.cli_pid || (data.bytes == 0 && data.cli_pid != info->si_pid))
		reset_info_struct(&data, info->si_pid);
	if (data.cli_pid != info->si_pid)
	{
		kill(info->si_pid, SIGUSR1);
		return ((void)context);
	}
	data.bits++;
	if (data.bytes < sizeof(int))
		save_length(&data, sig);
	else
	{
		data.ch |= (sig == SIGUSR1);
		if (data.bits == 8)
		{
			data.bytes++;
			data.bits = 0;
			handle_char(&data);
		}
		data.ch <<= 1;
	}
	kill(data.cli_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	s_action;

	ft_printf("%sWelcome to lua's minitalk server!%s 🦦🔅\n", CYAN, RESET);
	ft_printf("%s\tPID:%s %d\n\n", MAGENTA, RESET, getpid());
	s_action.sa_sigaction = handle_signals;
	sigemptyset(&s_action.sa_mask);
	s_action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &s_action, 0);
	sigaction(SIGUSR2, &s_action, 0);
	while (1)
	{
		pause();
	}
}
