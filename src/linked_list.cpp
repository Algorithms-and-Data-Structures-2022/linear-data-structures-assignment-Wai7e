#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {
    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    Node* newFront = new Node(value, nullptr);
    // для создания Node нужно (значение, ссылка на след элемент)
    if (front_ == nullptr) {
      // если фронт = налпрт, то значит он пуст
      front_ = newFront;
      back_ = newFront;
    } else {
      back_->next = newFront;
      // типа back_ ссылается на newFront
      back_ = newFront;
      // сейчас присвоили значение back_(последнему числу)
    }
    size_++;
    // пишем в этом месте, чтобы не писать в теле условия if, else, а
    // так она выполняется в любом случае
  }

  bool LinkedList::Insert(int index, int value) {
    // создаем новый узел

    if (index < 0 || index > size_) {
      return false;
    }

    Node* node = new Node(value);

    if (front_ == nullptr) {
      front_ = node;
      back_ = node;
    } else {
      // получается else расмматриваем случае, когда в linked list
      // что то есть
      if (index == 0) {
        // вставка в начало linked list
        node->next = front_;
        front_ = node;
      } else if (index == size_) {
        // вставка в конец linked list
        // первым действием мы указываем на узел
        back_->next = node;
        // вторым действий мы к конечному узлу прикрепляем новый узел
        back_ = node;
      } else {
        Node* prev_node = FindNode(index - 1);
        // node->next; возвращает ссылку на след-й элем.
        // prev_node->next (next потому что брали (index - 1))
        node->next = prev_node->next;
        prev_node->next = node;
      }
    }

    size_++;

    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    Node* node = front_;
    if (index >= 0 and index < size_) {
      for (int i = 0; i < size_; ++i) {
        if (i == index) {
          node->value = new_value;
          return true;
        }
        node = node->next;
      }
    }
    return false;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index >= size_ || index < 0) {
      return std::nullopt;
    }

    if (index == 0) {
      // прикольно указываем просто auto и он сам определяет
      // какой это тип
      auto* remove_node = front_;
      // этим самым получаем значение, которое будет удалено
      // а конст чтобы оно не изменилось
      const int remove_value = remove_node->value;

      // сдвигаем "начало" списка на следующий узел
      front_ = front_->next ;

      // высвобождаем выделенную под удаляемый узел память
      delete remove_node;

      size_--;

      return remove_value;
    }
    //удаление из любой другой позиции

    auto* prev_node = FindNode(index - 1);

    // находим удаляемый узел и его значение
    auto* remove_node = prev_node->next;
    const int remove_value = remove_node->value;

    // пропуская один элемент меняем указатель, в следствии этого
    // мы пропускаем один элемент
    prev_node->next = remove_node->next;

    // высвобождаем память от узла, который мы пропустили
    delete remove_node;

    size_--;

    return remove_value;
  }

  void LinkedList::Clear() {
    // пробегаемся по всем элементам
    for (auto* curr_node = front_; curr_node != nullptr;) {
      // сохраняем адрес удаляемого узла
      auto* remove_node = curr_node;

      // чтобы пробежаться по всем узлам
      curr_node = curr_node->next;

      // удаляем текущий элемент
      // delete curr_node; нельзя удалять узел пока мы по нему пробегаемся
      // поэтому создаем remove_node
      delete remove_node;
    }

    // если я напишу так, то не удалю узлы, которые были выделены под
    // linked_list, но при этом тесты пройдутся
    front_ = nullptr;
    back_ = nullptr;
    size_ = 0;
  }

  std::optional<int> LinkedList::Get(int index) const {
    //    Node* node = front_;
    if (index >= size_ || size_ == 0 || index < 0)
      return std::nullopt;
    return FindNode(index)->value;
  }
  //      return std::nullopt;
  //    int counter = 1;
  //    while ( counter != index)
  //    {
  //      node = (*node).next;
  //      counter++;
  //    }
  //    return  (*node).value;

  std::optional<int> LinkedList::IndexOf(int value) const {
    Node* node = front_;
    for (int i = 0; i < size_; ++i) {
      if (node->value == value) {
        return i;
      }
      node = node->next;
    }
    return std::nullopt;
  }
  bool LinkedList::Contains(int value) const {
    if (IndexOf(value) != std::nullopt) {
      return true;
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    return size_ == 0;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (size_ > 0) {
      return front_->value;
    }
    return std::nullopt;
  }

  std::optional<int> LinkedList::back() const {
    if (size_ > 0) {
      return back_->value;
    }
    return std::nullopt;
  }

  Node* LinkedList::FindNode(int index) const {
    Node* node = front_;
    // эти самым мы берем начало, для дальнейшего перебора
    for (int i = 0; i < size_; ++i) {
      if (i == index) {
        // возвращаем узел по индексу
        return node;
      }
      node = node->next;
      // указываем на следующий элемент
      // получается этим самым мы пробигаемся
      // по linked_list
    }
    return nullptr;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment