#include <minitalk.h>

void send_bit(int pid, int bit)
{
	int sent;

	if(bit == 1)
		sent = kill(pid, SIGUSR1);
	else 
		sent = kill(pid, SIGUSR2);
	if(sent != 0)
	{
		ft_printf("ERROR: unable to send a signal to the process, check the PID and if the server is still running please");
		exit(1);
	}
	ft_printf("Sent %d \n", bit);
	usleep(20);
}

void send_char(int pid, char ch)
{
	ft_printf("Debug: Sent '%c' to server [%d]\n", ch, pid);
}

int send_lenght(int pid, int len)
{
	int bits; 
	bits = sizeof(int) * 8;

	ft_printf("Debug: send_lenght(%d, %d) called\n", pid, len);
	while (bits--)
		send_bit(pid, (len >> bits) & 1);
	return (0);
}

void send_message(int pid, char *message)
{
	int i;

	send_lenght(pid, ft_strlen(message));
	i = 0;
	while(message[i])
		send_char(pid, message[i++]);
	send_char(pid, '\0');
}

int	main(int argc, char **argv)
{
	pid_t	srv_pid;

	if (argc == 3)
	{
		srv_pid = ft_atoi(argv[1]);
		if(!srv_pid)
		{
			ft_printf("ERROR: Wrong PID, check the PID please");
			return (1);
		}
		else 
		{
			send_message(srv_pid, argv[2]);
		}
	}
	else
	{
		ft_printf("ERROR: Invalid arguments, correct syntax is:\n\n\t./client [server PID] [message]\n\n");
		return (1);
	}
	return (0);
}
