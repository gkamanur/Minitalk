/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 19:17:51 by gkamanur          #+#    #+#             */
/*   Updated: 2025/03/13 20:11:50 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int receive_ind = 0;

void sig_sigusr_client(int bit, siginfo_t *info, void *dummy)
{
    (void)dummy;
    receive_ind = 1;

    if (bit == SIGUSR1)
    {
        ft_putstr_fd("\nMessage acknowledged by server PId:", 1);
        ft_putnbr_fd(info->si_pid, 1);
        write(1, "\n", 1); 
    }
}

void char2bin(int pid, char c)
{
    int bit;
    
    bit = 8;
    while (bit-- > 0)
    {
        if (((c >> bit) & 1) == 1)
            kill(pid, SIGUSR1);
        if (((c >> bit) & 1) == 0)
            kill(pid, SIGUSR2);
        receive_ind = 0;
        while (!receive_ind)
            usleep(500);
    }
}
void    word(const char *str, const int pid)
{
    int i;
    
    i = 0;
    while (str[i] != '\0')
        char2bin(pid, str[i++]);
    char2bin(pid, 0);
}
int main(int ac, char **av)
{
    int pid;
    
    pid = 0;
    if (ac != 3)
    {
        ft_putstr_fd("Give proper argumrnts\n", 1);
        return (1);
    }
    pid = ft_atoi(av[1]);
    if (pid <= 0)
    {
        ft_putstr_fd("Error: Invalid PID\n", 1);
        return (1);
    }
    if (signal_handler(sig_sigusr_client) == -1)
        return(-1);
    word(av[2], pid);
    return (0); 
}
