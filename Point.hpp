#ifndef POINT_HPP_
#define POINT_HPP_

namespace point
{
	enum PType { NOTYPE, INNER, BORDER, DUAL };

	template <typename TVal>
	class Point3d
	{
	public:
		PType type;
		const int id;
		union
		{
			double coords[3];
			struct
			{
				double x;	double y;	double z;
			};
		};

		Point3d() : id(-1), type(NOTYPE) {};
		Point3d(const double _x, const double _y, const double _z) : id(-1), x(_x), y(_y), z(_z), type(NOTYPE) { };
		Point3d(const int _id, const double _x, const double _y, const double _z) : id(_id), x(_x), y(_y), z(_z), type(NOTYPE) { };
		Point3d(const int _id, const double _x, const double _y, const double _z, const PType _type) : id(_id), x(_x), y(_y), z(_z), type(_type) { };
		Point3d(const int _id, const PType _type) : id(_id), type(_type) {};
		~Point3d() {};
		Point3d(const Point3d& a) : id(a.id)
		{
			(*this) = a;
		};
		Point3d& operator=(const Point3d& rhs)
		{
			x = rhs.x, y = rhs.y, z = rhs.z;
			type = rhs.type;
			return *this;
		};
		Point3d& operator/=(const double k)
		{
			x /= k;	y /= k;	z /= k;
			return *this;
		};
		Point3d& operator+=(const Point3d& rhs)
		{
			x += rhs.x;	y += rhs.y;	z += rhs.z;
			return *this;
		};
		Point3d& operator-=(const Point3d& rhs)
		{
			x -= rhs.x;	y -= rhs.y;	z -= rhs.z;
		};

		inline double norm() const { return sqrt(x * x + y * y + z * z); };

	};

	/*template <typename Point>
	inline bool operator==(const Point& a1, const Point& a2)
	{
	if ((fabs(a2.coords[0] - a1.coords[0]) > EQUALITY_TOLERANCE) ||
	(fabs(a2.coords[1] - a1.coords[1]) > EQUALITY_TOLERANCE) ||
	(fabs(a2.coords[2] - a1.coords[2]) > EQUALITY_TOLERANCE))
	return false;
	else
	return true;
	};*/
	template <typename Point>
	inline std::ostream& operator<<(std::ostream& os, const Point& a)
	{
		os << a.coords[0] << " " << a.coords[1] << " " << a.coords[2] << std::endl;
		return os;
	}
	template <typename Point>
	inline Point operator-(const Point& rhs)
	{
		return Point(-rhs.coords[0], -rhs.coords[1], -rhs.coords[2]);
	};
	template <typename Point>
	inline Point operator-(const Point& a1, const Point& a2)
	{
		return Point(a1.coords[0] - a2.coords[0], a1.coords[1] - a2.coords[1], a1.coords[2] - a2.coords[2]);
	};
	template <typename Point>
	inline Point operator+(const Point& rhs)
	{
		return Point(rhs.coords[0], rhs.coords[1], rhs.coords[2]);
	};
	template <typename Point>
	inline Point operator+(const Point& a1, const Point& a2)
	{
		return Point(a1.coords[0] + a2.coords[0], a1.coords[1] + a2.coords[1], a1.coords[2] + a2.coords[2]);
	};
	template <typename Point>
	inline Point operator*(const Point& a1, double k)
	{
		return Point(a1.coords[0] * k, a1.coords[1] * k, a1.coords[2] * k);
	};
	template <typename Point>
	inline Point operator*(double k, const Point& a1)
	{
		return a1 * k;
	};
	template <typename Point>
	inline Point operator/(const Point& a1, double k)
	{
		return Point(a1.coords[0] / k, a1.coords[1] / k, a1.coords[2] / k);
	};
	template <typename Point>
	inline Point operator/(const Point& a1, const Point& a2)
	{
		return Point(a1.coords[0] / a2.coords[0], a1.coords[1] / a2.coords[1], a1.coords[2] / a2.coords[2]);
	};
	template <typename Point>
	inline Point operator*(const Point& a1, const Point& a2)
	{
		return Point(a1.coords[0] * a2.coords[0], a1.coords[1] * a2.coords[1], a1.coords[2] * a2.coords[2]);
	};
	template <typename Point>
	inline double dot_product(const Point& a1, const Point& a2)
	{
		return a1.coords[0] * a2.coords[0] + a1.coords[1] * a2.coords[1] + a1.coords[2] * a2.coords[2];
	};
	template <typename Point>
	inline double dot_product(const Point& a1, const Point& a2, const Point& in)
	{
		const auto g = in.getMetric();
		return g[0] * a1.coords[0] * a2.coords[0] + g[1] * a1.coords[1] * a2.coords[1] + g[2] * a1.coords[2] * a2.coords[2];
	};
	template <typename Point>
	inline double distance(const Point& a1, const Point& a2, const Point& in)
	{
		return sqrt(dot_product(a2 - a1, a2 - a1, in));
	};
}

#endif /* POINT_HPP_ */