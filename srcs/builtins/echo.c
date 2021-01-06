/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m4nu </var/spool/mail/m4nu>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 16:31:05 by m4nu              #+#    #+#             */
/*   Updated: 2021/01/06 16:31:29 by m4nu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int ft_echo(char **args)
{
	int i;
	int option_n;


	i = 1;
	option_n = 0;
	if (args_number(args) > 1)
	{
		while (args[i] != 0 && ft_strcmp(args[i], "-n") == 0)
		{
			option_n = 1;
			i++;
		}
		while (args[i])
		{
			ft_putstr_fd(args[i], 1);
			if (args[i + 1] && args[i][0] != '\0')
				write(1, " ", 1);
			i++;
		}
	}
	if (option_n == 0)
		write(1, "\n", 1);
	return (1);
}
