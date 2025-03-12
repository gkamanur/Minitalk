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
#include "time.h"
#include <stdio.h>

static int receive_ind = 0;

void precise_sleep(int microseconds)
{
    struct timespec ts;
    ts.tv_sec = microseconds / 1000000;         // Convert to seconds
    ts.tv_nsec = (microseconds % 1000000) * 1000;  // Convert remaining microseconds to nanoseconds
    nanosleep(&ts, NULL);
}

void sig_sigusr_client(int bit, siginfo_t *info, void *dummy)
{
    (void)dummy;
    receive_ind = 1;

    if (bit == SIGUSR1)
    {
        ft_putstr_fd("\nMessage acknowledged by server!\n", 1);
    }
}

// void    sig_sigusr_client(int bit, siginfo_t *info, void *dummy)
// {
//     (void) dummy;
//     static int i;

//     i = 0;
//     receive_ind = 1;
//     if (bit == SIGUSR2)
//         i++;
//     else if (bit == SIGUSR1)
//     {
//         ft_putstr_fd("number of bytes received: ", 1);
//         ft_putnbr_fd(i/8, 1);
//         ft_putstr_fd("    server-pid: ", 1);
//         ft_putnbr_fd(info->si_pid, 1);
//         i = 0;
//     }   
// }

void char2bin(int pid, char c)
{
    int bit;
    
    bit = 8;
    while (bit-- > 0)
    {
        if ((c >> bit) & 1)
            kill(pid, SIGUSR1);
        else
            kill(pid, SIGUSR2);
        receive_ind = 0;
        while (!receive_ind)
            sleep(1);
    }
}
// void char2bin(int pid, char c)
// {
//     int bit = 8;

//     while (bit-- > 0)
//     {
//         if ((c >> bit) & 1)
//         {
//             if (kill(pid, SIGUSR1) == -1)
//             {
//                 perror("kill");
//                 exit(EXIT_FAILURE);
//             }
//         }
//         else
//         {
//             if (kill(pid, SIGUSR2) == -1)
//             {
//                 perror("kill");
//                 exit(EXIT_FAILURE);
//             }
//         }
//         receive_ind = 0;
//         while (receive_ind == 0)
//             precise_sleep(100);
//     }
// }

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
    if (pid <= 0)
    {
        ft_putstr_fd("Error: Invalid PID\n", 1);
        return (1);
    }
    if (signal_handler(sig_sigusr_client) == -1)
        return(-1);
    while (av[2][byte] != '\0')
    {
        char2bin(pid, av[2][byte]);
        byte++;
    }
    char2bin(pid, 0);
    return (0); 
}
