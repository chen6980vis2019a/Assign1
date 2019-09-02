#include <vtkXMLTreeReader.h>
#include <vtkTreeLayoutStrategy.h>
#include <vtkTreeRingView.h>
#include <vtkGraphLayoutView.h>
#include <vtkHierarchicalGraphView.h>
#include <vtkViewTheme.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkSmartPointer.h>

int main(int argc, char* argv[]) {

	cout << argc + "\n";
	if (argc != 3) {
		return 0;
	}

	auto treeReader = vtkSmartPointer<vtkXMLTreeReader>::New();
	treeReader->SetFileName(argv[1]);
	treeReader->SetEdgePedigreeIdArrayName("tree edge");
	treeReader->GenerateVertexPedigreeIdsOff();
	treeReader->SetVertexPedigreeIdArrayName("id");

	auto graphReader = vtkSmartPointer<vtkXMLTreeReader>::New();
	graphReader->SetFileName(argv[2]);
	graphReader->SetEdgePedigreeIdArrayName("graph edge");
	graphReader->GenerateVertexPedigreeIdsOff();
	graphReader->SetVertexPedigreeIdArrayName("id");
	graphReader->Update();

	auto view0 = vtkSmartPointer<vtkTreeRingView>::New();
	view0->SetTreeFromInputConnection(treeReader->GetOutputPort());
	view0->SetGraphFromInputConnection(graphReader->GetOutputPort());
	view0->SetAreaLabelArrayName("id");
	view0->SetAreaColorArrayName("VertexDegree");
	view0->SetAreaHoverArrayName("id");
	view0->SetAreaLabelVisibility(true);
	view0->SetShrinkPercentage(0.02);
	view0->SetBundlingStrength(.75);
	view0->Update();
	view0->SetEdgeColorArrayName("graph edge");
	view0->SetColorEdges(true);

	auto theme = vtkViewTheme::CreateMellowTheme();
	theme->SetLineWidth(2);
	theme->SetPointSize(10);
	theme->SetSelectedCellColor(1, 1, 1);
	theme->SetSelectedPointColor(1, 1, 1);
	view0->ApplyViewTheme(theme);
	theme->FastDelete();

	auto rw0 = view0->GetRenderWindow();
	rw0->SetSize(1280, 1280);
	view0->ResetCamera();
	view0->Render();

	auto rwi0 = view0->GetInteractor();
	rwi0->Start();

	return 0;
}