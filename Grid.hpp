#ifndef GRID_HPP_
#define GRID_HPP_

#include <vector>
#include "Cell.hpp"

namespace grid
{
	template <typename TVal>
	class Grid
	{
	public:
		typedef cell::Cell3d<TVal> Cell;
		typename typedef cell::Cell3d<TVal>::Point Point;
	public:
		TVal hx, hy, hz, V;
		int nx, ny, nz, n;
		std::vector<Cell> cells;
	public:
		Grid();
		Grid(const std::array<TVal, 3> _h, const std::array<int, 3> _n);
		~Grid();
	};

};

#endif /* GRID_HPP_ */
