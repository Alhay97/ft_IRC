#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <string>
#include <fcntl.h>
#include <poll.h>

class Command
{
	protected:
		std::string _name;
		std::string _description;
		std::string _usage;
		bool _is_operational;
		bool _needs_authorization;
		std::map< size_t, std::string > _example;
		Client *_sender;
		Server *_server;
		Message * _message;
		size_t _sender_index;

	public:
		Command();
		virtual 	~Command ();
		std::string 	getName () const;
		std::string 	getDescription () const;
		std::string 	getUsage () const;
		std::map< size_t, std::string > 	getExample () const;
		Client * 	getSender () const;
		void 	setSender (Client *sender);
		void 	setServer (Server *server);
		void 	setMessage (Message *message);
		bool 	hasOpe (void);
		bool 	needsAuth (void);
		virtual void 	execute ()=0;
		virtual bool 	validate (void);
		virtual std::vector< Message > 	parser (Message *message);
		Command ();
		void 	missingOpe (void);


		public:
			virtual void execute();
			std::string getDescription()const;
			std::map<size_t, std::string> getExample()const;
			std::string getName	(		)	const;
			Client* getSender	(		)	const;
			std::string getUsage	(		)	const;
			bool hasOpe(void);
			void missingOpe(void);
			bool needsAuth(void);
			virtual std::vector<Message> parser(Message	*message);
			void setMessage(Message *message);
			void setSender(Client *sender);
			void setServer(Server *server);
			virtual bool validate(void);

};
