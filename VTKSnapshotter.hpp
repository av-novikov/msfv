#ifndef VTKSNAPSHOTTER_HPP_
#define VTKSNAPSHOTTER_HPP_

#include <string>

namespace snapshotter
{
	class VTKSnapshotter
	{
	protected:
		std::string prefix;
		std::string pattern, name;
		std::string replace(std::string filename, std::string from, std::string to)
		{
			size_t start_pos = 0;
			while ((start_pos = filename.find(from, start_pos)) != std::string::npos)
			{
				filename.replace(start_pos, from.length(), to);
				start_pos += to.length();
			}
			return filename;
		};
		std::string getFileName(int i, const std::string name)	{	return replace(replace(pattern, "%{STEP}", std::to_string(i)), "%{NAME}", name);	};

		double R_dim, T_dim, P_dim, Q_dim;
	public:
		VTKSnapshotter() {};
		~VTKSnapshotter() {};

		void setPrefix(const std::string _prefix) { prefix = _prefix; };
		void setPattern(const std::string _pattern) { pattern = _pattern; };
		void setDimensions(double _R_dim, double _T_dim, double _P_dim, double _Q_dim) {	R_dim = _R_dim;	T_dim = _T_dim;		P_dim = _P_dim;		Q_dim = _Q_dim;	};

		void dump(const int snap_idx);
	};
};

#endif /* VTKSNAPSHOTTER_HPP_ */
