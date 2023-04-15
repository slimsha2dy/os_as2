#ifndef	KERNEL_HPP
#define	KERNEL_HPP

#include "Process.hpp"

class	Kernel
{
	private:
		Process	*headRq;	// head of readyqueue
		Process	*tailRq;	// tail of readyqueue
		Process	*headWq;	// head of waiting queue
		Process	*tailWq;	// tail of waiting queue
		Process	*tmp;		// running program on CPU
		Process	*newProcess;	// new process in cycle
		Process	*terProcess;	// terminated process in cycle

		string	mode;		// kernel/user
		string	kstate;		// state of kernel (boot, system call, schedule, idle)
		bool	syscallFlag;	// if process call syscall
		string	syscallCommand;	// syscall command
		int		last_pid;
		bool	allExit;	// if all processes exited

	public:
		Kernel(string pname);
		~Kernel(void);

		// Kernel.cpp
		void	checkSyscall(void);	// check if user call syscall
		void	updateState(void);	// 2. update processes state
		void	updateRq(void);		// 3. update readyqueue
		void	excute(void);		// 4. excute command
		void	scheduleIdle(void);	// excute scheduler or idle
		void	syscall(void);

		// Kernel_util.cpp
		void	changeKstate(const string kstate);
		bool	getSysflag(void) const;
		bool	getallExit(void) const;
		void	printState(void) const;	// 5. print state
		void	pushRq(Process *p);
		Process	*popRq(void);
};

#endif
