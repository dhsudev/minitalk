/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:32:04 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/08/13 18:43:10 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

void	send_bit(int pid, int bit)
{
	int	sent;

	usleep(300);
	if (bit == 1)
		sent = kill(pid, SIGUSR1);
	else
		sent = kill(pid, SIGUSR2);
	if (sent != 0)
	{
		ft_printf("%sERROR:%s unable to send a signal to the process, ", RED,
			RESET);
		ft_printf("check the PID and if the server is still running please\n");
		exit(1);
	}
	pause();
}

int	send_lenght(int pid, int len)
{
	int	bits;

	bits = sizeof(int) * 8;
	while (bits--)
		send_bit(pid, (len >> bits) & 1);
	return (0);
}

void	send_message(int pid, char *message)
{
	int	i;
	int	bits;

	send_lenght(pid, ft_strlen(message));
	i = 0;
	while (message[i])
	{
		bits = sizeof(char) * 8;
		while (bits--)
			send_bit(pid, (message[i] >> bits) & 1);
		i++;
	}
	bits = sizeof(char) * 8;
	while (bits--)
		send_bit(pid, ('\0' >> bits) & 1);
}

void	received(int sig)
{
	if (sig == SIGUSR1)
	{
		ft_printf("%sClosed connection!%s\n", GREEN, RESET);
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	pid_t	srv_pid;

	if (argc == 3)
	{
		srv_pid = ft_atoi(argv[1]);
		if (!srv_pid)
			ft_printf("%sERROR:%s Wrong PID, check the PID please", RED, RESET);
		else
		{
			ft_printf("%sWelcome to lua's minitalk client! 🦦🔅\n", CYAN, RESET);
			ft_printf("%s\tPID:%s %d\n\n", MAGENTA, RESET, getpid());
			signal(SIGUSR1, received);
			signal(SIGUSR2, received);
			ft_printf("%sSending text.. %s\n", CYAN, RESET);
			send_message(srv_pid, argv[2]);
			return (0);
		}
	}
	else
		ft_printf("%sERROR:%s Invalid arguments, correct syntax is:"
			"\n\n\t./client %s[server PID] %s[message]%s\n\n",
			RED, RESET, YELLOW, CYAN, RESET);
	return (1);
}
