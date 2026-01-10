/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 17:59:19 by joesanto          #+#    #+#             */
/*   Updated: 2026/01/10 19:14:47 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	main(void)
{
	int	age;

	printf("Put your age: ");
	scanf("%d", &age);
	printf("You will be %d years old in 10 years", age + 10);
	return (0);
}
