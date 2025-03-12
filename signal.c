/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkamanur <gkamanur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:20:35 by gkamanur          #+#    #+#             */
/*   Updated: 2025/03/12 15:29:11 by gkamanur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int signal_handler(void (*handler)(int, siginfo_t *, void *))
{
    struct sigaction sa;
    ft_memset(&sa, 0, sizeof(sa));
    sa.sa_flags = SA_SIGINFO;
    sa.sa_sigaction = handler;

    if ((sigaction(SIGUSR1, &sa, NULL) == -1) ||
        (sigaction(SIGUSR2, &sa, NULL) == -1))
    {
        ft_putstr_fd("Failed to set SIGUSR1/SIGUSR2 handler", 2);
        return (-1);
    }
    return (0);
}

