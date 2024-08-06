#include <minitalk.h>

int main(int argc, char **argv)
{
	pid_t	srv_pid;

	if(argc == 3)
	{
		srv_pid = ft_atoi(argv[1]);
		if(!srv_pid || kill(srv_pid, 0) != 0)
		{
			ft_printf("ERROR: Wrong PID, check if the PID is correct and if the server is still running");
			return(1);
		}
	}
	else 
	{
		ft_printf("ERROR: Invalid arguments, correct syntax is:\n\n\t./client [server PID] [message]\n\n");return(1);
	}
	return(0);
}
