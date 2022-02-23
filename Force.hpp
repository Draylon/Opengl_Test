#ifndef FORCE_VECT_H
#define FORCE_VECT_H

class Force {
public:
	glm::vec3 vector;
	Force(glm::vec3 v) {
		vector = v;
	}
};

#endif