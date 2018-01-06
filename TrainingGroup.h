//
// Created by adire on 04-Jan-18.
//

#ifndef WET2_TRAININGGROUP_H
#define WET2_TRAININGGROUP_H

#include "Exceptions.h"

/**
 * class representing a training group of gladiators
 * each group has a unique id and an index that represents in which the group is in in the heap
 */
class TrainingGroup {
    int ID;
    int idx;

public:
    TrainingGroup();
    TrainingGroup(int id);
    TrainingGroup(int id, int i);
    TrainingGroup(const TrainingGroup& group) : ID(group.ID), idx(group.idx) {};
    ~TrainingGroup() {};
    //set the index of the group to i
    void setIdx(int i);
    //get the index of the group in which the group is in the heap's array at the moment
    int getIdx();
    //set the id of the group
    void setID(int id);
    //get the id of the group
    int getID();
    //compares 2 groups by their id
    bool operator<(const TrainingGroup& rGroup) const;
    bool operator>(const TrainingGroup& rGroup) const;
    bool operator<=(const TrainingGroup& rGroup) const;
    bool operator>=(const TrainingGroup& rGroup) const;
};

#endif //WET2_TRAININGGROUP_H
