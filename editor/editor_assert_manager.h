


#ifndef EDITOR_ASSERT_MANAGER_H
#define EDITOR_ASSERT_MANAGER_H


#include "core/templates/list.h"
#include "core/templates/vector.h"
#include "core/object/ref_counted.h"
#include "core/variant/array.h"
#include "scene/main/window.h"

class TreeItem;
class ListItem;
class Button;
class LineEdit;
class Label;
class HBoxContainer;
class Container;
class ScrollContainer;
class HttpRequest;
class String;



class EditorAssertManager : public RefCounted {
	CLASS(EditorAssertManager , RefCounted);

};

class AssertDialog : public Control {
	CLASS(AssertDialog , Control);
	
public:
protected:
private:
};


#endif // EDITOR_ASSERT_MANAGER_H

