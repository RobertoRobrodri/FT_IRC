/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortiz-d <mortiz-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 13:06:53 by mortiz-d          #+#    #+#             */
/*   Updated: 2022/12/14 16:45:23 by mortiz-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.hpp"

/*###########################################
#	INTERFACE		PROTOCOL	FUNCTIONS	#
############################################*/

void server::welcome_client(int fd)
{
	std::string rp1 = "Welcome to the Network, please set up ur NICK and USER first\n";
	this->msg.send_message(fd,rp1);
	return;
}

void server::extract_NICK	(int i , std::string str)
{
	std::vector <std::string>	line;
	int aux;

	aux = find_single_word_on_str(str , NICKNAME);
	if (aux != -1)
	{
		line = split_in_vector(&str[aux],' ');
		if ( line.size() >= 2)
		{
			line[1].erase(line[1].find_last_not_of(" \n\r\t")+1);
			this->clients[i].setnick(line[1]);
			this->msg.send_message(this->fds[i].fd,"Server : NICK successfully established\n");
		}
		else
		{
			this->msg.send_message(this->fds[i].fd,"Server : Not enought args to set up NICK\n");
			std::cout << "Server : Not enough args to set up NICK for client["<<i<<"]" << std::endl;
		}
	}
  
	return;
}

//BASED ON  -> USER <username> <hostname> <servername> <realname> (RFC 1459)
void server::extract_USERNAME	(int i , std::string str)
{
	std::vector <std::string>	line;
	std::vector <std::string>	line2;
	int aux;

	aux = find_single_word_on_str(str , USERNAME);
	if (aux != -1)
	{
		line = split_in_vector(&str[aux],' ');
		line2 = split_in_vector(&str[aux],':');
		if ( line.size() >= 5 && line2.size() == 2)
		{
			line[1].erase(line[1].find_last_not_of(" \n\r\t")+1);
			this->clients[i].setusername_host(line[1]);
			line2[1].erase(line2[1].find_last_not_of("\n\r\t")+1);
			this->clients[i].setrealname_host(line2[1]);
			this->msg.send_message(this->fds[i].fd,"Server : USER set up " + this->clients[i].getusername_host() + " - " + this->clients[i].getrealname_host() + "\n" );
		}
		else
		{
			this->msg.send_message(this->fds[i].fd,"Server : Can not set up USER\n");
			std::cout << "Server : Could not to set up USER for client["<<i<<"]" << std::endl;
		}
			
	}
  
  	return;
}

void server::extract_MSG	(int i , std::string str)
{
	std::string str_aux;
	int aux;
	
	aux = find_single_word_on_str(this->msg.get_message() , MESSAGE);
	str = this->msg.get_message();
	if (aux != -1)
	{
		
		str_aux = this->msg.get_message();
		this->msg.set_message(clients[i].getnick() + ":" + &str[aux + 4]);
		if (clients[i].getnick() != "" )
			this->msg_to_all(i);
		else
		{
			this->msg.send_message(this->fds[i].fd,"Server : Set up ur NICK first before sending an MSG\n");
			std::cout << "Server : client["<<i<<"] couldnt send an MSG beacuse his NICK isnt set up" << std::endl;
		}
		this->msg.set_message(str_aux.erase(aux , str_aux.length()));
	}
  return;
}
