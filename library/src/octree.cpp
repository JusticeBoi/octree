#include "octree.hpp"

node::node() = default;

//fptr _isInsideFunc = node::setInsideOutsideTestFunction

node::node(double xmin,double xmax, double ymin, double ymax, double zmin, double zmax, unsigned int level ,std::weak_ptr<node> parent ): _x_min(xmin), _x_max(xmax), _y_min(ymin), _y_max(ymax), _z_min(zmin), _z_max(zmax), _level(level), m_parent(parent) 
{
		all_nodes.emplace_back(std::make_unique<node>(*this));
//		for(int i = 0; i < 8 ; ++i)
//		{
//			m_children.emplace_back(nullptr);
//		}
		//m_children = std::vector<std::shared_ptr<node>>(8,nullptr);
		++total_number_of_nodes;
}
void node::divideCell()
{
	double center_x = (_x_max + _x_min) * 0.5;
	double center_y = (_y_max + _y_min) * 0.5;
	double center_z = (_z_max + _z_min) * 0.5;
	int new_level = _level + 1;
    
	//std::cout <<"size of m_children : "<<m_children.size() <<std::endl;
	m_children[0] = std::make_shared<node>(_x_min,center_x,_y_min,center_y,_z_min,center_z,new_level,std::make_shared<node>(*this));

	m_children[1] = std::make_shared<node>(center_x,_x_max,_y_min,center_y,_z_min,center_z,new_level,std::make_shared<node>(*this));

	m_children[2] = std::make_shared<node>(_x_min,center_x,center_y,_y_max,_z_min,center_z,new_level,std::make_shared<node>(*this));

	m_children[3] = std::make_shared<node>(center_x,_x_max,center_y,_y_max,_z_min,center_z,new_level,std::make_shared<node>(*this));

	m_children[4] = std::make_shared<node>(_x_min,center_x,_y_min,center_y,center_z,_z_max,new_level,std::make_shared<node>(*this));

	m_children[5] = std::make_shared<node>(center_x,_x_max,_y_min,center_y,center_z,_z_max,new_level,std::make_shared<node>(*this));

	m_children[6] = std::make_shared<node>(_x_min,center_x,center_y,_y_max,center_z,_z_max,new_level,std::make_shared<node>(*this));

	m_children[7] = std::make_shared<node>(center_x,_x_max,center_y,_y_max,center_z,_z_max,new_level,std::make_shared<node>(*this));
}

unsigned int node::getLevelOfNode() const
{
	return this->_level;
}
unsigned int node::getTotalNumberOfNodes()
{
    return total_number_of_nodes;
}

bool node::amICut(const unsigned int no_points)
{
	bool cut = false;
	unsigned int insideCounter = 0 ;
	double dx = (_x_max - _x_min)/double(no_points-1);
	double dy = (_y_max - _y_min)/double(no_points-1);
	double dz = (_z_max - _z_min)/double(no_points-1);
//	std::cout <<"dx: "<<dx <<" dy: "<<dy <<" dz: "<<dz<<std::endl;
	double currentz = _z_min;
	double currenty = _y_min;
    //#pragma omp simd  
	for (unsigned int i = 0; i < no_points;++i)
	{
		double currentx = _x_min;
		for (unsigned int j = 0; j < no_points;++j)
		{
        //#pragma omp simd  
			for(unsigned int k = 0; k < no_points;++k)
			{
				//if(my_function(currentx,currenty,currentz,func)) insideCounter++;
				if(geo_->inside(currentx, currenty,currentz)) insideCounter++;
				//if(my_function(currentx,currenty,currentz,_isInsideFunc)) insideCounter++;
				currentx+=dx;

			}
			currenty+= dy;
			currentx = _x_min;
		}
		currenty = _y_min;
		currentz+= dz;
	}
//	std::cout <<"currenty: "<<currenty<<" currentz: " << currentz<<std::endl;
//	std::cout <<"inside counter : "<< insideCounter <<std::endl;
	if(insideCounter != no_points*no_points*no_points && insideCounter)
	{
		cut = true;
	}
//	std::cout <<"cut: "<<cut<<std::endl;
	return cut;


}
void node::generateQuadTree(const unsigned int _max_level)
{
	max_level = _max_level;
	if ( amICut(5) && _level < max_level)
	{
		this->divideCell();
		for(const auto& child: m_children)
		{
			child->generateQuadTree(max_level);
		}
	}
}


unsigned int node::total_number_of_nodes = 0;


implicit::AbsImplicitGeometry* node::geo_ =  nullptr;

void node::setGeometry(implicit::AbsImplicitGeometry* geo)
{
    geo_ = geo;
}

std::vector<std::unique_ptr<node>> node::all_nodes = std::vector<std::unique_ptr<node>>();

std::vector<std::vector<double>> node::getAllPoints() 
{
	std::vector<std::vector<double>> all_points;
    //all_points.reserve(node::all_nodes.size());
    std::for_each(node::all_nodes.begin(), node::all_nodes.end(), [&all_points](const std::unique_ptr<node>& node)
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

//	for(auto point_vec : all_points)
//	{
//		for( auto point : point_vec)
//		{
//			std::cout << point <<"\t";
//		}
//		std::cout << std::endl;
//	}

	return all_points;
}

std::vector<std::vector<double>> node::getAllPointsDeepestLevel() const
{
	std::vector<std::vector<double>> deepest_level_points;
    //deepest_level_points.reserve(node::all_nodes.size());
    std::for_each(node::all_nodes.begin(), node::all_nodes.end(), [this,&deepest_level_points](const std::unique_ptr<node>& node)
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
//		std::cout << deepest_level_points.size()/8<<std::endl;
//		for(auto point_vec : deepest_level_points)
//			{
//				for( auto point : point_vec)
//				{
//					std::cout << point <<"\t";
//				}
//				std::cout << std::endl;
//			}
		return deepest_level_points;

}


vtkSmartPointer<vtkUnstructuredGrid> node::assembleUGrid(const std::vector<std::vector<double>>& input_points)
		{
	vtkSmartPointer<vtkUnstructuredGrid> unstructured_grid =
			vtkSmartPointer<vtkUnstructuredGrid>::New();


	vtkSmartPointer<vtkPoints> points =
			vtkSmartPointer<vtkPoints>::New();

	vtkSmartPointer<vtkHexahedron> hex =
			vtkSmartPointer<vtkHexahedron>::New();



	std::vector<double> tmp_point;
	for(auto point_vec : input_points )
	{
		for( auto point_coord_scalar : point_vec)
		{
			tmp_point.push_back(point_coord_scalar);
		}
		points->InsertNextPoint(tmp_point[0],tmp_point[1],tmp_point[2]);
		tmp_point.clear();
	}
	unstructured_grid->SetPoints(points);
	//	  std::cout <<"points->GetNumberOfPoints() : "<< points->GetNumberOfPoints()<<"\t"<<(points->GetNumberOfPoints()) / 8 <<std::endl;
	//	  for(int a = 0;a<8 ;++a)
	//	  {
	//	  std::cout << points->GetPoint(a)[0]<<"\t"<<points->GetPoint(a)[1]<<"\t"<<points->GetPoint(a)[2]<<std::endl;
	//	  }
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
	vtkSmartPointer<vtkUnstructuredGrid> unstructured_grid = assembleUGrid();

		    writer->SetFileName(output_name.c_str());
		    writer->SetInputData(unstructured_grid);
		    writer->Write(); // writing the selected_out.vtu in the same folder.
}

void node::WriteUnstrucredGridDeepestLevel(const std::string output_name )
{
	vtkSmartPointer<vtkXMLUnstructuredGridWriter> writer =
		        vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
	vtkSmartPointer<vtkUnstructuredGrid> unstructured_grid = assembleUGrid(getAllPointsDeepestLevel());
//		    std::string folder_name = filename.substr(0,filename.find_last_of('/'));
//		    std::string outname = "sphere_.vtu";
		    writer->SetFileName(output_name.c_str());
		    writer->SetInputData(unstructured_grid);
		    writer->Write(); // writing the selected_out.vtu in the same folder.
}
