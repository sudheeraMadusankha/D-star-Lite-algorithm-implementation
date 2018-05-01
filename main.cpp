/*
	Name 	  :- S.M.Withanage
	Index no. :- 140698G
	Programme :- D* Lite Algorithm
	Inputs    :-
	Outputs   :-
*/

#include "Priority_queue_class.h"
#include "map.h"

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include <deque>
#include <algorithm>
#include <bits/stdc++.h>

using namespace std;

// Defined structures
struct Priority_queue_struct{
    int coordinates[2];
    float keys[2];
};
struct Tested_nodes_struct{
    int coordinates[2];
    float g;
    float rhs;
};
struct Succ_and_pred_struct{
    int coordinates[2];
};
struct Sort_struct{
    int x,y;
    float k1, k2;
};
struct Updated_edges_struct{
    int node1[2];
    int node2[2];
    int edge_cost;
};

// Function prototypes
void Initialize( deque<Priority_queue_struct> &Input, Priority_queue_class U );
void ComputeShortestPath( deque<Priority_queue_struct> &Input, Priority_queue_class U, deque<Tested_nodes_struct> Input2 );
float *CalcKey( int node[2], Priority_queue_class U  );
float *TopKey( deque<Priority_queue_struct> &Input );
void Put_into_Successors( deque<Succ_and_pred_struct> &Input, struct Succ_and_pred_struct node );
void Find_Predecessors( deque<Succ_and_pred_struct> &Input, int node[2] );
float cost( int node1[2], int node2[2] );
int UpdateVertex( int node[2], Priority_queue_class U );
bool compareInterval(Sort_struct i1, Sort_struct i2);
int *Return_ArgMin( int node[2] );
void Update_edge_cost( struct Updated_edges_struct updated_edge );

void Print_Priority_queue();

// Queues and arrays
deque<Priority_queue_struct> Priority_queue;
deque<Tested_nodes_struct> Tested_nodes;
deque<Succ_and_pred_struct> Succ;
deque<Succ_and_pred_struct> Pred;
deque<Updated_edges_struct> Updated_edges;
float map1[10][10][8];                           // input map with edge costs
float map2[10][10][2];                           // nodes with { g, rhs }

// Global variables
float k_m;
int grid_x = 10;
int grid_y = 10;
int goal_x = 6; int start_x = 0;
int goal_y = 0; int start_y = 9;
int start_node[2] = {start_x,start_y};
int goal_node[2] = {goal_x,goal_y};
int last_node[2];
float inf = std::numeric_limits<float>::infinity();
int Found_changes = 0;
int old_cost;

int main()
{
    struct Priority_queue_struct test_element;		// Elment to test the priority_queue
    struct Priority_queue_struct insert_element;	// Element to insert values into the priority_queue
    int Succ_node[2];								// Array used to assign values from Succ deque
    srand( time(NULL) );
    int node1[2];									// Node1 which has been changed the edge value
    int node2[2];									// Node2 which has been changed the edge value
    float min_rhs = inf;						// Minimum rhs value which I've used to replace node rhs value if (node != goal_node)
    float cal_rhs;									// cal_rhs(s) = cost ( s,u ) + g(u) , where s belongs to Pred(u)
    Sort_struct insert_array[800];					// Array which we use to store the changed edge values
    int insert_index = 0;							// index which goes through the insert_array
    int insert_check = 0;							// checking weather that selected node should be entered to the priority_queue

    ///////////////////////////////////////////// Define a map to test //////////////////////////////////////////////////////////
    Create_Map(map1, grid_x, grid_y, inf);
    ///////////////////////////////////////////// End of definition /////////////////////////////////////////////////////////////

    last_node[0] = start_node[0]; last_node[1] = start_node[1];	// {29'''} s_last = s_start
    Priority_queue_class U;										//		   Creating an object using priority_queue_class
    Initialize(Priority_queue,U);								// {30'''} Initialize()

    ///////////////////////////////////////////////////////////// Testing area //////////////////////////////////////////////////////////////////

    /*for ( int y=0 ; y<grid_y ; y++ )
    {
        for ( int x=0 ; x<grid_y ; x++ )
        {
            cout << "| " << map1[x][y][2] << " ";
        }
        cout << endl;
    }

    cout << endl;

    for ( int y=0 ; y<grid_y ; y++ )
    {
        for ( int x=0 ; x<grid_y ; x++ )
        {
            cout << "| " << map1[x][y][6] << " ";
        }
        cout << endl;
    }*/

    //Print_Priority_queue();

	///////////////////////////////////////////////////////////// End of Test area //////////////////////////////////////////////////////////////

    ComputeShortestPath(Priority_queue,U,Tested_nodes);			// {31'''} ComputeShortestPath()
    cout << "end of shortest path" << endl;

    while ( false )//( start_node != goal_node )							// {32'''} while ( s_start != s_goal )
    {
        if ( map2[start_x][start_y][1] == inf )			// {33'''} if ( rhs(s_start) = infinity ) then there is no known path
        {
            cout << "No known path !!!" << endl;
            break;
        }

        int *ArgMin_node = Return_ArgMin(start_node);			// {34'''} s_start = arg min ( c(s_start,s')+g(s') ), where s' belongs to Succ
        start_node[0] = ArgMin_node[0];
        start_node[1] = ArgMin_node[1];

																// {35'''} Move to s_start not coded yet

																// {36'''} If any changes found :- Found_changes=1, Updated_edges_struct element put into deque Updated_edges

        if (Found_changes)																							// {37'''} if any changed edge cost detected
        {
			// Have to make the Priority_queue empty !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ERROR_____Done
            Priority_queue.clear();

            k_m = k_m + U.h(last_node,start_node);																	// {38'''} km = km + h(s_last,s_start)
            last_node[0] = start_node[0]; last_node[1] = start_node[1];												// {39'''} s_last = s_start

            for ( int i=0 ; i<Updated_edges.size() ; i++ )															// {40'''} for loop goes through all edge updates
            {
                Update_edge_cost(Updated_edges.at(i));																// {41,42'''} getting updated cost and connected nodes to Update_edge_cost, node1 & node2
                node1[0] = Updated_edges.at(i).node1[0]; node1[1] = Updated_edges.at(i).node1[1];					// 		      old_cost is updated in the Update_edge_cost function
                node2[0] = Updated_edges.at(i).node2[0]; node2[1] = Updated_edges.at(i).node2[1];

                if (old_cost > Updated_edges.at(i).edge_cost)														// {43'''} if (old_cost > new_cost)
                {
                    if( map2[ node2[0] ][ node2[1] ][1] > ( map2[node1[0]][node1[1]][0] + cost( node1, node2 )))	// {44'''} rhs(node2) = min ( rhs(node2),cost(node2,node1) + g(node1) )
                    {
                        map2[ node2[0] ][ node2[1] ][1] = map2[node1[0]][node1[1]][0] + cost( node1, node2 ) ;
                    }
                    if( map2[ node1[0] ][ node1[1] ][1] > ( map2[node2[0]][node2[1]][0] + cost( node1, node2 )))	// {44'''} rhs(node1) = min ( rhs(node1),cost(node1,node2) + g(node2) )
                    {
                        map2[ node1[0] ][ node1[1] ][1] = map2[node2[0]][node2[1]][0] + cost( node1, node2 ) ;
                    }
                }
                else if ( ( map2[ node1[0] ][ node1[1] ][1] == old_cost + map2[ node2[0] ][ node2[1] ][0] ) || ( map2[ node2[0] ][ node2[1] ][1] == old_cost + map2[ node1[0] ][ node1[1] ][0] ) )
																													// {45'''} Because all of my edges are Bi-directional
																													// 		   else if ( ( rhs(node1) = old_cost + g(node1) ) || ( rhs(node2) = old_cost + g(node1) ) )
                {
					if ( map2[ node2[0] ][ node2[1] ][1] == old_cost + map2[ node1[0] ][ node1[1] ][0] )			// 		   if ( rhs(node2) = old_cost + g(node1) )
					{
						if ( node2!=goal_node )																		//   	   if ( node2 != s_goal )
						{
							for (int i=0 ; i<Succ.size() ; i++)														//     	   Loop which goes through Succ deque
							{
								Succ_node[0] = Succ.at(i).coordinates[0];											// 		   Assign selected node to Succ_node
								Succ_node[1] = Succ.at(i).coordinates[1];

								// Before calculate rhs we have to check weather it is a Succ of node2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ERROR_____Done
								if ( ( abs(Succ_node[0] - node2[0])<= 1 ) && ( abs(Succ_node[1] - node2[1])<= 1 ) )
                                {
                                    cal_rhs = cost(node2,Succ_node) + map2[ Succ_node[0] ][ Succ_node[1] ][0];

                                    if (min_rhs > cal_rhs)
                                    {
                                        min_rhs = cal_rhs;
                                    }
                                }
							}
							map2[ node2[0] ][ node2[1] ][1] = min_rhs;												// {46'''} rhs(node2) = min ( cost(node2,s') + g(s') ) where s' belongs to Succ(node2)
							min_rhs = inf;
						}
					}
					if ( map2[ node1[0] ][ node1[1] ][1] == old_cost + map2[ node2[0] ][ node2[1] ][0] )			// 		   if ( rhs(node1) = old_cost + g(node2) )
					{
						if ( node1!=goal_node )																		//   	   if ( node1 != s_goal )
						{
							for (int i=0 ; i<Succ.size() ; i++)														//     	   Loop which goes through Succ deque
							{
								Succ_node[0] = Succ.at(i).coordinates[0];											// 		   Assign selected node to Succ_node
								Succ_node[1] = Succ.at(i).coordinates[1];

								// Before calculate rhs we have to check weather it is a Succ of node2 !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ERROR _____ Done
								if ( ( abs(Succ_node[0] - node1[0])<= 1 ) && ( abs(Succ_node[1] - node1[1])<= 1 ) )
                                {
                                    cal_rhs = cost(node1,Succ_node) + map2[ Succ_node[0] ][ Succ_node[1] ][0];

                                    if (min_rhs > cal_rhs)
                                    {
                                        min_rhs = cal_rhs;
                                    }
                                }
							}
							map2[ node1[0] ][ node1[1] ][1] = min_rhs;												// {46'''} rhs(node2) = min ( cost(node2,s') + g(s') ) where s' belongs to Succ(node2)
							min_rhs = inf;
						}
					}
                        //cout << "cost is " << cost( u, node2 ) << endl;
                }

                insert_check = UpdateVertex( node2, U );														// {47'''} UpdateVertex (node2)

                if (insert_check)
                {
                    insert_array[insert_index].x = node2[0];
                    insert_array[insert_index].y = node2[1];
                    float *k_cal = CalcKey( node2,U );
                    insert_array[insert_index].k1 = k_cal[0];
                    insert_array[insert_index].k2 = k_cal[1];
                    insert_index = insert_index+1;																//         Inserting changed nodes and their keys into an array
                }

                insert_check = UpdateVertex( node1, U );														// {47'''} UpdateVertex (node1)

                if (insert_check)
                {
                    insert_array[insert_check].x = node1[0];
                    insert_array[insert_index].y = node1[1];
                    float *k_cal = CalcKey( node1,U );
                    insert_array[insert_index].k1 = k_cal[0];
                    insert_array[insert_index].k2 = k_cal[1];
                    insert_index = insert_index+1;																//         Inserting changed nodes and their keys into an array
                }

                insert_check = 0;
            }																									//         All elements are inside the array

            Sort_struct sort_array[insert_index];
            for(int i=0 ; i<insert_index ; i++)
            {
                sort_array[i] = insert_array[i];
            }

            int n = sizeof(sort_array)/sizeof(sort_array[0]);												//         Sorting that array according to the key values
            sort(sort_array, sort_array+n, compareInterval);

            for(int i=0 ; i<insert_index ; i++)
            {
                insert_element.coordinates[0] = sort_array[i].x;
                insert_element.coordinates[1] = sort_array[i].y;
                insert_element.keys[0] = sort_array[i].k1;
                insert_element.keys[1] = sort_array[i].k2;
                Priority_queue.push_back(insert_element);												        //         inserting elements in the array to the Priority_queue
            }
            insert_index = 0;

            ComputeShortestPath(Priority_queue,U,Tested_nodes);												    // {48'''} ComputeShortestPath()
        }
    }

	///////////////////////////////////////////////////////////// Testing area //////////////////////////////////////////////////////////////////

    for ( int y=(grid_y-1) ; y>=0 ; y-- )
    {
        for ( int x=0 ; x<grid_y ; x++ )
        {
            if (map2[x][y][0] == inf ) cout << "| " << "X" << " ";
            else cout << "| " << map2[x][y][0] << " ";
        }
        cout << endl;
    }

    //for ( int i=0 ; i<Succ.size() ; i++ )
    //{
    //    cout << "node is (" << Succ.at(i).coordinates[0] << "," << Succ.at(i).coordinates[1] << ")" << endl;
    //}

	///////////////////////////////////////////////////////////// End of Test area //////////////////////////////////////////////////////////////

    test_element = Priority_queue.front();

    return 0;
}

/*
Name 	:- Initialize
Inputs  :- Priority_queue, Priority_queue_class object
Outputs :- none
*/

void Initialize( deque<Priority_queue_struct> &Input, Priority_queue_class U )
{
    k_m = 0.0;											// {03'''} km = 0;

    for(int x=0 ; x<grid_x ; x++)						// {04'''} all rhs(s) = g(s) = infinity
    {
        for(int y=0 ; y<grid_y ; y++)
        {
            map2[x][y][0] = inf;
            map2[x][y][1] = inf;
        }
    }

    map2[goal_x][goal_y][1] = 0;						// {05'''} rhs(goal_node) = 0;

    struct Priority_queue_struct U_element;				// {06'''} Insert ( s_goal, [h(s_start,s_goal),0] )
    U_element.coordinates[0] = goal_x;
    U_element.coordinates[1] = goal_y;
    U_element.keys[0] = U.h( start_node,goal_node );
    U_element.keys[1] = 0;

    Input.push_back(U_element);
}

/*
Name 	:- ComputeShortestPath
Inputs  :- Priority_queue, Priority_queue_class object,
Outputs :- none
*/

void ComputeShortestPath ( deque<Priority_queue_struct> &Input, Priority_queue_class U, deque<Tested_nodes_struct> Input2 )
{
    cout << "In the Path planning" << endl;
    float *Top_k = TopKey(Input);
    float *Cal_k = CalcKey(start_node,U);

    while( (Top_k[0]<Cal_k[0]) || ( (Top_k[0]==Cal_k[0]) && (Top_k[1]<Cal_k[1]) ) || (map2[start_x][start_y][1]>map2[start_x][start_y][0]) )
																								// {10'''} while ( Priority_queue.TopKey() < CalcKey() OR rhs(s_start)>s(s_start) )
    {
        float *Top_k = TopKey(Input);
        float *Cal_k = CalcKey(start_node,U);

        cout << "In the While loop" << endl;
        struct Priority_queue_struct path_element;
        struct Priority_queue_struct insert_element;
        struct Succ_and_pred_struct current_node;
        path_element = Input.front();
        int u[2];
        Sort_struct insert_array[8];
        int insert_index = 0;
        int insert_check = 0;
        float k_old[2];
        u[0] = path_element.coordinates[0];														// {11'''} u = Priority_queue.Top()
        u[1] = path_element.coordinates[1];
        cout << "New element is " << u[0] << "," << u[1] << endl;
        k_old[0] = path_element.keys[0];														// {12'''} k_old = Priority_queue.TopKey()
        k_old[1] = path_element.keys[1];
        float *k_new = CalcKey( u,U );															// {13'''} k_new = CalcKey(u)

        current_node.coordinates[0] = u[0];
        current_node.coordinates[1] = u[1];
        Put_into_Successors(Succ,current_node);													// Putting the selected node to the Succ deque

        if ( (k_old[0]<k_new[0]) || ( (k_old[0]==k_new[0]) && (k_old[1]<k_new[1]) ) )			// {14'''} if (k_old > k_new)
        {
            cout << "   In the 1 st if" << endl;
            path_element.keys[0] = k_new[0];													// {15'''} Priority_queue.Update(u,k_new)
            path_element.keys[1] = k_new[1];
            Input.at(0) = path_element;
        }
        else if ( map2[u[0]][u[1]][0]>map2[u[0]][u[1]][1] )										// {16'''} else if ( g(u) > rhs(u) )
        {
            cout << "   In the else if" << endl;
            //cout << "   Priority queue length is " << Input.size() << endl;
            map2[u[0]][u[1]][0] = map2[u[0]][u[1]][1];											// {17'''} g(u) = rhs(u)
            cout << "   New g value of " << "(" << u[0] << "," << u[1] << ") is " << map2[u[0]][u[1]][0] << endl;
            Input.pop_front();																	// {18'''} Priority_queue.remove(u)
            Find_Predecessors(Pred,u);															//         Find the predecessors of u

            for (int i=0 ; i<Pred.size() ; i++)													// {19'''} Loop goes through all the predecessors
            {
                current_node = Pred.at(i);
                int node2[2];
                node2[0] = current_node.coordinates[0];											//         node2 is the selected node from the Pred deque
                node2[1] = current_node.coordinates[1];

                if( map2[ node2[0] ][ node2[1] ][1] > ( map2[u[0]][u[1]][0] + cost( u, node2 )))// {20'''} rhs(node2) = min ( rhs(node2),cost(node2,node1) + g(node1) )
                {
                    //cout << "               " << node2[0]  << endl;
                    //cout << "               " << node2[1]  << endl;
                    map2[ node2[0] ][ node2[1] ][1] = map2[u[0]][u[1]][0] + cost( u, node2 ) ;
                    //cout << "           (x,y) is " << "(" << node2[0] << "," << node2[1] << ")" << " rhs " << map2[ node2[0] ][ node2[1] ][1] << endl;
                    cout << "               g(u) = " << map2[u[0]][u[1]][0] << " & cost = " << cost( u, node2 ) << endl;
                }

                insert_check = UpdateVertex( node2, U );	                                    // {21'''} UpdateVertex()

                if (insert_check == 1)
                {
                    //cout << "       inside the insert check " << insert_check << endl;
                    insert_array[insert_index].x = node2[0];
                    //cout << "       insert_element x is " << insert_array[insert_index].x << endl;
                    insert_array[insert_index].y = node2[1];
                    float *k_cal = CalcKey( node2,U );
                    insert_array[insert_index].k1 = k_cal[0];
                    insert_array[insert_index].k2 = k_cal[1];
                    insert_index = insert_index+1;												//         putting values into the insert array
                }
            }

            Sort_struct sort_array[insert_index];
            for(int i=0 ; i<insert_index ; i++)
            {
                sort_array[i] = insert_array[i];
            }

            int n = sizeof(sort_array)/sizeof(sort_array[0]);
            //cout << "       insert_element x before sort " << sort_array[0].x << endl;
            sort(sort_array, sort_array+n, compareInterval);								//         sort the insert array according to the keys
            //cout << "       insert_element x after sort " << sort_array[0].x << endl;

            for(int i=0 ; i<insert_index ; i++)
            {
                insert_element.coordinates[0] = sort_array[i].x;
                insert_element.coordinates[1] = sort_array[i].y;
                cout << "       insert_element is " << "(" << insert_element.coordinates[0] << "," << insert_element.coordinates[1] << ")" << endl;
                insert_element.keys[0] = sort_array[i].k1;
                insert_element.keys[1] = sort_array[i].k2;
                Priority_queue.push_back(insert_element);										//         Insert all the array into the Priority_queue
            }

            //Print_Priority_queue();
            insert_index = 0;
        }
        else																					// {22'''} else
        {
            cout << "   In the else " << endl;
            struct Succ_and_pred_struct push_u;
            push_u.coordinates[0] = u[0];
            push_u.coordinates[1] = u[1];
			Find_Predecessors(Pred,u);
            Pred.push_back(push_u);																//         push u into the Pred deque because here loop has to go through Pred(u) U {u}

            int Succ_node[2];
            float min_rhs = inf;
            float cal_rhs;
            float g_old = map2[u[0]][u[1]][0];													// {23'''} g_old = g(u)
            map2[u[0]][u[1]][0] = inf;														// {24'''} g(u) = infinity

            for (int i=0 ; i<Pred.size() ; i++)													// {25'''} loop goes through Pred(u) U {u}
            {
                current_node = Pred.at(i);
                int node2[2];
                node2[0] = current_node.coordinates[0];
                node2[1] = current_node.coordinates[1];											//         selected node is node2

                if ( map2[ node2[0] ][ node2[1] ][1] = ( g_old + cost( u, node2 ) ) )			// {26'''} if ( rhs(s) = cost(node2,u) + g_old )
                {
                    if ( node2!=goal_node )														// {27'''} if ( node2!= goal_node)
                    {
						//Have to create a different deque including nearest members of Succ deque !!!!!!!!!!!!!!!!!!!!!!!!!!!! ERROR ____ Done

                        for (int i=0 ; i<Succ.size() ; i++)										// has to loop through above deque
                        {
                            Succ_node[0] = Succ.at(i).coordinates[0];
                            Succ_node[1] = Succ.at(i).coordinates[1];
                            if ( ( abs(Succ_node[0] - node2[0])<= 1 ) && ( abs(Succ_node[1] - node2[1])<= 1 ) )
                            {
                                cal_rhs = cost(node2,Succ_node) + map2[ Succ_node[0] ][ Succ_node[1] ][0];

                                if (min_rhs > cal_rhs)
                                {
                                    min_rhs = cal_rhs;												//         rhs( node2 ) = min ( cost(node2,s') + g(s') ) where s' is Succ_node
                                }
                            }
                        }
                        map2[ node2[0] ][ node2[1] ][1] = min_rhs;
						min_rhs = inf;
                    }
                }

                insert_check = UpdateVertex( node2, U );										// {28'''} UpdateVertex()

                if (insert_check)
                {
                    insert_array[insert_check].x = node2[0];
                    insert_array[insert_index].y = node2[1];
                    float *k_cal = CalcKey( node2,U );
                    insert_array[insert_index].k1 = k_cal[0];
                    insert_array[insert_index].k2 = k_cal[1];
                    insert_index = insert_index+1;
                }
            }

            Sort_struct sort_array[insert_index];
            for(int i=0 ; i<insert_index ; i++)
            {
                sort_array[i] = insert_array[i];
            }

            int n = sizeof(sort_array)/sizeof(sort_array[0]);
            sort(sort_array, sort_array+n, compareInterval);

            for(int i=0 ; i<insert_index ; i++)
            {
                insert_element.coordinates[0] = sort_array[i].x;
                insert_element.coordinates[1] = sort_array[i].y;
                insert_element.keys[0] = sort_array[i].k1;
                insert_element.keys[1] = sort_array[i].k2;
                Priority_queue.push_back(insert_element);
            }
            insert_index = 0;
            Pred.pop_back();																	// Popping back the {u} from Pred(u)
        }

        cout << "   Cal_k k1 = " << Cal_k[0] << endl;
        cout << "   Top_k k1 = " << Top_k[0] << endl;
        cout << "   Cal_k k2 = " << Cal_k[1] << endl;
        cout << "   Top_k k2 = " << Top_k[1] << endl;
        cout << "   rhs_start = " << map2[start_x][start_y][1] << endl;
        cout << "   g_start = " << map2[start_x][start_y][0] << endl;
        cout << "   condition 1 :- " << ( Top_k[0] < Cal_k[0] ) << endl;
        cout << "   condition 2 :- " << ( map2[start_x][start_y][1] > map2[start_x][start_y][0] ) << endl;
        cout << "   condition 3 :- " << ( (Top_k[0]==Cal_k[0]) && (Top_k[1]<Cal_k[1]) ) << endl;

        if ( !( Top_k[0] < Cal_k[0] ) && !( (Top_k[0]==Cal_k[0]) && (Top_k[1]<Cal_k[1]) ) && !( map2[start_x][start_y][1] > map2[start_x][start_y][0] ) ) break;
        //cout << "end of shortest path" << endl;
        //break; // remove this when you finished building
    }
}

/*
Name 	:- CalcKey
Inputs  :- Node, Priority_queue_class object
Outputs :- array pointer for calculated keys to the input node
*/

float *CalcKey( int node[2], Priority_queue_class U  )
{
    float* k = new float[2];
    k[1] = min( map2[ node[0] ][ node[1] ][0],map2[ node[0] ][ node[1] ][1] );	// {01'''} k1 = min ( g(node), rhs(node) )
    k[0] = k[1] + U.h(start_node,node) + k_m;									// {01'''} k0 = min ( g(node), rhs(node) ) + h(s_start,node) + km
    return k;
}

/*
Name 	:- TopKey
Inputs  :- Priority_queue
Outputs :- array pointer for shortest keys in the priority queue
*/

float *TopKey( deque<Priority_queue_struct> &Input )
{
    float* k = new float[2];

    if(!Input.empty())
    {
        struct Priority_queue_struct grab_element;
        grab_element = Input.front();
        k[0] = grab_element.keys[0];
        k[1] = grab_element.keys[1];
    }else
    {
        k[0] = inf;
        k[1] = inf;
    }
    return k;
}

/*
Name 	:- Put_into_Successors
Inputs  :- Succ, Succ_and_pred_struct node
Outputs :- none
*/

void Put_into_Successors( deque<Succ_and_pred_struct> &Input, struct Succ_and_pred_struct node )
{
    Input.push_back(node);			// Push_back the node into the Succ deque
}

/*
Name 	:- Find_Predecessors
Inputs  :- Pred, int node[2]
Outputs :- none
*/

void Find_Predecessors( deque<Succ_and_pred_struct> &Input, int node[2] )
{
	// Make Pred deque empty		!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!Error____ Done
	Pred.clear();
    struct Succ_and_pred_struct test_element;
    struct Succ_and_pred_struct insert_element;
    int Successor_check = 0;

    for (int x=(-1); x<=1 ; x++)								// Checking eight squares around the selected node
    {
        for (int y=(-1); y<=1 ; y++)
        {
            Successor_check = 0;

            if ( (x==0)&&(y==0) )								// Checking weather if it is the same node
            {
                continue;
            }
            else if ( ((node[0]+x)<0) || ((node[0]+x+1)>grid_x) || ((node[1]+y)<0) || ((node[1]+y+1)>grid_y) )
            {
                continue;										// Checking weather if it is outside from the map
            }
            else
            {
                for (int i=0 ; i<Succ.size() ; i++) 			// Checking if the node is already in successors deque
                {
                    test_element = Succ.at(i);
                    if( ( (node[0]+x)==test_element.coordinates[0] ) && ( (node[1]+y)==test_element.coordinates[1] ) )
                    {
                        Successor_check = 1;
                        break;
                    }
                }
            }
            if (Successor_check)
            {
                continue;										// if It's already in Succ deque, continue
            }
            else
            {
                insert_element.coordinates[0] = node[0]+x;		// Else put it into the Pred deque
                insert_element.coordinates[1] = node[1]+y;
                Input.push_back(insert_element);
            }
        }
    }
}

/*
Name 	:- cost
Inputs  :- node1, node2
Outputs :- return the edge cost between two nodes
*/

float cost( int node1[2], int node2[2] )
{
    float c;
    int x_difference = node1[0] - node2[0];
    int y_difference = node1[1] - node2[1];

    if (y_difference==(+1))
    {
        if (x_difference==(-1)) c = map1[node1[0]][node1[1]][4];
        if (x_difference==(0)) c = map1[node1[0]][node1[1]][5];
        if (x_difference==(+1)) c = map1[node1[0]][node1[1]][6];
    }
    if (y_difference==(0))
    {
        if (x_difference==(-1)) c = map1[node1[0]][node1[1]][3];
        if (x_difference==(0)) c = 0;
        if (x_difference==(+1)) c = map1[node1[0]][node1[1]][7];
    }
    if (y_difference==(-1))
    {
        if (x_difference==(-1)) c = map1[node1[0]][node1[1]][2];
        if (x_difference==(0)) c = map1[node1[0]][node1[1]][1];
        if (x_difference==(+1)) c = map1[node1[0]][node1[1]][0];
    }
    return c;
}

/*
Name 	:- UpdateVertex
Inputs  :- node, Priority_queue_class object
Outputs :- 1 if we have to insert anything into the priority queue
*/

int UpdateVertex( int node[2], Priority_queue_class U )
{
    int In_the_queue = 0;
    int i;
    int u[2];
    struct Priority_queue_struct check_element;

    for ( i=0 ; i<Priority_queue.size() ; i++)				// checking is the node is already in the Priority_queue
    {
        check_element = Priority_queue.at(i);

        if ( node[0]==check_element.coordinates[0] )
        {
            if ( node[1]==check_element.coordinates[1] )
            {
                In_the_queue = 1;							// Element is in the Queue
                u[0] = check_element.coordinates[0];
                u[1] = check_element.coordinates[1];
                break;
            }
        }
    }

    if ( ( map2[node[0]][node[1]][0] != map2[node[0]][node[1]][1] ) && (In_the_queue==1) )		// {07'''} if ( ( g(node) != rhs(node) ) && node is in the queue )
    {
        float *k_new = CalcKey( u,U );
        check_element.keys[0] = k_new[0];
        check_element.keys[1] = k_new[1];
        Priority_queue.at(i) = check_element;													// 		   Update ( node,CalcKey(node) )
        return 0;																				// 		   return 0 because don't have to insert node into the queue
    }
    else if ( ( map2[node[0]][node[1]][0] != map2[node[0]][node[1]][1] ) && (In_the_queue==0) ) // {08'''} if ( ( g(node) != rhs(node) ) && node is not in the queue )
    {
        return 1;																				// 		   return 1 because have to insert node into the queue
    }
    else if ( ( map2[node[0]][node[1]][0] == map2[node[0]][node[1]][1] ) && (In_the_queue==1) ) // {09'''} if ( ( g(node) == rhs(node) ) && node is in the queue )
    {
        Priority_queue.erase(Priority_queue.begin()+i);											// Remove node from Priority_queue
        return 0;
    }
    else
    {
        return 0;
    }
}

/*
Name 	:- compareInterval
Inputs  :- node1 and node2
Outputs :- return the logic if (node1 < node2)
*/

bool compareInterval(Sort_struct i1, Sort_struct i2)
{
    return ( (i1.k1 < i2.k1) || ( (i1.k1 == i2.k1) && (i1.k2 < i2.k2) ) );
}

/*
Name 	:- Return_ArgMin
Inputs  :- int node[2]
Outputs :- return node with the lowest ( c(s_start,node)+g(node) ), where node belongs to Succ
*/

int *Return_ArgMin( int node[2] )
{
    int Successor_check;
    int* return_node = new int[2];
    float ArgMin = inf;
    float cal_ArgMin;
    struct Succ_and_pred_struct test_element;

    for (int x=(-1); x<=1 ; x++)
    {
        for (int y=(-1); y<=1 ; y++)
        {
            Successor_check = 0;

            if ( (x==0)&&(y==0) )
            {
                continue;
            }
            else if ( ((node[0]+x)<0) || ((node[0]+x+1)>grid_x) || ((node[1]+y)<0) || ((node[1]+y+1)>grid_y) )
            {
                continue;
            }
            else
            {
                for (int i=0 ; i<Succ.size() ; i++) // Checking if the node is already in successors deque
                {
                    test_element = Succ.at(i);
                    if( ( (node[0]+x)==test_element.coordinates[0] ) && ( (node[1]+y)==test_element.coordinates[1] ) )
                    {
                        Successor_check = 1;
                        break;
                    }
                }
            }

            int new_node[2] = { node[0]+x , node[1]+y };
            cal_ArgMin = cost(node, new_node) + map2[ node[0]+x ][ node[1]+y ][0];

            if (Successor_check)
            {
                if (ArgMin > cal_ArgMin )
                {
                    ArgMin = cal_ArgMin;
                    return_node[0] = node[0] + x;
                    return_node[1] = node[1] + y;
                }
            }
        }
    }
    return return_node;
}

/*
Name 	:- Update_edge_cost
Inputs  :- Updated_edges_struct element - node1,node2,edge_cost
Outputs :- none
*/

void Update_edge_cost( struct Updated_edges_struct updated_edge )
{
    int node1[2] = { updated_edge.node1[0],updated_edge.node1[1] };
    int node2[2] = { updated_edge.node2[0],updated_edge.node2[1] };
    float new_cost = updated_edge.edge_cost;

    int x_difference = node1[0] - node2[0];
    int y_difference = node1[1] - node2[1];
																				// update new edge cost and assign old_cost. Both places for the same edge is updated
    if (y_difference==(+1))
    {
        if (x_difference==(-1)) old_cost = map1[node1[0]][node1[1]][0]; map1[node1[0]][node1[1]][0] = new_cost; map1[node2[0]][node2[1]][4] = new_cost;
        if (x_difference==(0)) old_cost = map1[node1[0]][node1[1]][1]; map1[node1[0]][node1[1]][1] = new_cost; map1[node2[0]][node2[1]][5] = new_cost;
        if (x_difference==(+1)) old_cost = map1[node1[0]][node1[1]][2]; map1[node1[0]][node1[1]][2] = new_cost; map1[node2[0]][node2[1]][6] = new_cost;
    }
    if (y_difference==(0))
    {
        if (x_difference==(-1)) old_cost = map1[node1[0]][node1[1]][7]; map1[node1[0]][node1[1]][7] = new_cost; map1[node2[0]][node2[1]][3] = new_cost;
        if (x_difference==(+1)) old_cost = map1[node1[0]][node1[1]][3]; map1[node1[0]][node1[1]][3] = new_cost; map1[node2[0]][node2[1]][7] = new_cost;
    }
    if (y_difference==(-1))
    {
        if (x_difference==(-1)) old_cost = map1[node1[0]][node1[1]][6]; map1[node1[0]][node1[1]][6] = new_cost; map1[node2[0]][node2[1]][2] = new_cost;
        if (x_difference==(0)) old_cost = map1[node1[0]][node1[1]][5]; map1[node1[0]][node1[1]][5] = new_cost; map1[node2[0]][node2[1]][1] = new_cost;
        if (x_difference==(+1)) old_cost = map1[node1[0]][node1[1]][4]; map1[node1[0]][node1[1]][4] = new_cost; map1[node2[0]][node2[1]][0] = new_cost;
    }
}


void Print_Priority_queue()
{
    struct Priority_queue_struct test_element;		// Elment to test the priority_queue

    for (int i=0; i<Priority_queue.size() ; i++)
    {
        cout << "1" << endl ;
        test_element = Priority_queue.at(i);
        cout << "   " << "x is " << test_element.coordinates[0] << endl;
        cout << "   " << "y is " << test_element.coordinates[1] << endl;
        cout << "   " << "k1 is " << test_element.keys[0] << endl;
        cout << "   " << "k2 is " << test_element.keys[1] << endl;
        cout << "   " << "rhs is " << map2[ test_element.coordinates[0] ][ test_element.coordinates[1] ][1] << endl;
        cout << "   " << "g is " << map2[ test_element.coordinates[0] ][ test_element.coordinates[1] ][0] << endl;
    }
}
