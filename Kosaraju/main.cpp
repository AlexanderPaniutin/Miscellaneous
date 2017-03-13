#include <iostream>
#include <list>
#include <map>
#include <vector>
#include <fstream>
#include <chrono>

// answer is 434821, 968, 459, 313, 211

using namespace std;

// main graph node
class GraphNode {
 public:
  GraphNode(int val): value(val), visited(false) {};
  int value;
  list<int> outArcs;
  bool visited;
};

// will store the input array
typedef list<pair<int, int>> InputStorageType;
InputStorageType mainInputStorage;
// will store number - graph node
typedef map<int, GraphNode *> GraphType;
GraphType revGraph;
GraphType graph;
// will store values from 1 to max
list<int> nodeValues;

#define DATA_FILE_PATH "/Users/alex.paniutin/Documents/Study/GitHub/Algorithms/Other/"

bool readInputFile(const char *fname, InputStorageType &storage);
bool buildGraph(InputStorageType &storage, GraphType &graph);
bool buildRevGraph(InputStorageType &storage, GraphType &graph);
void printGraph(GraphType &graph);

GraphNode *findUnvisited(GraphType &revGraph);
bool buildNodesValues(GraphType &revGraph, list<int> &nodeValues);

GraphNode *findUnvisitedMaxVal(GraphType &graph, list<int> &nodeValues);
int countScc(GraphType &graph, GraphNode *leadNode);

typedef chrono::high_resolution_clock::time_point timep;
timep time_now()
{
  return std::chrono::high_resolution_clock::now();
}

long long int time_diff_ms(timep p1, timep p2)
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(p1 - p2).count();
}



int main() {

  timep tic;

  cout << "Parsing input file... " << flush;
  tic = time_now();
  bool result = readInputFile(DATA_FILE_PATH"SCCOriginal.txt", mainInputStorage);
  cout << (result ? "Success" : "Failure") <<
      " (" << time_diff_ms(time_now(), tic) << "ms) " << endl;

  cout << "Building reversed graph... " << flush;
  tic = time_now();
  result &= buildRevGraph(mainInputStorage, revGraph);
  cout << (result ? "Success" : "Failure") << ". " << revGraph.size() << " elements" <<
      " (" << time_diff_ms(time_now(), tic) << "ms) " << endl;

//  cout << "Printing reversed graph... ";
//  printGraph(revGraph);
//  cout << "Success" << endl;

  // find node values only
  cout << "Building nodes values... " << endl << flush;
  result &= buildNodesValues(revGraph, nodeValues);
  cout << endl << (result ? "Success" : "Failure") <<
      " (" << time_diff_ms(time_now(), tic) << "ms) " << endl;

  // print sequence
//  cout << "node values: ";
//  for( list<int>::iterator it=nodeValues.begin(); it!=nodeValues.end(); it++) {
//    cout << *it << ' ';
//  }
//  cout << endl;

  cout << "Building direct graph... " << flush;
  vector<int> sccs;
  result &= buildGraph(mainInputStorage, graph);
  cout << (result ? "Success" : "Failure") << ". " << graph.size() << " elements" <<
      " (" << time_diff_ms(time_now(), tic) << "ms) " << endl;

  cout << "Count SCCs... ";
  GraphNode *node = findUnvisitedMaxVal(graph, nodeValues);
  while (node != NULL) {

    int scc = countScc(graph, node);
//    cout << " " << scc;
    sccs.push_back(scc);
    node = findUnvisitedMaxVal(graph, nodeValues);
  }
  cout << "Success" <<
      " (" << time_diff_ms(time_now(), tic) << "ms) " << endl;

  cout << "Sorting SCCs... ";
  sort(sccs.begin(), sccs.end(), greater<int>());
  cout << "Success" <<
      " (" << time_diff_ms(time_now(), tic) << "ms) " << endl;

  cout << "The final sorted SCCs (total " << sccs.size() << "): ";
  for (vector<int>::iterator it = sccs.begin(); it != sccs.end(); it++) {
    if (*it > 100)
      cout << *it << ' ';
  }
  cout << endl;

  return 0;
}

bool readInputFile(const char *fname, InputStorageType &storage) {
  fstream inputStream(fname, fstream::in);
  if (inputStream.is_open() == false) {
    cout << "failed to open a file";
    return false;
  }

  int nodeSrc = 0;
  int nodeDst = 0;

  while (inputStream.eof() == false) {
    inputStream >> nodeSrc;
    inputStream >> nodeDst;
    storage.push_back(make_pair(nodeSrc, nodeDst));
  }

  inputStream.close();

  return true;
}

bool buildGraph(InputStorageType &storage, GraphType &nodes) {
  InputStorageType::iterator it = storage.begin();
  while (it != storage.end())
  {
    int nodeSrcVal = it->first;
    int nodeDstVal = it->second;

    // check if first node exists
    if (nodes.find(nodeSrcVal) == nodes.end()) {
      nodes[nodeSrcVal] = new GraphNode(nodeSrcVal);
    }

    if (nodes.find(nodeDstVal) == nodes.end()) {
      nodes[nodeDstVal] = new GraphNode(nodeDstVal);
    }

    nodes[nodeSrcVal]->outArcs.push_back(nodeDstVal);
    it++;
  }

  return true;
}

bool buildRevGraph(InputStorageType &storage, GraphType &graph) {
  InputStorageType::iterator it = storage.begin();
  while (it != storage.end())
  {
    int nodeSrcVal = it->second;
    int nodeDstVal = it->first;

    // check if first node exists
    if (graph.find(nodeSrcVal) == graph.end()) {
      graph[nodeSrcVal] = new GraphNode(nodeSrcVal);
    }

    // check if second node exists
    if (graph.find(nodeDstVal) == graph.end()) {
      graph[nodeDstVal] = new GraphNode(nodeDstVal);
    }

    graph[nodeSrcVal]->outArcs.push_back(nodeDstVal);
    it++;
  }

  return true;
}

void printGraph(GraphType &graph) {
  GraphType::iterator it = graph.begin();
  while (it != graph.end()) {
    cout << it->first << " |";
    GraphNode *node = it->second;
    list<int>::iterator arcIt = node->outArcs.begin();
    while (arcIt != node->outArcs.end()) {
      cout << ' ' << *arcIt;
      arcIt++;
    }
    it++;
    cout << endl;
  }
}

bool graphItInitialized = false;
GraphType::iterator unvisitedGraphIt;

GraphNode *findUnvisited(GraphType &revGraph) {
//  GraphType::reverse_iterator rit = revGraph.rbegin();
//  while (rit != revGraph.rend()) {
//    if (rit->second->visited == false) {
//      return rit->second;
//    }
//    rit++;
//  }

  if (graphItInitialized == false) {
    unvisitedGraphIt = revGraph.begin();
    // set here to false to make it search from the beginning all over again
    graphItInitialized = true;
  }

  while (unvisitedGraphIt != revGraph.end()) {
    if (unvisitedGraphIt->second->visited == false) {
      return unvisitedGraphIt->second;
    }
    unvisitedGraphIt++;
  }

  return NULL;
}

bool buildNodesValues(GraphType &revGraph, list<int> &nodeValues) {
  // just to show some progress
  int lastProcessedNode = 1;
  timep tic_cycle = time_now();
  bool profile = true;

  list<GraphNode *> nodeStack;
  // main loop will try to push unvisited node into the stack
  GraphNode *unvisitedNode = findUnvisited(revGraph);
  while ( unvisitedNode != NULL)
  {
    if (lastProcessedNode + 10000 < unvisitedNode->value) {
      lastProcessedNode = unvisitedNode->value;
      cout << unvisitedNode->value <<
          " (" << time_diff_ms(time_now(), tic_cycle) << "ms) " << endl << flush;
      tic_cycle = time_now();
      profile = true;
    }

    // mark as visited
    unvisitedNode->visited = true;
    // and push to stack
    nodeStack.push_back(unvisitedNode);
    if (profile) {
      cout << "\tstack size: " << nodeStack.size() <<
          " (" << time_diff_ms(time_now(), tic_cycle) << "ms) " << endl << flush;
    }

    // main loop while stack is not empty
    while (nodeStack.empty() == false) {

      // pull the top stack element to check outgoing arcs
      GraphNode *stackTop = nodeStack.back();
      // have a bool to check if the node leads any deeper
      bool allArcsVisited = true;
      // check all the outgoing arcs
      list<int>::iterator arcIt = stackTop->outArcs.begin();
      while (arcIt != stackTop->outArcs.end()) {

        // take the child node
        GraphNode *childNode = revGraph[*arcIt];
        if (childNode == NULL) {
          cerr << "Failed to find node with " << *arcIt << " value. parent node is " << stackTop->value << endl;
          return false;
        }
        if (childNode->visited == false) {
          childNode->visited = true;
          nodeStack.push_back(childNode);
          allArcsVisited = false;
        }

        arcIt++;
      }

//      if (profile) {
//        cout << "\tbranch traversing is done" <<
//            " (" << time_diff_ms(time_now(), tic_cycle) << "ms) " << endl << flush;
//      }

      // now if no children were pushed to stack - need to mark current and pop it
      if (allArcsVisited) {
        nodeValues.push_back(stackTop->value);
        nodeStack.pop_back();
      }

//      if (profile) {
//        cout << "\tadded a node value" <<
//            " (" << time_diff_ms(time_now(), tic_cycle) << "ms) " << endl << flush;
//      }
    }

    // check if we still have something to work with
    unvisitedNode = findUnvisited(revGraph);
    if (profile) {
      cout << "\tunvisited node found" <<
          " (" << time_diff_ms(time_now(), tic_cycle) << "ms) " << endl << flush;
    }
    profile = false;
  }

  return true;
}

GraphNode *findUnvisitedMaxVal(GraphType &graph, list<int> &nodeValues) {
  // the lates node in a list has the biggest value
  while (nodeValues.empty() == false) {
    GraphNode *node = graph[nodeValues.back()];
    if (node->visited == false) {
      return node;
    }
    // if already visited - remove it from the list
    nodeValues.pop_back();
  }

  // if all the nodes visited
  return NULL;
}

int countScc(GraphType &graph, GraphNode *leadNode) {
  list<GraphNode *> nodeStack;
  int sccCount = 0;

  // push the lead node to the stack
  sccCount++;
  leadNode->visited = true;
  nodeStack.push_back(leadNode);
  // we added 1 item already

  while (nodeStack.empty() == false) {
    // pull the node out
    GraphNode *node = nodeStack.back();
    nodeStack.pop_back();
    // push to stack all the children
    for (list<int>::iterator it = node->outArcs.begin(); it != node->outArcs.end(); it++) {
      GraphNode *child = graph[*it];
      if (child->visited == false) {
        sccCount++;
        child->visited = true;
        nodeStack.push_back(child);
      }
    }
  }

  return sccCount;
}