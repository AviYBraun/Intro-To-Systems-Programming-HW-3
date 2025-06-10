#pragma once
#include "TaskManager.h"
#include "Person.h"

TaskManager::TaskManager() = default;
void TaskManager::assignTask(const string &personName, const Task &task) {
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




