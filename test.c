/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:23:59 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/03 16:29:34 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int main(void)
{
    char *input;

	while (1)
    {
        input = readline("minishell> ");
        if (!input)
        {
            printf("Exit.\n");
            break;
        }
        if (*input)
        {
            add_history(input);
        }
        printf("You entered: %s\n", input);
        free(input);
    }

    return 0;
}