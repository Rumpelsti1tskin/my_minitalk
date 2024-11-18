/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: surpetro <surpetro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:53:32 by ykisibek          #+#    #+#             */
/*   Updated: 2024/05/04 16:06:26 by surpetro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	number;
	int	sign;

	i = 0;
	sign = 1;
	number = 0;
	while (str[i] == 32 || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		number = 10 * number + (str[i] - '0');
		i++;
	}
	return (sign * number);
}

void	act(int signal)
{
	if (signal == SIGUSR1)
		write(1, "I have received you bit\n", 24);
}

void	ft_send(pid_t pid, int c)
{
	int	bit;

	bit = 7;
	while (bit >= 0)
	{
		if ((c >> bit) & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(100);
		bit--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		i;

	if (argc != 3)
	{
		write(2, "Error\n", 6);
		exit (1);
	}
	else
	{
		i = 0;
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			signal(SIGUSR1, act);
			signal(SIGUSR2, act);
			ft_send(pid, argv[2][i]);
			i++;
		}
		ft_send(pid, '\n');
	}
	return (0);
}
