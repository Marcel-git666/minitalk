/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 17:04:05 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/03 12:41:12 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft/libft.h"

void	send_char(char c, int pid)
{
	int	bit_count;

	bit_count = 0;
	while (bit_count < 8)
	{
		if (c & (1 << bit_count))
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		bit_count++;
		usleep(350);
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc != 3)
	{
		ft_printf("Usage: %s [PID] [message]\n", argv[0]);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid == 0)
	{
		ft_printf("Invalid PID: %s\n", argv[1]);
		return (1);
	}
	ft_printf("Sending message to PID: %d\n", pid);
	message = argv[2];
	while (*message)
	{
		send_char(*message, pid);
		message++;
	}
	send_char('\0', pid);
	return (0);
}
