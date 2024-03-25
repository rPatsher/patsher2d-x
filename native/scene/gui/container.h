#ifndef CONTAINER_H
#define CONTAINER_H


#include "scene/gui/control.h" 
#include "core/templates/vector.h" 


class Container : public Control {
	CLASS(Container, Control);
	
	bool pending_sort = false;
	void _sort_children();
	void _child_minsize_changed();

protected:
	void queue_sort();
	
	virtual void add_child_notify(Node *p_child);
	virtual void move_child_notify(Node *p_child);
	virtual void remove_child_notify(Node *p_child);


public:
	enum {
		NOTIFICATION_PRE_SORT_CHILDREN = 50,
		NOTIFICATION_SORT_CHILDREN = 51,
	};

	void fit_child_in_rect(Control *p_child, const Rect2 &p_rect);

	virtual Vector<int> get_allowed_size_flags_horizontal() const;
	virtual Vector<int> get_allowed_size_flags_vertical() const;
	
private:
	void bind_methods(); 
	Vector<int> flags;
	Vector<Node> children;
};


class HboxContainer : public Container {
	CLASS(HboxContainer , Container);


};

class VboxContainer : public Container {
	CLASS(HboxContainer , Container);


};






#endif // 