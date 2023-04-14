#ifndef	PROCESS_HPP
#define	PROCESS_HPP

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class	Process
{
	private:
		string	pname;
		int		pid;
		int		ppid;
		string	pstate;	// state of process (new, ready, running, wait, terminate)
		string	*code;
		Process	*next;
		int		pc;
		int		runtime;

	public:
		Process();
		~Process();
		Process(string pname);

		int	getPid(void) const;
		void	changeState(const string state);
		void	addNext(Process *next);
		Process	*getNext(void) const;
		string	getPstate(void) const;
		void	printInfo(void) const; // print "pid(pname, ppid)"
		
		string	readCommand(void);
		void	run(string arg);
};

#endif
