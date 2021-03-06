#include "octree.hpp"
#include "Manager.hpp"
#include <memory>

#include "utilities/inc/logging.hpp"
#include "utilities/inc/functionessentials.hpp"


int main(int argc, char *argv[])
{
    utilities::LogConfiguration::fancy = true;
    utilities::LogConfiguration::catchSignals = false;
    utilities::LogConfiguration::showLoopSummary = true;
    utilities::LogConfiguration::showProgressbar = true;
    utilities::LogConfiguration::showTimingSummary = false;
    std::string AdhoCppHeader = utilities::LogConfiguration::getAdhoCppHeader( );
    utilities::log(AdhoCppHeader, utilities::LogLevels::ERROR );
    //autoargs::ArgumentParser::parseCommandLine( argc, argv );
    //utilities::InfoLogger << "\nArguments: \n" << autoargs::ArgumentParser::listArguments( ) << '\n';

	if (argc != 2)
	{
		std::cerr<<"write the max tree depth as an argument"<<std::endl;
		return -1;
	}
	int max_level = std::stoi(std::string(argv[1]));



    const implicit::AbsImplicitGeometry* rec = new implicit::Rectangle(0., 0., 0.3, 0.3 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> rec_shared = std::make_shared<implicit::Rectangle>(0., 0., 0.3, 0.3 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> canvas = std::make_shared<implicit::Rectangle>(0., 0., 0.99, 0.99 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> circle_shared = std::make_shared<implicit::Circle>(0.3, 0.3, 0.1 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> sag = std::make_shared<implicit::Circle>(0.15, 0., 0.1 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> sol = std::make_shared<implicit::Circle>(-0.15, 0., 0.1 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> ortasi = std::make_shared<implicit::Rectangle>(-0.15, 0.1, 0.15, 0.9 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> circle_shared_2 = std::make_shared<implicit::Circle>(0., 0., 0.1 );
    const std::shared_ptr<implicit::AbsImplicitGeometry> sphere = std::make_shared<implicit::Sphere>(0.3, 0.3, 0.3, 0.1 );

    const std::shared_ptr<implicit::AbsImplicitGeometry> recAndCircle = std::make_shared<implicit::Union>(rec_shared.get(), circle_shared.get() );



    Manager M(-1., 1., -1., 1., -1., 1.);
    //M.addGeometry(&(*rec_shared));
    //M.addGeometry(rec_shared.get());
    //M.addGeometry(rec_shared);
    //M.addGeometry(circle_shared);
    //M.addGeometry(canvas);
    //M.addGeometry(circle_shared_2);

    M.addGeometry(sag);
    M.addGeometry(sol);
    M.addGeometry(ortasi);
    //M.addGeometry(sphere);
    M.createRootNodes();
    //M.generateQuadTree(max_level);
    M.renderAllGeometriesAndStart();



    delete rec;
	return 0;
}
