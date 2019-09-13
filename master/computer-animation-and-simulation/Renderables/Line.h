//
// Created by brent on 15.08.18.
//

#ifndef CAS_LINE_H
#define CAS_LINE_H

#include "VertexPrimitive.h"

class Line: public VertexPrimitive {
public:
	Line(GLuint shaderProgram, float width);

protected:
	void beforeInit() override;

	void afterInit() override;

	void beforeRender() override;

	void afterRender() override;

	void beforeBindUniforms() override;

	void afterBindUniforms() override;

private:
	void createLine();

private:
	std::vector<float> m_points;

	float m_width;
};


#endif //CAS_LINE_H
