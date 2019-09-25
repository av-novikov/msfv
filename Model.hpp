#ifndef MODEL_HPP_
#define MODEL_HPP_

#include "Grid.hpp"

namespace model
{
	template <typename TVal>
	struct Properties
	{
		TVal R_dim, T_dim, P_dim;
		TVal hx, hy, hz;
		int nx, ny, nz;
	};

	template <typename TVal>
	class Model
	{
	public:
		typedef Properties<TVal> Properties;
		typedef grid::Grid<TVal> Grid;
	protected:
		TVal R_dim, T_dim, P_dim, Q_dim;
		TVal hx, hy, hz;
		int nx, ny, nz;
		Grid mesh;

		void setProps(const Properties& props);
		void makeDimLess();
	public:
		Model();
		~Model();

		void snapshot(const int snap_idx);
		void load(const Properties& props);
	};

};

#endif /* MODEL_HPP_ */