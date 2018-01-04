//
// Created by adire on 04-Jan-18.
//

#ifndef WET2_TRAININGGROUP_H
#define WET2_TRAININGGROUP_H


class TrainingGroup {
    int ID;
    int idx;

public:
    TrainingGroup(int id) : ID(id), idx(-1) {};
    TrainingGroup(int id, int i) : ID(id), idx(i) {};
    TrainingGroup(const TrainingGroup& group) : ID(group.ID), idx(group.idx) {};
    ~TrainingGroup() = default;
    TrainingGroup& operator=(const TrainingGroup& group) = delete;
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
