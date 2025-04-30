/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:26:56 by lorenzo           #+#    #+#             */
/*   Updated: 2024/08/13 18:26:58 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strjoin(const char *line, const char *stash)
{
  int len_line = ft_strlen(line);
  int len_stash = ft_strlen(stash);

  int total = len_line + len_stash + 1;

  char *dest = malloc(sizeof(char) * total);
  int i = 0;
  int j = 0;
  while(line && line[i])
  {
    dest[j] = line[i];
    i++;
    j++;
  }
  i = 0;
  while(stash && stash[i])
  {
    dest[j] = stash[i];
    i++;
    j++;
  }
  free((char *)line);
  dest[j] = '\0';
  return dest;
}

/*int main()
{
	printf("%s\n", ft_strjoin("ciao", "bello"));
}*/
