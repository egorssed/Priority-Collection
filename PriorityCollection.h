#pragma once

#include <iostream>
#include <iterator>
#include <set>
#include <vector>


using namespace std;



template <typename T>
class PriorityCollection {
public:


	using Id = int;

	Id Add(T object) {
		auto it=priorities.insert({ 0, id });
		objects.push_back({ move(object), it.first });
		return id++;
	}

	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end,
		IdOutputIt ids_begin) {
		for (auto it = make_move_iterator(range_begin);
			it != make_move_iterator(range_end); ++it) {
			*(ids_begin++) = Add(*it);
		}
	}

	bool IsValid(Id id) const {
		if (id > objects.size() - 1) {
			return false;
		}
		if (objects[id].second == priorities.end()) {
			return false;
		}
		return true;
	}

	const T& Get(Id id) const {
		return objects[id].first;
	}

	void Promote(Id id) {
		auto it = objects[id].second;
		auto extr = priorities.extract(it).value();
		auto new_it=priorities.insert({ extr.first + 1, extr.second });
		objects[id].second = new_it.first;
	}

	pair<const T&, int> GetMax() const {
		auto max_info = prev(priorities.end());
		return { objects[max_info->second].first, max_info->first };
	}

	pair<T, int> PopMax() {
		auto it = prev(priorities.end());
		int priority = it->first;
		Id max_id = it->second;
		priorities.erase(it);
		objects[max_id].second = priorities.end();
		return { move(objects[max_id].first), priority };
	}
private:
	Id id = 0;
	set<pair<int, Id>> priorities;
	vector<pair<T,set<pair<int, Id>>::iterator>> objects;
};






int main() {
	
	int z;
	cin >> z;
	return 0;
}
