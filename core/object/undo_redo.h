/**
 * MIT License

Copyright (c) 2024/2025 rPatsher

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
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

    Vector<Action> undoStack;
    Vector<Action> redoStack;

protected:
    void _bind_method() {}
};





