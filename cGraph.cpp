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
	//int k = 0;
	//for( vertex_iter_t p = beginVertex();
	//	p != endVertex(); p++ )
	//{
	//	int x = ( k % 3 ) * 50;
	//	int y = ( k / 3 ) * 100;
	//	p->setXY(x,y);
	//	k++;
	//}

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
