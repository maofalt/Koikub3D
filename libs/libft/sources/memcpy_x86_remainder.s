/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motero <motero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 14:55:11 by motero            #+#    #+#             */
/*   Updated: 2023/10/18 22:00:40 by motero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

.global memcpy_x86_remainder

// void memcpy_x86_remainder(void** dest, const void** src, size_t remainder);
memcpy_x86_remainder:
    cld
    mov (%rdi), %rdi     
    mov (%rsi), %rsi    
    rep movsb
    ret
