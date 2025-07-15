/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asmafrid <asmafrid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 16:27:05 by asmafrid          #+#    #+#             */
/*   Updated: 2025/02/04 16:27:07 by asmafrid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 5 && ac != 6)
		return (printf("Args should be like: ./philo 5 800 200 200.\n"));
	if (checking_ar(av))
		return (printf("Invalid Args!\n"));
	data = ft_calloc(1, sizeof(t_data));
	if (data_init(data, ac, av))
		return (1);
	create_philo(data);
	destroy(data);
	return (0);
}
