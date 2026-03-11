#include "TaskManager.h"
#include <stdexcept>
#include <iostream>

namespace mtm {

/*** comparison for SortedList<Person> ***/
bool operator>(const Person& a, const Person& b) {
    return a.getName() > b.getName();  // alphabetical order
}

/*** 4.3.1 assignTask ***/
void TaskManager::assignTask(const std::string& person_name, const Task& task) {
    for (auto it = persons.begin(); it != persons.end(); ++it) {
        if (it->getName() == person_name) {
            Task new_task = task;
            new_task.setId(next_task_id++);
            persons.getMutable(it).assignTask(new_task);
            return;
        }
    }

    if (persons.length() >= MAX_PERSONS) {
        throw std::runtime_error("Maximum number of persons reached");
    }

    Person new_person(person_name);
    Task new_task = task;
    new_task.setId(next_task_id++);
    new_person.assignTask(new_task);
    persons.insert(new_person);
}

/*** 4.3.1 completeTask ***/
void TaskManager::completeTask(const std::string& person_name) {
    for (auto it = persons.begin(); it != persons.end(); ++it) {
        if (it->getName() == person_name) {
            persons.getMutable(it).completeTask();
            return;
        }
    }
    // if person not found → do nothing (spec)
}

/*** 4.3.1 bumpPriorityByType ***/
void TaskManager::bumpPriorityByType(TaskType type, int amount) {
    if (amount == 0) return;
    for (auto it = persons.begin(); it != persons.end(); ++it) {
        SortedList<Task> new_tasks;
        for (auto t_it = it->getTasks().begin(); t_it != it->getTasks().end(); ++t_it) {
            Task updated = *t_it;
            if (updated.getType() == type)
                updated.setPriority(updated.getPriority() + amount);
            new_tasks.insert(updated);
        }
        persons.getMutable(it).setTasks(new_tasks);
    }
}

/*** 4.3.2 printAllEmployees ***/
void TaskManager::printAllEmployees() const {
    for (auto it = persons.begin(); it != persons.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

/*** 4.3.2 printAllTasks ***/
void TaskManager::printAllTasks() const {
    SortedList<Task> all_tasks;
    for (auto it = persons.begin(); it != persons.end(); ++it) {
        for (auto t_it = it->getTasks().begin(); t_it != it->getTasks().end(); ++t_it) {
            all_tasks.insert(*t_it);
        }
    }
    for (auto t_it = all_tasks.begin(); t_it != all_tasks.end(); ++t_it) {
        std::cout << *t_it << std::endl;
    }
}

/*** 4.3.2 printTasksByType ***/
void TaskManager::printTasksByType(TaskType type) const {
    SortedList<Task> filtered;
    for (auto it = persons.begin(); it != persons.end(); ++it) {
        for (auto t_it = it->getTasks().begin(); t_it != it->getTasks().end(); ++t_it) {
            if (t_it->getType() == type)
                filtered.insert(*t_it);
        }
    }
    for (auto t_it = filtered.begin(); t_it != filtered.end(); ++t_it) {
        std::cout << *t_it << std::endl;
    }
}

} // namespace mtm
