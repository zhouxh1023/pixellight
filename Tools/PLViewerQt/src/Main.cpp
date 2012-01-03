/*********************************************************\
 *  File: Main.cpp                                       *
 *      PixelLight viewer with a lightweight Qt GUI-layer. Can be used to view for example scenes or to run scripted stand-alone applications.
 *      If a command line parameter is provided, the given scene or script is loaded automatically. Use drag'n'drop in order
 *      to feed the viewer. Press the 'F12'-key to make a screenshot.
 *
 *  Copyright (C) 2002-2012 The PixelLight Team (http://www.pixellight.org/)
 *
 *  This file is part of PixelLight.
 *
 *  PixelLight is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  PixelLight is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with PixelLight. If not, see <http://www.gnu.org/licenses/>.
\*********************************************************/


//[-------------------------------------------------------]
//[ Includes                                              ]
//[-------------------------------------------------------]
#include <PLCore/Frontend/FrontendMain.h>


//[-------------------------------------------------------]
//[ Module definition                                     ]
//[-------------------------------------------------------]
pl_module_application_frontend("PLViewerQt", "ApplicationQt", "PLFrontendQt::Frontend")
	pl_module_vendor("Copyright (C) 2002-2012 by The PixelLight Team")
	pl_module_license("GNU Lesser General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version")
	pl_module_description("Qt based PixelLight viewer")
pl_module_end