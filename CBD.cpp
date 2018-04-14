#include <stdio.h>

using namespace std;

int main()
{
	int m [1010][1010];
	int p, n, c;
	int cont, aux;
	int r=0;

	scanf("%d %d %d", &p, &n, &c);

	while(p!=0)
	{
		for(int i=0; i<p; i++)
		{
			for(int j=0; j<n; j++)
			{
				scanf("%d", m[i][j]);
			}
		}

		r=0;
		for(int i=0; i<p; i++)
		{
			for(int j=0; j<n; j++)
			{
				if( ( i==0 || m[i-1][j]==0 ) && m[i][j]==1 )
				{
					aux=i;
					cont=1;
					while(m[aux][j]==1)
					{
						cont++;
						if(aux<p-1)
							aux++;
					}//while

					if(cont >= c)
						r++;
				} 
			}
		}

		printf("%d\n", r);

		scanf("%d %d %d", &p, &n, &c);
	}

	return 0;
}