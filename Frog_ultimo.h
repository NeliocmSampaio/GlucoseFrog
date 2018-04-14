#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>

#define V 				std::vector

typedef	int 			Tv;
typedef	int 			Tc;
typedef void			VD;
#define UV 				0
#define	UF 				1
#define	FN 				2
#define IT 				::iterator
typedef int 			Tlit;
typedef std::pair<int, int> 	Pi;
#define PB 				push_back

using namespace std;

bool CMP( Pi a, Pi b )
{
	return a.first > b.first;
}

class Graph{
public:
	V< Tv > * 		adj;
	int					VN;

	Graph( int v )
	{
		VN	=	v;
		adj				=	new V< Tv > [v];
	}

	VD CFC( V< V< Tv > > * C )
	{
		V< Pi > ET ( VN );
		Graph T ( VN );

		DFS( &ET );
		sort( ET.begin(), ET.begin()+VN, CMP);

		TRSP( &T );

		T.DFS( C, ET );
	}

	VD DFS( V< Tv > * C, int v, Tc *CL)
	{
		(*C).PB( v );

		CL [ v ] = UF;

		V< Tv >IT it;

		for( it=adj[v].begin(); it!=adj[v].end(); it++ )
			if( CL[ *it ] == UV )
				DFS( C, *it, CL );

		CL[ v ] = FN;
	}

	VD DFS( V< V< Tv > > * C, V< Pi > ET )
	{
		Tc 	CL [ VN ];
		Tv	v;
		int i;

		for ( i=0; i<VN; i++ )
			CL[i] = UV;

		for( i=0; i<ET.size(); i++ )
		{
			if( CL[ ET[i].second ] == UV )
			{
				V< Tv > a;
				DFS( &a, ET[i].second, CL );
				(*C).PB( a );
			}
		}
	}
/*
	VD vDfs( V<Tv>IT v, Tc * CL, V< Pi > * ET, int * t )
	{
		*t = *t + 1;
		CL [ *v ] = UF;

		V<Tv>IT it;

		for( it=adj[*v].begin(); it!=adj[*v].end(); it++ )
			if( CL[*it] == UV )
				vDfs( it, CL, ET, t );

		*t += 1;
		(*ET)[ *v ].first = *t;
		(*ET)[ *v ].second = *v;
		CL [ *v ] = FN;
	}*/

	VD vDfs( int v, Tc * CL, V< Pi > * ET, int * t, int a )
	{
		*t = *t + 1;
		CL [ v ] = UF;

		V<Tv>IT it;

		for( it=adj[v].begin(); it!=adj[v].end(); it++ )
			if( CL[*it] == UV )
				vDfs( *it, CL, ET, t, 0 );

		*t = a==1 ? 1 : *t + 1;
		(*ET)[ v ].first = *t;
		(*ET)[ v ].second = v;
		CL [ v ] = FN;
	}

	VD DFS( V< Pi > * ET )
	{
		Tc 	CL [ VN ];
		Tv	v;
		int t = 0, i;

		for ( i=0; i<VN; i++ )
			CL[i] = UV;

		for( i=0; i<(VN); i++ )
			if( CL[i] == UV )
				vDfs( i, CL, ET, &t, 1 );
	}

	VD TRSP( Graph * g )
	{
		for( int i=0; i<VN; i++ )
		{
			V< Tv >IT it;
			for( it=(adj)[i].begin(); it!=(adj)[i].end(); it++)
				g->adj[*it].PB(i);
		}
	}

	/*VD DFS( V< Tv > * C, V<Tv>IT v, Tc *CL )
	{
		(*C).PB( *v );

		CL [ *v ] = UF;

		V< Tv >IT it;

		for( it=adj[*v].begin(); it!=adj[*v].end(); it++ )
			if( CL[ *it ] == UV )
				DFS( C, it, CL );

		CL[ *v ] = FN;
	}*/
};

typedef struct TCL{
	V< Tlit > vars;
}TCL;

class S{
public:
	V< TCL > FM;
	int nbVar;
	int nbCl;

	S ( int v )
	{
		nbVar		=	v;
	}

	VD add( TCL * c )
	{
		FM.PB( *c );
		nbCl++;
	}

	Tlit neg( int a )
	{
		return a<=nbVar ? nbVar + a : a-nbVar;
	}

	bool solve()
	{

		Graph G( 2*nbVar );
		TCL c;
		int a, b, i, cMap[nbVar*2];

		V< TCL >IT it;
		for( it=FM.begin(); it!=FM.end(); it++ )
			if(it->vars[1] == 0)
			{
				a = it->vars[0] < 0 ? nbVar+( it->vars[0] * -1 ) : it->vars[0];
				G.adj[neg(a)-1].clear();
			}else
			{
				a = it->vars[0] < 0 ? nbVar+( it->vars[0] * -1 ) : it->vars[0];
				b = it->vars[1] < 0 ? nbVar+( it->vars[1] * -1 ) : it->vars[1];
				G.adj[neg( a )-1].PB(b-1);
				G.adj[neg( b )-1].PB(a-1);
			}

		V< V<Tv> > C;
		G.CFC( &C );

		V< V<Tv> >IT itVec;
		V< Tv >IT itIn;
		for( itVec=C.begin(), i=0; itVec!=C.end(); itVec++, i++ )
			for( itIn=itVec->begin(); itIn!=itVec->end(); itIn++ )
				cMap[ *itIn ] = i;

		bool f = true;
		for( i=0; i<nbVar*2; i++ )
			if( cMap[i] == cMap[ neg(i) ] ) 
			{
				f = false;
				break;
			}

		return f;
	}
};

#endif