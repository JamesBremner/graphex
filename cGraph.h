class cVertex
{
public:
	void setName( const std::wstring& n )
	{
		myName = n;
	}
	void setXY( int X, int Y )	{ x = X, y = Y; }
	void Draw( System::Drawing::Graphics^ g );


	std::wstring myName;
	int x;
	int y;
	int myColor;
};

class cEdge
{
	int a;
	int b;
public:

	cEdge() {}
	cEdge( int A, int B )
		: a( A ), b( B )
	{}
	bool operator ==( const cEdge& other ) const
	{ return a == other.a && b == other.b; }
};

enum vertex_position_t { vertex_position = 502 };
namespace boost { 
   BOOST_INSTALL_PROPERTY(vertex, position); 
} 


class cGraph
{
public:
	void AddVertex();
	void AddEdge( int row, int col, const std::wstring& name );
	void RemoveEdge( int a, int b )		{ boost::remove_edge( a, b, myGraph ); }

	void Arrange();
	void MapColor();

	void setNameVertex( int i,  System::String^ n );
	const std::wstring& getNameVertex( int i );
	int getVertexCount()			{ return boost::num_vertices( myGraph); }

	int getEdgeCount()				{ return boost::num_edges( myGraph); }
	bool getEdge( int& iva, int& ivb, int ei );

	void DrawLayout( System::Drawing::Graphics^ g );

private:

	// The BGL graph

	typedef boost::square_topology<>::point_type point;
	typedef boost::property< boost::vertex_index_t, int,
			boost::property< vertex_position_t, point,
			cVertex > >
				vertex_props_t;
 	typedef boost::adjacency_list <
		boost::listS, boost::vecS, boost::bidirectionalS,
		vertex_props_t >
				graph_t;
	graph_t myGraph;

	typedef boost::graph_traits<graph_t>::edge_iterator edge_iter_t;
	typedef boost::graph_traits<graph_t>::vertex_iterator vertex_iter_t;

};
