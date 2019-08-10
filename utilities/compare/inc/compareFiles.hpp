/*                  ___        __ __            ______                         *
 *                 /   |  ____/ // /_   ____   / ____/ __     __               *
 *                / /| | / __  // __ \ / __ \ / /   __/ /_ __/ /_              *
 *               / ___ |/ /_/ // / / // /_/ // /___/_  __//_  __/              *
 *              /_/  |_|\__,_//_/ /_/ \____/ \____/ /_/    /_/                 *
 *                                                                             *
 * Copyright (C) 2012-2015, Chair for Computation in Engineering, TU Muenchen  *
 * All Rights Reserved.                                                        *
 * This file is part of the high order finite element framework AdhoC++.       */

#ifndef UTILITIES_PACKAGES_COMPARE_INC_COMPAREFILES_HPP_
#define UTILITIES_PACKAGES_COMPARE_INC_COMPAREFILES_HPP_

#include "utilities/inc/functionessentials.hpp"

namespace adhocpp {
namespace utilities {

bool compareContentOfFiles( const std::string& outputFileName,
                            const std::string& referenceFileName );

} // utilities
} // adhocpp

#endif // UTILITIES_PACKAGES_COMPARE_INC_COMPAREFILES_HPP_
