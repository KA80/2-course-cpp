#include <map>
#include <memory>

class Object {
 public:
  virtual std::string ToString() const = 0;
  virtual ~Object() {}
};

class Child : public Object {
  std::string class_id_;

 public:
  Child(const std::string &class_id) {
    class_id_ = class_id;
  }

  std::string ToString() const override {
    return class_id_;
  }
};

class Factory {
  using fp = Object *(*)();
  std::map<std::string, fp> map_{
      {"apple!", nullptr},
      {"list", nullptr},
      {"yet another identifier", nullptr},
  };

 public:
  void Register(const std::string &class_id, Object *(*instance_creator)()) {
    map_.emplace(class_id, instance_creator);
  }

  Object *Create(const std::string &class_id) {
    if (map_[class_id] != nullptr) {
      return map_[class_id]();
    }
    return new Child(class_id);
  }
};
