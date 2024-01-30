// undo_redo.h
#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include "core/typedefs.h"
#include "core/object/m_object.h"
#include <vector>
#include <functional>


class UndoRedo : public Object {
  CLASS(UndoRedo , Object);

public:
    UndoRedo();
    ~UndoRedo();

    // Push a new action onto the undo stack
    void add_action(const std::function<void()>& doAction, const std::function<void()>& undoAction);

    // Perform undo operation
    void undo();

    // Perform redo operation
    void redo();

    // Get the singleton instance of UndoRedo
    static UndoRedo& get_singleton();
private:
    struct Action {
        std::function<void()> doAction;
        std::function<void()> undoAction;
    };

    std::vector<Action> undoStack;
    std::vector<Action> redoStack;

protected:
    void _bind_method() {}
};





