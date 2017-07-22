#pragma once

#ifndef __CORE_ARRAY_EARRAY_H__
#define __CORE_ARRAY_EARRAY_H__

#include "../Core.h"

template<typename InType, typename InAlloc> class EArray {
	template<typename OtherType, typename OtherAlloc> friend class EArray;

public:
	typedef InType Type;
	typedef InAlloc Alloc;

private:
	//Helper functions
	//Move array
	template<typename FromType, typename ToType> static inline typename
		EEnableIf<EngineArray::ECanMoveEArrayPtrBetweenArrayTypes<FromType, ToType>::Value>::Type
		MoveOrCopy(ToType &ToArray, FromType &FromArray, int32_t prevMax) {
		ToArray.AllocatorInstance.MoveToEmpty(FromArray.AllocatorInstance);
		ToArray.ArrayNum = FromArray.ArrayNum;
		ToArray.ArrayMax = FromArray.ArrayMax;
		FromArray.ArrayNum = 0;
		FromArray.ArrayMax = 0;
	}

	//Copy array
	template<typename FromType, typename ToType> static inline typename
		EEnableIf<!EngineArray::ECanMoveEArrayPtrBetweenArrayTypes<FromType, ToType>::Value>::Type
		MoveOrCopy(ToType &ToArray, FromType &FromArray, int32_t prevMax) {
		ToArray.CopyToEmpty(FromArray.GetData(), FromArray.Num(), prevMax, 0);
	}

	//Move array and allocate extra memory
	template<typename FromType, typename ToType> static inline typename
		EEnableIf<EngineArray::ECanMoveEArrayPtrBetweenArrayTypes<FromType, ToType>::Value>::Type
		MoveOrCopyWithExtraAlloc(ToType &ToArray, FromType &FromArray, int32_t prevMax, uint64_t extraAlloc) {
		MoveOrCopy(ToArray, FromArray, prevMax);
		ToArray.Reserve(ToArray.ArrayNum + extraAlloc);
	}

	//Copy array and allocate extra memory
	template<typename FromType, typename ToType> static inline typename
		EEnableIf<!EngineArray::ECanMoveEArrayPtrBetweenArrayTypes<FromType, ToType>::Value>::Type
		MoveOrCopyWithExtraAlloc(ToType &ToArray, FromType &FromArray, int32_t prevMax, uint64_t extraAlloc) {
		ToArray.CopyToEmpty(FromArray.GetData(), FromArray.Num(), prevMax, extraAlloc);
	}

public:
	//Helper functions
	//Is index valid
	inline bool IsValidIndex(int32_t index) const {
		return index >= 0 && index < ArrayNum;
	}

	//Get number of elements
	inline int32_t Num() const {
		return ArrayNum;
	}

	//Get max number of elements in array
	inline int32_t Max() const {
		return ArrayMax;
	}

	//Return size of inner type
	inline uint64_t GetTypeSize() const {
		return sizeof(ElementType);
	}

	//Get memory allocated by the container
	inline uint64_t GetAllocatedSize() const {
		return AllocatorInstance.GetAllocatedSize(ArrayMax, sizeof(ElementType));
	}

	//Get amount of extra allocation in array
	inline uint64_t GetExtraAlloc() const {
		return ArrayMax - ArrayNum;
	}

public:
	//Destructor
	inline virtual ~EArray() {
		DestroyItems(GetData(), ArrayNum);
	}

	//Copy constructors
	inline EArray() : ArrayNum(0), ArrayMax(0) {}
	EArray(std::initializer_list<Type> InitList) {
		//Asserting that initializer_lists iterators are pointers
		CopyToEmpty(InitList.begin(), (int32_t)InitList.size(), 0, 0);
	}
	template<typename OtherType, typename OtherAlloc> inline explicit EArray(const EArray<OtherType, OtherAlloc>&other) {
		CopyToEmpty(other.GetData(), other.Num(), 0, 0);
	}
	inline EArray(const EArray &other) {
		CopyToEmpty(other.GetData(), other.Num(), 0, 0);
	}
	inline EArray(const EArray &other, uint64_t extraAlloc) { //Preceding with extra memory for preallocation
		CopyToEmpty(other.GetData(), other.Num(), 0, extraAlloc);
	}

	//Move constructors
	inline EArray(EArray &&other) {
		MoveOrCopy(*this, other, 0);
	}
	template<typename OtherType, typename OtherAlloc> inline explicit EArray(EArray<OtherType, OtherAlloc> &&other) {
		MoveOrCopy(*this, other, 0);
	}
	template<typename OtherType> inline EArray(EArray<OtherType, Alloc> &&other, uint64_t extraAlloc) {
		MoveOrCopyWithExtraAlloc(*this, other, 0, extraAlloc);
	}

	//Return ptr to first entry
	inline ElementType* GetData() {
		return (ElementType*)AllocatorInstance.GetAllocation();
	}
	inline const ElementType* GetData() const {
		return (const ElementType*)AllocatorInstance.GetAllocation();
	}

	//TODO: Check invariants of array, Check index being in address range

	//Push and pop an element
	inline ElementType Pop(bool allowShrink = true) {
		ElementType ret = MoveTemp(GetData()[ArrayNum - 1]);
		RemoveAt(ArrayNum - 1, 1, allowShrink);
		return ret
	}
	inline void Push(ElementType &&item) {
		Add(MoveTemp(Item));
	}
	inline void Push(const ElementType &&item) {
		Add(Item);
	}

	//Get n-th last element from array
	inline ElementType& Last(int32_t i_sub = 0) {
		int32_t i_new = ArrayNum - i_sub - 1;
		if (!IsValidIndex(i_new)) return NULL;
		return GetData()[i_new];
	}
	inline const ElementType& Last(int32_t i_sub = 0) const {
		int32_t i_new = ArrayNum - i_sub - 1;
		if (!IsValidIndex(i_new)) return NULL;
		return GetData()[i_new];
	}

	//Get the top element (last)
	inline ElementType& Top() {
		return Last();
	}
	inline const ElementType& Top() const {
		return Last();
	}

	//GC for array
	inline void Shrink() {
		if (ArrayMax != ArrayNum) {
			ResizeTo(ArrayNum);
		}
	}

	//Find element starting from beginning
	inline int32_t Find(const ElementType& item) {
		const ElementType* RESTRICT start = GetData();
		for (const ElementType* RESTRICT data = start, *RESTRICT dataEnd = data + ArrayNum; data != dataEnd; ++data) {
			if (*data == item) {
				return static_cast<int32_t>(data - start);
			}
		}
		return INDEX_NONE;
	}
	inline bool Find(const ElementType& item, int32_t& index) const {
		index = this->Find(item);
		return index != INDEX_NONE;
	}

	//Find element starting from end
	inline int32_t FindLast(const ElementType& item) const {
		for (const ElementType* RESTRICT start = GetData(), *RESTRICT data = start + ArrayNum; data != start; ) {
			--data;
			if (*data == item) {
				return static_cast<int32_t>(data - start);
			}
		}
		return INDEX_NONE;
	}
	inline bool FindLast(const ElementType& item, int32_t& index) const {
		index = this->FindLast(item);
		return index != INDEX_NONE;
	}

	//TODO: Find last/item by predicate, find item by key

	//Does array contain the element?
	template<typename ComparisonType> inline bool Contains(const ComparisonType& item) const {
		for (const ElementType* RESTRICT data = GetData(), *RESTRICT dataEnd = data + ArrayNum; data != dataEnd; ++data) {
			if (*data == item) {
				return true;
			}
		}
		return false;
	}

	//TODO: ContainsByPredicate()
	//TODO: Serialization

	//Add cnt uninitialized elements into the array
	inline int32_t AddUninitialized(int32_t cnt = 1) {
		//TODO: Invariant checking
		if (cnt <= 0) {
			return NULL;
		}
		const int32_t n_old = ArrayNum;
		if ((ArrayNum += cnt) > ArrayMax) {
			ResizeGrow(n_old);
		}
		return n_old;
	}

	//Insert cnt uninitialized elements at position pos
	inline int32_t InsertUninitialized(int32_t pos, int32_t cnt = 1) {
		//TODO: Invariant checking
		if (cnt <= 0) {
			return NULL;
		}
		if (!IsValidIndex(pos)) {
			return NULL;
		}
		const int32_t n_old = ArrayNum;
		if ((ArrayNum += cnt) > ArrayMax) {
			ResizeGrow(n_old);
		}
		ElementType* data = GetData() + pos;
		RelocateConstructItems<ElementType>(data + cnt, data, n_old - pos);
		return n_old;
	}

	//Insert cnt zeroed elements at position pos
	inline bool InsertZeroed(int32_t pos, int32_t cnt = 1) {
		if (InsertUninitialized(pos, cnt) != NULL) {
			memset((void*)AllocatorInstance.GetAllocation() + pos * sizeof(ElementType), 0, cnt * sizeof(ElementType));
			return true;
		}
		return false;
	}

	//Insert cnt defaulted elements at position pos
	inline bool InsertDefaulted(int32_t pos, int32_t cnt = 1) {
		if (InsertUninitialized(pos, cnt) != NULL) {
			DefaultConstructItems<ElementType>((uint8*)AllocatorInstance.GetAllocation() + pos * sizeof(ElementType), cnt);
			return true;
		}
		return false;
	}

public:
	//Operators
	inline EArray& operator=(std::initializer_list<InType> InitList) {
		DestroyItems(GetData(), ArrayNum);
		//Asserting initializer_list's iterators are ptrs
		CopyToEmpty(InitList.begin(), (int32_t)InitList.size(), ArrayMax, 0);
		return *this;
	}
	inline EArray& operator=(const EArray &other) {
		if (this != &other) {
			DestroyItems(GetData(), ArrayNum);
			CopyToEmpty(other.GetData(), other.Num(), ArrayMax, 0);
		}
		return *this;
	}
	inline EArray& operator=(const EArray &&other) {
		if (this != &other) {
			DestroyItems(GetData(), ArrayNum);
			MoveOrCopy(*this, other, ArrayMax);
		}
		return *this;
	}
	inline ElementType& operator[](int32_t index) {
		if (!IsValidIndex(index)) return NULL;
		return GetData()[index];
	}
	inline const ElementType& operator[](int32_t index) const {
		if (!IsValidIndex(index)) return NULL;
		return GetData()[index];
	}
	inline bool operator==(const EArray &other) const {
		int32_t cnt = num();
		return cnt == other.Num() && CompareItems(GetData(), other.GetData(), cnt);
		//Do we really have to make it so complicated? Can't we just copy invert the following definition
		//(operator!=)? This would make it a bit easier
	}
	inline bool operator!=(const EArray &other) const {
		return !(*this == other);
	}
	//TODO: Serialization operator (<<)
};

#endif