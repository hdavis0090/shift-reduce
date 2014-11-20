#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<cctype>
#include<stack>
#include<queue>
using namespace std;


void printStack(stack<int> pstack)
{
	char c;
	cout<<"Current contents : ";
	while(!pstack.empty())
	{
		if(pstack.top()>11) {
			c = pstack.top();
			cout<<c;
		}
		else
			cout<<pstack.top();
		pstack.pop();

	}
	cout<<endl;
}

void printQueue(queue<char> pqueue)
{
	cout<<"Current input : ";
	while(!pqueue.empty())
	{
		cout<<pqueue.front();
		pqueue.pop();
	}
	cout<<endl;
}
	
int checkAction(char c) {
	switch(c) {
		case 'i':
			return 0;
		case '+':
			return 1;
		case '*':
			return 2;
		case '(':
			return 3;
		case ')':
			return 4;
		case '$':
			return 5;
		}
}

int checkGoto(int i) {
	char c = i;
	switch(c) {
		case 'E':
			return 0;
		case 'T':
			return 1;
		case 'F':
			return 2;
		}
}
	
int main() {

	queue<char> input;
	char in[256];
	int flag = 0;
	while(1) {
		cout<<"Input your expression or 'E' to exit :"<<endl;
		
		cin.getline(in, 256);
		if(in[0] == 'E')
			exit(0);
		
		//push input into queue
		int i=0;
		while(in[i] != '\0')
		{

			if((int)in[i]>96 && (int)in[i]<123) 
				input.push('i');
			else if(in[i] == ' ')
			{
				
			}
			else if(in[i]>35 && in[i]<44)
				input.push(in[i]);
			else {
				flag=1;
			}

			i++;
		}

		
		//generate action table
		string atable[12][6] = {"eee"};
		atable[0][0]="s5";
		atable[0][3]="s4";
		atable[1][1]="s6";
		atable[1][5]="C";
		atable[2][1]="r2";
		atable[2][2]="s7";
		atable[2][4]="r2";
		atable[2][5]="r2";
		atable[3][1]="r4";
		atable[3][2]="r4";
		atable[3][4]="r4";
		atable[3][5]="r4";
		atable[4][0]="s5";
		atable[4][3]="s4";
		atable[5][1]="r6";
		atable[5][2]="r6";
		atable[5][4]="r6";
		atable[5][5]="r6";
		atable[6][0]="s5";
		atable[6][3]="s4";
		atable[7][0]="s5";
		atable[7][3]="s4";
		atable[8][1]="s6";
		atable[8][4]="s11";
		atable[9][1]="r1";
		atable[9][2]="s7";
		atable[9][4]="r1";
		atable[9][5]="r1";
		atable[10][1]="r3";
		atable[10][2]="r3";
		atable[10][4]="r3";
		atable[10][5]="r3";
		atable[11][1]="r5";
		atable[11][2]="r5";
		atable[11][4]="r5";
		atable[11][5]="r5";
		
		//generate goto table
		int gtable[11][3];
		gtable[0][0]=1;
		gtable[0][1]=2;
		gtable[0][2]=3;
		gtable[4][0]=8;
		gtable[4][1]=2;
		gtable[4][2]=3;
		gtable[6][1]=9;
		gtable[6][2]=3;
		gtable[7][2]=10;
		
		//apply main shift reduce algorithm
		stack<int> parse;	

		int state;
		int rowNum;
		int ruleNum=0;
		char c;
		string direction;
		
		//push initial state
		parse.push(0);
		while(1)
		{
			//check input errors
			if(flag==1) {
				if(!input.empty())
					input.pop();
				cout<<"Invalid input"<<endl<<endl;
				break;
			}
			printStack(parse);
			printQueue(input);
			
			//set state and find table info
			state = parse.top();
			rowNum = checkAction(input.front());
			direction = atable[state][rowNum];
			cout<<"Direction: "<<direction.c_str()<<endl<<endl;
			
			//check table for entry
			if(direction[0] == '\0') {
				cout<<"Error: No entry at "<<state<<", "<<rowNum<<endl;
				break;
				}
				
			//exit condition
			if(direction.compare("C") ==0)
				{
					cout<<"ACCEPTED"<<endl;
					input.pop();
					break;
				}
			c = direction[1];
			
			//check if shift or reduce
			if(direction[0]=='s') //shift
			{
				parse.push((int)input.front());
				if(direction.compare("s11") ==0)
				{
					
				}
				else
					parse.push((int)c-48);
				input.pop();
			}
			else if(direction[0]=='r') //reduce
			{
				//find which grammar rule to use
				ruleNum = c-48;
				switch(ruleNum) {
					case 1:
						parse.pop();
						parse.pop();
						parse.pop();
						parse.pop();
						parse.pop();
						parse.pop();
						state = parse.top();
						parse.push('E');
						break;
					case 2:
						parse.pop();
						parse.pop();
						state = parse.top();
						parse.push('E');
						break;
					case 3:
						parse.pop();
						parse.pop();
						parse.pop();
						parse.pop();
						parse.pop();
						parse.pop();
						state = parse.top();
						parse.push('T');
						break;
					case 4:
						parse.pop();
						parse.pop();
						state = parse.top();
						parse.push('T');
						break;
					case 5:
						parse.pop();
						parse.pop();
						parse.pop();
						parse.pop();
						parse.pop();
						parse.pop();
						state = parse.top();
						parse.push('F');
						break;
					case 6:
						parse.pop();
						parse.pop();
						state = parse.top();
						parse.push('F');
						break;
					}
				//check go to
				rowNum = checkGoto(parse.top());
				parse.push(gtable[state][rowNum]);
				
			}
		}
		cout<<endl<<endl;
	}	
}