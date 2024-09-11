/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:34:40 by labdello          #+#    #+#             */
/*   Updated: 2024/09/09 18:19:41 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(void)
{
	char	cwd_buffer[PATH_MAX];

	getcwd(cwd_buffer, sizeof(cwd_buffer));
	ft_putendl_fd(cwd_buffer, 1);
	return (0);
}
