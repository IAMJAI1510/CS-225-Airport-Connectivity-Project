
/**
 * @file minheap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>
#include "minheap.h"
//#include "graph.h"
#include "airport.h"



size_t MinHeap::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    return 1;
}


size_t MinHeap::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    if(!hasAChild(currentIdx)) return 0;
    return 2*currentIdx;
}


size_t MinHeap::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    if(2*currentIdx+1>=_elems.size()) return 0;
    return 2*currentIdx+1;
}


size_t MinHeap::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    if (currentIdx==1) return 0;
    int idx= (int) currentIdx;
    return idx/2;
}


bool MinHeap::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    return 2*currentIdx<_elems.size();
}


size_t MinHeap::minPriorityChild(size_t currentIdx) const

{
    if(!hasAChild(currentIdx)) return 0;
    if(leftChild(currentIdx)&&!rightChild(currentIdx))  return leftChild(currentIdx);
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
   if (_elems[2*currentIdx]->getDjiDist()<_elems[2*currentIdx+1]->getDjiDist()) return 2*currentIdx;//changed
   return 2*currentIdx+1;
}
 

void MinHeap::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    if(hasAChild(currentIdx)){
        size_t idx= minPriorityChild(currentIdx);
        //if(idx==0) return;
        if(_elems[currentIdx]->getDjiDist()>_elems[idx]->getDjiDist()){//changed
            Airport* temp= _elems[idx];
            _elems[idx]=_elems[currentIdx];
            _elems[currentIdx]=temp;
            heapifyDown(idx);
        }
    }
}


void MinHeap::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (_elems[currentIdx]->getDjiDist()< _elems[parentIdx]->getDjiDist()) {//changed
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}


MinHeap::MinHeap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    _elems.push_back(NULL);
}


MinHeap::MinHeap(const std::vector<Airport*>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    _elems=elems;
    _elems.insert(_elems.begin(),NULL);
    for( size_t i=parent(_elems.size()-1);i>0; i--) heapifyDown(i);
}


Airport* MinHeap::pop()
{
    // @TODO Remove, and return, the element with highest priority
    if(_elems.size()==1) return NULL;

    Airport* temp=_elems[1];
    _elems[1]= _elems[_elems.size()-1];

    _elems.pop_back();
    heapifyDown(1);
    return temp;
    
    
    
}


Airport* MinHeap::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    if(_elems.size()>1) return _elems[1];
    return NULL;
}


void MinHeap::push( Airport*& elem)
{
    // @TODO Add elem to the heap
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}


void MinHeap::updateElem(const size_t & idx,  Airport*& elem)
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
    _elems[idx]=elem;
    for( size_t i=parent(_elems.size()-1);i>0; i--) heapifyDown(i);
}

void MinHeap::update()
{
    // @TODO In-place updates the value stored in the heap array at idx
    // Corrects the heap to remain as a valid heap even after update
   
    for( size_t i=_elems.size()-1;i>0; i--) heapifyDown(i);
}



bool MinHeap::empty() const
{
    // @TODO Determine if the heap is empty
    if(_elems.size()==1) return true;
    return false;
}


void MinHeap::getElems(std::vector<Airport*> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
void MinHeap::newFront(Airport* a){
    uint idx;
    for(uint i=1; i<_elems.size(); i++){
        if(_elems[i]->getName()==a->getName()){
            idx=i;
            break;
        }
    }
//std::cout<<_elems[idx]->getName();
    std::swap(_elems[idx], _elems[1]);
}
