#include <bits/stdc++.h>
#include <ctime>
#include <iostream>
using namespace std;

/*Dimiourgia enos struct me ta simia x,y sto epipedo*/
struct Point
{
	int x, y;
};
/*Dimiourgia enos struct me ta simia x,y sto epipedo*/

/*Determinant*/
int determinant(Point a, Point b, Point c)
{
	int val = (b.y - a.y) * (c.x - b.x) - (b.x - a.x) * (c.y - b.y); //Ipologismos orizousas

	if (val == 0)
	{
		return 0;
	}
	else if (val > 0)
	{
		return 1;
	}
	else
	{
		return 2;
	}
}
/*	Dimiourgia sinartisis me skopo ton upologismo tis orizousas trion simion kathe fora,
	i metavliti val krataei to apotelesma tis orizousas kai h parakaot domi "if" domi epistrefei mia
	timi analoga me timi tis orizousas. i timi 0 simainei oti ta simia einai sinefthiaka, i timi 1 
	simainei oti ta simia sximatizoun deksia gonia kai i timi 2 simainei oti ta simia sximatizoun aristeri gonia.
	i sinartisi pairnei 3 orismata tipou Point
*/
/*Determinant*/

/* CONVEX HULL*/
void convexhull(Point points[], int n)
{

	vector<Point> hull; // Dimiourgia enos vector tipou Point me onoma hull
	int a = 0, c;

	/*Prosthiki simion sto HULL*/
	do
	{
		hull.push_back(points[a]); /*Eisagogi ton simion sto hull*/
		c = (a + 1) % n;		   /*To q kanei loop mexri ton airthmo ton simion pou exoume dosei*/
		for (int i = 0; i < n; i++)
		{
			if (determinant(points[a], points[i], points[c]) == 2)
			{
				c = i;
				/*An i orizousa einai 2 tote ta simio I den aniki sto periblima kai to simio c pairnei thn thesi tou*/
			}
		}
		a = c;
	} while (a != 0); /*0 orizetai os to start-exit point tis domis. I domi ksikinaei apo to to p=0 os to proto simio me basi tin taksinomisi
						 kai teleionei pali me p=0 pou simainei oti exei ftasei sto proto simio */
	/*Prosthiki simion sto HULL*/

	/*Emfanisi ton simion stin othoni*/
	cout << "Convex Hull Points:" << endl;
	for (int i = 0; i < hull.size(); i++)
	{
		cout << "(" << hull[i].x << "," << hull[i].y << ")\n";
	}
	/*Emfanisi ton simion stin othoni*/
}
/*CONVEX HULL*/

/*SELECTION SORT*/
void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void selectionSort(struct Point arr[], int n)
{
	int i, j, min_idx;

	for (i = 0; i < n - 1; i++)
	{
		min_idx = i;
		for (j = i + 1; j < n; j++)
		{
			if (arr[j].x < arr[min_idx].x)
			{
				min_idx = j;
			}
		}
		swap(&arr[min_idx].x, &arr[i].x);
		swap(&arr[min_idx].y, &arr[i].y);
	}

	int z, count = 0;
	bool flag = false; //false
	int position = 0;
	for (z = 0; z <= n - 1; z++)
	{
		if (z != n - 1)
		{
			if (arr[z].x == arr[z + 1].x)
			{
				count++;
				flag = true; //true
			}
			else
			{
				if (flag == true)
				{ //true

					for (i = position; i < position + count + 1; i++)
					{
						min_idx = i;
						for (j = i + 1; j < z + count; j++)
						{
							if (arr[j].y < arr[min_idx].y)
							{
								min_idx = j;
							}
						}
						swap(&arr[min_idx].y, &arr[i].y);
					}
				}
				flag = false;
				position = z + 1;
				count = 0;
			}
		}
		else
		{

			for (i = position; i < position + count; i++)
			{
				min_idx = i;
				for (j = i + 1; j < position + count; j++)
				{
					if (arr[j].y < arr[min_idx].y)
					{
						min_idx = j;
					}
				}
				swap(&arr[min_idx].y, &arr[i].y);
			}
		}
	}
}
/*SELECTION SORT*/

int main()
{
	/*Dilosi metabliton*/
	int n = 100;				/*Arithmos simion*/
	struct Point points[n];		/*Pinakas struct tipou points*/
	struct timespec start, end; /*Struct gia tin litourgia tou rologiou*/
	srand(time(0));
	/*Dilosi metabliton*/

	/*Eisagogi tixaion simion ston pinaka*/
	for (int i = 0; i < n; i++)
	{
		points[i].x = rand() % 1001;
		points[i].y = rand() % 1001;
	}
	/*Eisagogi tixaion simion ston pinaka*/
	selectionSort(points, n);				/*Kalesma tis sinartisis quickSoer gia taksinomisi ton simion*/
	clock_gettime(CLOCK_MONOTONIC, &start); /*Enarksi rologiou*/
	ios_base::sync_with_stdio(false);

	convexhull(points, n);				  /*Kalesma tis sinartisis convexhull*/
	clock_gettime(CLOCK_MONOTONIC, &end); /*Stamatimos rologiou*/

	/*Ipologismos xronou pou xriastike to programma*/
	double time_taken;
	time_taken = (end.tv_sec - start.tv_sec) * 1e9;
	time_taken = (time_taken + (end.tv_nsec - start.tv_nsec)) * 1e-9;
	cout << "Time taken by program is : " << fixed << time_taken << setprecision(9) << " sec";
	/*Ipologismos xronou pou xriastike to programma*/
	return 0;
}
