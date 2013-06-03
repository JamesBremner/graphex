#include "stdafx.h"
#include "cGraph.h"

cGraph theGraph;

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
	graph_t::edge_descriptor e = *edges(myGraph).first;
	iva = source( e, myGraph );
	ivb = target( e, myGraph );

	return true;


}
/**

  Change the name of a vertex

  @param[in] i index number of vertex to be changed
  @param[in] n the new name

  @return 0 success
  @return 1 name already exists, no change made
  @return 2 index out of range, no change made

*/
int cGraph::setNameVertex( int i,  System::String^ n )
{
	if( 0 > i || i >= getVertexCount() )
		return 2;
	if( FindVertex(  msclr::interop::marshal_as<std::wstring>( n ) ) )
		return 1;
	graph_t::vertex_descriptor v = *vertices(myGraph).first;
	myGraph[v+i].myName =  msclr::interop::marshal_as<std::wstring>( n );
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
}

void cGraph::AddVertex()
{ 
	boost::add_vertex(  myGraph );
}
/**

  Arrange the vertices in a circle

*/
void cGraph::Arrange()
{
	boost::circle_graph_layout( myGraph,  get(&cVertex::myPoint,myGraph), 100.0);
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
/**

  Draw graph on screen

  @param[in] g The graphics context of the window where the drawing is reuired

*/
void cGraph::DrawLayout( System::Drawing::Graphics^ g )
{
	using namespace System::Drawing;

	/** Draw the edges

	This is done first so that the vertexes will overwrite the edges

	*/
	int a,b;
	graph_t::vertex_descriptor v0 = *vertices(myGraph).first;
	edge_iter_t ei, ei_end;
	for( tie(ei, ei_end) = edges( myGraph ); ei != ei_end; ei++ ) {
		a=source(*ei,myGraph);
		b=target(*ei,myGraph);
		g->DrawLine( gcnew Pen(Color::Black, 3),
				 myGraph[v0+a].getScreenX(), myGraph[v0+a].getScreenY(),
				 myGraph[v0+b].getScreenX(), myGraph[v0+b].getScreenY() );
	}

	// Draw the vertices
	vertex_iter_t vi, vi_end;
	for (tie(vi, vi_end) = vertices(myGraph); vi != vi_end; ++vi) {
		myGraph[*vi].Draw( g );
	}

	// Highlight selected vertex
	if( mySelectedVertex != vi_end ) {
		myGraph[ * mySelectedVertex ].DrawAsSelected( g );
	}

}
/**

  Draw vertex on screen

  @param[in] g The graphics context of the window where the drawing is reuired

*/
void cVertex::Draw( System::Drawing::Graphics^ g  )
{
	using namespace System::Drawing;

	// Represent vertex with a box of specified color
	const int box_size = theGraph.getVertexBoxSize();
	SolidBrush^ brush = gcnew SolidBrush(Color::Black);
	switch( myColor ) {
		case 0: brush->Color = Color::LightGreen; break;
		case 1: brush->Color = Color::Red; break;
		case 2: brush->Color = Color::Blue; break;
		case 3: brush->Color = Color::Yellow; break;
	}

	int x = getScreenX();
	int y = getScreenY();
	g->FillRectangle( brush,
		x-box_size/2,y-box_size/2,box_size,box_size);

	// label the vertex
	g->DrawString(gcnew System::String(myName.c_str()), 
		gcnew Font( "Arial",16 ),
		gcnew SolidBrush( Color::Black ),
		(float)x-box_size/2,(float)y-box_size/2);
}
/**

  Highlight vertex

*/
void cVertex::DrawAsSelected( System::Drawing::Graphics^ g )
{
	using namespace System::Drawing;
	const int box_size = theGraph.getVertexBoxSize();
	int x = getScreenX();
	int y = getScreenY();
	g->DrawRectangle( gcnew Pen( Color::Black,3.0f ),
		x-box_size/2,y-box_size/2,box_size,box_size);

}
/**

  Is this vertex hit

  @param[in] mx  x location in screen co-ords
  @param[in] my  y location in screen co-ords

  @return true if location inside box representing vertex

*/
bool cVertex::IsHit( int mx, int my)
{
	int x = getScreenX();
	int y = getScreenY();
	int size = theGraph.getVertexBoxSize()/2;
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
	myPoint[0] = mx-200;
	myPoint[1] = my-200;
}
