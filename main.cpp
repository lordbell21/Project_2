#include <iomanip>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stack>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <fstream>
#include <new>
#include <climits>
#include <list>
 
using namespace std;
 
struct EDGE{
    int end;
    int edge;
    bool touched;
};
 
int main(int argc, char * argv[]){
    // OPEN AND READ FROM INPUT.TXT FILE
    ifstream inFile;
    inFile.open("input.txt", inFile.in);
    // OPEN AND WRITE TO OUTPUT.TXT FILE
    ofstream outFile;
    outFile.open("bell.txt", outFile.out);
    int instances = 0, loop = 0;
    int vertices = 0, edges = 0;
    int V_I = 0, V_II = 0;
 
    // READS NUMBER OF ITERATIONS/DATA SETS
    inFile >> instances;
    //MAIN LOOP TO READ INPUT.TXT
    while (loop < instances)
    {
        // READS NUMBER OF VERTICES AND NUMBER OF EDGES
        inFile >> vertices >> edges;
 
        stack <int> PATH;
        //Array of Linked lists
        list<EDGE> *V_array = new list<EDGE>[ vertices + 1 ];
        EDGE tmp;
 
        int First_Vertex = 0;
        int Last_Vertex = 0;
        //This for loop is to determine what vertex's don't have anything entering.
        for (int i = 1; i <= edges; i++)
        {
            inFile >> V_I >> V_II;
             
            if (i == 1)
            {
                First_Vertex = V_I; 
                tmp.touched = true;
            }
            else
            {
                Last_Vertex = V_II;
                tmp.touched = false;
            }
			// STORES EDGE
            tmp.edge = i;
			// STORES SECOND VERTEX
			tmp.end = V_II;
			// BUILDS ARRAY->LINK_LIST
            V_array[V_I].push_back(tmp);
        }
        list<EDGE>::iterator iter;
        for (int i = 1; i <= vertices; i++)
        {
            iter = V_array[i].begin();
            cout << "[" << i << "] ";
            while ( iter != V_array[i].end() )
            {
				cout << iter->end << "-->";
                iter++;
            }
            cout << endl;
        }
		// FROM HERE ON DOWN INPLEMENT TRAVERSAL
		for( int i = 1; i <= vertices; i++ )
		{
			iter = V_array[i].begin();
			while( iter != V_array[i].end() )
			{
				if( V_array[i].front().touched == true )
				{
					iter->touched = true;
					if( i < vertices && (*iter).end < vertices )
					{  V_array[ (*iter).end ].front().touched = true;  }
				}
				iter++;
			}
		}
		cout << "There " << endl;
		cout << "V " << vertices << endl;
		// FROM HERE ON DOWN BACKTRACK
		//iter = V_array[ vertices ].begin();
		int tmp_holder = Last_Vertex;

		cout << "Here " << endl;
		for( int i = vertices - 1; i > 0; i-- )
		{
			
			iter = V_array[i].begin();

			while( iter != V_array[i].end() && iter->touched == true )
			{
				cout << "tmp_ " << tmp_holder << endl;
				if( iter->end == tmp_holder )
				{
					tmp_holder = i;
					PATH.push( iter->edge );
				}
				iter++;
			}
		}
		while( !PATH.empty() )
		{
			cout << PATH.top() << endl;
			PATH.pop();
		}
        system("pause");
        loop++;
    }
    system("pause");
    return 0;
}
