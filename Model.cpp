#include "Model.hpp"

using namespace model;

template <typename TVal>
Model<TVal>::Model()
{
}
template <typename TVal>
Model<TVal>::~Model()
{
}
template <typename TVal>
void Model<TVal>::load(const Properties& props)
{
	setProps(props);
	mesh.create2Dgrid({ hx, hy, hz }, { nx, ny, nz });
	mesh.setDimensions(R_dim, T_dim, P_dim, Q_dim);
	mesh.setPattern("mesh2d");
}
template <typename TVal>
void Model<TVal>::snapshot(const int snap_idx)
{
	mesh.dump(snap_idx);
}
template <typename TVal>
void Model<TVal>::setProps(const Properties& props)
{
	R_dim = props.R_dim;	
	P_dim = props.P_dim;
	T_dim = props.T_dim;
	Q_dim = R_dim * R_dim * R_dim / T_dim;

	hx = props.hx;	hy = props.hy;	hz = props.hz;
	nx = props.nx;	ny = props.ny;	nz = props.nz;

	makeDimLess();
}
template <typename TVal>
void Model<TVal>::makeDimLess()
{
	hx /= R_dim;	hy /= R_dim;	hz /= R_dim;
}


template class model::Model<float>;
template class model::Model<double>;
