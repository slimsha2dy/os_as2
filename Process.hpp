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
		string	pstate;	// state of process (new, ready, running, waiting, terminate)
		string	*code;
		Process	*next;
		string	tmpCode;
		int		pc;
		int		runtime;	// remaining time to run
		int		sleeptime;	// remaining time to sleep

	public:
		Process();
		~Process();
		Process(string pname);

		// Process.cpp
		string	readCommand(void);
		void	run(string arg);
		void	exit(void);
		void	sleep(string arg);
		
		// Process_util.cpp
		int		getPid(void) const;
		void	changeState(const string state);
		void	addNext(Process *next);
		Process	*getNext(void) const;	// get next process on queue
		void	printInfo(void) const;	// print "pid(pname, ppid)"
		void	printWait(void) const;	// print "pid(S/W)"
		string	getPstate(void) const;
		string	getCommand(void) const;
		void	subSleep(void);	
		int		getSleep(void);
};

#endif
