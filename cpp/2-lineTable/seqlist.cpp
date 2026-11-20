#include <iostream>
#include <limits>
#include <new>

using ElemType = int;
constexpr int InitSize = 10;

// 动态顺序表：length 是已有元素数量，capacity 是已分配容量。
struct SeqList {
    ElemType* data = nullptr;
    int length = 0;
    int capacity = 0;
};

// 引用参数让函数直接修改原表；只对未初始化或已销毁的表初始化。
bool InitList(SeqList& L) {
    if (L.data != nullptr) {
        return false;
    }
    ElemType* data = new (std::nothrow) ElemType[InitSize];
    if (data == nullptr) {
        return false;
    }
    L.data = data;
    L.length = 0;
    L.capacity = InitSize;
    return true;
}

bool ExpandList(SeqList& L) {
    // 防止容量翻倍时 int 溢出。
    if (L.capacity > std::numeric_limits<int>::max() / 2) {
        return false;
    }
    const int newCapacity = L.capacity == 0 ? InitSize : L.capacity * 2;

    // 1. 先申请新空间。失败时保留原来的数据。
    ElemType* newData = new (std::nothrow) ElemType[newCapacity];
    if (newData == nullptr) {
        return false;
    }

    // 2. 只复制实际存在的元素，下标范围是 [0, length)。
    for (int i = 0; i < L.length; ++i) {
        newData[i] = L.data[i];
    }

    // 3. 释放旧空间。new[] 必须与 delete[] 配对。
    delete[] L.data;

    // 4. 更新地址和容量。扩容没有增加元素，所以 length 不变。
    L.data = newData;
    L.capacity = newCapacity;
    return true;
}

// 教材中的位序 i 从 1 开始，数组下标从 0 开始。
bool ListInsert(SeqList& L, int i, ElemType e) {
    if (i < 1 || i - 1 > L.length) {
        return false;
    }
    if (L.length >= L.capacity && !ExpandList(L)) {
        return false;
    }

    // 从后往前移动，避免覆盖尚未搬走的元素。
    for (int j = L.length; j >= i; --j) {
        L.data[j] = L.data[j - 1];
    }
    L.data[i - 1] = e;
    ++L.length;
    return true;
}

void PrintList(const SeqList& L) {
    for (int i = 0; i < L.length; ++i) {
        std::cout << L.data[i] << ' ';
    }
    std::cout << "\n长度：" << L.length << "，容量：" << L.capacity << '\n';
}

void DestroyList(SeqList& L) {
    delete[] L.data;
    L.data = nullptr;
    L.length = 0;
    L.capacity = 0;
}

// 练习版手动管理内存：不要直接复制 SeqList，否则会共享同一个指针。
// 实际业务通常用 std::vector 管理这些操作。
int main() {
    SeqList L;
    if (!InitList(L)) {
        std::cerr << "初始化失败\n";
        return 1;
    }

    // 第 11 次插入时，容量从 10 扩大到 20。
    for (int value = 1; value <= 12; ++value) {
        if (!ListInsert(L, L.length + 1, value)) {
            std::cerr << "插入失败\n";
            DestroyList(L);
            return 1;
        }
    }
    std::cout << "尾部插入 12 个元素后：\n";
    PrintList(L);

    if (!ListInsert(L, 3, 99)) {
        std::cerr << "插入失败\n";
        DestroyList(L);
        return 1;
    }
    std::cout << "\n在第 3 个位置插入 99 后：\n";
    PrintList(L);

    DestroyList(L);
    return 0;
}
