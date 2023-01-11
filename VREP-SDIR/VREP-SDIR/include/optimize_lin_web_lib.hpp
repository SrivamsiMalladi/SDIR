/**
*	class containing all the necessary functions and members to make a call to the web api
**/

#include <vector>
namespace optimize_lin{

	/**	\brief	Takes two 6D points and calculates a series of stable configurations for a linear motion from the first to the second point
	*
	*	@param[in]	point_1,point_2	6D points, in the format X Y Z A B C
	*	\result		vector containing configurations as vectors of doubles or an empty vector (size=0) if an exception occurs
	*	\exception	std::ifstream::failure	thrown if an operation (opening, reading, closing) on the configuration file fails
	*	\exception	std::length_error		thrown if parts of the configuration dont match what is expected
	*	\exception std::runtime_error		thrown if the program fails to optain a curse handle or under unforseen circumstances
	**/
	std::vector<std::vector<double> > calc_stable_positions_for_lin(std::vector<double> point_1, std::vector<double> point_2);

    /** \brief dummy version of optimize_lin::calc_stable_positions_for_lin()
    *   @param[in] point_1,point_2 two 3D points, can be longer but only the first three elements (X,Y,Z) will be used
    *   \result     vector containing dummy configurations. The dummy configurations will describe a linear motion between the two input points with their first three values and are padded with Zeroes (0.0) to reach a total of 7 values.
    **/
    std::vector<std::vector<double> > calc_stable_positions_for_lin_DUMMY(std::vector<double> point_1, std::vector<double> point_2);
}