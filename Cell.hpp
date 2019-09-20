#ifndef CELL_HPP_
#define CELL_HPP_

#include <array>
#include "Point.hpp"

namespace cell
{
	enum CType { NOTYPE, INNER, BORDER, DUAL };

	template <typename TVal>
	class Cell3d
	{
	public:
		typedef point::Point3d<TVal> Point;
	protected:
		
	public:
		int id;
		CType type;
		Point c;
		TVal hx, hy, hz, V;

		Cell3d() : id(-1), type(NOTYPE) {};
		Cell3d(const int _id, const CType _type) : id(_id), type(_type) {};
		Cell3d(const int _id, const CType _type, const Point _c, const std::array<TVal, 3> _h) : id(_id), type(_type), c(_c), hx(_h[0]), hy(_h[1]), hz(_h[2]) { V = hx * hy * hz; };
		Cell3d(const Cell3d& a) { (*this) = a; };
		~Cell3d() {};
	};
}

#endif /* CELL_HPP_ */