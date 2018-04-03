#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <utility>
#include <algorithm>
#include <cstdio>

#define V 				std::vector

typedef	int 			Tv;
typedef	int 			Tc;
#define UV 				0
#define	UF 				1
#define	FN 				2
typedef int 			Tlit;
typedef std::pair<int, int> 	Pi;
#define PB 				push_back

using namespace std;

bool CMP( Pi a, Pi b )
{
	return a.first > b.first;
}

class Graph{
private:
	V< Tv > * 		adj;
	int					VN;
public:
	Graph( int v )
	{
		this->VN	=	v;
		this->adj				=	new V< Tv > [v];
	}

	void add( Tv a, Tv b)
	{
		(this->adj)[a].PB ( b );
	}

	void rem(Tv a)
	{ 
		(this->adj)[a].clear();
	}

	void CFC( V< V< Tv > > * C )
	{
		V< Pi > ET ( this->VN );
		Graph T ( this->VN );

		this->DFS( &ET );
		sort( ET.begin(), ET.begin()+this->VN, CMP);

		this->TRSP( &T );

		T.DFS( C, ET );
	}

	void DFS( V< V< Tv > > * C, V< Pi > ET )
	{
		Tc 	color [ this->VN ];
		Tv	v;
		int i;

		for ( i=0; i<this->VN; i++ )
		{
			color[i] = UV;
		}

		for( i=0; i<ET.size(); i++ )
		{
			if( color[ ET[i].second ] == UV )
			{
				V< Tv > aux;
				DFS( &aux, ET[i].second, color );
				(*C).PB( aux );
			}
		}
	}

	void vDfs( V<Tv>::iterator v, Tc * color, V< Pi > * ET, int * time )
	{
		*time = *time + 1;
		color [ *v ] = UF;

		V<Tv>::iterator it;

		for( it=this->adj[*v].begin(); it!=this->adj[*v].end(); it++ )
		{
			if( color[*it] == UV )
			{
				vDfs( it, color, ET, time );
			}
		}

		*time = *time + 1;
		(*ET)[ *v ].first = *time;
		(*ET)[ *v ].second = *v;
		color [ *v ] = FN;
	}

	void vDfs( int v, Tc * color, V< Pi > * ET, int * time )
	{
		*time = *time + 1;
		color [ v ] = UF;

		V<Tv>::iterator it;

		for( it=this->adj[v].begin(); it!=this->adj[v].end(); it++ )
		{
			if( color[*it] == UV )
			{
				vDfs( it, color, ET, time );
			}
		}

		*time = *time + 1;
		(*ET)[ v ].first = *time;
		(*ET)[ v ].second = v;
		color [ v ] = FN;
	}

	void DFS( V< Pi > * ET )
	{
		Tc 	color [ this->VN ];
		Tv	v;
		int time = 0;

		int i;
		for ( i=0; i<this->VN; i++ )
		{
			color[i] = UV;
		}

		for( i=0; i<(this->VN); i++ )
		{
			if( color[i] == UV )
			{
				vDfs( i, color, ET, &time );
			}
		}
	}

	void TRSP( Graph * G )
	{
		int i;

		for( i=0; i<this->VN; i++ )
		{
			V< Tv >::iterator it;
			for( it=(this->adj)[i].begin(); it!=(this->adj)[i].end(); it++)
			{
				G->add( *it, i );
			}
		}
	}

	void DFS( V< Tv > * C, 
		V<Tv>::iterator v, Tc *color )
	{
		(*C).PB( *v );

		color [ *v ] = UF;

		V< Tv >::iterator it;

		for( it=this->adj[*v].begin(); it!=this->adj[*v].end(); it++ )
		{
			if( color[ *it ] == UV )
			{
				DFS( C, it, color );
			}
		}

		color[ *v ] = FN;
	}

	void DFS( V< Tv > * C, 
		int v, Tc *color )
	{
		(*C).PB( v );

		color [ v ] = UF;

		V< Tv >::iterator it;

		for( it=this->adj[v].begin(); it!=this->adj[v].end(); it++ )
		{
			if( color[ *it ] == UV )
			{
				DFS( C, it, color );
			}
		}

		color[ v ] = FN;
	}
};

typedef struct TCL{
	V< Tlit > vars;
}TCL;

class S{
private:
	V< TCL > FM;
	int nbVar;
	int nbCl;
public:
	S ( int v )
	{
		this->nbVar		=	v;
	}

	S (){};

	void add( TCL * c )
	{
		(this->FM).PB( *c );
		(this->nbCl)++;
	}

	Tlit neg( int a )
	{
		if( a <= this->nbVar )
			return (this->nbVar) + a;
		else
			return (a-nbVar);
	}

	bool solve()
	{
		Graph G( (2*this->nbVar) );
		TCL c;
		int a, b;

		V< TCL >::iterator it;
		for( it=this->FM.begin(); it!=this->FM.end(); it++ )
		{
			if(it->vars[1] == 0)
			{
				a = it->vars[0] < 0 ? this->nbVar+( it->vars[0] * -1 ) : it->vars[0];
				G.rem(neg( a )-1);
			}else
			{
				a = it->vars[0] < 0 ? this->nbVar+( it->vars[0] * -1 ) : it->vars[0];
				b = it->vars[1] < 0 ? this->nbVar+( it->vars[1] * -1 ) : it->vars[1];
				G.add( neg( a )-1, b-1 );
				G.add( neg( b )-1, a-1 );
			}
		}

		V< V<Tv> > C;
		G.CFC( &C );
		int cMap[this->nbVar*2];

		int i;
		V< V<Tv> >::iterator itVec;
		V< Tv >::iterator itIn;
		for( itVec=C.begin(), i=0; itVec!=C.end(); itVec++, i++ )
		{
			for( itIn=itVec->begin(); itIn!=itVec->end(); itIn++ )
			{
				cMap[ *itIn ] = i;
			}
		}

		bool flag = true;
		for( i=0; i<this->nbVar*2; i++ )
		{
			if( cMap[i] == cMap[ neg(i) ] ) 
			{
				flag = false;
				break;
			}
		}

		return flag;
	}

		void print()
	{
		std::vector< TCL >::iterator it;
		for( it=this->FM.begin(); it!=this->FM.end(); it++ )
		{
			printf( "%d %d\n", it->vars[0], it->vars[1] );
		}
	}

	void read()
	{
		int v, cl, a, b;
		TCL c;

		scanf( "%d", &v );
		this->nbVar = v;
		scanf( "%d", &cl );

		for( int i=0; i<cl; i++ )
		{
			scanf( "%d %d", &a, &b );
			if( a<0 ) a = neg( a*(-1) );
			if( b<0 ) b = neg( b*(-1) );
			c.vars.PB(a);
			c.vars.PB(b);
			this->add(&c);
			c.vars.clear();
		}
	}
};

#endif