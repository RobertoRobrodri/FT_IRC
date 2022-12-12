#ifndef MSG_HPP
#define MSG_HPP

#include "../general/general.hpp"
#include "I_protocols.hpp"

class	msg : public I_protocols
{

	private:
		std::string message;
		int			bytes_recieved;
		std::string cmd[2];

		/*###########################################
		#			CLOSED    	FUNCTIONS			#
		############################################*/
		msg ( std::string str );

	public:

		msg ( void );
		msg ( const msg & var );
		~msg ( void );
		msg &operator=(const msg &tmp);
	
		/*###########################################
		#			PUBLIC	FUNCTIONS				#
		############################################*/
		
		void 	clear_message	(void);
		int		recv_message	(int fd);
		int		send_message	(int fd, std::string str);
		/*###########################################
		#	INTERFACE		PROTOCOL	FUNCTIONS	#
		############################################*/
		void welcome_client	(int fd);
		/*###########################################
		#				GETTERS						#
		############################################*/
		std::string get_message			(void) const {return(this->message);};
		int			get_bytes_recieved	(void) const {return(this->bytes_recieved);};
		/*###########################################
		#				SETTERS						#
		############################################*/
		void set_message		(std::string str) 	{this->message = str;};
		void set_bytes_recieved	(int i) 			{this->bytes_recieved = i;};
};

std::ostream &operator<<(std::ostream& os, const msg &tmp);

#endif
