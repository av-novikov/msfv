#include "Grid.hpp"

using namespace grid;

template <typename TVal>
Grid<TVal>::Grid()
{}
template <typename TVal>
Grid<TVal>::Grid(const std::array<TVal, 3> _h, const std::array<int, 3> _n) : hx(_h[0]), hy(_h[1]), hz(_h[2]), nx(_n[0]), ny(_n[1]), nz(_n[2])
{
	V = hx * hy * hz;
	n = (nx + 2) * (ny + 2) * nz;
	Point cell_h = { hx / (TVal)nx, hy / (TVal)ny, hz / (TVal)nz };

	int counter = 0;
	Point cent = {0.0, 0.0, 0.0};
	for (int i = 0; i < nx; i++)
	{
		cent.x += cell_h.x;
		for (int j = 0; j < ny; j++)
		{
			cells.push_back(counter++, cell::BORDER, cent, cell_h);
			cent.y += cell_h.x / 2.0;
			for (int k = 0; k < nz; k++)
			{
				cells.push_back(counter++, cell::INNER, cent, cell_h);
				cent.y += cell_h.x;
			}
			cent.y -= cell_h.x / 2.0;
			cells.push_back(counter++, cell::BORDER, cent, cell_h);
		}
	}
}
template <typename TVal>
Grid<TVal>::~Grid()
{
}

