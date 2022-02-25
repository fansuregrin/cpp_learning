// Implement Dijkstra's Algorithm
// compile with c++ standard c++11
#include <iostream>
#include <vector>
#include <random>
#include <limits>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;
class Vertex;
class Edge;
class Graph;

// define infinity(a big number)
const double INF = numeric_limits<double>::max()/2;

// define vertex(or node)
class Vertex{
    private:
        int id;                             //unique identifier of a vertex(or node)
        int value;                          //the value of vertex(or node)
        int degree;                         //the degree of vertex(or node)
        Edge * first_edge, * last_edge;     //the first and last edge of this vertex
    public:
        Vertex(int, int);                   //constructor, init with a id and a value
        friend Graph;                       //let a graph instance access a vertex's private properties
        friend ostream & operator<<(ostream &, const Graph &);   //let overloaded function of << operator access a vertex's private properties
        friend bool operator==(const Vertex &, const Vertex &);  //overloaded function of == operator
};

Vertex::Vertex(int _id, int _value): id(_id), value(_value) {
    first_edge = NULL;
    last_edge = NULL;
    degree = 0;
}

bool operator==(const Vertex & lhs, const Vertex & rhs){
    if(&lhs == &rhs){       //lhs and rhs is the same instance of Vertex
        return true;
    }
    else{
        return false;
    }
}

// define edge
class Edge{
    private:
        double distance;                //the distance of edge
        Edge * next;                    //next edge of the same vertex
        Vertex * head;                  //the vertex that this edge points to
        Vertex * tail;                  //the vertex that ponit to this edge
    public:
        Edge(double, Vertex *, Vertex *);         //constructor, init with a distance and a head-vertex(the edge points to)
        void set_next_edge(Edge *);     //set next edge
        friend Graph;                   //let a graph instance access a edge's private properties
        friend ostream & operator<<(ostream &, const Graph &);  //let overloaded function of << operator access a edge's private properties
        friend bool operator<(const Edge &, const Edge &);
};

Edge::Edge(double _distance, Vertex * _tail, Vertex * _head): distance(_distance), tail(_tail), head(_head) {
    next = NULL;
}

void Edge::set_next_edge(Edge * e){
    next = e;
}

bool operator<(const Edge & lhs, const Edge & rhs){
    if(lhs.distance < rhs.distance){
        return true;
    }
    else{
        return false;
    }
}

//define graph
class Graph{
    private:
        vector<Vertex> vertexs;                         //vertexs of the graph
    public:
        Graph(int, double, double, double);             //constructor, init with a vertex(or node) counts, a density and a distance range
        Graph(const string &);                          //read in a graph from a file
        Graph(int);                                     //constructor, init with some vertices, no edge
        ~Graph();                                       //destructor, free memory allocated
        int get_node_count();                           //return the number of vertices in the graph
        int get_edge_count();                           //return the number of edges in the graph
        bool adjacent(int, int);                        //tests whether there is an edge from node v1 to node v2.
        bool add_edge(int, int, double);                //adds to the graph the edge from v1 to v2, if it is not there.
        int get_node_value(int);                        //returns the value associated with the node v
        bool set_node_value(int, int);                  //sets the value associated with the node v to _value
        double get_edge_value(int, int);                //returns the value associated to the edge between v1 and v2
        bool set_edge_value(int, int, double);          //sets the value associated to the edge between v1 and v2 to _distance
        void short_path(int, int);                      //find shortest path between v1-v2, and prints the sequence of vertices 
                                                        //representing shorest path v1-t1-t2-…-tn-v2 and the path cost associated 
                                                        //with the shortest path.
        bool has_path(int, int);                        //check if a path is reachable between two vertices
        void msf();                                     //finds a minimum spanning forest 
        friend ostream & operator<<(ostream &, const Graph &);
};

Graph::Graph(int count, double density, double range_l, double range_r){
    int i;
    for(i=0; i<count; ++i){
        vertexs.push_back(Vertex(i, i));
    }
    int edge_count = int(count * (count-1) /2 * density);
    while(edge_count){
        random_device rd;
        default_random_engine eng(rd());
        uniform_real_distribution<double> rand_distance(range_l, range_r);
        uniform_int_distribution<int> rand_vertex(0, count-1);
        if(add_edge(rand_vertex(eng), rand_vertex(eng), int(rand_distance(eng)*10)/10.0)){
            --edge_count;
        }
    }
}

//read in a graph from a file
Graph::Graph(const string & filepath){
    ifstream data_file(filepath);
    while(!data_file.good()){
        string temp;
        cout << "Error! Please input the correct filepath: ";
        cin >> temp;
        data_file = ifstream(temp);
    }
    istream_iterator<int> start(data_file), end;
    vector<int> data(start, end);
    if(data.size()%3 != 1){
        cerr << "the file data is not correct!" << endl;
        return;
    }
    for(int i=0; i<data[0]; ++i){
        vertexs.push_back(Vertex(i, i));
    }
    for(auto arg = data.begin()+1; arg != data.end(); arg+=3){
        add_edge(*arg, *(arg+1), double(*(arg+2)));
    }
}

Graph::Graph(int count){
    for(int i=0; i<count; ++i){
        vertexs.push_back(Vertex(i, i));
    }
}

Graph::~Graph(){
    int i;
    for(i=0; i<vertexs.size(); ++i){
        Edge * edge = vertexs[i].first_edge;
        while(edge){
            Edge * temp = edge;
            edge = edge->next;
            delete temp;
        }
    }
}

//return the number of vertices in the graph
int Graph::get_node_count(){
    return vertexs.size();
}

//return the number of edges in the graph
int Graph::get_edge_count(){
    int count = 0;
    for(auto ver: vertexs){
        count += ver.degree;
    }
    return count/2;
}

//tests whether there is an edge from node v1 to node v2.
bool Graph::adjacent(int v1, int v2){
    if(
        v1 >= vertexs.size() || 
        v2 >= vertexs.size() ||
        v1 < 0 ||
        v2 < 0
    ){
        return false;
    }
    else if(v1 == v2){
        return true;
    }
    bool has_edge_1 = false, has_edge_2 = false;
    Edge * edge = vertexs[v1].first_edge;
    while(edge){
        if(*(edge->head) == vertexs[v2]){
            has_edge_1 = true;
            break;
        }
        edge = edge->next;
    }
    edge = vertexs[v2].first_edge;
    while(edge){
        if(*(edge->head) == vertexs[v1]){
            has_edge_2 = true;
            break;
        }
        edge = edge->next;
    }
    return (has_edge_1 && has_edge_2);
}

//adds to the graph the edge from v1 to v2, if it is not there.
bool Graph::add_edge(int v1, int v2, double _distance){
    if(
        v1 >= vertexs.size() || 
        v2 >= vertexs.size() ||
        v1 < 0 ||
        v2 < 0 ||
        v1 == v2
    ){
        return false;
    }
    else if(adjacent(v1, v2)){
        return false;
    }
    else{
        if(vertexs[v1].first_edge == NULL){
            vertexs[v1].first_edge = new Edge(_distance, &vertexs[v1], &vertexs[v2]);
            vertexs[v1].last_edge = vertexs[v1].first_edge;
        }
        else{
            vertexs[v1].last_edge->next = new Edge(_distance, &vertexs[v1], &vertexs[v2]);
            vertexs[v1].last_edge = vertexs[v1].last_edge->next;
        }
        vertexs[v1].degree++;
        if(vertexs[v2].first_edge == NULL){
            vertexs[v2].first_edge = new Edge(_distance, &vertexs[v2], &vertexs[v1]);
            vertexs[v2].last_edge = vertexs[v2].first_edge;
        }
        else{
            vertexs[v2].last_edge->next = new Edge(_distance, &vertexs[v2], &vertexs[v1]);
            vertexs[v2].last_edge = vertexs[v2].last_edge->next;
        }
        vertexs[v2].degree++;
        return true;
    }
}

//returns the value associated with the node v
int Graph::get_node_value(int v){
    if(v>=0 && v<vertexs.size())
        return vertexs[v].value;
    else
        return -1;
}

//sets the value associated with the node v to _value
bool Graph::set_node_value(int v, int _value){
    if(v>=0 && v<vertexs.size()){
        vertexs[v].value = _value;
        return true;
    }
    else{
        return false;
    }
}

//returns the value associated to the edge between v1 and v2
double Graph::get_edge_value(int v1, int v2){
    double re;
    if(adjacent(v1, v2)){
        if(v1 == v2){
            re = 0.0;
        }
        Edge * edge = vertexs[v1].first_edge;
        while(edge){
            if(*(edge->head) == vertexs[v2]){
                re = edge->distance;
                break;
            }
            edge = edge->next;
        }
    }
    else{
        re = INF;
    }
    return re;
}

//sets the value associated to the edge between v1 and v2 to _distance
bool Graph::set_edge_value(int v1, int v2, double _distance){
    if(adjacent(v1, v2)){
        Edge * edge = vertexs[v1].first_edge;
        while(edge){
            if(*(edge->head) == vertexs[v2]){
                edge->distance = _distance;
            }
            else{
                edge = edge->next;
            }
        }
        edge = vertexs[v2].first_edge;
        while(edge){
            if(*(edge->head) == vertexs[v1]){
                edge->distance = _distance;
            }
            else{
                edge = edge->next;
            }
        }
        return true;
    }
    else{
        return false;
    }
}

//find shortest path between v1-v2, and prints the sequence of vertices 
//representing shorest path v1-t1-t2-…-tn-v2 and the path cost associated 
//with the shortest path. 
void Graph::short_path(int v1, int v2){
    int v_count = vertexs.size();
    vector<double> dist(v_count);           //record the distance from v1 to each vertex
    vector<int> path(0);                    //record the vertices on the v1 to v2 path
    for(int i=0; i<v_count; ++i){           //set the dist[i] to infinity except dist[v1]
        if(i == v1)
            dist[i] = 0;
        else
            dist[i] = INF;
    }
    vector<bool> visited(v_count);          //record whether the shortest path from v1 to each vertex is found
    for(int i=0; i<v_count; ++i){
        visited[i] = false;
    }
    while(!visited[v2]){                    //the shortest path from v1 to v2 has not been found, enter loop
        double min_dist = INF;             
        int min_dist_pos = 0;
        for(int i=0; i<v_count; ++i){       //find the smallest distance among the distances not marked as the shortest path
            if(dist[i] < min_dist && !visited[i]){
                min_dist = dist[i];
                min_dist_pos = i;
            }
        }
        if(min_dist == INF){                //v1 cannot reach v2
            break;
        }
        if(!visited[min_dist_pos]){
            visited[min_dist_pos] = true;   //marked than find the short path v1 to min_dist_post node
            for(int i=0; i<v_count; ++i){
                //is there a shorter path to reach other vertices(vertex i) via min_dist_post
                if(dist[i] > dist[min_dist_pos] + get_edge_value(min_dist_pos, i)){
                    dist[i] = dist[min_dist_pos] + get_edge_value(min_dist_pos, i);
                    if(i == v2 && min_dist_pos!=v1){
                        path.push_back(min_dist_pos);       //there is a shorter path from vertex i to vertex v2, put vertex i as the part of shortest path
                    }
                }
            }
        }
    }
    cout << v1;
    for(int i=0; i<path.size(); ++i){
        cout << "-" << path[i];
    }
    cout << "-" << v2 << ": ";
    if(dist[v2] == INF){
        cout << "distance = ∞" << endl;
    }
    else{
        cout << "distance = " << dist[v2] << endl;
    }
}

//check if a path is reachable between two vertices
bool Graph::has_path(int v1, int v2){
    static vector<bool> visited(vertexs.size(), false);
    if(v1 == v2){
        return true;
    }
    visited[v1] = true;
    Edge * edge = vertexs[v1].first_edge;
    while(edge){
        if(!visited[edge->head->id] && has_path(edge->head->id, v2)){
            visited[v1] = false;
            return true;
        }
        else{
            edge = edge->next;
        }
    }
    visited[v1] = false;
    return false;
}

//finds a minimum spanning forest 
void Graph::msf(){
    vector<Edge> edges;
    for(auto ver: vertexs){
        Edge * _edge = ver.first_edge;
        while(_edge){
            if(ver.id < _edge->head->id)
            edges.push_back(*_edge);
            _edge = _edge->next;
        }
    }
    sort(edges.begin(), edges.end());
    Graph forest(vertexs.size());
    for(auto edge: edges){
        if(!forest.has_path(edge.tail->id, edge.head->id)){
            forest.add_edge(edge.tail->id, edge.head->id, get_edge_value(edge.tail->id, edge.head->id));
        }
    }
    cout << forest;
}

ostream & operator<<(ostream & out, const Graph & graph){
    out.flags(ios::fixed);
    out.precision(1);
    for(int i=0; i<graph.vertexs.size(); ++i){
        Edge * edge = graph.vertexs[i].first_edge;
        while(edge){
            if(i<edge->head->id){
                out << "(id:" << i << ", value:" << graph.vertexs[i].value << ") ----[distance:" << edge->distance << "]----> (id:" 
                    << edge->head->id << ", value:" << edge->head->value << ")" << endl;
            }
            edge = edge->next;
        }
    }
    return out;
}

int main(){
    Graph g1(10, 0.4, 1.0, 10.0);
    cout << g1;
    cout << "\nhow many edges in g1: " << g1.get_edge_count() << endl;
    g1.short_path(2, 4);

    //test if a path is reachable between two vertices
    // bool ctn = true;
    // while(ctn){
    //     int ver1, ver2;
    //     cout << "input vertex1: ";
    //     cin >> ver1;
    //     cout << "input vertex2: ";
    //     cin >> ver2;
    //     if(g1.has_path(ver1, ver2)){
    //         cout << ver1 << "--✔--->" << ver2 << endl;
    //     }
    //     else{
    //         cout << ver1 << "--❌--->" << ver2 << endl;
    //     }
    //     cout << "continue to test? input 1 for yes and 0 for no: ";
    //     cin >> ctn;
    // }

    //minimum spanning forest of g1
    g1.msf();

    // Graph g2("data.txt");
    // cout << g2;
    return 0;
}
