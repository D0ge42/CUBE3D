/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lorenzo <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:27:23 by lorenzo           #+#    #+#             */
/*   Updated: 2024/08/13 18:52:57 by lorenzo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#ifndef BUFFER_SIZE
#define BUFFER_SIZE 1
#endif

static int ft_strchr_gnl(char *str, char c)
{
	int i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return 1;
		i++;
	}
	return 0;
}

char *extract_line(char *stash)
{
  int i = 0;
  while(stash[i] && stash[i] != '\n')
    i++;
  char *line = malloc(sizeof(char) * (i + 2));
  int j = 0;
  while(j < i)
  {
    line[j] = stash[j];
    j++;
  }
  if (stash[i] == '\n')
    line[j++] = '\n';
  line[j] = '\0';
  return line;
}

void update_stash(char *stash)
{
    int i = 0;
    int j = 0;

    while (stash[i] && stash[i] != '\n')
        i++;
    if (stash[i] == '\n')
        i++;
    while (stash[i])
    {
        stash[j] = stash[i];
        i++;
        j++;
    }
  while(stash[j])
  {
    stash[j] = '\0';
    j++;
  }
}

/*Gnl will work like that. We join stash to line each iteration, until there's a new line.
 * If a new line is present we extract it and join it to line.
 * We update the stash and return it.
 * If no new line is present we update stash and call bytes_read.
 * If bytes_read == 0 and line at [0] is NULL we free line and return NULL?
 * else we return line.
 * 
 * Update stash will just shift the stash and fill remaining part with '/0'
 * Extract line is just basic extract line.
 * */

char *get_next_line(int fd)
{
  // error checking
  if (fd < 0 || BUFFER_SIZE <= 0)
    return NULL;
  static char stash[BUFFER_SIZE + 1];
  char *line = NULL;

  stash[BUFFER_SIZE] = '\0';
  while(1)
  {
    if (ft_strchr_gnl(stash,'\n'))
    {
      char *line_to_join = extract_line(stash);
      line = ft_strjoin(line, line_to_join);
      free(line_to_join);
      update_stash(stash);
      return line;
    }
    line = ft_strjoin(line,stash);
    update_stash(stash);
    int bytes_read = read(fd,stash,BUFFER_SIZE);
    if (bytes_read == -1)
    {
      free(line);
      return NULL;
    }
    if (bytes_read == 0)
    {
      if (line[0] == '\0')
      {
        free(line);
        return NULL;
      }
      return line;
    }
  }
}
