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

/**
 * @class List
 * A List class that provides a type-safe and convenient way to manage elements in TypeScript.
 */
class List<T> {
  private items: T[];

  /**
   * Creates a new List instance.
   */
  constructor() {
    this.items = [];
  }

  /**
   * Adds an element to the end of the list.
   * @param item The element to add.
   */
  add(item: T): void {
    this.items.push(item);
  }

  /**
   * Same as `add`, adds an element to the end of the list.
   * @param item The element to add.
   */
  push_back(item: T): void {
    this.push(item);
  }
  
  /**
   * Inserts an element at a specific index in the list.
   * @param index The index where to insert the element.
   * @param item The element to insert.
   * @throws {Error} If the provided index is out of bounds.
   */
  insert(index: number, item: T): void {
    if (index < 0 || index > this.items.length) {
      throw new Error("Index out of bounds");
    }
    this.items.splice(index, 0, item);
  }

  /**
   * Removes the first occurrence of the specified element from the list.
   * @param item The element to remove.
   */
   erase(item: T): void {
    const index = this.items.indexOf(item);
    if (index !== -1) {
      this.items.splice(index, 1);
    }
  }

  /**
   * Removes the element at the specified index from the list.
   * @param index The index of the element to remove.
   * @throws {Error} If the provided index is out of bounds.
   */
  remove_at(index: number): void {
    if (index < 0 || index >= this.items.length) {
      throw new Error("Index out of bounds");
    }
    this.items.splice(index, 1);
  }
  
  /**
   * Searches for an element in the list that satisfies the condition defined in the callback function.
   * @param callback A function that takes an element (of type T) and returns a boolean indicating if it matches the criteria.
   * @returns The first element that matches the condition in the callback, or undefined if none is found.
   */
  find(callback: (item: T) => boolean): T | undefined {
    return this.items.find(callback);
  }

  /**
   * Returns the element at the end of the list (the last element).
   * @returns The last element in the list, or undefined if the list is empty.
   */
  end(): T | undefined {
    return this.items[this.size() - 1];
  }
  
  /**
   * Pre-allocates space in the underlying array to potentially improve performance for future insertions.
   * This method doesn't guarantee memory allocation, but adjusts the internal array size to at least the provided size.
   * @param size The desired size for pre-allocation.
   */
  reserve(size: number): void {
    this.items.length = Math.max(this.items.length, size);
  }

  /**
   * Retrieves the element at a specific index in the list.
   * @param index The index of the element to retrieve.
   * @returns The element at the specified index, or undefined if the index is out of bounds.
   */
  get(index: number): T | undefined {
    return this.items[index];
  }

  /**
   * Returns an iterator object that allows you to iterate over the elements in the list.
   * @returns An iterator object that implements the `Iterator<T>` protocol.
   */
  [Symbol.iterator](): Iterator<T> {
    let index = 0;
    const items = this.items;

    return {
      next(): IteratorResult<T> {
        if (index < items.length) {
          return { done: false, value: items[index++] };
        } else {
          return { done: true };
        }
      },
    };
  }

  /**
   * Simulates bracket notation (`[]`) for accessing and modifying elements by index.
   */
  public [index: number]: {
    /**
     * Gets the element at the specified index.
     * @returns The element at the index, or undefined if the index is out of bounds.
     */
    get(): T | undefined;
    /**
     * Sets the element at the specified index.
     * @param value The new value for the element.
     * @throws {Error} If the provided index is out of bounds.
     */
    set(value: T): void;
  };

  /**
   * Creates a new List instance that contains a copy of all elements from the current list.
   * @returns A new List instance with a copy of the elements.
   */
  duplicate(): List<T> {
    const newList = new List<T>();
    for (const item of this) {
      newList.add(item);
    }
    return newList;
  }

  /**
   * Clears all elements from the list.
   */
  clear(): void {
    this.items.length = 0;
  }

  /**
   * Checks if the list is empty.
   * @returns True if the list is empty, false otherwise.
   */
  isEmpty(): boolean {
    return this.items.length === 0;
  }

  /**
   * Returns a sublist containing elements between the specified start and end indices (inclusive).
   * @param startIndex The starting index (inclusive).
   * @param endIndex The ending index (inclusive).
   * @throws {Error} If the provided indices are out of bounds or endIndex is less than startIndex.
   * @returns A new List instance containing the sublist.
   */
  sublist(startIndex: number, endIndex: number): List<T> {
    if (startIndex < 0 || startIndex > endIndex || endIndex >= this.items.length) {
      throw new Error("Invalid start or end index");
    }
    const sublist = new List<T>();
    for (let i = startIndex; i <= endIndex; i++) {
      sublist.add(this.items[i]);
    }
    return sublist;
  }

  
}
