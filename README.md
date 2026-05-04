Intro To Systems Programming HW 3

Overview
  This project demonstrates the implementation of a Generic Task Management System using a custom-built, template-based Sorted Linked List. It focuses on object-oriented         design, template programming, and iterator implementation in C++.

Project Core
  1. Template-Based SortedList
  The SortedList<T> is the backbone of the system, supporting any data type that implements the > operator.
  - Iterator Pattern: Includes a fully custom ConstIterator class, allowing for standard-compliant traversal (begin() and end()).
  - Functional Programming Hooks:
     - filter: Takes a predicate function and returns a new list containing only elements that satisfy the condition.
     - apply: Takes an operation function and returns a new list where each element has been transformed.
  - Memory Safety: Implements the Rule of Three (Copy Constructor, Assignment Operator, and Destructor) to manage dynamic Node<T> allocations.

  2. Task & Priority System
     - Priority Enforcement: The Task class handles priorities in the range [0,100] .
     - Unique Identification: Each task is assigned a persistent ID used for tracking completion.
     - Type Categorization: Supports various TaskType enums (e.g., Development, Testing, CustomerSupport) to allow for bulk operations.
       
Usage Example:

  // Create a manager
  TaskManager boss;
  
  // Assign tasks with different priorities
  boss.assignTask("Avraham", Task(90, TaskType::Development, "Fix critical kernel bug"));
  boss.assignTask("Avraham", Task(50, TaskType::Documentation, "Write README"));
  
  // Complete the highest priority task (ID of bug fix task)
  boss.completeTask("Avraham");
  
  // Bulk update: Increase priority for all testing tasks
  boss.bumpPriorityByType(TaskType::Testing, 20);
  
  // Print status of all employees
  boss.printAllEmployees();
