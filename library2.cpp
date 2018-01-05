//
// Created by adire on 05-Jan-18.
//

#include "library2.h"
#include "Colosseum.h"

void* init(int n, int* trainingGroupsIDs){
    if(n < 2) return NULL;
    Colosseum *DS;
    try {
        DS = new Colosseum(n, trainingGroupsIDs);
    } catch(...) {
        return NULL;
    }
    return DS;
}

StatusType addTrainingGroup(void* DS, int trainingGroupID){
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    Colosseum *colosseum = (Colosseum *) DS;
    try {
        colosseum->addTrainingGroup(trainingGroupID);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    } catch (InvalidParameter &e) {
        return INVALID_INPUT;
    } catch (KeyAlreadyExists &e) {
        return FAILURE;
    } catch (...) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType addGladiator(void* DS, int gladiatorID, int score, int trainingGroup){
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    Colosseum *colosseum = (Colosseum *) DS;
    try {
        colosseum->addGladiator(gladiatorID, score, trainingGroup);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    } catch (InvalidParameter &e) {
        return INVALID_INPUT;
    } catch (KeyAlreadyExists &e) {
        return FAILURE;
    } catch (...) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType trainingGroupFight(void* DS, int trainingGroup1, int trainingGroup2, int k1, int k2){
    if (DS == NULL) {
        return INVALID_INPUT;
    }
    Colosseum *colosseum = (Colosseum *) DS;
    try {
        colosseum->trainingGroupFight(trainingGroup1, trainingGroup2, k1, k2);
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    } catch (InvalidParameter &e) {
        return INVALID_INPUT;
    } catch (KeyAlreadyExists &e) {
        return FAILURE;
    } catch (Failure &e) {
        return FAILURE;
    } catch (...) {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType getMinTrainingGroup(void* DS, int* trainingGroup){
    if (DS == NULL || trainingGroup == NULL) {
        return INVALID_INPUT;
    }
    Colosseum *colosseum = (Colosseum *) DS;
    try {
        *trainingGroup = colosseum->getMinTrainingGroup();
    } catch (std::bad_alloc &e) {
        return ALLOCATION_ERROR;
    } catch (InvalidParameter &e) {
        return INVALID_INPUT;
    } catch (KeyAlreadyExists &e) {
        return FAILURE;
    } catch (Failure &e) {
        return FAILURE;
    } catch (...) {
        return FAILURE;
    }
    return SUCCESS;
}

void quit(void** DS){
    if (DS != NULL) {
        delete(((Colosseum*)*DS));
        *DS = NULL;
    }
}