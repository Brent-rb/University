//
// Created by brent on 16.08.18.
//

#ifndef CAS_INTERPOLATEDPATH_H
#define CAS_INTERPOLATEDPATH_H

#include "Path.h"


class InterpolatedPath: public Path {
public:
	InterpolatedPath(OpenGLRenderer* renderer, Mode mode, bool looping = true);
	~InterpolatedPath();

	void setTau(float tau);
	float getTau();

	void calculate() override;

	void render(float deltaMillis) override;

	glm::vec3 interpolate(float secondsPassed) override;


protected:
	float m_tau;

	std::vector<std::map<float, float>> m_samples;
	std::vector<float> m_sampledPath;
	std::vector<float> m_sampleLengths;

	glm::mat4 m_matrix;
	Line* m_line;
};


#endif //CAS_INTERPOLATEDPATH_H
