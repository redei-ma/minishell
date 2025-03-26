/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:01:43 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 16:59:53 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst || !del)
		return ;
	(del)(lst->content);
	free(lst);
}

/* int main()
{
	t_list	*lst;
	lst = malloc(1 * sizeof(t_list));
	char	c[5] = "ciao";
	lst->content = malloc(5 * sizeof(char));
	if (lst->content == NULL)
		free(lst);
    ft_strlcpy(lst->content ,"ciao", 5);
	lst->next = NULL;
	printf("%s\n", (char *)lst->content);
	ft_lstdelone(lst, ft_lstdelete);
	printf("%s\n fdsgv", (char *)lst->content);
} */