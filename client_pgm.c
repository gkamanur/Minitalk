/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_pgm.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:17:32 by gkamanur          #+#    #+#             */
/*   Updated: 2025/03/13 20:10:20 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

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
    word(av[2], pid);
    return (0); 
}

