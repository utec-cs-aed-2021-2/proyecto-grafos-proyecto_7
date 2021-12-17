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
```cpp
//Given the graph
UndirectedGraph<char, int> graph;

//1- Generates a MST graph using the Kruskal approach (only for undirected graphs)
Kruskal<char, int> kruskal(&graph);
UndirectedGraph<char, int> result = kruskal.apply();//return a tree

//2- Generates a MST graph using the Prim approach (only for undirected graphs)
Prim<char, int> prim(&graph, "A");
UndirectedGraph<char, int> result = prim.apply();//return a tree

//3- A *
AStar<char, int> astar(&graph, "A", "Z", vector<int> heuristics);
UndirectedGraph<char, int> result = astar.apply();

```



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
