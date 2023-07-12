/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhamel <aalhamel@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:27:04 by rsaeed            #+#    #+#             */
/*   Updated: 2023/07/11 14:42:22 by aalhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef UTILS_HPP
# define UTILS_HPP

#define RESET "\e[0m"
#define BGRN "\e[1;32m"
#include <iostream>

namespace ft
{

	bool	invalidCharacter( std::string str );

	void	errorMessage( std::string function,	std::string error );

}

#endif
