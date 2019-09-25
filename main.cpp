#include "Model.hpp"

using namespace std;

#pragma comment(lib, "vtkCommonCore-7.1.lib")
#pragma comment(lib, "vtkCommonDataModel-7.1.lib")
#pragma comment(lib, "vtkFiltersCore-7.1.lib")
#pragma comment(lib, "vtkIOCore-7.1.lib")
#pragma comment(lib, "vtkIOXML-7.1.lib")

int main()
{
	typedef model::Model<double> Model;
	typedef Model::Properties Properties;

	Properties props;
	props.hx = props.hy = 2100.0;
	props.hz = 100.0;

	props.nx = props.ny = 21;
	props.nz = 1;

	props.R_dim = props.hx;
	props.T_dim = 3600.0;
	props.P_dim = 1.E+5;

	Model model;
	model.load(props);
	model.snapshot(0);

	return 0;
}