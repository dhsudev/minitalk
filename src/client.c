/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:32:04 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/08/12 17:19:21 by ltrevin-         ###   ########.fr       */
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
		ft_printf("%sERROR:%s unable to send a signal to the process, ", RED, RESET);
		ft_printf("check the PID and if the server is still running please\n");
		exit(1);
	}
	//ft_printf("%sSending bit:%s %d \n", CYAN, RESET, bit);
	pause();
}

void	send_char(int pid, char ch)
{
	int bits;
	bits = sizeof(char) * 8;
	//ft_printf("%sDebug:%s Sent '%c' to server [%d]\n",YELLOW, RESET, ch, pid);
	while(bits--)
		send_bit(pid, (ch >> bits) & 1);\
}

int	send_lenght(int pid, int len)
{
	int	bits;

	bits = sizeof(int) * 8;
	ft_printf("%sDebug:%s send_lenght(%d, %d) called\n", YELLOW, RESET, pid, len);
	while (bits--)
		send_bit(pid, (len >> bits) & 1);
	return (0);
}

void	send_message(int pid, char *message)
{
	int	i;

	send_lenght(pid, ft_strlen(message));
	i = 0;
	while (message[i])
		send_char(pid, message[i++]);
	send_char(pid, '\0');
}

void recieved(int sig)
{
	static int sent;

	if (sig == SIGUSR1)
	{
		ft_printf("%sMessage sent successfully!%s\n", GREEN, RESET);
		exit(0);
	}
	if (sig == SIGUSR2)
		++sent;
}

int	main(int argc, char **argv)
{
	pid_t	srv_pid;
	
	if (argc == 3)
	{
		srv_pid = ft_atoi(argv[1]);
		if (!srv_pid)
		{
			ft_printf("%sERROR:%s Wrong PID, check the PID please", RED, RESET);
			return (1);
		}
		else
		{
			ft_printf("%sWelcome to lua's minitalk client! 🦦🔅\n", CYAN, RESET);
			ft_printf("%s\tPID:%s %d\n\n",MAGENTA, RESET, getpid());
			signal(SIGUSR1, recieved);
			signal(SIGUSR2, recieved);
			ft_printf("%sSending text.. %s\n", CYAN, RESET);
			send_message(srv_pid, argv[2]);
		}
	}
	else
	{
		ft_printf("%sERROR:%s Invalid arguments, correct syntax is:\n", RED, RESET);
		ft_printf("\n\t./client %s[server PID] %s[message]%s\n\n", YELLOW, CYAN, RESET);
		return (1);
	}
	return (0);
}
