


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
	//void Draw( System::Drawing::Graphics^ g );
	//void DrawAsSelected( System::Drawing::Graphics^ g );
	int getScreenX()			{  return (int)myPoint[0]+250; }
	int getScreenY()			{  return (int)myPoint[1]+250; }
	bool IsHit( int mx, int my );
	void Move( int mx, int my );
	void ConvertFromUTF8();
	void ConvertToUTF8();


	std::wstring myName;
	std::string myName_utf8;
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
	double myWeight;
};

class cGraphProps {
public:
	std::string myName;
	int myInt;
};


class cGraph
{
public:
	cGraph();
	//void setOptions( graphex::cOptions^ O )		{ theOptions = O; }
	void Clear()								{ myGraph.clear(); }
	bool OpenDB( const std::wstring& n );
	void SaveToDB();
	void LoadFromDB();
	void SaveSelectedVertexLocationToDB();
	void AddVertex();
	void AddEdge( int row, int col, const std::wstring& name );
	void RemoveEdge( int a, int b );
	void RemoveVertex( int i );

	void ArrangeCircle();
	void ArrangeKK();
	void MapColor();
	bool IsPlanar();

	int setNameVertex( int i,  const std::wstring& n );
	const std::wstring& getNameVertex( int i );
	int getVertexCount()			{ return boost::num_vertices( myGraph); }
	bool FindVertex( const std::wstring& n );
	void setFreeLocation( int i );
	void setFixedLocation( int i,  double x, double y );
	bool IsPinned( int i );
	void getVertexLocation( double& x, double& y, int i );
	cVertex& getVertex( int i );
	cVertex& getVertexSelected();

	int getEdgeCount()				{ return boost::num_edges( myGraph); }
	bool getEdge( int& iva, int& iv, int ei );
	bool IsEdge( int iva, int ivb );

	int getVertexBoxSize()			{ return myVertexBoxSize; }
	void getScreenOrigin( int&x, int& y )	{ x = myScreenOriginX; y = myScreenOriginY; }


	void MouseClick( int x, int y );
	bool IsSelectedVertex();
	int  getVertexSelectedIndex();
	void setLocationSelectedVertex( int mx, int my );

	void ReadGraphML(const std::wstring& n);
	void WriteGraphML( const std::wstring& n);

private:

	// The BGL graph
 	typedef boost::adjacency_list <
		boost::vecS, boost::vecS, boost::undirectedS,
		cVertex, cEdge, cGraphProps  >
				graph_t;
	graph_t myGraph;

	typedef boost::graph_traits<graph_t>::edge_iterator edge_iter_t;
	typedef boost::graph_traits<graph_t>::vertex_iterator vertex_iter_t;

	int myVertexBoxSize;
	int myScreenOriginX;
	int myScreenOriginY;	
	
	vertex_iter_t mySelectedVertex;

	// The database
	raven::sqlite::cDB theDB;

	// The Options
	//gcroot< graphex::cOptions^ > theOptions;

};

extern 	cGraph theGraph;