#include "Grid.hpp"

using namespace grid;

template <typename TVal>
Grid<TVal>::Grid()
{
}
template <typename TVal>
Grid<TVal>::Grid(const std::array<TVal, 3> _h, const std::array<int, 3> _n)
{
	create2Dgrid(_h, _n);
}
template <typename TVal>
Grid<TVal>::~Grid()
{
}
template <typename TVal>
void Grid<TVal>::create2Dgrid(const std::array<TVal, 3> _h, const std::array<int, 3> _n)
{
	hx = _h[0];		hy = _h[1];		hz = _h[2];
	nx = _n[0];		ny = _n[1];		nz = _n[2];

	V = hx * hy * hz;
	n = (nx + 2) * (ny + 2) * nz;
	Point cell_h = { hx / (TVal)nx, hy / (TVal)ny, hz / (TVal)nz };

	int counter = 0;
	Point cent = { 0.0, 0.0, 0.0 };

	// x = 0
	cells.push_back(Cell(counter++, cell::BORDER, cent, {0.0, 0.0, cell_h.z }));
	cent.y += cell_h.y / 2.0;
	for (int j = 0; j < ny; j++)
	{
		cells.push_back(Cell(counter++, cell::BORDER, cent, { 0.0, cell_h.y, cell_h.z }));
		cent.y += cell_h.y;
	}
	cent.y -= cell_h.y / 2.0;
	cells.push_back(Cell(counter++, cell::BORDER, cent, { 0.0, 0.0, cell_h.z }));
	// middle x
	cent.x -= cell_h.x / 2.0;
	for (int i = 0; i < nx; i++)
	{
		cent.x += cell_h.x;
		cent.y = 0.0;

		cells.push_back(Cell(counter++, cell::BORDER, cent, { cell_h.x, 0.0, cell_h.z }));
		cent.y += cell_h.y / 2.0;
		for (int j = 0; j < ny; j++)
		{
			cells.push_back(Cell(counter++, cell::INNER, cent, cell_h));
			cent.y += cell_h.y;
		}
		cent.y -= cell_h.y / 2.0;
		cells.push_back(Cell(counter++, cell::BORDER, cent, { cell_h.x, 0.0, cell_h.z }));
	}
	// x = hx
	cent.x = hx;
	cent.y = 0.0;
	cells.push_back(Cell(counter++, cell::BORDER, cent, { 0.0, 0.0, cell_h.z }));
	cent.y += cell_h.y / 2.0;
	for (int j = 0; j < ny; j++)
	{
		cells.push_back(Cell(counter++, cell::BORDER, cent, { 0.0, cell_h.y, cell_h.z }));
		cent.y += cell_h.y;
	}
	cent.y -= cell_h.y / 2.0;
	cells.push_back(Cell(counter++, cell::BORDER, cent, { 0.0, 0.0, cell_h.z }));
}
template <typename TVal>
void Grid<TVal>::dump(const int snap_idx)
{
	points = vtkSmartPointer<vtkPoints>::New();
	snap_grid = vtkSmartPointer<vtkStructuredGrid>::New();
	snap_grid->SetDimensions(nx + 1, ny + 1, nz + 1);

	for (int i = 0; i < nx + 1; i++)
	{
		for (int j = 0; j < ny + 1; j++)
		{
			const auto& cell = cells[j + i * (ny + 2)];
			points->InsertNextPoint(R_dim * (cell.c.x + cell.hx / 2.0), R_dim * (cell.c.y + cell.hy / 2.0), R_dim * (cell.c.z - cell.hz / 2.0));
		}
	}
	for (int i = 0; i < nx + 1; i++)
	{
		for (int j = 0; j < ny + 1; j++)
		{
			const auto& cell = cells[j + i * (ny + 2)];
			points->InsertNextPoint(R_dim * (cell.c.x + cell.hx / 2.0), R_dim * (cell.c.y + cell.hy / 2.0), R_dim * (cell.c.z + cell.hz / 2.0));
		}
	}
	snap_grid->SetPoints(points);

	//const int np = (nx + 1) * (ny + 1);
	//hexs = vtkSmartPointer<vtkCellArray>::New();
	auto poro_poro = vtkSmartPointer<vtkDoubleArray>::New();
	poro_poro->SetName("porosity");
	for (int i = 0; i < nx; i++)
	{
		for (int j = 0; j < ny; j++)
		{
			const auto& cell = cells[j + 1 + (i + 1) * (ny + 2)];
			poro_poro->InsertNextValue(1.0);
			/*auto hex = vtkSmartPointer<vtkHexahedron>::New();
			hex->GetPointIds()->SetId(0, j + i * (ny + 1));
			hex->GetPointIds()->SetId(1, j + 1 + i * (ny + 1));
			hex->GetPointIds()->SetId(2, j + 1 + (i + 1) * (ny + 1));
			hex->GetPointIds()->SetId(3, j + (i + 1) * (ny + 1));
			hex->GetPointIds()->SetId(4, j + i * (ny + 1) + np);
			hex->GetPointIds()->SetId(5, j + 1 + i * (ny + 1) + np);
			hex->GetPointIds()->SetId(6, j + 1 + (i + 1) * (ny + 1) + np);
			hex->GetPointIds()->SetId(7, j + (i + 1) * (ny + 1) + np);
			hexs->InsertNextCell(hex);*/
		}
	}

	vtkCellData* fd_frac = snap_grid->GetCellData();
	fd_frac->AddArray(poro_poro);
	//snap_grid->SetExtent(0.0, R_dim * hx, 0.0, R_dim * hy, 0.0, R_dim * hz);

	//snap_grid->SetCells(VTK_HEXAHEDRON, hexs);
	writer = vtkSmartPointer<vtkXMLStructuredGridWriter>::New();
	writer->SetFileName(getFileName(snap_idx).c_str());
	writer->SetInputData(snap_grid);
	writer->Write();
}


template class grid::Grid<float>;
template class grid::Grid<double>;