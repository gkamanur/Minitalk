/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_pgm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:47:30 by gkamanur          #+#    #+#             */
/*   Updated: 2025/03/13 19:59:31 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void bin2char(int sig_num, siginfo_t *info)
{
    static char char_byte = 0;
    static int i = 0;
    static int pid = 0;

    if (pid == 0)
        pid = info->si_pid;
    if (sig_num == SIGUSR1)
        char_byte = (char_byte << 1) | 1;
    else if (sig_num == SIGUSR2)
        char_byte = (char_byte << 1);
    i++;
    if (i == 8)
    {
        if (char_byte == '\0')
        {
            // kill(pid, SIGUSR1);
            pid = 0;
        }
        else
            write(1, &char_byte, 1);
        char_byte = 0;
        i = 0;
    }
    // kill(pid, SIGUSR2);
}

void sig_sigusr_serv(int bit, siginfo_t *info, void *dummy)
{
    (void)dummy;
    bin2char(bit, info);
}

int main()
{
    ft_putstr_fd("server PID : ", 1);
    ft_putnbr_fd(getpid(), 1);
    write(1, "\n", 1);
    if (signal_handler(sig_sigusr_serv) == -1)
        return(-1);
    while (1)
        pause();
    return (0);
}
