//
// Created by brent on 14.08.18.
//

#ifndef CAS_TIMEPOINT_H
#define CAS_TIMEPOINT_H


#include <vector>
#include <glm/vec3.hpp>

class TimePoint {
public:
	TimePoint();

private:
	std::vector<glm::vec3> m_points;
	std::vector<float> m_seconds;

	bool m_looping;
};


#endif //CAS_TIMEPOINT_H
