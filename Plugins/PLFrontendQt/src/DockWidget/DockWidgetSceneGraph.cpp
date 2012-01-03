/*********************************************************\
 *  File: DockWidgetSceneGraph.cpp                       *
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
#include <QtGui/qtreeview.h>
#include <QtGui/qdockwidget.h>
#include <QtGui/qmainwindow.h>
#include <PLCore/Base/Class.h>
#include <PLEngine/Application/EngineApplication.h>
#include "PLFrontendQt/QtStringAdapter.h"
#include "PLFrontendQt/DataModels/SceneGraphTreeModel.h"
#include "PLFrontendQt/DockWidget/DockWidgetManager.h"
#include "PLFrontendQt/DockWidget/DockWidgetSceneGraph.h"


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
using namespace PLCore;
using namespace PLScene;
namespace PLFrontendQt {


//[-------------------------------------------------------]
//[ RTTI interface                                        ]
//[-------------------------------------------------------]
pl_implement_class(DockWidgetSceneGraph)


//[-------------------------------------------------------]
//[ Public functions                                      ]
//[-------------------------------------------------------]
/**
*  @brief
*    Constructor
*/
DockWidgetSceneGraph::DockWidgetSceneGraph(QMainWindow *pQMainWindow, DockWidgetManager *pDockWidgetManager) : DockWidgetScene(pQMainWindow, pDockWidgetManager),
	m_pSceneGraphTreeModel(nullptr)
{
	// Get encapsulated Qt dock widget
	QDockWidget *pQDockWidget = GetQDockWidget();
	if (pQDockWidget) {
		// Create tree view and set scene graph model
		QTreeView *pQTreeView = new QTreeView();
		connect(pQTreeView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(QtSlotTreeViewClicked(const QModelIndex&)));
		pQDockWidget->setWidget(pQTreeView);
		m_pSceneGraphTreeModel = new DataModels::SceneGraphTreeModel(pQDockWidget);
		pQTreeView->setModel(m_pSceneGraphTreeModel);
		pQTreeView->expandToDepth(0);

		// Set a default start node to have a decent standard behaviour
		SceneNode *pSceneNode = nullptr;
		{
			CoreApplication *pApplication = CoreApplication::GetApplication();
			if (pApplication && pApplication->IsInstanceOf("PLEngine::EngineApplication"))
				pSceneNode = reinterpret_cast<SceneNode*>(static_cast<PLEngine::EngineApplication*>(pApplication)->GetScene());
			m_pSceneGraphTreeModel->SetStartNode(pSceneNode, true);
		}

		// Set window title
		QString sQStringWindowTitle = pQDockWidget->tr(GetClass()->GetProperties().Get("Title"));
		if (pSceneNode) {
			sQStringWindowTitle += ": ";
			sQStringWindowTitle += QtStringAdapter::PLToQt('\"' + pSceneNode->GetAbsoluteName() + '\"');	// Put it into quotes to make it possible to see e.g. trailing spaces
		}
		pQDockWidget->setWindowTitle(sQStringWindowTitle);

		// Add the created Qt dock widget to the given Qt main window
		pQMainWindow->addDockWidget(Qt::LeftDockWidgetArea, pQDockWidget);
	}
}

/**
*  @brief
*    Destructor
*/
DockWidgetSceneGraph::~DockWidgetSceneGraph()
{
}

/**
*  @brief
*    Selects the given scene node
*/
void DockWidgetSceneGraph::SelectSceneNode(SceneNode *pSceneNode)
{
	// [TODO] Select the given scene node within the scene graph tree view
}


//[-------------------------------------------------------]
//[ Private Qt slots (MOC)                                ]
//[-------------------------------------------------------]
void DockWidgetSceneGraph::QtSlotTreeViewClicked(const QModelIndex &cQModelIndex)
{
	// Is there a scene graph tree model instance?
	if (m_pSceneGraphTreeModel) {
		// If there's a dock widget manager provided, perform a dock widget manager broadcast
		DockWidgetManager *pDockWidgetManager = GetDockWidgetManager();
		if (pDockWidgetManager) {
			// Get selected scene node
			SceneNode *pSceneNode = m_pSceneGraphTreeModel->GetSceneNodeFromIndex(cQModelIndex);

			// Perform a dock widget manager broadcast
			pDockWidgetManager->CallDockWidgetsMethod("SelectSceneNode", Params<void, SceneNode*>(pSceneNode));
		}
	}
}


//[-------------------------------------------------------]
//[ Namespace                                             ]
//[-------------------------------------------------------]
} // PLFrontendQt