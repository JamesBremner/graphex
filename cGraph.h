#include "raven_sqlite.h"
#include "cOptions.h"

class cVertex
{
public:
	cVertex()
		: myFixedLocation( false )
	{}
	void setName( const std::wstring& n ) {	myName = n; }
	void setFixedLocation( double X, double Y )	{ myPoint[0] = X, myPoint[1] = Y; }
	double getLocationX() { return myPoint[0]; }
	double getLocationY() { return myPoint[1]; }
	void Draw( System::Drawing::Graphics^ g );
	void DrawAsSelected( System::Drawing::Graphics^ g );
	int getScreenX()			{  return (int)myPoint[0]+250; }
	int getScreenY()			{  return (int)myPoint[1]+250; }
	bool IsHit( int mx, int my );
	void Move( int mx, int my );


	std::wstring myName;
	int myColor;
	boost::square_topology<>::point_type myPoint;
	bool myFixedLocation;
};

class cEdge
{
public:

	cEdge() 
		:  myWeight(1.0)
	{}
	cEdge( int A, int B )
		: a( A ), b( B )
		, myWeight(1.0)

	{}
	bool operator ==( const cEdge& other ) const
	{ return a == other.a && b == other.b; }

	int a;
	int b;
	double myWeight;
};


class cGraph
{
public:
	cGraph();
	bool OpenDB( graphex::cOptions^ theOptions );
	void SaveToDB();
	void LoadFromDB();
	void AddVertex();
	void AddEdge( int row, int col, const std::wstring& name );
	void RemoveEdge( int a, int b )		{ boost::remove_edge( a, b, myGraph ); }
	void RemoveVertex( int i )			{ boost::remove_vertex( i, myGraph ); }

	void ArrangeCircle();
	void ArrangeKK();
	void MapColor();

	int setNameVertex( int i,  System::String^ n );
	const std::wstring& getNameVertex( int i );
	int getVertexCount()			{ return boost::num_vertices( myGraph); }
	bool FindVertex( const std::wstring& n );
	void setFreeLocation( int i );
	void setFixedLocation( int i,  double x, double y );
	bool IsPinned( int i );
	void getVertexLocation( double& x, double& y, int i );

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
		boost::vecS, boost::vecS, boost::undirectedS,
		cVertex, cEdge  >
				graph_t;
	graph_t myGraph;

	typedef boost::graph_traits<graph_t>::edge_iterator edge_iter_t;
	typedef boost::graph_traits<graph_t>::vertex_iterator vertex_iter_t;

	int myVertexBoxSize;
	vertex_iter_t mySelectedVertex;

	// The database
	raven::sqlite::cDB theDB;

};

extern 	cGraph theGraph;