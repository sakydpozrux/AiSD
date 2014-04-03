#include <cstdio>
#include <vector>
#include <queue>


struct Edge
{
    unsigned int a, b, w;

    Edge(const unsigned int a, const unsigned int b, const unsigned int w) : a(a), b(b), w(w)
    { }
};

bool operator< (const Edge& a, const Edge& b)
{
    return a.w > b.w;
}

struct UnionFind
{
    std::vector<unsigned int> groups;

    unsigned int Find(const unsigned int a) // Find point group's representant.
    {
        return ( groups[a] == a ? a : (groups[a] = Find(groups[a])) );
    }

    bool Union(const unsigned int a, const unsigned int b)
    {
        return ( Find(a) == Find(b) ? 0 : (groups[Find(a)] = Find(b)) );
    }

    UnionFind(const unsigned int n)
    {
        groups.resize(n+1);

        for (unsigned int i = 0; i <= n; ++i)
            groups[i] = i; // At the beginning each point points at itself.
    }
};

template <class T>
class reservable_priority_queue : public std::priority_queue<T>
{
public:
    reservable_priority_queue(unsigned int capacity)
    {
        this->c.reserve(capacity);
    }
};

int main()
{
    unsigned int n, m; // number of places and number of cords
    scanf("%u %u", &n, &m);

    UnionFind graph(n);
    reservable_priority_queue<Edge> edges(m);

    unsigned int a, b, w;
    for (unsigned int i = 0; i < m; ++i)
    {
        scanf("%u %u %u", &a, &b, &w);
        edges.push( Edge(a, b, w) );
    }

    unsigned int edgeCounter = 1;
    Edge e(0, 0, 0);
    while (edgeCounter < n)
    {
        e = edges.top();
        edges.pop();
        if ( graph.Union( e.a, e.b ) )
            ++edgeCounter;
    }

    printf("%u\n", e.w);

    return 0;
}
