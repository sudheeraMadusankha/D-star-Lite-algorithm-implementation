#include "Priority_queue_class.h"

using namespace std;

Priority_queue_class::Priority_queue_class()
{
    //smallest_priority_vertex[0] = -1;
    //smallest_priority_vertex[1] = -1;
}

//int *Priority_queue_class::Top( queue<Priority_queue_struct> &input )
//{
//    smallest_priority_vertex[0] = input.front().coordinates[0];
//    smallest_priority_vertex[1] = input.front().coordinates[1];
//    return smallest_priority_vertex;
//}

float Priority_queue_class::h(int node1[2],int node2[2])
{
    float val  = ( floor ( sqrt( pow( (node1[0]-node2[0]),2 ) + pow( (node1[1]-node2[1]),2 ) ) * 100.0 ) ) / 100.0 ;

    return val;
}
