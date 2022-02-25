// Implement Dijkstra's Algorithm
// compile with c++ standard c++11
#include <iostream>
#include <vector>
#include <random>
#include <limits>

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
    public:
        Edge(double, Vertex *);         //constructor, init with a distance and a head-vertex(the edge points to)
        void set_next_edge(Edge *);     //set next edge
        friend Graph;                   //let a graph instance access a edge's private properties
        friend ostream & operator<<(ostream &, const Graph &);  //let overloaded function of << operator access a edge's private properties
};

Edge::Edge(double _distance, Vertex * _head): distance(_distance), head(_head) {
    next = NULL;
}

void Edge::set_next_edge(Edge * e){
    next = e;
}

//define graph
class Graph{
    private:
        vector<Vertex> vertexs;                         //vertexs of the graph
    public:
        Graph(int, double, double, double);             //constructor, init with a vertex(or node) counts, a density and a distance range
        ~Graph();                                       //destructor, free memory allocated
        bool adjacent(int, int);                        //tests whether there is an edge from node v1 to node v2.
        bool add_edge(int, int, double);                //adds to the graph the edge from v1 to v2, if it is not there.
        int get_node_value(int);                        //returns the value associated with the node v
        bool set_node_value(int, int);                  //sets the value associated with the node v to _value
        double get_edge_value(int, int);                //returns the value associated to the edge between v1 and v2
        bool set_edge_value(int, int, double);          //sets the value associated to the edge between v1 and v2 to _distance
        void short_path(int, int);                      //find shortest path between v1-v2, and prints the sequence of vertices 
                                                        //representing shorest path v1-t1-t2-…-tn-v2 and the path cost associated 
                                                        //with the shortest path. 
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
            vertexs[v1].first_edge = new Edge(_distance, &vertexs[v2]);
            vertexs[v1].last_edge = vertexs[v1].first_edge;
        }
        else{
            vertexs[v1].last_edge->next = new Edge(_distance, &vertexs[v2]);
            vertexs[v1].last_edge = vertexs[v1].last_edge->next;
        }
        if(vertexs[v2].first_edge == NULL){
            vertexs[v2].first_edge = new Edge(_distance, &vertexs[v1]);
            vertexs[v2].last_edge = vertexs[v2].first_edge;
        }
        else{
            vertexs[v2].last_edge->next = new Edge(_distance, &vertexs[v1]);
            vertexs[v2].last_edge = vertexs[v2].last_edge->next;
        }
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
    Graph g1(10, 0.5, 1.0, 10.0);
    cout << g1;
    g1.short_path(2, 4);
    return 0;
}
