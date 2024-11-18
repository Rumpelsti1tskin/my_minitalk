/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykisibek <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:53:44 by ykisibek          #+#    #+#             */
/*   Updated: 2024/04/21 16:53:48 by ykisibek         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	ft_count(int n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n / 10 > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

int	ft_printint(int n)
{
	char	num;
	int		count;

	num = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	count = ft_count(n);
	if (-2147483648 < n && n <= 2147483647)
	{
		if (n < 0)
		{
			write(1, "-", 1);
			n = -n;
		}
		if (n / 10 != 0)
			ft_printint(n / 10);
		num = n % 10 + '0';
		write(1, &num, 1);
	}
	return (count);
}

void	getbits(int signal, siginfo_t *siginfo, void *s)
{
	static int	c;
	static int	count;

	(void)s;
	c = (signal & 1) | c;
	count++;
	if (count == 8)
	{
		write(1, &c, 1);
		c = 0;
		count = 0;
		kill(siginfo->si_pid, SIGUSR1);
	}
	else
		c = c << 1;
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	write(1, "pid = ", 6);
	ft_printint(pid);
	write(1, "\n", 1);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = getbits;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
}
