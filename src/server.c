/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ltrevin- <ltrevin-@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:32:07 by ltrevin-          #+#    #+#             */
/*   Updated: 2024/08/08 15:32:55 by ltrevin-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minitalk.h>

int	main(void)
{
	ft_printf("Welcome to lua's minitalk! 🦦🔅\n");
	ft_printf("\tPID: %d\n", getpid());
	while (1)
		pause();
}
