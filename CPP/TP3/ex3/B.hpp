#ifndef B_H
#define B_H

class A;
class B
{
	private:
		int j;
	public:
		B(int k = 0);
		void send(A * a);
		void exec(int k);
	
};

#endif