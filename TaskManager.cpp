
#pragma once

 #include "TaskManager.h"

// implementation depends on if Person has default constructor, might need to change after testing.
TaskManager::TaskManager() : employees(new Person("")), size(0), nextID(0){
    for (int i = 1; i < MAX_PERSONS; i++) {
        new(employees + i) Person("");
    }
};


void TaskManager::assignTask(const string &personName, const Task &task) {
    Task newTask(task);
    newTask.setId(nextID);
    for (int i = 0; i < size; i++) {
        if (personName == employees[i].getName()) {
            employees[i].assignTask(newTask);
            nextID++;
            return;
        }
    }
    if (size == MAX_PERSONS) {
        throw std::runtime_error("can't add new employee");
    }
    // if we want to add a new employee, and have resources to do it.
    employees[size].assignTask(newTask);
    size++;
    nextID++;
}


void TaskManager::completeTask(const string &personName) {
    for (int i = 0; i < size; i++) {
        if (personName == employees[i].getName()) {
            employees[i].completeTask();
        }
    }
}


void bumpPriorityByType(TaskType type, int priority) {
    if (priority < 0) {
        return;
    }

}