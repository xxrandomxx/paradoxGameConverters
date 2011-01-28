#ifndef EU3WORLD_H_
#define EU3WORLD_H_

#include <vector>
#include "EU3Province.h"
#include "Parsers/Object.h"
#include "EU3Country.h"
using namespace std;


class EU3World {
	public:
		void				init(Object* obj);
		EU3Province*	getProvince(int provNum);
	private:
		vector<EU3Province>	provinces;
		vector<EU3Country>	countries;
};


#endif // EU3WORLD_H_