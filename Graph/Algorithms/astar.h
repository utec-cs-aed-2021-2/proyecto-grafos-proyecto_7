#include "../UndirectedGraph.h"

#ifndef ASTAR_H
#define ASTAR_H


template<typename TV, typename TE>
class AStar{

private:
	unordered_map<Vertex<TV, TE>* , bool> visited;
    unordered_map<Vertex<TV, TE>*, Vertex<TV,TE>*> hijo_padre;
	Vertex<TV, TE>* startV,*endV;
    unordered_map<Vertex<TV,TE>*, int> costo;
    //unordered_map<vector<TV,TE>*,int>heuristica;
public:
	AStar(Graph<TV, TE>* graph, TV start, TV end)//, unordered_map<Vertex<TV,TE>*,int>_heuristica)
    {
        auto un_map = graph->vertexes;
        this->startV = graph->vertexes[start];
        this->endV = graph->vertexes[end];
        //this->heuristica = _heuristica;
        for (auto [k, v] : un_map) {
            this->visited[v] = false;
            this->costo[v] = 0;
            if(v == startV){
                for(auto &i:v->edges){
                    auto tmp = i->edgeVertexes[1];
                    hijo_padre[tmp] = v;
                    this->costo[tmp] = i->weight; //+ heuristica[tmp];
                }
            }
        }
        //for (auto [k, v] : visited)
        //	cout << k->data << " -> " << v << endl;
    }
	AStar(UnDirectedGraph<TV, TE>* graph, TV start, TV end)//, unordered_map<Vertex<TV,TE>*,int>_heuristica)
	{
		auto un_map = graph->vertexes;
		this->startV = graph->vertexes[start];
        this->endV = graph->vertexes[end];
        //this->heuristica = _heuristica;
		for (auto [k, v] : un_map) {
            this->visited[v] = false;
            this->costo[v] = 0;
            if(v == startV){
                for(auto &i:v->edges){
                    auto tmp = i->edgeVertexes[1];
                    hijo_padre[tmp] = v;
                    this->costo[tmp] = i->weight; //+ heuristica[tmp];
                }
            }
        }
		//for (auto [k, v] : visited)
		//	cout << k->data << " -> " << v << endl;
	}
    AStar(DirectedGraph<TV, TE>* graph, TV start, TV end)//, unordered_map<Vertex<TV,TE>*,int>_heuristica)
    {
        auto un_map = graph->vertexes;
        this->startV = graph->vertexes[start];
        this->endV = graph->vertexes[end];
        //this->heuristica = _heuristica;
        for (auto [k, v] : un_map) {
            this->visited[v] = false;
            this->costo[v] = 0;
            if(v == startV){
                for(auto &i:v->edges){
                    auto tmp = i->edgeVertexes[1];
                    hijo_padre[tmp] = v;
                    this->costo[tmp] = i->weight; //+ heuristica[tmp];
                }
            }
        }
        //for (auto [k, v] : visited)
        //	cout << k->data << " -> " << v << endl;
    }
    Vertex<TV,TE>* less_cost_node(){
        int menor,n=0;
        auto tmp = startV;
        for(auto &i:costo){
            if(n==0 && i.second !=0 && visited[i.first] == false)
            {
                menor = i.second;
                tmp = i.first;
                n++;
            }
            else if(i.second != 0 && n>0 && visited[i.first] == false){
                if(i.second < menor) {
                    tmp = i.first;
                    menor = i.second;
                }
            }
        }
        visited[tmp] = true;
        return tmp;
    }
    void actualizar_costos(Vertex<TV,TE>* node){
        for(auto &i:node->edges){
            auto tmp = i->edgeVertexes[1];
            if(this->costo[tmp] == 0)
            {
                this->costo[tmp] = this->costo[node] + i->weight; //+ heuristica[tmp];
                this->hijo_padre[tmp] = node;
            }
            else
            {
                if (this->costo[tmp] > this->costo[node] + i->weight){ //+ heuristica[tmp]) {
                    this->costo[tmp] = this->costo[node] + i->weight; //+ heuristica[tmp];
                    this->hijo_padre[tmp] = node;
                }
            }
        }
    }
    bool union_nodos(Vertex<TV,TE>*tmp,Vertex<TV,TE>* nodo_menor){
        bool veracidad= false;
        if(tmp == startV)
            return true;
        for(auto &i:tmp->edges)
        {
            if((i->edgeVertexes[1] == nodo_menor) && (i->weight + costo[tmp] <= costo[nodo_menor]) && tmp != startV){
                veracidad = true;
                break;
            }
        }
        return veracidad;
    }
    void camino_final(stack<Vertex<TV,TE>*> &q)
    {
        q.push(this->endV);
        auto tmp = this->hijo_padre[this->endV];
        q.push(tmp);
        while (q.top() != this->startV){
            tmp = this->hijo_padre[q.top()];
            q.push(tmp);
        }
    }

	void apply()
	{
        stack<Vertex<TV,TE>*> s;
        stack<Vertex<TV, TE>*>q;
        s.push(startV);
        visited[startV] = true;
        while (s.top() != endV)
        {
            Vertex<TV,TE>* nodo_menor = less_cost_node();
            auto tmp = s.top();
            while (!union_nodos(tmp,nodo_menor))
            {
                s.pop();
                tmp = s.top();
            }
            if(nodo_menor == this->endV)
            {
                camino_final(q);
                break;
            }
            s.push(nodo_menor);
            actualizar_costos(nodo_menor);
        }
        while (!q.empty()){
            cout << q.top() <<"-> ";
            q.pop();
        }
        cout << "end";

    }
};


#endif
