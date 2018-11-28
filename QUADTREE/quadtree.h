#ifndef QUADTREE_H
#define QUADTREE_H

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>

using namespace std;

struct Point2D
{
	int x;
	int y;
	Point2D(int _x,int _y){
		x=_x;
		y=_y;
	}
	Point2D(){
		x=0;
		y=0;
	}
};

struct NodeQuad{
	Point2D pos;
	int data;
	NodeQuad(Point2D _pos,int _data){
		pos = _pos;
		data= _data;
	}
	NodeQuad(){
		data=0;
	}
};

class Quadtree
{
	

public:


	Quadtree(){
		topLeft 	= Point2D(0,0);
		botRight 	= Point2D(0,0);
		nodeQ		= NULL;
		topRightTree	= NULL;
		topLeftTree		= NULL;
		botRightTree	= NULL;
		botLeftTree		= NULL;
		tam=0;
	}
	Quadtree(Point2D topL,Point2D botR){
		nodeQ 		= NULL;
		topRightTree	= NULL;
		topLeftTree		= NULL;
		botRightTree	= NULL;
		botLeftTree		= NULL;
		topLeft 		= topL;
		botRight  		= botR;
		tam=0;
		vector<int> v;
		for (int i = 0; i < botR.x; ++i)
		{
			v.push_back(0);
		}
		for (int i = 0; i < botR.y; ++i)
		{
			matrixt.push_back(v);
		}
	}

	NodeQuad* getNode(){ return nodeQ;}
	void insert(NodeQuad*);
	void insert(Point2D,int);
	NodeQuad* search(Point2D);
	bool inBoundary(Point2D);
	void showTree(int);
	void showPoint();
	void GenerarMAtrix(vector<vector<int>> &);

	Point2D topLeft;
	Point2D botRight;

	std::vector<std::vector<int>> matrixt;
	NodeQuad *nodeQ;
	int tam;
	Quadtree *topLeftTree;
	Quadtree *topRightTree;
	Quadtree *botRightTree;
	Quadtree *botLeftTree;
		//~quadtree();	
};

void Quadtree::GenerarMAtrix(std::vector<std::vector<int>> & points){
	if (nodeQ != NULL){
    	for (int i = topLeft.y; i <botRight.y ; ++i)
    	{
    		for (int j = topLeft.x; j < botRight.x; ++j)
    		{
    			points[i][j]=1;
    		}
    	}
        return; 
    }else{
    	if (topLeftTree!=NULL)
    	{
			topLeftTree->GenerarMAtrix(points);
    	}
    	if (topRightTree!=NULL)
    	{
			topRightTree->GenerarMAtrix(points);
    	}
    	if (botLeftTree!=NULL)
    	{
    		botLeftTree->GenerarMAtrix(points);
    	}
    	if (botRightTree!=NULL)
    	{
    		botRightTree->GenerarMAtrix(points);
    	}

    }
}

void Quadtree::showPoint(){
	
	GenerarMAtrix(matrixt);
    cout<<matrixt.size()<<endl;
    for (int i = 0; i < matrixt.size(); ++i)
    {
    	for (int j = 0; j < matrixt[i].size(); ++j)
    	{
    		cout<<matrixt[i][j];
    	}
    	cout<<"\n";
    }
}

void Quadtree::insert(Point2D point,int _data){
	if (!inBoundary(point))
	{
		return;
	}
	//cout<<tam<<endl;
	if (tam==0)
	{
		NodeQuad *node= new NodeQuad(point,_data);
		nodeQ=node;
		tam++;
		return;
	}else if (tam==1){
		tam++;
		insert(nodeQ->pos,nodeQ->data);
		nodeQ=NULL;
		
		//cout<<"AQUI"<<endl;
	}
	if ((topLeft.x + botRight.x)/2>=point.x)
	{	
		///ARRIBA IZQUIERDA
		if ((topLeft.y + botRight.y)/2>=point.y)
		{
			if (topLeftTree == NULL)
			{
				topLeftTree = new Quadtree(
					Point2D(topLeft.x,topLeft.y),
					Point2D((topLeft.x+botRight.x)/2, (topLeft.y+botRight.y)/2)
					);
				//topLeftTree->tam=1;
				topLeftTree->insert(point,_data);

			}
		////ABAJO IZQUIERDA	
		}else{
			if (botLeftTree==NULL)
			{
				botLeftTree = new Quadtree(
					Point2D(topLeft.x,(topLeft.y+botRight.y)/2),
					Point2D((topLeft.x+botRight.x)/2,botRight.y)
					);
				//botLeftTree->tam=1;
				botLeftTree->insert(point,_data);
			}
		}
	}else{
		////ARRIBA DERECHA
		if ((topLeft.y + botRight.y) / 2 >= point.y) 
        { 
            if (topRightTree == NULL) 
                topRightTree = new Quadtree( 
                    Point2D((topLeft.x + botRight.x) / 2, 
                        topLeft.y), 
                    Point2D(botRight.x, 
                        (topLeft.y + botRight.y) / 2)); 
            //topRightTree->tam=1;
            topRightTree->insert(point,_data); 
            //cout<<topRightTree->tam<<"\n";
        } 

        ///ABAJO DERECHA
        else
        { 
            if (botRightTree == NULL) 
                botRightTree = new Quadtree( 
                    Point2D((topLeft.x + botRight.x) / 2, 
                        (topLeft.y + botRight.y) / 2), 
                    Point2D(botRight.x, botRight.y)); 
            //botRightTree->tam=1;
            botRightTree->insert(point,_data); 
        } 

	}	

}

void Quadtree::showTree(int level){
	/*if (!inBoundary(p)){ 
        cout<<" ESTA EN EL LIMITE "<<"\n";
        return NULL; 
    }*/
  
    // We are at a quad of unit length 
    // We cannot subdivide this quad further 
    if (nodeQ != NULL){
    	cout<<"Posiciones de margen ("<<topLeft.x<<","<<topLeft.y<<"), ("<<botRight.x<<","<<botRight.y<<")"<<"\n";
    	cout<<" Nodito data "<<nodeQ->data<<"\n";
    	cout<<" Nodito pos "<<nodeQ->pos.x<<","<<nodeQ->pos.y<<"\n\n";
        return; 
    }else{
    	cout<<" Nodito  es Null leyendo hojas"<<"\n";
    	if (topLeftTree!=NULL)
    	{
			cout<<"Leyendo TL"<<"\n";
			cout<<"Nivel "<<level<<"\n";
    		topLeftTree->showTree(level+1);
    	}else{
    		cout<<"TL es NULL"<<"\n";
    		cout<<"Nivel "<<level<<"\n\n";
    	}
    	if (topRightTree!=NULL)
    	{
			cout<<"Leyendo TR"<<"\n";
    		cout<<"Nivel "<<level<<"\n";
    		topRightTree->showTree(level+1);

    	}else{
    		cout<<"TR es NULL"<<"\n";
    		cout<<"Nivel "<<level<<"\n\n";
    	}
    	if (botLeftTree!=NULL)
    	{
			cout<<"Leyendo BL"<<"\n";
			cout<<"Nivel "<<level<<"\n";
    		botLeftTree->showTree(level+1);
    	}else{
    		cout<<"BL es NULL"<<"\n";
    		cout<<"Nivel "<<level<<"\n\n";
    	}
    	if (botRightTree!=NULL)
    	{
			cout<<"Leyendo BR"<<"\n";
			cout<<"Nivel "<<level<<"\n";
    		botRightTree->showTree(level+1);
    	}else{
    		cout<<"BR es NULL"<<"\n";
    		cout<<"Nivel "<<level<<"\n\n";
    	}

    }
    
}

void Quadtree::insert(NodeQuad *node){
	if (node==NULL)
	{
		return;
	}
	if (!inBoundary(node->pos))
	{
		return;
	}
	if (tam==1)
	{
		if (nodeQ == NULL)
		{
			nodeQ=node;
			tam++;
			return;
		}
	}
	if ((topLeft.x + botRight.x)/2>=node->pos.x)
	{	
		///ARRIBA IZQUIERDA
		if ((topLeft.y + botRight.y)/2>=node->pos.y)
		{
			if (topLeftTree == NULL)
			{
				topLeftTree = new Quadtree(
					Point2D(topLeft.x,topLeft.y),
					Point2D((topLeft.x+botRight.x)/2, (topLeft.y+botRight.y)/2)
					);
				topLeftTree->tam=1;
				topLeftTree->insert(node);

			}
		////ABAJO IZQUIERDA	
		}else{
			if (botLeftTree==NULL)
			{
				botLeftTree = new Quadtree(
					Point2D(topLeft.x,(topLeft.y+botRight.y)/2),
					Point2D((topLeft.x+botRight.x)/2,botRight.y)
					);
				botLeftTree->tam=1;
				botLeftTree->insert(node);
			}
		}
	}else{
		////ARRIBA DERECHA
		if ((topLeft.y + botRight.y) / 2 >= node->pos.y) 
        { 
            if (topRightTree == NULL) 
                topRightTree = new Quadtree( 
                    Point2D((topLeft.x + botRight.x) / 2, 
                        topLeft.y), 
                    Point2D(botRight.x, 
                        (topLeft.y + botRight.y) / 2)); 
            topRightTree->tam=1;
            topRightTree->insert(node); 
            cout<<topRightTree->tam<<"\n";
        } 

        ///ABAJO DERECHA
        else
        { 
            if (botRightTree == NULL) 
                botRightTree = new Quadtree( 
                    Point2D((topLeft.x + botRight.x) / 2, 
                        (topLeft.y + botRight.y) / 2), 
                    Point2D(botRight.x, botRight.y)); 
            botRightTree->tam=1;
            botRightTree->insert(node); 
        } 

	}
}


NodeQuad* Quadtree::search(Point2D p){
	if (!inBoundary(p)) 
        return NULL; 
  
    // We are at a quad of unit length 
    // We cannot subdivide this quad further 
    if (nodeQ != NULL) 
        return nodeQ; 
  
    if ((topLeft.x + botRight.x) / 2 >= p.x) 
    { 
        // Indicates topLeftTree 
        if ((topLeft.y + botRight.y) / 2 >= p.y) 
        { 
            if (topLeftTree == NULL) 
                return NULL; 
            return topLeftTree->search(p); 
        } 
  
        // Indicates botLeftTree 
        else
        { 
            if (botLeftTree == NULL) 
                return NULL; 
            return botLeftTree->search(p); 
        } 
    } 
    else
    { 
        // Indicates topRightTree 
        if ((topLeft.y + botRight.y) / 2 >= p.y) 
        { 
            if (topRightTree == NULL) 
                return NULL; 
            return topRightTree->search(p); 
        } 
  
        // Indicates botRightTree 
        else
        { 
            if (botRightTree == NULL) 
                return NULL; 
            return botRightTree->search(p); 
        } 
    } 

}

bool Quadtree::inBoundary(Point2D p) 
{ 
    return (p.x >= topLeft.x && 
        p.x <= botRight.x && 
        p.y >= topLeft.y && 
        p.y <= botRight.y); 
} 




#endif	