//Group Members:
//Tse Man Kit


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string>
#include <cstring>
#include <list>
#include <algorithm>
#include <sys/wait.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

typedef struct h{
	string c;
	float t;
}h;


bool compare (const h &,const h&);

int main(){
	pid_t pid;
	list<h>l;
	while(true){
		cout<<"tinyshell>";
		char input[256];
		cin.getline(input,sizeof(input));
		string s=input;
		string ns=s;
		ns.erase(remove_if(ns.begin(),ns.end(),::isspace), ns.end());
		high_resolution_clock::time_point t1= high_resolution_clock::now();
		if (ns=="exit"){exit(0);}
		else if (ns=="history"){
			list<h>::iterator itr;
			for (itr=l.begin();itr!=l.end();itr++){
				cout<<itr->c<<"  "<<itr->t<<"s"<<endl;
			}			
		}//history
		else if (ns=="history-sbu" && s!="history-sbu"){
			list<h>l1(l);
			l1.sort(compare);
			list<h>::iterator itr1;
			for (itr1=l1.begin();itr1!=l1.end();itr1++){
				cout<<itr1->c<<"  "<<itr1->t<<"s"<<endl;
			}			
		}//-sbu
		else{
			const char* command=s.c_str();
			pid = fork();//start of fork()
			if(pid == 0){system(command);exit(0);}//in child
			else if (pid>0) {waitpid(pid,NULL,0);}//in parent, wait for child
			else {return 1;}//if fork fails
		}	
		high_resolution_clock::time_point t2= high_resolution_clock::now();
		double time=duration_cast<milliseconds>(t2-t1).count();
		h newcommand;
		newcommand.c=s;
		if(time==0){newcommand.t=0.001;}
		else{newcommand.t=time/1000.000;}
		if(l.size()==5){l.pop_back();}
		l.push_front(newcommand);
	}//endwhileloop
	
}

bool compare (const h &a,const h& b){
	return a.t>b.t;
}

