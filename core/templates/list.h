#ifndef LIST_H
#define LIST_H




#define INLINE inline
template <class T, class A>
class List { 
private:
    struct Data;

public:
	class Element {
	private:
		friend class List<T, A>;

		T value;
		Element *next_ptr = nullptr;
		Element *prev_ptr = nullptr;
        Data data = nullptr;


    public:
		INLINE const Element *next() const {
			return next_ptr;
		}
		INLINE Element *next() {
			return next_ptr;
		}
        INLINE const Element *prev() const {
			return prev_ptr;
		}
        INLINE const T &operator*() const {
			return value;
		}
        INLINE const T *operator->() const {
			return &value;
		}

       
		INLINE T &get() {
			return value;
		}
		/
		INLINE const T &get() const {
			return value;
		}
		
		INLINE void set(const T &p_value) {
			value = (T &)p_value;
		}


        void erase() {
			data->erase(this);
		}

		void transfer_to_back(List<T, A> *p_dst_list);
        INLINE Element() {}


    };
    typedef T ValueType;
    struct Iterator {
		INLINE T &operator*() const {
			return E->get();
		}
		INLINE T *operator->() const { return &E->get(); }
		INLINE Iterator &operator++() {
			E = E->next();
			return *this;
		}
		INLINE Iterator &operator--() {
			E = E->prev();
			return *this;
		}

		INLINE bool operator==(const Iterator &b) const { return E == b.E; }
		INLINE bool operator!=(const Iterator &b) const { return E != b.E; }

		Iterator(Element *p_E) { E = p_E; }
		Iterator() {}
		Iterator(const Iterator &p_it) { E = p_it.E; }

	private:
		Element *E = nullptr;
	};

	struct ConstIterator {
		INLINE const T &operator*() const {
			return E->get();
		}
		INLINE const T *operator->() const { return &E->get(); }
		INLINE ConstIterator &operator++() {
			E = E->next();
			return *this;
		}
		INLINE ConstIterator &operator--() {
			E = E->prev();
			return *this;
		}

		INLINE bool operator==(const ConstIterator &b) const { return E == b.E; }
		INLINE bool operator!=(const ConstIterator &b) const { return E != b.E; }

		INLINE ConstIterator(const Element *p_E) { E = p_E; }
		INLINE ConstIterator() {}
		INLINE ConstIterator(const ConstIterator &p_it) { E = p_it.E; }

	private:
		const Element *E = nullptr;
	};

	INLINE Iterator begin() {
		return Iterator(front());
	}
	INLINE Iterator end() {
		return Iterator(nullptr);
	}

#if 0
	//to use when replacing find()
	INLINE Iterator find(const K &p_key) {
		return Iterator(find(p_key));
	}
#endif
	INLINE ConstIterator begin() const {
		return ConstIterator(front());
	}
	INLINE ConstIterator end() const {
		return ConstIterator(nullptr);
	}
#if 0
	//to use when replacing find()
	INLINE ConstIterator find(const K &p_key) const {
		return ConstIterator(find(p_key));
	}
#endif
private:
	struct _Data {
		Element *first = nullptr;
		Element *last = nullptr;
		int size_cache = 0;
    };
    _Data *_data = nullptr;
    public:
	/**
	 * return a const iterator to the beginning of the list.
	 */
	INLINE const Element *front() const {
		return _data ? _data->first : nullptr;
	}

	/**
	 * return an iterator to the beginning of the list.
	 */
	INLINE Element *front() {
		return _data ? _data->first : nullptr;
	}

	/**
	 * return a const iterator to the last member of the list.
	 */
	INLINE const Element *back() const {
		return _data ? _data->last : nullptr;
	}

	/**
	 * return an iterator to the last member of the list.
	 */
	INLINE Element *back() {
		return _data ? _data->last : nullptr;
	}

	/**
	 * store a new element at the end of the list
	 */
	Element *push_back(const T &value) {
		if (!_data) {
			_data = memnew_allocator(_Data, A);
			_data->first = nullptr;
			_data->last = nullptr;
			_data->size_cache = 0;
		}

		Element *n = memnew_allocator(Element, A);
		n->value = (T &)value;

		n->prev_ptr = _data->last;
		n->next_ptr = nullptr;
		n->data = _data;

		if (_data->last) {
			_data->last->next_ptr = n;
		}

		_data->last = n;

		if (!_data->first) {
			_data->first = n;
		}

		_data->size_cache++;

		return n;
	}

    void pop_back() {
		if (_data && _data->last) {
			erase(_data->last);
		}
	}

	/**
	 * store a new element at the beginning of the list
	 */
	Element *push_front(const T &value) {
		if (!_data) {
			_data = memnew_allocator(_Data, A);
			_data->first = nullptr;
			_data->last = nullptr;
			_data->size_cache = 0;
		}

		Element *n = memnew_allocator(Element, A);
		n->value = (T &)value;
		n->prev_ptr = nullptr;
		n->next_ptr = _data->first;
		n->data = _data;

		if (_data->first) {
			_data->first->prev_ptr = n;
		}

		_data->first = n;

		if (!_data->last) {
			_data->last = n;
		}

		_data->size_cache++;

		return n;
	}

	void pop_front() {
		if (_data && _data->first) {
			erase(_data->first);
		}
	}

	Element *insert_after(Element *p_element, const T &p_value) {

		if (!p_element) {
			return push_back(p_value);
		}

		Element *n = memnew_allocator(Element, A);
		n->value = (T &)p_value;
		n->prev_ptr = p_element;
		n->next_ptr = p_element->next_ptr;
		n->data = _data;

		if (!p_element->next_ptr) {
			_data->last = n;
		} else {
			p_element->next_ptr->prev_ptr = n;
		}

		p_element->next_ptr = n;

		_data->size_cache++;

		return n;
	}

	Element *insert_before(Element *p_element, const T &p_value) {
		if (!p_element) {
			return push_back(p_value);
		}

		Element *n = memnew_allocator(Element, A);
		n->value = (T &)p_value;
		n->prev_ptr = p_element->prev_ptr;
		n->next_ptr = p_element;
		n->data = _data;

		if (!p_element->prev_ptr) {
			_data->first = n;
		} else {
			p_element->prev_ptr->next_ptr = n;
		}

		p_element->prev_ptr = n;

		_data->size_cache++;

		return n;
	}

	/**
	 * find an element in the list,
	 */
	template <class T_v>
	Element *find(const T_v &p_val) {
		Element *it = front();
		while (it) {
			if (it->value == p_val) {
				return it;
			}
			it = it->next();
		}

		return nullptr;
	}

	/**
	 * erase an element in the list, by iterator pointing to it. Return true if it was found/erased.
	 */
	bool erase(const Element *p_I) {
		if (_data && p_I) {
			bool ret = _data->erase(p_I);

			if (_data->size_cache == 0) {
				_data = nullptr;
			}

			return ret;
		}

		return false;
	}

	/**
	 * erase the first element in the list, that contains value
	 */
	bool erase(const T &value) {
		Element *I = find(value);
		return erase(I);
	}

	/**
	 * return whether the list is empty
	 */
	INLINE bool is_empty() const {
		return (!_data || !_data->size_cache);
	}

	/**
	 * clear the list
	 */
	void clear() {
		while (front()) {
			erase(front());
		}
	}

	INLINE int size() const {
		return _data ? _data->size_cache : 0;
	}

	void swap(Element *p_A, Element *p_B) {

		if (p_A == p_B) {
			return;
		}
		Element *A_prev = p_A->prev_ptr;
		Element *A_next = p_A->next_ptr;
		Element *B_prev = p_B->prev_ptr;
		Element *B_next = p_B->next_ptr;

		if (A_prev) {
			A_prev->next_ptr = p_B;
		} else {
			_data->first = p_B;
		}
		if (B_prev) {
			B_prev->next_ptr = p_A;
		} else {
			_data->first = p_A;
		}
		if (A_next) {
			A_next->prev_ptr = p_B;
		} else {
			_data->last = p_B;
		}
		if (B_next) {
			B_next->prev_ptr = p_A;
		} else {
			_data->last = p_A;
		}
		p_A->prev_ptr = A_next == p_B ? p_B : B_prev;
		p_A->next_ptr = B_next == p_A ? p_B : B_next;
		p_B->prev_ptr = B_next == p_A ? p_A : A_prev;
		p_B->next_ptr = A_next == p_B ? p_A : A_next;
	}
	/**
	 * copy the list
	 */
	void operator=(const List &p_list) {
		clear();
		const Element *it = p_list.front();
		while (it) {
			push_back(it->get());
			it = it->next();
		}
	}

	T &operator[](int p_index) {
		
		Element *I = front();
		int c = 0;
		while (c < p_index) {
			I = I->next();
			c++;
		}

		return I->get();
	}

	const T &operator[](int p_index) const {
		

		const Element *I = front();
		int c = 0;
		while (c < p_index) {
			I = I->next();
			c++;
		}

		return I->get();
	}

	void move_to_back(Element *p_I) {
		
		if (!p_I->next_ptr) {
			return;
		}

		if (_data->first == p_I) {
			_data->first = p_I->next_ptr;
		}

		if (_data->last == p_I) {
			_data->last = p_I->prev_ptr;
		}

		if (p_I->prev_ptr) {
			p_I->prev_ptr->next_ptr = p_I->next_ptr;
		}

		p_I->next_ptr->prev_ptr = p_I->prev_ptr;

		_data->last->next_ptr = p_I;
		p_I->prev_ptr = _data->last;
		p_I->next_ptr = nullptr;
		_data->last = p_I;
	}

	void reverse() {
		int s = size() / 2;
		Element *F = front();
		Element *B = back();
		for (int i = 0; i < s; i++) {
			F = F->next();
			B = B->prev();
		}
	}

	void move_to_front(Element *p_I) {
		
		if (!p_I->prev_ptr) {
			return;
		}

		if (_data->first == p_I) {
			_data->first = p_I->next_ptr;
		}

		if (_data->last == p_I) {
			_data->last = p_I->prev_ptr;
		}

		p_I->prev_ptr->next_ptr = p_I->next_ptr;

		if (p_I->next_ptr) {
			p_I->next_ptr->prev_ptr = p_I->prev_ptr;
		}

		_data->first->prev_ptr = p_I;
		p_I->next_ptr = _data->first;
		p_I->prev_ptr = nullptr;
		_data->first = p_I;
	}

	void move_before(Element *value, Element *where) {
		if (value->prev_ptr) {
			value->prev_ptr->next_ptr = value->next_ptr;
		} else {
			_data->first = value->next_ptr;
		}
		if (value->next_ptr) {
			value->next_ptr->prev_ptr = value->prev_ptr;
		} else {
			_data->last = value->prev_ptr;
		}

		value->next_ptr = where;
		if (!where) {
			value->prev_ptr = _data->last;
			_data->last = value;
			return;
		}

		value->prev_ptr = where->prev_ptr;

		if (where->prev_ptr) {
			where->prev_ptr->next_ptr = value;
		} else {
			_data->first = value;
		}

		where->prev_ptr = value;
	}
    List(const List &p_list) {
		const Element *it = p_list.front();
		while (it) {
			push_back(it->get());
			it = it->next();
		}
	}

	List() {}

	~List() {
		clear();
		if (_data) {
			memdelete_allocator<_Data, A>(_data);
		}
	}





};





#endif