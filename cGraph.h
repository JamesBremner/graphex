class cVertex
{
public:
	void setName( const std::wstring& n )
	{
		myName = n;
	}
	void setXY( int X, int Y )	{ x = X, y = Y; }
	void Draw( System::Drawing::Graphics^ g );
	void DrawAsSelected( System::Drawing::Graphics^ g );
	int getScreenX()			{  return (int)myPoint[0]+200; }
	int getScreenY()			{  return (int)myPoint[1]+200; }
	bool IsHit( int mx, int my );
	void Move( int mx, int my );


	std::wstring myName;
	int x;
	int y;
	int myColor;
	boost::square_topology<>::point_type myPoint;
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


class cGraph
{
public:
	cGraph()
		: myVertexBoxSize( 30 )
	{}
	void AddVertex();
	void AddEdge( int row, int col, const std::wstring& name );
	void RemoveEdge( int a, int b )		{ boost::remove_edge( a, b, myGraph ); }
	void RemoveVertex( int i )			{ boost::remove_vertex( i, myGraph ); }

	void Arrange();
	void MapColor();

	int setNameVertex( int i,  System::String^ n );
	const std::wstring& getNameVertex( int i );
	int getVertexCount()			{ return boost::num_vertices( myGraph); }
	bool FindVertex( const std::wstring& n );

	int getEdgeCount()				{ return boost::num_edges( myGraph); }
	bool getEdge( int& iva, int& iv, int ei );
	int getVertexBoxSize()			{ return myVertexBoxSize; }

	void DrawLayout( System::Drawing::Graphics^ g );

	void MouseClick( int x, int y );
	bool IsSelectedVertex();
	void setLocationSelectedVertex( int mx, int my );

private:

	// The BGL graph
 	typedef boost::adjacency_list <
		boost::listS, boost::vecS, boost::bidirectionalS,
		cVertex  >
				graph_t;
	graph_t myGraph;

	typedef boost::graph_traits<graph_t>::edge_iterator edge_iter_t;
	typedef boost::graph_traits<graph_t>::vertex_iterator vertex_iter_t;

	int myVertexBoxSize;
	vertex_iter_t mySelectedVertex;

};

extern 	cGraph theGraph;