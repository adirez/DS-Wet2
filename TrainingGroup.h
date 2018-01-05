//
// Created by adire on 04-Jan-18.
//

#ifndef WET2_TRAININGGROUP_H
#define WET2_TRAININGGROUP_H

#include "Exceptions.h"

class TrainingGroup {
    int ID;
    int idx;

public:
    TrainingGroup();
    TrainingGroup(int id);
    TrainingGroup(int id, int i);
    TrainingGroup(const TrainingGroup& group) : ID(group.ID), idx(group.idx) {};
    ~TrainingGroup() {};
    void setIdx(int i);
    int getIdx();
    void setID(int id);
    int getID();
    bool operator<(const TrainingGroup& rGroup) const;
    bool operator>(const TrainingGroup& rGroup) const;
    bool operator<=(const TrainingGroup& rGroup) const;
    bool operator>=(const TrainingGroup& rGroup) const;
};

#endif //WET2_TRAININGGROUP_H
