#ifndef V2WORLD_H_
#define V2WORLD_H_


#include "V2Country.h"
#include "V2Diplomacy.h"
#include "V2Factory.h"
#include "Mapper.h"


class V2World {
	public:
		void				init(string V2Loc);
		void				addPotentialCountries(ifstream &countriesMapping, string V2Loc);
		vector<string>	getPotentialTags(); 
		void				sortCountries(const vector<string>& order);
		void				convertCountries(EU3World sourceWorld, countryMapping countryMap, cultureMapping cultureMap, unionCulturesList unionCultures, religionMapping religionMap, governmentMapping governmentMap);
		void				convertProvinces(EU3World sourceWorld, provinceMapping provinceMap, countryMapping countryMap, cultureMapping cultureMap, religionMapping religionMap);
		void				addUnions(unionMapping unionMap);
		void				convertCapitals(EU3World sourceWorld, provinceMapping provinceMap);
		void				setupStates(stateMapping);
		void				setupPops(EU3World& sourceWorld);
		void				convertTechs(EU3World sourceWorld);
		void				output(FILE*);
		void				convertDiplomacy(EU3World sourceWorld, countryMapping countryMap);
		void				convertLeaders(EU3World sourceWorld, map<int,int>& leaderIDMap);
		void				convertArmies(EU3World sourceWorld, provinceMapping provinceMap, const map<int,int>& leaderIDMap);
		void				allocateFactories(EU3World sourceWorld, V2FactoryFactory& factoryBuilder);
	private:
		void					outputHeader(FILE*);
		void				getProvinceLocalizations(string file);
		V2Province*			getProvinceForExpeditionaryArmy(const V2Country& country);
		vector<int>			getPortProvinces(vector<int> provinces);
		int					addRegimentToArmy(V2Army* army, RegimentCategory category, const inverseProvinceMapping& inverseProvinceMap, V2Country& country);
		V2Country*			getCountry(string tag);
		vector<V2Province>	provinces;
		vector<V2Country>		countries;
		vector<V2Country>		potentialCountries;
		V2Diplomacy			diplomacy;

		int					equalityLeft;
		int					libertyLeft;
};


#endif // V2WORLD_H_