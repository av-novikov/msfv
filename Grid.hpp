#ifndef GRID_HPP_
#define GRID_HPP_

#include <vtkVersion.h>
#include <vtkSmartPointer.h>
#include <vtkDoubleArray.h>
#include <vtkIntArray.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkPoints.h>
#include <vtkHexahedron.h>
#include <vtkStructuredGrid.h>
#include <vtkXMLStructuredGridWriter.h>

#include <vector>
#include "Cell.hpp"
#include "VTKSnapshotter.hpp"

namespace grid
{
	template <typename TVal>
	class Grid : public VTKSnapshotter
	{
	public:
		typedef cell::Cell3d<TVal> Cell;
		typename typedef cell::Cell3d<TVal>::Point Point;
	public:
		TVal hx, hy, hz, V;
		int nx, ny, nz, n;
		std::vector<Cell> cells;

		vtkSmartPointer<vtkPoints> points;
		vtkSmartPointer<vtkStructuredGrid> snap_grid;
		vtkSmartPointer<vtkCellArray> hexs;
		vtkSmartPointer<vtkXMLStructuredGridWriter> writer;
	public:
		Grid();
		Grid(const std::array<TVal, 3> _h, const std::array<int, 3> _n);
		~Grid();

		void create2Dgrid(const std::array<TVal, 3> _h, const std::array<int, 3> _n);
		void dump(const int snap_idx);
	};

};

#endif /* GRID_HPP_ */
