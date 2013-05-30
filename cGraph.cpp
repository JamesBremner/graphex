#include "stdafx.h"
#include "cGraph.h"

bool cGraph::firstEdge( int& a, int& b )
{
	tie(ei, ei_end) = edges( myGraph );
	if( ei == ei_end )
		return false;
    a=source(*ei,myGraph);
    b=target(*ei,myGraph);
	return true;
}
bool cGraph::nextEdge( int& a, int& b )
{
	ei++;
	if( ei == ei_end )
		return false;
    a=source(*ei,myGraph);
    b=target(*ei,myGraph);
	return true;

}
cGraph::vertex_iter_t cGraph::getVertex( int i )
{
	if( 0 > i || i >= (int)myVertex.size() ) {
		return myVertex.end();
	}
	return myVertex.begin() + i;
}
void cGraph::AddEdge( int row, int col, const std::wstring& name )
{
	boost::add_edge( row, col, myGraph );
}

void cGraph::AddVertex()
{ 
	myVertex.push_back( cVertex() );
	static int vertex_index = 1;
	boost::add_vertex( vertex_index++, myGraph );
}
void cGraph::Arrange()
{

	boost::property_map<graph_t, vertex_position_t>::type
		position = get(vertex_position, myGraph);

	boost::circle_graph_layout( myGraph,  position, 100.0);

	vertex_iter_t p = beginVertex();
	vertex_iter_bgl vi, vi_end;
	for (tie(vi, vi_end) = vertices(myGraph); vi != vi_end; ++vi) {
		int x = (int)position[*vi][0];
		int y = (int)position[*vi][1];
		p->setXY(x+200,y+200);
		p++;
	}

}
void cGraph::DrawLayout( System::Drawing::Graphics^ g )
{
	using namespace System::Drawing;
	int a,b;
	edge_iter ei, ei_end;
	for( tie(ei, ei_end) = edges( myGraph ); ei != ei_end; ei++ ) {
		a=source(*ei,myGraph);
		b=target(*ei,myGraph);
		g->DrawLine( gcnew Pen(Color::Black, 3),
				 myVertex[a].x, myVertex[a].y,
				 myVertex[b].x, myVertex[b].y );
	}

	for( vertex_iter_t p = myVertex.begin();
		p != myVertex.end(); p++ )
	{
		p->Draw( g );
	}

}
void cVertex::Draw( System::Drawing::Graphics^ g )
{
	using namespace System::Drawing;

	// Represent vertex with a box
	const int box_size = 30;
	g->FillRectangle(gcnew SolidBrush( Color::LightGreen ),
		x-box_size/2,y-box_size/2,box_size,box_size);
	// label the vertex
	g->DrawString(gcnew System::String(myName.c_str()), 
		gcnew Font( "Arial",16 ),
		gcnew SolidBrush( Color::Black ),
		(float)x-box_size/2,(float)y-box_size/2);
}
