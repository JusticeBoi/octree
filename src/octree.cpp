#include "octree.hpp"

node::node()
{
    std::cout <<"default constructed " <<'\n';
}




node::node(double xmin,double xmax, double ymin, double ymax, double zmin, double zmax, unsigned int level ,std::weak_ptr<node> parent, const implicit::AbsImplicitGeometry* geo, std::vector<std::shared_ptr<node>>* all_nodes  ): _x_min(xmin), _x_max(xmax), _y_min(ymin), _y_max(ymax), _z_min(zmin), _z_max(zmax), _level(level), m_parent(parent), _geo(geo)
{
    my_ptr_to_all_nodes = all_nodes; all_nodes->emplace_back(std::make_shared<node>(*this));

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
//	std::cout <<"size of m_children : "<<m_children.size() <<std::endl;
    m_children.reserve(8);
    //std::cout <<"before emplacing back"<<'\n';
    //std::cout <<"size of m_children " << m_children.size() <<'\n';

	m_children.emplace_back(std::make_shared<node>(center_x,_x_max,center_y,_y_max,center_z,_z_max,new_level,shared_from_this(),_geo,my_ptr_to_all_nodes));
    //std::cout <<"after emplacing back"<<'\n';

	m_children.emplace_back(std::make_shared<node>(_x_min,center_x,center_y,_y_max,center_z,_z_max,new_level,shared_from_this(),_geo,my_ptr_to_all_nodes));

	m_children.emplace_back(std::make_shared<node>(center_x,_x_max,_y_min,center_y,center_z,_z_max,new_level,shared_from_this(),_geo,my_ptr_to_all_nodes));

	m_children.emplace_back(std::make_shared<node>(_x_min,center_x,_y_min,center_y,center_z,_z_max,new_level,shared_from_this(),_geo,my_ptr_to_all_nodes));

	m_children.emplace_back(std::make_shared<node>(center_x,_x_max,center_y,_y_max,_z_min,center_z,new_level,shared_from_this(),_geo,my_ptr_to_all_nodes));

	m_children.emplace_back(std::make_shared<node>(_x_min,center_x,center_y,_y_max,_z_min,center_z,new_level,shared_from_this(),_geo,my_ptr_to_all_nodes));

	m_children.emplace_back(std::make_shared<node>(center_x,_x_max,_y_min,center_y,_z_min,center_z,new_level,shared_from_this(),_geo,my_ptr_to_all_nodes));

	m_children.emplace_back(std::make_shared<node>(_x_min,center_x,_y_min,center_y,_z_min,center_z,new_level,shared_from_this(),_geo,my_ptr_to_all_nodes));



	//m_children.emplace_back(std::make_shared<node>(_x_min,center_x,_y_min,center_y,_z_min,center_z,new_level,std::make_shared<node>(*this),_geo,my_ptr_to_all_nodes));

	//m_children.emplace_back(std::make_shared<node>(center_x,_x_max,_y_min,center_y,_z_min,center_z,new_level,std::make_shared<node>(*this),_geo,my_ptr_to_all_nodes));

	//m_children.emplace_back(std::make_shared<node>(_x_min,center_x,center_y,_y_max,_z_min,center_z,new_level,std::make_shared<node>(*this),_geo,my_ptr_to_all_nodes));

	//m_children.emplace_back(std::make_shared<node>(center_x,_x_max,center_y,_y_max,_z_min,center_z,new_level,std::make_shared<node>(*this),_geo,my_ptr_to_all_nodes));

	//m_children.emplace_back(std::make_shared<node>(_x_min,center_x,_y_min,center_y,center_z,_z_max,new_level,std::make_shared<node>(*this),_geo,my_ptr_to_all_nodes));

	//m_children.emplace_back(std::make_shared<node>(center_x,_x_max,_y_min,center_y,center_z,_z_max,new_level,std::make_shared<node>(*this),_geo,my_ptr_to_all_nodes));

	//m_children.emplace_back(std::make_shared<node>(_x_min,center_x,center_y,_y_max,center_z,_z_max,new_level,std::make_shared<node>(*this),_geo,my_ptr_to_all_nodes));

	//m_children.emplace_back(std::make_shared<node>(center_x,_x_max,center_y,_y_max,center_z,_z_max,new_level,std::make_shared<node>(*this),_geo,my_ptr_to_all_nodes));
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
unsigned int node::getLevelOfNode() const
{
	return this->_level;
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

	//for ( int i = 0; i < 1;++i)
    //
    //
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
        if ( !i && insideCounter != no_points*no_points && insideCounter ) return true;
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
    std::cout <<"extendQuadTree " << '\n';
    if ( isRoot() )
    {

        std::vector<std::shared_ptr<node>> iter = *my_ptr_to_all_nodes;


        for( auto& v : iter )
        {
            if ( v->getLevelOfNode() == max_level )
            {

                v->generateQuadTree(extend_by_level + max_level);
            }
        }
        max_level += extend_by_level;
        std::cout <<"size of all nodes :" << my_ptr_to_all_nodes->size() << '\n';
    }

}

std::vector<std::vector<double>> node::getAllPoints() const
{
    std::cout <<"called getAllPoints " << '\n';
	std::vector<std::vector<double>> all_points;
    std::for_each(my_ptr_to_all_nodes->begin(), my_ptr_to_all_nodes->end(), [&all_points](const std::shared_ptr<node>& node)
            {
		all_points.emplace_back(std::vector<double>{node->_x_min,node->_y_min,node->_z_min});
		all_points.emplace_back(std::vector<double>{node->_x_max,node->_y_min,node->_z_min});


		all_points.emplace_back(std::vector<double>{ node->_x_max , node->_y_max , node->_z_min });
		all_points.emplace_back(std::vector<double>{ node->_x_min, node->_y_max, node->_z_min});


		all_points.emplace_back(std::vector<double>{ node->_x_min, node->_y_min , node->_z_max });
		all_points.emplace_back(std::vector<double>{ node->_x_max , node->_y_min , node->_z_max });


		all_points.emplace_back(std::vector<double>{ node->_x_max , node->_y_max , node->_z_max });
		all_points.emplace_back(std::vector<double>{ node->_x_min , node->_y_max , node->_z_max });
            });


	return all_points;
}

std::vector<std::vector<double>> node::getAllPointsDeepestLevel() const
{
	auto start = std::chrono::steady_clock::now();
	std::vector<std::vector<double>> deepest_level_points;
    deepest_level_points.reserve(std::pow(6,max_level));
    std::for_each(my_ptr_to_all_nodes->begin(), my_ptr_to_all_nodes->end(), [this,&deepest_level_points](const std::shared_ptr<node>& node)
            {
			if(node->getLevelOfNode() == max_level)
            {
		deepest_level_points.emplace_back(std::vector<double>{node->_x_min,node->_y_min,node->_z_min});
		deepest_level_points.emplace_back(std::vector<double>{node->_x_max,node->_y_min,node->_z_min});


		deepest_level_points.emplace_back(std::vector<double>{ node->_x_max , node->_y_max , node->_z_min });
		deepest_level_points.emplace_back(std::vector<double>{ node->_x_min, node->_y_max, node->_z_min});


		deepest_level_points.emplace_back(std::vector<double>{ node->_x_min, node->_y_min , node->_z_max });
		deepest_level_points.emplace_back(std::vector<double>{ node->_x_max , node->_y_min , node->_z_max });


		deepest_level_points.emplace_back(std::vector<double>{ node->_x_max , node->_y_max , node->_z_max });
		deepest_level_points.emplace_back(std::vector<double>{ node->_x_min , node->_y_max , node->_z_max });
        }});

	    auto end = std::chrono::steady_clock::now();
	    auto diff = end - start;
	    std::cout <<"duration getAllPointsDeepestLevel :  "<< std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
		return deepest_level_points;

}


vtkSmartPointer<vtkUnstructuredGrid> node::assembleUGrid(const std::vector<std::vector<double>>& input_points) const
		{
	auto start = std::chrono::steady_clock::now();
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
   auto end = std::chrono::steady_clock::now();
   auto diff = end - start;
	std::cout <<"duration of assembleUGrid:  "<< std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
	return unstructured_grid;

		}
void node::showAll(const std::vector<std::vector<double>>& points)
{
	auto start = std::chrono::steady_clock::now();
	  vtkSmartPointer<vtkUnstructuredGrid> unstructured_grid = assembleUGrid(points);
//
//
//	  vtkSmartPointer<vtkPoints> points =
//	    vtkSmartPointer<vtkPoints>::New();
//
//		vtkSmartPointer<vtkHexahedron> hex =
//				vtkSmartPointer<vtkHexahedron>::New();
//
//
//
//	  std::vector<double> tmp_point;
//
//	  for(auto point_vec : allpoints)
//	  	{
//	  		for( auto point_coord_scalar : point_vec)
//	  		{
//	  			tmp_point.push_back(point_coord_scalar);
//	  		}
//	  		points->InsertNextPoint(tmp_point[0],tmp_point[1],tmp_point[2]);
//	  		tmp_point.clear();
//	  	}
//	  unstructured_grid->SetPoints(points);
////	  std::cout <<"points->GetNumberOfPoints() : "<< points->GetNumberOfPoints()<<"\t"<<(points->GetNumberOfPoints()) / 8 <<std::endl;
////	  for(int a = 0;a<8 ;++a)
////	  {
////	  std::cout << points->GetPoint(a)[0]<<"\t"<<points->GetPoint(a)[1]<<"\t"<<points->GetPoint(a)[2]<<std::endl;
////	  }
//	  for ( int j =0 ; j < int(points->GetNumberOfPoints() / 8)  ;++j)
//	  	{
//	  		hex->Initialize();
//	  		hex->GetPointIds()->SetNumberOfIds(8);
//	  	for( int i = 0; i < 8 ; ++i)
//	  	{
//	  		hex->GetPointIds()->SetId(i,8*j +i);
//	  	}
//	  	unstructured_grid->InsertNextCell(hex->GetCellType(),hex->GetPointIds());
//	  	}
//



		vtkSmartPointer<vtkDataSetMapper> mapper =
				vtkSmartPointer<vtkDataSetMapper>::New();

		mapper->SetInputData(unstructured_grid);

		vtkSmartPointer<vtkActor> actor =
				vtkSmartPointer<vtkActor>::New();

		actor->SetMapper(mapper);
		actor->GetProperty()->SetRepresentationToWireframe();

		vtkSmartPointer<vtkRenderer> renderer =
				vtkSmartPointer<vtkRenderer>::New();

		vtkSmartPointer<vtkRenderWindow> renderWindow =
				vtkSmartPointer<vtkRenderWindow>::New();

		renderWindow->AddRenderer(renderer);

		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
				vtkSmartPointer<vtkRenderWindowInteractor>::New();

		renderWindowInteractor->SetRenderWindow(renderWindow);

		// Add the actor to the scene
		renderer->AddActor(actor);

		renderer->SetBackground(.3, .6, .3); // Background color green
		renderWindow->Render();
		auto end = std::chrono::steady_clock::now();
		auto diff = end - start;
		std::cout <<"duration of show all:  "<< std::chrono::duration <double, std::milli> (diff).count() << " ms" << std::endl;
		renderWindowInteractor->Start();
}

void node::WriteUnstrucredGrid(const std::string output_name ) 
{
	vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
		        vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
	vtkSmartPointer<vtkUnstructuredGrid> unstructured_grid = assembleUGrid(getAllPoints());

		    writer->SetFileName(output_name.c_str());
		    writer->SetInputData(unstructured_grid);
		    writer->Write(); // writing the selected_out.vtu in the same folder.
}

void node::WriteUnstrucredGridDeepestLevel(const std::string output_name )
{
	vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
		        vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
	vtkSmartPointer<vtkUnstructuredGrid> unstructured_grid = assembleUGrid(getAllPointsDeepestLevel());
		    writer->SetFileName(output_name.c_str());
		    writer->SetInputData(unstructured_grid);
		    writer->Write(); // writing the selected_out.vtu in the same folder.
}
