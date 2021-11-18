#ifndef DSARRAY_H
#define DSARRAY_H

#include "ds.h"

template <typename T>
class DisjoinSetArray: public DisjoinSet<T>
{
private:
    // define the structures

    T* data = nullptr;
    int* parent = nullptr;
    int* rank = nullptr;
    int capacity = 0;

    void resize(int nc)
    {
        int *nPa = new int[nc], *nRank = new int[nc];
        T* nData = new T[nc];

        for (int i = 0; i < min(capacity, nc); ++i) 
            nData[i] = data[i], nPa[i] = parent[i], nRank[i] = rank[i];

        delete[] data; delete[] parent, delete[] rank;
        data = nullptr ; rank = nullptr; parent = nullptr;

        data = nData; parent = nPa; rank = nRank;
        capacity = nc;
    }
public:
    DisjoinSetArray() = default;

    explicit DisjoinSetArray(vector<T> vec)
    {
        capacity = vec.size();
        data = new T[capacity];
        for (int i = 0; i < capacity; ++i) data[i] = vec[i];

        parent = new int[capacity];
        rank = new int[capacity];
        this->MakeSet();
    }       // O(2n)

    ~DisjoinSetArray() = default;

    // implement all functions
    void MakeSet(int x)
    { rank[x] = 0; parent[x] = x; }                   // O(1)

    void MakeSet()
    {
        for (int i = 0; i < capacity; ++i)
            this->MakeSet(i);
    }                        // O(n)

    int Find(int x)
    {
        if (parent[x] == x)
            return x;
        return parent[x] = Find(parent[x]);
    }                       // O(alpha(n))

    void Union(int x, int y)
    {
        auto idX = Find(x);
        auto idY = Find(y);

        if (idX == idY)
            return;
        else if (rank[idX] < rank[idY])
            parent[idX] = idY;
        else if (rank[idX] > rank[idY])
            parent[idY] = idX;
        else
        {
            parent[idY] = idX;
            rank[idX]++;
        }
    }              // O(alpha(n))

    bool isConnected(int x, int y)
    { return Find(x) == Find(y); }        // O(2*alpha(n)) = O(alpha(n))

    int size(){ return capacity; }              // O(1)

    int sets()
    {
        int cnt = 0;
        for (int i = 0; i < capacity; ++i)
            if (parent[i] == i) cnt++;
        return cnt;
    }                            // O(n)

    int size(int x)
    {
        int cnt = 0;
        int idxP = Find(x);
        for (int i = 0; i < capacity; ++i)
            if (Find(i) == idxP) cnt++;
        return cnt;
    }                       // O(n * alpha(n)) = O(n)

    void add(T element, int x)
    {
        this->resize(capacity + 1);         // add one space in arrays
        // initialize new "Node"
        data[capacity - 1] = element;
        parent[capacity - 1] = x;
        rank[capacity - 1] = 0;
    }            // O(n) * resize

    vector<T> getElementsSet(int x)
    {
        vector<T> result;
        int idxP = Find(x);
        for (int i = 0; i < capacity; ++i)
            if (Find(i) == idxP) result.push_back(data[i]);
        return result;
    }       // O(n * alpha(n)) = O(n)

    void print()
    {
        for (int i = 0; i < capacity; ++i)
            cout << " (" << data[i] << ", " << data[parent[i]] << ") ";
        cout << endl;
    }                          // O(n)
};


#endif