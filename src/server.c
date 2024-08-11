/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:32:07 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/08/11 19:44:30 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void handle_signals(int sig, siginfo_t *info, void *context)
{
	static int cli_pid;
	static int end = 0;
	static char* message;
	char ch;

	// Primer mensaje que recibo o cambio de cliente
	if(!cli_pid || (end && cli_pid != info->si_pid))
		ft_printf("Helllooow\n\n\n");
	ft_printf("%sRecived signal:%s %d from pid[%d]\n", CYAN, RESET, sig, info->si_pid);
	(void)info;
	(void)context;
}

int	main(void)
{
	struct sigaction s_action;
	
	ft_printf("%sWelcome to lua's minitalk server!%s 🦦🔅\n", CYAN, RESET);
	ft_printf("%s\tPID:%s %d\n\n",MAGENTA, RESET, getpid());
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
