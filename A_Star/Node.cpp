#include "Node.h"

Node::Node() {}

Node::Node(bool v, int s, int e, int b, int i, int d)
{
	visited = v;
	startDist = s;
	endDist = e;
	backtrace = b;
	nodeIndex = i;
	nodeData = d;
}

//Node::~Node() { }

bool Node::Visited() { return visited; }
void Node::SetVisited(bool v) { visited = v; }

int Node::StartDist() { return startDist; }
void Node::SetStartDist(int s) { startDist = s; }

int Node::EndDist() { return endDist; }
void Node::SetEndDist(int e) { endDist = e; }

int Node::TotalDist() { return totalDist; }
void Node::SetTotalDist(int s, int e, int d) { totalDist = s + e + d; }

int Node::Backtrace() { return backtrace; }
void Node::SetBacktrace(int b) { backtrace = b; }

int Node::NodeIndex() { return nodeIndex; }
void Node::SetNodeIndex(int i) { nodeIndex = i; }

int Node::NodeData() { return nodeData; }
void Node::SetNodeData(int d) { nodeData = d; }

int Node::GetI() { return i; }
void Node::SetI(int i) { this->i = i; }

int Node::GetJ() { return j; }
void Node::SetJ(int j) { this->j = j; }

void Node::Reset(int i) {
	visited = false;
	startDist = 99999;
	endDist = 99999;
	nodeIndex = i;
	backtrace = 0;
	totalDist = startDist + endDist + nodeData;
}