[![Open in Visual Studio Code](https://classroom.github.com/assets/open-in-vscode-f059dc9a6f8d3a56e377f745f24479a46679e63a5d9fe6f495e02850cd0d8118.svg)](https://classroom.github.com/online_ide?assignment_repo_id=6164444&assignment_repo_type=AssignmentRepo)
# Algoritmos y Estructura de Datos
## Proyecto sobre Grafos
--------
## Profesor
- Heider Sanchez Enriquez
## Integrantes
- Juan Diego Laredo
- Jeremy Matos
- Diego Guerra

----

El proyecto del curso consiste en implementar una estructura de datos de grafo y un file parser. La estructura debe soportar los métodos y algoritmos descritos a continuacion:  


## Graph data structure

* El grafo debe ser dinámico (inserciones. eliminaciones, búsquedas, ...)
* Se debe implementar los dos tipos de grafos: dirigidos y no-dirigidos.
* No considerar loops ni multi-arista. 


### Methods:
```cpp
bool insertVertex(string id, V data); // Creates a new vertex in the graph with some data and an ID

bool createEdge(string start, string end, E data); // Creates a new edge in the graph with some data

bool deleteVertex(string id); // Deletes a vertex in the graph

bool deleteEdge(string start, string end); // Deletes an edge in the graph, it is not possible to search by the edge value, since it can be repeated

E &operator()(string start, string end); // Gets the value of the edge from the start and end vertexes

float density() const; // Calculates the density of the graph

bool isDense(float threshold = 0.5) const; // Calculates the density of the graph, and determine if it is dense dependening on a threshold value

bool isConnected(); // Detect if the graph is connected

bool isStronglyConnected() throw(); // Detect if the graph is strongly connected (only for directed graphs)

bool empty(); // If the graph is empty

void clear(); // Clears the graph
```

##  Grafo no dirigido (Graph/UndirectedGraph.h)
### Especificaciones de los métodos
```cpp
bool insertVertex(string id, TV vertex){   
    // check if node already exists
    if (this->vertexes.find(id) != this->vertexes.end())
        return false; 

    // create and insert node in std::unordered_map
    Vertex<TV,TE>* newVertex = new Vertex<TV,TE>();
    newVertex->data = vertex;
    newVertex->id = id;
    this->vertexes[id] = newVertex;
    this->numVertexes++;
    return true;
}
```
Para insertar un vértice, lo primero que se verifica es si es que ya existe uno con el mismo id. En caso exista, se retorna falso. En caso no,
se crea un nuevo vértice asignándole la data y id respectiva. Luego, se inserta en en el unordered_map de vértices, se incrementa el atributo que cuenta la cantidad de vértices del grafo y, por último, se retorna verdadero.

```cpp
bool createEdge(string id1, string id2, TE w){   
    // check if nodes don't exist
    if (this->vertexes.find(id1) == this->vertexes.end() || this->vertexes.find(id2) == this->vertexes.end())
        return false;

    // create bidirectional edges
    Edge<TV,TE>* newEdge1 = new Edge<TV,TE>();
    newEdge1->edgeVertexes[0] = this->vertexes[id1];
    newEdge1->edgeVertexes[1] = this->vertexes[id2];
    newEdge1->weight = w;

    Edge<TV,TE>* newEdge2 = new Edge<TV,TE>();
    newEdge2->edgeVertexes[0] = this->vertexes[id2];
    newEdge2->edgeVertexes[1] = this->vertexes[id1];
    newEdge2->weight = w;

    // add edges
    this->vertexes[id1]->edges.push_back(newEdge1);
    this->vertexes[id2]->edges.push_back(newEdge2);            

    this->numEdges++;
    return true;
}
```
Para insertar una arista, se verifica si los vértices a unir no existen. Si no existen, se retorna falso. Caso contrario, se procede a crear las dos aristas que permitirán la bidireccionalidad que trae consigo el grafo no dirigido. A estas aristas creadas se les asigna el mismo peso, se añaden a la lista de aristas de cada vértice respectivo, se incrementa el atributo que cuenta la cantidad de aristas y se retorna verdadero.

```cpp
bool deleteVertex(string id)
{
    for(auto &i: this->vertexes){
        for(auto &j: i.second->edges){
            if(j->edgeVertexes[1] == this->vertexes[id]){
                i.second->edges.remove(j);
                break;
            }
        }
    }
    this->vertexes.erase(id);
    this->numVertexes--;
    return true;
}
```
Para eliminar un vértice, se recorre entre todos los vértices disponibles para verificar si el vértice a eliminar pertenece a alguna arista. Si pertenece a alguna arista, se elimina dicho vértice. Una vez se elimine cada arista donde el vértice a eliminar está presente, se procede a eliminar el vértice, a reducir el atributo numVertexes y retornar verdadero.

```cpp
bool deleteEdge(string id1, string id2)
{
    if(this->vertexes.find(id1) == this->vertexes.end() || this->vertexes.find(id2) == this->vertexes.end())
        return false;
    for(auto &i: this->vertexes[id1]->edges){
        if(i->edgeVertexes[1]->data == this->vertexes[id2]->data){
            this->vertexes[id1]->edges.remove(i);
            break;
        }
    }
    for(auto &i: this->vertexes[id2]->edges){
        if(i->edgeVertexes[1]->data == this->vertexes[id1]->data){
            this->vertexes[id2]->edges.remove(i);
        }
        break;
    }
    this->numEdges--;
    return true;
}
```
Para eliminar una arista, se verifica si no existe alguno de los dos vértices involucrados. Si no existe por lo menos uno, se retorna falso. Si existen ambos, se busca la arista en cada vértice y se procede a eliminarla para ambos vértices. Finalmente, se reduce el atributo numEdges y se retorna verdadero.

```cpp
bool findById(string id)
{
    if (this->vertexes.find(id) == this->vertexes.end())
        return false;
    return true;
}
```
Para simplificar la búsqueda de un vértice de acuerdo a su id, se crea la función findById, la cual verifica si se encuentra dicho vértice en el unordered_map de vértices del grafo.

```cpp
TE &operator()(string start, string end)
{
    if (!findById(start))
        throw std::invalid_argument("invalid start node\n");

    auto aristas = this->vertexes[start]->edges;
    for (auto it : aristas){
        //revisa cada par de vertices -> se puede verificar solo la componente[1]
        if (it->edgeVertexes[0] == this->vertexes[end] || it->edgeVertexes[1] == this->vertexes[end])
            return it->weight;      //si es que encuentra una donde este el vertice end
    }
    // no encuentra arista
    throw std::invalid_argument("end node not found\n");
}
```
Para retornar el peso de la arista con el operador (), se comprueba que exista el inicio del grafo. Si no existe, se lanza un error. Si existe, se recorre entre todas las aristas presentes en el vértice de inicio hasta encontrar la arista con el vértice final deseado para posteriormente retornar el peso de dicha arista. Si no se encuentra la arista, se lanza un error.

```cpp
float density()
{
    return (2 * this->numEdges)/(this->numVertexes * (this->numVertexes - 1));
}
```
Para calcular la densidad de un grafo se sigue la ecuación que sigue así: (2 * número de aristas) / (número de vértices * (número de vértices - 1)).

```cpp
bool isDense(float threshold = 0.5)
{
    return this->density() > threshold;
} 
```
Para verifica si la densidad del grafo es mayor a cierto threshold predeterminado, en este caso, 0.5, se ejecuta esta función.

```cpp
bool isConnected()
{
    BFS<TV, TE> treeTraversal(this);
    //DFS<TV, TE> treeTraversal(this->vertexes.begin(), this->vertexes.end());
    int visitedNodes = 0;
    treeTraversal.run([&visitedNodes](Vertex<TV, TE>* currentVertex){
        cout << currentVertex->data << " ";
        visitedNodes++;
    });
    if (visitedNodes == this->vertexes.size())
        return true;
    return false;
}
```
Para verificar si un grafo está conectado, se realiza un recorrido de tipo BFS donde se marca cada vértice visitado, se imprime la data de dicho vértice y, si es que la cantidad de vértices diferentes visitados es igual a la cantidad de vértices totales en el grafo, entonces está conectado.

```cpp
bool isStronglyConnected(){ 
    throw std::runtime_error("funcion invalida\n");
}
```
Para el caso de los grafos no dirigidos, esta función no tiene sentido verificarse, dado que no presenta alguna diferencia a comparación de isConnected.

```cpp
bool empty()
{
    return this->numEdges == 0 && this->numVertexes == 0;
}
```
Para verificar si un grafo está vacío, se revisa si las cantidades de vértices y aristas dan 0.

```cpp
void clear()
{
    for(auto &[k,v]: this->vertexes){
        v->edges.clear();
    }
    this->numEdges = 0;
    this->vertexes.clear();
    this->numVertexes = 0;
}
```
Para vaciar el grafo, se recorre cada uno de los vértices y se vacía la lista de aristas de cada uno. La cantidad de aristas y vertices se asignan a 0. 

```cpp
void displayVertex(string id)
{
    for(auto &i: this->vertexes){
        if(i.first == id)
            for(auto &j:i.second->edges){
                cout << j->edgeVertexes[0]->data << "-" << j->edgeVertexes[1]->data << ", weight: " << j->weight<< endl;
            }
    }
}
```
Para mostrar todas las aristas a las que está conectado un vértice, se recorre el unordered_map de vértices para imprimir cada una de las aristas (vértice inicio, vértice fin, peso de arista).

```cpp
void display()
{
    for(auto &i: this->vertexes){
        cout << "Para el vertice " << i.first << " :" << endl;
        for(auto &j:i.second->edges){
            cout << j->edgeVertexes[0]->data << "-" << j->edgeVertexes[1]->data << ", weight: " << j->weight << endl;
        }
        cout << endl;
    }
}
```
```
//Ejemplo de output
Para el vertice D :
D-E, weight: 1
D-C, weight: 2

Para el vertice A :
A-B, weight: 3

Para el vertice B :
B-A, weight: 1
B-E, weight: 4
```

Para hacer un display de todas las conexiones presentes en el grafo, se recorre por todos los vértices y sus aristas para, posteriormente, imprimir la información de estas (vértice inicio, vértice fin, peso de arista).

```cpp
void adjList()
{
    for (auto [k, v]: this->vertexes)
    {
        cout << v->data << ": ";
        for (Edge<TV, TE>* ed : v->edges)
            cout << " ("<< ed->edgeVertexes[1]->data << " " << ed->weight << ") ";
        cout << endl;
    }
    cout << endl;
}

```

```
//Ejemplo de output
C:  (D 1) 
E:  (B 1)  (D 1) 
D:  (E 1)  (C 1) 
A:  (B 1) 
B:  (A 1)  (E 1) 
```
Para imprimir de una manera que tenga formato de adjacencyList, se recorre por todos los vértices y sus aristas, imprimiendo la información deseada en la forma correcta.


##  Grafo dirigido (Graph/DirectedGraph.h)
### Especificaciones de los métodos
```cpp
bool insertVertex(string id, TV vertex){   
    // check if node already exists
    if (this->vertexes.find(id) != this->vertexes.end())
        return false; 

    // create and insert node in std::unordered_map
    Vertex<TV,TE>* newVertex = new Vertex<TV,TE>();
    newVertex->data = vertex;
    newVertex->id = id;
    this->vertexes[id] = newVertex;
    this->numVertexes++;
    return true;
}
```
De manera similar al grafo no dirigido, para insertar un vértice, lo primero que se verifica es si es que ya existe uno con el mismo id. En caso exista, se retorna falso. En caso no, se crea un nuevo vértice asignándole la data y id respectiva. Luego, se inserta en en el unordered_map de vértices, se incrementa el atributo que cuenta la cantidad de vértices del grafo y, por último, se retorna verdadero.

```cpp
bool createEdge(string id1, string id2, TE w)
{
    if (this->vertexes.find(id1) == this->vertexes.end() || 
        this->vertexes.find(id2) == this->vertexes.end())
        return false;

    Edge<TV,TE>* newEdge = new Edge<TV,TE>();
    newEdge->weight = w;
    newEdge->edgeVertexes[0] = this->vertexes[id1];
    newEdge->edgeVertexes[1] = this->vertexes[id2];
    this->vertexes[id1]->edges.push_back(newEdge);
    this->numEdges++;
    return true;
}     
```
A diferencia del grafo no dirigido, al momento de crear una arista, ya no hacemos la consideración de crearla en ambas direcciones. Esta vez el orden en que los parámetros id1 y id2 están puestos, seguirán el orden de vértice source y vértice destino. De esa manera, se creará el vértice que solo irá en la dirección de id1->id2. Luego, procede a añadirlo a la lista de aristas del vértice source y se aumenta la cantidad de aristas del grafo.

```cpp
bool deleteVertex(string id)
{
    for(auto &i: this->vertexes){
        for(auto &j: i.second->edges){
            if(j->edgeVertexes[1] == this->vertexes[id]){
                i.second->edges.remove(j);
                break;
            }
        }
    }
    this->vertexes.erase(id);
    this->numVertexes--;
    return true;
}
```
Al igual que para el grafo no dirigido, para eliminar un vértice, se recorre entre todos los vértices disponibles para verificar si el vértice a eliminar pertenece a alguna arista. Si pertenece a alguna arista, se elimina dicho vértice. Una vez se elimine cada arista donde el vértice a eliminar está presente, se procede a eliminar el vértice, a reducir el atributo numVertexes y retornar verdadero.

```cpp
bool deleteEdge(string id1, string id2)
{
    if(this->vertexes.find(id1) == this->vertexes.end() || this->vertexes.find(id2) == this->vertexes.end())
        return false;
    for(auto &i: this->vertexes[id1]->edges){
        if(i->edgeVertexes[1]->data == this->vertexes[id2]->data){
            this->vertexes[id1]->edges.remove(i);
            break;
        }
    }
    this->numEdges--;
    return true;
}
```
A diferencia del grafo no dirigido, para eliminar una arista, solo se recorre la lista de aristas del vértice id1 (source), hasta encontrar la arista que conecte con el vértice id2 (destino) para luego eliminarla y reducir la cantidad de aristas del grafo.

```cpp
bool findById(string id)
{
    if (this->vertexes.find(id) == this->vertexes.end())
        return false;
    return true;
}
```
Para simplificar la búsqueda de un vértice de acuerdo a su id, se crea la función findById, la cual verifica si se encuentra dicho vértice en el unordered_map de vértices del grafo.

```cpp
TE &operator()(string start, string end)
{
    if (!findById(start))
        throw std::invalid_argument("invalid start node\n");

    auto aristas = this->vertexes[start]->edges;
    for (auto it : aristas){
        //revisa cada par de vertices -> se puede verificar solo la componente[1]
        if (it->edgeVertexes[0] == this->vertexes[end] || it->edgeVertexes[1] == this->vertexes[end])
            return it->weight;      //si es que encuentra una donde este el vertice end
    }
    // no encuentra arista
    throw std::invalid_argument("end node not found\n");
}

TE& operator()(string start, string end)
{
    if (!findById(start) || !findById(end))
        throw std::invalid_argument("inexistent node(s)\n");
    for (Edge<TV, TE>* ed : this->vertexes[start]->edges)
        if (ed->edgeVertexes[1]->data == this->vertexes[end]->data)
            return ed->weight;
    throw std::invalid_argument("inexistent edge\n");
} 
```
Para retornar el peso de la arista con el operador (), se comprueba que exista el inicio del grafo y el final. Si uno de los dos no existe, se lanza un error. Si existe, se recorre entre todas las aristas presentes en el vértice de inicio hasta encontrar la arista con el vértice final deseado para posteriormente retornar el peso de dicha arista. Si no se encuentra la arista, se lanza un error.

```cpp
float density()
{
    return (2 * this->numEdges)/(this->numVertexes * (this->numVertexes - 1));
}
```
Para calcular la densidad de un grafo se sigue la ecuación que sigue así: (2 * número de aristas) / (número de vértices * (número de vértices - 1)).

```cpp
bool isDense(float threshold = 0.5)
{
    return this->density() > threshold;
} 
```
Para verifica si la densidad del grafo es mayor a cierto threshold predeterminado, en este caso, 0.5, se ejecuta esta función.

```cpp
bool empty()
{
    return this->numEdges == 0 && this->numVertexes == 0;
}
```
Para verificar si un grafo está vacío, se revisa si las cantidades de vértices y aristas dan 0.

```cpp
void clear()
{
    for(auto &[k,v]: this->vertexes){
        v->edges.clear();
    }
    this->numEdges = 0;
    this->vertexes.clear();
    this->numVertexes = 0;
}
```
Para vaciar el grafo, se recorre cada uno de los vértices y se vacía la lista de aristas de cada uno. La cantidad de aristas y vertices se asignan a 0. 

```cpp
void displayVertex(string id)
{
    for(auto &i: this->vertexes){
        if(i.first == id)
            for(auto &j:i.second->edges){
                cout << j->edgeVertexes[0]->data << "-" << j->edgeVertexes[1]->data << ", weight: " << j->weight<< endl;
            }
    }
}
```
Para mostrar todas las aristas a las que está conectado un vértice, se recorre el unordered_map de vértices para imprimir cada una de las aristas (vértice inicio, vértice fin, peso de arista).

```cpp
void display()
{
    for(auto &i: this->vertexes){
        cout << "Para el vertice " << i.first << " :" << endl;
        for(auto &j:i.second->edges){
            cout << j->edgeVertexes[0]->data << "-" << j->edgeVertexes[1]->data << ", weight: " << j->weight << endl;
        }
        cout << endl;
    }
}
```
```
//Ejemplo de output
Para el vertice D :
D-E, weight: 1
D-C, weight: 2

Para el vertice A :
A-B, weight: 3

Para el vertice B :
B-A, weight: 1
B-E, weight: 4
```

Para hacer un display de todas las conexiones presentes en el grafo, se recorre por todos los vértices y sus aristas para, posteriormente, imprimir la información de estas (vértice inicio, vértice fin, peso de arista).

```cpp
void adjList()
{
    for (auto [k, v]: this->vertexes)
    {
        cout << v->data << ": ";
        for (Edge<TV, TE>* ed : v->edges)
            cout << " ("<< ed->edgeVertexes[1]->data << " " << ed->weight << ") ";
        cout << endl;
    }
    cout << endl;
}

```

```
//Ejemplo de output
C:  (D 1) 
E:  (B 1)  (D 1) 
D:  (E 1)  (C 1) 
A:  (B 1) 
B:  (A 1)  (E 1) 
```
Para imprimir de una manera que tenga formato de adjacencyList, se recorre por todos los vértices y sus aristas, imprimiendo la información deseada en la forma correcta.

### Algorithms:

Los algoritmos que se implementaron fueron los siguientes:

#### BFS
```cpp
template<typename TV, typename TE>
class BFS{
private:
	unordered_map<Vertex<TV, TE>* , bool> visited;
	Vertex<TV, TE>* startV;
public:
	BFS() = default;
	BFS(Graph<TV, TE>* graph)
	{
		auto un_map = graph->vertexes;
		this->startV = (un_map.begin())->second;
		for (auto [k, v] : un_map)
			this->visited[v] = false;
		//for (auto [k, v] : visited)
		//	cout << k->data << " -> " << v << endl;
	}

	BFS(Graph<TV, TE>* graph, TV dataId)
	{
		auto un_map = graph->vertexes;
		for (auto [k, v] : un_map)
		{
			if (v->data == dataId)
				this->startV = v;
			this->visited[v] = false;
		}
		//for (auto [k, v] : visited)
		//	cout << k->data << " -> " << v << endl;
	}

	BFS(umap_it<TV, TE> start, umap_it<TV, TE> end, Vertex<TV, TE>* startVertex = nullptr)
	{
		if (startVertex == nullptr)			// set first vertex
			startVertex = start->second;		
		this->startV = startVertex;

		while (start != end)				// iterate over all [k, v] in unordered_map
		{
			Vertex<TV, TE>* vertexIt = start->second;
			//cout << vertexIt->data << " ";
			visited[vertexIt] = false;		// initialize all as unvisited
			start = next(start);
		}
		//cout << '\n' << startVertex->data << '\n';
	}

	void setInitialVertex(Vertex<TV, TE>* startVV)
	{
		this->startV = startVV;
	}

	template<typename Op>
	void run(Op op)
	{
		//for (auto [k, v]: this->visited)
		//	cout << k->data << ": " << boolalpha << v << endl;
		queue<Vertex<TV, TE>*> qu;
		qu.push(this->startV);
		while (!qu.empty())
		{
			auto currentV = qu.front();
			qu.pop();
			if (this->visited[currentV] == true)
				continue;	// verify if node already visited
			this->visited[currentV] = true;
			op(currentV);
			for (auto edge : currentV->edges)
			{
				auto adj = edge->edgeVertexes[1];
				if (this->visited[adj] == false)
					qu.push(adj);		//cout << '\t' << currentV->data << " - " << adj->data << endl;
			}
		}
	}
};
```
El algoritmo BFS está hecho para realizar un recorrido desde un punto Start hasta un punto End, desde un punto Start en específico o, incluso, sin un punto declarado previamente. Cuando se inicializa la clase BFS, se realiza un recorrido para inicializa un unordered_map inicializado en false para cada vértice presente en el grafo. Este mapa tiene como objetivo ir registrando los id's de los vértices visitados como true, mientras los que no son visitados los mantiene como false. Después, para ejecutar el algoritmo se tiene que llamar al método run, el cual es capaz de recibir una función lambda que se ejecuta más adelante en el código. La idea del BFs es almacenar en un queue los vértices adyacentes al vértice que se está visitando en el front, siempre y cuando estos no hayan sido visitados. Antes de almacenar los vértices adyacentes se ejecuta la operación deseada (enviada como parámetro).

#### DFS

```cpp
template<typename TV, typename TE>
class DFS{
private:
	unordered_map<Vertex<TV, TE>* , bool> visited;
	Vertex<TV, TE>* startV;
public:
	DFS() = default;
	DFS(Graph<TV, TE>* graph)
	{
		auto un_map = graph->vertexes;
		this->startV = (un_map.begin())->second;
		for (auto [k, v] : un_map)
			this->visited[v] = false;
		//for (auto [k, v] : visited)
		//	cout << k->data << " -> " << v << endl;
	}

	DFS(Graph<TV, TE>* graph, TV dataId)
	{
		auto un_map = graph->vertexes;
		for (auto [k, v] : un_map)
		{
			if (v->data == dataId)
				this->startV = v;
			this->visited[v] = false;
		}
		//for (auto [k, v] : visited)
		//	cout << k->data << " -> " << v << endl;
	}

	void setInitialVertex(Vertex<TV, TE>* startVV)
	{
		this->startV = startVV;
	}

	DFS(umap_it<TV, TE> start, umap_it<TV, TE> end, Vertex<TV, TE>* startVertex = nullptr)
	{
		if (startVertex == nullptr)			// set first vertex
			startVertex = start->second;		
		this->startV = startVertex;

		while (start != end)				// iterate over all [k, v] in unordered_map
		{
			Vertex<TV, TE>* vertexIt = start->second;
			//cout << vertexIt->data << " ";
			this->visited[vertexIt] = false;		// initialize all as unvisited
			start = next(start);
		}
		//cout << '\n' << startVertex->data << '\n';
	}

	template<typename Op>
	void run(Op op)
	{
		//for (auto [k, v]: this->visited)
		//	cout << k->data << ": " << boolalpha << v << endl;
		stack<Vertex<TV, TE>*> st;
		st.push(this->startV);
		while (!st.empty())
		{
			auto currentV = st.top();
			st.pop();
			if (this->visited[currentV] == true)
				continue;	// verify if node already visited
			this->visited[currentV] = true;
			op(currentV);
			for (Edge<TV, TE>* edge : currentV->edges)
			{
				auto adj = edge->edgeVertexes[1];
				if (this->visited[adj] == false)
					st.push(adj);		//cout << '\t' << currentV->data << " - " << adj->data << endl;
			}
		}
	}
};
```
El DFS funciona de manera muy similar al BFS en cuanto a estructura de código. La principal y vital diferencia es el uso de un stack en vez de un queue, lo cual hace que se explora de manera profunda en vez de ancha.


#### Kruskal

```cpp
template<typename TV, typename TE>
class Kruskal{
	vector<Edge<TV, TE>*> vEdges;
	vector<Vertex<TV, TE>*> vNodes;
	DisjoinSetArray<Vertex<TV, TE>*>* ds = nullptr;
	unordered_map<Vertex<TV, TE>*, int> posVertex;
public:
	Kruskal(Graph<TV, TE>* graph)
	{
		for (auto [id, vertex] : graph->vertexes)
		{
			vNodes.push_back(vertex);
			for (Edge<TV, TE>* ed : vertex->edges)
				vEdges.push_back(ed);		// add edges on std::vector
		}
		this->ds = new DisjoinSetArray<Vertex<TV, TE>*>(this->vNodes);
		int idx = 0;
		for (auto node : this->vNodes)			// initialize position hash
			posVertex[node] = idx++;
	}
	~Kruskal()
	{
		vEdges.clear(); posVertex.clear(); vNodes.clear();
	}

	UnDirectedGraph<TV, TE> apply()
	{
		vector<Edge<TV, TE>*> nEdges;
		sort(vEdges.begin(), vEdges.end(), [](Edge<TV, TE>* e1, Edge<TV, TE>* e2){
			return e1->weight < e2->weight;
		});
		//for (auto ed: vEdges)	cout << ed << '\n';	cout << '\n';
		//for (auto [k, idx] : posVertex) cout << k->data << " -> " << idx << endl;

		for (Edge<TV, TE>* ed: vEdges)
		{
			auto posFNode = posVertex[ed->edgeVertexes[0]];
			auto posSNode = posVertex[ed->edgeVertexes[1]];
			if (!ds->isConnected(posFNode, posSNode))
			{
				nEdges.push_back(ed);
				ds->Union(posFNode, posSNode);
			}
		}
		auto mstResult = new UnDirectedGraph<TV, TE>();
		for (auto v : this->vNodes)
			mstResult->insertVertex(v->data, v->data);
		for (auto ed: nEdges)
		{	// cout << ed << '\n';
			auto id1 = ed->edgeVertexes[0]->data;
			auto id2 = ed->edgeVertexes[1]->data;
			mstResult->createEdge(id1, id2, ed->weight);
		}
			
		return *mstResult;
	}
};
```



#### Prim
```cpp
using peso = double;
//peso, start y end 
using weightPar = pair<peso, pair<string, string>>; 

struct ComparatorPrim{
    bool operator()(const weightPar w1, const weightPar w2) const {
        return w1.first > w2.first;
    }
};


template<typename TV, typename TE>
class Prim{
private:
	int costo;
	UnDirectedGraph<TV,TE>* outGraph;
   
public:
	Prim(DirectedGraph<TV, TE>* graph, string start)
	{
		if (!(graph->findById(start))) throw std::invalid_argument("node not found\n");

		priority_queue<weightPar,vector<weightPar>, ComparatorPrim> pq;        
		unordered_map<string, bool> visitados;
		for (auto i : graph->vertexes){
            visitados[i.first] = false;
        }
		outGraph = new UnDirectedGraph<TV,TE>;	

		visitados[start] = true;
		outGraph->insertVertex(start, graph->vertexes[start]->data);

		Vertex<TV,TE>* auxVert = graph->vertexes[start];

		for(auto currEdge: auxVert->edges){
			Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
			if(visitados[currVert->id] == false){
				pq.push(make_pair(currEdge->weight, make_pair(start,currVert->id)));
			}
		}
		costo = 0;

		while(!pq.empty()){
			string idS = pq.top().second.first;
			string idF = pq.top().second.second;
			auto peso = pq.top().first;

			pq.pop();

			if(visitados[idF] == false){
				costo += peso;
				visitados[idF] = true;
				outGraph->insertVertex(idF, graph->vertexes[idF]->data);
				outGraph->createEdge(idS, idF, peso);
				Vertex<TV,TE>* vertStart = graph->vertexes[idF];

				for (auto currEdge: vertStart->edges){
					Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
					if (visitados[currVert->id] == false){
						pq.push(make_pair(currEdge->weight, make_pair(vertStart->id, currVert->id)));
					}
				}
			}
		}
	}

	Prim(Graph<TV, TE>* graph, string start)
	{
		if (!(graph->findById(start))) throw std::invalid_argument("node not found\n");

		priority_queue<weightPar,vector<weightPar>, ComparatorPrim> pq;        
		unordered_map<string, bool> visitados;
		for (auto i : graph->vertexes){
            visitados[i.first] = false;
        }
		outGraph = new UnDirectedGraph<TV,TE>;	

		visitados[start] = true;
		outGraph->insertVertex(start, graph->vertexes[start]->data);

		Vertex<TV,TE>* auxVert = graph->vertexes[start];

		for(auto currEdge: auxVert->edges){
			Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
			if(visitados[currVert->id] == false){
				pq.push(make_pair(currEdge->weight, make_pair(start,currVert->id)));
			}
		}
		costo = 0;

		while(!pq.empty()){
			string idS = pq.top().second.first;
			string idF = pq.top().second.second;
			auto peso = pq.top().first;

			pq.pop();

			if(visitados[idF] == false){
				costo += peso;
				visitados[idF] = true;
				outGraph->insertVertex(idF, graph->vertexes[idF]->data);
				outGraph->createEdge(idS, idF, peso);
				Vertex<TV,TE>* vertStart = graph->vertexes[idF];

				for (auto currEdge: vertStart->edges){
					Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
					if (visitados[currVert->id] == false){
						pq.push(make_pair(currEdge->weight, make_pair(vertStart->id, currVert->id)));
					}
				}
			}
		}
	}

	int primmCosto(){
		return costo;
	}

	UnDirectedGraph<TV,TE>* apply()
	{
		return outGraph;
	}
};
```
El algoritmo Prim está hecho de tal manera que puede recibir como parámetro un grafo de cualquier tipo (dirigido, no dirigido) y un punto de inicio. Primero que nada, preparamos una estructura llamada weightPar que almacena pares (aunque hubiera sido mejor que sea un tupla de 3, pensándolo mejor), donde se guarda el peso de la arista, el vértice source y el vértice destiny. Se encarga de inicializar un unordered map de visitados en falso, a excepción del vértice de inicio, el cual inicia como verdadero. La idea consiste en almacenar en un priority queue todas las aristas adyacentes al vértice que se encuentra en el top del pq, siempre y cuando estas no hayan sido visitadas previamente. Es importante mencionar que el pq está hecho de tal manera que siempre se ponga primero a la arista de menor peso. A lo largo de todo el recorrido, se va sumando el peso de cada arista al atributo costo y, a su vez, se van insertando los vértices y aristas que han sido visitados. Con el método apply(), se termina retornando un grafo no dirigido con los vértices y aristas visitados, es decir, el MST. Con el método primmCosto(), se retorna el costo total del recorrido.

#### Djikstra
```cpp
template<typename TV, typename TE>
class Dijkstra{
    map<Vertex<TV, TE>*, TE> dist;

    void run(Graph<TV, TE>* graph, Vertex<TV, TE>* source)
    {
        auto comparer = [](pair<TE, Vertex<TV, TE>*> p1, pair<TE, Vertex<TV, TE>*> p2){
            return p1.first > p2.first;
        };
        priority_queue<pair<TE, Vertex<TV, TE>*>, vector<pair<TE, Vertex<TV, TE>*>>, decltype(comparer) > pq(comparer, vector<pair<TE, Vertex<TV, TE>*>>());
        for (const auto& [id, vertex] : graph->vertexes)
            this->dist[vertex] = INF;
        pq.push({0, source});
        this->dist[source] = 0;

        while (!pq.empty())
        {
            Vertex<TV, TE>* curr = pq.top().second;
            TE curr_d = pq.top().first;
            pq.pop();

            for (const auto& ed : curr->edges)
            {
                auto src = ed->edgeVertexes[1];
                if (curr_d + ed->weight < this->dist[src])
                {
                    dist[src] = curr_d + ed->weight;
                    pq.push({dist[src], src});
                }
            }
        }
    }
public:
    Dijkstra(Graph<TV, TE>* graph){
        Vertex<TV, TE>* start;
        for (auto [id, vertex] : graph->vertexes)
        {
            if (id == "1")
            {
                start = vertex;
                break;
            }
        }

        run(graph, start);
    }
    Dijkstra(Graph<TV, TE>* graph, Vertex<TV, TE>* source){
        run(graph, source);
    }


    map<Vertex<TV, TE>*, TE> run(){ return dist; }
};
```
El Djikstra está hecho de tal manera que puede recibir un grafo de cualquier tipo con un vértice de inicio para iniciar el recorrido o solamente el grafo, ya que dentro de la función decide agarrar un vértice como el vértice de inicio. Cuando se inicia el algoritmo con el método run(), se inicializa un mapa de distancias para cada vértice en INF. Luego, se empuja al priority queue el vértice de inicio con costo 0. A partir de ahí, se van explorando los vértices adjacentes y se agregan al priority queue sumándoles el costo acumulado para llegar hast ahí. Si es que se encuentra una arista de coste menor para llegar al siguiente vértice, se actualiza el valor de la distancia de dicho vértice. Se retorna el mapa de las distancias para cada vértice.


#### AStar
```cpp
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
```
Este algoritmo se caracteriza por tener, además de los datos de los pesos en los bordes, una heurística que sumada al peso determina por qué vértices avanzar hasta llegar al nodo final. En esta implementación, tenemos 3 atributos clave: parent_child, que almacena el padre a través del cual se debe llegar al niño, is_visited, que restringe el cambio de pesos entre nodos, y cost, que almacena el costo mínimo para llegar a ese nodo. Con estos atributos, sumados al vértice inicial y final, es posible construir el algoritmo. En resumen, los vértices que eran posibles caminos se almacenan y eliminan de una pila, hasta que se alcanza el vértice final. Luego, desde ese vértice final, se busca su padre, luego el padre de ese padre, y así sucesivamente hasta que el padre sea el nodo inicial (esto está 100% garantizado). De esa manera obtenemos la forma menos costosa.

#### BestBFS
```cpp
using peso = double;
//peso, start y end 
using weightPar = pair<peso, pair<string, string>>; 

struct Comparator{
    bool operator()(const weightPar w1, const weightPar w2) const {
        return w1.first > w2.first;
    }
};

template<typename TV, typename TE>
class BestBFS{
private:
    DirectedGraph<TV,TE>* outGraph;

public:
    BestBFS() = default;

    BestBFS(Graph<TV,TE>* graph, string start, string end){
        if (!(graph->findById(start)) || !(graph->findById(end))) throw std::invalid_argument("one or both nodes not found\n");

        unordered_map<string, bool> visitados;

        for (auto i : graph->vertexes){
            visitados[i.first] = false;
        }
        //weightpar = weight, start, end
        priority_queue<weightPar,vector<weightPar>, Comparator> pq;        


        pq.push(make_pair(0,make_pair(start,"")));

        outGraph = new DirectedGraph<TV,TE>;
        outGraph->insertVertex(start, graph->vertexes[start]->data);
        
        visitados[start] = true;

        while(!pq.empty()){
            string idF = "";
            if (pq.top().second.second == ""){
                idF = pq.top().second.first;
            } else{
                idF = pq.top().second.second;
            }

            string idS = pq.top().second.first;
            auto weight = pq.top().first;
            Vertex<TV,TE>* vertStart = graph->vertexes[idF];

            if (idF != "" && (visitados[vertStart->id] == false)){
                visitados[vertStart->id] = true;
                outGraph->insertVertex(idF, vertStart->data);
                outGraph->createEdge(idS,idF, weight);
            }
            
            pq.pop();

            if (idS == end) break;

            for (auto currEdge : vertStart->edges){
                Vertex<TV,TE>* currVert = currEdge->edgeVertexes[1];
                if (visitados[currVert->id] == false){
                    pq.push(make_pair(currEdge->weight, make_pair(vertStart->id, currVert->id)));
                }
            }
        }
    }

    DirectedGraph<TV,TE>* apply() {
        return outGraph;
    }
};
```
Al igual que para el Prim, volvemos a utilizar el renombramiento de pares weightPar, el cual almacena el costo de la arista, el id del vértice source y el id del vértice destiny. El algoritmo BestBFS puede recibir tanto un grafo dirigido como uno no dirigido. Es necesario que también reciba como parámetro el id del vértice de inicio y el id del vértice al que se quiere llegar. Primero que nada, se verifica que ambos vértices existan. Después, se inicializa un unorderedmap de vértices visitados en falso. Se agrega al priority queue el vértice de inicio con costo 0 y se marca como visitado. Se guardan los datos del weightPar presente en el top del pq, para luego eliminarlo con un pop. Se verifica si es que el vértice en el top ha sido visitado, si no fue visitado se marca como visitado. Después, se verifica si es que se llegó al vértice destiny, si es así se termina la función. Si no, se recorren todos los vértices adyacentes siempre y cuando estos no hayan sido visitados. Para cada iteración, se va armando un grafo dirigido con las aristas y vértices visitados, el cual es retornado con el método apply().

#### FloydWarshall
```cpp
template<typename TV, typename TE>
class FloydWarshall{
    map<Vertex<TV, TE>*, map<Vertex<TV, TE>*, TE>> dist;
public:
    FloydWarshall(DirectedGraph<TV, TE>* graph)
    {
        for (const auto& v1 : graph->vertexes)
            for (const auto& v2 : graph->vertexes)
                this->dist[v1.second][v2.second] = (*graph->vertexes[v1.first])[v2.second];
        for (const auto& v1 : graph->vertexes)
            for (const auto& v2 : graph->vertexes)
                for (const auto& v3 : graph->vertexes)
                    if (dist[v1.second][v2.second] < INF && dist[v3.second][v2.second] < INF)
                        this->dist[v1.second][v2.second] = min(dist[v1.second][v2.second], dist[v1.second][v3.second] + dist[v3.second][v2.second]);
    }
    auto run(){ return this->dist; }
};
```

#### BellmanFord
```cpp
template<typename TV, typename TE>
class BellmanFord{
private:
    DirectedGraph<TV,TE>* graph;
    string start;
    bool cicloNegativo = false;
public:
    BellmanFord(DirectedGraph<TV, TE>* graph, string start)
    {
        this->graph = graph;
        this->start = start;
    };

    unordered_map<TV,TE> apply(){
        unordered_map<TV, TE> distancia;
        DirectedGraph<TV,TE>* result;

        for (auto i: graph->vertexes){
            distancia[i.first] = INF;
        } distancia[start] = 0;

        auto tmn = graph->vertexes.size();


        for(int i = 0; i < tmn - 1; i++){
            for (auto currVert : graph->vertexes){
                for (auto currEdge : currVert.second->edges){
                    string idS = currEdge->edgeVertexes[0]->id;
                    string idF = currEdge->edgeVertexes[1]->id;
                    auto peso = currEdge->weight;
                    
                    if (distancia[idS] != INF && (distancia[idS]+peso < distancia[idF]))
                    {
                        distancia[idF] = distancia[idS]+peso;
                    }
                }
            }
        }

        for (auto currVert : graph->vertexes){
            for (auto currEdge : currVert.second->edges){
                string idS = currEdge->edgeVertexes[0]->id;
                string idF = currEdge->edgeVertexes[1]->id;
                auto peso = currEdge->weight;

                if (distancia[idS] != INF && (distancia[idS]+peso < distancia[idF]))
                {
                    cout << "Grafo tiene ciclo de peso negativo";
                    this->cicloNegativo = true;
                    return unordered_map<TV,TE>();
                }
            }
        }
        return distancia;
    }

    bool hayNegCycle(){
        return cicloNegativo;
    }
};
```
El algoritmo BellmanFord viene a ser muy similar al Djikstra, en el sentido que este trata de hallar también el camino más corto. Sin embargo, la ventaja que ofrece es que es capaz de funcionar con grafos dirigidos con pesos negativos y, a su vez, puede detectar ciclos negativos, pero como desventaja es que resulta siendo un método muy exhaustivo el cual termina siendo más complejo que el Djikstra. Este algoritmo solo puede recibir un grafo dirigido y un punto de inicio, los cuales los guarda como atributos en el constructor. Primero, se inicializa un mapa de distancias, el cual inicia para todos como INF, a excepción del vértice de inicio el cual inicia con distancia 0. Después, se hace un recorrido del número de vértices en el grafo - 1, para cada una de las aristas, trata de dar los caminos de distancias más cortas. Después, se vuelve a recorrer de manera final todas las aristas y, en caso se encuentre un camino más corto, este se reporta como un ciclo negativo y la función retorna un mapa vacío. Si es que no se detecta un ciclo negativo, retorna el mapa de las distancias hallado. El método hayNegCycle() retorna un booleano que indica si hubo o no un ciclo negativo.

## Tester
Para experimentar de manera exhaustiva con cada uno de los algoritmos y estructuras presentadas, se realizó un tester en el directorio tester/tester.h, el cual se ejecuta a través del main. Este tester está hecho de tal manera que nos permite experimentar tanto con ejemplos puestos por nosotros, como por ejemplos sacados de un archivo JSON. Ambas formas aceptan interactuar con grafos dirigidos y no dirigidos. Al correr el tester, aparecerá un menú el cual dará a elegir al usuario el método de testeo que el desea: Undirected Tester, Directed Tester, Undirected Parser o Directed Parser. Cada test, tiene asignado a si mismo un JSON para leer o un directorio a un archivo txt, el cual contiene los vértices y aristas del grafo a crear. Cada algoritmo tiene 1 o 2 testcases para experimentar consigo.

## Tester_Imagenes
Para el caso del Tester, se decidió realizar ejemplos sacados de PPTs de Clase u otro material anexado. El output que se recibe como resultado se corrobora con la imagen respectiva en la carpeta Tester/imgTest.


## JSON file parser
* Construye un grafo a partir de una archivo JSON de aereopuertos del mundo. 


### Methods:
```cpp
void clear(); // Clears parser saved atributes

void readJSON(); // Parses JSON file and saves data into class
// NOTE: each derived class has its own readJSON method

void uGraphMake(UndirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified undirected graph

void dGraphMake(DirectedGraph<string, double> &tempGraph); // Adds the parsed data into the specified directed graph
```

## [Git Karma Guidelines](http://karma-runner.github.io/5.2/dev/git-commit-msg.html)

```
<type>(<scope>): <subject>

<body>
```

### Allowed ```<type>``` values

* feat (new feature for the user, not a new feature for build script)
* fix (bug fix for the user, not a fix to a build script)
* docs (changes to the documentation)
* style (formatting, missing semi colons, etc)
* refactor (refactoring production code, eg. renaming a variable)
* test (adding missing tests, refactoring tests)
* chore (updating grunt tasks etc)

### Allowed ```<scope>``` values

* graph
* directedGraph
* undirectedGraph
* parser
* main
* tester


> **PD:** Puntos extras sobre Evaluación Continua si se implementa una GUI.
