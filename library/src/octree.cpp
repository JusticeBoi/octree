#include "octree.hpp"

#include "utilities/inc/logging.hpp"
#include "utilities/inc/functionessentials.hpp" //node::node()
//{
//    std::cout <<"default constructed " <<'\n';
//}




node::node(double xmin,double xmax, double ymin, double ymax, double zmin, double zmax, int level ,std::weak_ptr<node> parent, const implicit::AbsImplicitGeometry* geo  ): m_parent(parent), _x_min(xmin), _x_max(xmax), _y_min(ymin), _y_max(ymax), _z_min(zmin), _z_max(zmax),   _level(level),max_level(level), _geo(geo)
{
    //my_ptr_to_all_nodes = all_nodes;
    //all_nodes->emplace_back(std::make_shared<node>(*this));
    //max_level = _level;
    //if ( isRoot() )
    //{
    //    max_level = _level;
    //}


//		for(int i = 0; i < 8 ; ++i)
//		{
//			m_children.emplace_back(nullptr);
//		}
		//m_children = std::vector<std::shared_ptr<node>>(8,nullptr);
}
void node::divideCell() {

	double center_x = (_x_max + _x_min) * 0.5;
	double center_y = (_y_max + _y_min) * 0.5;
	double center_z = (_z_max + _z_min) * 0.5;
	int new_level = _level + 1;

    m_children.reserve(8);

	m_children.emplace_back(std::make_shared<node>(center_x,_x_max,center_y,_y_max,center_z,_z_max,new_level,shared_from_this(),_geo));

	m_children.emplace_back(std::make_shared<node>(_x_min,center_x,center_y,_y_max,center_z,_z_max,new_level,shared_from_this(),_geo));

	m_children.emplace_back(std::make_shared<node>(center_x,_x_max,_y_min,center_y,center_z,_z_max,new_level,shared_from_this(),_geo));

	m_children.emplace_back(std::make_shared<node>(_x_min,center_x,_y_min,center_y,center_z,_z_max,new_level,shared_from_this(),_geo));

	m_children.emplace_back(std::make_shared<node>(center_x,_x_max,center_y,_y_max,_z_min,center_z,new_level,shared_from_this(),_geo));

	m_children.emplace_back(std::make_shared<node>(_x_min,center_x,center_y,_y_max,_z_min,center_z,new_level,shared_from_this(),_geo));

	m_children.emplace_back(std::make_shared<node>(center_x,_x_max,_y_min,center_y,_z_min,center_z,new_level,shared_from_this(),_geo));

	m_children.emplace_back(std::make_shared<node>(_x_min,center_x,_y_min,center_y,_z_min,center_z,new_level,shared_from_this(),_geo));

}
bool node::hasChildren() const
{
    return m_children.size() ? true : false;
}
bool node::isRoot() const
{
    auto spt = m_parent.lock();
    return !spt ? true : false;
}
int node::getLevelOfNode() const
{
	return _level;
}

int node::getMaxLevel() const 
{
    return max_level;
}
std::shared_ptr<node> node::getParent() const
{
    if (auto p = m_parent.lock()) return p;
    else return nullptr;
}
bool node::amICut(const int no_points)
{
	bool cut = false;
	int insideCounter = 0 ;
	double dx = (_x_max - _x_min)/double(no_points-1);
	double dy = (_y_max - _y_min)/double(no_points-1);
	double dz = (_z_max - _z_min)/double(no_points-1);
	double currentz = _z_min;
	double currenty = _y_min;
    double currentx = _x_min;
    int no_points_x = no_points;
    //int no_points_square = no_points * no_points;

    if ( dz < std::numeric_limits<double>::min() )
    {
        no_points_x = 1;  
    }
    //auto innerLoop = [&no_points,&dx,&currentx, &currenty, &currentz,this,&insideCounter]()
    auto innerLoop = [&no_points,&dx, this,&insideCounter](double& currentx, double currenty, double currentz)
    {
			for( int k = 0;k < no_points;++k)
			{
				if(_geo->inside(currentx, currenty, currentz)) 
                {
                    ++insideCounter;
                }
				currentx+=dx;
			}

    };

	for ( int i = 0; i < no_points_x;++i)
	{
		currentx = _x_min;
		for ( int j = 0; j < no_points;++j)
		{
            innerLoop(currentx, currenty, currentz);
            //innerLoop();
			//for( int k = 0;k < no_points;++k)
			//{
			//	if(_geo->inside(currentx, currenty, currentz)) 
            //    {
            //        ++insideCounter;
            //    }
			//	currentx+=dx;
			//}
			currenty+= dy;
			currentx = _x_min;
		}
        if ( insideCounter && insideCounter != no_points*no_points*(i+1) ) return true;
		currenty = _y_min;
		currentz+= dz;
	}
//	std::cout <<"currenty: "<<currenty<<" currentz: " << currentz<<std::endl;
//	std::cout <<"inside counter : "<< insideCounter <<std::endl;
	if(insideCounter != no_points*no_points*no_points_x && insideCounter)
	{
		cut = true;
	}
//	std::cout <<"cut: "<<cut<<std::endl;
	return cut;


}
void node::generateQuadTree(const int _max_level)
{
	max_level = _max_level;
	//if ( amICut(10) && _level < max_level)
	if (_level < max_level && amICut(10) ) 
	{
		this->divideCell();
		for(auto& child: m_children)
		{
			child->generateQuadTree(max_level);
		}
	}
}
void node::extendQuadTree(const int extend_by_level )
{
    SCOPED_FUNCTION_START;
    if ( isRoot( ) )
    {

        if ( max_level == 0 )
        {
            this->generateQuadTree(extend_by_level);
        }
        else
        {
            auto recursiveExtendQuadTree = [this, extend_by_level](auto &&f, const node* node) -> void
            {
                    for(auto child : node->m_children)
                    {
                        child->max_level += extend_by_level;
                        if ( child->getLevelOfNode( ) == max_level )
                        {
                            child->generateQuadTree(extend_by_level + max_level);
                        }
                        else
                        {
                            f(f,child.get());
                        }
                    }
            };
            recursiveExtendQuadTree(recursiveExtendQuadTree,this);
            max_level += extend_by_level;
        }
    }
    SCOPED_FUNCTION_END;

}
void node::getAllPointsUntilRecursive(const node* n,int level, std::vector<std::vector<double>>& fill) const
{
        if ( n->getLevelOfNode() <= level)
        {
		    fill.emplace_back(std::vector<double>{n->_x_min,n->_y_min,n->_z_min});
		    fill.emplace_back(std::vector<double>{n->_x_max,n->_y_min,n->_z_min});

		    fill.emplace_back(std::vector<double>{ n->_x_max , n->_y_max , n->_z_min });
		    fill.emplace_back(std::vector<double>{ n->_x_min, n->_y_max, n->_z_min});

		    fill.emplace_back(std::vector<double>{ n->_x_min, n->_y_min , n->_z_max });
		    fill.emplace_back(std::vector<double>{ n->_x_max , n->_y_min , n->_z_max });

		    fill.emplace_back(std::vector<double>{ n->_x_max , n->_y_max , n->_z_max });
		    fill.emplace_back(std::vector<double>{ n->_x_min , n->_y_max , n->_z_max });

        }

        for(auto& child : n->m_children )
        {
            getAllPointsUntilRecursive(child.get(),level, fill);
        }
}
std::vector<std::vector<double>> node::getAllPointsUntil(int max_l) const
{
    SCOPED_FUNCTION_START;
    if ( max_l == -1) max_l = max_level;

	std::vector<std::vector<double>> all_points;

    getAllPointsUntilRecursive(this, max_l, all_points);

	return all_points;
    SCOPED_FUNCTION_END;
}

bool node::isPointInsideMe(const Point& p )
{
    
    //bool return_val =  (_z_max <= std::numeric_limits<double>::epsilon() && _z_min <= std::numeric_limits<double>::epsilon() ) ?
    //                            p[0] >= _x_min && p[1] >= _y_min &&  p[0] <= _x_max && p[1] <= _y_max:
    //                                p[0] >= _x_min && p[1] >= _y_min && p[2] >= _z_min && p[0] <= _x_max && p[1] <= _y_max && p[2] <= _z_max ;

    //bool return_val =p[0] >= _x_min && p[1] >= _y_min &&  p[0] <= _x_max && p[1] <= _y_max;

    //if ( return_val )
    //{
    //    std::cout <<" my x min : " << _x_min << " my _x_max : " << _x_max << " my y min : " << _y_min << " my y max : " << _y_max <<'\n';
    //    std::cout <<"pointx: " << p[0] << " point y : "<< p[1] << '\n';
    //}
    return p[0] >= _x_min && p[1] >= _y_min &&  p[0] <= _x_max && p[1] <= _y_max;
}
void node::refineTowardsPoint( const Point& p )
{

    if ( this->isRoot() )
    {
        bool divided = false;
        auto recursiveFindLeaf = [&p,&divided](auto&& f, const node * n) -> void
        {
            for ( auto& child : n->m_children )
            {

                if ( !child->hasChildren() )
                {
                    if ( child->isPointInsideMe(p) )
                    {
                        child->divideCell();
                        divided = true;
                    }
                }
                else
                {
                    f(f,child.get());
                }
            }
        };
    if ( !this->hasChildren() ) 
    {
        if ( this->isPointInsideMe(p) )
        {
            this->divideCell();
            divided = true;
        }
    }
    else
    {
        recursiveFindLeaf(recursiveFindLeaf, this );
    }

    if ( divided )
    {
        ++max_level;
    }


    }
}


void node::getAllPointsAtLevelRecursive(const node* n, int max_l, std::vector<std::vector<double>>& fill) const
{
        if ( n->getLevelOfNode() == max_l)
        {
		    fill.emplace_back(std::vector<double>{n->_x_min,n->_y_min,n->_z_min});
		    fill.emplace_back(std::vector<double>{n->_x_max,n->_y_min,n->_z_min});

		    fill.emplace_back(std::vector<double>{ n->_x_max , n->_y_max , n->_z_min });
		    fill.emplace_back(std::vector<double>{ n->_x_min, n->_y_max, n->_z_min});

		    fill.emplace_back(std::vector<double>{ n->_x_min, n->_y_min , n->_z_max });
		    fill.emplace_back(std::vector<double>{ n->_x_max , n->_y_min , n->_z_max });

		    fill.emplace_back(std::vector<double>{ n->_x_max , n->_y_max , n->_z_max });
		    fill.emplace_back(std::vector<double>{ n->_x_min , n->_y_max , n->_z_max });
        }

        for(auto child : n->m_children )
        {
            getAllPointsAtLevelRecursive(child.get(),max_l, fill);
        }
}
std::vector<std::vector<double>> node::getAllPointsAtLevel(int max_l) const
{
    SCOPED_FUNCTION_START;
    if ( max_l == -1) max_l = max_level;
    //std::cout <<"max level : " << max_level <<'\n';
	std::vector<std::vector<double>> deepest_level_points;

    deepest_level_points.reserve(std::pow(4,max_level));

    if ( this->isRoot() ) getAllPointsAtLevelRecursive(this,max_l, deepest_level_points);

    else { std::cout <<"not root something is wrong"<<'\n';}

    //std::cout <<"size of deepest_level_points : " << deepest_level_points.size() <<'\n';
	return deepest_level_points;
    SCOPED_FUNCTION_END;

}

vtkSmartPointer<vtkUnstructuredGrid> node::assembleUGrid(const std::vector<std::vector<double>>& input_points) const
		{
    SCOPED_FUNCTION_START;
	vtkSmartPointer<vtkUnstructuredGrid> unstructured_grid =
			vtkSmartPointer<vtkUnstructuredGrid>::New();


	vtkSmartPointer<vtkPoints> points =
			vtkSmartPointer<vtkPoints>::New();

	vtkSmartPointer<vtkHexahedron> hex =
			vtkSmartPointer<vtkHexahedron>::New();


	std::vector<double> tmp_point;
    tmp_point.reserve(3);
	for(auto& point_vec : input_points)
	{
        std::transform(std::cbegin(point_vec), std::cend(point_vec),std::back_inserter(tmp_point),[](double point){return point;});
		//for( auto point_coord_scalar : point_vec)
		//{
		//	tmp_point.push_back(point_coord_scalar);
		//}
		points->InsertNextPoint(tmp_point[0],tmp_point[1],tmp_point[2]);
		tmp_point.clear();
	}	
	unstructured_grid->SetPoints(points);
	//	  std::cout <<"points->GetNumberOfPoints() : "<< points->GetNumberOfPoints()<<"\t"<<(points->GetNumberOfPoints()) / 8 <<std::endl;
	//	  for(int a = 0;a<8 ;++a)
	//	  {
	//	  std::cout << points->GetPoint(a)[0]<<"\t"<<points->GetPoint(a)[1]<<"\t"<<points->GetPoint(a)[2]<<std::endl;
	//	  }
     #pragma omp simd
	for ( int j =0 ; j < int(points->GetNumberOfPoints() / 8)  ;++j)
	{
		hex->Initialize();
		hex->GetPointIds()->SetNumberOfIds(8);
		for( int i = 0; i < 8 ; ++i)
		{
			hex->GetPointIds()->SetId(i,8*j +i);
		}
		unstructured_grid->InsertNextCell(hex->GetCellType(),hex->GetPointIds());
	}
    //unstructured_grid->vtkDataSet::PrintSelf(std::cout,vtkIndent());
	return unstructured_grid;
    SCOPED_FUNCTION_END;

		}
void node::WriteUnstrucredGrid(const std::string output_name ) 
{
	vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
		        vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
	vtkSmartPointer<vtkUnstructuredGrid> unstructured_grid = assembleUGrid(getAllPointsUntil());

		    writer->SetFileName(output_name.c_str());
		    writer->SetInputData(unstructured_grid);
		    writer->Write(); // writing the selected_out.vtu in the same folder.
}

void node::WriteUnstrucredGridDeepestLevel(const std::string output_name )
{
	vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
		        vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
	vtkSmartPointer<vtkUnstructuredGrid> unstructured_grid = assembleUGrid(getAllPointsAtLevel());
		    writer->SetFileName(output_name.c_str());
		    writer->SetInputData(unstructured_grid);
		    writer->Write(); // writing the selected_out.vtu in the same folder.
}
