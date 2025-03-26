/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 23:24:03 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 16:59:24 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while (tmp)
	{
		f(tmp ->content);
		tmp = tmp->next;
	}
}

/* void ft_deletecont(void *content)
{
	free(content);
}

int main(void)
{
	char *c = ft_strdup("hello");
	t_list	*head = (t_list *)malloc(sizeof(t_list));

	t_list	*second = (t_list *)malloc(sizeof(t_list));
	head -> content = c;
	head -> next = second;
	second -> content = ft_strdup("ciao");
	second -> next = NULL;
	
	t_list	*tmp = head;
	while (tmp -> next != NULL)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp -> next;
	}
	printf("%s\n", (char *)tmp->content);
	ft_lstiter(head, ft_deletecont);
	while (head -> next != NULL)
	{
		printf("%s\n", (char *)head->content);
		head = head->next;
	}
	printf("%s\n", (char *)head->content);	
	printf("finish");
} */