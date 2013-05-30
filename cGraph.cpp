#include "stdafx.h"
#include "cGraph.h"

bool cGraph::firstEdge( int& a, int& b )
{
	tie(ei, ei_end) = edges( bgl );
	if( ei == ei_end )
		return false;
    a=source(*ei,bgl);
    b=target(*ei,bgl);
	return true;
}
bool cGraph::nextEdge( int& a, int& b )
{
	ei++;
	if( ei == ei_end )
		return false;
    a=source(*ei,bgl);
    b=target(*ei,bgl);
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

		boost::add_edge( row, col, bgl );

}