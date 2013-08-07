#include "stdafx.h"

#include "cGraph.h"


cGraph theGraph;

cGraph::cGraph(  )
: myVertexBoxSize( 30 )
, myScreenOriginX( 250 )
, myScreenOriginY( 250 )
{}

	// Open the database file
bool cGraph::OpenDB( const std::wstring& n )
{
	theDB.Close();

	theDB.Open( n );
	if( theDB.myError )
		return false;
	theDB.Query(
		L"CREATE TABLE IF NOT EXISTS vertex "
		L"( vertex_id INTEGER PRIMARY KEY, "
		L"name, X, Y, pinned );");
	theDB.Query(
		L"CREATE TABLE IF NOT EXISTS edge "
		L"( edge_id INTEGER PRIMARY KEY, "
		L"a, b );");

	LoadFromDB();


	return true;
}

void cGraph::SaveToDB()
{
	theDB.Query(L"DELETE FROM vertex;");
	theDB.Query(L"DELETE FROM edge;");

	theDB.Query(L"BEGIN TRANSACTION;");
	vertex_iter_t vi, vi_end;
	for (tie(vi, vi_end) = vertices(myGraph); vi != vi_end; ++vi) {
		const cVertex& v = myGraph[*vi];
		theDB.Query(
			L"INSERT INTO vertex "
			L"( name, X, Y, pinned ) "
			L"VALUES ( '%s', %f, %f, %d );",
			v.myName.c_str(), v.myPoint[0], v.myPoint[1],
			(int) v.myFixedLocation );
	}	
	theDB.Query(L"END TRANSACTION;");
	theDB.Query(L"BEGIN TRANSACTION;");
	int a,b;
	edge_iter_t ei, ei_end;
	for( tie(ei, ei_end) = edges( myGraph ); ei != ei_end; ei++ ) {
		a=source(*ei,myGraph);
		b=target(*ei,myGraph);
		theDB.Query(
			L"INSERT INTO edge "
			L"( a, b ) "
			L"VALUES ( %d, %d );",
			a, b );

	}
	theDB.Query(L"END TRANSACTION;");


}

void cGraph::SaveSelectedVertexLocationToDB()
{
	if( ! IsSelectedVertex() )
		return;

	theDB.Query(
		L"UPDATE vertex SET X = %f, Y = %f WHERE vertex_ID = %d;",
		myGraph[ *mySelectedVertex ].getLocationX(),
		myGraph[ *mySelectedVertex ].getLocationY(),
		mySelectedVertex + 1 );


}

void cGraph::LoadFromDB()
{
	myGraph.clear();

	int row_count = theDB.Query(L"SELECT * FROM vertex;");

	vertex_iter_t vi;
	for( int k = 0; k < row_count; k++ ) {
		boost::add_vertex(  myGraph );
		vi = boost::vertices( myGraph ).second - 1;
		myGraph[*vi].myName = theDB.myResult[k*5+1];
		myGraph[*vi].myFixedLocation = _wtoi(theDB.myResult[k*5+4].c_str()) != 0;
		//if( myGraph[*vi].myFixedLocation ) {
			myGraph[*vi].myPoint[0] = _wtof(theDB.myResult[k*5+2].c_str());
			myGraph[*vi].myPoint[1] = _wtof(theDB.myResult[k*5+3].c_str());
		//}
	}

	row_count = theDB.Query(L"SELECT * FROM edge;");

	for( int k = 0; k < row_count; k++ ) {
		int a,b;
		a = _wtoi( theDB.myResult[k*3+1].c_str());
		b = _wtoi( theDB.myResult[k*3+2].c_str());
		boost::add_edge( a, b, myGraph );
	}
}

/**

  get edge

  @param[in] idx Index of edge in graph
  @param[out] a index of 1st vertex
  @param[out] b index of second edge

  @return true if edge found

*/
bool cGraph::getEdge( int& iva, int& ivb, int idx )
{
	if( 0 > idx || idx >= getEdgeCount() )
		return false;

	edge_iter_t ei = edges(myGraph).first;

	/* For some reason this does not work! */
	//ei += idx;

	// We have to do this instead  ( http://stackoverflow.com/q/17001541/16582 )
	for( int k = 0; k < idx; k++ ) {
		ei++;
	}

	iva = source( *ei, myGraph );
	ivb = target( *ei, myGraph );

	return true;


}

bool cGraph::IsEdge( int iva, int ivb )
{
	return boost::edge( iva, ivb, myGraph ).second;
}

/**

  Change the name of a vertex

  @param[in] i index number of vertex to be changed
  @param[in] n the new name

  @return 0 success
  @return 1 name already exists, no change made
  @return 2 index out of range, no change made

*/
int cGraph::setNameVertex( int i,  const std::wstring& n )
{
	if( 0 > i || i >= getVertexCount() )
		return 2;
	if( FindVertex( n ) )
		return 1;
	graph_t::vertex_descriptor v = *vertices(myGraph).first;
	myGraph[v+i].myName =  n;
	return 0;
}
/**

  Check if vertex name already exists in graph

  @param[in] n name to check

  @return true vertex with this name already exists
  @return false no vertex with this name

  */
bool cGraph::FindVertex( const std::wstring& n )
{
	vertex_iter_t vi, vi_end;
	for (tie(vi, vi_end) = vertices(myGraph); vi != vi_end; ++vi) {
		if( myGraph[*vi].myName == n )
			return true;
	}
	return false;

}	
void cGraph::setFreeLocation( int i )
{
	if( 0 > i || i >= getVertexCount() )
		return;
	graph_t::vertex_descriptor v = *vertices(myGraph).first;
	myGraph[v+i].myFixedLocation = false;
	SaveToDB();
}
void cGraph::setFixedLocation( int i,  double x, double y )
{
	if( 0 > i || i >= getVertexCount() )
		return ;
	graph_t::vertex_descriptor v = *vertices(myGraph).first;
	myGraph[v+i].myFixedLocation = true;
	myGraph[v+i].setFixedLocation( x, y );
	SaveToDB();
}

bool cGraph::IsPinned( int i )
{
	if( 0 > i || i >= getVertexCount() )
		return false ;
	return myGraph[ *vertices(myGraph).first + i ].myFixedLocation;
}
void cGraph::getVertexLocation( double& x, double& y, int i )
{
	if( 0 > i || i >= getVertexCount() )
		return;
	x = myGraph[ *vertices(myGraph).first + i ].getLocationX();
	y = myGraph[ *vertices(myGraph).first + i ].getLocationY();
}
cVertex& cGraph::getVertex( int i )
{
	if( 0 > i || i >= getVertexCount() ) {
		static cVertex vertex_null;
		return vertex_null;
	}
	return  myGraph[ *vertices(myGraph).first + i ];
}
cVertex& cGraph::getVertexSelected()
{
	vertex_iter_t vi, vi_end;
	tie(vi, vi_end) = vertices(myGraph);
	if( mySelectedVertex == vi_end ) { 
		static cVertex vertex_null;
		return vertex_null;
	}
	return  myGraph[ *mySelectedVertex ];
}


/**

  Mouse click

  @param[in] x location of mouse on screen
  @param[in] y location of mouse on screen

  If the mouse click is inside the box representing a vertex,
  the vertex becomes selected

  */

void cGraph::MouseClick( int x, int y )
{
	vertex_iter_t vi, vi_end;
	tie(vi, vi_end) = vertices(myGraph);
	mySelectedVertex = vi_end;
	for ( ; vi != vi_end; ++vi) {
		if( myGraph[*vi].IsHit( x, y ) ) {
			mySelectedVertex = vi;
			break;
		}
	}
}
/**

  Is there a selected vertex

  @return true if selected vertex exists

*/
bool cGraph::IsSelectedVertex()
{
	vertex_iter_t vi, vi_end;
	tie(vi, vi_end) = vertices(myGraph);
	return mySelectedVertex != vi_end;
}
/**

  Index to selected vertex

  @return -1 if no selected vertexs

*/
int cGraph::getVertexSelectedIndex()
{
	vertex_iter_t vi, vi_end;
	tie(vi, vi_end) = vertices(myGraph);
	if( mySelectedVertex == vi_end )
		return -1;
	return (int) ( mySelectedVertex - vi );

}

/**

  Move the selected vertex

  @param[in] mx new x location in screen co-ords
  @param[in] my new y location in screen co-ords

*/
void cGraph::setLocationSelectedVertex( int mx, int my )
{
	if( ! IsSelectedVertex() )
		return;
	myGraph[ *mySelectedVertex ].Move(mx,my);
}


const std::wstring& cGraph::getNameVertex( int i )
{
	if( 0 > i || i >= getVertexCount() ) {
		static std::wstring nullstr(L"");
		return nullstr;
	}
	graph_t::vertex_descriptor v = *vertices(myGraph).first;
	return myGraph[v+i].myName;

}


void cGraph::AddEdge( int row, int col, const std::wstring& name )
{
	boost::add_edge( row, col, myGraph );

	SaveToDB();
}

void cGraph::AddVertex()
{ 
	boost::add_vertex(  myGraph );

	SaveToDB();
}

	void cGraph::RemoveEdge( int a, int b )	
	{ 
		boost::remove_edge( a, b, myGraph );
	SaveToDB();
	}
	void cGraph::RemoveVertex( int i )		
	{ 
		boost::remove_vertex( i, myGraph );
	SaveToDB();
	}

	bool cGraph::IsPlanar()
	{
		return boost::boyer_myrvold_planarity_test( myGraph );
	}

/**

  Arrange the vertices in a circle

*/
void cGraph::ArrangeCircle()
{
	boost::pin_circle_graph_layout( myGraph,
		get(&cVertex::myPoint,myGraph),
		get(&cVertex::myFixedLocation,myGraph), 100.0);
}
/**

  Arrange the vertices according to their connections

*/
void cGraph::ArrangeKK()
{

	boost::pin_circle_graph_layout( myGraph,
		get(&cVertex::myPoint,myGraph),
		get(&cVertex::myFixedLocation,myGraph),100.0);

	boost::kamada_kawai_spring_layout(myGraph, 
		get(&cVertex::myPoint,myGraph),
		get(&cVertex::myFixedLocation,myGraph),
		get(&cEdge::myWeight, myGraph),
		boost::square_topology<>(),
		boost::edge_length(30.0 ) );

	SaveToDB();
}
/**

   assign colors to vertices

*/
void cGraph::MapColor()
{
	boost::sequential_vertex_coloring(
		myGraph,
		get(&cVertex::myColor,myGraph) );
}


void cGraph::WriteGraphML( const std::wstring& n)
{
	vertex_iter_t vi, vi_end;
	for (tie(vi, vi_end) = vertices(myGraph); vi != vi_end; ++vi) {
		myGraph[*vi].ConvertToUTF8();
	}
	boost::dynamic_properties dp;
	dp.property("label", boost::get(&cVertex::myName_utf8, myGraph));
	std::ofstream fout( n.c_str() );
	boost::write_graphml( fout, myGraph, dp, true );

}
/**

  Check for a yEd file

  @param[in] n  the filename
  @return true if the file weas written by yED

  The input file is copied to a new file graphex_processed.graphml
  If the intput file was NOT produced by yEd, then the copy is perfect
  If input was produced by yEd then the copy is filtered so that it can be
  read by boost::read_graphml
  Most of the yEd stuff is discarded, except for the node labels
  the text of which are copied to a simple node attribute "label"

*/

bool cGraph::IsGraphMLbyYED(const std::wstring& n)
{
	bool yEd = false;

	// open the input file
	std::ifstream fin;
	fin.open(n.c_str(), std::ifstream::in);
	if( ! fin.is_open() ) {
		return false;
	}
	// open the output file
	std::ofstream fout;
	fout.open("graphex_processed.graphml", std::ifstream::out );
	if( ! fout.is_open() ) {
		return false;
	}


	// loop over input file lines
	fin.clear();
	char buf[1000];
	while( fin.good() ) {
		fin.getline( buf,999 );
		std::string l( buf ); 

		// check for file produced by yEd
		if( l.find("<!--Created by yFiles") != -1 ) {
			yEd = true;
			// convert NodeLabel text to simple label attribute
			fout << "<key id=\"key0\" for=\"node\" attr.name=\"label\" attr.type=\"string\" />\n";
		}

		// check for file already identified as yEd
		if( yEd ) {

			// filter out yED attributes
			if( l.find("<key") != -1 ) {
				continue;
			}
			// convert NodeLabel text
			if( l.find("<y:NodeLabel") != -1 ) {
				int p = l.find(">")+1;
				int q = l.find("<",p);
				std::string label = l.substr(p,q-p);
				fout << "<data key=\"key0\">" << label << "</data>\n";
				continue;
			}

			// filter out outher yEd stuff
			if( l.find("<y:") != -1 ) {
				continue;
			}
			if( l.find("</y:") != -1 ) {
				continue;
			}
			if( l.find("<data") != -1 ) {
				continue;
			}
			if( l.find("</data") != -1 ) {
				continue;
			}
		}
		// copy input line to output
		fout << buf << std::endl;
	}

	// close files
	fin.close();
	fout.close();

	// return true if yED file
	return yEd;
	
}
void cGraph::ReadGraphML(const std::wstring& n)
{
	// check if file was produced by yEd
	if( IsGraphMLbyYED( n ) ) {

		int dbg = 1;
	}

	boost::dynamic_properties dp;
	dp.property("label", boost::get(&cVertex::myName_utf8, myGraph));


	//dp.property("color", boost::get(&cVertex::myColor, myGraph));

	//std::map< std::string, std::string > attribute_name2name;
	//boost::associative_property_map< std::map< std::string, std::string > > graphname_map( attribute_name2name );
	//dp.property("graphname", graphname_map );

	myGraph.clear();
	std::ifstream fin;
	fin.open("graphex_processed.graphml", std::ifstream::in);
	if( ! fin.is_open() ) {
		return;
	}
	boost::read_graphml( fin, myGraph, dp );

	//myGraph[boost::graph_bundle].myName = get(graphname_map,"graphname");

	// convert from UTF8 to UTF16
	vertex_iter_t vi, vi_end;
	for (tie(vi, vi_end) = vertices(myGraph); vi != vi_end; ++vi) {
		myGraph[*vi].ConvertFromUTF8();
	}

}


/**

  Is this vertex hit

  @param[in] mx  x location in screen co-ords
  @param[in] my  y location in screen co-ords

  @return true if location inside box representing vertex

*/
bool cVertex::IsHit( int mx, int my)
{
	int size = theGraph.getVertexBoxSize()/2;
	int xo, yo;
	theGraph.getScreenOrigin( xo, yo );
	int x = (int)myPoint[0] + xo;
	int y = (int)myPoint[1] + yo;
	return ( x-size <= mx &&
		mx <= x+ size &&
		y-size <= my &&
		my <= y+size );
}
/**

  Move the vertex

  @param[in] mx  x location in screen co-ords
  @param[in] my  y location in screen co-ords

*/
void cVertex::Move( int mx, int my )
{
	myPoint[0] = mx-250;
	myPoint[1] = my-250;
}
 
void cVertex::ConvertFromUTF8()
{
	raven::cUTF utf( myName_utf8 );
	myName = utf.get16();
}
void cVertex::ConvertToUTF8()
{
	raven::cUTF utf( myName );
	myName_utf8 = utf.get8();
}