#ifndef REFERENTIAL_INTEGRITY_MANAGER_H
#define REFERENTIAL_INTEGRITY_MANAGER_H

#include "Faculty.h"
#include "Student.h"
#include "BinarySearchTree.h"

class ReferentialIntegrityManager {

private:

public:
    ReferentialIntegrityManager();
    ~ReferentialIntegrityManager();
    void initializeReferentialIntegrity(BinarySearchTree<int, Student>& treeToInitializeIntegrityOf, BinarySearchTree<int, Faculty>& treeToBaseReferenceOffOf);
    void initializeReferentialIntegrity(BinarySearchTree<int, Faculty>& treeToInitializeIntegrityOf, BinarySearchTree<int, Student>& treeToBaseReferenceOffOf);

};

#endif
