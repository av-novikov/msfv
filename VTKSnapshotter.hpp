#ifndef VTKSNAPSHOTTER_HPP_
#define VTKSNAPSHOTTER_HPP_

#include <string>

class VTKSnapshotter
{
protected:
	const std::string prefix;
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
	std::string getFileName(int i)	{	return replace(pattern, "%{STEP}", std::to_string(i));	};
	double R_dim, T_dim, P_dim, Q_dim;
public:
	VTKSnapshotter() : prefix("snaps/")
	{
		pattern = prefix + name + "_%{STEP}.vtu";
	};
	~VTKSnapshotter() {};

	void setPattern(const std::string _name) 
	{ 
		name = _name; 
		pattern = prefix + name + "_%{STEP}.vts";
	};
	void setDimensions(double _R_dim, double _T_dim, double _P_dim, double _Q_dim) {	R_dim = _R_dim;	T_dim = _T_dim;		P_dim = _P_dim;		Q_dim = _Q_dim;	};

	virtual void dump(const int snap_idx) = 0;
};

#endif /* VTKSNAPSHOTTER_HPP_ */
