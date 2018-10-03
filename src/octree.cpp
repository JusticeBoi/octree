#include "octree.hpp"

bool octree::isInside_sphere(double r,double c_x,double c_y,double c_z)
{
//	std::cout <<"c_x*c_x + c_y*c_y + c_z*c_z : " << c_x*c_x + c_y*c_y + c_z*c_z << " r*r : "<< r*r <<std::endl;
	return ((c_x-0.5)*(c_x-0.5) + (c_y-0.5)*(c_y-0.5) + (c_z-0.5)*(c_z-0.5) <= r*r ) ? 1: 0;
}
octree::octree()
{
}
octree::octree(double xmin,double xmax, double ymin, double ymax,double zmin,double zmax,int level ,std::weak_ptr<octree> parent ):_x_min(xmin),
											_x_max(xmax),_y_min(ymin),_y_max(ymax),_z_min(zmin),_z_max(zmax),_level(level),m_parent(parent)
{
//		std::cout << "node generated " <<std::endl;
		all_nodes.push_back(std::make_shared<octree>(*this));
		for(int i = 0; i < 8 ; ++i)
		{
			m_children.emplace_back(nullptr);
		}
		total_number_of_nodes++;

}
void octree::divideCell()
{
//	std::cout <<"divide cell " <<std::endl;
	double center_x = (_x_max + _x_min) * 0.5;
	double center_y = (_y_max + _y_min) * 0.5;
	double center_z = (_z_max + _z_min) * 0.5;
	int new_level = _level + 1;
//	std::cout <<"size of m_children : "<<m_children.size() <<std::endl;

	m_children[0] = std::make_shared<octree>(_x_min,center_x,_y_min,center_y,_z_min,center_z,new_level,std::make_shared<octree>(*this));

	m_children[1] = std::make_shared<octree>(center_x,_x_max,_y_min,center_y,_z_min,center_z,new_level,std::make_shared<octree>(*this));

	m_children[2] = std::make_shared<octree>(_x_min,center_x,center_y,_y_max,_z_min,center_z,new_level,std::make_shared<octree>(*this));

	m_children[3] = std::make_shared<octree>(center_x,_x_max,center_y,_y_max,_z_min,center_z,new_level,std::make_shared<octree>(*this));

	m_children[4] = std::make_shared<octree>(_x_min,center_x,_y_min,center_y,center_z,_z_max,new_level,std::make_shared<octree>(*this));

	m_children[5] = std::make_shared<octree>(center_x,_x_max,_y_min,center_y,center_z,_z_max,new_level,std::make_shared<octree>(*this));

	m_children[6] = std::make_shared<octree>(_x_min,center_x,center_y,_y_max,center_z,_z_max,new_level,std::make_shared<octree>(*this));

	m_children[7] = std::make_shared<octree>(center_x,_x_max,center_y,_y_max,center_z,_z_max,new_level,std::make_shared<octree>(*this));

	for(int j = 0; j < 8 ; ++j)
	{
		all_nodes.push_back(m_children[j]);
	}


}

double octree::getLevelOfNode()
{
	return this->_level;
}
bool octree::amICut(int no_points)
{
	bool cut = false;
	int insideCounter = 0 ;
	double dx = (_x_max - _x_min)/double(no_points-1);
	double dy = (_y_max - _y_min)/double(no_points-1);
	double dz = (_z_max - _z_min)/double(no_points-1);
//	std::cout <<"dx: "<<dx <<" dy: "<<dy <<" dz: "<<dz<<std::endl;
	double currentz = _z_min;
	double currenty = _y_min;
	for (int i = 0; i < no_points;++i)
	{
		double currentx = _x_min;
		for (int j = 0; j < no_points;j++)
		{
			for(int k = 0;k < no_points;k++)
			{
				if(isInside_sphere(0.5,currentx,currenty,currentz)) insideCounter++;
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
	else cut = false;
//	std::cout <<"cut: "<<cut<<std::endl;
	return cut;


}
void octree::generateQuadTree(int max_level)
{
	if ( amICut(5) && _level < max_level)
	{
		this->divideCell();
		for(auto child: m_children)
		{
			child->generateQuadTree(max_level);
		}
	}
}
unsigned int octree::total_number_of_nodes = 0;
std::vector<std::shared_ptr<octree>> octree::all_nodes = std::vector<std::shared_ptr<octree>>();

std::vector<std::vector<double>> octree::getAllPoints(int max_level)
{
	std::vector<std::vector<double>> all_points;

	std::shared_ptr<octree> nodes = std::make_shared<octree>(*this);

	for(auto node : this->all_nodes)
	{
		all_points.emplace_back(std::vector<double>{node->_x_min,node->_y_min,node->_z_min});

		all_points.emplace_back(std::vector<double>{node->_x_max,node->_y_min,node->_z_min});


		all_points.emplace_back(std::vector<double>{ node->_x_max , node->_y_max , node->_z_min });

		all_points.emplace_back(std::vector<double>{ node->_x_min, node->_y_max, node->_z_min});



		all_points.emplace_back(std::vector<double>{ node->_x_min, node->_y_min , node->_z_max });

		all_points.emplace_back(std::vector<double>{ node->_x_max , node->_y_min , node->_z_max });


		all_points.emplace_back(std::vector<double>{ node->_x_max , node->_y_max , node->_z_max });
		all_points.emplace_back(std::vector<double>{ node->_x_min , node->_y_max , node->_z_max });



	}

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

std::vector<std::vector<double>> octree::getAllPointsDeepestLevel(int max_level)
{
	std::vector<std::vector<double>> deepest_level_points;

		std::shared_ptr<octree> nodes = std::make_shared<octree>(*this);

		for(auto node : this->all_nodes)
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
			}
		}
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

void octree::showVtk(std::vector<std::vector<double>> allpoints)
{

	  vtkSmartPointer<vtkUnstructuredGrid> unstructured_grid =
			  vtkSmartPointer<vtkUnstructuredGrid>::New();


	  vtkSmartPointer<vtkPoints> points =
	    vtkSmartPointer<vtkPoints>::New();

		vtkSmartPointer<vtkHexahedron> hex =
				vtkSmartPointer<vtkHexahedron>::New();


//		 std::vector<double> tmp_point;
//
//			  for(auto point_vec : points_for_hex)
//			  	{
//			  		for( auto point_coord_scalar : point_vec)
//			  		{
//			  			tmp_point.push_back(point_coord_scalar);
//			  		}
//			  		points->InsertNextPoint(tmp_point[0],tmp_point[1],tmp_point[2]);
//			  		tmp_point.clear();
//			  	}
	  std::vector<double> tmp_point;

	  for(auto point_vec : allpoints)
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
		 renderWindowInteractor->Start();


}
