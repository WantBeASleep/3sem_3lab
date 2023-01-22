#pragma once

template <class T>
class ListNode 
{
  public:
    T data;
    ListNode<T>* next;

  ListNode(T data)
  {
    this->data = data; 
    next = nullptr;
  }

  ListNode()
  {
    next = nullptr;
  }
};



template <class T>
class LinkedList 
{
  private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int length;

  public:
    LinkedList()
    {
      head = nullptr;
      tail = nullptr;
      length = 0;
    }

    LinkedList(const LinkedList<T>& list)
    {
      length = list.length;
      head = new ListNode<T>(list.head->data);

      ListNode<T>* ptr_this = head;
      ListNode<T>* ptr_other = list.head;

      for (int i = 1; i < length; i++)
      {
        ptr_this->next = new ListNode<T>(ptr_other->next->data);
        ptr_this = ptr_this->next;
        ptr_other = ptr_other->next;
      }
      tail = ptr_this;
    }

    LinkedList& operator= (const LinkedList& list)
    {
      if (list.length == 0) {return *this;}
      length = list.length;
      head = new ListNode<T>(list.head->data);

      ListNode<T>* ptr_this = head;
      ListNode<T>* ptr_other = list.head;

      for (int i = 1; i < length; i++)
      {
        ptr_this->next = new ListNode<T>(ptr_other->next->data);
        ptr_this = ptr_this->next;
        ptr_other = ptr_other->next;
      }
      tail = ptr_this;
      return *this;
    }
    
    ~LinkedList()
    {
      ListNode<T>* ptr = head;
      ListNode<T>* ptr_prev = ptr;
 
      while (ptr) 
      {
        ptr_prev = ptr;
        ptr = ptr->next;
        if (ptr_prev) delete ptr_prev;
      }
    }

    T& Get(int index) const 
    {
      ListNode<T>* ptr = head;
      for (int i = 0; i < index; i++)
      {
        ptr = ptr->next;
      }
      return ptr->data;
    }

    void Delete(int idx)
    {
      if (length == 1)
      {
        length--;
        delete head;
        head = nullptr;
        tail = nullptr;
        return;
      }
      ListNode<T>* ptr_prev = head;
      ListNode<T>* ptr_next = nullptr;
      for(int i = 0; i < idx-1; ptr_prev = ptr_prev->next, i++);
      if (idx != length-1) {ptr_next = ptr_prev->next->next;}
      if (idx == 0)
      {
        length--;
        ptr_prev = ptr_prev->next;
        delete head;
        head = ptr_prev;
        return;
      }
      delete ptr_prev->next;
      ptr_prev->next = ptr_next;
      length--;
      tail = ptr_prev;
    }

    int IndexOf(const T& item) const 
    {
      ListNode<T>* ptr = head;
      for (int i = 0; i < length; i++){
        if (ptr->data == item) return i;
        ptr = ptr->next;
      }
      return -1;
    }

    int GetLength() const 
    {
        return length;
    }

    void Append(const T& item)
    {
      if (length == 0){
        head = new ListNode<T>(item);
        tail = head;
        length++;
      }
      else{
        tail->next = new ListNode<T>(item);
        tail = tail->next;
        length++;
      }
    }

    bool operator== (const LinkedList<T>& val) const
    {
      return true;
    }
};
