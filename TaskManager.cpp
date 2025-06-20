#include "TaskManager.h"
#include "Person.h"
#include "SortedList.h"

static TaskType filterType;
bool filterByType(const Task& task) {
        return task.getType() == filterType;
    }
bool filterOutType(const Task& task) {
        return task.getType() != filterType;
    }
static int globalPriority;
Task bumpPriorityOperator(const Task& task) {
    int currentPriority = task.getPriority();
    string currentDescription = task.getDescription();
    TaskType currentType = task.getType();
    int currentId = task.getId();
    Task updated(currentPriority + globalPriority, currentType, currentDescription);
    updated.setId(currentId);
    return updated;
}


TaskManager::TaskManager() = default;
void TaskManager::assignTask(const string& personName, const Task& task) {
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
        if(numberOfWorkers == 10) {
            throw std::runtime_error("Too many workers!");
        }
        Task copy = task;
        copy.setId(currentId);
        currentId++;
        Person currentWorker(personName);
        currentWorker.assignTask(copy);
        workers[numberOfWorkers] = currentWorker;
        numberOfWorkers++;
        return;
    }
    Task copy = task;
    copy.setId(currentId);
    currentId++;
    workers[whereIsWorker].assignTask(copy);
}
void TaskManager::completeTask(const string& personName) {
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
    workers[whereIsWorker].completeTask();
}
void TaskManager::bumpPriorityByType(TaskType type, int priority) {
    if(priority <= 0) {
        return;
    }
    for(int i = 0; i < numberOfWorkers; i++){
        SortedList<Task> currentTasks = workers[i].getTasks();
        filterType = type;
        SortedList<Task> listWithType = currentTasks.filter(filterByType);
        SortedList<Task> listWithoutType = currentTasks.filter(filterOutType);
        globalPriority = priority;
        SortedList<Task> bumped = listWithType.apply(bumpPriorityOperator);
        SortedList<Task> final;
        for(SortedList<Task>::ConstIterator it = bumped.begin(); it != bumped.end(); ++it){
            final.insert(*it);
        }
        for(SortedList<Task>::ConstIterator it = listWithoutType.begin();
            it!= listWithoutType.end(); ++it) {
            final.insert(*it);
        }
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
    for(int i = 0; i < numberOfWorkers; i++) {
        SortedList<Task> employeeTaskList = workers[i].getTasks();
        SortedList<Task> temporaryList = employeeTaskList.filter(filterByType);
        for(SortedList<Task>::ConstIterator it = temporaryList.begin();
            it!= temporaryList.end(); ++it) {
            masterTypeList.insert(*it);
        }
    }
    for(SortedList<Task>::ConstIterator it = masterTypeList.begin();
            it!= masterTypeList.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

void TaskManager::printAllTasks() const {
    SortedList<Task> allTasksList;
    for(int i = 0; i < numberOfWorkers; i++) {
        SortedList<Task> temporaryList = workers[i].getTasks();
        for(SortedList<Task>::ConstIterator it = temporaryList.begin();
            it!= temporaryList.end(); ++it) {
            allTasksList.insert(*it);
        }
    }
    for(SortedList<Task>::ConstIterator it = allTasksList.begin();
        it != allTasksList.end(); ++it) {
        std::cout << *it << std::endl;
    }
}


