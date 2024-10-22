#pragma once
class Node
{
public:
	Node();
	Node(bool v, int s, int e, int b, int i, int d);
	//~Node();  // should NOT have a destructor because nodes in main.cpp will be de-allocated with delete[] 
				// if we create a destructor, the program will try to delete each node twice causing 
				// a breakpoint instruction to be executed

	void Reset(int i);

	// getter methods
	bool Visited();
	int StartDist();
	int EndDist();
	int TotalDist();
	int Backtrace();
	int NodeIndex();
	int NodeData();
	int GetI();
	int GetJ();

	// setter methods
	void SetVisited(bool v);
	void SetStartDist(int s);
	void SetEndDist(int e);
	void SetTotalDist(int s, int e, int d);
	void SetBacktrace(int b);
	void SetNodeIndex(int i);
	void SetNodeData(int d);
	void SetI(int i);
	void SetJ(int j);
private:
	bool visited;
	int startDist; // g(n)
	int endDist; // h(n)
	int totalDist; // f(n) = g(n) + h(n)
	int backtrace;
	int nodeIndex;
	int nodeData;
	int i; // used to construct 2d map grid: map[i][j]
	int j; // used to construct 2d map grid: map[i][j]
};

