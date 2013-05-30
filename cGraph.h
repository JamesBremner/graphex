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
/*struct point 
{ 
   double x; 
   double y; 
};*/ 

class cGraph
{
public:
	typedef std::vector< cVertex >::iterator vertex_iter_t;
	void AddVertex();
	void AddEdge( int row, int col, const std::wstring& name );
	void RemoveEdge( int a, int b )		{ boost::remove_edge( a, b, myGraph ); }
	void Arrange();
	void NameVertex( int i,  System::String^ n )
	{
		if( 0 > i || i >= (int)myVertex.size() )
			return;
		myVertex[ i ].setName(  msclr::interop::marshal_as<std::wstring>( n ) );
	}
	int getVertexCount()			{ return myVertex.size(); }
	vertex_iter_t beginVertex()		{ return myVertex.begin(); }
	vertex_iter_t endVertex()		{ return myVertex.end(); }
	vertex_iter_t  getVertex( int i );
	bool firstEdge( int& a, int& b );
	bool nextEdge( int& a, int& b );
	void DrawLayout( System::Drawing::Graphics^ g );

private:
	typedef boost::square_topology<>::point_type point;
 	typedef boost::adjacency_list <
		boost::listS, boost::vecS, boost::bidirectionalS,
		// Vertex properties
		boost::property<
			boost::vertex_index_t, int,
			boost::property<vertex_position_t, point> >
	> graph_t;
	graph_t myGraph;

	std::vector< cVertex > myVertex;

	typedef boost::graph_traits<graph_t>::edge_iterator edge_iter;
	edge_iter ei, ei_end;
	typedef boost::graph_traits<graph_t>::vertex_iterator vertex_iter_bgl;

};
