#pragma once
#include "TaskManager.h"
#include "Person.h"
#include "SortedList.h"
//make static TaskType variable so that I can use lambda expression later - then we can
//change that variable in the bumpPriorityByType function, and use it in our lambda expression
//make filter predicate functions
static TaskType filterType;
bool filterByType(const Task& task) {
        return task.getType() == filterType;
    }
bool filterOutType(const Task& task) {
        return task.getType() != filterType;
    }
//static priority and operation functions for use in bumpPriorityByType
static int globalPriority;
Task bumpPriorityOperator(const Task& task) {
    int currentPriority = task.getPriority();
    string currentDescription = task.getDescription();
    TaskType currentType = task.getType();
    int currentId = task.getId();
    //construct updated Task with the information from the task passed
    Task updated(currentPriority + globalPriority, currentType, currentDescription);
    updated.setId(currentId);
    return updated;
}


TaskManager::TaskManager() = default;
void TaskManager::assignTask(const string& personName, const Task& task) {
    //check if the person is in the array - if he is in, save his array number for future use

    bool isin = false;
    int whereIsWorker;
    for(int i = 0; i < 10; i++) {
        if (workers[i].getName() == personName) {
            isin = true;
            whereIsWorker = i;
            break;
        }
    }
    //if person isn't in the array
    if(!isin) {
        if(numberOfWorkers == 10) {
            throw std::runtime_error("Too many workers!");
        }
        //1)assign current id to task at hand - need to make a copy, since task is const
        Task copy = task;
        copy.setId(currentId);
        currentId++;
        //2) create new person, given him the task with updated id
        Person currentWorker(personName);
        currentWorker.assignTask(copy);
        //3) set new worker in array, update array counter (numberOfWorkers)
        workers[numberOfWorkers] = currentWorker;
        numberOfWorkers++;
        return;
    }
    //if the person is in the array
    //1) copy the task, set the id
    Task copy = task;
    copy.setId(currentId);
    currentId++;
    //2) assign the task to the person - use array id that we found for worker
    workers[whereIsWorker].assignTask(copy);
}
void TaskManager::completeTask(const string& personName) {
    //check if the worker is in the company
    bool isin = false;
    int whereIsWorker;
    for(int i = 0; i < 10; i++) {
        if (workers[i].getName() == personName) {
            isin = true;
            whereIsWorker = i;
            break;
        }
    }
    if(!isin) {
        return;
    }
    //worker is in the company, use whereIsWorker function to find his array number
    //completeTask function will remove the highest priority task from the list
    workers[whereIsWorker].completeTask();
}
void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    //if int <= 0, function won't do anything
    if(priority <= 0) {
        return;
    }
    for(int i = 0; i < numberOfWorkers; i++){
        //1) make sortedList of current tasks
        SortedList<Task> currentTasks = workers[i].getTasks();
        //2) create two lists with filter - one with specific task, one with other task
        filterType = type;
        SortedList<Task> listWithType = currentTasks.filter(filterByType);
        SortedList<Task> listWithoutType = currentTasks.filter(filterOutType);
        //3) apply the priority raise to listWithType using bumpPriorityOperator from earlier
        globalPriority = priority;
        SortedList<Task> bumped = listWithType.apply(bumpPriorityOperator);
        //4) merge the bumped and listWithoutType into an updated list of worker's tasks
        SortedList<Task> final;
        //iterate through both lists, add to 'final' list
        for(SortedList<Task>::ConstIterator it = bumped.begin(); it != bumped.end(); ++it){
            final.insert(*it);
        }
        for(SortedList<Task>::ConstIterator it = listWithoutType.begin();
            it!= listWithoutType.end(); ++it) {
            final.insert(*it);
        }
        //finally, assign the person his new tasks list
        workers[i].setTasks(final);
    }
}
void TaskManager::printAllEmployees() const {
    for(int i = 0; i < numberOfWorkers; i++) {
        std::cout << workers[i] << std::endl;
    }
}

void TaskManager::printTasksByType(TaskType type) const {
    filterType = type;
    SortedList<Task> masterTypeList;
    //iterate through employees
    for(int i = 0; i < numberOfWorkers; i++) {
        SortedList<Task> employeeTaskList = workers[i].getTasks();
        SortedList<Task> temporaryList = employeeTaskList.filter(filterByType);
        //add temporary list to master
        for(SortedList<Task>::ConstIterator it = temporaryList.begin();
            it!= temporaryList.end(); ++it) {
            masterTypeList.insert(*it);
        }
    }
    //iterate through master list, print using task print method
    for(SortedList<Task>::ConstIterator it = masterTypeList.begin();
            it!= masterTypeList.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

void TaskManager::printAllTasks() const {
    //note: > operator in task.cpp will ensure that == priorities are sorted based on id,
    //so we needn't worry

    //create master list by going through all the employees
    SortedList<Task> allTasksList;
    //iterate through employees
    for(int i = 0; i < numberOfWorkers; i++) {
        SortedList<Task> temporaryList = workers[i].getTasks();
        //iterate through the employee's tasks, add them to allTasksList
        for(SortedList<Task>::ConstIterator it = temporaryList.begin();
            it!= temporaryList.end(); ++it) {
            allTasksList.insert(*it);
        }
    }
    //iterate throughout master list, print all tasks using Task's print method
    for(SortedList<Task>::ConstIterator it = allTasksList.begin();
        it != allTasksList.end(); ++it) {
        std::cout << *it << std::endl;
    }
}


