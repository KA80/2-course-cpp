#include <map>

template<class Vertex>
class BfsVisitor {
  Vertex *vertex_ = nullptr;
  std::map<Vertex, Vertex> *pairs = new std::map<Vertex, Vertex>();

 public:
  void ExamineVertex(const Vertex &vertex) {
    if (vertex_ == nullptr) {
      vertex_ = new Vertex(vertex);
    } else {
      *vertex_ = vertex;
    }
  }

  void DiscoverVertex(const Vertex &vertex) {
    if (vertex_ != nullptr) {
      pairs->emplace(vertex, *vertex_);
    } else {
      pairs->emplace(vertex, vertex);
    }
  }

  size_t DistanceTo(const Vertex &target) const {
    size_t path = 0;

    auto i = target;
    while (i != (*pairs)[i] && ++path) {
      i = (*pairs)[i];
    }
    return path;
  }
  Vertex Parent(const Vertex &vertex) const {
    return (*pairs)[vertex];
  }
};
