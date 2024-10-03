/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmravec <mmravec@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 10:43:50 by mmravec           #+#    #+#             */
/*   Updated: 2024/10/03 09:48:16 by mmravec          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "ft_printf.h"
#include "libft/libft.h"

void	sigusr_handler(int signum, siginfo_t *info, void *context)
{
	static int				bit_count = 0;
	static unsigned char	character = 0;

	(void)info;
	(void)context;
	if (signum == SIGUSR2)
		character |= (1 << bit_count);
	bit_count++;
	if (bit_count == 8)
	{
		if (character == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", character);
		bit_count = 0;
		character = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = sigusr_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("Server running. PID: %d\n", getpid());
	while (1)
		usleep(500);
	return (0);
}