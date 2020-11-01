#include <iostream>
#include <vector>
#include <string>

class FormatVisitor : public BaseVisitor {
  std::vector<std::string> formatted_code;
  std::string spaces;

 public:
  void Visit(const BaseNode *node) override {
    node->Visit(this);
  }

  void Visit(const ClassDeclarationNode *node) override {
    if (formatted_code.empty())
      PrintSpaces();
    formatted_code[formatted_code.size() - 1] +=
        ("class " + node->ClassName() + " {");
    AddSpaces();

    if (!node->PublicFields().empty()) {
      PrintSpaces();
      formatted_code[formatted_code.size() - 1] += "public:";
      AddSpaces();
      for (auto i : node->PublicFields()) {
        PrintSpaces();
        Visit(i);
        formatted_code[formatted_code.size() - 1] += ";";
      }
      PopSpaces();
      if (!node->ProtectedFields().empty() || !node->PrivateFields().empty())
        PrintEmptyLine();
    }

    if (!node->ProtectedFields().empty()) {
      PrintSpaces();
      formatted_code[formatted_code.size() - 1] += "protected:";
      AddSpaces();
      for (auto i : node->ProtectedFields()) {
        PrintSpaces();
        Visit(i);
        formatted_code[formatted_code.size() - 1] += ";";
      }
      PopSpaces();
      if (!node->PrivateFields().empty())
        PrintEmptyLine();
    }
    if (!node->PrivateFields().empty()) {
      PrintSpaces();
      formatted_code[formatted_code.size() - 1] += "private:";
      AddSpaces();
      for (auto i : node->PrivateFields()) {
        PrintSpaces();
        Visit(i);
        if (formatted_code[formatted_code.size() - 1][
            formatted_code[formatted_code.size() - 1].size() - 1] != ';')
          formatted_code[formatted_code.size() - 1] += ";";
      }
      PopSpaces();
    }
    PopSpaces();
    PrintSpaces();
    formatted_code[formatted_code.size() - 1] += "};";
  }

  void Visit(const VarDeclarationNode *node) override {
    formatted_code[formatted_code.size() - 1] +=
        node->TypeName() + " " + node->VarName();
  }

  void Visit(const MethodDeclarationNode *node) override {
    formatted_code[formatted_code.size() - 1] +=
        node->ReturnTypeName() + " " + node->MethodName() + "(";
    for (unsigned int i = 0; i < node->Arguments().size(); i++) {
      Visit(node->Arguments()[i]);
      if (i + 1 != node->Arguments().size())
        formatted_code[formatted_code.size() - 1] += ", ";
    }
    formatted_code[formatted_code.size() - 1] += ")";
  }

  const std::vector<std::string> &GetFormattedCode() const {
    return formatted_code;
  }

  void PrintSpaces() {
    PrintEmptyLine();
    formatted_code[formatted_code.size() - 1] += spaces;
  }

  void PrintEmptyLine() {
    formatted_code.emplace_back("");
  }

  void AddSpaces() {
    spaces += "  ";
  }

  void PopSpaces() {
    spaces.pop_back();
    spaces.pop_back();
  }
};
