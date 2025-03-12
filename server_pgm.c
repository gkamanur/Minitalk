/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_pgm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:47:30 by gkamanur          #+#    #+#             */
/*   Updated: 2025/03/12 16:41:54 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

char   bin2char(int sig_num)
{
    static char char_byte = 0;
    static int i = 0;
    char res;
    
    if (sig_num == SIGUSR1)
        char_byte = (char_byte << 1) | 1;
    else if (sig_num == SIGUSR2)
        char_byte = (char_byte << 1);
    i++;
    if (i == 8)
    {
        res = char_byte;
        char_byte = 0;
        i = 0;
        return(res);
    }
    return (0);
    
}

void    sig_sigusr_serv(int bit, siginfo_t *info, void *dummy)
{
    (void) dummy;
    char c;
    static int pid;
    static int bits_recv = 0;

    if (pid == 0)
        pid = info->si_pid;
    bits_recv++;
    c = bin2char(bit);
    if (c != 0 && bits_recv % 8 == 0)
    {
        if (c == '\0')
        {
            kill(pid, SIGUSR1);
            pid = 0;
            bits_recv = 0;
            return ;
        }
        write (1, &c, 1);
        kill(pid, SIGUSR2);
    }
    // else if (bits_recv % 8 != 0)
    //     kill(pid, SIGUSR2);
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
