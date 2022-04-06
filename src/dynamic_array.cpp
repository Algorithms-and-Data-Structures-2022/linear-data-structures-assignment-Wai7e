#include "assignment/dynamic_array.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  DynamicArray::DynamicArray(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость массива
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    capacity_ = capacity;
    data_ = new int[capacity];
    // data_ = new int[capacity]{}
    // std::fill(&data_[0], &data[capacity], 0)
    for (int i = 0; i < capacity; ++i) {
      data_[i] = 0;
    }
  }
  // ++i что это

  DynamicArray::~DynamicArray() {  // деструктор
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
    data_ = nullptr;
  }

  void DynamicArray::Add(int value) {
    if (size_ == capacity_)
      Resize(capacity_ + kCapacityGrowthCoefficient);
    data_[size_] = value;
    size_++;
  }

  bool DynamicArray::Insert(int index, int value) {
    if (index < 0 or index > size_) {
      return false;
    }
    //    if (index == capacity_){
    if (size_ == capacity_) {
      Resize(capacity_ + kCapacityGrowthCoefficient);
    }

    int* arrNew = new int[capacity_]{};

    for (int i = 0; i < index; i++) {
      arrNew[i] = data_[i];
    }

    arrNew[index] = value;

    for (int i = index; i < size_; i++) {
      arrNew[i + 1] = data_[i];
    }

    data_ = arrNew;
    size_++;
    //    delete arrNew;

    return true;
  }

  //    for (int i = index; i < size_; i++) {
  //      data_[i + 1] = data_[i];
  //    }
  //    int* data_ = new int[size_];
  //    std::copy(&data_[0], &data_[size_], data_);
  //    for (int i = 0; i < size_; ++i) {
  //      return true;
  //    }

  bool DynamicArray::Set(int index, int new_value) {
    if (index >= 0 and index < size_) {
      data_[index] = new_value;
      return true;
    }
    return false;
  }

  std::optional<int> DynamicArray::Remove(int index) {
    // index < size_ потому что index начинается нумерация с 0
    if (index < 0 or index >= size_)
      return std::nullopt;
    int del_value = data_[index];
    for (int i = index; i < size_; i++)
      data_[i] = data_[i + 1];
    size_ -= 1;  // так удаляем элемент
    return del_value;
  }

  void DynamicArray::Clear() {
    data_ = nullptr;
    size_ = 0;
  }

  std::optional<int> DynamicArray::Get(int index) const {
    if (index >= 0 and index < size_) {  // проверка на out of range
      return data_[index];
    }
    return std::nullopt;
  }

  std::optional<int> DynamicArray::IndexOf(int value) const {
    for (int i = 0; i < size_; ++i) {
      if (data_[i] == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool DynamicArray::Contains(int value) const {
    for (int i = 0; i < size_; ++i) {
      if (data_[i] == value) {
        return true;
      }
    }
    return false;
    //    return IndexOf(value).has_value();
    //    Чтобы проверить, есть ли реально
    //    значение в объекте, вы можете использовать метод has_value()
  }

  bool DynamicArray::IsEmpty() const {
    return size_ == 0;
  }

  int DynamicArray::size() const {
    return size_;  // берем из класса
  }

  int DynamicArray::capacity() const {
    return capacity_;
  }

  bool DynamicArray::Resize(int new_capacity) {
    if (new_capacity > capacity_) {
      int* newArr = new int[new_capacity];
      for (int i = 0; i < capacity_; ++i)
        newArr[i] = data_[i];
      //      std::copy(data_[0], data_[capacity_], newArr);
      //      как работает capacity
      capacity_ = new_capacity;
      data_ = newArr;
      return true;
    }
    return false;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  DynamicArray::DynamicArray(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> DynamicArray::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment