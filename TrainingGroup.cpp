//
// Created by adire on 04-Jan-18.
//

#include "TrainingGroup.h"

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
