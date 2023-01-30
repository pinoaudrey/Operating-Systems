For this lab, you need to complete the implementation of the signals.c program. This program should count the number of times the user has sent the SIGINT signal to the running process. Pressing Ctl-C from the keyboard send this signal. When the process receives the SIGTSTP signal (Ctl-Z), it should print to the terminal the number of SIGINT signals it has received. After it receives 5 SIGINT signals, the program should prompt the user to exit. If the user does not respond within 3 seconds, an SIGALRM signal should force the program to exit.

An example output of running signals is shown below:

	bash> ./signals 
	^C^C^C^C^C
	Really exit? [Y/n]: n

	Continuing
	^C^C^C^Z

	So far, '3' Ctl-C presses were counted

	^C^Z

	So far, '4' Ctl-C presses were counted

	^C
	Really exit? [Y/n]: n

	Continuing
	^C^C^C^C^C
	Really exit? [Y/n]: 
	User taking too long to respond. Exiting  . . .
