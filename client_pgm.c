/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_pgm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:17:32 by gkamanur          #+#    #+#             */
/*   Updated: 2025/03/12 16:45:28 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int receive_ind = 0;

void    sig_sigusr_client(int bit, siginfo_t *info, void *dummy)
{
    (void) dummy;
    static int i;

    i = 0;
    receive_ind = 1;
    if (bit == SIGUSR1)
        i++;
    else if (bit == SIGUSR2)
    {
        ft_putstr_fd("number of bytes received: ", 1);
        ft_putnbr_fd(i/8, 1);
        ft_putstr_fd("    server-pid: ", 1);
        ft_putnbr_fd(info->si_pid, 1);
    }   
}

void char2bin(int pid, char c)
{
    int bit;
    
    bit = 8;
    while (bit-- > 0)
    {
        if ((c >> bit) & 1)
            kill(pid,SIGUSR1);
        else
            kill(pid,SIGUSR2);
        while (receive_ind == 0)
            sleep (1);
    }
}
int main(int ac, char **av)
{
    int pid;
    int byte;
    
    pid = 0;
    byte = 0;
    if (ac != 3)
    {
        ft_putstr_fd("Give proper argumrnts\n", 1);
        return (1);
    }
    pid = ft_atoi(av[1]);
    if (signal_handler(sig_sigusr_client) == -1)
        return(-1);
    while (av[2][byte] != 0)
        char2bin(pid, av[2][byte++]);
    char2bin(pid, 0);
    return (0); 
}