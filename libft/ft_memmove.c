/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybelhaj <aybelhaj@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 17:26:30 by aybelhaj          #+#    #+#             */
/*   Updated: 2024/09/22 16:57:06 by aybelhaj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h" 

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*local_src;
	unsigned char	*local_dest;
	size_t			i;

	local_src = (unsigned char *)src;
	local_dest = (unsigned char *)dest;
	if (local_src < local_dest)
	{
		while (n--)
			local_dest[n] = local_src[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			local_dest[i] = local_src[i];
			i++;
		}
	}
	return (dest);
}

/*
int main (void)
{
  char d[]= "hola";
  char r[] = "el jo";
  char *res;
  char *res_org;

  res = ft_memmove(d, r , 3);
  printf("resulta:wdo: %s\n",res);
  //res_org = ft_memmove(d, r , -15);
  //printf("resultado org: %s\n",res_org);
  //write(1,res,5);
  return(0);
}*/
