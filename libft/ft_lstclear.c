/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 18:03:24 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 16:59:56 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (!lst || !del)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = temp;
	}
	*lst = NULL;
}

/* int main()
{
    // Creazione di una lista con 3 nodi
    int val1 = 10, val2 = 20, val3 = 30;
    t_list* head = ft_lstnew(&val1);
    head->next = ft_lstnew(&val2);
    t_list* head2 = head->next;
    head2->next = ft_lstnew(&val3);
	while (head->next != NULL)
	{
		printf("%d ->\n", *(int *)head->content);
		head = head -> next;
	}
	// lst = lst1;
	// ft_lstclear(&lst, ft_lstdelete);
	//printf("%s\n fdsgv", (char *)lst->content);
} */