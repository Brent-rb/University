#ifndef CPOSTBODE_H
#define CPOSTBODE_H

class CPostbode: public CBeroep, public CPersoon {
public:
	CPostbode();
	~CPostbode();
private:
	int delivered;
};

#endif