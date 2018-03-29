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
//#define this-> 				this->
//#define return 			return

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

	void CFC( V< V< Tv > > * components )
	{
		V< Pi > endingTime ( this->VN );
		Graph trans( this->VN );

		this->DFS( &endingTime );
		sort( endingTime.begin(), endingTime.begin()+this->VN, CMP);

		this->TRSP( &trans );

		trans.DFS( components, endingTime );
	}

	void DFS( V< V< Tv > > * components, V< Pi > endingTime )
	{
		V< V< Tv > >::iterator index;

		Tc 	color [ this->VN ] = {0};
		Tv	v;
		int i;


		for ( i=0; i<this->VN; i++ )
		{
			color[i] = UV;
		}

		for( i=0; i<endingTime.size(); i++ )
		{
			if( color[ endingTime[i].second ] == UV )
			{
				V< Tv > aux;
				DFS( &aux, endingTime[i].second, color );
				(*components).PB( aux );
			}
		}
	}

	void vDfs( V<Tv>::iterator v, Tc * color, V< Pi > * endingTime, int * time )
	{
		//printf("in: %d\n", *v);
		*time = *time + 1;
		color [ *v ] = UF;

		V<Tv>::iterator it;

		for( it=this->adj[*v].begin(); it!=this->adj[*v].end(); it++ )
		{
			if( color[*it] == UV )
			{
				vDfs( it, color, endingTime, time );
			}
		}

		*time = *time + 1;
		(*endingTime)[ *v ].first = *time;
		(*endingTime)[ *v ].second = *v;
		color [ *v ] = FN;
	}

	void vDfs( int v, Tc * color, V< Pi > * endingTime, int * time )
	{
		*time = *time + 1;
		color [ v ] = UF;

		V<Tv>::iterator it;
		//printf("Vdfs 1. i: %d\n", v);

		for( it=this->adj[v].begin(); it!=this->adj[v].end(); it++ )
		{
			//printf("it: %d\n", *it);
			if( color[*it] == UV )
			{
				//printf("v: %d\n", v);
				//printf("*it: %d\n", *it);
				vDfs( it, color, endingTime, time );
			}
		}
		//printf("saiu. v: %d\n", v);

		*time = *time + 1;
		(*endingTime)[ v ].first = *time;
		(*endingTime)[ v ].second = v;
		color [ v ] = FN;
	}

	void DFS( V< Pi > * endingTime )
	{
		//printf("vertices number: %d\n", this->VN);
		Tc 	color [ this->VN ];
		//printf("Graph\n");
		Tv	v;
		int time = 0;

		int i;
		for ( i=0; i<this->VN; i++ )
		{
			color[i] = UV;
		}

		//printf("teste\n");
		for( i=0; i<(this->VN); i++ )
		{
			if( color[i] == UV )
			{
				//printf("%d\n", i);
				vDfs( i, color, endingTime, &time );
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

	void DFS( V< Tv > * components, 
		V<Tv>::iterator v, Tc *color )
	{
		(*components).PB( *v );

		color [ *v ] = UF;

		V< Tv >::iterator it;

		for( it=this->adj[*v].begin(); it!=this->adj[*v].end(); it++ )
		{
			if( color[ *it ] == UV )
			{
				DFS( components, it, color );
			}
		}

		color[ *v ] = FN;
	}

	void DFS( V< Tv > * components, 
		int v, Tc *color )
	{
		(*components).PB( v );

		color [ v ] = UF;

		V< Tv >::iterator it;

		for( it=this->adj[v].begin(); it!=this->adj[v].end(); it++ )
		{
			if( color[ *it ] == UV )
			{
				DFS( components, it, color );
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
		//printf("a: %d\n", a);
		if( a <= this->nbVar )
			return (this->nbVar) + a;
		else
			return (a-nbVar);
	}

	bool solve()
	{
		//this->print();
		//printf("end %d\n", this->nbVar);
		Graph G( (2*this->nbVar) );
		TCL c;
		int a, b;

		V< TCL >::iterator it;
		for( it=this->FM.begin(); it!=this->FM.end(); it++ )
		{
			if(it->vars.size()==2)
			{
				a = it->vars[0] < 0 ? this->nbVar+( it->vars[0] * -1 ) : it->vars[0];
				b = it->vars[1] < 0 ? this->nbVar+( it->vars[1] * -1 ) : it->vars[1];
				G.add( neg( a )-1, b-1 );
				G.add( neg( b )-1, a-1 );
/*				if(neg(a)-1 == -1 || b-1==-1 || neg(b)-1==-1 || a-1==-1 )
				{
					printf("%d, %d\n", a, it->vars[0]);
				}*/
			}
		}

		V< V<Tv> > components;
		G.CFC( &components );
		int cMap[this->nbVar*2];

		int i;
		V< V<Tv> >::iterator itVec;
		V< Tv >::iterator itIn;
		for( itVec=components.begin(), i=0; itVec!=components.end(); itVec++, i++ )
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
		}//for
	}//print()

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