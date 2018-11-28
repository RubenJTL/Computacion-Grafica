#include <iostream>
#include <stdlib.h> 

#include "quadtree.h"

using namespace std;

int main() 
{ 
    Quadtree center(Point2D(0, 0), Point2D(8, 8)); 
    NodeQuad a(Point2D(1, 1), 1); 
    NodeQuad b(Point2D(2, 5), 2); 
    NodeQuad c(Point2D(7, 6), 3);
    NodeQuad d(Point2D(8, 6), 4);
    NodeQuad e(Point2D(8, 7), 5);
    NodeQuad f(Point2D(8, 1), 6);
    NodeQuad g(Point2D(8, 2), 7); 

    center.insert(Point2D(1, 1), 1); 
    center.insert(Point2D(2, 5), 2); 
    center.insert(Point2D(7, 6), 3);
    center.insert(Point2D(8, 6), 4);
    center.insert(Point2D(8, 7), 5);
    center.insert(Point2D(8, 1), 6);
    center.insert(Point2D(8, 2), 7); 
    /*center.insert(&e);
    center.insert(&f);
    center.insert(&g); 
    /*center.insert(&a); 
    center.insert(&b); 
    center.insert(&c);
    center.insert(&d);
    center.insert(&e);
    center.insert(&f);
    center.insert(&g); */
    center.showTree(1);
    cout << "Node a: " << 
        center.search(Point2D(1, 1))->data << "\n"; 
    cout << "Node b: " << 
        center.search(Point2D(2, 5))->data << "\n"; 
    cout << "Node c: " << 
        center.search(Point2D(7, 6))->data << "\n"; 
    center.showPoint();
    /*cout << "Node g: " << 
        center.search(Point2D(8, 2))->data << "\n"<< 
        center.search(Point2D(8, 2))->pos.x<<","<<
        center.search(Point2D(8, 2))->pos.y<< "\n";     
    /*cout << "Non-existing node: "
        << center.search(Point2D(5, 5));
	*/
    
    return 0; 
} 