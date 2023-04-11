#include "Process.hpp"

Process::Process()
{
	
}

Process::~Process()
{

}

Process::Process(string pname)
{
	this->pname = pname;
	this->pid = 1;
	this->ppid = 0;
	this->pstate = "new";
	this->next = 0;
	this->pc = 0;
	this->runtime = 0;

	ifstream	file(pname);
	int	length = 0;				// number of lines in the file(pname)
	string	line;
	
	while (getline(file, line))	// count length
		length++;
	file.clear();
	file.seekg(0, ios::beg);	// reset file stream

	this->code = new string[length];
	for (int i = 0; i < length; i++) {
		this->code[i] = line;
	}
}

int	Process::getPid(void) const
{
	return (this->pid);
}

void	Process::changeState(const string state)
{
	this->pstate = state;
}

void	Process::addNext(Process *next)
{
	this->next = next;
}

Process	*Process::getNext(void) const
{
	return (this->next);
}

void	Process::printInfo(void) const
{
	cout << this->pid << "(" << this->pname << ", " << this->ppid \
		<< ")" << endl;
}

string	Process::readCommand(void)
{
	string	command[2];
	stringstream	ss(this->code[this->pc]);	// temporary command

	ss >> command[0];
	ss >> command[1];

	if (command[0] == "run")
	{
		this->run(command[1]);
		return (command[0]);
	}
	else if (command[0] == "exit")
		return (command[0]);
	return (command[0]);
}

void	Process::run(string arg)
{
	if (runtime == 0)
		this->runtime = stoi(arg);
	this->runtime--;
	if (runtime == 0)
		this->pc++;
}
