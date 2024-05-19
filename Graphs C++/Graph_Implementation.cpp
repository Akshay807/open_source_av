#include<iostream>
#include<list>
#include<unordered_map>
#include<queue>
#include<stack>
using namespace std;

class Graph{
    public:

    unordered_map<int, list<int>> adj;
    void addEdge(int u, int v, bool direction){
        adj[u].push_back(v);
        // if direction = 0 --> Undirected
        // if durection = 1 --> Directed
        if (direction == 0){
            adj[v].push_back(u);
        }
        return;
    }

    void printGraph(){
        cout<<endl<<"Start of Graph Printing!"<<endl;
        for(auto i:adj){
            cout<<i.first<<"->";
            for (auto j:i.second){
                cout<<j<<" ";
            }
            cout<<endl;
        }
        cout<<"End of Graph Printing!"<<endl;
        return;
    }

    void BFS_traversal(int node){               // This is a driver function for main BFS implementation.
        int apnaNode = node;
        unordered_map<int, bool> visited;
        /*A doubt 1. How can the elements (key) of unordered_map be set to the nodes of our map.
                  2. How can the value of corresponding key of  unordered_map be set false.
        
        // for (auto i:adj){                    // Making of visited map for tracking visited nodes in queue.
        //     visited[i.first] = false;
        // }
        */
        list<int> traversal;
        queue<int> visitedQueue;                // Queue for BFS Traversal
        // stack<int> visitedStack;             // Stack for Iterative DFS traversal
        BFS_main(apnaNode, visited, visitedQueue);
        return;
    }

    void BFS_main(int node, unordered_map<int, bool> &visited, queue<int> &visitedQueue){   // This is the main algorithm for BFS.
        cout<<endl<<"Start of BFS_traversal Printing!"<<endl;
        int head = node;                        // We will need a starting head to start our traversing our graph.
        visitedQueue.push(head);
        visited[head] = true;
        
        while (visitedQueue.empty() == false){  // Iterating over the queue.
            int curr = visitedQueue.front();    // Taking the front element of queue.
            for (auto i:adj[curr]){             // Iterating over the neighbours of front element of the queue.
                if (!visited[i]){               // Checking if the neighbour is not visited before.
                    visitedQueue.push(i);       // Push it to queue if not visited before.
                    visited[i] = true;          // Marking the neighbour true in visited queue.
                }
            }
            cout<<curr<<" ";                    // Printing the front element.
            visitedQueue.pop();                 // Popping the front element.
        }  
        cout<<endl;
        cout<<"End of BFS_traversal"<<endl;
        return;
    }
    
    
    void DFS_traversal(int node){               // This is a driver function for main BFS implementation.
        int apnaNode = node;
        unordered_map<int, bool> visited;
        /*A doubt 1. How can the elements (key) of unordered_map be set to the nodes of our map.
                  2. How can the value of corresponding key of  unordered_map be set false.
        
        // for (auto i:adj){                    // Making of visited map for tracking visited nodes in queue.
        //     visited[i.first] = false;
        // }
        */
        list<int> traversal;
        // queue<int> visitedQueue;             // Queue for BFS Traversal
        stack<int> visitedStack;                // Stack for Iterative DFS traversal
        DFS_main(apnaNode, visited, visitedStack);
        return;
    }
    
    void DFS_main(int node, unordered_map<int, bool> &visited, stack<int> &visitedStack){
        cout<<endl<<"Start of DFS_traversal Printing!"<<endl;
        unordered_map<int, int> childParent;        // Cycle Detection, To map the child and its parent.
        childParent[node] = -1;                     // Cycle Detection, Parent of root node as -1.
        bool checkCycle = false;                    // Cycle Detection, Initially assuming the cycle is not present.

        int currNode = node;
        visitedStack.push(node);
        visited[node] = true;
        
        while(visitedStack.empty() == false){
            int frontNode = visitedStack.top();     // There is a slight difference between BFS & iterative DFS, in bfs we use queue, in iterative DFS we ue stack
                                                    // In BFS we push the all neighbours first and the pop the front node
                                                    // However, in iterative DFS we pop the front element first and then push all the neighbours to stack.
            visitedStack.pop();
            for (auto i:adj[frontNode]){                                                                        // Made mistake here - was not checking elements from adj[curr], else did as i:visitedStack
                if(!visited[i]){                                                                                // Made mistake here - did not check whether element already in stack or not
                    visitedStack.push(i);
                    visited[i] = true;
                    childParent[i] = frontNode;     // Assigning the parent to chile node.
                    checkCycle = cyclePresent(frontNode, visited, i, childParent);
                }
            }
            cout<<frontNode<<" ";   
        }

        cout<<endl;
        cout<<"End of DFS_traversal"<<endl<<endl;
        
        if(checkCycle){
            cout<<"Cycle Present!"<<endl;
        }
        else{
            cout<<"Cycle Not Present!"<<endl;
        }
        return;
    }
    
    bool cyclePresent(int frontNode, unordered_map<int, bool> &visited, int iCurr, unordered_map<int, int> &childParent){
        // Here we need two nodes (to receive from the calling function) to check the relation among them. The relation to be checked is whether the,
        // a. frontNode is already visited, and, b. frontNode (i.e., the node we are currently on) is NOT child of any of its adjacent nodes (iCurr).
        // Basically Check agr a. Pehle se visited hai AND b. uska parent jo hum is iteration me leke aaye hai uske paas pehle se koi hai. Toh Cycle banegi.

        if ((visited[frontNode] == true) && (childParent[iCurr] == frontNode)){
            return true;
        }
        else return false;
    }
};

int main(){
    int n, m;
    cout<<"Enter the number of nodes"<<endl;
    cin>>n;

    cout<<"Enter the number of edges"<<endl;
    cin>>m;
    Graph g;
    int head;
    
    for(int i=0; i<m; i++){
        int u, v;
        cin>>u>>v;
        if (i == 0){                            // Making the first element of graph as head of it.
            head = u;
        }
        g.addEdge(u,v,0);
        
    }
    g.printGraph();
    // g.BFS_traversal(head);
    g.DFS_traversal(head);
}