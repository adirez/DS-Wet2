//
// Created by adire on 04-Jan-18.
//

#include "TrainingGroup.h"

TrainingGroup::TrainingGroup(int id) {
    if(ID < 0){
        throw InvalidParameter();
    }
    ID = id;
    idx = -1;
}

TrainingGroup::TrainingGroup(int id, int i) {
    if(ID < 0){
        throw InvalidParameter();
    }
    ID = id;
    idx = i;
}

void TrainingGroup::setIdx(int i) {
    idx = i;
}

int TrainingGroup::getIdx() {
    return idx;
}

void TrainingGroup::setID(int id) {
    ID = id;
}

int TrainingGroup::getID() {
    return ID;
}

bool TrainingGroup::operator<(const TrainingGroup &rGroup) const {
    return ID < rGroup.ID;
}

bool TrainingGroup::operator>(const TrainingGroup &rGroup) const {
    return ID > rGroup.ID;
}

bool TrainingGroup::operator<=(const TrainingGroup &rGroup) const {
    return ID <= rGroup.ID;
}

bool TrainingGroup::operator>=(const TrainingGroup &rGroup) const {
    return ID>= rGroup.ID;
}
