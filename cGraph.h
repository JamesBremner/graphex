class cVertex
{
public:
	void setName( const std::wstring& n )
	{
		myName = n;
	}
	void setXY( int X, int Y )	{ x = X, y = Y; }


	std::wstring myName;
	int x;
	int y;
};

class cEdge
{
	int a;
	int b;
	public:
	cEdge( int A, int B )
		: a( A ), b( B )
	{}
	bool operator ==( const cEdge& other ) const
	{ return a == other.a && b == other.b; }
};

class cGraph
{
public:
	typedef std::vector< cVertex >::iterator vertex_iter_t;
	typedef std::vector< cEdge >::iterator edge_iter_t;
	void AddVertex()
	{
		myVertex.push_back( cVertex() );
	}
	void AddEdge( int row, int col, const std::wstring& name );
	void RemoveEdge( int a, int b )		{ boost::remove_edge( a, b, bgl ); }
	void Arrange()
	{
		int k = 0;
			for( vertex_iter_t p = beginVertex();
				p != endVertex(); p++ )
			{
				int x = ( k % 3 ) * 50;
				int y = ( k / 3 ) * 100;
				p->setXY(x,y);
				k++;
			}

	}
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

private:
	typedef boost::adjacency_list<> graph_t;

	std::vector< cVertex > myVertex;
	graph_t bgl;

	typedef boost::graph_traits<graph_t>::edge_iterator edge_iter;
	edge_iter ei, ei_end;

};
