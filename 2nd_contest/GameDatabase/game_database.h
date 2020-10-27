#include <iostream>
#include <utility>
#include <vector>
#include <memory>
#include <map>
#include <set>
#include <unordered_map>

bool operator>(const GameObject &a, const GameObject &b) {
  return a.id > b.id;
}

class GameDatabase {

  template<class Tp, template<class> class Compare>
  class DereferenceCompare {
    Compare<Tp> comp;

   public:
    bool operator()(const Tp *const a, const Tp *const b) const {
      return comp(*a, *b);
    }
  };

  std::map<ObjectId, GameObject, std::greater<>> map_by_id;

  std::map<std::pair<size_t, size_t>,
           std::set<GameObject *, DereferenceCompare<GameObject, std::greater>>>
      map_by_pos;

  std::unordered_map<std::string,
                     std::set<GameObject *,
                              DereferenceCompare<GameObject, std::greater>>>
      map_by_name;

  std::map<ObjectId, std::unique_ptr<GameObject>> map_un_ptr;

 public:
  GameDatabase() = default;

  /// вставляет в базу объект с именем [name] и позицией [x, y]
  /// если объект с таким id в базе уже есть, заменяет его новым
  void Insert(ObjectId id, const std::string &name, size_t x, size_t y) {
    GameObject a = {id, name, x, y};
    Remove(id);
    map_un_ptr.emplace(id, make_unique<GameObject>(a));

    map_by_pos[{x, y}].emplace(map_un_ptr[id].get());
    map_by_name[name].emplace(map_un_ptr[id].get());
    map_by_id.emplace(id, a);
  }

  /// удаляет элемент по id
  /// если такого элемента нет, ничего не делает
  void Remove(ObjectId id) {
    auto search = map_by_id.find(id);
    if (search != map_by_id.end()) {
      std::size_t x = search->second.x;
      std::size_t y = search->second.y;
      std::string name = search->second.name;

      map_by_id.erase(id);
      map_by_pos.find({x, y})->second.erase(map_un_ptr[id].get());
      map_by_name.find(name)->second.erase(map_un_ptr[id].get());

      map_un_ptr.erase(id);
    }
  }

  /// возвращает вектор объектов c именем [name]
  /// сортировка по убыванию id
  std::vector<GameObject> DataByName(std::string name) const {
    std::vector<GameObject> got_objects;
    got_objects.reserve(map_by_id.size());
    auto search = map_by_name.find(name);
    if (search != map_by_name.end()) {
      for (auto i : search->second) {
        got_objects.emplace_back(*i);
      }
    }
    return got_objects;
  }

  /// возвращает вектор объектов, находящихся в позиции [x, y]
  /// сортировка по убыванию id
  std::vector<GameObject> DataByPosition(size_t x, size_t y) const {
    std::vector<GameObject> got_objects;
    got_objects.reserve(map_by_id.size());
    auto search = map_by_pos.find(std::make_pair(x, y));
    if (search != map_by_pos.end()) {
      for (auto i : search->second) {
        got_objects.emplace_back(*i);
      }
    }
    return got_objects;
  }

  /// возвращает вектор всех объектов из базы
  /// сортировка по убыванию id
  std::vector<GameObject> Data() const {
    std::vector<GameObject> got_objects;
    got_objects.reserve(map_by_id.size());
    for (const auto &i : map_by_id) {
      got_objects.emplace_back(i.second);
    }
    return got_objects;
  }
};

