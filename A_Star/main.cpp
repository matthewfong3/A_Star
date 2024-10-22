#include <assert.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "Priority_Queue.h"
#include "Node.h"

using namespace std;

void ReadBinary(const string file, Node* nodes) {
	ifstream inFile(file, ios::binary);

	if (inFile.is_open()) {
		inFile.seekg(0, ios::end);
		int len = (int)inFile.tellg();

		inFile.seekg(0, ios::beg);

		char* fileContents = new char[len + 1];

		inFile.read(fileContents, len);
		fileContents[len] = 0;

		inFile.close();

		cout << fileContents << endl;

		delete[] fileContents;
	}
}

void ReadFile(const string file, Node* nodes) {
	ifstream inFile;
	string line;

	inFile.open(file);

	if (inFile.is_open()) {
		while (getline(inFile, line)) {
			cout << line << endl;
		}
	}

	inFile.close();
}

void ReadStringStream(const string file, Node* nodes) {
	ifstream inFile;
	string line;

	inFile.open(file);

	int offset = 0;

	if (inFile.is_open()) {
		while (getline(inFile, line)) {
			istringstream ss = istringstream(line);
			string s;

			for (int i = 0; i < 5; i++) {
				ss >> s;

				//nodes[i + offset].SetNodeData(stoi(s));
				nodes[i + offset].SetNodeData(stoi(s));
			}

			offset += 5;
		}
	}

	inFile.close();
}

void Create2dGrid(Node* nodes) {
	nodes[0].SetI(0); nodes[0].SetJ(0);
	nodes[1].SetI(0); nodes[1].SetJ(1);
	nodes[2].SetI(0); nodes[2].SetJ(2);
	nodes[3].SetI(0); nodes[3].SetJ(3);
	nodes[4].SetI(0); nodes[4].SetJ(4);

	nodes[5].SetI(1); nodes[5].SetJ(0);
	nodes[6].SetI(1); nodes[6].SetJ(1);
	nodes[7].SetI(1); nodes[7].SetJ(2);
	nodes[8].SetI(1); nodes[8].SetJ(3);
	nodes[9].SetI(1); nodes[9].SetJ(4);

	nodes[10].SetI(2); nodes[10].SetJ(0);
	nodes[11].SetI(2); nodes[11].SetJ(1);
	nodes[12].SetI(2); nodes[12].SetJ(2);
	nodes[13].SetI(2); nodes[13].SetJ(3);
	nodes[14].SetI(2); nodes[14].SetJ(4);

	nodes[15].SetI(3); nodes[15].SetJ(0);
	nodes[16].SetI(3); nodes[16].SetJ(1);
	nodes[17].SetI(3); nodes[17].SetJ(2);
	nodes[18].SetI(3); nodes[18].SetJ(3);
	nodes[19].SetI(3); nodes[19].SetJ(4);

	nodes[20].SetI(4); nodes[20].SetJ(0);
	nodes[21].SetI(4); nodes[21].SetJ(1);
	nodes[22].SetI(4); nodes[22].SetJ(2);
	nodes[23].SetI(4); nodes[23].SetJ(3);
	nodes[24].SetI(4); nodes[24].SetJ(4);
}

void displayMap(Node* nodes) {
	for (int i = 0; i < 25; i++) {
		if (i % 5 == 0) cout << endl;

		if (nodes[i].Visited()) cout << "x ";
		else cout << nodes[i].NodeData() << ' ';
	}
};

void AddNeighbor(Priority_Queue<int, Node>& pq, Node* nodes, int curr, int i, int start, int end) {
	int prevTotalDist = nodes[i].TotalDist();

	nodes[i].SetStartDist(abs(nodes[i].GetI() - nodes[start].GetI()) + abs(nodes[i].GetJ() - nodes[start].GetJ()));
	nodes[i].SetEndDist(abs(nodes[i].GetI() - nodes[end].GetI()) + abs(nodes[i].GetJ() - nodes[end].GetJ()));
	nodes[i].SetTotalDist(nodes[i].StartDist(), nodes[i].EndDist(), nodes[i].NodeData());

	if (!nodes[i].Visited() && nodes[i].TotalDist() < prevTotalDist) {
		nodes[i].SetStartDist(nodes[i].TotalDist());
		nodes[i].SetBacktrace(curr);
		pq.Push(nodes[i].StartDist() , nodes[i]);
	}
}

void PrintBacktrace(Node* nodes, int i) {
	if (nodes[i].Backtrace() == -1) {
		cout << nodes[i].NodeIndex() << endl;
		return;
	}

	cout << nodes[i].NodeIndex() << " -> ";
	PrintBacktrace(nodes, nodes[i].Backtrace());
}

void aStar(Node* nodes) {
	ReadStringStream("map.txt", nodes);

	// g(n) = distance from start node to n
	// h(n) = estimated distance from n to goal
	// nodes are visited in order of least f(n) = g(n) + h(n)

	// initialize a search data table | reset all nodes
	for (int i = 0; i < 25; i++) nodes[i].Reset(i);

	Create2dGrid(nodes);

	// loop through nodes to find the start index and end index
	int startIndex = -1;
	int endIndex = -1;
	for (int i = 0; i < 25; i++) {
		if (nodes[i].NodeData() == 0) {
			if (startIndex == -1) {
				startIndex = nodes[i].NodeIndex();
				continue;
			}
			
			endIndex = nodes[i].NodeIndex();
			nodes[i].SetEndDist(0);
		}
	}

	// Add start node to priority queue
	// key = g(n), start distance
	// value = node itself
	Priority_Queue<int, Node> pq;
	nodes[startIndex].SetBacktrace(-1);
	nodes[startIndex].SetStartDist(0);

	pq.Push(nodes[startIndex].StartDist(), nodes[startIndex]);

	// Remove the next nearest unvisited node from the priority queue
	// If there are no nodes in the priority queue, FAILURE!
	// Print that the goal was not found and exit the function

	int currIndex;
	int leftNeighbor, rightNeighbor, topNeighbor, botNeighbor;

	// loop while there are nodes in priority queue
	while (pq.GetSize() > 0) {
		currIndex = pq.GetValue(0).NodeIndex();

		// check if the algorithm reached the goal
		if (currIndex == endIndex) {
			nodes[currIndex].SetVisited(true);
			displayMap(nodes);
			cout << "\n\naStar Algorithm Success!" << endl;

			// follow trace back and print path
			cout << "\nPrinting trace back path: ";
			PrintBacktrace(nodes, endIndex);
			
			return;
		}

		// get neighbors of current node
		leftNeighbor = currIndex - 1;
		rightNeighbor = currIndex + 1;
		topNeighbor = currIndex - 5;
		botNeighbor = currIndex + 5;
		
		// set current node visited to true and remove from priority queue
		nodes[currIndex].SetVisited(true);
		pq.Pop();
		
		// display the map
		displayMap(nodes);

		// add neighbors to priority queue
		AddNeighbor(pq, nodes, currIndex, leftNeighbor, startIndex, endIndex);
		AddNeighbor(pq, nodes, currIndex, rightNeighbor, startIndex, endIndex);
		AddNeighbor(pq, nodes, currIndex, topNeighbor, startIndex, endIndex);
		AddNeighbor(pq, nodes, currIndex, botNeighbor, startIndex, endIndex);

		// print priority queue 
		cout << "\n" << endl;
		cout << "Printing priority queue: " << endl;
		for (int i = 0; i < pq.GetSize(); i++) {
			cout << "index: " << pq.GetValue(i).NodeIndex() << " | data: " << pq.GetValue(i).NodeData() << " | total dist: " << pq.GetValue(i).TotalDist() << endl;
		}

		// allows user to press enter for next aStar iteration
		cin.get();
		cout << endl;
	}

	// if we ever get here, that means there are no more nodes in priority queue, FAILURE: GOAL WAS NOT FOUND!
	cout << "FAILURE: Goal was not found!" << endl;
}

int main() {
	Node* nodes = new Node[25];

	// Testing Priority_Queue implementation
	Priority_Queue<float, char> minHeap;

	minHeap.Push(4.f, 'a');
	minHeap.Push(1.f, 'b');
	minHeap.Push(3.f, 'c');
	minHeap.Push(2.f, 'd');

	cout << "Printing current priority queue: " << endl;
	for (int i = 0; i < minHeap.GetSize(); i++) {
		cout << minHeap.GetKey(i) << "\t" << minHeap.GetValue(i) << endl;
	}

	cout << endl;

	for(int i = 0; i < minHeap.GetSize(); i++) assert(minHeap.Pop() == static_cast<float>(i+1));

	cout << "Assert: Pop() works correctly!" << endl;

	// Run aStar Algorithm
	aStar(nodes);
	
	delete[] nodes;
	return 0;
}