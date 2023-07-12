/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalhamel <aalhamel@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:26:57 by rsaeed            #+#    #+#             */
/*   Updated: 2023/07/09 01:13:28 by aalhamel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Utils.hpp"
#include "iostream"


bool	ft::invalidCharacter( std::string str ) {

	for (int i = 0; str[i] != '\0'; i++)
		if (!isalnum(str[i]) && !isalpha(str[i]))
			return (true);
	return (false);

}

void	ft::errorMessage( std::string function, std::string error ) {

	throw std::runtime_error(function + " " + error);

}


